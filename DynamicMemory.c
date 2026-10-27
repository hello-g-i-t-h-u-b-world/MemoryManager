#include <stdio.h>
#include "DynamicMemory.h"

char storageArr[SIZE];
int head;

void initStorageArr(){
    Header* pHead = (Header*)&storageArr[0];
    pHead->size = SIZE - HEADER_SIZE;
    pHead->next = -1;
    head = 0;
}

int myalloc(int request_size) {
    if (request_size <= 0 || request_size > SIZE - HEADER_SIZE) {
        return -1; // 최대 용량 초과
    }

    int prev = -1;
    int h = head;

    Header* phead = NULL; 
    
    // 빈 공간 찾기
    while (h != -1){
        phead = (Header*)&storageArr[h];
        if(phead->size >= request_size){
            break;
        }
        prev = h;
        h = phead->next;
    }

    if(h == -1){
        return -1;
    }

    return h + HEADER_SIZE;
}

void myfree(int start_address) {
    
}

void printFreeList(){
    printf(" 리스트 : ");
    if(head == -1){
        printf("(빈 공간 없음)\n");
        return;
    }

    int h = head;
    int count = 0;
    while(h != -1){
        Header* pHead = (Header*)&storageArr[h];
        if(count > 0 ){
            printf(" -> ");
        }
        printf("[start: %d, size: %d, next: %d]", h, pHead->size, pHead->next);
        h = pHead->next;

        if(++count > SIZE / HEADER_SIZE){
            printf("오류 발생");
            break;
        }
    }
    printf("\n");
}