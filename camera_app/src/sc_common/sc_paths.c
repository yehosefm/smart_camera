#include <unistd.h>
#include <limits.h>
#include <linux/limits.h>
#include <string.h>

#include "sc_paths.h"
#include "sc_logger.h"

#define ROOT_NAME "smart_camera"
#define EXTERNAL_DIR_NAME "external/"

const char *paths_get_project_root(){
    static char project_root[PATH_MAX];
    char * pos;
    if(project_root[0] != 0) {
        return project_root;
    }
    if (getcwd(project_root, sizeof(project_root)) == NULL) {
        LOGGER_LOG(L__WARN, "getcwd failed %s", project_root);
        return NULL;
    }
    if(NULL == (pos = strstr(project_root,ROOT_NAME))) {
        LOGGER_LOG(L__WARN, "substring not founding: %s", project_root);
        return NULL;
    }
    pos[sizeof(ROOT_NAME)] = '\0';
    return project_root;
}


const char *paths_get_external_path(){
    static char external_path[PATH_MAX];
    char  *pos;
    char const *project_root;
    int i;

    if(external_path[0] != 0){
        return external_path;
    }
    project_root = paths_get_project_root();
    if(project_root == NULL){
        LOGGER_LOG(L_ERROR, "can't got project root path");
        return NULL;
    }
    pos = external_path;
    while(*project_root != '\0') {
        *pos++ = *project_root++; 
    }
    strncpy(pos, EXTERNAL_DIR_NAME, sizeof(EXTERNAL_DIR_NAME));
    return external_path;
}