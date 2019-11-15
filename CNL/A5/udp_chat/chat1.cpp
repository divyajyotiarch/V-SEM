#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <errno.h>
#include<fstream>
#include<cmath>

#define PORT_NUMBER     5001
#define SERVER_ADDRESS "127.0.0.1"
#define PI 3.14159265

using namespace std;

class myServer
{
	int sockfd;
	sockaddr_in server_addr,client_addr;
	socklen_t sock_len;

public:
	myServer()
	{
		sock_len = sizeof(client_addr);
	}
	
	void screate();
	void sconstruct();
	void sbind();
	void sclose()
	{
		close(sockfd);
	}
	void schat();
		
};

void myServer::screate()
{
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd == -1)
        {
                fprintf(stderr, "Error creating socket --> %s", strerror(errno));

                exit(1);
        }
	else
	{
		cout<<"Socket created Successfully\n";
	}
	int en=1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(int)) < 0)
   	{ fprintf(stderr, "Error reusing socket --> %s\n", strerror(errno)); }

}

void myServer::sconstruct()
{
	/* Zeroing server_addr struct */

	memset(&server_addr, 0, sizeof(server_addr));

	/* Construct server_addr struct */

	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVER_ADDRESS, &(server_addr.sin_addr));
	server_addr.sin_port = htons(PORT_NUMBER);

}

void myServer::sbind()
{
	 if ((bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))) == -1)
        {
                fprintf(stderr, "Error on bind --> %s", strerror(errno));

                exit(1);
        }
	else
	{
		cout<<"Binding Successful \n";
	}
	
}


void myServer::schat()
{
	char buffer[256];
	cin.ignore();
	while(1)
	{ 
		cout <<endl<< "..." << endl;
		bzero(buffer,256);
		recvfrom(sockfd,buffer,255,0,(struct sockaddr *)&client_addr,&sock_len);
		cout<<"Client: "<<buffer<<endl;
		if(buffer[0]=='e' && buffer[1]=='x' && buffer[2]=='i' && buffer[3]=='t'){
			sclose();
			cout<<"Termination of Connection";
 			return;
		}
		cout<<"\nmsg >> ";
		
		string data;
		//cin.ignore();
		getline(cin,data);
		bzero(buffer,256);
		strcpy(buffer,data.c_str());
		
		//cin.clear();
		// fflush(stdin);
		sendto(sockfd,(char*)&buffer,strlen(buffer),0,(struct sockaddr *)&client_addr,sock_len);

		if(buffer[0]=='e' && buffer[1]=='x' && buffer[2]=='i' && buffer[3]=='t'){
			sclose();
			cout<<"Termination of Connection";
 			return;
		}
	}

}


int main()
{
	myServer ms;
	
		ms.screate();
		ms.sconstruct();
		ms.sbind();
		ms.schat();


return 0;

}
