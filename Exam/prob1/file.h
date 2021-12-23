#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>

void _cp(const char*,const char*);

int write_all_nbytes(int ,void*,ssize_t);

size_t read_all_bytes(int fd,char* buffer,size_t max_bytes);

int print(const char* str);

