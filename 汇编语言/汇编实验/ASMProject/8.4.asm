DATA SEGMENT
	ROW	DW 0
	COL	DW 0			
	COLOR DB 1
DATA ENDS

CODE SEGMENT
	ASSUME	CS:CODE,DS:DATA
START:MOV AX, DATA
	MOV	DS,	AX
	
	MOV	AH,	15		
	INT	10H			;获取当前显示模式，放入AL

	PUSH AX			
	MOV	AX,	0004H		
	INT	10H			;设置显示模式为4号

	MOV	AH,	0BH		
	MOV	BH,	01H		;设置调色板
	MOV	BL,	00H		;调色板ID
	INT	10H			

	MOV	CX,	3		;设置CX为3
	;以下保存寄存器的值
@1:	PUSH	AX
	PUSH	CX
	PUSH	DX
	PUSH	SI
	PUSH	DI
	
	MOV	AH,	0CH		;设置写图形像素模式
	MOV	AL,	COLOR	;设置颜色
	MOV	DI,	100		;
	MOV	DX,	ROW		;设置x为ROW
@@1:MOV	SI,	20		
	MOV	CX,	COL		;设置y为COL
@@2:INT	10H			;	
	INC	CX			;CX递增
	DEC	SI			;SI递减
	JNZ	@@2			;如果SI不为0，则跳转继续设置写图形像素模式
	INC	DX			;DX递增
	DEC	DI			;DI递减
	JNZ	@@1			;如果DI不为0，则跳转
	;恢复寄存器的值
	POP	DI			
	POP	SI
	POP	DX
	POP	CX
	POP	AX
	;从键盘获取一个字符
	MOV AH,01H
	INT 21H

	INC	COLOR		;修改颜色
	ADD	COL,	40	;修改列
	LOOP	@1		;循环
	POP	AX			;恢复AX
	MOV	AH,	0H		;设置显示模式
	INT	10H		
	
	MOV	AH,	4CH		
	INT	21H
CODE	ENDS
	END	START
