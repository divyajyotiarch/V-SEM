//SERVER-SIDE

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#define PORT_NUMBER     5040
#define MAX 64512	//63KB
#define SERVER_ADDRESS  "127.0.0.1"


int main(int argc, char **argv)
{
       int sockfd;
       ssize_t len,size;
	//socklen_t len;	
	FILE *fp;
        struct sockaddr_in      server_addr;
        struct sockaddr_in      peer_addr;	//client
        int fd;
        int sent_bytes = 0;
        char file_size[MAX],*buffer;
        struct stat file_stat;
        off_t offset;
	int length = sizeof(peer_addr);
        int remain_data;

        /* Create server socket */
        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
	}
	else
	{
	printf("Socket successfully created \n");
	}

        // Zeroing server_addr struct
        memset(&server_addr, 0, sizeof(server_addr));
	memset(&peer_addr, 0, sizeof(peer_addr));

        // Construct server_addr struct 
        server_addr.sin_family = AF_INET;
        inet_pton(AF_INET, SERVER_ADDRESS, &(server_addr.sin_addr));
        server_addr.sin_port = htons(PORT_NUMBER);

        // Bind
       if ( bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 )
	{
	perror("bind failed");
	exit(EXIT_FAILURE);
	}
	else
	{
	printf("Binding done \n");
	}

	int n;
	char file_name[MAX];	//file name
	
	n = recvfrom(sockfd, (char *)file_name, BUFSIZ, MSG_WAITALL, ( struct sockaddr *) &peer_addr, &length);
	file_name[n] = '\0';
	printf("Client wants this file: %s\n", file_name);

        fd = open(file_name, O_RDONLY);	//O_RDONLY - open for read only
        if (fd == -1)
        {
                fprintf(stderr, "Error opening file --> %s", strerror(errno));

                exit(EXIT_FAILURE);
        }

        /* Get file stats */
 /*       if (fstat(fd, &file_stat) < 0)
        {
                fprintf(stderr, "Error fstat --> %s", strerror(errno));

                exit(EXIT_FAILURE);
        }

        fprintf(stdout, "File Size: \n%ld bytes\n", file_stat.st_size);
       
        sprintf(file_size, "%ld", file_stat.st_size); */
	 len=0;
        /* Sending file size */
        len = sendto(sockfd, file_size, sizeof(file_size), 0,(struct sockaddr *)&peer_addr, length);
        if (len == -1)
        {
              fprintf(stderr, "Error on sending greetings --> %s", strerror(errno));

              exit(EXIT_FAILURE);
        }

        fprintf(stdout, "Server sent %ld bytes as file size \n", len);

        offset = 0;
        remain_data = file_stat.st_size;
	

size_t newLen;	
	fp = fopen(file_name, "r");
if (fp != NULL) 
{
    // Go to the end of the file. 
    if (fseek(fp, 0L, SEEK_END) == 0) {
        // Get the size of the file.
        long bufsize = ftell(fp);

        if (bufsize == -1) 
		{ fprintf(stderr, "Error1 --> %s", strerror(errno)); }

        // Allocate our buffer to that size.
        buffer = malloc(sizeof(char) * (bufsize + 1));

        // Go back to the start of the file.
        if (fseek(fp, 0L, SEEK_SET) != 0) { fprintf(stderr, "Error2 --> %s", strerror(errno)); }

        // Read the entire file into memory.
        newLen = fread(buffer, sizeof(char), bufsize, fp);

        if ( ferror( fp ) != 0 ) {
            fputs("Error reading file", stderr);
        } else {
            buffer[newLen++] = '\0';
        }
    }
    fclose(fp);
}
else
{fprintf(stderr, "Error3 --> %s", strerror(errno));}


 // Sending file data 
	while(offset<length)
	{
		//sent_bytes = sendfile( sockfd,fd, &offset, length - offset);
		sent_bytes=sendto(sockfd, buffer, newLen-1, 0,(struct sockaddr *)&peer_addr, length);
		
		if (sent_bytes>=0)
		{
			fprintf(stdout, "1. Server sent %d bytes from file's data, offset is now : %ld and remaining data = %d\n", sent_bytes, offset, remain_data);
			offset+=sent_bytes;
			remain_data -= sent_bytes;
			fprintf(stdout, "2. Server sent %d bytes from file's data, offset is now : %ld and remaining data = %d\n", sent_bytes, offset, remain_data);
		}
		else
		{
			fprintf(stderr,"Error4 %s",strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

        close(sockfd);

        return 0;
}
