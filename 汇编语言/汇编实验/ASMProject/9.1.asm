DATAS SEGMENT
    GRADE DB 76, 69, 84, 90, 73, 88, 99, 63, 100, 80
    S6 DB 0
    S7 DB 0
    S8 DB 0
    S9 DB 0
    S10 DB 0
DATAS ENDS

STACKS SEGMENT
    DW 17 DUP(0)
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS, SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;保存寄存器
    PUSH AX
    PUSH CX
    PUSH SI
    CALL CAL                ;调用子程序
    MOV AH,4CH
    INT 21H
    CAL:MOV CX, 10              ;循环次数
    MOV SI, OFFSET GRADE
    LOP:
    LODSB                   ;将成绩送入AL
    CMP AL, 100
    JZ HUD                  ;100
    CMP AL, 90
    JNB NIE                 ;90-99
    CMP AL, 80
    JNB EIT                 ;80-89
    CMP AL, 70
    JNB SET                 ;70-79
    CMP AL, 60              
    JNB SIT                 ;60-69
        HUD:
        INC S10             ;计数器递增
        JMP E
        NIE:
        INC S9              ;计数器递增
        JMP E
        EIT:
        INC S8              ;计数器递增
        JMP E
        SET:
        INC S7              ;计数器递增
        JMP E
        SIT:
        INC S6              ;计数器递增
        JMP E
E:  LOOP LOP
    ;恢复寄存器
    POP SI
    POP CX
    POP AX
    RET
CODES ENDS
    END START