#include <iostream>
#include "server.h"

int main(int argv, char* argc[]){
  
  sulcata::server *s = sulcata::server::instance();
  s->start();

  return 0;
}
