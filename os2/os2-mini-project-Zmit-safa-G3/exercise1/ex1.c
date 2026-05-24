#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* football_ex1(void* arg) {
    int id = *(int*)arg;
    printf("Football %d is waiting\n", id);
    sleep(rand() % 3 + 1);
    printf("Football %d is done\n", id);
    return NULL;
}

void* sm_ex1(void* arg) {
    int id = *(int*)arg;
    printf("SM %d is waiting\n", id);
    sleep(rand() % 3 + 1);
    printf("SM %d is done\n", id);
    return NULL;
}

void* nfs_ex1(void* arg) {
    int id = *(int*)arg;
    printf("NFS %d is waiting\n", id);
    sleep(rand() % 3 + 1);
    printf("NFS %d is done\n", id);
    return NULL;
}

void run_ex1() {
    pthread_t threads[16];
    int ids[16];

    // Football
    for (int i = 0; i < 8; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, football_ex1, &ids[i]);
    }

    // SM
    for (int i = 8; i < 12; i++) {
        ids[i] = i - 8;
        pthread_create(&threads[i], NULL, sm_ex1, &ids[i]);
    }

    // NFS
    for (int i = 12; i < 16; i++) {
        ids[i] = i - 12;
        pthread_create(&threads[i], NULL, nfs_ex1, &ids[i]);
    }

    for (int i = 0; i < 16; i++) {
        pthread_join(threads[i], NULL);
    }
}