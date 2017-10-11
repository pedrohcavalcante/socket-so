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
	
	vetorA = malloc (sizeof(int) * TAM);
	vetorB = malloc (sizeof(int) * TAM);
	vetorC = malloc (sizeof(int) * TAM);
	// int TAM = atoi (argv[2]);
	
	int matrizA[TAM][TAM];
	int matrizB[TAM][TAM];


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

	// INICIALIZANDO MATRIZ
	
	srand(time(NULL));
	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			matrizA[i][j] = rand() % 100;
			matrizB[i][j] = rand() % 500;
		}
	}

	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
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
	for (int i = 0; i < TAM; i++) {
		if (i == TAM - 1) {
			printf("%d\n", vetorA[i]);
		}
		else {
			printf("%d ", vetorA[i]);
		}
	}
	for (int i = 0; i < TAM; i++) {
		if (i == TAM - 1) {
			printf("%d\n", vetorB[i]);
		}
		else {
			printf("%d ", vetorB[i]);
		}
	}
	for (int i = 0; i < TAM; i++) {
		if (i == TAM - 1) {
			printf("%d\n", vetorC[i]);
		}
		else {
			printf("%d ", vetorC[i]);
		}
	}
	printf("\n");
	

	// ENVIANDO PACOTE PARA ESCRAVO A
	if (sendto(sockA, vetorA, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoA, slenA) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA ESCRAVO B
	if (sendto(sockB, vetorB, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoB, slenB) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO C
	if (sendto(sockC, vetorC, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoC, slenC) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}

	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			if (i == 0) {
				vetorA[j] = matrizB[i][j];
			}
			else if (i == 1) {
				vetorB[j] = matrizB[i][j];
			}
			else {
				vetorC[j] = matrizB[i][j];
			}
		}
	}

	printf("PRINTANDO A MATRIZ B:\n");
	for (int i = 0; i < TAM; i++) {
		if (i == TAM - 1) {
			printf("%d\n", vetorA[i]);
		}
		else {
			printf("%d ", vetorA[i]);
		}
	}
	for (int i = 0; i < TAM; i++) {
		if (i == TAM - 1) {
			printf("%d\n", vetorB[i]);
		}
		else {
			printf("%d ", vetorB[i]);
		}
	}
	for (int i = 0; i < TAM; i++) {
		if (i == TAM - 1) {
			printf("%d\n", vetorC[i]);
		}
		else {
			printf("%d ", vetorC[i]);
		}
	}
	printf("\n");


	if (sendto(sockA, vetorA, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoA, slenA) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA ESCRAVO B
	if (sendto(sockB, vetorA, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoB, slenB) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO C
	if (sendto(sockC, vetorA, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoC, slenC) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}

	if (sendto(sockA, vetorB, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoA, slenA) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA ESCRAVO B
	if (sendto(sockB, vetorB, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoB, slenB) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO C
	if (sendto(sockC, vetorB, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoC, slenC) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}

	if (sendto(sockA, vetorC, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoA, slenA) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA ESCRAVO B
	if (sendto(sockB, vetorC, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoB, slenB) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO C
	if (sendto(sockC, vetorC, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoC, slenC) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}

	recvfrom(sockA, buf, BUFLEN, 0, (struct sockaddr *) &escravoA, &slenA);
  	printf("Pacote recebido de %s: %d\nDado: %s\n", inet_ntoa(escravoA.sin_addr), ntohs(escravoA.sin_port), buf);
  	close(sockA);

 	recvfrom(sockB, buf, BUFLEN, 0, (struct sockaddr *) &escravoB, &slenB);
  	printf("Pacote recebido de %s: %d\nDado: %s\n", inet_ntoa(escravoB.sin_addr), ntohs(escravoB.sin_port), buf);
  	close(sockB);

 	recvfrom(sockC, buf, BUFLEN, 0, (struct sockaddr *) &escravoC, &slenC);
  	printf("Pacote recebido de %s: %d\nDado: %s\n", inet_ntoa(escravoC.sin_addr), ntohs(escravoC.sin_port), buf);
  	close(sockC);
	
	return 0;
}