// CPU Benchmarking
// Calculating FLOPS & IOPS
// By Snehal Sonawane(A20360111)

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#define BYTE 1
#define KILOBYTE 1024
#define MEGABYTE 1024*1024
#define MAX_BYTE 10000000
#define MAX_KB 100000
#define MAX_MB 10


double latency; 

char * bufferData;

//Read Kilo Byte Block Size Sequentially
void *readKiloByteSequential()
{
	FILE *myfile;
	int i;
	myfile = fopen("Test.txt", "r+");// open file
	fseek(myfile, 0, SEEK_SET);// sets the pointer to beginning of file
    	for(i=0;i<MAX_KB;i++)
    	{
		fread(bufferData,1,KILOBYTE,myfile);// reads 
    	}
    	fclose(myfile);// close file
}

//Write Kilo Byte Block Size Sequentially 
void *writeKiloByteSequential(){	
	double cpu_time_used;
	int i;
	FILE *myfile;
	myfile=fopen("Test.txt","a+");// open file
	fseek(myfile,0,SEEK_SET);// sets the pointer to beginning of file		
	for ( i=0;i<MAX_KB; i++)
	{
		fwrite(bufferData, 1, KILOBYTE, myfile);// write 	
	}
	fclose(myfile);// close file
}

//Write Byte Block Size Sequentially 
void *writeToFile(){
	int i;
	char c='c';
	FILE *myfile;
	myfile=fopen("Test.txt","w+");// open file
		
	for ( i=0;i<MAX_BYTE; i++)
	{
		fputc(c,myfile);// writes one charater
	}
	fclose(myfile);// close file
}

//Read Byte Block Size Sequentially 
void *readToFile(){
	int i;	
	FILE *myfile;
	myfile=fopen("Test.txt","r+");// open file
	fseek(myfile,0,SEEK_SET);// sets the pointer to beginning of file
	for ( i=0; i<MAX_BYTE; i++)
	{
		fread(bufferData,1,BYTE,myfile);// read
	}
	fclose(myfile);// close file		
}

//Write Byte Block Size Randomly
void *writeRandomsToFile(){
	int i,s;
	char c='c';	
	double cpu_time_used;
	FILE *myfile;
	myfile=fopen("TestRandom.txt","wb");// open file
	for ( i=0; i<MAX_BYTE; i++)
	{
		s=rand()%3000;
		fseek(myfile,s,SEEK_SET);// sets the pointer to sth point of file
		fputc(c,myfile); //writes one character
	}
	fclose(myfile);	// close file	
}

//Read Byte Block Size Randomly
void *readRandomsToFile(){
	int i,s;
	char buffer[1024*1024];		
	FILE *myfile;
	myfile=fopen("TestRandom.txt","r+");// open file
	for ( i=0; i<MAX_BYTE; i++)
	{
		s=rand()%3000;
		fseek(myfile,s,SEEK_SET);// sets the pointer to beginning of file
		fread(buffer,1,BYTE,myfile);// read
	}
	fclose(myfile);// close file
}

//Write Kilo Byte Block Size Randomly
void *writeKiloByteRandom()
{
	FILE *myfile;
	int i,j;
	myfile = fopen("file.txt", "w+");// open file
    	for(i=0;i<MAX_KB;i++)
    	{
    		int r=rand()%KILOBYTE;
	    	fseek(myfile,r,SEEK_SET); // sets the pointer to beginning of file
    		fwrite(bufferData, 1, KILOBYTE, myfile);// write 
    	}
    	fclose(myfile);// close file
}

//Write Mega Byte Block Size Sequentially
void *writeMegaByteSequential()
{
	FILE *myfile;
	int i,j;
	myfile = fopen("Test.txt", "w+");// open file
    	for(i=0;i<MAX_MB;i++)
    	{
    		fwrite(bufferData, 1, MEGABYTE, myfile);// write 
    	}
    	fclose(myfile);// close file
}

//Read Mega Byte Block Size Randomly
void *readMegaByteRandom()
{
	FILE *myfile;
	int i;
	myfile = fopen("Test.txt", "r+");// open file
    	for(i=0;i<MAX_MB;i++)
    	{
    		int r=rand()%MEGABYTE;
	    	fseek(myfile,r,SEEK_SET); // sets the pointer to rth point of file
    		fread(bufferData, 1,MEGABYTE, myfile);// read
    	}
    	fclose(myfile);// close file
}

//Read Kilo Byte Block Size Randomly
void *readKiloByteRandom()
{
	FILE *myfile;
	int i;
	myfile = fopen("Test.txt", "r+");// open file
    	for(i=0;i<MAX_KB;i++)
    	{
    		int r=rand()%KILOBYTE;
	    	fseek(myfile,r,SEEK_SET); // sets the pointer to rth point of file
    		fread(bufferData,1, KILOBYTE,myfile);// read
    	}
    	fclose(myfile);// close file
}

//Write Mega Byte Block Size Sequentially
void *readMegaByteSequential()
{
	FILE *myfile;
	int i;
	myfile = fopen("Test.txt", "r+");// open file
    	for(i=0;i<MAX_MB;i++)
    	{
    		fread(bufferData, 1,MEGABYTE, myfile);// read
    	}
    	fclose(myfile);// close file
}

//Write Mega Byte Block Size Randomly
void *writeMegaByteRandom()
{
	FILE *myfile;
	int i,j;
	myfile = fopen("file.txt", "w+");// open file
    	for(i=0;i<MAX_MB;i++)
    	{
    		int r=rand()%MEGABYTE;
	    	fseek(myfile,r,SEEK_SET); // sets the pointer to rth point of file
    		fwrite(bufferData, 1, MEGABYTE, myfile);// write 
    	}
    	fclose(myfile);// close file
}

int main(){
	 //menu driven program
	int ch, nthread, i,k;
	bufferData= (char *)malloc(1024*1024);// allocating memory 
	clock_t start, end; 
	double time;
	double l, l1, throughput;
	double total_mb;
	for(k=0;k<(1024*1024);k++)// Buffer data should contain character S
	{
		bufferData[k]='S';
	}
	pthread_t th[4];
		//Select the Block Size to carry out  
		printf("..Disk Benchmarking...\n");
		printf("..Block Size...\n");
		printf("1.Byte\n");
		printf("2.Kilo Byte\n");
		printf("3.Mega Byte\n");
		printf("4.EXIT\n");
		printf("\nEnter your choice :");
		scanf("%d",&ch);
		
		switch(ch){
			case 1: printf("\n\nBlock size selected is Byte");
					printf("\n\nEnter the number of threads(1/2) :\n");
					scanf("%d",&nthread);
					start=clock();
					for(i=0;i<nthread;i++)
						{
							pthread_create(&th[i],NULL,writeToFile,NULL);//creates threads
							pthread_join(th[i], NULL);// joins threads
						}
					end=clock();
					time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken 
					total_mb=(nthread * MAX_BYTE * BYTE)/1000000;
					throughput=total_mb/time;// Calulating throughput
					printf("\n\nSEQUENTIAL WRITE");
					printf("\nThroughtput:%f MB/s",throughput);					
					l= (time)*1000/total_mb;// Calculating latency
					printf("\nLatency : %f ms",l);
			
    					start=clock();
					for(i=0;i<nthread;i++)
						{
							pthread_create(&th[i],NULL,readToFile,NULL);//creates threads
							pthread_join(th[i], NULL);// joins threads
						}
					end=clock();
					time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken 
					total_mb=(nthread * BYTE * MAX_BYTE)/1000000;
					throughput=total_mb/time;// Calulating throughput
					printf("\n\nSEQUENTIAL READ");
					printf("\nThroughtput:%f MB/s",throughput);
					l1= (time)*1000/total_mb;// Calculating latency
					printf("\nLatency : %f ms",l1);
					
					start=clock();
					for(i=0;i<nthread;i++)
						{
							pthread_create(&th[i],NULL,writeRandomsToFile,NULL);//creates threads
							pthread_join(th[i], NULL);// joins threads
						}
					end=clock();
					time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken 
					total_mb=(nthread * BYTE * MAX_BYTE)/1000000;
					throughput=total_mb/time;// Calulating throughput
					printf("\n\nRANDOM WRITE");
					printf("\nThroughtput:%f MB/s",throughput);
					l= (time)*1000/total_mb;// Calculating latency
					printf("\nLatency : %f ms",l);
					
					start=clock();
					for(i=0;i<nthread;i++)
						{
							pthread_create(&th[i],NULL,readRandomsToFile,NULL);//creates threads
							pthread_join(th[i], NULL);// joins threads
						}
					end=clock();
					time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken 
					total_mb=(nthread * BYTE * MAX_BYTE)/1000000;
					throughput=total_mb/time;// Calulating throughput
					printf("\n\nRANDOM READ");
					printf("\nThroughtput:%f MB/s",throughput);
					l1= (time)*1000/total_mb;// Calculating latency
					printf("\nLatency : %f ms",l1);
					
						break;	
			
		case 2: printf("\n\nBlock size selected is KILOBYTE");

					printf("\n\nEnter the number of threads(1/2) :\n");
					scanf("%d",&nthread);
					start=clock();
					for(i=0;i<nthread;i++)
						{
							pthread_create(&th[i],NULL,writeKiloByteSequential,NULL);//creates threads
							pthread_join(th[i], NULL);// joins threads
						}
					end=clock();
					time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken 
					
					total_mb=(nthread * KILOBYTE * MAX_KB)/1000000;
					throughput=total_mb/time;// Calulating throughput
					printf("\n\nSEQUENTIAL WRITE 1KB");
					printf("\nThroughtput:%f MB/s",throughput);
					l= (time)*1000/total_mb;// Calculating latency
					printf("\nLatency : %f ms",l);
			
    					start=clock();
					for(i=0;i<nthread;i++)
						{
							pthread_create(&th[i],NULL,readKiloByteSequential,NULL);//creates threads
							pthread_join(th[i], NULL);// joins threads
						}
					end=clock();
					time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken 					
					total_mb=(nthread * KILOBYTE * MAX_KB)/1000000;
					throughput=total_mb/time;// Calulating throughput
					printf("\n\nSEQUENTIAL READ");
					printf("\nThroughtput:%f MB/s",throughput);
					l1= (time)*1000/total_mb;// Calculating latency
					printf("\nLatency : %f ms",l1);
					start=clock();
					for(i=0;i<nthread;i++)
						{
							pthread_create(&th[i],NULL,writeKiloByteRandom,NULL);//creates threads
							pthread_join(th[i], NULL);// joins threads
						}
					end=clock();
					total_mb=(nthread * KILOBYTE * MAX_KB)/1000000;
					time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken 
					
					printf("\n\nRANDOM WRITE 1KB");
					throughput=total_mb/time;// Calulating throughput
					printf("\nThroughtput:%f MB/s",throughput);
					l= (time*1000)/total_mb;// Calculating latency
					printf("\nLatency : %f ms",l);
					
					start=clock();
					for(i=0;i<nthread;i++)
						{
							pthread_create(&th[i],NULL,readKiloByteRandom,NULL);//creates threads
							pthread_join(th[i], NULL);// joins threads
						}
					end=clock();
					total_mb=(nthread * KILOBYTE * MAX_KB)/1000000;
					time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken 
					l1= (time*1000)/total_mb;// Calculating latency
					printf("\n\nRANDOM READ");
					throughput=total_mb/time;// Calulating throughput
					printf("\nThroughtput:%f MB/s",throughput);
					printf("\nLatency : %f ms",l1);
						break;	
		case 3: printf("\n\nBlock size selected is MEGABYTE");
					printf("\n\nEnter the number of threads(1/2) :\n");
					scanf("%d",&nthread);
					start=clock();
					for(i=0;i<nthread;i++)
						{
							pthread_create(&th[i],NULL,writeMegaByteSequential,NULL);//creates threads
							pthread_join(th[i], NULL);
						}
					end=clock();
					total_mb=(nthread * MEGABYTE * MAX_MB)/1000000;
					time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken 
					l= (time*1000)/total_mb;// Calculating latency
					printf("\n\nSEQUENTIAL WRITE 1MB");
					
					throughput=total_mb/time;// Calulating throughput
					printf("\nThroughtput:%f MB/s",throughput);
					printf("\nLatency : %f ms",l);
					start=clock();
					for(i=0;i<nthread;i++)
						{
							pthread_create(&th[i],NULL,readMegaByteSequential,NULL);//creates threads
							pthread_join(th[i], NULL);
						}
					end=clock();
					total_mb=(nthread * MEGABYTE * MAX_MB)/1000000;
					time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken 
					l1= (time*1000)/total_mb;// Calculating latency
					printf("\n\nSEQUENTIAL READ");
					throughput=total_mb/time;// Calulating throughput
					printf("\nThroughtput:%f MB/s",throughput);
					printf("\nLatency : %f ms",l1);
					start=clock();
					for(i=0;i<nthread;i++)
						{
							pthread_create(&th[i],NULL,writeMegaByteRandom,NULL);//creates threads
							pthread_join(th[i], NULL);
						}
					end=clock();
					total_mb=(nthread * MEGABYTE * MAX_MB)/1000000;
					time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken 
					l= (time*1000)/total_mb;// Calculating latency
					printf("\n\nRANDOM WRITE 1MB");
					throughput=total_mb/time;// Calulating throughput
					printf("\nThroughtput:%f MB/s",throughput);
					printf("\nLatency : %f ms",l);
					start=clock();
					for(i=0;i<nthread;i++)
						{
							pthread_create(&th[i],NULL,readMegaByteRandom,NULL);//creates threads
							pthread_join(th[i], NULL);
						}
					end=clock();
					total_mb=(nthread * MEGABYTE * MAX_MB)/1000000;
					time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken 
					l= (time*1000)/total_mb;// Calculating latency
					printf("\n\nRANDOM READ 1MB");
					throughput=total_mb/time;// Calulating throughput
					printf("\nThroughtput:%f MB/s",throughput);
					printf("\nLatency : %f ms",l);
				
						break;	
		case 4: break;
		}
	
}
