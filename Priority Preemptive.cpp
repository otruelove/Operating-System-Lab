#include <iostream>
#include <climits>
using namespace std;

struct Process {
    int id;    // process number
    int at;    // arrival time
    int bt;    // burst time
    int rt;    // remaining time
    int pr;    // priority (smaller number = higher priority)
    int ct;    // completion time
    int tat;   // turnaround time
    int wt;    // waiting time
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
        p[i].rt = p[i].bt; // initially remaining time = burst time
    }

    int completed = 0, current_time = 0;

    while (completed < n) {
        int idx = -1;
        int bestPriority = INT_MAX;

        // choose process with highest priority among arrived ones
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                if (p[i].pr < bestPriority) {
                    bestPriority = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++; // CPU idle
            continue;
        }

        // execute for 1 unit time
        p[idx].rt--;
        current_time++;

        // if process finishes
        if (p[idx].rt == 0) {
            completed++;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
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
