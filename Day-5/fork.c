#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<ctype.h>

#define CMD_SIZE 200
#define PARAM_SIZE 20
#define READ 0
#define WRITE 1




int write_all_nbytes(int fd,void* buffer,ssize_t nbytes)
{

    ssize_t bytes_to_be_written=nbytes;
    ssize_t nwrite=0;
    size_t total_written=0;
    while (bytes_to_be_written>0)
    {
        nwrite=write(fd,buffer+total_written,bytes_to_be_written);
        if(nwrite==-1)
        {
            printf("error while writing data\n");
            break;
        }
        total_written+=nwrite;
        bytes_to_be_written-=nwrite;
    }
    

    return  total_written;;
    
}

int main(int argc,char* argv[])
{
    

    char user_input[CMD_SIZE]={'\0'};
    size_t nwrite;

        int fd1[2];
        pipe(fd1);
        pid_t id;

        while (1)
        {
            fprintf(stderr,"%s","shell$");
            fgets(user_input,CMD_SIZE,stdin);
            

            if(strncmp(user_input,"exit",4)==0)
            {
                return 1;
            }
            id=fork();
            if(id == 0)
            {
                char file_path[CMD_SIZE+5]="/bin/";
                char user_string_buff[CMD_SIZE]={'\0'};
                int nread;

                nread=read(fd1[READ],user_string_buff,CMD_SIZE);

                char *args[PARAM_SIZE]; //* to arguments of length PARAM_SIZE each

                char command[PARAM_SIZE];
                size_t num_args=0;
                size_t len=0;
                
                printf("userstring we got is %s\n",user_string_buff);

                for (size_t i = 0; user_string_buff[i]!='\0'; i++)
                {
                    while (!isspace(user_string_buff[i]) && user_string_buff[i]!='\0')
                    {
                        command[len]=user_string_buff[i];
                        i+=1;
                        len+=1;
                    }
                    command[len]='\0';
                    args[num_args]=(char*)malloc(sizeof(char)*PARAM_SIZE);
                    strncpy(args[num_args],command,len);
                    len=0;
                    num_args++;
                }
                
                strncat(file_path,args[0],PARAM_SIZE);

                args[num_args]=NULL;

                execv(file_path,args);
            
                for (size_t i = 0; i < num_args; i++)
                {
                    free(args[i]);
                }       
            }
            else{
                size_t len=strlen(user_input);
                nwrite=write_all_nbytes(fd1[WRITE],user_input,len-1);
                
                int status;
                wait(&status);
                printf("status is %d\n",status);
            }
        }
        close(fd1[WRITE]);
        close(fd1[READ]);
            
    return 0;
}