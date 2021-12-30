WINWIDTH	=	40					;宽度	
WINTOP		=	8					;上边界
WINLEFT		=	20					;左边界
WINBOTTOM	=	17					;下边界
WINRIGHT	=	WINLEFT+WINWIDTH-1	;右边界
COLOR		=	74H					;颜色
PAGEN		=	0					;页码
CTRL_C		=	03H			
CODE SEGMENT
	ASSUME CS:CODE
START:	MOV	AL,	PAGEN				;第0页
		MOV	AH,	5					;选择活动显示页
		INT	10H						;选择活动显示页为第0页
		;设置图形范围
		MOV	CH,	WINTOP				
		MOV	CL,	WINLEFT
		MOV	DH,	WINBOTTOM
		MOV	DL,	WINRIGHT

		MOV	BH,	COLOR				;设置背景色和前景色
		MOV	AL,	0					;清除
		MOV	AH,	6					;向上滚动窗口
		INT	10H
		;
		MOV	BH,	PAGEN				;第0页
		MOV	DH,	WINBOTTOM			;最底行
		MOV	DL,	WINLEFT				;最左的列
		MOV	BH,	COLOR				;颜色
		MOV	AH,	2
		INT	10H						;设置光标位置

NEXT:	MOV	AH,	0					;
		INT	16H						;从键盘读入一个字符存入AL
		CMP	AL,	CTRL_C				;
		JE	EXIT					;如果键盘按下CTRL C，则退出

		MOV	BH,	PAGEN				;页码为0
		MOV	CX,	1					;打印一次
		MOV	AH,	0AH					;
		INT	10H						;在光标位置写入字符

		INC	DL						;列数增加
		CMP	DL,	WINRIGHT+1			;当前列是否达到了窗口最右侧
		JNE	SETCUR					;不是的话，则跳转
		MOV	CH,	WINTOP				;窗口上边界
		MOV	CL,	WINLEFT				;窗口左边界
		MOV	DH,	WINBOTTOM			;窗口下边界
		MOV	DL,	WINRIGHT			;窗口右边界
		MOV	BH,	COLOR				;设置颜色
		MOV	AL,	1					;滚动1行
		MOV	AH,	6					;向上滚动窗口
		INT	10H						
		MOV	DL,	WINLEFT				;让最右的列改到最左

SETCUR:	MOV	BH,	PAGEN				;设置第0页
		MOV	AH,	02H					;设置光标位置
		INT	10H						
		JMP	NEXT					;跳转，再次从键盘接收字符
EXIT:	MOV	AH,	4CH
		INT	21H
CODE ENDS
	END	START
