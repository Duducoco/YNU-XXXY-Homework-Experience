CODE SEGMENT
	ASSUME	CS:CODE
START:	
	MOV	AX,	0002H	;设置显示模式	
	INT	10H			;
	MOV	AH,	02H		;设置光标位置选项
	MOV	BH,	00H		;第0页
	MOV	DX,	0524H	;第5H行第24H列
	INT	10H			;设置光标位置
	MOV	AH,	09H		;
	MOV	BH,	00H		;第0页
	MOV	BL,	2CH		;设置颜色
	MOV	AL,	'G'		;设置输出的字符
	MOV	CX,	8		;设置打印次数
	INT	10H			;在当前光标位置写字符和属性
	MOV	AH,	02H		;设置光标位置选项
	MOV	BH,	00H		;第0页
	MOV	DX,	0A24H	;第0AH行，第24H列
	INT	10H			;设置光标位置
	MOV	AH,	09H		;
	MOV	BH,	00H		;第0页
	MOV	BL,	1EH		;设置颜色
	MOV	AL,	'O'		;设置输出字符为'o'
	MOV	CX,	8		;设置输出次数为8
	INT	10H			;在当前光标位置写字符和属性
	MOV	AH,	02H		;设置光标位置选项
	MOV	BH,	00H		;第0页
	MOV	DX,	0F24H	;第0FH行，第24H列
	INT	10H			;设置光标位置
	MOV	AH,	09H		;
	MOV	BH,	00H		;第0页
	MOV	BL,	4FH		;设置颜色
	MOV	AL,	'O'		;设置输出字符为'o'
	MOV	CX,	8		;设置输出次数为8
	INT	10H			;在当前光标位置写字符和属性
	MOV	AH,	02H		;设置光标位置选项
	MOV	BH,	00H		;第0页
	MOV	DX,	1424H	;第14H行，第24H列
	INT	10H			;设置光标位置
	MOV	AH,	09H		
	MOV	BH,	00H		;第0页
	MOV	BL,	02H		;设置颜色
	MOV	AL,	'D'		;设置输出字符为'D'
	MOV	CX,	8		;设置输出次数为8
	INT	10H			;在当前光标位置写字符和属性
	MOV	AH,	4CH		
	INT	21H
CODE	ENDS
	END	START
