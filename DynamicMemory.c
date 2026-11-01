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
        printf("  결과 : 실패, 요청 크기 : %d (1 ~ %d만 가능)\n", request_size, SIZE - HEADER_SIZE);
        return -1;
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

    // 빈 공간 없음
    if(h == -1){
        printf("  결과 : 실패, 요청 크기 : %d (맞는 크기의 빈 공간 없음)\n", request_size);
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
    if(start_address < HEADER_SIZE || start_address >= SIZE){
        printf("  결과 : 실패, 주소 : %d (범위 밖)\n", start_address);
        return;
    }

    // 입력 값이 존재하는 블럭의 주소인지 확인
    int h = start_address - HEADER_SIZE;
    int i = 0;

    while(i < h){
        Header* pI = (Header*)&storageArr[i];
        i += HEADER_SIZE + pI->size;
    }

    if(i != h){
        printf("  결과 : 실패, 주소 : %d (할당된 블럭이 아님)\n", start_address);
        return;
    }

    // 빈 공간 리스트에 있으면 이미 반환된 블럭
    int j = head;

    while(j != -1){
        if(j == h){
            printf("  결과 : 실패, 주소 : %d (이미 반환됨)\n", start_address);
            return;
        }
        j = ((Header*)&storageArr[j])->next;
    }

    Header* phead = (Header*)&storageArr[h];
    int hEnd = h + HEADER_SIZE + phead->size;

    printf("  결과 : 성공, 주소 : %d (블럭 %d ~ %d) 반환\n", start_address, h, hEnd);

    // 시작 주소가 hEnd인 빈 블럭을 h에 흡수
    int prev = -1;
    int cur = head;
    
    while(cur != -1){
        Header* pCur = (Header*)&storageArr[cur];

        if(cur == hEnd){
            phead->size += HEADER_SIZE + pCur->size;
            if(prev == -1){
                head = pCur->next;
            }
            else {
                Header* pPrev = (Header*)&storageArr[prev];
                pPrev->next = pCur->next;
            }
            break;
        }
        prev = cur;
        cur = pCur->next;
    }

    // 끝 주소가 h인 빈 블럭이 h를 흡수
    cur = head;

    while(cur != -1){
        Header* pCur = (Header*)&storageArr[cur];

        if(cur + HEADER_SIZE + pCur->size == h){
            pCur->size += HEADER_SIZE + phead->size;
            return;
        }
        cur = pCur->next;
    }

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