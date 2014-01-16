#ifndef SULCATA_CONFIG_H
#define SULCATA_CONFIG_H

#include <string>
#include <map>
#include <iostream>
#include <mutex>

namespace sulcata{
  
  //This structure holds the configuration for each host.
  typedef struct{
    std::string docroot; /*Path of docroots for this host*/

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
      configuration();
      ~configuration();
      static configuration* instance();
  };
  
}//namespace ends

#endif
