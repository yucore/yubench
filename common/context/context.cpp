#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int func() {
	int dummy = 0, times = 1024*1024*128;
	for (int i = 0; i < times; i++) {
		dummy = dummy + i;
		dummy = dummy * i;
	}
	return dummy;
}

int main(int argc, char* argv[]) {
	pid_t pid[10240];

	struct timeval t0, t1, tcost;
	struct timezone tzp;
	gettimeofday(&t0, &tzp);

	if (argc != 2) {
		printf("usage: ./context [num of threads]\n");
		return 1;
	}else {
		int n = atoi(argv[1]);
		int is_root = 1;
		for (int i = 0; i < n; i++) {
		  pid[i] = fork();
			if (pid[i] == 0) { // child
				is_root = 0;
				break;
			}
		}

		// cost time
		int r = func();

		if (is_root) {
			wait(NULL);
			gettimeofday(&t1, &tzp);
			if (t0.tv_usec > t1.tv_usec) {
				t1.tv_usec += 1000000;
				t1.tv_sec--;
			}
			tcost.tv_usec = t1.tv_usec - t0.tv_usec;
			tcost.tv_sec = t1.tv_sec - t0.tv_sec; 
			printf("cost time %.10f\n", tcost.tv_sec + 0.000001 * tcost.tv_usec);
		}
		return (r & 1);
	}
}
