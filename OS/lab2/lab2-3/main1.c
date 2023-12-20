#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>


#define CNT 5

typedef struct {
    pthread_t* philosophers;
    pthread_mutex_t* forks;
    int id;
} philosopher_data;

void* run_philosopher(void* data) {
    philosopher_data ph_data = *((philosopher_data*) data);
    int ph_id = ph_data.id;
    pthread_mutex_t* fork_l = &ph_data.forks[ph_id];
    pthread_mutex_t* fork_r = &ph_data.forks[(ph_id + 1) % CNT];

    while (1) {
        printf("Философ %d размышляет\n", ph_id);
        pthread_mutex_lock(fork_l);
        printf("Философ %d берёт левую вилку (-%d)\n", ph_id, ph_id);
        pthread_mutex_lock(fork_r);
        printf("Философ %d берёт правую вилку (-%d)\n", ph_id, (ph_id + 1) % CNT);
        printf("Философ %d ест\n", ph_id);
        printf("Философ %d кладёт левую вилку (+%d)\n", ph_id, ph_id);
        printf("Философ %d кладёт правую вилку (+%d)\n", ph_id, (ph_id + 1) % CNT);
        pthread_mutex_unlock(fork_l);
        pthread_mutex_unlock(fork_r);
    }
    return NULL;
}

int main() {
    philosopher_data philosophers_info[CNT];
    pthread_t philosophers[CNT];
    pthread_mutex_t forks[CNT];

    // mutex threads initialization
    for (int i = 0; i < CNT; ++i) {
        pthread_mutex_init(&forks[i], NULL);
    }
    for (int i = 0; i < CNT; ++i) {
        philosophers_info[i].id = i;
        philosophers_info[i].philosophers = philosophers;
        philosophers_info[i].forks = forks;
        pthread_create(&philosophers[i], NULL, run_philosopher, (void*) &(philosophers_info[i]));
    }
    // wait until all philosophers eat
    for (int i = 0; i < CNT; ++i) {
        pthread_join(philosophers[i], NULL);
    }
    // destroy mutex threads
    for (int i = 0; i < CNT; ++i) {
        pthread_mutex_destroy(&forks[i]);
    }
}