#ifndef SULCATA_CONFIG_H
#define SULCATA_CONFIG_H

#include <string>
#include <map>
#include <iostream>
#include <mutex>
#include <list>

namespace sulcata{
  
  //This structure holds the configuration for each host.
  typedef struct{
    //Path of docroots for this host
    std::string docroot; 
    //Return one of these files when the path is a directory
    std::list<std::string> default_files; 
  } host_configuration;

  //This class holds the configuration for whole server.
  class configuration{
    protected:
      //This is the default configuration if the 
      //host can't be found in the defined host table.
      host_configuration default_config_; 
      
      //map between host name to host config structure.
      std::map<std::string, host_configuration*> config_table_; 
      
      //Singleton object.
      static configuration* singleton_;
      static std::mutex mtx_;

    public:
      host_configuration& default_config(){ return default_config_; }
      configuration();
      ~configuration();
      static configuration* instance();
  };
  
}//namespace ends

#endif
