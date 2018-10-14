#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

/* gcc pthread.c -lpthread */

int global_var = 10;

void *thread_fn(void *arg)
{

    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s-%d\n", __func__, __LINE__);

    printf("thread pid: %d; tid: %d\n", pid, tid);

    while(1) {
        sleep(1);
        printf("thread global_var : %d\n", global_var);
    }

}

int main()
{

    int err;
    pid_t pid;
    pthread_t tid;
    
    pid = getpid();
    printf("main pid: %d\n", pid);

    err = pthread_create(&tid, NULL, thread_fn, NULL);

    if (err != 0) {
        printf("pthread_create fail!\n");
    }

    sleep(10);
    global_var = 100;
    while(1);

    return 0;
}
