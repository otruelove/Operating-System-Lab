#include <iostream>
#include <climits>
using namespace std;

struct Process {
    int id;    // process number
    int at;    // arrival time
    int bt;    // burst time
    int rt;    // remaining time
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
        p[i].rt = p[i].bt; // initially remaining time = burst time
    }

    int completed = 0, current_time = 0;
    int shortest = -1;
    int minRT = INT_MAX;

    while (completed < n) {
        shortest = -1;
        minRT = INT_MAX;

        // find process with smallest remaining time at this moment
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                if (p[i].rt < minRT) {
                    minRT = p[i].rt;
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            current_time++; // CPU idle
            continue;
        }

        // execute process for 1 unit time
        p[shortest].rt--;
        current_time++;

        // if process finished
        if (p[shortest].rt == 0) {
            completed++;
            p[shortest].ct = current_time;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
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
