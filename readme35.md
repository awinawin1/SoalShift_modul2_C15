## no3 
Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
Gunakan fork dan exec.
Gunakan minimal 3 proses yang diakhiri dengan exec.
Gunakan pipe 
Pastikan file daftar.txt dapat diakses dari text editor

```
  int main() {
  pid_t child_id_satu, child_id_dua, child_id_tiga;
  
  int pipe_satu[2];
  int pipe_dua[2];
  //2 pipe yang menampung masing-masing2

  pipe(pipe_satu);
  pipe(pipe_dua);
  
```
 ->proses 1 -> unzip
```
  child_id_satu = fork();
  //melakukan forking
  
  if (child_id_satu < 0) 
    exit(EXIT_FAILURE);

  if (child_id_satu == 0) {
  //child
    
    char *argv[5] = {"unzip", "/home/awin/praktikum2/campur2.zip", "-d", "/home/awin/praktikum2/", NULL};
    execv("/usr/bin/unzip", argv);
    //mengunzip dari /home/awin/praktikum2/campur2.zip ke /home/awin/praktikum2/. Program tidak lanjut 
    sebelum selesai menjalankan program
  }
else {
 
        while(wait(NULL) > 0); // karena harus menunggu proses diatasnya selesai
```
proses 2 -> ls

```
  child_id_dua = fork();
  //melakukan forking

if (child_id_dua < 0) 
   exit(EXIT_FAILURE);

if (child_id_dua == 0) 
//childnya
{
//stdout = write
//stdin = read
        dup2(pipe_satu[1], STDOUT_FILENO); //agar output dari ls tidak keluar di luar, 
                                            maka di masukkan ke pipe yang write (1) 
        close(pipe_satu[1]);
        close(pipe_satu[0]);
        //pipe_satu diclose semua

        char *argv[4] = {"ls", "/home/awin/praktikum2/campur2", NULL};
        //perintah ls
        execvp("/bin/ls", argv);
}
```
```
else {

        while(wait(NULL) > 0);
```
->proses 3 -> grep
```
 child_id_tiga = fork();
 //melakukan forking

if(child_id_tiga < 0) 
   exit(EXIT_FAILURE);

if(child_id_tiga == 0) 
//childnya
{
        dup2(pipe_satu[0], STDIN_FILENO); //inputnya grep kan didapat dari proses sebelumnya, 
                                            lalu disimpan di pipe _satu yang read(0)
        dup2(pipe_dua[1], STDOUT_FILENO); //outputnya grep disimapn di pipe_dua yang write(1)
        close(pipe_dua[0]);
        close(pipe_dua[1]);
        close(pipe_satu[0]);
        close(pipe_satu[1]);
        //karena pipe 1 dan pipe2 digunakan maka, semua pipe di close

        char *argv[4] = {"grep", ".txt$", NULL};
        execvp("/bin/grep", argv);
}
```
```
else {
        //while(wait(NULL) > 0);

        char jawaban[255];
        close(pipe_dua[1]);
        close(pipe_satu[0]);
        close(pipe_satu[1]);
        read(pipe_dua[0], jawaban, sizeof(jawaban));

        FILE *filenya = fopen("/home/awin/praktikum2/daftar.txt", "w");
        fputs(jawaban, filenya);
        fclose(filenya);
      }
}
  }
        return 0;
}
```
## no5 
Kerjakan poin a dan b di bawah:
Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
Per menit memasukkan log#.log ke dalam folder tersebut
‘#’ : increment per menit. Mulai dari 1
Buatlah program c untuk menghentikan program di atas.

```

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
    // main program here
     //ambil waktu program sekarang
        time_t waktuwaktu;
        time(&waktuwaktu);

        struct tm *waktu;
        waktu = localtime(&waktuwaktu); //mengkonversi raw time di time_t biar jadi kepisah pisah hari, jam, bulan
        //1900 = 0 makanya + 1900 
        char fungsi_memisah[150]; //tm_sec dll didapat dari struct tm 
        sprintf(fungsi_memisah, "%d:%d:%d-%d:%d", waktu->tm_mday, waktu->tm_mon+1, waktu->tm_year+1900, waktu->tm_hour, waktu->tm_min); // untuk misah2 waktu disimpan di fungsi_memisah, cari struct tm
        //sprintf : nge print yang di print kemudian hasil print nya di simpan di yg kiri
	//sprintf mengubah interger ke string
        printf("%s", fungsi_memisah);
	char awin[255];
	sprintf(awin, "/home/awin/praktikum2/%s", fungsi_memisah); //letak dimana mkdir ini akan dibuat
        mkdir(awin, 0777); //777 biar bisa akses semua (rwx)

        int incr;
        for(incr=1; incr<30; incr++)
        {
                FILE *file_syslog; //membuat file baru untuk syslog
                FILE *file_ygdibuat; //membuat file baru yang akan dibuat
                file_syslog = fopen("/var/log/syslog", "r");
                char nama_filebaru[255];
                sprintf(nama_filebaru, "/home/awin/praktikum2/%s/log%d.log", fungsi_memisah, incr); //hasil print nya disimpan di nama_filebaru
                file_ygdibuat = fopen(nama_filebaru, "w");
		
		//pindah seluruh file ke log#.log
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
```

```
int main()
{
	int total_length = 10;
	char line[total_length];
	FILE * command = popen("pidof no5","r");

	fgets(line,total_length,command);

	pid_t pid = strtoul(line,NULL,10);
	kill(pid,SIGKILL);
	pclose(command);
}
```
