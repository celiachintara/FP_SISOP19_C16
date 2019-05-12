#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/types.h>
#include<string.h>
#include<pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/stat.h>
#include <syslog.h>

pthread_t tid[10]; 

void* config(void *arg)
{
    while(1)
    {	
    	char karakter;
		char command[10][100];
    	char timer[10][100];

		//baca file
	    FILE *file;
	    file = fopen("crontab.data", "r"); 
	    
	    if (file==NULL)
	    {
	        perror("Cannot open the file.\n");
	        exit(EXIT_FAILURE);
	    }

	    int i=0,j=0; // j ini nanti menandakan perpindahan perintah crontab -------- i nandain urutan karakter
		int spasi=0; //jumlah spasi dalam timer wajib ada 5
		
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
	    
	    //jangan lupa tutup filenyaa!
	    fclose(file);
	
		//EKSEKUSI
	    int k;
	    char temp[10];
	    int subcron = 0;
		int tag = 0;
	    
	    time_t timez;
		struct tm *utuh;
		int m,jm,d,mo,nh;
		char menit[3]; //00-59
		char jam[3]; // 00-23
		char day[3]; // 1-31
		char mon[3]; // 0-11
		char namahari[3]; //sunday = 0, monday = 1 dst saturday = 6
	
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
	
	    	int l_char_timer = strlen(timer[k]);

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
	    printf(".\n");
	    if(tag >= 5)
	    {
	        printf("Executing command: %s\n",command[k]);
	        system(command[k]);
	    }   
	      sleep(1);
		
	      tag=0;
	    }
	    }
}



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

  if ((chdir("/home/celiachintara/SISOP/fp/")) < 0) {
    exit(EXIT_FAILURE);
  }


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
  
  exit(EXIT_SUCCESS);
}


