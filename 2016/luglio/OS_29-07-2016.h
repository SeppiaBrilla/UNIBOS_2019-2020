#include <stdio.h>
#include <sys/types.h>
#include <grp.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int is_regular_file(const char *path);

void printgroupdir(const char *dirp, const char *group);

int main(int argc, char const *argv[]);