#include <iostream>
#include <thread>
#include <semaphore>
#include <queue>
#include <mutex>
#include <chrono>

using namespace std;

const int BUFFER_SIZE = 2;

queue<int> buffer;

counting_semaphore<BUFFER_SIZE> emptySlots(BUFFER_SIZE);
counting_semaphore<BUFFER_SIZE> fullSlots(0);

mutex mtx;

void producer()
{
    for (int i = 1; i <= 5; i++)
    {
        cout << "\n----------------------------------\n";
        cout << "Producer wants to produce: " << i << endl;

        cout << "Producer: wait(emptySlots)\n";


        emptySlots.acquire();

        cout << "Producer: got an empty slot\n";


        // Critical Section
        mtx.lock();

        cout << "Producer ENTERED critical section\n";

        buffer.push(i);

        cout << "Produced: " << i << endl;
        cout << "Buffer size: "
             << buffer.size()
             << "/" << BUFFER_SIZE << endl;

        mtx.unlock();

        cout << "Producer EXITED critical section\n";



        fullSlots.release();

        cout << "Producer: signal(fullSlots)\n";


        this_thread::sleep_for(chrono::seconds(1));
    }
}

void consumer()
{
    for (int i = 1; i <= 5; i++)
    {
        cout << "\n----------------------------------\n";
        cout << "Consumer wants to consume\n";

        cout << "Consumer: wait(fullSlots)\n";

        fullSlots.acquire();

        cout << "Consumer: got an item\n";


        mtx.lock();

        cout << "Consumer ENTERED critical section\n";

        int item = buffer.front();
        buffer.pop();

        cout << "Consumed: " << item << endl;
        cout << "Buffer size: "
             << buffer.size()
             << "/" << BUFFER_SIZE << endl;

        mtx.unlock();

        cout << "Consumer EXITED critical section\n";


        emptySlots.release();

        cout << "Consumer: signal(emptySlots)\n";


        this_thread::sleep_for(chrono::seconds(3));
    }
}


int main()
{
    cout << "========================================\n";
    cout << "     PRODUCER-CONSUMER SEMAPHORE\n";
    cout << "========================================\n";

    cout << "Buffer size = " << BUFFER_SIZE << endl;

    thread p(producer);
    thread c(consumer);

    p.join();
    c.join();

    cout << "\n========================================\n";
    cout << "             PROGRAM END\n";
    cout << "========================================\n";

    return 0;
}
