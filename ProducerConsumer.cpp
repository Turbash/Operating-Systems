#include <iostream>
#include <queue>

using namespace std;

queue<int> buffer;

int emptySlots = 2;
int full = 0;
int mutex = 1;

void producer(int item)
{
    if (emptySlots == 0)
    {
        cout << "Producer BLOCKED: buffer is full\n";
        return;
    }

    if (mutex == 0)
    {
        cout << "Producer BLOCKED: critical section is busy\n";
        return;
    }

    emptySlots--;
    mutex = 0;

    cout << "Producer ENTERED critical section\n";

    buffer.push(item);

    cout << "Produced: " << item << endl;

    mutex = 1;
    full++;
    cout << "Producer EXITED critical section\n";
}

void consumer()
{
    if (full == 0)
    {
        cout << "Consumer BLOCKED: buffer is empty\n";
        return;
    }

    if (mutex == 0)
    {
        cout << "Consumer BLOCKED: critical section is busy\n";
        return;
    }

    full--;
    mutex = 0;

    cout << "Consumer ENTERED critical section\n";

    int item = buffer.front();
    buffer.pop();

    cout << "Consumed: " << item << endl;

    mutex = 1;
    emptySlots++;

    cout << "Consumer EXITED critical section\n";
}

int main()
{
    producer(1);
    producer(2);
    producer(3);

    consumer();
    producer(3);

    consumer();
    consumer();

    return 0;
}