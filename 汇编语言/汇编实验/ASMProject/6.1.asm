DATAS SEGMENT
    ARRAY DW 0013H, 0009H, 0002H, 0034H, 0028H, 0012H, 0049H, 0099H, 0023H, 0039H
    TAR DW 0089H
    OUTC DB 'N', '$'
DATAS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;CX 是 i
    ;外层循环
    MOV CX, 0
OER:CMP CX, 9               ;为9则退出循环
    JZ E
    ;内层循环
    ;DX是j
    MOV DX, 0
IER:MOV AX, 9
    SUB AX, CX              ;DX < AX
    CMP DX, AX
    JZ EI                   ;如果DX等于9-AX，则内层循环结束
    ;让AX和BX存放相邻两个字单元的内容
    MOV SI, DX;
    ADD SI, DX;
    MOV AX, [SI]
    MOV BX, [SI+2]
    CMP AX, BX
    JNC EI0                 ;如果AX大于BX则进入下一次循环
    ;如果AX小于等于BX，则交换内存中两个数的位置
    MOV WORD PTR [SI], BX
    MOV WORD PTR [SI+2], AX
EI0:INC DX
    JMP IER
    ;内层循环结束
EI: INC CX
    JMP OER
    ;外层循环结束

    ;查找一个数
E:  MOV CX, 0   ;设置CX为计数器
QRY:CMP CX, 10
    JZ PUT      ;循环结束，跳转到输出
    LODSW       ;从串中取一个字到AX
    CMP AX, TAR ;与目标数比较
    JZ Y        ;若相等，则跳转，输出置为'Y'

    INC CX
    JMP QRY     ;循环
Y:  MOV OUTC, 'Y';输出设置为'Y'
PUT:MOV DX, OFFSET OUTC
    ;利用9号中断输出
    MOV AH, 09H
    INT 21H

LAS:MOV AH,4CH
    INT 21H
CODES ENDS
    END START