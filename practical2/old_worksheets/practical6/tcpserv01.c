#include	"acc.h"

static void	*doit(void *);		/* each thread executes this function */

int
main(int argc, char **argv)
{
	int		listenfd, connfd;
	socklen_t	addrlen, len;
	pthread_t	tid;
	struct sockaddr	*cliaddr;

	if (argc == 2)
		listenfd = Tcp_listen(NULL, argv[1], &addrlen);
	else if (argc == 3)
		listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
	else
		err_quit("usage: tcpserv01 [ <host> ] <service or port>");

	cliaddr = (struct sockaddr *) Malloc(addrlen);

	for ( ; ; ) {
		len = addrlen;
		connfd = Accept(listenfd, cliaddr, &len);
		Pthread_create(&tid, NULL, &doit, (void *) connfd);
	}
}

static void *
doit(void *arg)
{
	Pthread_detach(pthread_self());
	str_echo((int) arg);	 /*same function as before */
	Close((int) arg);	/* we are done with connected socket */
	return(NULL);
}
