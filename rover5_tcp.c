
/*
    C socket server example
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>

// for yolo
#include <sys/stat.h>
#define  FIFO_FROM_YOLO   "/tmp/from_yolo_fifo"
#define  FIFO_TO_YOLO     "/tmp/to_yolo_fifo"
#define  BUFF_SIZE   1024

int   counter = 0;
int   fd_from_yolo;
int   fd_to_yolo;
char  buff[BUFF_SIZE];

int     handle;
struct  termios  oldtio,newtio;
    
char    *TitleMessage = "Welcome Serial Port\r\n";
char    Buff[256];
int     RxCount;
int     loop;
int     ending;    
int     key;
            
// for select
int     i;
int     n;
int     state;

// 쓰레드 함수
void *t_function(void *data)
{
    int id;
    int i = 0;
    id = *((int *)data);

    //from yolo
    while(1)
    {
        while(read(fd_from_yolo, buff, BUFF_SIZE) != NULL)
        {
            write( handle, buff, 1 );
            printf("%s", buff);
            memset(buff, 0x00, BUFF_SIZE);
        }
    }
}

int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
    fd_set readfds;
    pthread_t p_thread[2];
    int thr_id;
    int status;
    int a = 1;
    int b = 2;

    // 쓰레드 생성 아규먼트로 1 을 넘긴다.  
    thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)&a);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
    //for yolo 
    if ( -1 == ( fd_from_yolo = open( FIFO_FROM_YOLO, O_RDWR)))
    {
        if ( -1 == mkfifo( FIFO_FROM_YOLO, 0666))
        {
            perror( "mkfifo() run error");
            exit( 1);
        }

        if ( -1 == ( fd_from_yolo = open( FIFO_FROM_YOLO, O_RDWR)))
        {
            perror( "open() error");
            exit( 1);
        }
    }
    if ( -1 == ( fd_to_yolo = open( FIFO_TO_YOLO, O_RDWR)))
    {
        if ( -1 == mkfifo( FIFO_TO_YOLO, 0666))
        {
            perror( "mkfifo() run error");
            exit( 1);
        }

        if ( -1 == ( fd_to_yolo = open( FIFO_TO_YOLO, O_RDWR)))
        {
            perror( "open() error");
            exit( 1);
        }
    }
    //for STM32
    handle = open( "/dev/ttyUSB0", O_RDWR | O_NOCTTY );
    if( handle < 0 ) 
    {
        //화일 열기 실패
        printf( "Serial Open Fail [/dev/ttyUSB2]\r\n "  );
        exit(0);
    }    
    tcgetattr( handle, &oldtio );  // 현재 설정을 oldtio에 저장

    memset( &newtio, 0, sizeof(newtio) );
    newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD ; 
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;    
    newtio.c_cc[VTIME] = 128;    // time-out 값으로 사용된다. time-out 값은 TIME*0.1초 이다.
    newtio.c_cc[VMIN]  = 0;     // MIN은 read가 리턴되기 위한 최소한의 문자 개수
    
    tcflush( handle, TCIFLUSH );
    tcsetattr( handle, TCSANOW, &newtio );    

    // motor stop
    Buff[0] = 'i';
    write( handle, Buff, 1 );
    printf("i send\n");
  
    // 1 문자씩 받아서 되돌린다. 
    ending = 0;

////////////////////////////////////////////////////////////////
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 1234 );
     
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    listen(socket_desc , 3);
     
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
     
    //Receive a message from client
    while( (read_size = recv(client_sock, client_message, 2000, 0)) > 0 )
    {
        printf("%s[%d] \n", client_message, read_size);
        //to STM32
        if(!strncmp(client_message, "left", 4))
        {
            Buff[0] = 'a';
            write( handle, Buff, 1 );
            printf("a left\n");
        }
        if(!strncmp(client_message, "right", 5))
        {
            Buff[0] = 'b';
            write( handle, Buff, 1 );
            printf("b right\n");
        }
        if(!strncmp(client_message, "up", 2))
        {
            Buff[0] = 'c';
            write( handle, Buff, 1 );
            printf("c up\n");
        }
        if(!strncmp(client_message, "down", 4))
        {
            Buff[0] = 'd';
            write( handle, Buff, 1 );
            printf("d down\n");
        }
        if(!strncmp(client_message, "stop", 4))
        {
            Buff[0] = 'i';
            write( handle, Buff, 1 );
            printf("i send\n");
        }
        
        //to yolo
        if(!strncmp(client_message, "apple", 5))
        {
            Buff[0] = 'A';
            write( fd_to_yolo, Buff, 1 );
            printf("%c send\n", Buff[0]);
        }     
        if(!strncmp(client_message, "banana", 6))
        {
            Buff[0] = 'B';
            write( fd_to_yolo, Buff, 1 );
            printf("%c send\n", Buff[0]);
        }
        if(!strncmp(client_message, "bicycle", 7))
        {
            Buff[0] = 'C';
            write( fd_to_yolo, Buff, 1 );
            printf("%c send\n", Buff[0]);
        }
        if(!strncmp(client_message, "dog", 3))
        {
            Buff[0] = 'D';
            write( fd_to_yolo, Buff, 1 );
            printf("%c send\n", Buff[0]);
        }
        if(!strncmp(client_message, "truck", 5))
        {
            Buff[0] = 'E';
            write( fd_to_yolo, Buff, 1 );
            printf("%c send\n", Buff[0]);
        }
        memset(client_message, 0, sizeof(client_message));
    }

    Buff[0] = 'i';
    write( handle, Buff, 1 );
    printf("i send\n");
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }

    close(socket_desc);
    close( fd_from_yolo);
    close( fd_to_yolo);
    // 쓰레드 종료를 기다린다. 
    //pthread_join(p_thread[0], (void **)&status);
     
    return 0;
}

