DATAS SEGMENT
    RES DB ?, "$"
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    
    ;1号中断，输入数据到AL中
    MOV AH, 01H
    INT 21H
    
    MOV CL, 61H         ;把a的ASCII码送入CL
    MOV DL, 7AH         ;把z的ASCII码送入DL
    SUB AL, CL          ;计算AL与CL之间的差值，结果存入AL
    SUB DL, AL          ;让DL减去差值，结果即为倒数与该字母序号相同的那个字母
    MOV RES, DL         ;将结果存入RES单元

    MOV DX, OFFSET RES  ;将RES单元的偏移地址送入DX中
    MOV AH, 09H         ;执行9号中断，输出首地址为DX的字符串，以"$"结束
    INT 21H

    MOV AH,4CH
    INT 21H
CODES ENDS
    END START