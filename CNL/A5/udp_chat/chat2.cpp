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

#define PORT_NUMBER     5001
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
	void c_chat();

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


void myClient::c_chat()
{
	char buffer[256];
	cin.ignore();
	 while(1)
	 {
		 bzero((char *)buffer,256);
		 	cout<<"\nmsg >> ";
		 	string data;
			
		 	getline(cin, data);
		 	strcpy(buffer,data.c_str());

		 sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)&server_addr,sock_len);

		 bzero(buffer,256);
		 cout <<endl<< "..." << endl;
		 recvfrom(sockfd,(char*)&buffer,sizeof(buffer),0,(struct sockaddr *)&server_addr,&sock_len);
		 cout<<"Server: "<<buffer<<endl;

		if(buffer[0]=='e' && buffer[1]=='x' && buffer[2]=='i' && buffer[3]=='t'){
			c_close();
 			break;
		}
	}

}

int main()
{
	myClient cl;
		
	cl.c_create();
	cl.c_construct();
	cl.c_chat();
	
	return 0;
}

