CODES SEGMENT
    ASSUME CS:CODES
START:
    MOV AX, 1234H       ;给AX赋值
    ;保留把AL的低4位，并送入DL，得到AX的1-4位
    MOV DL, AL          
    AND DL, 0FH

    ;将AH的低4位送入BL，得到AX的9-12位
    MOV BL, AH
    AND BL, 0FH
    
    ;把AH的高4位送入CH,最后送入AL
    MOV CH, AH
    AND CH, 0F0H
    ;AL右移4位，得到AX的13-16位
    MOV CL, 4
    SHR CH, CL

    ;保留AL中的高4位，并送入DH
    MOV DH, AL
    AND DH, 0F0H
    ;把DH右移4位，既是AX的5-8位
    MOV CL, 4
    SHR DH, CL
    ;将结果送入CL
    MOV CL, DH

    ;把AX的13-16位送入AL
    MOV AL, CH


    MOV AH,4CH
    INT 21H
CODES ENDS
    END START