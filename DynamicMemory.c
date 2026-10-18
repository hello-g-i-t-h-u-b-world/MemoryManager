#include "DynamicMemory.h"

#define SIZE 108

typedef struct Header
{
    int size;
    int next;
} Header;

char storageArr[SIZE];
int head;

void initStorageArr(){
    Header* pHeader = (Header*)&storageArr[0];
    pHeader->size = SIZE - 8;
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
}

void myfree(int start_address) {
    
}