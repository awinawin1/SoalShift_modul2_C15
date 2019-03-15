#include <sys/stat.h>
#include <sys/types.h>

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

int main() {
  pid_t pid, sid;
  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/awin/Documents/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);


  while(1) {

DIR *x;

    struct dirent *dir;

    x = opendir(".");

    if (x)
    {
        while ((dir = readdir(x)) != NULL)
//ketika di document ada file nya
        {
		int krktr = (int) strlen(dir->d_name);
	   	char temp[1000];
		char *name = dir->d_name;


	    if(strstr(dir->d_name,".png")!=NULL){
		//yang belakangnya .png

		strcpy(temp, "/home/awin/modul2/gambar/");
		strcat(temp, name);
		krktr = (int)strlen(temp);
		temp[krktr-4] = '\0';
		//menghilangkan  ekstensi dibelakang
		strcat(temp, "_grey.png");
		//menggabungkan _grey.png di belakang
		char *argv[] = {"mv", name, temp, NULL};
		//di move ke gambar
		execv("/bin/mv", argv);

		printf("%s\n", temp);
	    }
        }
        closedir(x); 

}
   
    sleep(10);
  }
  
  exit(EXIT_SUCCESS);
}


