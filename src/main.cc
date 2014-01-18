#include <iostream>
#include "server.h"

int main(int argv, char* argc[]){
  
  sulcata::server *s = sulcata::server::instance();
  s->start(8080);

  return 0;
}
