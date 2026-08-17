#include <bits/stdc++.h>
using namespace std;

class Process{
    public:

    int arrivalTime;
    int burstTime;
    Process* next;

    Process(int a, int b){
        arrivalTime = a;
        burstTime = b;
        next = NULL;
    }
};

class ProcessQueue{
    public:
    Process* head;
    Process* tail;

    ProcessQueue(){
        head = NULL;
        tail = NULL;
    }

    void push(Process* n){
        Process* curr = head;
        Process* prev = NULL;
        while(curr!=NULL){
            if(curr->arrivalTime < n->arrivalTime){
                prev = curr;
                curr=curr->next;
            }else {
                break;
            }
        }
        if(prev==NULL){
            n->next = head;
            head = n;
        }else{
            prev->next = n;
            n->next = curr;
        }

        if(n->next == NULL){
            tail = n;
        }
    }
    void pop(){
        if(head == NULL){
            throw std::underflow_error("Queue Underflow: Cannot pop from an empty queue.");
        }
        Process* temp = head;
        head = head->next;
        delete temp;
        if(head == NULL){
            tail = NULL;
        }
    }
    bool empty(){
        return head == NULL;
    }
    Process* front(){
        return head;
    }
};

int main(){
    int n;
    cout<<"Enter the number of processes"<<endl;
    cin>>n;
    ProcessQueue pq;
    for(int i=0;i<n;i++){
        int a,b;
        cout<<"Enter the arrival time of Process"<<endl;
        cin>>a;
        cout<<"Enter the burst time of Process"<<endl;
        cin>>b;
        Process* p1 = new Process(a,b);
        pq.push(p1);
    }
    int pct = 0;
    while(!pq.empty()){
        Process* now = pq.front();
        pct+= now->burstTime;
        int tt = pct - now->arrivalTime;
        int wt = tt - now->burstTime;
        cout<<"Arrival Time: "<<now->arrivalTime<<" "<<" Burst Time: "<<now->burstTime<<endl;
        cout<<"Turnaround Time: "<<tt<<endl;
        cout<<"Waiting Time: "<<wt<<endl;
        pq.pop();
    }
    return 0;
}