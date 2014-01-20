#include "template.h"
#include "sulcata_const.h"

namespace sulcata{
  using std::string;

  std::string error_page(const std::string& title,
                          const std::string& header){
    
    return string("<html><head><title>") + title + string("</title></head>")
            + string("<body bgcolor=\"white\"><center><h1>") + header
            + string("</h1></center><hr><center>") + SULCATA_VERSION 
            + string("</center></body></html>");
  }
}//namespace ends
