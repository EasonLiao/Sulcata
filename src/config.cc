#include "config.h"

namespace sulcata{
  configuration* configuration::singleton_ = NULL;
  std::mutex configuration::mtx_;

  configuration::configuration(){}
  
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

