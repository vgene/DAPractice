# DAPractice
数算大作业－判决文书中的金额项提取

***
	MODIFIED BY:Ultimanecat
	DATE:20151013
	
	chonly: change data.csv into chonly.txt, which only contains chinese characters, except some marks. Exceptions are set at BANLIST.
	wordfreq: count all word frequency in chonly.txt . Will cost some time. output:wordfreq.txt. Note that threshold value of output at #define thr
	wordfreq_acautomachine: Make things clear. input:wordfreq.txt, output: wordfreq_acautomachine.txt. Note that threshold value of insertion at #define thr
	charfreq: doesn't make any sense so far. May be very useful from now on :D. input:chonly.txt
***



***
	MODIFIED BY:VEGE ZIYANG
	DATE:20151008

1) S | “元”不是数字；BUG；大写汉字
2) T | 按数字分隔模型；按字符数量分隔模型；按行分隔模型
3) S<-->T | 之后讨论

***

＃UPDATE:
	MODIFIED BY:VEGE ZIYANG
	DATE:20151006

*0xcd 0xf2 万*

已处理万元情况

未处理大写数字情况

***

# UPDATE：
	MODIFIED BY:VEGE ZIYANG
	DATE:20151006

~~未处理万元情况!~~


***

#UPDATE:
	MODIFIED BY:VEGE ZIYANG
	DATE:20151006
Ascii:

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

***

#PLAN:
	MODIFIED BY:VEGE ZIYANG
	DATE:20151004
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

