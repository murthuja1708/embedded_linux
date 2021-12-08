#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<ctype.h>

#define CMD_SIZE 200
#define PARAM_SIZE 20
#define NO_OF_ARGS 10
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
        int return_status;

        while (1)
        {
            fprintf(stderr,"%s","shell$");
            fgets(user_input,CMD_SIZE,stdin);
            

            if(strncmp(user_input,"exit",4)==0)
            {
                break;
            }
            else if(strncmp(user_input,"\n",1)==0)
            {
                continue;
            }
            
            id=fork();
            if(id == 0)
            {
                int nread;
                char* user_string_buff=(char*)calloc(CMD_SIZE,sizeof(char));
            
                nread=read(fd1[READ],user_string_buff,CMD_SIZE);

                
                char *args[NO_OF_ARGS]={NULL}; //* to arguments of length PARAM_SIZE each

                char* command=(char*)calloc(PARAM_SIZE,sizeof(char));

                size_t num_args=0;
                //since user_string_buff gets modified by strsep function we are pointing to data

                while ((command=strsep(&user_string_buff," "))!=NULL)
                {
                     args[num_args]=(char*)calloc(PARAM_SIZE,sizeof(char));
                     args[num_args]=strdup(command);
                     num_args++;
                }


                args[num_args]=NULL;

                if(execvp(args[0],args)==-1)
                {
                    perror("error");
                    
                    return_status=0;
                }
                else{
                    return_status=1;
                }


                for (size_t i = 0; i < num_args; i++)
                {
                    free(args[i]);
                    
                }
                free(command);
                
                free(user_string_buff);
                


                return return_status;
            }
            else{

                size_t len=strlen(user_input);
                nwrite=write_all_nbytes(fd1[WRITE],user_input,len-1);
                
                int status;
                wait(&status);
                if(WIFEXITED(status))
                {
                    switch (status)
                    {
                    case 0:
                        break;
                    default:
                        printf("status is %d\n",status);
                    }
                }
            }
        }
        close(fd1[WRITE]);
        close(fd1[READ]);
            
    return 1;
}