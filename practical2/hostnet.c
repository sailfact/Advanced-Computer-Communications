#include "acc.h"

int main(int argc, char **argv) {
	int a = 384;
	printf("htons(a) = %x\n", htons(a));
	printf("ntohs(a) = %x\n", ntohs(a));
	printf("htons(ntohs(a)) = %x\n", htons(ntohs(a)));
	printf("ntohs(htons(a)) = %x\n", ntohs(htons(a)));

	return 0;
}
