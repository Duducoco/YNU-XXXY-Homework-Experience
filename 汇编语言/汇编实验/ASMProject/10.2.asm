DATA SEGMENT
    COUNT DW 1
    MESS DB 'The bell is ring!', 0DH, 0AH, '$'
DATA ENDS
CODE SEGMENT
    ASSUME CS: CODE, DS: DATA, ES: DATA
    MAIN PROC FAR
START:  MOV      AX,     DATA
        MOV      DS,     AX
        ;获得1CH的中断程序入口地址，保存在ES和BX寄存器中
        MOV      AL,     1CH           
        MOV      AH,     35H           
        INT      21H
        ;保存寄存器的值
        PUSH     ES                    
        PUSH     BX                    
        PUSH     DS
        MOV      DX,    OFFSET   RING     ;RING子程序偏移地址送DX
        MOV      AX,    SEG   RING        ;RING子程序段地址送AX
        MOV      DS,    AX                ;AX送入DS
        ;设置中断向量，终端号为1C，中断程序入口为DS:DX
        MOV      AL,    1CH               
        MOV      AH,    25H          
        INT      21H                   
        POP      DS                 ;恢复DS的值
        IN       AL,      21H       ;从21H号端口输入8位数据到AL寄存器
        AND      AL,      11111110B ;将AL的最低位置0
        OUT      21H,     AL        ;将置0后的数据从21H号端口输出
        STI                         ;允许中断发生
        ;设置延时
        MOV      DI,      60000       
DELAY:  MOV      SI,      60000         
DELAY1: DEC      SI
        JNZ     DELAY1
        DEC     DI
        JNZ     DELAY
        ;恢复寄存器
        POP     DX                    
        POP     DS
        ;设置中断向量，终端号为1C，中断程序入口为DS:DX
        MOV     AL,      1CH
        MOV     AH,      25H
        INT     21H
        ;程序结束
        MOV     AH,      4Ch
        INT     21H
MAIN    ENDP

    ;RING子程序
    RING:
        ;保护寄存器
        PUSH    DS 
        PUSH    AX
        PUSH    CX
        PUSH    DX
        MOV     AX,      DATA
        MOV     DS,      AX
        STI                      ;允许中断发生
        DEC     COUNT            ;次数减1
        JNZ     EXIT             ;如果为0，则退出
        ;屏幕输出MESS字符串
        MOV     DX,     OFFSET   MESS   
        MOV     AH,     09H
        INT     21H
        MOV     DX,     100     ;设置DX为100.循环SOUND 100 次
        IN      AL,     61H     ;从61H端口取出数据到AL
        AND     AL,     0FCH    ;修改AL的值
SOUND:  XOR     AL,     02      ;修改AL的值
        OUT     61H,    AL      ;将修改后的值输出到61H端口      
        MOV     CX,     0F400H  ;设置循环次数
WAIT1:  LOOP    WAIT1           ;循环，延时作用      
        DEC     DX              ;DX递减
        JNE     SOUND           ;如果DX不为0，则继续发声
        MOV     COUNT, 18       ;将COUNT置为18
EXIT:   CLI                     ;禁止中断发生         
        ;恢复寄存器
        POP     DX
        POP     CX
        POP     AX
        POP     DS
        sti         ;允许中断发生
        IRET                          
CODE    ENDS
    END     START
