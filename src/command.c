#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "command.h"


void gen_path_list(CommandPath * cp_ptr) {
    Gen_Begin(cp_ptr->state);

    cp_ptr->envpath = getenv("PATH");
    cp_ptr->start = cp_ptr->end = 0;

    while (cp_ptr->envpath[cp_ptr->start]) {
        const char * envpath = cp_ptr->envpath;
        while (envpath[cp_ptr->end] && envpath[cp_ptr->end] != ENVPATHSEP) {
            cp_ptr->end += 1;
        }

        Gen_Yield();
        if (cp_ptr->envpath[cp_ptr->end]) {
            cp_ptr->start = cp_ptr->end = cp_ptr->end + 1;
        }
        else {
            break;
        }
    }
    Gen_Finish();
}


char * get_command_path(char path[], int path_len, char command[]) {
    int command_len = strlen(command);
    char * full_path = malloc(path_len + command_len + 2);
    memcpy(full_path, path, path_len);

    if (full_path[path_len] != PATHSEP) {
        full_path[path_len++] = PATHSEP;
    }
    full_path[path_len] = '\0';

    memcpy(full_path + path_len, command, command_len + 1);
    return full_path;
}


bool is_executable(char path[]) {
    // TODO: check is executable
    FILE *fp;
    if ((fp = fopen(path, "r"))) {
        fclose(fp);
        return true;
    }
    return false;
}


char * gen_find(Command * c_ptr) {
    Gen_Begin(c_ptr->state);

    Gen_Init(c_ptr->command_path.state);

    while (!(c_ptr->command_path.state.finished)) {
        gen_path_list(&(c_ptr->command_path));
        if (c_ptr->command_path.state.finished) {
            break;
        }

        c_ptr->full_path = get_command_path(
            c_ptr->command_path.envpath + c_ptr->command_path.start,
            c_ptr->command_path.end - c_ptr->command_path.start,
            c_ptr->name
        );

        if (is_executable(c_ptr->full_path)) {
            Gen_Yield(c_ptr->full_path);

            if (!(c_ptr->find_all)) {
                free(c_ptr->full_path);
                c_ptr->full_path = NULL;
                break;
            }
        }
        free(c_ptr->full_path);
        c_ptr->full_path = NULL;
    }
    Gen_Finish(NULL);
}
