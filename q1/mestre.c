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
	
	int matriz[TAM][TAM];

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
			matriz[i][j] = rand() % 100;
		}
	}

	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			if (i == 0) {
				vetorA[j] = matriz[i][j];
			}
			else if (i == 1) {
				vetorB[j] = matriz[i][j];
			}
			else {
				vetorC[j] = matriz[i][j];
			}
		}
	}
	
	// ENVIANDO PACOTE PARA ESCRAVO A
	if (sendto(sockA, &vetorA, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoA, slenA) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA ESCRAVO B
	if (sendto(sockB, &vetorB, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoB, slenB) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	// ENVIANDO PACOTE PARA O ESCRAVO C
	if (sendto(sockC, &vetorC, sizeof(int) * TAM, 0, (struct sockaddr *) &escravoC, slenC) == -1) {
		printf("Erro ao enviar pacote.\n");
		return 1;
	}
	return 0;
}