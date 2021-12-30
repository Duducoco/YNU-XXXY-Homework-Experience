DATA SEGMENT
    BUF	DB 38H, 73H, 8FH
    PL DB "plus", 0DH, 0AH, '$'
	MI DB "minux", 0DH, 0AH, '$'
DATA ENDS

CODE SEGMENT
	ASSUME CS:CODE,DS:DATA	
start:MOV AX,DATA
	MOV	DS,AX
	MOV CL, 3			;BUF单元的数量为3
	MOV SI, OFFSET BUF	;将BUF偏移地址送入SI
S:	CMP CL, 0			;将CL于0比较，判断是否遍历完3个数字
	JZ RT				;如果是0，则结束传送
	DEC CL				;CL递减

	LODSB 				;从BUF单元中传送一个字节到AL
	AND AL, 80H			;AL与80H相与
	CMP AL, 0			;如果是0，说明是正数
	JZ PLUS				

	MOV DX, OFFSET MI	;否则是负数，将"minus"单元偏移地址送入DX
    MOV AH, 09H			;利用9号中断输出
    INT 21H
	JMP S
	
PLUS:MOV DX, OFFSET PL	;是正数，将"plus"单元偏移地址送入DX
    MOV AH, 09H			;利用9号单元输出
    INT 21H
	JMP S
	
RT:	MOV	AH,4CH
	INT	21H
CODE ENDS
	END start
