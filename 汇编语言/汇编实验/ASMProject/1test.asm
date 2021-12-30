;数据段，名字为DATA
DATA SEGMENT
	X   DB 0E5H		;定义一个字节，名字叫X，数据为E5H
	Y   DB 34H		;定义一个字节，名字叫Y，数据为34H
	W   DW ?		;定义一个字，名字叫W，暂不指定数据
DATA ENDS

;代码段，名字为CODE
CODE SEGMENT
	;指定CS的内容为CODE段的地址，DS的内容为DATA段的地址
	ASSUME CS:CODE,DS:DATA
START:	MOV	AX,	DATA	;将DATA段的地址赋值给寄存器AX
	    MOV	DS,	AX		;将AX寄存器的内容赋值给DS
	    XOR	AH,	AH		;将AH的内容与AH的内容异或，即让AH为0
	    MOV	AL,	X		;将数据段中的X送入AL
	    ADD	AL,	Y		;将AL与数据段中的Y相加，结果放入AL
	    ADC	AH,	0		;带符号位加法，如果X+Y大于255，那么AH即为1，否则为0
	    MOV	W,	AX		;将寄存器AX的内容送入数据段中的W
		;结束程序，返回操作系统
	    MOV	AH,	4CH		
	    INT 21H			
CODE ENDS				;代码段结束
END START
