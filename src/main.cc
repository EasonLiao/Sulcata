#include <iostream>
#include "server.h"
#include "config.h"

int main(int argv, char* argc[]){
  
  sulcata::configuration* config = sulcata::configuration::instance();
  sulcata::server *s = sulcata::server::instance();
  s->start(8080);

  return 0;
}
