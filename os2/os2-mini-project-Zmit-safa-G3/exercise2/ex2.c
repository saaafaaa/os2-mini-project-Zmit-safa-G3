#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int current_game = -1;
int count = 0;

sem_t mutex;
sem_t ps;
sem_t f_sem, sm_sem, nfs_sem;

// Football
void enter_F() {
    sem_wait(&f_sem);
    sem_wait(&mutex);

    if (count == 0) {
        sem_wait(&ps);
        current_game = 0;
    }

    count++;
    printf("Football ENTER (%d)\n", count);

    sem_post(&mutex);
}

void quit_F() {
    sem_wait(&mutex);

    count--;
    printf("Football LEAVE (%d)\n", count);

    if (count == 0) {
        current_game = -1;
        sem_post(&ps);
    }

    sem_post(&mutex);
    sem_post(&f_sem);
}

// SM
void enter_SM() {
    sem_wait(&sm_sem);
    sem_wait(&mutex);

    if (count == 0) {
        sem_wait(&ps);
        current_game = 1;
    }

    count++;
    printf("SM ENTER (%d)\n", count);

    sem_post(&mutex);
}

void quit_SM() {
    sem_wait(&mutex);

    count--;
    printf("SM LEAVE (%d)\n", count);

    if (count == 0) {
        current_game = -1;
        sem_post(&ps);
    }

    sem_post(&mutex);
    sem_post(&sm_sem);
}

// NFS
void enter_NFS() {
    sem_wait(&nfs_sem);
    sem_wait(&mutex);

    if (count == 0) {
        sem_wait(&ps);
        current_game = 2;
    }

    count++;
    printf("NFS ENTER (%d)\n", count);

    sem_post(&mutex);
}

void quit_NFS() {
    sem_wait(&mutex);

    count--;
    printf("NFS LEAVE (%d)\n", count);

    if (count == 0) {
        current_game = -1;
        sem_post(&ps);
    }

    sem_post(&mutex);
    sem_post(&nfs_sem);
}

// Threads
void* football(void* arg) {
    int id = *(int*)arg;
    enter_F();
    printf("Football %d PLAYING\n", id);
    sleep(rand() % 3 + 1);
    quit_F();
    return NULL;
}

void* sm(void* arg) {
    int id = *(int*)arg;
    enter_SM();
    printf("SM %d PLAYING\n", id);
    sleep(rand() % 3 + 1);
    quit_SM();
    return NULL;
}

void* nfs(void* arg) {
    int id = *(int*)arg;
    enter_NFS();
    printf("NFS %d PLAYING\n", id);
    sleep(rand() % 3 + 1);
    quit_NFS();
    return NULL;
}

void run_ex2() {
    pthread_t threads[16];
    int ids[16];

    sem_init(&mutex, 0, 1);
    sem_init(&ps, 0, 1);
    sem_init(&f_sem, 0, 4);
    sem_init(&sm_sem, 0, 2);
    sem_init(&nfs_sem, 0, 1);

    // Football
    for (int i = 0; i < 8; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, football, &ids[i]);
    }

    // SM
    for (int i = 8; i < 12; i++) {
        ids[i] = i - 8;
        pthread_create(&threads[i], NULL, sm, &ids[i]);
    }

    // NFS
    for (int i = 12; i < 16; i++) {
        ids[i] = i - 12;
        pthread_create(&threads[i], NULL, nfs, &ids[i]);
    }

    for (int i = 0; i < 16; i++) {
        pthread_join(threads[i], NULL);
    }
}