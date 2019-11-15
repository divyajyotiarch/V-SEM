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

#define PORT_NUMBER     5002
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
	void trigo();
		
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
	 if ((bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(struct sockaddr))) == -1)
        {
                fprintf(stderr, "Error on bind --> %s", strerror(errno));

                exit(1);
        }
	else
	{
		cout<<"Binding Successful \n";
	}
	
}


void myServer::trigo()
{
	float degrees,rad;
	float sine,cosine,tangent;
	char angle[3],s_ans[20],c_ans[20],t_ans[20],op[1];

		int n=recvfrom(sockfd,angle,3,0,( struct sockaddr *) &client_addr, &sock_len);
		cout<<"Angle in degrees "<<angle<<endl;
                
		degrees=atof(angle);	//atof - string to floating point number
		bzero((char *)angle,sizeof(angle));

		rad = degrees * PI / 180.0;
		
		recvfrom(sockfd,(char*)op,1,0,( struct sockaddr *) &client_addr, &sock_len);
		cout<<op[0]<<"\n";
		
		//bzero((char *)op,sizeof(op));
		
                if(op[0]=='s')
                {
                sine = sin(rad);
		cout<<"Sine of angle "<<degrees<<" is "<<sine<<endl;
		bzero((char *)s_ans,sizeof(s_ans));
		snprintf(s_ans,20,"%f",sine);
		sendto(sockfd, (char*)s_ans,20, 0,(struct sockaddr *)&client_addr,sock_len);
                }
                else if(op[0]=='c')
		{
		cosine = cos(rad);
		cout<<"Cosine of angle "<<degrees<<" is "<<cosine<<endl;
		bzero((char *)c_ans,sizeof(c_ans));
		snprintf(c_ans,20,"%f",cosine);
		sendto(sockfd,(const char*) c_ans,20, 0,(struct sockaddr *)&client_addr,sock_len);
                }
                else if(op[0]=='t')
		{
		tangent = tan(rad);
		cout<<"Tangent of angle "<<degrees<<" is "<<tangent<<endl;
		bzero((char *)t_ans,sizeof(t_ans));
		snprintf(t_ans,20,"%f",tangent);
		sendto(sockfd, ( char*)t_ans,20, 0,(struct sockaddr *)&client_addr,sock_len);
                }
                
		sclose();
}

int main()
{
	myServer ms;

		ms.screate();
		ms.sconstruct();
		ms.sbind();
		ms.trigo();


return 0;

}
