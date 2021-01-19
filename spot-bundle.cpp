#include <caliper/Caliper.h>
#include <adiak.hpp>
#include <iostream>

extern "C" void kokkosp_push_region(const char*);
extern "C" void kokkosp_pop_region();
extern "C" void kokkosp_declare_metadata(const char* key, const char* value){
  std::string parseme(value);
  try {
    size_t end;
    float v = std::stof(parseme,&end);
    adiak::value(key, v);
    return;
  }
  catch(std::invalid_argument){
  }
  try {
    size_t end;
    int i = std::stoi(parseme,&end);
    adiak::value(key, i);
    return;
  }
  catch(std::invalid_argument){
  }
  adiak::value(key,value);
}
__attribute__((constructor)) void prepare_list_globals(){
    adiak::user();
    adiak::launchdate();
    adiak::executablepath();
    adiak::libraries();
    adiak::cmdline();
    adiak::clustername();
    adiak::jobsize();
}
