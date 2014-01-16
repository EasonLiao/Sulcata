#ifndef SULCATA_MESSAGE_H
#define SULCATA_MESSAGE_H 
#include <iostream>
#include <map>
#include <string>

namespace sulcata{
 
  class http_headers{
    friend class http_message; 
    protected:
      std::map<const std::string, std::string> header_table_;
    
    public:
      void set(const std::string& key, const std::string& value){
        header_table_[key] = value;
      }
      
      bool get(const std::string& key, std::string& value){
        std::map<const std::string, std::string>::iterator iter;
        iter = header_table_.find(key);
        if(iter == header_table_.end())
          return false;
        
        value = iter->second;
        return true;
      }
      
      friend std::ostream& operator<<(std::ostream& os, http_headers& hdr){
        std::map<const std::string, std::string>::iterator iter; 
        for(iter = hdr.header_table_.begin(); iter != hdr.header_table_.end(); ++iter)
          os << iter->first<<": "<<iter->second;

        os<<std::endl;
        return os;
      }
  };

  class http_message{
    protected:
      http_headers headers_;
      std::string body_;

    public:
      http_headers& headers() { return headers_; } 
  };

  class http_request : public http_message{
    protected:
      std::string method_;
      std::string path_;
      std::string http_ver_;
    
    public:
      void set_method(const std::string& method){ method_ = method; }
      std::string& get_method() { return method_; }
      
      void set_path(const std::string& path){ path_ = path; }
      std::string& get_path(){ return path_; }

      void set_http_ver(const std::string& ver){ http_ver_ = ver; }
      std::string& get_http_ver() { return http_ver_; }
    
      friend std::ostream& operator<<(std::ostream& os, http_request& req){
        os<<req.method_<<" "<<req.path_<<" "<<req.http_ver_<<std::endl;
        os<<req.headers_;
        os<<req.body_; 
      }
  };

  class http_response : public http_message{
    protected:
      unsigned int status_;
      std::string description_;
  };

}//end namespace.

#endif
