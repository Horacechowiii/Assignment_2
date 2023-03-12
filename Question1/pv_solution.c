
int buffer[K];
int fill = 0;
int use=0;
int count = 0;  //numbr of items in buffer
int read = 0;
int A = 123
sem_t empty;
sem_t full;
sem_t mutex;
// when producer put item A in the buffer, all consumers must access item A first before deleting it out from the buffer; or

void put(int value){
    buffer[fill] = value;
    fill=(fill+1) % K;
    count++;
}
int get() {
    int tmp = buffer[use];
    return tmp;
}

void *producer(void *arg) {
    int i;
    for (i = 0; i < M; i++) {
        while (count == K); //if the buffer size if full, keep waiting
        sem_wait(&empty); //if the buffer size is empty, keep waiting
        sem_wait(&mutex); //this is mutual exclusion
        put(A); // add items to buffer
        sem_post(&mutex); // relase the mutual exclusion
        sem_post(&full); // add the value of the 
    }
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        while (count == 0); //if the buffer size if 0, keep waiting
        sem_wait(&full); //if the buffer size is full, keep waiting
        for (j = 0; j < N ; j++){
            sem_wait(&mutex); //this is mutual exclusion
            int tmp = get(); //read the data from buffer
            sem_post(&mutex);   // relase the mutual exclusion 
        }
        use=(use+1) % K;
        count--;    //decrease the number of item of the buffer
        sem_post(&empty); // add value to senaphores
        printf(“%d\n”, tmp);    //print result
    } 
}


int main(int argc, char *argv[]) {
    // …
    sem_init(&empty, 0, K); // k buffers are empty to begin with …
    sem_init(&full, 0, 0); // ... and 0 are full
    sem_init(&mutex, 0, 1); // mutex=1 because it is a lock
    sem_init(&read, 0, N); // read=1 because it is a lock
    // …
}
