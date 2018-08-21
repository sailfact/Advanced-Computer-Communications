/* QAS_SKC:.C - Question and answer via SOCKET datgrams */
#include        <stdio.h>
#include        <string.h>
#include        <sys/types.h>
#include        <sys/socket.h>
#include        <netinet/in.h>
#include        <arpa/inet.h>
#define strequ(a,b)     (!strcmp(a,b))

#define SERV_UDP_PORT   3700

/* A macro to handle error messages from Socket calls */
#define IF_ERROR(msg)   \
	if ( ErrorNumber < 0 )\
	{       fprintf(stderr,"Cannot %s\n",msg);\
		return 1;\
	}




int             main    
	( int           argc            /* Number of arguments */
	, char *        argv[]          /* Pointers to arguments */
	)
{       struct sockaddr_in   LocalNetName;  /* My name as required by SOCKETS */
	struct sockaddr_in   RemoteNetName; /* Remote name as SOCKETS requires*/
	int             SizeRemoteNetName;  /* Bytes actually used in name */
	int             Sock;           /* Socket No for comms channel */
	int             ErrorNumber;    /* If Sockets returns -1 */
#define SIZE            128
	char            Buffer[SIZE];   /* Data buffer for message */
	int             DataBufferSize; /* Amount of data in buffer */
	int             ToStop;         /* Is Server to stop */

	/* Create a socket */
	ErrorNumber = socket(AF_INET, SOCK_DGRAM, 0);
	IF_ERROR("Create Socket");
	Sock = ErrorNumber;

	/* Set Name to Socket */
	bzero( (char *) &LocalNetName, sizeof(LocalNetName));
	LocalNetName.sin_family = AF_INET;
	LocalNetName.sin_addr.s_addr = htonl(INADDR_ANY);
	LocalNetName.sin_port = htons(SERV_UDP_PORT);
	ErrorNumber = bind( Sock, (struct sockaddr *)&LocalNetName,
						sizeof(LocalNetName) );
	IF_ERROR("Bind Server Name");

	/* Interact over the network */
	ToStop = 0;
	while ( !ToStop )
	{       /* Get Message */
		DataBufferSize = SIZE;
		SizeRemoteNetName = sizeof(RemoteNetName);
		ErrorNumber = recvfrom(Sock, Buffer, DataBufferSize, 0,
					(struct sockaddr *) &RemoteNetName,
					&SizeRemoteNetName);
		IF_ERROR("Receive Datagram");
		DataBufferSize = ErrorNumber;
		Buffer[DataBufferSize] = '\0';

		/* Determine the response */
		if ( strequ(Buffer,"quit") )
		{       ToStop = 1;     /* The server is to stop */
			strcpy(Buffer, "Thank you for using ");
			strcat(Buffer, "Sockets Connectionless Q&A service\n");
		}
		else
		{       printf("Received the question: %s\n", Buffer);
			printf("Your answer:");
			gets(Buffer);
		}

		/* Send Reply */
		DataBufferSize = strlen(Buffer);
		ErrorNumber = sendto(Sock, Buffer, DataBufferSize, 0,
					(struct sockaddr *) &RemoteNetName,
					sizeof(RemoteNetName));
		IF_ERROR("Send Datagram");
		printf("Have sent reply '%s'\n",Buffer);        /* Debug */
	}

	/* Its all over now */
	ErrorNumber = close( Sock );
	IF_ERROR("Close");
	printf("Terminating\n");
	return 0;
}
