# markdown语法速查

## 标题
### 标题 1
#### 标题 2
##### 标题 3
###### 标题 4

## 强调

- **粗体**
- *斜体*
- ***粗体加斜体***

## 引用

> 引用
> > 嵌套引用

## 列表

1. 有序列表项1
   - 无序嵌套列表项1
   - 无序嵌套列表项2
2. 有序列表项2

## 链接

这是一个链接 [Markdown语法](https://markdown.com.cn)。

这是一个链接 [Markdown语法](https://markdown.com.cn "最好的markdown教程")。

<https://markdown.com.cn>

<fake@example.com>

[hobbit-hole][1]

[1]: https://en.wikipedia.org/wiki/Hobbit#Lifestyle

## 图片

这是一个链接 [![img.png](img.png)](https://markdown.com.cn "最好的markdown教程")。

## 表格

| Syntax      | Description | Test Text     |
| :---        |    :----:   |          ---: |
| Header      | Title       | Here's this   |
| Paragraph   | Text        | And more      |

## 代码块

`行间代码`

```json
{
  "firstName": "John",
  "lastName": "Smith",
  "age": 25
}
```

## 脚注

Here's a simple footnote,[^1] and here's a longer one.[^bignote]

[^1]: This is the first footnote.

[^bignote]: Here's one with multiple paragraphs and code.

    Indent paragraphs to include them in the footnote.

    `{ my code }`

    Add as many paragraphs as you like.

## 标题编号

### My Great Heading {#t1}