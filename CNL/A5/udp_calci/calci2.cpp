#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <errno.h>
#include<fstream>

using namespace std;

#define PORT_NUMBER     5002
#define SERVER_ADDRESS "127.0.0.1"

class myClient
{
	int sockfd;
	sockaddr_in server_addr;
	socklen_t sock_len;

public:
	myClient()
	{
		sock_len = sizeof(server_addr);
	}
	void c_construct();
	void c_create();
	void c_close()
	{
		close(sockfd);
	}
	void trigo();
};

void myClient::c_create()
{
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd == -1)
        {
                fprintf(stderr, "Error creating socket --> %s\n", strerror(errno));

                exit(1);
        }
	else
	{
		cout<<"Socket created sucessfully\n";
	}

	

}

void myClient::c_construct()
{
	/* Zeroing server_addr struct */
        memset(&server_addr, 0, sizeof(server_addr));

        /* Construct server_addr struct */
        server_addr.sin_family = AF_INET;
        inet_pton(AF_INET, SERVER_ADDRESS, &(server_addr.sin_addr));
        server_addr.sin_port = htons(PORT_NUMBER);

}

void myClient::trigo()
{

	char angle[3],op[1];
	char s_ans[20],c_ans[20],t_ans[20];

	
		cout<<"Enter angle "<<endl;
		cin>>angle;

		int n=sendto(sockfd,(char*)angle,strlen(angle),0,(struct sockaddr *)&server_addr,sock_len);
		
		cout<<"Enter trigo op: 's-sin'/'c-cos'/'t-tan' \n";
		cin>>op;
		sendto(sockfd,( char*)op,strlen(op),0,(struct sockaddr *)&server_addr,sock_len);
		
		if(op[0]=='s')
                {
		 cout<<"Sine of angle "<<angle<<" is ";
		recvfrom(sockfd,( char*)s_ans,20,0,(struct sockaddr *)&server_addr,&sock_len);
		cout<<s_ans<<endl;
		//bzero((char*)s_ans,sizeof(s_ans));  
		 }
                else if(op[0]=='c')
		{
		 cout<<"Cosine of angle "<<angle<<" is ";
		//bzero((char*)c_ans,sizeof(c_ans));
		recvfrom(sockfd,( char*)c_ans,20,0,(struct sockaddr *)&server_addr,&sock_len);
		cout<<c_ans<<endl;
		 }
                else if(op[0]=='t')
		{
		cout<<"Tangent of angle "<<angle<<" is ";
		//bzero((char*)t_ans,sizeof(t_ans));
		recvfrom(sockfd,(char*)t_ans,20,0,(struct sockaddr *)&server_addr,&sock_len);
		cout<<t_ans<<endl;
		}
		
		c_close();

}

int main()
{
	myClient cl;

	cl.c_create();
	cl.c_construct();
	cl.trigo();

	
	
	return 0;
}

