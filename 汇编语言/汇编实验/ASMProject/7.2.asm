DATAS SEGMENT
    RES DW 0001H    ;存放结果
DATAS ENDS
CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS
START:
    MOV AX, DATAS
    MOV DS, AX      
    MOV AX, 2       ;被乘数
    MOV CX, 65535   ;近似死循环
    HEAD:
    MOV BX, AX      ;
    INC BX          ;让BX = AX+1
    MUL BX          ;AX存放AX*BX的内容
    ADD RES, AX      ;结果累加
    CMP RES, 200     ;结果与200比较
    JNB ED          ;如果大于等于200，则跳转结束
    MOV AX, BX      ;否则让AX等于BX，继续循环
    LOOP HEAD
    ED:
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START