#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFLEN 512
#define SRV_IP "127.0.0.1"

int main (int argc, char * argv[]) {
	struct sockaddr_in escravoA, escravoB, escravoC;
	int sockA, sockB, sockC, i;
	socklen_t slenA = sizeof(escravoA);
	socklen_t slenB = sizeof(escravoB);
	socklen_t slenC = sizeof(escravoC);

	int portaA = atoi (argv[1]);
	int portaB = portaA++;
	int portaC = portaB++;

	int* vetorA;
	int* vetorB;
	int* vetorC;
	
	int TAM = 3; // atoi (argv[2])
	
}