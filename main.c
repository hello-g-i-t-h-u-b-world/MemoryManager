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
    printf("  myfree(72)\n");
    myfree(72);
    printFreeList();
    printf("  myfree(8)\n");
    myfree(8);
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

    printf("뒤쪽 병합\n");
    initStorageArr();
    a = myalloc(10);
    b = myalloc(20);
    printf("myfree(b)\n");
    myfree(b);
    printFreeList();
    printf("  (예상: [18, 82, -1])\n");
    printf("------------------------------------------\n");

    printf("앞뒤 모두 병합\n");
    initStorageArr();
    a = myalloc(10);
    b = myalloc(10);
    c = myalloc(10);
    printf("myfree(a)\n");
    myfree(a);
    printFreeList();
    printf("  (예상: [0, 10, 54] -> [54, 46, -1])\n");
    printf("myfree(c)\n");
    myfree(c);
    printFreeList();
    printf("  (예상: [36, 64, 0] -> [0, 10, -1])\n");
    printf("myfree(b)\n");
    myfree(b);
    printFreeList();
    printf("  (예상: [0, 100, -1])\n");
    printf("------------------------------------------\n");
}

void exceptionTest(){
    int a, b, c;

    printf("범위 밖 주소 테스트\n");
    initStorageArr();
    a = myalloc(10);
    printFreeList();
    printf("myfree(200)\n");
    myfree(200);
    printf("myfree(3)\n");
    myfree(3);
    printf("myfree(-1)\n");
    myfree(-1);
    printFreeList();
    printf("  (예상: 세 번 모두 실패, 리스트 [18, 82, -1])\n");
    printf("------------------------------------------\n");

    printf("블럭 중간 주소\n");
    initStorageArr();
    a = myalloc(10);
    b = myalloc(10);
    printFreeList();
    printf("myfree(30)\n");
    myfree(30);
    printf("myfree(%d)\n", a + 1);
    myfree(a + 1);
    printFreeList();
    printf("  (예상: 두 번 모두 실패, 리스트 [36, 64, -1])\n");
    printf("------------------------------------------\n");

    printf("같은 주소 두 번 반환 테스트\n");
    initStorageArr();
    a = myalloc(10);
    b = myalloc(10);
    printFreeList();
    printf("myfree(a)\n");
    myfree(a);
    printf("myfree(a)\n");
    myfree(a);
    printFreeList();
    printf("  (예상: 두 번째는 실패(이미 반환됨), [0, 10, 36] -> [36, 64, -1])\n");
    printf("------------------------------------------\n");

    printf("흡수된 블럭 다시 반환 테스트\n");
    initStorageArr();
    a = myalloc(10);
    b = myalloc(10);
    c = myalloc(10);
    printFreeList();
    printf("myfree(a)\n");
    myfree(a);
    printf("myfree(b)\n");
    myfree(b);
    printf("myfree(b)\n");
    myfree(b);
    printFreeList();
    printf("  (예상: 세 번째는 실패, [0, 28, 54] -> [54, 46, -1])\n");
    printf("------------------------------------------\n");
}

void memoryScenario_01(){
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
    // testScenario();
    exceptionTest();
    return 0;
}