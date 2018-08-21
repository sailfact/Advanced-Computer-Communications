/* nameaddr.c - convert a host name to an address */
#include	<stdlib.h>		/* NULL */
#include	<ctype.h>		/* isdigit */
#include	<sys/types.h>		/* Sockets */
#include	<sys/socket.h>		/* inet_addr, inet_ntoa */
#include	<netinet/in.h>		/* inet_addr, inet_ntoa */
#include	<arpa/inet.h>		/* inet_addr, inet_ntoa */
#include	<netdb.h>		/* gethostbyname */

/* inet_host2addr
**	input is a string containing a host name which is either
**		internet address in dot notation
**		hostname.domainname
**	output is a 32 bit network byte order internet address
*/

int		inet_host2addr
	( char *		host	/* User supplied host name */
	, struct in_addr *	address	/* Address as required by sockets */
	)
{	if ( isdigit(*host) )
	{	/* Number is is in internet address dot notation */
		address->s_addr = inet_addr(host);
	}
	else
	{	/* hostname.domainname form */
		struct hostent *	HostData;

		HostData = gethostbyname(host);
		if ( HostData == NULL )
			return -1;
		*address = *((struct in_addr *) HostData->h_addr);
	}

	return 0;			/* No error */
}



/*** Test Mainline */
#include	<stdio.h>			/* fprintf */

void		main
	( int		argc
	, char *	argv[]
	)
{	char *		SuppliedAddress;	/* Of remote system */
	struct in_addr	address;		/* Socket Address  */

	/* Command Line */
	if ( argc != 2 )
	{	fprintf(stderr,"USAGE: nameaddr name\n");
		exit(1);
	}
	SuppliedAddress = argv[1];

	/* Convert the name into an internet address */
	if ( inet_host2addr(SuppliedAddress,&address) == -1 )
	{	fprintf(stderr,"Could not convert the name %s\n",
							SuppliedAddress);
		exit(1);
	}

	/* Print out result */
	printf("Host '%s' has internet address %lx = %s\n"
			, SuppliedAddress
			, address.s_addr
			, inet_ntoa(address)
			);

	exit(0);
}
