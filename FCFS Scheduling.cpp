#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int AT[n], BT[n], WT[n], TAT[n], CT[n];

    // Input Arrival Time & Burst Time
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time of P" << i+1 << ": ";
        cin >> AT[i];
        cout << "Enter Burst Time of P" << i+1 << ": ";
        cin >> BT[i];
    }

    // Calculate Completion, Waiting and Turnaround Times
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < AT[i]) {
            current_time = AT[i]; // CPU idle until process arrives
        }
        CT[i] = current_time + BT[i]; // Completion Time
        current_time = CT[i];

        TAT[i] = CT[i] - AT[i]; // Turnaround Time = CT - AT
        WT[i] = TAT[i] - BT[i]; // Waiting Time = TAT - BT
    }

    // Print Table
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t" 
             << AT[i] << "\t" 
             << BT[i] << "\t" 
             << CT[i] << "\t" 
             << TAT[i] << "\t" 
             << WT[i] << "\n";
    }

    // Calculate average WT and TAT
    float avgWT = 0, avgTAT = 0;
    for (int i = 0; i < n; i++) {
        avgWT += WT[i];
        avgTAT += TAT[i];
    }
    avgWT /= n;
    avgTAT /= n;

    cout << "\nAverage Waiting Time: " << avgWT;
    cout << "\nAverage Turnaround Time: " << avgTAT << endl;

    return 0;
}
