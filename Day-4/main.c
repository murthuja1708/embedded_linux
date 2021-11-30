#include "file.h"

int main(int argc,char* argv[])
{

    if(argc >2)
    {
        _cp(argv[1],argv[2]);
    }
    else if(argc==2)
    {
        print("missing destination file path\n");
        return -1;
    }
    else{
        print("please provide required arguments\n");
        return -1;
    }
    return 1;
}