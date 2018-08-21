#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#define	MAXLINE	4096
#define	LISTENQ	1024
#define	SERV_TCP_PORT	52000
#define	SERV_UDP_PORT	52000
#define	SERV_UDP_PORT_BCAST	52000
#define	SERV_UDP_PORT_MCAST	52001
#define	MCAST_GROUP	"224.0.0.7"
#define	SA	struct sockaddr
#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))
typedef	void	Sigfunc(int);
