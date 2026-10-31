#include <stdio.h>
#include "DynamicMemory.h"

void testScenario(){
    printf("==========================================\n");
    initStorageArr();
    printf(" 빈 공간 리스트 \n");
    printFreeList();
    printf("==========================================\n");

    printf("분할 \n");
    printf("  myalloc(10)  = %d\n", myalloc(10));
    printFreeList();
    printf("  myalloc(20)  = %d\n", myalloc(20));
    printFreeList();
    printf("  myalloc(10)  = %d\n", myalloc(10));
    printFreeList();
    printf("  (기대: [64, 36, -1])\n");
    printf("------------------------------------------\n");
    
    printf("빈 공간 부족으로 할당에 실패\n");
    printf("  myalloc(50)  = %d\n", myalloc(50));
    printFreeList();
    printf("------------------------------------------\n");

    printf("남은 공간이 헤더 크기(8)보다 작을 때\n");
    printf("  myalloc(30)  = %d\n", myalloc(30));
    printFreeList();
    printf("------------------------------------------\n");

    printf("myfree\n");
    myfree(72);
    printf("  myfree(72)\n");
    printFreeList();
    myfree(8);
    printf("  myfree(8)\n");
    printFreeList();
    printf("------------------------------------------\n");

    printf("병합 테스트\n");
    initStorageArr();

    int a, b, c;
    a = myalloc(10);
    b = myalloc(10);
    c = myalloc(10);
    printFreeList();
    printf("myfree (a)\n");
    myfree(a);
    printFreeList();
    printf("  (예상 결과값: [0, 10, 54] -> [54, 46, -1])\n");
    printf("myfree (b)\n");
    myfree(b);
    printFreeList();
    printf("  (예상 결과값: [0, 28, 54] -> [54, 46, -1])\n");
    printf("------------------------------------------\n");
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