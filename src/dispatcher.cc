#include "dispatcher.h"
#include <iostream>
#include "handler.h"

namespace sulcata{
  using namespace std;

  sequential_dispatcher::sequential_dispatcher(){}

  bool sequential_dispatcher::dispatch(int fd, sockaddr_in *addr){
    connection_handler::serve(fd, addr);

    return true;
  }

}//namespace ends.

