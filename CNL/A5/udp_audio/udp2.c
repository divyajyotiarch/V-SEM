//CLIENT-SIDE
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT_NUMBER     5040
#define MAX 64512	//63KB
#define SERVER_ADDRESS  "127.0.0.1"
#define FILENAME        "new.wav"

int main(int argc, char **argv)
{
        int sockfd;
	
       // ssize_t len;
	socklen_t len;
        struct sockaddr_in server_addr;	
	int length=sizeof(server_addr);	
        char buffer[MAX];		//BUFSIZ - controlling buffering
        int file_size;
        FILE *received_file;
        int remain_data = 0;

        /* Zeroing remote_addr struct */
        memset(&server_addr, 0, sizeof(server_addr));

        /* Construct remote_addr struct */
        server_addr.sin_family = AF_INET;
        inet_pton(AF_INET, SERVER_ADDRESS, &(server_addr.sin_addr));
        server_addr.sin_port = htons(PORT_NUMBER);

        // Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
	perror("socket creation failed");
	exit(EXIT_FAILURE);
	}
	else
	{
	printf("Socket successfully created \n");
	}

	
	
	char chat[50];// = "file.txt";
	printf("Enter filename\n");
	scanf("%s",chat);
	 sendto(sockfd, (const char *)chat, strlen(chat),  MSG_CONFIRM, ( struct sockaddr *) &server_addr, length );

        /* Receiving file size */
        ssize_t l = recvfrom(sockfd, buffer, MAX, 0 ,( struct sockaddr *) &server_addr,  &length);
     //   file_size = atoi(buffer);
		file_size = MAX;
       // fprintf(stdout, "\nFile size : %d\n", file_size);

        received_file = fopen(FILENAME, "w+");
        if (received_file == NULL)
        {
                fprintf(stderr, "Failed to open file  --> %s\n", strerror(errno));

                exit(EXIT_FAILURE);
        }

        remain_data = file_size;
	
	int i;
        while (((len = recvfrom(sockfd, buffer, file_size, 0,(struct sockaddr *) &server_addr,  &length)) > 0) && (remain_data > 0))
        {
                if( (i=fwrite(buffer, sizeof(char), len, received_file))<0)
		{	fprintf(stderr, "Failed to write  --> %s\n", strerror(errno));	}
		

                remain_data -= len;
              //  fprintf(stdout, "Received %d bytes and %d bytes remaining\n", len, remain_data);
		break;
        }
	
        fclose(received_file);
	
        close(sockfd);

        return 0;
}
