#include "handler.h"
#include <unistd.h>
#include <iostream>

namespace sulcata{
  using namespace std;

  int connection_handler::serve(int fd, sockaddr_in* addr){
    cout<<"server"<<endl;  
    return 0;
  }

}//namespace ends.
