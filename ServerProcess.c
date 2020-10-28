/*Proceso B*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

struct childAttributes{
    int ID;
    int status;
    int access;
    int connectTo;
};
#define NO_CONNECTED 0
#define ALLOWED_CONNECTION 32
#define CONNECTION_NOT_ALLOWED 0

int main()
{
    struct childAttributes childList[50], portData;
    char buffer[12]="";

    bool localFlag, foundFlag;
    int index;
    //system("mkfifo fifo2");
    int fd,fd2;

    for(index=0; index<50; index++)
    {
        childList[index].ID= -1;
    }   
    //fd2=open("fifo2",O_WRONLY);
         
    
    puts("Esperando nuevo cliente o petición...\n");
    do
    {
        /* code */  
        localFlag = false;     
        
        //fd=open("fifo1", O_RDONLY);
        fd=open("server.pipe", O_RDONLY);
        if (fd==-1)
        {
            // Is  process
            // Check for other pipes
            system("mkfifo server.pipe");
            fd=open("server.pipe", O_RDONLY);
            
        } else {
            // Is the parent process (main server)
            
            fd=open("server.pipe", O_RDONLY);

        }
        
        read(fd, &portData.ID, sizeof(&portData.ID));
        read(fd, &portData.status, sizeof(&portData.status));            
        read(fd, &portData.access, sizeof(&portData.access));     
        read(fd, &portData.connectTo, sizeof(&portData.connectTo)); 
        close(fd);
        index = 1;
        system("clear");
        while((childList[index].ID != -1) && index<50)
        {
            printf("Comparing: %d with %d\n", portData.ID, childList[index].ID);
            if(portData.ID == childList[index].ID)
            {
                localFlag=true;
                break;
            }     
            index++;   
        }

        if(index < 50)
        {              
            childList[index].ID = portData.ID;   
            childList[index].status = portData.status;
            childList[index].access = portData.access;
            childList[index].connectTo = portData.connectTo;
            if(false == localFlag)   
            {
                printf("Comunicación enlazada con cliente: %d\n", portData.ID);
            } 
            else
            {
                
                printf("Ya estaba enlazada con: %d\n", portData.ID);
                /* code */                     
                foundFlag = false;
                if(childList[index].connectTo != NO_CONNECTED)
                {
                    for(int j=0;j<50;j++)
                    {
                        if(childList[j].ID == childList[index].connectTo)
                        {
                            if(childList[j].access == ALLOWED_CONNECTION)
                            {
                                foundFlag=true;
                                childList[index].access == CONNECTION_NOT_ALLOWED;
                            }
                            break;
                        }
                    }
                    
                }          
            
            
                /*puts(&portData.estado);*/            
            }
        }
        else
        {
                puts("Comunication error\n");
            

        }
        
        
        index=1;
        
        
        printf( "\n             Clientes conectados" );
        while(childList[index].ID != -1 && index<50)
        {
            printf( "\n   ID            Permisos            Status" );
            if(childList[index].status==0)
            {
                printf( "\n   %d                %d                  libre\n",childList[index].ID, childList[index].access);
            }
            else
            {
                printf( "\n   %d                %d                  Ocupado\n",childList[index].ID, childList[index].access);
            }
            index++;
        }        
        puts("\n\n\nEsperando nuevo cliente o petición...\n\n\n");


    } while (buffer != "chau\n");
    close(fd);
    system("rm server.pipe");
    //close(fd2);

    return 0;
}