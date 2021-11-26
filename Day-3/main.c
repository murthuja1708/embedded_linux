#include "file.h"


int main()
{
    FILE* stream=fopen("../files/sample.txt","r");
    char* res=NULL;

    
    while ((res=read_file(stream))!=NULL)
    {
        printf("%s\n",res);
        free(res);
    }
    

    return 0;
}