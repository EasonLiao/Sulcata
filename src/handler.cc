#include "handler.h"
#include <unistd.h>
#include <iostream>
#include "message.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "config.h"

#define LINESIZE 4096

namespace sulcata{
  using namespace std;

  int connection_handler::serve(int fd, sockaddr_in* addr){
    rio_t rt;
    rio_readinitb(&rt, fd);
    http_request req;

    while(parse_request_stream(&rt, req) == OK){
      int ret = request_handler::handle(&rt, req);
    }
    
    cout<<"end!!"<<endl;
    close(fd);
    return 0;
  }

  int connection_handler::parse_request_stream(rio_t *rt, http_request& req){
    char line[LINESIZE];
    char method[32];
    char path[LINESIZE];
    char http_version[32];
    int ret;
    
    //read request line
    ret = rio_readlineb(rt, line, LINESIZE);
    if(ret == 0 || ret == -1)
      return CONNECTION_ERROR;
    
    sscanf(line, "%s %s %s", method, path, http_version);
    req.set_method(method);
    req.set_path(path);
    req.set_http_ver(http_version);
    
    //read headers
    while(1){
      ret = rio_readlineb(rt, line, LINESIZE);
      
      if(ret == 0 || ret == -1)
        return CONNECTION_ERROR;
      
      if(strcmp(line, "\r\n") == 0) //end of the headers
        break;
      
      std::string strline = line;
      std::string key, value;
      size_t pos = strline.find(':');
      
      key = strline.substr(0, pos);

      if(isspace(strline[pos + 1]))
        pos += 1;

      value = strline.substr(pos + 1, strline.size() - pos - 2);
      req.headers().set(key, value);  
    }

    return OK;
  }
  
  int request_handler::handle(rio_t *rt, http_request& req){ 
    http_response resp;
    resp.headers().set("Server", "Sulcate");
    resp.headers().set("Connection", "ssSulcate");
    resp.set_status_code(200);
    resp.set_status_description("HAHA OK");
    resp.set_http_ver("HTTP/1.1");

    std::cout<<req<<std::endl;
    std::cout<<"handled"<<std::endl;
    
    std::cout<<resp<<std::endl;

    return 0;
  }

}//namespace ends.
