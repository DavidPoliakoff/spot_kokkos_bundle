#include <caliper/Caliper.h>
#include <adiak.hpp>
#include <iostream>

extern "C" void kokkosp_push_region(const char*);
extern "C" void kokkosp_pop_region();
extern "C" void kokkosp_declare_metadata(const char* key, const char* value){
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
