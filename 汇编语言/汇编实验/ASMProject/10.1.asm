DATA SEGMENT
	DATA1 DB 'INPUT NUMBER1-8 (QUIT: Ctrl-C)--$'
DATA ENDS

STACK SEGMENT PARA STACK 'STACK'
	STA	DW	32 DUP(?)
STACK ENDS

CODE SEGMENT
	ASSUME	CS:CODE, DS:DATA, SS:STACK, ES:DATA
START:  MOV	AX,	DATA
	MOV	DS,	AX		
	MOV	ES,	AX	
	;输出换行	
	KKK:
	MOV	AH,	02H
	MOV	DL,	0DH
	INT	21H
	MOV	AH,	02H 			
	MOV	DL,	0AH
	INT	21H

	;输出DATA1字符串
    MOV AH,	09H
	MOV	DX, OFFSET DATA1
	INT	21H
	;获取键盘输入，存入AL
	MOV	AH,	01H		
	INT	21H
	;将AL与CTRL/C比较
	CMP	AL,	03H		
	JZ PPP			;遇到CTRL/C则跳转结束
	CMP	AL,	30H		;
	JBE	TTT			;如果小于等于30H，数值上小于等于0，跳转继续输入
	CMP AL,	39H		;与数值上的9比较
	JA TTT			;如果大于9，则跳转继续输入
	SUB	AL,	30H		;让AL中存放数值
	XOR	AH,	AH		;AH清零，且CF置0
	MOV BP,	AX		;AX送入BP
	;发出声音
GGG:MOV	AH,	02H
	MOV	DL,	07h
	INT	21H

    MOV BX, 100
back: MOV CX, 663
	PUSH AX
	
	;产生延迟时间
WAITF1:  
	IN AL,61H
	AND AL,10H
        CMP     AL,AH
        JE      WAITF1
        MOV     AH,AL
        LOOP    WAITF1
        POP     ax
        dec     bx
        jnz     back
        DEC     BP                      
	JNZ	GGG
	
TTT:JMP	KKK			
PPP:MOV	AX,	4C00H		
	INT	21H
CODE	ENDS
	END	START
