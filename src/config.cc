#include "config.h"

namespace sulcata{
  configuration* configuration::singleton_ = NULL;
  std::mutex configuration::mtx_;

  configuration::configuration(){
    default_config_.docroot = "../html/";
    default_config_.default_files.push_back("index.html");
    default_config_.default_files.push_back("index.htm");
    default_config_.default_files.push_back("home.html");
    default_config_.default_files.push_back("home.htm");
    default_config_.default_files.push_back("index.cgi");
  }
  
  configuration::~configuration(){   
  }

  configuration* configuration::instance(){

    if(singleton_ == NULL){
      std::lock_guard<std::mutex> lock(mtx_);

      if(singleton_ == NULL)
        singleton_ = new configuration(); 
    }

    return singleton_;
  }

}//namespace ends

