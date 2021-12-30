DATAS SEGMENT
    a DB 2
    b DB -4
    c DB -18
    d DB -13
    RESL DW ?
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX

    MOV AL, a       ;将a送入AL
    IMUL b          ;有符号乘，AL*b，结果送入AX,完成运算a*b
    ADD AX, 10      ;a*b+10
    MOV BX, 10      ;将10送入BX
    IMUL BX         ;有符号乘，AX*BX,结果送入DX,AX
                    ;由于结果是小于16位数，故DX为0
                    ;完成运算((a*b)+10)*10
Z:  MOV CH, 0FFH    ;CX高位全置为1
    MOV CL, c       ;将c送入CL
                    ;此时，CX中即为c的补码
    ADD AX, CX      ;完成运算((a*b)+10)*10+c
    IMUL BX         ;有符号乘10，(((a*b)+10)*10+c)*10
                    ;结果送入DX,AX   由于结果是小于16位数，故DX为0
Z2: MOV BH, 0FFH    ;BX高位赋为0
    MOV BL, d       ;d送入BL
                    ;此时，BX为d的补码    
    ADD AX, BX      ;完成运算(((a*b)+10)*10+c)*10+d
    MOV RESL, AX    ;将运算结果送入RESL内容单元

    MOV AH,4CH
    INT 21H
CODES ENDS
    END START