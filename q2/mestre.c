#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

#define BUFLEN 512
#define SRV_IP "127.0.0.1"

void print_matriz (int l, int c, int** m) {
	for (int i = 0; i < l; i++) {
		printf("[");
		for (int j = 0; j < c; j++) {
			if (j == c-1) {
				printf("%d]\n", m[i][j]);
			}
			else {
				printf("%d\t", m[i][j]);
			}
		}
	}
}
void print_vet (int * vet, int size) {
	int i = 0;
	printf("[");
	while (i < size) {
		if (i == size - 1) {
			printf("%d]\n", vet[i]);
		}
		else {
			printf("%d ", vet[i]);

		}
		i++;
	}
}

int main (int argc, char* argv[]) {

	int port_in = atoi(argv[1]);
	int TAM = atoi(argv[2]);

	int ports[TAM];
	for (int i = 0; i < TAM; i++) {
		ports[i] = port_in + i;
	}

	int ** matrizA = malloc (sizeof(int*) * TAM);
	int ** matrizB = malloc (sizeof(int*) * TAM);
	for (int i = 0; i < TAM; i++) {
		matrizA[i] = malloc (sizeof(int) * TAM);
		matrizB[i] = malloc (sizeof(int) * TAM);
	}
	srand(time(NULL));
	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			matrizA[i][j] = rand() % 50;
			matrizB[i][j] = (rand() % 50) + 50;
		}
	}
	printf("\n");
	print_matriz (TAM, TAM, matrizA);
	printf("\n");
	print_matriz (TAM, TAM, matrizB);
	printf("\n");

	int sock[TAM];
	socklen_t slen[TAM];
	struct sockaddr_in escravo[TAM];

	for (int i = 0; i < TAM; i++) {
		slen[i] = sizeof(escravo[i]);
	}

	for (int i = 0; i < TAM; i++) {
		sock[i] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sock[i] == -1) {
			printf("Erro ao criar o socket.\n");
			return 1;
		}
	}
	for (int i = 0; i < TAM; i++) {
		memset((char*) &escravo[i], 0, sizeof(&escravo[i]));
		escravo[i].sin_family = AF_INET;
		escravo[i].sin_port = htons (ports[i]);
		if (inet_aton(SRV_IP, &escravo[i].sin_addr) == 0) {
			printf("Erro ao transformar endereco.\n");
			return 1;
		}
	}

	int vetor[TAM];

	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			vetor[j] = matrizA[i][j];
		}
		if (sendto(sock[i], &TAM, sizeof(int), 0, (struct sockaddr *) &escravo[i], slen[i]) == -1) {
			printf("Erro ao enviar pacote.\n");
			return 1;
		}
		if (sendto(sock[i], vetor, sizeof(int) * TAM, 0, (struct sockaddr *) &escravo[i], slen[i]) == -1) {
			printf("Erro ao enviar pacote.\n");
			return 1;
		}
 	}
 	for (int i = 0; i < TAM; i++) {
 		for (int j = 0; j < TAM; j++) {
 			vetor[j] = matrizB[i][j];
 		}
 		for (int j = 0; j < TAM; j++) {
 			if (sendto(sock[j], vetor, sizeof(int) * TAM, 0, (struct sockaddr *) &escravo[j], slen[j]) == -1) {
 				printf("Erro ao enviar matriz.\n");
 				return 1;
 			}
 		}
 	}
	return 0;

}