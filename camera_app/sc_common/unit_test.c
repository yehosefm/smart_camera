#include <stdio.h>

#include "sc_logger.h"
#include "sc_paths.h"


int main(){
    LOGGER_LOG(L_INFO, "first");
    //logger_log(L_INFO, "fdfdsal");
    printf("%s", paths_get_external_path());
}


