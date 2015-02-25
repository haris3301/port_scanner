#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

char host[100];
struct arg_struct
{
	char host[100];
	int port;
};

void *port_scan(void *arguments)
{
	int s, x;
	struct sockaddr_in addr;
	struct servent *bar;

	struct arg_struct *args = arguments;
	char* host;

	int port = args -> port;
	host = args -> host;

	s = -1;
	s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	while(s < 0)
	{
		sleep(60);
		s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		//printf("ERROR: socket() failed\n");
		//printf("%s\n", strerror(errno));
		//exit(0);
	}

	addr.sin_family = PF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(host);

	x = connect(s,(struct sockaddr *) &addr, sizeof(addr));

	close(s);
    
	if(x == 0)
	{
		bar = getservbyport(htons(port),"tcp");
       		printf("At port-%d service-(%s) is running.\n", port, (bar == NULL) ? "UNKNOWN" :bar->s_name);
		//printf("%d port open\n",i);
		//exit(0);
	}
	else
		//printf("closed");
	pthread_exit(0);
}


int main(int argc, char* argv[])
{
	int a, b, c, d, e, f, i, j;
	struct hostent *foo;
	struct arg_struct args[65536];
	pthread_t threads[65536];

	if(argc < 2)
	{
		printf("\nCall the program with the hostname that has to be scanned\n");
		printf("$> port_scan.o www.google.com");
		return 0;
	}

	if(sscanf(argv[1],"%d.%d.%d.%d",&a,&b,&c,&d) != 4)
	{
		foo = gethostbyname(argv[1]);
		if(foo == NULL)
		{
         		fprintf(stderr,"error: cannot resolve host %s\n",argv[1]);
         		return 0;
		}
		sprintf(host,"%d.%d.%d.%d",(unsigned char )foo->h_addr_list[0][0],
		(unsigned char ) foo->h_addr_list[0][1],
		(unsigned char ) foo->h_addr_list[0][2],
		(unsigned char ) foo->h_addr_list[0][3]);
	}
	else
	{
		strncpy(host,argv[1],99);
	}

	//f = port_scan(host, 22);
	//printf("%d\n",f);
	//printf("%s\n\n", host);
	printf("Port Scanning starting...\n\n");
	
	i = 1;
	while(i < 1024)
	{
		for(j = 0; j < 1024; j++)
		{
			strncpy( (args + i + j - 1) -> host, host, 99);
		//	printf("hello");
			args[i + j - 1].port = i + j;
			//printf("%d",i);
			f = pthread_create( (threads + i + j - 1), NULL, &port_scan, (void *)(args + i + j - 1) );
		//	printf("%d",f);
		}
		sleep(10);
		i = i + j;
	}
}

