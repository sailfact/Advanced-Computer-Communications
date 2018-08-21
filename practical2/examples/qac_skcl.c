/* QAC_SKCL.C - Question and answer via SOCKET datagrams */
#include        <stdio.h>
#include        <string.h>
#include        <sys/types.h>
#include        <sys/socket.h>
#include        <netinet/in.h>
#include        <arpa/inet.h>

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
{       char *          remote_name;    /* Pointer to remote's name */
	struct sockaddr_in   LocalNetName;  /* My name as required by SOCKETS */
	struct sockaddr_in   RemoteNetName; /* Remote name as SOCKETS requires*/
	int             SizeRemoteNetName;  /* Bytes actually used in name */
	int             Sock;           /* Socket No for comms channel */
	int             ErrorNumber;    /* If Sockets returns -1 */
#define SIZE            128
	char            Buffer[SIZE];   /* Data buffer for message */
	int             DataBufferSize; /* Amount of data in buffer */

	/***** Command line analysis *****/
	if ( argc != 2 )
	{       fprintf(stderr,"USAGE: qac_skcl remote\n");
		return 1;
	}
	remote_name = argv[1];

	/***** Interact over the network *****/
	/* Create a socket */
	ErrorNumber = socket(AF_INET, SOCK_DGRAM, 0);
	IF_ERROR("Create Socket");
	Sock = ErrorNumber;

	/* Set Name to Socket */
	bzero( (char *) &LocalNetName, sizeof(LocalNetName));
	LocalNetName.sin_family = AF_INET;
	LocalNetName.sin_addr.s_addr = htonl(INADDR_ANY);
	LocalNetName.sin_port = htons(0);
	ErrorNumber = bind( Sock, (struct sockaddr *)&LocalNetName,
						sizeof(LocalNetName) );
	IF_ERROR("Bind Server Name");

	/* Set Name Of Remote Socket */
	bzero( (char *) &RemoteNetName, sizeof(RemoteNetName));
	RemoteNetName.sin_family = AF_INET;
	RemoteNetName.sin_addr.s_addr = inet_addr(remote_name);
	RemoteNetName.sin_port = htons(SERV_UDP_PORT);

	/* Send a question */
	printf("What is the question you want to send\n\t:");   /* Get user's question */
	gets(Buffer);
	DataBufferSize = strlen(Buffer);
	ErrorNumber = sendto(Sock, Buffer, DataBufferSize, 0,
					(struct sockaddr *) &RemoteNetName,
					sizeof(RemoteNetName));
	IF_ERROR("Send Datagram");
	printf("Sent the message '%s'\n",Buffer);

	/* Get Reply */
	DataBufferSize = SIZE;
	SizeRemoteNetName = sizeof(RemoteNetName);
	ErrorNumber = recvfrom(Sock, Buffer, DataBufferSize, 0,
					(struct sockaddr *) &RemoteNetName,
					&SizeRemoteNetName);
	IF_ERROR("Receive Datagram");
	DataBufferSize = ErrorNumber;
	Buffer[DataBufferSize] = '\0';
	printf("Received message: %s\n", Buffer);

	/* Its all over now */
	ErrorNumber = close( Sock );
	IF_ERROR("Close");
	printf("Terminating\n");
	return 0;
}
