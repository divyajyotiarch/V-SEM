//============================================================================
// Name        : A6 server file.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <errno.h>
#include <iostream>
#include <sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include <unistd.h>
#include<stdio.h>
using namespace std;

#define PORT 4000
void die(string error)
{
	cout<<error;
	exit(1);
}
int main() {

	sockaddr_in server_addr,client_addr;

	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
		die("SOCKET CREATE ERROR");
	else
		cout<<"Socket Created.";
	bzero((char *)&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr= inet_addr("127.0.0.1");
	server_addr.sin_port=htons(PORT);

	if(bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
	{	//die("ERROR IN BINDING");
	fprintf(stderr, "Error  --> %s", strerror(errno));
		}
	if(listen(sock,10)<0)
	{
		die("ERROR WHILE LISTENING");
	}
	socklen_t socklen=sizeof(client_addr);

	int newSocket=accept(sock,(struct sockaddr*)&client_addr,&socklen);
	if(newSocket<0)
		die("ACCEPT ERROR");
	else
		cout<<"\nCONNECTION ACCEPTED";
	long long int msg_len;


	{
		cout<<"\nENter Filename:";
		char filename[100];
		cin>>filename;
		cout<<filename;
		fstream fout;



		msg_len=send(newSocket,filename,100,0); //send filename
		if(msg_len==-1)
			die("Filename error");

		fout.open(filename,ios::in|ios::out|ios::binary);
				fout.seekg(0,ios::end);
				long long int filesize=fout.tellg(); //get file size
				char *filebuff=new char[filesize];
				fout.seekg(0,ios::beg);
				fout.read(filebuff,filesize); //reading file content



		msg_len=send(newSocket,filebuff,filesize,0); //send file conetents
		if(msg_len==-1)
			die("File transmission error");
		else
			cout<<"Transmission Successful";
		fout.close();
		shutdown(newSocket,0);
		close(newSocket);
	}
	return 0;
}
