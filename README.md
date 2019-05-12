# FP_SISOP19_C16

Buatlah program C yang menyerupai crontab menggunakan daemon dan thread. Ada sebuah file crontab.data untuk menyimpan config dari crontab. Setiap ada perubahan file tersebut maka secara otomatis program menjalankan config yang sesuai dengan perubahan tersebut tanpa perlu diberhentikan. Config hanya sebatas * dan 0-9 (tidak perlu /,- dan yang lainnya)

Jawab :

- Untuk membaca file `crontab.data ` , maka kami menggunakan sintaks dibawah ini :
```
	    FILE *file;
	    file = fopen("crontab.data", "r"); 
	    
	    if (file==NULL)
	    {
	        perror("Cannot open the file.\n");
	        exit(EXIT_FAILURE);
	    }
```
- Sintaks dibawah ini berfungsi untuk membaca karakter satu per satu lalu dimasukkan ke dalam array. Array untuk eksekusi waktu dan perintah/command dibedakan.
```
	    while( (karakter = fgetc(file)) != EOF)
	    {
	        if(spasi<5)
	        {
	            if(karakter == ' ') spasi++;
	            
	            timer[j][i] = karakter;
	            i++;
	            
	            if(spasi == 5)
	            {
	                timer[j][i] = '\0';
	                i = 0;
	            }
	        }
	        else
	        {
	             if(karakter =='\n') //sudah mencapai enter
	            {
	                command[j][i] = '\0';
	                j++; // naik ke crontab selanjutnya
	                spasi = 0;
	                i = 0;
	            }
	            else
	            {
	                command[j][i] = karakter;
	                i++;
	            }
	        }
	    }
        
	    command[j][i]='\0';
```
- Cacah tiap command dalam crontab menjadi atomik.
```
	    for(k=0;k<j;k++)
	    {
	        time( &timez );
	
		    utuh = localtime( &timez );
		    m = utuh->tm_min;
                    jm = utuh->tm_hour;
                    d = utuh->tm_mday;
                    mo = utuh->tm_mon + 1;
                    nh = utuh->tm_wday ;

		    	sprintf(menit, "%02d", m);
			sprintf(jam, "%02d", jm ); 
 			sprintf(day, "%02d", d); 
			sprintf(mon, "%02d", mo ); 
			sprintf(namahari, "%02d", nh); 
```
- Sintaks dibawah berfungsi untuk memeriksa apabila input tiap command subcron adalah bagian dari crontabnya (subcron = 0 untuk menit, subcron = 1 untuk jam, dst).
```
for(int c=0 ; c<l_char_timer ; c++)
			{
	    		if(timer[k][c] == ' ')
	    		{
	        		subcron++; // pindah ke subcron selanjutnya
	    		}
	    		else if(subcron == 0) //bagian menit
	    		{
	    			memset(temp, 0, sizeof(temp));
	    			
			        if(timer[k][c]=='*')
			        {
			            tag++;
			        }
			        else
			        {
			            if(timer[k][c+1]==' ') // yang ini dibuat just in case inputannya itu 1 digit. misal jam 8 itukan 08, tp dinput 8 aja
			            {
			                temp[0] = '0';
			                temp[1] = timer[k][c];
			                temp[2] = '\0';
			            }
			            else // ini kalo inputannya 2 digit
			            {
			            	temp[0] = timer[k][c]; 
			                temp[1] = timer[k][c+1];
			                temp[2] = '\0';
			                c++;
			            }
			
				        if(strcmp(menit,temp)==0){
				        	tag++;
						} 
				//		printf("nums 0 = %d\n", tag);
			        }
	    		}
	    		else if(subcron == 1) //bagian jam
	    		{
	    			memset(temp, 0, sizeof(temp));
	    			
			        if(timer[k][c]=='*')
			        {
			            tag++;
			        }
			        else
			        {
			            if(timer[k][c+1]==' ') // yang ini dibuat just in case inputannya itu 1 digit. misal jam 8 itukan 08, tp dinput 8 aja
			            {
			                temp[0] = '0';
			                temp[1] = timer[k][c];
			                temp[2] = '\0';
			            }
			            else // ini kalo inputannya 2 digit
			            {
			            	temp[0] = timer[k][c]; 
			                temp[1] = timer[k][c+1];
			                temp[2] = '\0';
			                c++;
			            }
			
				        if(strcmp(jam,temp)==0){
				        	tag++;
						} 
				//		printf("nums 1 = %d\n", tag);
			        }
	    		}
				else if(subcron == 2) //bagian hari
	    		{
	    			memset(temp, 0, sizeof(temp));
	    			
			        if(timer[k][c]=='*')
			        {
			            tag++;
			        }
			        else
			        {
			            if(timer[k][c+1]==' ') // yang ini dibuat just in case inputannya itu 1 digit. misal jam 8 itukan 08, tp dinput 8 aja
			            {
			                temp[0] = '0';
			                temp[1] = timer[k][c];
			                temp[2] = '\0';
			            }
			            else // ini kalo inputannya 2 digit
			            {
			            	temp[0] = timer[k][c]; 
			                temp[1] = timer[k][c+1];
			                temp[2] = '\0';
			                c++;
			            }
			
				        if(strcmp(day,temp)==0){
				        	tag++;
						} 
				//		printf("nums 2 = %d\n", tag);
			        }
	    		}
				else if(subcron == 3) //bagian bulan
	    		{
	    			memset(temp, 0, sizeof(temp));
	    			
			        if(timer[k][c]=='*')
			        {
			            tag++;
			        }
			        else
			        {
			            if(timer[k][c+1]==' ') // yang ini dibuat just in case inputannya itu 1 digit. misal jam 8 itukan 08, tp dinput 8 aja
			            {
			                temp[0] = '0';
			                temp[1] = timer[k][c];
			                temp[2] = '\0';
			            }
			            else // ini kalo inputannya 2 digit
			            {
			            	temp[0] = timer[k][c]; 
			                temp[1] = timer[k][c+1];
			                temp[2] = '\0';
			                c++;
			            }
			
				        if(strcmp(mon,temp)==0){
				        	tag++;
						} 
				//		printf("nums 3 = %d\n", tag);
			        }
	    		}
	    		else if(subcron == 4) //bagian nama hari
	    		{
	    			memset(temp, 0, sizeof(temp));
	    			
			        if(timer[k][c]=='*')
			        {
			            tag++;
			        }
			        else
			        {
			            if(timer[k][c+1]==' ') // yang ini dibuat just in case inputannya itu 1 digit. misal jam 8 itukan 08, tp dinput 8 aja
			            {
			                temp[0] = '0';
			                temp[1] = timer[k][c];
			                temp[2] = '\0';
			            }
			            else // ini kalo inputannya 2 digit
			            {
			            	temp[0] = timer[k][c]; 
			                temp[1] = timer[k][c+1];
			                temp[2] = '\0';
			                c++;
			            }
			
				        if(strcmp(namahari,temp)==0){
				        	tag++;
						} 
				//		printf("nums 4 = %d\n", tag);
			        }
	    		}
			    else
			    {
			        break;
			    }   
			}
```
- Tiap-tiap `else if` pada subcron berfungsi untuk mengambil variabel angka dari array timer (yang berisi waktu).
```
          else if(subcron == 0) //bagian menit
	    		{
	    			memset(temp, 0, sizeof(temp));
	    			
			        if(timer[k][c]=='*')
			        {
			            tag++;
			        }
			        else
			        {
			            if(timer[k][c+1]==' ') // yang ini dibuat just in case inputannya itu 1 digit. misal jam 8 itukan 08, tp dinput 8 aja
			            {
			                temp[0] = '0';
			                temp[1] = timer[k][c];
			                temp[2] = '\0';
			            }
			            else // ini kalo inputannya 2 digit
			            {
			            	temp[0] = timer[k][c]; 
			                temp[1] = timer[k][c+1];
			                temp[2] = '\0';
			                c++;
			            }
			
				        if(strcmp(menit,temp)==0){
				        	tag++;
						} 
				//		printf("nums 0 = %d\n", tag);
			        }
	    		}
```
- Lalu, tiap-tiap elemen subcron akan melalui pengecekan lewat perbandingan antar tiap elemen dengan waktu asli.
```
            if(strcmp(menit,temp)==0){
				        	tag++;
						} 
```
- Jika command tersebut berjalan, maka akan ter-print seperti dibawah ini :
```
	    if(tag >= 5)
	    {
	        printf("Executing command: %s\n",command[k]);
	        system(command[k]);
	    }   
	      sleep(1);
		
	      tag=0;
```
- Thread dibuat di dalam daemon.
```
	while(1) {

	    int i=0;
		int err;
		while(i<1) 
		{
			err=pthread_create(&(tid[i]),NULL,&config ,NULL); //buat thread
			if(err!=0) 
			{

			}
			else
			{
				printf("\n create thread success\n");
			}
			i++;
		}
		pthread_join(tid[0],NULL);
		exit(0);


	    sleep(30);
	  }
```  
