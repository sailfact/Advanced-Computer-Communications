#include "acc.h"

void str_fileRqt(int sockfd) {
	FILE *fp;
	char *filename;
	ssize_t n;
	char line[MAXLINE];

	while (1) {
		if ((n = Readline(sockfd, line, MAXLINE)) == 0)
			return;

		if (sscanf(line, "%s", filename) == 1) {
			fp = fopen (filename,"r");
			if (fp!=NULL)
			{
				Fgets(line, MAXLINE, fp);
				n = strlen(line);
				Writen(sockfd, line, n);
				fclose (fp);
			}
		}
		else {
			snprintf(line, sizeof(line), "input error\n");
			n = strlen(line);
			Writen(sockfd, line, n);
		}
	}
}
