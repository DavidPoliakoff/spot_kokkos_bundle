#include <caliper/Caliper.h>
#include <adiak.hpp>
#include <iostream>

extern "C" void kokkosp_push_region();
extern "C" void kokkosp_pop_region();
__attribute__((constructor)) void prepare_list_globals(){
    adiak::user();
    adiak::launchdate();
    adiak::executablepath();
    adiak::libraries();
    adiak::cmdline();
    adiak::clustername();
    adiak::jobsize();
}
