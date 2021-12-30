DATAS SEGMENT
    X DW 8
DATAS ENDS
CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;BX = 2X^4
    MOV BX, X
    ;8 = 2^3，2X^4 = 2^13，所以8左移10位即可得到2X^4
    MOV CL, 10  
    SHL BX, CL
    ;AX = 3X^3
    MOV AX, X
    ;8左移6位得到8^3
    MOV CL, 6
    SHL AX, CL
    ;AX乘3得到结果，DX为0，AX存放的既是结果
    MOV DX, 3
    MUL DX
    ;BX = 2X^4 + 3X^3
    ADD BX, AX
    ;DX = 5X^2
    MOV AX, X
    ;8左移3位即得到X^2
    MOV CL, 3
    SHL AX, CL
    ;结果乘5，DX为0，AX中存放的就是结果
    MOV DX, 5
    MUL DX
    ;BX = 2X^4 + 3X^3 +　5X*2   
    ADD BX, AX
    ;AX = 2X^4 + 3X^3 +　5X*2 + 8X + 6
    MOV AX, X
    ;乘8，即8左移3位
    MOV CL, 3
    SHL AX, CL
    ADD AX, BX
    ;加6
    ADD AX, 6
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START