#include <pthread.h>
#include <stdio.h>

constexpr auto NUM_THREADS = 5;

// 注意函数定义: void* (*)(void*)
void* PrintHello(void* threadid)
{
	int tid;
	tid = reinterpret_cast<int>(threadid);
	printf("Hello World! It's me, thread #%d!\n", tid);
	pthread_exit(NULL);
    return nullptr;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int rc, t;
    for (t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, reinterpret_cast<void*>(t));
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            return -1;
        }
    }

    pthread_exit(NULL);
    return 0;
}