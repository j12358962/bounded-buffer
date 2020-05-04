#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t mutex;
sem_t empty;
sem_t full;

int count = 0;
int bufferSize = 100;

void producer();
void consumer();

int main() {

    int i[2];
    i[0] = 0;
    i[1] = 1;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, bufferSize);
    sem_init(&full, 0, 0);  
    
    pthread_t thread_producer;
    pthread_t thread_consumer;

    pthread_create(&thread_producer, NULL, (void *) &producer, (void *) &i[0]);
    pthread_create(&thread_consumer, NULL, (void *) &consumer, (void *) &i[1]);

    pthread_join(thread_producer, NULL);
    pthread_join(thread_consumer, NULL);

    return 1;
}

void producer(){
    while(1){
    sem_wait(&mutex);
    sem_post(&full);
    sem_wait(&empty);
    count++;
    printf("\nProducer produces the item %d", count);
    sem_post(&mutex);
    sleep(3);
    }
}

void consumer(){
    while(1){
    sem_wait(&mutex);
    sem_wait(&full);
    sem_post(&empty);
    printf("\nConsumer consumes items %d", count);
    count--;
    sem_post(&mutex);
    sleep(5);
    }
}