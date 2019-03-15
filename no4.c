#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

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

if ((chdir("/home")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

int urutan = 1;

strcpy(path,"/home/awin/Documents/makanan/makan_enak.txt");

while(1) {
    char path[500];
    struct stat x;

    stat(path, &x);

	time_t makanan; //file
	makanan = x.st_atime;
	
	time_t jalan;//program
	jalan = time(NULL);

	double syarat = difftime(jalan, makanan);

        if(syarat < 31)
        {
		FILE *open;
                char x_temp[100];

		char x_temp2[100];
		int ke=1;

                strcpy(x_temp,"/home/awin/Documents/makanan/makan_sehat");

                sprintf(x_temp2, "%d.txt", ke);

                strcat(x_temp, x_temp2);

                open = fopen(x_temp, "w");
                fclose(open);

                ke=ke+1;
        }

    	sleep(5);
	}

	exit(EXIT_SUCCESS);
