/* QAS_SKCO.c - Server for exchange of Question and Answer over a Sockets session */
#include        <stdio.h>
#include        <string.h>
#include        <sys/types.h>
#include        <sys/socket.h>
#include        <netinet/in.h>
#include        <arpa/inet.h>
#define strequ(a,b)     (!(strcmp(a,b)))

#define SERV_TCP_PORT   3700

/* A macro to handle error messages from SOCKET calls */
#define IF_ERROR(msg)   \
	if ( ErrorNumber < 0 )\
	{       fprintf(stderr,"Cannot %s\n",msg);\
		return 1;\
	}




int             main    
	( void )
{       struct sockaddr_in LocalNetName;/* My name as required by SOCKETS */
	struct sockaddr_in RemoteNetName;/* Remote name as required by SOCK*/
	int		SizeRemoteNetName;/* Size of above for accept */
	int             ServiceSocket;  /* Initial socket descriptor */
	int             Sess;           /* Session fd for comms channel */
	int             ErrorNumber;    /* Return value from socket calls */
#define SIZE            128
	char            Buffer[SIZE];   /* Data buffer for message */
	int             DataBufferSize; /* Amount of data in buffer */
	int             ToStop;         /* Has request to stop been met */

	/***** Interact over the network *****/
	/* Create a socket for the service */
	ErrorNumber = socket(AF_INET, SOCK_STREAM, 0);
	IF_ERROR("Create Socket");
	ServiceSocket = ErrorNumber;

	/* Bind Name to Socket */
	bzero( (char *) &LocalNetName, sizeof(LocalNetName));
	LocalNetName.sin_family = AF_INET;
	LocalNetName.sin_addr.s_addr = htonl(INADDR_ANY);
	LocalNetName.sin_port = htons(SERV_TCP_PORT);
	ErrorNumber = bind( ServiceSocket, (struct sockaddr *)&LocalNetName,
						sizeof(LocalNetName) );
	IF_ERROR("Bind Server Name");

	/* Establish session */
	listen(ServiceSocket,1);
	ToStop = 0;
	while ( !ToStop )
	{	SizeRemoteNetName = sizeof(RemoteNetName);
	        ErrorNumber=accept      ( ServiceSocket
					, (struct sockaddr *) &RemoteNetName
					, &SizeRemoteNetName
					);
		IF_ERROR("Accept");
		Sess = ErrorNumber;     /* Socket for this conversation */

		/* Get message */
		DataBufferSize = SIZE;
		ErrorNumber = read(Sess, Buffer, DataBufferSize);
		IF_ERROR("Read");
		DataBufferSize = ErrorNumber;
		Buffer[DataBufferSize] = '\0';

		/* Determine the response */
		if ( strequ(Buffer,"quit") )
		{       ToStop = 1;
			strcpy(Buffer,"Thank you for using ");
			strcat(Buffer,"Socket Connection oriented Q&A service\n");
		}
		else
		{       printf("Received the question: %s\n", Buffer);
			printf("Your answer:");
			gets(Buffer);
		}

		/* Send Reply */
		DataBufferSize = strlen(Buffer);
		ErrorNumber = write(Sess, Buffer, DataBufferSize);
		IF_ERROR("Write");
		printf("Have sent reply '%s'\n",Buffer);        /* Debug */

		/* Terminate Session */
		ErrorNumber = close(Sess);
		IF_ERROR("Close connection");
	}

	/* Its all over now */
	printf("Terminating\n");
	ErrorNumber = close(ServiceSocket);
	IF_ERROR("Close socket");
	return 0;
}
