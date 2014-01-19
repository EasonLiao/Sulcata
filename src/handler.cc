#include "handler.h"
#include <unistd.h>
#include <iostream>
#include "message.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "config.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sstream>

#define LINESIZE 4096

namespace sulcata{
  
  static handle_pair pairs[] = {  {"html",  "text/html",  static_file_handler::handle},
                                  {"htm",   "text/html",  static_file_handler::handle},
                                  {"jpg",   "image/jpeg", static_file_handler::handle},
                                  {"gif",   "image/gif",  static_file_handler::handle},
                                  {"py",    "",           cgi_file_handler::handle},
                                  {"pl",    "",           cgi_file_handler::handle},
                                  {"",      "",           NULL}
                                }; 

  std::map<std::string, handle_pair*> request_handler::suffix2proc_;
  request_handler g_init(pairs); 

  int connection_handler::serve(int fd, sockaddr_in* addr){
    rio_t rt;
    rio_readinitb(&rt, fd);
    http_request req;

    while(parse_request_stream(&rt, req) == OK){
      int ret = request_handler::handle(&rt, req);
      
      if(ret < 0)
        break;
    }
    
    std::cout<<"end!!"<<std::endl;
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
  
  request_handler::request_handler(handle_pair* handlers){
    register_handlers(handlers);
  }

  void request_handler::register_handlers(handle_pair* handlers){
    if(handlers == 0)
      return;
   
    while(1){
      if(handlers->func == 0)
        break;  
      
      suffix2proc_[handlers->suffix] = handlers;
      handlers++;
    }
  }
  
  void request_handler::parse_uri(std::string& uri,
                                  std::string& filename,
                                  std::string& args){
    if(uri[0] == '/')
      uri = uri.substr(1, uri.size() - 1);

    size_t pos = uri.find('?');
    
    if(pos != std::string::npos){
      args = uri.substr(pos + 1, uri.size() - pos);
      filename = uri.substr(0, pos);
    }else{
      args = ""; 
      filename = uri;
    }
  }

  void request_handler::get_file_extension(const std::string& filename,
                                            std::string& suffix){
    size_t pos = filename.find('.');
    if(pos == std::string::npos){
      suffix = "";
      return;
    }
    suffix = filename.substr(pos + 1, filename.size() - pos);
  }

  int request_handler::handle(rio_t *rt, http_request& req){ 
    http_response resp;
    resp.headers().set("Server", "Sulcate");
    resp.set_http_ver("HTTP/1.1");

    std::string filename, args, suffix, filepath;
  
    parse_uri(req.get_path(), filename, args);
    get_file_extension(filename, suffix); 
    
    req.set_filename(filename);
    req.set_args(args);
    
    filepath = configuration::instance()->default_config().docroot + filename; 
    req.set_filepath(filepath);

    struct stat sbuf;
    if(stat(filepath.c_str(), &sbuf) < 0){
      std::cerr<<"can't find file 404"<<filepath<<std::endl;
      return -1;
    }
    
    req.set_stat(&sbuf);

    std::map<std::string, handle_pair*>::iterator iter = suffix2proc_.find(suffix);

    if(iter == suffix2proc_.end())
      return -1; 
    
    resp.set_mime_type(iter->second->mime_type);
    handle_proc proc = iter->second->func;
    proc(rt, req, resp); 
    
    return 0;
  }
  
  int static_file_handler::handle(rio_t* rt, http_request& req, http_response &resp){
    uint64_t filesize = req.get_stat()->st_size;
    std::stringstream ss;
    std::string content;
    ss << filesize;

    resp.set_status_code(200);
    resp.set_status_description("OK");
    resp.headers().set("Content-type", resp.get_mime_type()); 
    resp.headers().set("Content-length", ss.str()); 
    
    ss.clear();
    ss << resp;
    content = ss.str(); 
    rio_writen(rt, content.c_str(), content.size());
    
    int srcfd = open(req.get_filepath().c_str(), O_RDONLY, 0);
    char* srcp;
    srcp = (char*)mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    close(srcfd);
    
    rio_writen(rt, srcp, filesize);
    munmap(srcp, filesize);

    return 0;
  }
  
  int cgi_file_handler::handle(rio_t* rt, http_request& req, http_response &resp){
    std::cout<<"cgi handle"<<std::endl; 
    return 0;
  }

}//namespace ends.
