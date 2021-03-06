#include "server.h"
#include <iostream>
#include <string.h>

namespace sulcata{
  
  server* server::singleton_ = NULL;
  std::mutex server::mtx_;

  server::server() :  port_(8080),
                      listenfd_(-1),
                      dispatcher_(new sequential_dispatcher()){}

  //start the server and wait for connections.
  bool server::start(uint16_t port){
    port_ = port;
    struct sockaddr_in serveraddr, clientaddr;
    int clientfd;
    int optval = 1;

    if((listenfd_ =  socket(AF_INET, SOCK_STREAM, 0)) < 0)
      return false;
   
    if(setsockopt(listenfd_, SOL_SOCKET, SO_REUSEADDR,
                    (const void*)&optval, sizeof(int)) < 0)
        return false;

    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)port_);
   
    if(bind(listenfd_, (sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
      return false;
  
    if(listen(listenfd_, 100) < 0)
      return false;
    
    std::cout<<"Waitting..."<<std::endl;
    
    while(1){
      socklen_t clientlen = sizeof(clientaddr);
      clientfd = accept(listenfd_, (sockaddr*)&clientaddr, &clientlen);  
      
      std::cout<<"Accept client connection request..."<<std::endl;
      std::cout<<"==================================="<<std::endl;
      dispatcher_->dispatch(clientfd, &clientaddr);
    }
  }

  server* server::instance(){
    if(singleton_ == NULL){
      std::lock_guard<std::mutex> lock(mtx_);

      if(singleton_ == NULL){
        singleton_ = new server();
      }
    }

    return singleton_;;
  }

}//namespace ends


