KELOMPOK C-15
Nama: Muhammad Iqbal    (05111440000095)
      Risky Aswi Narni  (05111740000014)
      
## soal no1
Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

while(1) {

   ```struct stat temp;```
   
   -> declarasi struct stat temp
   
	```stat("/home/awin/hatiku/elen.ku",&temp);```
  
  -> menggunakan struct stat yang nanti disimpan di variable temp, dalam stat terdapat informasi dari owner dan group
  
		```if(!strcmp(getpwuid(temp.st_uid)->pw_name,"www-data")
		{!strcmp(getgrgid(temp.st_gid)->gr_name,"www-data")){```
    
  -> membandingkan owner dengan groupnya dan akan berjalan dengan syarat "www-data", strcmp ketika sama adalah 0, 
  kami buat !stcrmp agar if dapat berjalan karena if akan berjalan ketika kondisinya 1
		
		```chmod("/home/awin/hatiku/elen.ku", 0777);```
    
   ->mengubah permissionnya menjadi 777. chmod: Perintah ini digunakan untuk mengganti permission dari sebuah file/folder. Pada dasarnya, setiap file dapat diakses oleh 3 jenis pengguna yaitu owner, group, others
    
   ```remove("/home/awin/hatiku/elen.ku");```
	```}
	   }```
 
  ->meremove / menghapus yang ada di direktori hatiku/elen.ku
  
  ``sleep(3);
  }``
  ->sleep sebagai pengganti crontab, program berjalan 3 detik sekali
