#include "file.h"

#define SIZE 1024

char* read_file(FILE* file_path)
{
    size_t count=0;
    char* buffer=NULL;
    ssize_t nread=0;

    //allocates size dynamically if buffer is null and count is 0
    nread=getline(&buffer,&count,file_path);
    if(nread==EOF)
    {
        return NULL;
    }
    return buffer;
}