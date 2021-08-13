# parser实现思路

1. 由一个driver函数驱动逐个token解析
2. 默认在driver中先解析```KeyWord```，各个解析出的stmt按照Block的方式串联起来
3. 在各个解析出的stmt中对应调用ParsePrimaryExpr
4. 在```ParsePrimaryExpr()```对```lexer::CurrentToken```依据类型分别解析```LiteralNum, LiteralString, Operator, Separator, Identifier```

