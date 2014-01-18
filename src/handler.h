#ifndef SULCATA_HANDLER_H
#define SULCATA_HANDLER_H
#include <netinet/in.h>
#include "message.h"
#include "rio.h"

namespace sulcata{
  
  class connection_handler{
    enum {CONNECTION_ERROR, FORMAT_ERROR, OK};

    public:
      static int parse_request_stream(rio_t* rt, http_request& req);
      static int serve(int fd, sockaddr_in *addr); 
  };
  
  class request_handler{
    public:
      static int handle(rio_t* rt, http_request& req);
  };
  
  class static_file_handler{
    public:
      static int handle(rio_t* rt, http_request& req, http_response& resp);
  };
  
  class cgi_file_handler{
    public:
      static int handle(rio_t *rt, http_request& req, http_response& resp);
  };

}//namespace ends.

#endif
