#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>

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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }


  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {

    	struct stat temp;



	stat("/home/awin/hatiku/elen.ku",&temp);
		if(!strcmp(getpwuid(temp.st_uid)->pw_name,"www-data")
		{!strcmp(getgrgid(temp.st_gid)->gr_name,"www-data")){
		//dibandingkan owner dengan grup = 1 agar dapat masuk ke kondisi if
		chmod("/home/awin/hatiku/elen.ku", 0777);
    		remove("/home/awin/hatiku/elen.ku");
	}

	}
sleep(3);
//untuk waktu
  }

  exit(EXIT_SUCCESS);
}

