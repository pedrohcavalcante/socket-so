#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>

int* calculaMatriz (int* vA, int szA, int* vB, int szB, int* vC, int szC, int* vD, int szD, int* vE, int szE) {
	for (int i = 0; i < szE; i++) {
		for (int j = 0; j < szE; j++) {
			if (i == 0) {
				vE[i] += vA[j] * vB[j];
			}
			else if (i == 1) {
				vE[i] += vA[j] * vC[j];	
			}
			else {
				vE[i] += vA[j] * vD[j];
			}
		}
	}
	return vE;
}

int main (int argc, char* argv[]) {

	struct sockaddr_in mestre;
	int sock;
	socklen_t slen = sizeof(mestre);

	int TAM = 0;

	int port = atoi (argv[1]);

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == -1) {
		printf("Erro na criacao do socket.\n");
		return 1;
	}
	
	memset((char*) &mestre, 0, sizeof(mestre));
	mestre.sin_family = AF_INET;
	mestre.sin_port = htons (port);
	mestre.sin_addr.s_addr = htonl (INADDR_ANY);

	if (bind(sock, (struct sockaddr *) &mestre, sizeof (mestre)) == -1) {
		printf("Erro no binding.\n");
		return 1;
	}

	if (recvfrom(sock, &TAM, sizeof(int), 0, (struct sockaddr *) &mestre, &slen) == -1) {
		printf("Erro ao receber tamanho.\n");
	}

	return 0;
}