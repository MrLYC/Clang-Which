#include "cgenerator/src/gen.h"

typedef struct {
    int start;
    int end;
    char * envpath;
    GenState state;
} CommandPath;

typedef struct {
    char * name;
    char * full_path;
    bool find_all;
    CommandPath command_path;
    GenState state;
} Command;

#ifndef PATHSEP
#if defined(WIN32) || defined(_WIN32)
#define ENVPATHSEP ';'
#define PATHSEP '\\'
#else
#define ENVPATHSEP ':'
#define PATHSEP '/'
#endif
#endif

char * gen_find(Command *);
