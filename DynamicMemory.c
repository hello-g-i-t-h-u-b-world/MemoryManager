#include "DynamicMemory.h"

#define SIZE 108

typedef struct Header
{
    int size;
    int next;
} Header;

char storageArr[SIZE];