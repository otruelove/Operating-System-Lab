#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int id;   // process number
    int at;   // arrival time
    int bt;   // burst time
    int rt;   // remaining time
    int ct;   // completion time
    int tat;  // turnaround time
    int wt;   // waiting time
};

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter Arrival Time of P" << i+1 << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time of P" << i+1 << ": ";
        cin >> p[i].bt;
        p[i].rt = p[i].bt; // initially remaining = burst time
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    queue<int> q;
    int current_time = 0, completed = 0;
    bool inQueue[n] = {false};

    // start with first process that arrives
    while (completed < n) {
        // push newly arrived processes
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && p[i].at <= current_time && p[i].rt > 0) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (q.empty()) {
            current_time++; // CPU idle
            continue;
        }

        int idx = q.front();
        q.pop();

        int execTime = min(tq, p[idx].rt);
        p[idx].rt -= execTime;
        current_time += execTime;

        // add new processes that arrived during this execution
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && p[i].at <= current_time && p[i].rt > 0) {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (p[idx].rt > 0) {
            q.push(idx); // not finished, requeue
        } else {
            completed++;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }

    // print results
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
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
