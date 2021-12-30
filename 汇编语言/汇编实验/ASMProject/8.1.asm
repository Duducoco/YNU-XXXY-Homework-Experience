DATA SEGMENT
A	DB	'How do you do?',0AH,0DH
	DB	'$'
B	DB	20, ?, 20 DUP(?)
DATA ENDS
CODE SEGMENT
	ASSUME	CS:CODE,DS:DATA
START:	MOV	AX,	DATA
	MOV	DS,	AX
	MOV	AH,	09H		;
	LEA	DX,	A		;把A字符串的首地址送入DX
	INT	21H			;输出A字符串
	LEA	DX,	B		;把B数组首地址送入DX
	MOV	AH,	0AH		;
	INT	21H			;取键盘输入，输入内容存放在B数组，B数组第一个单元存放输入的个数
	MOV	DL,	0AH		;将DL置为0AH
	MOV	AH,	02H		;
	INT	21H			;输出换行
	MOV	AL,	B+1		;AL为输入字符串中的字符个数
	MOV	AH,	0
	MOV	SI,	AX		;SI为输入字符串中的字符个数
	MOV	DX,	OFFSET B+2	;
	MOV	BX,	DX		;输入字符串首地址送入BX
	MOV	BYTE PTR [BX+SI+1], '$'		;输入字符串末尾添加'$'符号
	MOV	AH,	09H		;
	INT	21H			;调用中断，输出输入的字符串
	MOV	AH,	4CH
	INT	21H
CODE	ENDS
	END	START
