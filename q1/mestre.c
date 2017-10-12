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
#define TAM 3

void print_matriz (int l, int c, int m[l][c]) {
	for (int i = 0; i < TAM; i++) {
		printf("[");
		for (int j = 0; j < TAM; j++) {
			if (j == TAM - 1) {
				printf("%d]\n", m[i][j]);
			}
			else {
				printf("%d ", m[i][j]);
			}
		}
	}
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
	struct sockaddr_in escravoA, escravoB, escravoC;
	int sockA, sockB, sockC, i;
	socklen_t slenA = sizeof(escravoA);
	socklen_t slenB = sizeof(escravoB);
	socklen_t slenC = sizeof(escravoC);

	char buf[BUFLEN];

	int port_in = atoi (argv[1]);
	int portaA = port_in;
	int portaB = port_in + 1;
	int portaC = port_in + 2;

	int* vetorA;
	int* vetorB;
	int* vetorC;
	
	// const int TAM = atoi (argv[2]);
	vetorA = malloc (sizeof(int) * TAM);
	vetorB = malloc (sizeof(int) * TAM);
	vetorC = malloc (sizeof(int) * TAM);

	
	int matrizA[TAM][TAM] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
	int matrizB[TAM][TAM] = {{8, 7, 6}, {5, 4, 3}, {2, 1, 0}};

	sockA = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockA == -1) {
		printf("Erro ao criar socket.\n");
		return 1;
	}
	sockB = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockB == -1) {
		printf("Erro ao criar socket.\n");
		return 1;
	}
	sockC = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockC == -1) {
		printf("Erro ao criar socket.\n");
		return 1;
	}

	memset((char*) &escravoA, 0, sizeof(escravoA));
	escravoA.sin_family = AF_INET;
	escravoA.sin_port = htons(portaA);
	if (inet_aton (SRV_IP, &escravoA.sin_addr) == 0) {
		printf("Erro ao transformar endereco.\n");
		return 1;
	}

	memset((char*) &escravoB, 0, sizeof(escravoB));
	escravoB.sin_family = AF_INET;
	escravoB.sin_port = htons(portaB);
	if (inet_aton (SRV_IP, &escravoB.sin_addr) == 0) {
		printf("Erro ao transformar endereco.\n");
		return 1;
	}
	memset((char*) &escravoC, 0, sizeof(escravoC));
	escravoC.sin_family = AF_INET;
	escravoC.sin_port = htons(portaC);
	if (inet_aton (SRV_IP, &escravoC.sin_addr) == 0) {
		printf("Erro ao transformar endereco.\n");
		return 1;
	}

	// INICIALIZANDO AS MATRIZES
	/*
	srand(time(NULL));
	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			matrizA[i][j] = rand() % 100;
			matrizB[i][j] = rand() % 500;
		}
	}
	*/

	// ASSOCIACAO COM MATRIZ A
	for (int i = 0; i < TAM; i++) {
		for(int j = 0; j < TAM; j++) {
			if (i == 0) {
				vetorA[j] = matrizA[i][j];
			}
			else if (i == 1) {
				vetorB[j] = matrizA[i][j];
			}
			else {
				vetorC[j] = matrizA[i][j];
			}
		}
	}
	
	printf("PRINTANDO A MATRIZ A:\n");
	print_matriz(TAM, TAM, matrizA);
	printf("\n");
	

	// ENVIANDO PACOTE PARA O ESCRAVO A
	if (sendto(sockA, vetorA, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoA, slenA) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO B
	if (sendto(sockB, vetorB, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoB, slenB) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO C
	if (sendto(sockC, vetorC, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoC, slenC) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}

	// ASSOCIACAO COM MATRIZ B

	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			if (j == 0) {
				vetorA[i] = matrizB[i][j];
			}
			else if (j == 1) {
				vetorB[i] = matrizB[i][j];
			}
			else {
				vetorC[i] = matrizB[i][j];
			} 
		}
	}

	printf("PRINTANDO A MATRIZ B:\n");
	print_matriz(TAM, TAM, matrizB);
	printf("\n");

	// ENVIANDO PACOTE PARA O ESCRAVO A
	if (sendto(sockA, vetorA, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoA, slenA) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO B
	if (sendto(sockB, vetorA, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoB, slenB) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO C
	if (sendto(sockC, vetorA, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoC, slenC) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO A
	if (sendto(sockA, vetorB, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoA, slenA) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO B
	if (sendto(sockB, vetorB, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoB, slenB) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO C
	if (sendto(sockC, vetorB, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoC, slenC) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO A
	if (sendto(sockA, vetorC, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoA, slenA) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO B
	if (sendto(sockB, vetorC, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoB, slenB) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO C
	if (sendto(sockC, vetorC, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoC, slenC) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}

	free(vetorA);
	free(vetorB);
	free(vetorC);

	vetorA = malloc (sizeof(int) * TAM);
	vetorB = malloc (sizeof(int) * TAM);
	vetorC = malloc (sizeof(int) * TAM);


	recvfrom(sockA, &vetorA, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoA, &slenA);
  	for (int i = 0; i < TAM; i ++) {
	  	printf("Pacote recebido de %s: %d\nDado: %d\n", inet_ntoa(escravoA.sin_addr), ntohs(escravoA.sin_port), vetorA[i]);
  	}
  	close(sockA);

 	recvfrom(sockB, &vetorB, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoB, &slenB);
  	for (int i = 0; i < TAM; i ++) {
	  	printf("Pacote recebido de %s: %d\nDado: %d\n", inet_ntoa(escravoB.sin_addr), ntohs(escravoB.sin_port), vetorB[i]);
  	}
  	close(sockB);

 	recvfrom(sockC, &vetorB, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoC, &slenC);
   	for (int i = 0; i < TAM; i ++) {
	 	printf("Pacote recebido de %s: %d\nDado: %d\n", inet_ntoa(escravoC.sin_addr), ntohs(escravoC.sin_port), vetorC[i]);
  	}
  	close(sockC);
	
	return 0;
}