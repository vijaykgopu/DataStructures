#include <stdio.h>
#include <pthread.h>

int count = 0;

pthread_mutex_t lock;
pthread_cond_t cond;

void * thread_function (void *thread_count) {
    int val = * (int *)thread_count;
    
    while(count <= 20){
        pthread_mutex_lock(&lock);
        
        if(count % 2 != val){
            pthread_cond_wait(&cond, &lock);
        }else {
            printf("Printing count = %d from thread %ld\n", count, pthread_self());
            count++;
            pthread_cond_signal(&cond);
        }
        
        pthread_mutex_unlock(&lock);
    }
    
    pthread_exit(thread_count);
}

int main(){
    pthread_t tid[2];
    int val[2] = {0, 1};
    
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    
    pthread_create(&tid[0], NULL, thread_function, &val[0]);
    pthread_create(&tid[1], NULL, thread_function, &val[1]);

    void *ret[2];
    pthread_join(tid[0], &ret[0]);
    pthread_join(tid[1], &ret[1]);
    
    printf("Return value from thread %ld is %d\n", tid[0], * (int *) ret[0]);
    printf("Return value from thread %ld is %d\n", tid[1], * (int *) ret[1]);
    
    return 0;
}
