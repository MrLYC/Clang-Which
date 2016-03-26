#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

const int SUCCESSNO = 0;
const int SYSERRNO = -1;
const int USRERRNO = 1;
const int OPTFINISHED = -1;

typedef struct {
    bool option_all;
    bool option_help;
    char * filename;
} Argument;


bool parse_command_line(Argument * arg_ptr, int argc, char * const argv[]) {
    int option;

    arg_ptr->option_all = false;
    arg_ptr->option_help = false;
    arg_ptr->filename = NULL;

    while ((option = getopt(argc, argv, "ah")) != OPTFINISHED) {
        switch (option) {
            case 'a':
                arg_ptr->option_all = true;
                break;
            case 'h':
                arg_ptr->option_help = true;
                break;
            default:
                return false;
        }
    }

    if (optind >= argc) {
        return false;
    }

    arg_ptr->filename = argv[optind];

    if (strlen(arg_ptr->filename) == 0) {
        return false;
    }

    return true;
}


void print_usage() {
    printf("which - locate a command\n");

    printf("\npositional arguments:\n");
    printf("\tfilename\n");

    printf("\noptional arguments:\n");
    printf("\t-h  show this help message and exit\n");
    printf("\t-a  print all matching pathnames of each argument\n");
}


int main(int argc, char * const argv[]) {
    Argument arg = {false, false, NULL};
    if (!parse_command_line(&arg, argc, argv)) {
        print_usage();
        return USRERRNO;
    }
    else if (arg.option_help) {
        print_usage();
        return SUCCESSNO;
    }

    Command command;
    command.name = arg.filename;
    command.find_all = arg.option_all;

    char * command_path = NULL;
    Gen_Init(command.state);
    while (!(command.state.finished)) {
        command_path = gen_find(&command);
        if (!(command.state.finished)) {
            printf("%s\n", command_path);
        }
    }

    return SUCCESSNO;
}
