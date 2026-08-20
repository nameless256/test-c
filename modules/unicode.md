好问题。Unicode 码点范围里有一些**关键边界和特殊区域**，开发中踩坑率很高，列出来给你。

## 一、BMP / 非 BMP 边界

```
BMP (Plane 0):    U+0000  ~  U+FFFF    —— 基本多语言平面
SMP (Plane 1):    U+10000 ~  U+1FFFF   —— 多语言补充平面
SIP (Plane 2):    U+20000 ~  U+2FFFF   —— 表意文字补充平面
TIP (Plane 3):    U+30000 ~  U+3FFFF   —— 表意文字第三平面
SSP (Plane 14):   U+E0000 ~  U+EFFFF   —— 专用补充平面
PUA-A (Plane 15): U+F0000 ~  U+FFFFF   —— 私用区 A
PUA-B (Plane 16): U+100000 ~ U+10FFFF  —— 私用区 B
```

**核心注意点：**

- **UTF-16 中 BMP 字符占 2 字节，非 BMP 字符占 4 字节（代理对 surrogate pair）**
- JavaScript 的 `String.length` 会把代理对算成 2 个字符 → 坑
- Python 3.3+ 内部统一用灵活表示，但 `len()` 返回的是码点数量（Python 层面没问题）
- 数据库 MySQL utf8 只支持 BMP（3 字节），要用 `utf8mb4` 才能存 emoji 等非 BMP 字符

## 二、必须记住的特殊范围

### 1. 代理区（Surrogates）
```
U+D800  ~  U+DFFF  (高代理 + 低代理)
```
- **永远不能出现在合法的 Unicode 文本中**
- 只在 UTF-16 编码过程中作为中间表示
- 如果你自己拼字符串时直接塞了 `\uD800`，很多库会崩

### 2. 私用区（Private Use Area）
```
PUA:      U+E000  ~  U+F8FF    (BMP 内)
PUA-A:    U+F0000 ~  U+FFFFF   (Plane 15)
PUA-B:    U+100000 ~ U+10FFFF  (Plane 16)
```
- 字体厂商自定义字符（如图标字体）、企业内部编码
- **不同系统/字体下显示完全不同**
- 做文本处理时如果遇到 PUA 字符，通常需要特殊处理

### 3. 非字符（Noncharacters）
```
U+FDD0  ~  U+FDEF
U+FFFE, U+FFFF
U+1FFFE, U+1FFFF
U+2FFFE, U+2FFFF
... 一直到 U+10FFFE, U+10FFFF
```
- Unicode 标准保留的"非字符"，**不允许用于交换**
- 但有些系统内部用它做特殊标记（如 Windows 用 U+FFFF 做某些内部标记）
- 你如果做文本校验，应该拒绝这些码点

### 4. 控制字符（C0 + C1）
```
C0:   U+0000 ~ U+001F  (含 \t \n \r)
C1:   U+0080 ~ U+009F
```
- C0 里只有 `U+0009`(Tab)、`U+000A`(LF)、`U+000D`(CR) 是"允许的空白"
- 其他 C0/C1 控制字符在文本处理中通常需要过滤或转义
- `U+0000`(NUL) 尤其危险——C 语言字符串终结符

### 5. BOM（Byte Order Mark）
```
U+FEFF  — 零宽不换行空格（ZWNBSP）/ BOM
U+FFFE  — 非字符（用于检测字节序）
```
- 文件开头 `U+FEFF` 作为 BOM 标记 UTF-16/UTF-32 字节序
- 很多解析器不处理 BOM 会出问题
- UTF-8 不需要 BOM，但 Windows 记事本会加（`\xEF\xBB\xBF`）

### 6. 零宽字符（Zero Width）
```
U+200B  — 零宽空格（ZWSP）
U+200C  — 零宽非连接符（ZWNJ）
U+200D  — 零宽连接符（ZWJ）
U+FEFF  — 零宽不换行空格（BOM）
U+2060  — 单词连接符
```
- 不可见，但会影响文本处理、字符串比较、正则匹配
- **ZWJ 序列**（如 `U+200D` 连接多个 emoji）是 emoji 组合的关键

### 7. 组合字符（Combining Characters）
```
U+0300 ~ U+036F  — 组合变音符号
U+20D0 ~ U+20FF  — 组合符号
U+FE00 ~ U+FE0F  — 异体字选择符（VS1-VS16）
U+E0100 ~ U+E01EF — 异体字选择符补充（VS17-VS256）
```
- 一个"视觉字符"可能由多个码点组成
- `é` 可以是 `U+00E9`（预组合），也可以是 `U+0065` + `U+0301`（分解形式）
- 做字符串比较/搜索时，需要先做 **NFC 规范化**（`unicodedata.normalize('NFC', s)`）

## 三、实用速查表

```python
# Python 检查示例
import unicodedata

def classify_codepoint(cp):
    if 0xD800 <= cp <= 0xDFFF:
        return "代理区 (Surrogate)"
    if 0xFDD0 <= cp <= 0xFDEF or cp in {0xFFFE, 0xFFFF} or cp >= 0x1FFFE:
        return "非字符 (Noncharacter)"
    if 0xE000 <= cp <= 0xF8FF or 0xF0000 <= cp <= 0x10FFFF:
        return "私用区 (PUA)"
    if cp <= 0x1F or 0x80 <= cp <= 0x9F:
        return "控制字符"
    if cp == 0xFEFF:
        return "BOM"
    cat = unicodedata.category(chr(cp))
    return f"常规字符, 分类={cat}"
```

## 四、开发中常见坑

| 场景 | 坑 | 对策 |
|------|----|------|
| JS `"😂".length` | 返回 2（代理对） | 用 `[...str].length` 或 `Array.from` |
| MySQL `utf8` 存 emoji | 报错 `Incorrect string value` | 用 `utf8mb4` |
| 正则 `\w` 匹配中文 | 不匹配 | 用 `\p{L}` 或显式范围 |
| 字符串排序 | 组合字符顺序不同 | 先 NFC 规范化 |
| 文件解析 BOM | 第一个字符是 `\uFEFF` | 读文件时跳过 BOM |
| 用户输入过滤 | 零宽字符注入 | 白名单校验 |

有具体场景需要深入的吗？比如某个语言/框架下的 Unicode 处理？