/*Client */
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
    struct childAttributes childList[20], portData;
    char buffer[50]="";
    int connectTo;    
    int n, option;
    bool localFlag, foundFlag;
    int index;
    pid_t pid_son;
    //system("mkfifo fifo1");
    int fd;
    portData.connectTo =0;
    portData.ID =0;
    portData.status =0;
    portData.access =0;
    
    do
    {
        system("clear");
        
        printf("%d",getppid());
        printf( "\n   1. Conectarse al servidor" );
        printf( "\n   2. Solicitar conexión con otro cliente" );
        printf( "\n   3. Modificar Permisos");
        printf( "\n   4. Salir." );
        printf( "\n\n   Introduzca opción (1-4): ");

        scanf( "%d", &option );

        /* Inicio del anidamiento */

        switch ( option )
        {
            case 1: printf( "\n   Tu ID es: %d",getppid() );
                    portData.ID = getppid();
                    break;

            case 2: printf( "\n   Introduzca un número de ID del cliente: " );
                    scanf( "%d", &portData.connectTo );
                    break;

            case 3: printf( "\n   Permisos para ser conectado(1 -Si, 2- No): " );
                    scanf( "%d", &portData.access );
                    break;
            default:

                    break;
         }
        if(option >0 && option < 4) 
        {
            
            fd=open("server.pipe",O_WRONLY);
            write(fd, &portData.ID, sizeof(&portData.ID));
            write(fd, &portData.status, sizeof(&portData.status));            
            write(fd, &portData.access, sizeof(&portData.access));     
            write(fd, &portData.connectTo, sizeof(&portData.connectTo));             
            close(fd);  
        }
         /* Fin del anidamiento */

    } while ( option != 4 );
     
    close(fd);

    return 0;
}