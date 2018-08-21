/* QAC_SKCO.c - Client for exchange of Question & Answer over a Sockets session */
#include        <stdio.h>
#include        <string.h>
#include        <sys/types.h>
#include        <sys/socket.h>
#include        <netinet/in.h>
#include        <arpa/inet.h>

#define SERV_TCP_PORT   3700

/* A macro to handle error messages from SOCKET calls */
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
	struct sockaddr_in   RemoteNetName; /* Remote name as required by SOCK*/
	int             Sess;           /* Session fd for comms channel */
	int             ErrorNumber;    /* From socket calls */
#define SIZE            128
	char            Buffer[SIZE];   /* Data buffer for message */
	int             DataBufferSize; /* Amount of data in buffer */

	/***** Command line analysis *****/
	if ( argc != 2 )
	{       fprintf(stderr,"USAGE: qac_skco remote\n");
		return 1;
	}
	remote_name = argv[1];

	/***** Interact over the network *****/
	/* Create a socket */
	ErrorNumber = socket(AF_INET, SOCK_STREAM, 0);
	IF_ERROR("Create Socket");
	Sess = ErrorNumber;

	/* Establish session */
	bzero( (char *) &RemoteNetName, sizeof(RemoteNetName));
	RemoteNetName.sin_family = AF_INET;
	RemoteNetName.sin_addr.s_addr = inet_addr(remote_name);
	RemoteNetName.sin_port = htons(SERV_TCP_PORT);

	ErrorNumber=connect(Sess, (struct sockaddr *)&RemoteNetName,
						sizeof(RemoteNetName));
	IF_ERROR("Connect");

	/* Send a message */
	printf("What is the question you want to send?\n\t:");  /* Get user's message */
	gets(Buffer);
	ErrorNumber = write(Sess, Buffer, strlen(Buffer));
	IF_ERROR("Write");
	printf("CLIENT: Sent question '%s'\n",Buffer);          /* Debug */

	/* Get Reply */
	DataBufferSize = SIZE;
	ErrorNumber = read(Sess, Buffer, DataBufferSize);
	IF_ERROR("Read");
	DataBufferSize = ErrorNumber;
	Buffer[DataBufferSize] = '\0';
	printf("Answer: %s\n", Buffer);

	/* Terminate Session */
	ErrorNumber = close(Sess);
	IF_ERROR("Client Close");

	/* Its all over now */
	printf("Terminating\n");                                /* Debug */
	return 0;
}
