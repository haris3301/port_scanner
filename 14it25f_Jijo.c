#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

struct sockaddr_in addr;
#define PORT_UP 1024
char start_host[16],rmt[16];


int check(int port,char host[32]){
	
	int con,sock;

	struct timeval timeout;      
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	if(!(sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))){
		printf("Error creating socket!!\n");
		return;
	}

	if (setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
		error("setsockopt failed\n");

	if (setsockopt (sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
		error("setsockopt failed\n");

	addr.sin_family = PF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(host);

	//printf("Connecting PORT : %d\n",port);
	con = connect(sock,(struct sockaddr *) &addr,sizeof(addr));
	close(sock);
	if(con==-1)
		return 0;
	return 1;
}


char* nextIp(char strt[16])
{
	int sip[4];
	char out[16];
	int i,j;



	sscanf(strt,"%d.%d.%d.%d",&sip[0],&sip[1],&sip[2],&sip[3]);

	for(i=3;i>=0;i--){
		if(sip[i]+1<=255){
			sip[i]++;
			break;
		}
		else{
			sip[i]=0;
		}
	}
	for(i=0;i<4;i++){
		char temp[16];
		sprintf(temp, "%d", sip[i]);
		strcat(out,temp);
	}
	return out;
}
		
	
int main(){

	int i,ip[4];
	struct hostent *h;
	char end_host[16];
	char terminate[16];

	printf("Host(start) : ");
	scanf("%s",start_host);
	printf("Host(end) : ");
	scanf("%s",end_host);
	
	

	while(terminate!=end_host){
		char *temp=NULL;
		strcpy(terminate,start_host);
		if(terminate!=end_host){
			temp=nextIp(start_host);
			strcpy(start_host,temp);
		}

		if(sscanf(terminate,"%d.%d.%d.%d",&ip[0],&ip[1],&ip[2],&ip[3])!=4){
			if((h=gethostbyname(terminate))==NULL){
				printf("Cannot resolve host!");
				return 0;
			}
			sprintf(rmt,"%d.%d.%d.%d",
			(unsigned char ) h->h_addr_list[0][0],
		      	(unsigned char ) h->h_addr_list[0][1], 
		      	(unsigned char ) h->h_addr_list[0][2], 
		      	(unsigned char ) h->h_addr_list[0][3]);
			
			printf("HOST Resolved! %s\n",rmt);
		}
		else{
			strcpy(rmt,terminate);
		}
		printf("IP : %s\n",terminate);
		for(i=1;i<=PORT_UP;i++){
			if(check(i,rmt)){
				printf("PORT : %d is OPEN\n",i);
			}
			else{
				printf("PORT : %d is CLOSED\n",i);
			}
		}
	}

	return 0;
}
