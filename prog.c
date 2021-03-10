#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

struct thread_args
{
    int iNum;
    FILE *pFile;
    int iPeriod;
    pthread_mutex_t *Mutex;
};

void *thread_func(void *arg)
{   
    struct thread_args *th_args = (void*) arg;
    struct timeval start, current;
    for(int i = 0; i < 10; i++)
    {
        /*
        gettimeofday(&start, NULL);
        int usecStart = start.tv_sec*10000000 + start.tv_usec;
        gettimeofday(&current, NULL);
        int usecCur;

        do
        {
            gettimeofday(&current, NULL);
            usecCur = current.tv_sec*10000000 + current.tv_usec;

        } while( (usecCur - usecStart) < th_args->iPeriod);

        */
       
        sleep(th_args->iPeriod);
        pthread_mutex_lock(th_args->Mutex);
        fprintf( th_args->pFile,"I`m %d thread\n", th_args->iNum);
        printf("I`m %d thread\n", th_args->iNum);
        pthread_mutex_unlock(th_args->Mutex);

    }
}

int main()
{
    FILE *output = fopen("out.txt", "w");
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[3];

    struct thread_args args_arr[3];
    
    for(int i = 0; i < 3; i++)
    {
        args_arr[i].iNum = i + 1;
        args_arr[i].Mutex = &mutex;
        args_arr[i].pFile = output;
        args_arr[i].iPeriod = (i + 1);
    }

    

    for(int i = 0; i < 3; i++)
    {
        pthread_create(&threads[i], NULL, thread_func, &args_arr[i]);
    }

    for(int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    fclose(output);
    return 0;
}