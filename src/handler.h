#ifndef SULCATA_HANDLER_H
#define SULCATA_HANDLER_H
#include <netinet/in.h>
#include "message.h"
#include "rio.h"

namespace sulcata{
  //handler function type  
  typedef int (*handle_proc)(rio_t* rt, http_request& req, http_response& resp); 
  
  typedef struct{
    std::string suffix;
    std::string mime_type;
    handle_proc func;
  } handle_pair;

  class connection_handler{
    enum {CONNECTION_ERROR, FORMAT_ERROR, OK};
    static void parse_uri(std::string &uri, std::string& filename, std::string& args);
    static void get_file_extension(const std::string& filename, std::string &suffix);

    public:
      static int parse_request_stream(rio_t* rt, http_request& req);
      static int serve(int fd, sockaddr_in *addr); 
  };
  
  class request_handler{
    //Table which maps suffix to proper handler function.
    static std::map<std::string, handle_pair*> suffix2proc_;
    static void register_handlers(handle_pair* handlers);
    static void serve_404(rio_t* rt, http_response& resp);

    public:
      request_handler(handle_pair* handlers = NULL);
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
