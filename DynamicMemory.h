#define SIZE 108
#define HEADER_SIZE 8

typedef struct Header
{
    int size;
    int next;
} Header;

extern char storageArr[SIZE];
extern int head;

void initStorageArr();
int myalloc(int request_size);
void myfree(int start_address);
void printFreeList();