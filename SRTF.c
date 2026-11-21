
#include <stdio.h>

int main()
{
    // Declare variables
    int n, i, time = 0, completed = 0;

    // Declare arrays for process information
    int at[20], bt[20], rem[20], ct[20], tat[20], wt[20];
    int pid[20], shortest;

    // Arrays for storing Gantt Chart information
    int gantt_pid[1000], gantt_time[1000];
    int segments = 0, current;

    // Variables for average time and Throughput calculation
    float avg_wt = 0, avg_tat = 0, throughput;

    // Take number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Take Arrival Time and Burst Time
    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        // Take process information in the new input format
        printf("\nProcess P%d\n", pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        // Copy Burst Time into Remaining Time
        rem[i] = bt[i];
    }

    // Initialize current process
    current = -2;
    gantt_time[0] = 0;

    // Continue until all processes are completed
    while (completed < n)
    {
        shortest = -1;

        // Find process with shortest remaining time
        for (i = 0; i < n; i++)
        {
            // Check if process has arrived and is not completed
            if (at[i] <= time && rem[i] > 0)
            {
                // Select process with minimum remaining time
                if (shortest == -1 || rem[i] < rem[shortest])
                    shortest = i;
            }
        }

        // Check if CPU has no available process
        if (shortest == -1)
            shortest = -1;

        // Record Gantt chart when process changes
        if (current != shortest)
        {
            // Store ending time of previous segment
            if (segments > 0)
                gantt_time[segments] = time;

            // Store the new process
            gantt_pid[segments] = shortest;
            current = shortest;
            segments++;
        }

        // If no process is available, CPU remains idle
        if (shortest == -1)
        {
            time++;
            continue;
        }

        // Execute process for one time unit
        rem[shortest]--;
        time++;

        // Check if process is completed
        if (rem[shortest] == 0)
        {
            // Calculate Completion Time
            ct[shortest] = time;
            completed++;
        }
    }

    // Store ending time of last Gantt chart segment
    gantt_time[segments] = time;

    // Calculate Turnaround Time and Waiting Time
    for (i = 0; i < n; i++)
    {
        // Turnaround Time = Completion Time - Arrival Time
        tat[i] = ct[i] - at[i];

        // Waiting Time = Turnaround Time - Burst Time
        wt[i] = tat[i] - bt[i];

        // Add times for average calculation
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    // Display process table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    // Display average Waiting Time and Turnaround Time
    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);

    // Calculate Throughput
    throughput = (float)n / time;

    // Display Throughput
    printf("\nThroughput = %.2f processes/unit time\n", throughput);

    // Display Gantt Chart
    printf("\nGantt Chart:\n");
    printf("%d", gantt_time[0]);

    for (i = 0; i < segments; i++)
    {
        // Display Idle time
        if (gantt_pid[i] == -1)
            printf(" | Idle | %d", gantt_time[i + 1]);
        else
            // Display process and ending time
            printf(" | P%d | %d", gantt_pid[i] + 1, gantt_time[i + 1]);
    }

    printf("\n");

    return 0;
}
