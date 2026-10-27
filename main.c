#include <stdio.h>
#include "DynamicMemory.h"

void testScenario(){
    printf("==========================================\n");
    initStorageArr();
    printf(" 빈 공간 리스트 \n");
    printFreeList();
    printf("==========================================\n");

    Header* pA = (Header*)&storageArr[0];
    pA->size = 10;
    pA->next = 30;
    Header* pB = (Header*)&storageArr[30];
    pB->size = 70;
    pB->next = -1;
    head = 0;
    printFreeList();

    printf("==========================================\n");
    printf("  myalloc(5)   = %d\n", myalloc(5));
    printf("  myalloc(10)  = %d\n", myalloc(10));
    printf("  myalloc(20)  = %d\n", myalloc(20));
}

void memoryScenario_01() {
    int a, b, c, d;
    a = myalloc(10);
    b = myalloc(20);
    c = myalloc(10);
    myfree(a);
    a = myalloc(30);
    myfree(c);
    d = myalloc(20);
    myfree(b);
}

int main(){
    testScenario();
    return 0;
}