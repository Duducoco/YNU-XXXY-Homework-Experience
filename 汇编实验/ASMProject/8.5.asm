DATA SEGMENT
	ROW	DW 0		;行
	COL	DW 160		;列
	COLOR DB 3		;颜色
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE ,DS:DATA
START: 
    MOV AX,DATA
    MOV DS,AX	

	PUSH AX			
	MOV	AX,	0004H		
	INT	10H			;设置显示模式为4号

	MOV	AH,	0BH		
	MOV	BH,	01H		;设置调色板
	MOV	BL,	00H		;调色板ID
	INT	10H			
	
	MOV	AH,	0CH		;设置写图形像素模式
	MOV	AL,	COLOR	;设置颜色
	MOV	DI,	200		;长度
	MOV	DX,	ROW		;设置x为ROW

	MOV CX, COL		;设置列
P:	INT 10H			;填充像素颜色
	INC DX			;下一行
	DEC DI			;次数减1
	JNZ P

L:	MOV AX, 0		;死循环，避免出现程序结束提示
	JMP L	

    MOV AH,4CH
    INT 21H
CODE ENDS
    END START