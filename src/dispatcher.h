#ifndef SULCATA_DISPATCHER_H
#define SULCATA_DISPATCHER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace sulcata{

  class dispatcher{
    public:
      virtual bool dispatch(int fd, sockaddr_in* addr) = 0;
      virtual ~dispatcher(){}; 
  };

  class sequential_dispatcher : public dispatcher{
    public:
      sequential_dispatcher();
      bool dispatch(int fd, sockaddr_in* addr);
  };

}//namespace ends.

#endif
