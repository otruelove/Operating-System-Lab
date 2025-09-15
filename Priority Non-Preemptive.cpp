#include <iostream>
using namespace std;

struct Process {
    int id;    // process number
    int at;    // arrival time
    int bt;    // burst time
    int pr;    // priority (smaller = higher priority)
    int ct;    // completion time
    int tat;   // turnaround time
    int wt;    // waiting time
    bool done; // finished or not
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter Arrival Time of P" << i+1 << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time of P" << i+1 << ": ";
        cin >> p[i].bt;
        cout << "Enter Priority of P" << i+1 << ": ";
        cin >> p[i].pr;
        p[i].done = false;
    }

    int current_time = 0, completed = 0;
    while (completed < n) {
        int idx = -1;
        int bestPriority = 1e9;

        // choose process with highest priority (smallest number) among arrived
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= current_time) {
                if (p[i].pr < bestPriority) {
                    bestPriority = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx == -1) { 
            // no process has arrived yet
            current_time++;
        } else {
            // execute process
            current_time += p[idx].bt;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = true;
            completed++;
        }
    }

    // print results
    cout << "\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t" 
             << p[i].at << "\t" 
             << p[i].bt << "\t" 
             << p[i].pr << "\t" 
             << p[i].ct << "\t" 
             << p[i].tat << "\t" 
             << p[i].wt << "\n";
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    cout << "\nAverage Turnaround Time: " << (totalTAT / n);
    cout << "\nAverage Waiting Time: " << (totalWT / n) << endl;

    return 0;
}
