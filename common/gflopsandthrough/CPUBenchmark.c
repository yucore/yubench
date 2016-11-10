// CPU Benchmarking
// Calculating FLOPS & IOPS
// By Snehal Sonawane(A20360111)

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

#define ITERATION 1000000000

struct arg_struct {		
	int thread_id;
};

double b[4];
double c[4];

//thread function for multiple operations
void *threadFunctionIopsCal(void *arg)
{
	volatile int i;
	int a=5;
	for(i = 0; i < ITERATION; i++)
    	{
        	a =0.5+2+3+5+6+3+1+1+7+5+1+2+2+3+6+8+1+2+9+1+6+1+9;
    	}
	return NULL;
}

//thread function for multiple operations
void *threadFunctionFlopCal(void *arg)
{
	volatile int i;
	double a;
	for(i = 0; i < ITERATION; i++)
    	{
        	a =0.5+2+3+5+6+3+1+1+7+5+1+2+2+3+6+8+1+2+9+1+6+1+9;
    	}
	return NULL;
}

// thread function to calculate Flops
void *threadFunctionFlop(void *arg)
{
	int index= *(int *)arg;
	double a;
	while(1)
    	{
		a =0.5+2+3+5+6+3+1+1+7+5+1+2+2+3+6+8+1+2+9+1+6+1+9;
		b[index]=b[index]+23;
	}
	return NULL;
}

// thread function to calculate Iops
void *threadFunctionIops(void *arg)
{
	int index= *(int *)arg;
	int a;
	while(1)
    	{
		a =0.5+2+3+5+6+3+1+1+7+5+1+2+2+3+6+8+1+2+9+1+6+1+9;	
		c[index]=c[index]+23;//calculating the number of instructions
	}
	
	return NULL;
}

//Calulates the GIOPS
void *iopsCal(int numberOfThreads)
{
	volatile int i;
	int a;
	clock_t start, end;
	struct arg_struct args;
	pthread_t th[10];// array of threads
	double cpu_time_used, time_in_sec;
	start = clock();
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_create(&th[i],NULL,threadFunctionIopsCal,(void *)&args);//creates a thread 
		pthread_join(th[i], NULL);// joins threads if the concurrency is 2/4
	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;//Clock records the time taken to perform the task
	printf("\nTime taken in: %f seconds\n",cpu_time_used);
	double count=23;
	double Iops=(double)( numberOfThreads * count *(ITERATION/cpu_time_used));//calculating iops
    	double gIops=(double)Iops/1000000000;//converting iops to GIOPS
	printf("GIOPS : %f\n",gIops);
	return NULL;
}

//Calculates 600 GFLOPS per second and stores in CPU_Log.txt 
void flops(int numberOfThreads)
{	
	FILE *fp;
	fp= fopen("CPU_Log.txt","a+");
	int i=0;
    	pthread_t th[10];// array of threads
	struct arg_struct args;
  	int a[4];
	for(i=0;i<4;i++)
	{
		b[i]=0;
		a[i]=i;
	}
	printf("\nProgram to find 600 samples for GFLOPS %d threads",numberOfThreads);
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_create(&th[i],NULL,threadFunctionFlop,&a[i]);//creates a thread 
	}
	for(i=0;i<600;i++)
	{
		sleep(1);
		fprintf(fp,"%lf\n",((double)(b[0]+b[1]+b[2]+b[3]))/1000000000); //Printing instructions per second
		b[0]=b[1]=b[2]=b[3]=0;
	}
	fclose(fp);
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_kill(&th[i],1);//kills the thread
	}
	printf("600 Samples Experiment for GFLOPS Done");
}

//calculates the GFLOPS 
void flopsCal(int numberOfThreads)
{	
	clock_t start, end;
	double cpu_time_used;
	volatile int i;
    	struct arg_struct args;
    	pthread_t th[10];// array of threads
	printf("\nProgram to find GFLOPS for %d threads",numberOfThreads);
	start = clock();
	for(i=0;i<numberOfThreads;i++)
	{		
		pthread_create(&th[i],NULL,threadFunctionFlopCal,(void *)&args);//Creates a thread
		pthread_join(th[i], NULL);// joins threads if the concurrency is 2/4
	}
    	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	double count=23;	
    	printf("\nTime: %f sec\n",cpu_time_used);
    	double Flops=(double)( numberOfThreads * count *(ITERATION/cpu_time_used));//calculating flops
    	double gFlops=(double)Flops/1000000000;//Converting flops to gflops
    	printf("GFLOPS : %lf\n",gFlops);
}

//Calculates 600 GIOPS per second and stores in CPU_IOPS.txt
void iops(int numberOfThreads)
{
	
	FILE *fp;
	fp= fopen("CPU_IOPS.txt","a+");	
	int i=0;
	struct arg_struct args;
    	pthread_t th[10];// array of threads
	int a[4];
	for(i=0;i<4;i++)
	{
		c[i]=0;
		a[i]=i;
	}
	printf("\nProgram to find IOPS for %d threads",numberOfThreads);
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_create(&th[i],NULL,threadFunctionIops,&a[i]);//Creates a thread
	}
	for(i=0;i<600;i++)
	{
		sleep(1);
		fprintf(fp,"%lf\n",((double)(c[0]+c[1]+c[2]+c[3]))/1000000000);//Printing instructions per second
		c[0]=c[1]=c[2]=c[3]=0;
	}
	fclose(fp);
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_kill(&th[i],1);// kills the threads
	}
	printf("600 Samples Experiment for GIOPS Done");
}


int main()
{       //menu driven program
	while(1){	
	int numberOfThreads;

		printf("\nEnter the no of threads:(1/2/4) /(Enter 8 for 600 Samples /Exit-0: ");
		scanf("%d",&numberOfThreads);	
		// Enter 1/2/3 threads for GFLOPS/GIOPS 
		// Incase to get 600 samples for GFLOPS/GIOPS Enter 8 
		// To exit press 0
		if(numberOfThreads!=1 && numberOfThreads!=2 && numberOfThreads!=4 && numberOfThreads!=0 && numberOfThreads!=8)
		{
			printf("\nInvalid choice..Please enter again");
			
		}
		else if(numberOfThreads==8)
		{
			flops(4);
    			iops(4);
		}
		else if(numberOfThreads==0)
		{
			exit(0);
		}
		else 
		{
			flopsCal(numberOfThreads);
    			iopsCal(numberOfThreads);
		}	
    	}
    	return 0;
}
