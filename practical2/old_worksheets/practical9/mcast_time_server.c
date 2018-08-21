#include	"acc.h"

void getTime(int sockfd);

 /***********************************
 * 
 ***********************************/
int main(int argc, char **argv) {
	int	sockfd, port = SERV_UDP_PORT_MCAST;
	socklen_t len;
	struct sockaddr_in servaddr;
	char addr[MAXLINE+1];
	struct ip_mreq mreq;

	len = sizeof(SA);

	if (argc > 3)
          err_quit("usage: %s [IP-multicast-address] [bind port #]\n", argv[0]);

	if (argc == 1)
	  sprintf(addr, "%s", MCAST_GROUP);	// use default addr
	else if (argc >= 2) {
	  snprintf(addr, MAXLINE, "%s", argv[1]);
	  if (argc == 3) {
	    if (sscanf(argv[2], "%d", &port) != 1)
		err_quit("invalid port #");
	  }
	}

	printf("Join multicast group: %s\n", addr);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	//destination address for sendto
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, addr, &servaddr.sin_addr.s_addr);
	servaddr.sin_port = htons(port);
	Bind(sockfd, (SA *) &servaddr, len);

	//set to join the multicast group
	Inet_pton(AF_INET, addr, &mreq.imr_multiaddr);
	mreq.imr_interface.s_addr = INADDR_ANY;
	if(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
		err_quit("setsockopt fails");


	for (;;)
           getTime(sockfd);

	exit(0);
}


void getTime(int sockfd) {
	int n;
	time_t ticks;
	char line[MAXLINE + 1];
	struct sockaddr reply_addr;
	struct utsname myname;
	socklen_t len = sizeof(SA);

	
	n = Recvfrom(sockfd, line, MAXLINE, 0, &reply_addr, &len);
	line[n] = 0;
	printf("Client message: %s\n", line);
	ticks = time(NULL);
	snprintf(line, sizeof(line), "%.24s\r\n",ctime(&ticks));
	if (uname(&myname) < 0)
		err_sys("uname error");

	Sendto(sockfd, line, strlen(line), 0, &reply_addr, len);
}

