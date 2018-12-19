/*A server that handles multiple clients at the same time  *
 * The ip address has been set to loopback address         *
 * This server was tested in a kali linux system using gcc *
 
*/


#include "headers.h"
int main (int argc, char **argv)
{
	int sockfd,newSock;
	pid_t child;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int yes = 1;
	socklen_t len;
	/*create the socket*/
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd == -1)
	{
		perror("socket");
		exit(1);
	}else{
/*set the socket options allow the port to be reused*/
if(	setsockopt(sockfd,	SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int))==-1){
		perror("setsockopt");
}

	/*fill the address*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr =INADDR_ANY;
	memset(&(server_addr.sin_zero),'\0',8);
	/*bind the address to the port*/
	int ret_bind = bind(sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr));
	if (ret_bind == -1)
	{
		perror("bind");
		exit(1);
	}else{
	/*listen for any incoming connections*/
	int ret_listen = listen(sockfd,BACKLOG);
	if (ret_listen == -1)
	{
		perror("listen");
		exit(1);
	}else{
	printf("The server is running \n");
	printf("[+] listening for connections\n");
	/*time to accept connections from incoming clients(loop)*/
	for ( ; ;)/*loop forever*/
	{
		 len = sizeof(struct sockaddr_in);
	 newSock= accept(sockfd,(struct sockaddr *)&client_addr,&len);
		if (newSock == -1)
		
		{
		
			perror("accept");
			exit(1);
		}else{
		printf("The server got connection from %s at port %d\n",inet_ntoa(client_addr.sin_addr),client_addr.sin_port);
		/*if accept succeeds fork a new process to handle the connection*/
		child = fork();
		//fork returns the child process id in parent, 0 in child and -1 on error
		if (child == -1)
		{
			perror("fork");
			exit(1);
		}
	   else	if (child == 0)//this is the child process
		{
			close(sockfd);//the child closes the listening port
			char buf[] = "This is a message from the server";
			
			send(newSock,buf,strlen(buf),0);
			close(newSock);
			exit(0);
		
		}
	
	close(newSock);
//	close(sockfd);
	}
	}

}
}
}
	return 0;
}

