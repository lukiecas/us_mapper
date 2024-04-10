#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
void sendData() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    while(true){
        std::string message;
        std::cout << "send a message: ";
        std::cin >> message;
        const char* ptrMessage = message.c_str();
        send(clientSocket, ptrMessage, strlen(ptrMessage), 0);
        
    }
    close(clientSocket);
    
}
int main() {
    sendData();
    return 0;
}