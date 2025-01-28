#define_WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include<iostream>
#include<winsock2.h>
#include<string>
int main(){
  std::cout<<"Attemting to create a server";
  SOCKET wsocket;
  SOCKET new_wsocket;
  WSADATA wsaData;
  struct sockaddr_in server;
  int server_len;
  int BUFFER_SIZE = 30720;
  //initialize
  if(WSAStartup(MAKEWORD(2,2), &wsaData)) ! =0){
    std::cout<<"Could not initilize";
  }
  //create a socket
  wsocket =socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if(wsocket == INVALID_SOCKET){
    std::cout<<"could not create socket";
    
  }
  //bind to socket to address
  server.sin_family = AF_INET;
  server.sin_addr.s_add = inet_addr("127.0.0.1");
  server.sin_port = htons(8080);
  server_len =sizeof(server);
  if(bind(wsocket,(SOCKADDR *)&server_len) ! = 0){
    std::cout<<"Could not bind socket";
  }
  //listen to address
   if(listen(wsocket, 20) ! = 0){
     std::cout<<"Could not start listening \n";
   }
   std::cout<<"Listening on 127.0.0.1:8080 \n";
   int bytes = 0;
   while(true){
   //accept client request
     new_wsocket = accept(wsocket, (SOCKADDR *)&server,&server_len);
    if(new_wsocket ==INVALID_SOCKET){
      std::cout<<"Could not accept \n";
    }
   
   //read request
   char buff[30720] = {0};
   bytes = recv(new_wsocket,buff, BUFFER_SIZE, 0);
   if(bytes < 0){
     std::cout<<"Could not read client request";
   }
   std::string serverMessage = "HTTP/1.1 200ok\nContent-Type: text/html\nContent-Length: ";
   std::string response ="<html><h1>Hello World</h1></html>";
   serverMessage.append(std::to_string(response.size()));
   serverMessage.append("\n\n");
   serverMessage.append (response);
   
   int bytesSent = 0;
   int totalBytesSent = 0;
   while(totalBytesSent  < serverMessage.size()){
     bytesSent = send(new_wsocket, serverMessage.c_str(),serverMessage.size(), 0);
    if(bytesSent <0){
      std::cout<<"Could not send response";
    }
    totalBytesSent +=bytesSent;
   }
   std::cout<<"sent response to client";
   closesocket(new_wsocket);
   }
   closesocket(new_wsocket);
   WSACleanup();
   
  return 0;
  }
}
