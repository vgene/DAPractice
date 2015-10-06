MODIFIED BY:VEGE ZIYANG
DATE:20151004

PLAN:

提取金额
	找“元”，向前找到金额，考虑以上特例

		问题
			逗号 合计
			万元 括号 算式
			美元 


提取关键字
	上下文
	统计词频 切词（关键字 费 金 息）
	按照词频结果 人工筛选（去掉明显不是金额类型的，人工改变权重，按照词长加权）

		问题
			变更 减半 多个key合计

金额关键词匹配
	key词频 距离 前后
	关键词match后弹出

		问题
			关键词不能跳一个数字管之后的数字


MODIFIED BY:VEGE ZIYANG
DATE:20151006


0x0d 0x0a CR LF
0x2c COMMA ','
0xa3 0xac CHINESE COMMA '，'
0xd4 0xaa 元

算法：

1. 按行截取（getline(cin,str))
2. 找documentID，找到行号置为0，更新documentID；找不到的话，行号＋＋，documentID不变。
3. 置字符偏移量为0。
4. 在一行中找“元”，记录下“元”字符第一个byte（0xd4）的偏移量（按byte计，从0开始）。
5. 在“元”前找第一个出现的数字，找到后入栈（忽略逗号），数字找完后出栈，将数字变为字符串。
6. 重复4，5步，直到一行内“元”搜索完。

UPDATE：
未处理万元情况！
			