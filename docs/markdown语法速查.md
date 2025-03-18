# markdown语法速查

## 目录
1. [标题](#-t1)
2. [强调](#-t2)
3. [引用](#-t3)
4. [列表](#-t4)
5. [链接](#-t5)
6. [图片](#-t6)
7. [表格](#-t7)
8. [代码块](#-t8)
8. [脚注](#-t9)
8. [标题编号](#-t10)
8. [定义列表](#-t11)
8. [删除线](#-t12)
8. [任务列表](#-t13)

## 标题 {#t1}
### 标题 1
#### 标题 2
##### 标题 3
###### 标题 4

## 强调 {#t2}

- **粗体**
- *斜体*
- ***粗体加斜体***

## 引用 {#t3}

> 引用
> > 嵌套引用

## 列表 {#t4}

1. 有序列表项1
   - 无序嵌套列表项1
   - 无序嵌套列表项2
2. 有序列表项2

## 链接 {#t5}

这是一个链接 [Markdown语法](https://markdown.com.cn)。

这是一个链接 [Markdown语法](https://markdown.com.cn "最好的markdown教程")。

<https://markdown.com.cn>

<fake@example.com>

[hobbit-hole][1]

[1]: https://en.wikipedia.org/wiki/Hobbit#Lifestyle

## 图片 {#t6}

这是一个链接 [![img.png](img.png)](https://markdown.com.cn "最好的markdown教程")。

## 表格 {#t7}

| Syntax      | Description | Test Text     |
| :---        |    :----:   |          ---: |
| Header      | Title       | Here's this   |
| Paragraph   | Text        | And more      |

## 代码块 {#t8}

`行间代码`

```json
{
  "firstName": "John",
  "lastName": "Smith",
  "age": 25
}
```

## 脚注 {#t9}

Here's a simple footnote,[^1] and here's a longer one.[^bignote]

[^1]: This is the first footnote.

[^bignote]: Here's one with multiple paragraphs and code.

    Indent paragraphs to include them in the footnote.

    `{ my code }`

    Add as many paragraphs as you like.

## 标题编号 {#t10}

### My Great Heading {#demo}

[demo](#my-great-heading-demo)

## 定义列表 {#t11}

First Term
: This is the definition of the first term.

Second Term
: This is one definition of the second term.
: This is another definition of the second term.

## 删除线 {#t12}

~~删除线~~

## 任务列表 {#t13}

- [ ] 1
- [x] 2
- [ ] 3
- [ ] 4