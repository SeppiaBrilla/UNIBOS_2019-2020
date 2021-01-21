#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <printgroupdir.h>

void printgroupdir(const char *dirpath, const char *groupname){
	gid_t gid = -1;
	struct group *grp;
	DIR *dir = opendir(dirpath);
	struct dirent *mydir;

	while(grp = getgrent()){
		if(strcmp(grp->gr_name, groupname) == 0){
			gid = grp->gr_gid;
			break;
		}
	}
	if(gid == -1){
		printf("Could not find user group.\n");
		exit(1);
	}
	while(mydir = readdir(dir)){
		if(mydir->d_type != DT_DIR){
			struct stat st;
			char buf[64];
			sprintf(buf, "%s/%s", dirpath, mydir->d_name);
			if(lstat(buf, &st) == -1)
				perror("lstat");
			if(st.st_gid == gid)
				printf("%s\n", mydir->d_name);
		}
	}
}
