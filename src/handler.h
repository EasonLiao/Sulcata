#ifndef SULCATA_HANDLER_H
#define SULCATA_HANDLER_H
#include <netinet/in.h>

namespace sulcata{
  
  class connection_handler{
    public:
      static int serve(int fd, sockaddr_in *addr);
  };

}//namespace ends.

#endif
