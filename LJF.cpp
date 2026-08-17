#include <bits/stdc++.h>
using namespace std;

class Process
{
public:
    int arrivalTime;
    int burstTime;
    Process *next;

    Process(int a, int b)
    {
        arrivalTime = a;
        burstTime = b;
        next = NULL;
    }
};

class ProcessQueue
{
public:
    Process *head;

    ProcessQueue() { head = NULL; }

    void push(Process *n)
    {
        Process *curr = head;
        Process *prev = NULL;
        while (curr != NULL)
        {
            if (curr->arrivalTime < n->arrivalTime)
            {
                prev = curr;
                curr = curr->next;
            }
            else
            {
                break;
            }
        }
        if (prev == NULL)
        {
            n->next = head;
            head = n;
        }
        else
        {
            prev->next = n;
            n->next = curr;
        }
    }

    Process* pop()
    {
        if (head == NULL) return NULL;
        Process *temp = head;
        head = head->next;
        temp->next = NULL; 
        return temp;      
    }
    
    bool empty() { return head == NULL; }
    Process *front() { return head; }
};

class WaitQueue
{
public:
    Process *head;

    WaitQueue() { head = NULL; }
    
    void push(Process *n)
    {
        Process *curr = head;
        Process *prev = NULL;
        while (curr != NULL)
        {
            if (curr->burstTime > n->burstTime)
            {
                prev = curr;
                curr = curr->next;
            }
            else
            {
                break;
            }
        }
        if (prev == NULL)
        {
            n->next = head;
            head = n;
        }
        else
        {
            prev->next = n;
            n->next = curr;
        }
    }
    
    Process* pop()
    {
        if (head == NULL) return NULL;
        Process *temp = head;
        head = head->next;
        temp->next = NULL; 
        return temp;
    }
    
    bool empty() { return head == NULL; }
    Process *front() { return head; }
};

int main()
{
    int n;
    cout << "Enter the number of processes" << endl;
    cin >> n;
    ProcessQueue pq;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cout << "Enter arrival time and burst time:" << endl;
        cin >> a >> b;
        pq.push(new Process(a, b));
    }

    cout << "\n--- Input Processes ---" << endl;
    Process* tempHead = pq.front();
    while(tempHead != NULL) {
        cout << "Arrival: " << tempHead->arrivalTime << " | Burst: " << tempHead->burstTime << endl;
        tempHead = tempHead->next;
    }
    cout << "-----------------------\n" << endl;

    int pct = 0;
    WaitQueue wq;

    if (!pq.empty())
    {
        pct = pq.front()->arrivalTime;
        while (!pq.empty() && pq.front()->arrivalTime <= pct)
        {
            wq.push(pq.pop()); 
        }
    }
    int totalWaitingTime = 0;
    while (!wq.empty())
    {
        Process *now = wq.pop(); 
        
        pct = max(pct, now->arrivalTime);
        pct += now->burstTime;
        int tt = pct - now->arrivalTime;
        int wt = tt - now->burstTime;
        totalWaitingTime += wt;
        cout << "Arrival Time: " << now->arrivalTime << " | Burst Time: " << now->burstTime << endl;
        cout << "Process Completion Time: " << pct << endl;
        cout << "Turnaround Time: " << tt << endl;
        cout << "Waiting Time: " << wt << endl;
        cout << "-----------------------------------" << endl;
        
        while (!pq.empty() && pq.front()->arrivalTime <= pct)
        {
            wq.push(pq.pop());
        }
        
        if (wq.empty() && !pq.empty())
        {
            pct = pq.front()->arrivalTime; 
            while (!pq.empty() && pq.front()->arrivalTime <= pct)
            {
                wq.push(pq.pop());
            }
        }
        delete now;
    }
    cout << "Total Waiting Time: " << totalWaitingTime << endl;
    float averageWaitingTime = static_cast<float>(totalWaitingTime) / n;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;
    return 0;
}
