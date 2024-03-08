#include "header.h"

void f(int i, sem_t *lock)
{
	struct timeval tv;

	printf("ana dkhlt %d\n", i);
	// if (i == 1)
	// 	sleep(10);
	sem_wait(lock);
	sem_wait(lock);
	sem_wait(lock);
	printf("i am P number %d\n", i);
	gettimeofday(&tv, 0);
	printf("time: %ld\n", tv.tv_sec);
	sem_post(lock);
	sem_post(lock);
	printf("i am done bn8 %d\n", i);
}


int main() {
	int i = 0;
    int pid[2];
	sem_t *lock;

	lock = sem_open("/lock", O_CREAT, 0644, 2);
	while (i < 2)
	{
		pid[i] = fork();
		if (!pid[i])
		{
			f(i, lock);
			exit(0);
		}
		i++;
	}
	waitpid(pid[0], 0, 0);
	waitpid(pid[1], 0, 0);
	sem_unlink("/lock");
	sem_close(lock);
    return 0;
}