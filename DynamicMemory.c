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

    //남은 공간에 빈 블럭 생성
    int remain = phead->size - request_size;
    int emptyBlock = h + HEADER_SIZE + request_size;
    
    Header* pEmptyBlock = (Header*)&storageArr[emptyBlock];

    if(remain > HEADER_SIZE){
        pEmptyBlock->size = remain - HEADER_SIZE;
        pEmptyBlock->next = phead->next;
        phead->size = request_size;
    }
    else {
        // 남은 공간이 부족하면 블럭 전체 할당: 다음 빈 블럭을 연결
        emptyBlock = phead->next;
    }
    phead->next = -1;

    // 리스트 연결
    if(prev == -1){
        head = emptyBlock;
    } 
    else {
        Header* pPrev = (Header*)&storageArr[prev];
        pPrev->next = emptyBlock;
    }

    return h + HEADER_SIZE;
}

void myfree(int start_address) {
    int h = start_address - HEADER_SIZE;
    Header* phead = (Header*)&storageArr[h];

    // 리스트 맨 앞으로
    phead->next = head;
    head = h;
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