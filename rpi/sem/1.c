/*
 * filename:shm
 *
 */
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<fcntl.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#define SEM_KEY1 5555
union semun
{
    int setval;
    struct semid_ds *buf;
    short *array;
};

int main()
{
    int shmid,semid;
    int *addr;
    int h = 0, w = 0;
    int ret;
    union semun sem_args;
    unsigned short array[2] = {1, 1};

    sem_args.array = array;

    /* create share memory */
    shmid = shmget(ftok("/etc/passwd",1001), getpagesize(), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if(shmid == -1) {
        perror("shmget error:");
        exit(EXIT_FAILURE);
    }

    /* create semaphore */
    semid = semget(SEM_KEY1, 2, IPC_CREAT|0600);
    if(semid == -1) {
        perror("semget error:");
        exit(EXIT_FAILURE);
    }

    ret = semctl(semid , 1, SETALL, sem_args);
    if(ret == -1) {
        perror("shmctl error:");
        exit(EXIT_FAILURE);
    }

    struct sembuf sem1_opt_wakeup[1] ={0,  1, SEM_UNDO};
    struct sembuf sem2_opt_wait[1]   ={1, -1, SEM_UNDO};

    while(1)
    {
        int i = 0;

        semop(semid, sem2_opt_wait, 1);

        addr = shmat(shmid, 0, 0);

        printf("please input your information:\n");

        scanf("%d%d", addr, addr+1);

        shmdt(addr);

        semop(semid, sem1_opt_wakeup, 1);

        printf("exit please enter 1");

        scanf("%d", &i);

        if(i == 1) {
            shmctl(shmid, IPC_RMID, NULL);
            semctl(semid, IPC_RMID, NULL);
            exit(1);
        }
    }
    return 0;
}
