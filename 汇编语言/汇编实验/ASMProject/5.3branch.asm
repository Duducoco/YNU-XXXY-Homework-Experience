DATA SEGMENT
	XD DB 38H
	ZER DB "0", 0DH, 0AH, "$"
	MINUS DB "-1", 0DH, 0AH, "$"
	PLUS DB "1", 0DH, 0AH, "$"
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE,DS:DATA	
start:MOV AX,DATA
	MOV	DS,AX

	MOV AL, XD			;获取X的值
	CMP AL, 0			;判断是否为0
	JNZ COM				;不是0，则去判断正负
	MOV DX, OFFSET ZER	;把字符串0的偏移地址送入DX
	JMP EN				;转向结束

COM:AND AL, 80H			;判断最高位是否为1
	CMP AL, 0		
	JZ PL				;是0，正数
	MOV DX, OFFSET MINUS;把字符串-1的偏移地址送入DX
	JMP EN
PL:	MOV DX, OFFSET PLUS	;把字符串1的偏移地址送入DX

EN:	MOV AH, 09H			;输出内容
	INT 21H
	
	MOV AH, 4CH
	INT 21H
	
CODE ENDS
	END start
