#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define SEM_KEY 5555

int main()
{
    int shmid, semid;
    int *addr;
    int h, w;
    float result, sum;

    struct sembuf sem1_opt_wait[1]   = {0, -1, SEM_UNDO};   /* -1 means I need a  resource */
    struct sembuf sem2_opt_wakeup[1] = {1, 1,  SEM_UNDO};   /*  1 means I release resource */

    /* 1. wait sem1 */
    /* 2. access share memory */
    /* 3. wakeup sem2 */
    while(1) {
        /* get share memory */
        shmid = shmget(0x1234, getpagesize(), S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        sleep(1);

        printf("%s-%d\n", __func__, __LINE__);

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
        printf("%s-%d\n", __func__, __LINE__);
        /* attach share memory */
        addr = shmat(shmid,0,0);

        printf("%s-%d\n", __func__, __LINE__);

        w = *(addr + 1);
        h = *addr;
        sum = h * h / 10000;
        result = w / sum;

        semop(semid, sem1_opt_wait, 1);

        printf("%s-%d %d\n", __func__, __LINE__, result);

        printf("%s-%d %d\n", __func__, __LINE__, result);

        if(result > 25) {
            printf("big\n");
            printf("%s-%d\n", __func__, __LINE__);
            *(addr + 2) = 0;
        } else if(result < 20) {
            printf("small\n");
            printf("%s-%d\n", __func__, __LINE__);
            *(addr+2) = 0;

        } else {

            printf("%s-%d %d\n", __func__, __LINE__, result);
            printf("%s-%d %d\n", __func__, __LINE__, result);
            if(result > 5 && result < 20) {
                printf("normal\n");
                *(addr+2) = 0;
            }
        }

        /* detach the share memory */
        shmdt(addr);

        semop(semid, sem2_opt_wakeup, 1);

        printf("%s-%d\n", __func__, __LINE__);

        sleep(2);
    }
}
