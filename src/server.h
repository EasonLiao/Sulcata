#ifndef SULCATA_SERVER_H
#define SULCATA_SERVER_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "dispatcher.h"
#include <mutex>

namespace sulcata{

  class server{
    uint16_t port_;
    int listenfd_;
    dispatcher* dispatcher_;
    
    static std::mutex mtx_;
    static server* singleton_;

    public:
      server();  
      bool start(uint16_t port = 80);  
      static server* instance();
  };

}//namespace end

#endif
