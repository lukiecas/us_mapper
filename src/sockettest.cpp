#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <list>
#include <thread>
std::list<std::string> values; 

void receiveData() {

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    while(true) {
        char buffer[1024] = {0};
        recv(clientSocket, buffer, sizeof(buffer), 0);
        values.push_front(buffer);
    }
    close(serverSocket);
}
int main() {
    std::string result;
    std::thread t1(receiveData);
    while(true) {
        for(std::string element : values) {
            result += element + " ";
        }
        
        std::cout << result << std::endl;
    }
    
    
    return 0;
}