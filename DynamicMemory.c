#include <stdio.h>
#include "DynamicMemory.h"

char storageArr[SIZE];
int head;

void initStorageArr(){
    Header* pHeader = (Header*)&storageArr[0];
    pHeader->size = SIZE - HEADER_SIZE;
    pHeader->next = -1;
    head = 0;
}

int myalloc(int request_size) {
    if ((SIZE - 8) < request_size) {
        return -1; // 최대 용량 초과
    }

    int ptr, bsize;

    Header* pHeader = (Header*)&storageArr[head];
    
    // next가 존재 시 next로 이동
    if (pHeader->next != -1) {
        head = pHeader->next;
        pHeader = (Header*)&storageArr[head];
    }

    bsize = pHeader->size;
    pHeader->size = request_size;
    pHeader->next = -1;
    ptr = head + 8;

    // 빈 공간 생성
    pHeader = (Header*)&storageArr[ptr + request_size];
    pHeader->size = bsize - (request_size + 8);
    pHeader->next = -1;

    return 0;
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
        Header* pHeader = (Header*)&storageArr[h];
        if(count > 0 ){
            printf(" -> ");
        }
        printf("[start: %d], size: %d, next: %d", h, pHeader->size, pHeader->next);
        h = pHeader->next;

        if(++count > SIZE / HEADER_SIZE){
            printf("오류 발생");
            break;
        }
    }
    printf("\n");
}