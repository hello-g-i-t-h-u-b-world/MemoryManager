typedef struct Header;
char storageArr[SIZE];
int head;
void initStorageArr();
int myalloc(int request_size);
void myfree(int start_address);