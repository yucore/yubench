#include<stdio.h>
#include<sys/time.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

#define BLOCK_SIZE 1
#define BLOCK_SIZE_KB 1024
#define BLOCK_SIZE_MB 1024*1024
#define MAX_BYTE 1000000
#define MAX_KB 100000
#define MAX_MB 100

void *block_Byte();
void *block_Kbyte();
void *block_Mbyte();
void *block_Byte_random();
void *block_KByte_random();
void *block_MByte_random();

//Sequential Read & Write for 1 Byte
void *block_Byte()
{
int i;
char *mem = (char *)malloc(MAX_BYTE);//allocating memory 		
char *mem1 =(char *)malloc(MAX_BYTE);//allocating memory
	for(i=0;i<MAX_BYTE;i++)
		{
		memcpy(mem1, mem, BLOCK_SIZE);// copy content from source to destination
		mem1=mem1+BLOCK_SIZE;
		mem=mem+BLOCK_SIZE;
		}

}

//Random Read & Write for 1 Byte
void *block_Byte_random()
{
	int i,r;	
	char *mem = (char *)malloc(MAX_BYTE);//allocating memory	
	char *mem1 =(char *)malloc(MAX_BYTE);//allocating memory
		
	for(i=0;i<MAX_BYTE;i++)
	{
		r = rand()%((BLOCK_SIZE*MAX_BYTE)-BLOCK_SIZE);	
		memcpy(&mem1[r],&mem[r],BLOCK_SIZE);// copy content from source to destination randomly
	}
}

//Sequential Read & Write for 1 KB
void *block_Kbyte()
{
	int i;
	char *mem = (char *)malloc(MAX_KB*BLOCK_SIZE_KB);//allocating memory	
	char *mem1 =(char *)malloc(BLOCK_SIZE_KB*MAX_KB);//allocating memory
	for(i=0;i<MAX_KB;i++)
	{
	memcpy(mem1, mem, BLOCK_SIZE_KB);// copy content from source to destination randomly
	mem1=mem1+BLOCK_SIZE_KB;
	mem=mem+BLOCK_SIZE_KB;
	}
}

//Random Read & Write for 1 KB
void *block_KByte_random()
{
	int i,r;
	char *mem = malloc(MAX_KB*BLOCK_SIZE_KB);//allocating memory
	char *mem1= malloc(BLOCK_SIZE_KB*MAX_KB);//allocating memory
		
	for(i=0;i<MAX_KB;i++)
	{
		r = (rand()%(MAX_KB*BLOCK_SIZE_KB)-BLOCK_SIZE_KB);	
		memcpy(&mem1[r],&mem[r],BLOCK_SIZE_KB);	//copy content from source to destination 
	}
}

//Sequential Read & Write for 1 MB
void *block_Mbyte()
{
	int i;
	char *mem = malloc(MAX_MB*BLOCK_SIZE_MB);//allocating memory
	char *mem1= malloc(BLOCK_SIZE_MB*MAX_MB);//allocating memory
		
	for(i=0;i<MAX_MB;i++)
	{
		memcpy(mem1, mem, BLOCK_SIZE_MB);//copy content from source to destination 
		mem1=mem1+BLOCK_SIZE_MB;
		mem=mem+BLOCK_SIZE_MB;
	}
}

//Random Read & Write for 1 MB
void *block_MByte_random()
{	
	int i,r;
	char *mem = malloc(BLOCK_SIZE_MB*MAX_MB);//allocating memory	
	char *mem1=malloc(BLOCK_SIZE_MB*MAX_MB);//allocating memory

	for(i=0;i<MAX_MB;i++)
	{
		r = rand()%MAX_MB;	
		memcpy(&mem1[r],&mem[r],BLOCK_SIZE_MB);//copy content from source to destination
	}
}

int main()
{
	//Menu driven program
	clock_t start, end;
	double latency,throughput,total_mb;
	double time;
	pthread_t th[10];// array of threads
	int i;
	int ch,nthread;
	while(1)
	{// Select the block size to read write sequentially and randomly
		printf(".. Memory Benchmarking..");
		printf("\n\nEnter the Block Size:\n1.BYTE\n2.KILOBYTE\n3.MEGABYTE\n4.Exit\n");
		scanf("%d",&ch);
		if(ch==4)
		{
			exit(0);
		}
		printf("\nEnter the number of threads(1/2) :\n");
		scanf("%d",&nthread);
		switch (ch)
		{
			case 1: 
			//Sequential Read & Write
			printf("\nByte read+write for %d thread",nthread);
			printf("\n..Sequential Read+Write..\n");
			printf("-------------------------------------");
			start = clock();
			for(i=0;i<nthread;i++)
			{	
				pthread_create(&th[i],NULL,block_Byte,NULL);//creates a thread 
				pthread_join(th[i], NULL); //joins the threads
			}
			
			end=clock();
			total_mb=(nthread * BLOCK_SIZE * MAX_BYTE)/1000000;// Calulating the total 
			time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken
			latency= (time*1000)/total_mb;// calculating latency
    			printf("\nLatency : %f ms",latency);
    			throughput=total_mb/time;// calculating throughput
    			printf("\nThroughtput:%f MB/s",throughput);
			
			// Random Memroy Read+Write
			
			printf("\n\n..Random read+write..\n");
			printf("-------------------------------------");
			start=clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Byte_random,NULL);//creates a thread
				pthread_join(th[i], NULL);//joins the threads
			}
			end=clock();
			total_mb=(nthread * BLOCK_SIZE * MAX_BYTE)/1000000;
			time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken
			latency= (time*1000)/total_mb;// calculating latency
    			printf("\nLatency : %f ms",latency);
    			throughput=total_mb/time;// calculating throughput
    			printf("\nThroughtput:%f MB/s",throughput);
			break;
			
			case 2: 
			//Sequential Memroy Read+Write for KILOBYTE block
			
			printf("\n\nKiloByte read+write for %d thread ",nthread);//creates a thread
			printf("\n..Sequential Read+Write..\n");
			printf("-------------------------------------");
			start = clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Kbyte,NULL);//creates the threads
				pthread_join(th[i], NULL);//joins the threads
			}
			end=clock();
			total_mb=(nthread * BLOCK_SIZE_KB * MAX_KB)/1000000;
			time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken
			latency= (time*1000)/total_mb;// calculating latency
    			printf("\nLatency : %f ms",latency);
    			throughput=total_mb/time;// calculating throughput
    			printf("\nThroughtput:%f MB/s",throughput);
			
	
			//Random Memroy Read+Write for KILOBYTE block
			
			printf("\n\n..Random read+write..\n");
			printf("-------------------------------------");
			start= clock();
			for(i=0;i<nthread;i++)
			{

				pthread_create(&th[i],NULL,block_KByte_random,NULL);//creates a thread
				pthread_join(th[i], NULL);//joins the threads
			}
			end=clock();
			total_mb=(nthread * BLOCK_SIZE_KB * MAX_KB)/1000000;
			time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken
			latency= (time*1000)/total_mb;// calculating latency
    			printf("\nLatency : %f ms",latency);
    			throughput=total_mb/time;// calculating throughput
    			printf("\nThroughtput:%f MB/s",throughput);
			break;

			case 3: 
			
			//Sequential Memroy Read+Write
			
			printf("\nMegaByte read+write for %d thread",nthread);
			printf("\n..Sequential Read+Write..\n");
			printf("-------------------------------------");
			start = clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_Mbyte,NULL);//creates a thread
				pthread_join(th[i], NULL);//joins the threads
			}
			
			end=clock();
			total_mb=(nthread * BLOCK_SIZE_MB * MAX_MB)/1000000;
			time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken
			latency= (time*1000)/total_mb;// calculating latency
    			printf("\nLatency : %f ms",latency);
    			throughput=total_mb/time;// calculating throughput
    			printf("\nThroughtput:%f MB/s",throughput);			
			
			
			//Random Memory Read+Write
			
			printf("\n\n..Random read+write..\n");
			printf("-------------------------------------");
			start = clock();
			for(i=0;i<nthread;i++)
			{
				pthread_create(&th[i],NULL,block_MByte_random,NULL);//creates a thread
				pthread_join(th[i], NULL);//joins the threads
			}
			end=clock();
			total_mb=(nthread * BLOCK_SIZE_MB * MAX_MB)/1000000;
			time=((double) (end-start))/ CLOCKS_PER_SEC;// calculating time taken
			latency= (time*1000)/total_mb;// calculating latency
    			printf("\nLatency : %f ms",latency);
    			throughput=total_mb/time;// calculating throughput
    			printf("\nThroughtput:%f MB/s",throughput);				
			
			break;

			case 4: exit(0);
			break;
			default:printf("\nPlease enter a valid option..\n");	
		}
	}
}


