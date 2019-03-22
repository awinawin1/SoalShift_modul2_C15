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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    
        time_t waktuwaktu;
        time(&waktuwaktu);

        struct tm *waktu;
        waktu = localtime(&waktuwaktu); 
        char fungsi_memisah[150];
        sprintf(fungsi_memisah, "%d:%d:%d-%d:%d", waktu->tm_mday, waktu->tm_mon+1, waktu->tm_year+1900, waktu->tm_hour, waktu->tm_min);
        printf("%s", fungsi_memisah);
	char awin[255];
	sprintf(awin, "/home/awin/praktikum2/%s", fungsi_memisah); 
        mkdir(awin, 0777);

        int incr;
        for(incr=1; incr<30; incr++)
        {
                FILE *file_syslog; 
                FILE *file_ygdibuat; 
                file_syslog = fopen("/var/log/syslog", "r");
                char nama_filebaru[255];
                sprintf(nama_filebaru, "/home/awin/praktikum2/%s/log%d.log", fungsi_memisah, incr);   
file_ygdibuat = fopen(nama_filebaru, "w");
		
                char karakter; 
                while(fscanf(file_syslog, "%c", &karakter) != EOF)
                {
                        fprintf(file_ygdibuat, "%c", karakter);
                }
                fclose(file_syslog);
                fclose(file_ygdibuat);
                sleep(2);
        }

  }
  
  exit(EXIT_SUCCESS);
}
