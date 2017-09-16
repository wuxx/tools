#include<sys/types.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#define SEM_KEY 5555

int main()
{
    int shmid, semid;
    int *addr;
    int h, w;
    float result, sum;
    struct sembuf sem1_opt_wait[1]={0,-1,SEM_UNDO};
    struct sembuf sem2_opt_wakeup[1]={1,1,SEM_UNDO};

    while(1) {
        /* get share memory */
        shmid = shmget(ftok("/etc/passwd",1001), getpagesize(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        sleep(1);

        if(shmid == -1) {
            perror("shmget error:");
            exit(EXIT_FAILURE);
        }

        /* get the semaphore set */
        semid = semget(SEM_KEY, 2, 0600);
        if(semid == -1) {
            perror("semget error:");
            exit(EXIT_FAILURE);
        }

        /* attach share memory */
        addr = shmat(shmid,0,0);

        w = *(addr + 1);
        h = *addr;
        sum = h * h / 10000;
        result = w / sum;

        semop(semid, sem1_opt_wait, 1);

        if(result > 25) {
            printf("big\n");
            *(addr + 2) = 0;
        } else if(result < 20) {
            printf("small\n");
            *(addr+2) = 0;

        } else {

            if(result > 5 && result < 20) {
                printf("normal\n");
                *(addr+2) = 0;
            }
        }

        /* detach the share memory */
        shmdt(addr);

        semop(semid, sem2_opt_wakeup, 1);
        sleep(2);
    }
}
