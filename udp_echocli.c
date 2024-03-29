udp_echocli.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 511

int main(int argc, char *argv[]){
        struct sockaddr_in servaddr;
        int s,nbyte,addrlen=sizeof(servaddr);
        char buf[ MAXLINE+1 ];

        if(argc != 3){
                printf("Usage: %s ip_address port_number\n", argv[0]);
                exit(0);
        }

        //소켓생성
        if((s=socket(PF_INET, SOCK_DGRAM, 0)) <0 ){
                perror("socket fail");
                exit(0);
        }

        //서버의 소켓주소 구조체 작성
        bzero((char *)&servaddr, sizeof(servaddr));

        //servaddr의 주소지정
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=inet_addr(argv[1]);
        servaddr.sin_port=htons(atoi(argv[2]));

        //키보드입력을 받음
        printf("입력: ");
        if(fgets(buf,MAXLINE,stdin)==NULL){
                printf("fgets 실패");
                exit(0);
        }

        //에코서버로 메세지 송신
        if(sendto(s,buf,strlen(buf),0,(struct sockaddr *)&servaddr,addrlen) <0){
                perror("sendto fail");
                exit(0);
        }

        //수신된 에코메시지
        if((nbyte==recvfrom(s,buf,MAXLINE,0,(struct sockaddr *)&servaddr,&addrlen)) <0){
                perror("recevfrom fail");
                exit(0);
        }

        buf[nbyte]=0;
        printf("%s\n", buf);
        close(s);
        return 0;
}
