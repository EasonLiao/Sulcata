#include <iostream>
#include "server.h"

int main(int argv, char* argc[]){
  
  sulcata::server s(8080, 10);
  s.start();

  return 0;
}
