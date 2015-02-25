#include<stdio.h>
#include<sys/socket.h>
#include<errno.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>

int main(int argc , char **argv)
{
    struct hostent *host;
    int err, i , sock ,start , end;
    char hostname[100];
    struct sockaddr_in sa;

    printf("Enter hostname or IP : ");
    gets(hostname);
    printf("\nEnter start port number : ");
    scanf("%d" , &start);
    printf("Enter end port number : ");
    scanf("%d" , &end);

    strncpy((char*)&sa , "" , sizeof sa);
    sa.sin_family = AF_INET;

    if(isdigit(hostname[0]))
    {
        printf("Doing inet_addr...");
        sa.sin_addr.s_addr = inet_addr(hostname);
        printf("Done\n");
    }
    else if( (host = gethostbyname(hostname)) != 0)
    {
        printf("Doing gethostbyname...");
        strncpy((char*)&sa.sin_addr , (char*)host->h_addr , sizeof sa.sin_addr);
        printf("Done\n");
    }
    else
    {
    herror(hostname);
        exit(2);
    }
    printf("%s",gethostbyname(hostname)->h_name);
    printf("Starting the portscan loop : \n");
    for( i = start ; i <= end ; i++)
    {
        sa.sin_port = htons(i);
        sock = socket(AF_INET , SOCK_STREAM , 0);

        if(sock < 0)
        {
            perror("\nSocket");
            exit(1);
        }
        err = connect(sock , (struct sockaddr*)&sa , sizeof sa);

        printf("Starting the portscan loop : %s\n",strerror(errno));
        if( err < 0 )
        {
            printf("%s %-5d %s\r" , hostname , i, strerror(errno));
            fflush(stdout);
        }
        else
        {
            printf("%-5d open\n",  i);
        }
        close(sock);
    }

    printf("\r");
    fflush(stdout);
    return(0);
}

