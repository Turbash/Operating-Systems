#include <bits/stdc++.h>
#include <semaphore.h>
using namespace std;

sem_t rw_mutex, mutex_read;
int read_count = 0;

void reader(int id) {
    cout << "Reader " << id << " wants to read\n";

    sem_wait(&mutex_read);
    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex);
    sem_post(&mutex_read);

    cout << "Reader " << id << " is reading\n";
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Reader " << id << " finished reading\n";

    sem_wait(&mutex_read);
    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex);
    sem_post(&mutex_read);
}

void writer(int id) {
    cout << "Writer " << id << " wants to write\n";
    cout << "Writer " << id << " is waiting\n";

    sem_wait(&rw_mutex);

    cout << "Writer " << id << " is writing\n";
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Writer " << id << " finished writing\n";

    sem_post(&rw_mutex);
}






int main() {
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex_read, 0, 1);

    thread r1(reader, 1), r2(reader, 2);
    this_thread::sleep_for(chrono::milliseconds(200));

    thread w1(writer, 1);
    r1.join();
    r2.join();
    w1.join();

    thread w2(writer, 2);
    this_thread::sleep_for(chrono::milliseconds(200));

    thread r3(reader, 3);
    w2.join();
    r3.join();

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex_read);
}