#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define READ_SIZE 512
#define WRITE_SIZE 256
#define _SIZE 1024

void _cp(const char*,const char*);

int write_all_nbytes(int ,void*,ssize_t);

int print(const char* str);

