#include <stdio.h>
#include <stdlib.h>

#define INVALID -1
#define TOTAL_VP 8 // 页表大小
#define total_instructions 17
//页表
typedef struct page_struct {
    int pn;   //页号
    int pfn;  //页面号
    int time; //时间
} page_type;
page_type page_table[TOTAL_VP];

//free和busy表
typedef struct page_node {
    int pn;
    int pfn;
    struct page_node *next;
} pfc;

pfc *free_head; //空闲链表头
pfc *busy_head; //已用链表头
pfc *busy_tail; //已用链表尾

//每一条指令的页号
typedef struct instruction {
    int pn;
} instruction;

instruction instructions[total_instructions]; //指令

int diseffect;

//初始化
void initialize(int total_pf) {
    free_head = NULL;
    //初始化页表
    for (int i = 0; i < TOTAL_VP; i++) {
        page_table[i].pn = i;
        page_table[i].pfn = INVALID;
        page_table[i].time = 0;
    }
    //初始化空闲页面
    for (int i = 0; i < total_pf; i++) {
        pfc *new_node = (pfc *) malloc(sizeof(pfc));
        new_node->pn = INVALID; //空闲页面没有页号
        new_node->pfn = i;
        new_node->next = free_head;
        free_head = new_node;
    }
}

//每一条命令访问的页号
void init_inst() {
    int tmp[total_instructions] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1};
    for (int i = 0; i < total_instructions; i++) {
        instructions[i].pn = tmp[i];
        printf("%d ", instructions[i].pn);
    }
    printf("\n");
}

void FIFO(int total_pf) {
    //total_pf表示页面数
    initialize(total_pf);
    diseffect = 0;
    pfc *p;
    busy_head = busy_tail = NULL;
    for (int i = 0; i < total_instructions; i++) {
        //找到需要的页号
        int pn = instructions[i].pn;
        if (page_table[pn].pfn == INVALID) {
            //页面不存在
            diseffect++;

            if (free_head == NULL) {
                //从busy链表中取出放入free链表
                p = busy_head->next; //保留
                page_table[busy_head->pn].pfn = INVALID;
                free_head = busy_head;
                free_head->next = NULL; ////改的这里
                busy_head = p;
            }
            //从free中取出
            p = free_head->next;
            free_head->next = NULL;
            free_head->pn = pn;
            page_table[pn].pfn = free_head->pfn;

            //放入busy链表
            if (busy_tail == NULL) {
                busy_head = busy_tail = free_head;
            } else {
                busy_tail->next = free_head;
                busy_tail = free_head;
            }
            free_head = p;
        }
    }
    printf("FIFO:%.2f%%\n", (1 - (float) diseffect / total_instructions) * 100);
}

void LRU(int total_pf) {
    int min_time;
    int min_j;
    pfc *p = NULL, *prep = NULL;
    diseffect = 0;
    initialize(total_pf);
    int present_time = 0;
    for (int i = 0; i < total_instructions; i++) {
        int pn = instructions[i].pn;
        if (page_table[pn].pfn == INVALID) {
            diseffect++;
            if (free_head == NULL) {
                //找到最早进入的页面
                min_time = 65535;
                for (int j = 0; j < TOTAL_VP; j++) {
                    if (page_table[j].time < min_time && page_table[j].pfn != INVALID) {
                        min_time = page_table[j].time;
                        min_j = j;
                    }
                }
                prep = NULL;
                p = busy_head;
                while (p != NULL) {
                    if (p->pn == min_j) {
                        break;
                    }
                    prep = p;
                    p = p->next;
                }

                //从busy链表中取出
                if (prep == NULL) {
                    busy_head = p->next;
                } else {
                    prep->next = p->next;
                }
                //放入free链表
                free_head = p;
                free_head->next = NULL;

                page_table[min_j].pfn = INVALID;
                page_table[min_j].time = -1;
            }

            //从free中取出一个p
            p = free_head;
            free_head = free_head->next;
            p->pn = pn;
            p->next = NULL;

            //把p插入busy链表
            if (busy_tail == NULL) {
                busy_head = p;
            } else {
                busy_tail->next = p;
            }

            busy_tail = p;

            page_table[pn].pfn = p->pfn;
            page_table[pn].time = present_time;
        } else {
            page_table[pn].time = present_time;
        }
        present_time++;
    }
    printf("LRU:%.2f%%\n", (1 - (float) diseffect / total_instructions) * 100);
}

int main() {
    printf("Query Order:\n");
    init_inst();
    printf("Three Pages ");
    FIFO(3);
    printf("Three Pages ");
    LRU(3);
    printf("Four Pages ");
    FIFO(4);
    printf("Four Pages ");
    LRU(4);
    return 0;
}
