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
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>  //needed for open
#include <fcntl.h>     //needed for open

#define	MAXLINE	4096
#define	LISTENQ	1024
#define	SERV_TCP_PORT	51020
#define	SA	struct sockaddr
