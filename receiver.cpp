#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <iostream>
#define PORT 8080

using json = nlohmann::json;

int main(int argc, char const* argv[])
{
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char buffer[1024] = { 0 };
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket creation error\n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("Invalid address\n");
		return -1;
	}

	if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}

    while (true) {
        valread = read(client_fd, buffer, 1024);
        json msg_json = json::parse(std::string(buffer));

        for (auto obj : msg_json[0]["objects"]) { 
            std::cout << "lat, lon:" << obj["lat"] << ", " << obj["lon"] << std::endl;
        }
    }

	return 0;
}
