#include <stdio.h>
#include "DynamicMemory.h"

void testScenario(){
    printf("==========================================\n");
    initStorageArr();
    printf(" 빈 공간 리스트 \n");
    printFreeList();
    printf("==========================================\n");
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