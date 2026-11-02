#include <stdio.h>
#include "DynamicMemory.h"

void memoryScenario_01(){
    int a, b, c, d;

    printf("==========================================\n");
    printf("시나리오 1: 문제지 예제 (SIZE = 108)\n");
    printf("==========================================\n");
    initStorageArr();
    printf("[초기] 빈 공간 리스트\n");
    printFreeList();
    printf("------------------------------------------\n");

    printf("(1) a = myalloc(10)\n");
    a = myalloc(10);
    if(a != -1){
        printf("  결과 : 성공, 주소 : %d\n", a);
    }
    printFreeList();
    printf("------------------------------------------\n");

    printf("(2) b = myalloc(20)\n");
    b = myalloc(20);
    if(b != -1){
        printf("  결과 : 성공, 주소 : %d\n", b);
    }
    printFreeList();
    printf("------------------------------------------\n");

    printf("(3) c = myalloc(10)\n");
    c = myalloc(10);
    if(c != -1){
        printf("  결과 : 성공, 주소 : %d\n", c);
    }
    printFreeList();
    printf("------------------------------------------\n");

    printf("(4) myfree(a)\n");
    myfree(a);
    printFreeList();
    printf("------------------------------------------\n");

    printf("(5) a = myalloc(30)\n");
    a = myalloc(30);
    if(a != -1){
        printf("  결과 : 성공, 주소 : %d\n", a);
    }
    printFreeList();
    printf("------------------------------------------\n");

    printf("(6) myfree(c)\n");
    myfree(c);
    printFreeList();
    printf("------------------------------------------\n");

    printf("(7) d = myalloc(20)\n");
    d = myalloc(20);
    if(d != -1){
        printf("  결과 : 성공, 주소 : %d\n", d);
    }
    printFreeList();
    printf("------------------------------------------\n");

    printf("(8) myfree(b)\n");
    myfree(b);
    printFreeList();
    printf("==========================================\n\n");
}

void memoryScenario_02(){
    int a, b, c, d;

    printf("==========================================\n");
    printf("시나리오 2: 전체 할당 후 추가 요청\n");
    printf("==========================================\n");
    initStorageArr();
    printf("[초기] 빈 공간 리스트\n");
    printFreeList();
    printf("------------------------------------------\n");

    printf("(1) a = myalloc(100)\n");
    a = myalloc(100);
    if(a != -1){
        printf("  결과 : 성공, 주소 : %d\n", a);
    }
    printFreeList();
    printf("------------------------------------------\n");

    printf("(2) b = myalloc(1)\n");
    b = myalloc(1);
    if(b != -1){
        printf("  결과 : 성공, 주소 : %d\n", b);
    }
    printFreeList();
    printf("==========================================\n\n");
}

void memoryScenario_03(){
    int a, b, c, d;

    printf("==========================================\n");
    printf("시나리오 3: 같은 주소 두 번 반환\n");
    printf("==========================================\n");
    initStorageArr();
    printf("[초기] 빈 공간 리스트\n");
    printFreeList();
    printf("------------------------------------------\n");

    printf("(1) a = myalloc(100)\n");
    a = myalloc(100);
    if(a != -1){
        printf("  결과 : 성공, 주소 : %d\n", a);
    }
    printFreeList();
    printf("------------------------------------------\n");

    printf("(2) myfree(a)\n");
    myfree(a);
    printFreeList();
    printf("------------------------------------------\n");

    printf("(3) myfree(a)\n");
    myfree(a);
    printFreeList();
    printf("==========================================\n\n");
}

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

int main(){
    memoryScenario_01();
    memoryScenario_02();
    memoryScenario_03();
    // testScenario();
    // exceptionTest();
    return 0;
}