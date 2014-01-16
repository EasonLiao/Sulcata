#ifndef SULCATA_SERVER_H
#define SULCATA_SERVER_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "dispatcher.h"

namespace sulcata{

  class server{
    uint16_t port_;
    uint16_t max_connections_;
    int listenfd_;
    dispatcher* dispatcher_;

    public:
      server(uint16_t port, uint16_t max_connections);  
      bool start();  
  };

}//namespace end

#endif
