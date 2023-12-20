#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>

#define PH_COUNT 5

typedef struct
{
    pthread_t* philosophers;
    pthread_mutex_t* forks;
    int id;
} philosopher_data;

void* run_philosopher(void* data)
{
    philosopher_data ph_data = *((philosopher_data*) data);
    int ph_id = ph_data.id;
    pthread_mutex_t* fork_l = &ph_data.forks[ph_id];
    pthread_mutex_t* fork_r = &ph_data.forks[(ph_id + 1) % PH_COUNT];

    while(1)
    {
        printf("Философ %d размышляет\n", ph_id);
        pthread_mutex_lock(fork_l);
        printf("Философ %d берёт левую вилку (-%d)\n", ph_id, ph_id);
        pthread_mutex_lock(fork_r);
        printf("Философ %d берёт правую вилку (-%d)\n", ph_id, (ph_id + 1) % PH_COUNT);
        printf("Философ %d ест\n", ph_id);
        printf("Философ %d кладёт левую вилку (+%d)\n", ph_id, ph_id);
        printf("Философ %d кладёт правую вилку (+%d)\n", ph_id, (ph_id + 1) % PH_COUNT);
        pthread_mutex_unlock(fork_l);
        pthread_mutex_unlock(fork_r);
    }
    return NULL;
}

int main()
{
    philosopher_data philosophers_info[PH_COUNT];
    pthread_t philosophers[PH_COUNT];
    pthread_mutex_t forks[PH_COUNT];

    // mutex threads initialization
    for (int i = 0; i < PH_COUNT; ++i)
    {
        pthread_mutex_init(&forks[i], NULL);
    }
    for (int i = 0; i < PH_COUNT; ++i)
    {
        philosophers_info[i].id = i;
        philosophers_info[i].philosophers = philosophers;
        philosophers_info[i].forks = forks;
        pthread_create(&philosophers[i], NULL, run_philosopher, (void*) &(philosophers_info[i]));
    }
    // wait until all philosophers eat
    for (int i = 0; i < PH_COUNT; ++i)
    {
        pthread_join(philosophers[i], NULL);
    }
    // destroy mutex threads
    for (int i = 0; i < PH_COUNT; ++i)
    {
        pthread_mutex_destroy(&forks[i]);
    }
}