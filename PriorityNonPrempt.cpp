#include <bits/stdc++.h>
using namespace std;

class Process
{
public:
    int arrivalTime;
    int burstTime;
    int permanentBurstTime;
    int pct;
    string name;
    int priority;
    Process *next;

    
    Process(int a, int b, int p, string n = "", int c = 0)
    {
        arrivalTime = a;
        burstTime = b;
        permanentBurstTime = b;
        pct = c;
        name = n;
        next = NULL;
        priority = p;
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
            if (curr->priority > n->priority)
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
    ProcessQueue outQueue;
    for (int i = 0; i < n; i++)
    {
        int a, b, p;
        cout << "Enter arrival time and burst time and priority:" << endl;
        cin >> a >> b >> p;
        Process* newProcess = new Process(a, b, p);
        pq.push(newProcess);
        // outQueue.push(newProcess);
    }
    int now = 1;
    cout << "\n--- Input Processes ---" << endl;
    Process* tempHead = pq.front();
    while(tempHead != NULL) {
        string processName = "P" + to_string(now++);
        tempHead->name = processName;
        cout << "Process: " << tempHead->name << " | Arrival: " << tempHead->arrivalTime << " | Burst: " << tempHead->burstTime <<" | Priority: " << tempHead->priority << endl;
        tempHead = tempHead->next;
    }
    cout << "-----------------------\n" << endl;

    WaitQueue wq;
    int time = 0;
    if (!pq.empty())
    {
        time = pq.front()->arrivalTime;
        while (!pq.empty() && pq.front()->arrivalTime <= time)
        {
            wq.push(pq.pop()); 
        }
    }
    int totalWaitingTime = 0;
    while (!wq.empty())
    {
        Process *now = wq.pop();
        
        time+=now->burstTime;
        now->burstTime = 0;

        cout<<now->name<<" "<<now->burstTime<<" "<<time<<endl;

        // cout<<now->burstTime<<endl;
        if(now->burstTime == 0)
        {
            now->pct = time;
            outQueue.push(now); 
        }
        else
        {
            wq.push(now);
        }
        while (!pq.empty() && pq.front()->arrivalTime <= time)
        {
            wq.push(pq.pop());
        }
        
        if (wq.empty() && !pq.empty())
        {
            time = pq.front()->arrivalTime;
            while (!pq.empty() && pq.front()->arrivalTime <= time)
            {
                wq.push(pq.pop());
            }
        }
    }
    int totalTurnaroundTime = 0;
    while(!outQueue.empty())
    {
        Process *now = outQueue.pop();
        int tt = now->pct - now->arrivalTime;
        int wt = tt - now->permanentBurstTime;
        totalWaitingTime += wt;
        totalTurnaroundTime += tt;
        cout <<  "Process: " << now->name << " | Arrival Time: " << now->arrivalTime << " | Burst Time: " << (now->permanentBurstTime) <<endl;
        cout<< "Completion Time: " << now->pct << " | Turnaround Time: " << tt << " | Waiting Time: " << wt << endl;
        delete now;
    }
    cout << "Total Waiting Time: " << totalWaitingTime << endl;
    float averageWaitingTime = static_cast<float>(totalWaitingTime) / n;
    float averageTurnaroundTime = static_cast<float>(totalTurnaroundTime) / n;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;
    return 0;
}
