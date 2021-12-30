STACK   SEGMENT PARA    STACK   'STACK'
        DB      64 DUP(0)
STACK   ENDS

DSEG    SEGMENT
        ;音乐频率
        MUS_FREQ        DW      330,294,262,294,3 DUP(330)
                        DW      3 DUP (294),330,392,392
                        DW      330,294,262,294,4 DUP(330)
                        DW      294,294,330,294,262,-1
        ;音乐节拍
        MUS_TIME        DW      6 DUP(25),50
                        DW      2 DUP(25,25,50)
                        DW      12 DUP(25),100
DSEG    ENDS

CSEG    SEGMENT
        ASSUME  CS:CSEG,SS:STACK,DS:DSEG
MUSIC   PROC                    ;MUSIC进程  
        MOV     AX,DSEG         
        MOV     DS,AX
        LEA     SI,MUS_FREQ     ;MUS_FREQ的偏移地址送入SI
        LEA     BP,DS:MUS_TIME  ;MUS_TIME的偏移地址送入BP
FREQ:
        MOV     DI,[SI]         ;从MUS_FREQ数组取出一个字送入DI
        CMP     DI,-1           ;判断音乐是否结束
        JE      END_MUS         ;如果相等，则跳转结束
        MOV     BX,DS:[BP]      ;从MUS_TIME数组取出一个字送入BX
        ;保护寄存器
        PUSH    AX
        PUSH    BX
        PUSH    CX
        PUSH    DX
        PUSH    DI
        ;将AL的值从43H端口输出
        MOV     AL,0B6H         ;向计数器写控制字
        OUT     43H,AL          ;方式3，双字节和二进制计数方式写到控制口
        MOV     DX,12H          ;设置被除数
        MOV     AX,348CH        ;将348CH送入AX
        DIV     DI              ;商为AX，
        OUT     42H,AL          ;先送LSB
        MOV     AL,AH           
        OUT     42H,AL          ;再送MSB
        IN      AL,61H          ;从61H端口获取数据，送入AL
        MOV     AH,AL           ;把AH送入AL
        OR      AL,3            ;将AL与3进行或运算
        OUT     61H,AL          ;接通扬声器
        ;BX增加两倍
        ADD     BX, BX
        ADD     BX, BX
        ;产生延迟时间
back:   MOV     CX,     663        ;设置循环次数为663
        PUSH    AX              ;保存AX的内容
WAITF1:
        IN      AL,61H          ;从61H端口获取数据送入AL
        AND     AL,10H          ;
        CMP     AL,AH
        JE      WAITF1
        MOV     AH,AL
        LOOP    WAITF1
        ;恢复AX
        POP     AX
        DEC     BX              ;循环持续BX次，即传进来的节拍时间
        JNZ     back
        MOV     AL,AH           ;写回61H端口，关闭扬声器
        OUT     61H,AL          
        ;恢复寄存器
        POP     DI
        POP     DX
        POP     CX
        POP     BX
        POP     AX
        ADD     SI,2            ;取下一个频率值
        ADD     BP,2            ;取下一时间节拍
        JMP     FREQ            ;循环，继续发声
END_MUS:
        MOV     AX,4C00H
        INT     21H
MUSIC   ENDP
CSEG    ENDS
        END     MUSIC
