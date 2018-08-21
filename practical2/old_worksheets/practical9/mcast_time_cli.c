#include	"acc.h"

const static char *message = "What time is it?";
static void timeout();

int 
main(int argc, char **argv) 
{

	char	line[MAXLINE], addr[MAXLINE+1];
	int	n, sockfd, on = 1;
	socklen_t len = sizeof(SA);
	struct sockaddr_in replyAdd;
	struct sockaddr_in mcastaddr;
	int port = SERV_UDP_PORT_MCAST;
	int noOfReply = 0;
	struct ip_mreq mreq;


	if (argc > 3)
       	   err_quit("usage: %s [IP-multicast-address] [port #]\n", argv[0]);

	if (argc == 1)
	   sprintf(addr, "%s", MCAST_GROUP);	// use default addr
	else if (argc >= 2) {
	   snprintf(addr, MAXLINE, "%s", argv[1]);
	   if (argc == 3) {
	      if (sscanf(argv[2], "%d", &port) != 1)
	         err_quit("invalid port #");
	   }
	}

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	printf("Send to servers in multicast group: %s:%d\n", addr, port);


	//set to join the multicast group
	Inet_pton(AF_INET, addr, &mreq.imr_multiaddr);
	mreq.imr_interface.s_addr = INADDR_ANY;
	if(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
		err_quit("setsockopt fails");


	//destination address for sendto
	bzero(&mcastaddr, sizeof(mcastaddr));
	mcastaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, addr, &mcastaddr.sin_addr.s_addr);
	mcastaddr.sin_port = htons(port);
	// send to this message to sthiservers in multicast group
	Sendto(sockfd, message, strlen(message), 0, (SA *) &mcastaddr, len);

	Signal(SIGALRM, timeout);
	alarm(2);

	while (1) {
	   if((n = recvfrom(sockfd,line,MAXLINE,0,(SA *)&replyAdd, &len)) < 0){
	      if (errno == EINTR)
		 break;
	      else
	  	 err_sys("error recvfrom");
	   }
	   line[n] = 0;
	   printf("The time on server %s:%d is: ", inet_ntop(AF_INET, &replyAdd.sin_addr, addr, sizeof(addr)), ntohs(replyAdd.sin_port));
	   printf("%s \n", line);
           noOfReply ++;
	   alarm(2);
	}
	
	printf("%d Replies have been received \n", noOfReply);

	return 0;
}

static void timeout() {

}
