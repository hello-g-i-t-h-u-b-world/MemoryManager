#include <stdio.h>
#include "DynamicMemory.h"

void memoryScenario_01(void) {
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
    return 0;
}