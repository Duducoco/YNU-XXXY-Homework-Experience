DATAS SEGMENT
    CHAR DB  'aBCEFghi15OXyZ',0DH
    RES  DB ?
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX

    ;将字符串的偏移地址送入DI
    MOV SI, OFFSET CHAR
    MOV CL, 0       ;用CL表示字符的个数

    CLD             ;DF置0
CST:LODSB           ;串传送指令，每次传送一个字节到AL
    ;让AL与0D比较
    CMP AL, 0DH     
    JZ CEN          ;若相等，则跳转到CEN
    INC CL          ;不相等，则CL加1,跳转到CST继续串传送
    JMP CST

;到这里结束
CEN:MOV RES, CL     ;将CL的值送入RES单元
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START