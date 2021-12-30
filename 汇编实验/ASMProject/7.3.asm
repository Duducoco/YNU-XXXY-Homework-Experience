DATAS SEGMENT
    AD DB 01H, 02H,03H,04H,05H,06H,07H,08H,09H,0AH,0BH,0CH,0DH,0EH,0FH
    BD DB 01H,02H,03H,04H,05H,11H,12H,13H,14H,15H,0AH,0BH,0CH,0DH,0EH,1AH,1BH,1CH,1DH,1EH
    CD DB 15 DUP(?)
DATAS ENDS
CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    MOV SI, OFFSET AD
    MOV DI, OFFSET CD   ;CD的首地址
    OUTER:
    LODSB               ;取出数据放到AL
    CMP SI,15           ;循环结束则退出
    JZ ED
    ;内层循环20次
    MOV CX,20
        INNER:
        ;从后往前
        MOV BX, CX
        DEC BX
        ;与AL比较
        CMP AL, BD[BX]
        JNZ LPI
        ;相等，则把AL送入主存单元
        MOV BYTE PTR [DI], AL
        INC DI
        ;不相等，继续循环
        LPI:
        LOOP INNER
    JMP OUTER
ED: MOV AH,4CH
    INT 21H
CODES ENDS
    END START