#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void scan(char* ip, int port) {
	int sockfd = 0, res;
	struct sockaddr_in* addr = malloc(sizeof(struct sockaddr_in));

	if(!addr) {
		perror("malloc() failed");
		exit(EXIT_FAILURE);
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket() error");
		exit(EXIT_FAILURE);
	}

	addr->sin_family = AF_INET;
	if((res = inet_aton(ip, &addr->sin_addr)) == 0) {
		perror("invalid ip address");
		exit(EXIT_FAILURE);
	}
	addr->sin_port = htons(port);

	if(res = connect(sockfd, (struct sockaddr*) addr, sizeof(struct sockaddr)) != -1) {
		printf("%d open\n", port);
	}

	free(addr);
}

int main(int argc, char* argv[]) {
	if(argc < 4) {
		printf("./scaner <ip> <start_port_number> <end_port_number>\n");
		return EXIT_SUCCESS;
	}

	char* ip = argv[1];
	int s_port = atoi(argv[2]);
	int e_port = atoi(argv[3]);
	int i;

	printf("Started scan for %s\n", ip);
	printf("Range %d-%d\n", s_port, e_port);

	for(i = s_port; i <= e_port; i++) {
		scan(ip, i);
	}

	return EXIT_SUCCESS;
}