#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFLEN 512
#define TAM 3

int* calculaMatriz (int* a, int szA, int* b, int szB, int* c, int szC, int* d, int szD, int* e, int szE) {
	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			if (i == 0) {
				e[i] += a[j]*b[j];
			}
			else if (i == 1) {
				e[i] += a[j]*c[j];	
			}
			else {
				e[i] += a[j]*d[j];
			}
		}
	}
	return e;
}

void print_vet (int * vet, int size) {
	int i = 0;
	printf("[");
	while (i < TAM) {
		if (i == TAM - 1) {
			printf("%d]\n", vet[i]);
		}
		else {
			printf("%d ", vet[i]);

		}
		i++;
	}
}

int main (int argc, char * argv[]) {
	
	struct sockaddr_in mestre;
	int sock_res;

	
	socklen_t slen = sizeof(mestre);
	char buf[BUFLEN];
	
	int port = atoi(argv[1]);
	// const int TAM = atoi(argv[2]);
	
	int vetor[TAM] = {-1,-1,-1};
	int vetorA_Matriz[TAM] = {-1,-1,-1};
	int vetorB_Matriz[TAM] = {-1,-1,-1};
	int vetorC_Matriz[TAM] = {-1,-1,-1};
	int vetor_f[TAM] = {0};
	
	sock_res = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock_res == -1) {
		printf("Erro na criacao do socket.\n");
		return 1;
	}
	memset((char*) &mestre, 0, sizeof(mestre));
	mestre.sin_family = AF_INET;
	mestre.sin_port = htons(port);
	mestre.sin_addr.s_addr = htonl (INADDR_ANY);

	if (bind(sock_res, (struct sockaddr *) &mestre, sizeof(mestre)) == -1) {
		printf("Erro no binding.\n");
		return 1;
	}

	if (recvfrom(sock_res, &vetor, sizeof(int) * TAM, 0, (struct sockaddr *) &mestre, &slen) == -1) {
		printf("Erro ao receber linha.\n");
	}

	for (int i = 0; i < TAM; i++) {
		printf("PACOTE RECEBIDO DE %s: %d\nDADO: %d\n", inet_ntoa(mestre.sin_addr), htons(mestre.sin_port), vetor[i]);
	}

	if (recvfrom(sock_res, &vetorA_Matriz, sizeof(int) * TAM, 0, (struct sockaddr *) &mestre, &slen) == -1) {
		printf("Erro ao receber matriz.\n");
	}

	for (int i = 0; i < TAM; i++) {
		printf("PACOTE RECEBIDO DE %s: %d\nDADO: %d\n", inet_ntoa(mestre.sin_addr), htons(mestre.sin_port), vetorA_Matriz[i]);
	}

	if (recvfrom(sock_res, &vetorB_Matriz, sizeof(int) * TAM, 0, (struct sockaddr *) &mestre, &slen) == -1) {
		printf("Erro ao receber matriz.\n");
	}

	for (int i = 0; i < TAM; i++) {
		printf("PACOTE RECEBIDO DE %s: %d\nDADO: %d\n", inet_ntoa(mestre.sin_addr), htons(mestre.sin_port), vetorB_Matriz[i]);
	}

	if (recvfrom(sock_res, &vetorC_Matriz, sizeof(int) * TAM, 0, (struct sockaddr *) &mestre, &slen) == -1) {
		printf("Erro ao receber matriz.\n");
	}

	for (int i = 0; i < TAM; i++) {
		printf("PACOTE RECEBIDO DE %s: %d\nDADO: %d\n", inet_ntoa(mestre.sin_addr), htons(mestre.sin_port), vetorC_Matriz[i]);
	}

	int* valor = calculaMatriz(vetor, TAM, vetorA_Matriz, TAM, vetorB_Matriz, TAM, vetorC_Matriz, TAM, vetor_f, TAM);
	print_vet(valor, TAM);
	
	sendto(sock_res, valor, sizeof(int) * TAM, 0, (struct sockaddr *) &mestre, slen);

	return 0;
}