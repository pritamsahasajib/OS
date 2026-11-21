
#include <stdio.h>

int main()
{
    // Declare variables
    int n, i, time = 0, completed = 0;

    // Declare arrays for process information
    int at[20], bt[20], rem[20], pr[20];
    int ct[20], tat[20], wt[20], pid[20];

    // Arrays for storing Gantt Chart information
    int gantt_pid[1000], gantt_time[1000];
    int segments = 0, highest, current = -2;

    // Variables for average time and Throughput calculation
    float avg_wt = 0, avg_tat = 0, throughput;

    // Take number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Take Arrival Time, Burst Time and Priority
    for (i = 0; i < n; i++)
    {
        // Assign process ID
        pid[i] = i + 1;

        // Take process information in the new input format
        printf("\nProcess P%d\n", pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority: ");
        scanf("%d", &pr[i]);

        // Copy Burst Time into Remaining Time
        rem[i] = bt[i];
    }

    // Initialize starting time of Gantt Chart
    gantt_time[0] = 0;

    // Continue until all processes are completed
    while (completed < n)
    {
        // Initialize highest priority process
        highest = -1;

        // Find highest priority available process
        for (i = 0; i < n; i++)
        {
            // Check if process has arrived and is not completed
            if (at[i] <= time && rem[i] > 0)
            {
                // Select process with highest priority
                // Smaller priority number means higher priority
                if (highest == -1 || pr[i] < pr[highest])
                    highest = i;
            }
        }

        // Record process change in Gantt Chart
        if (current != highest)
        {
            // Store ending time of previous segment
            if (segments > 0)
                gantt_time[segments] = time;

            // Store the selected process
            gantt_pid[segments] = highest;
            current = highest;
            segments++;
        }

        // Check if no process is available
        if (highest == -1)
        {
            // Increase time while CPU is idle
            time++;
            continue;
        }

        // Execute process for one time unit
        rem[highest]--;
        time++;

        // Check if process is completed
        if (rem[highest] == 0)
        {
            // Calculate Completion Time
            ct[highest] = time;

            // Increase completed process count
            completed++;
        }
    }

    // Store ending time of last Gantt Chart segment
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
    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], pr[i],
               ct[i], tat[i], wt[i]);
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

    // Display all Gantt Chart segments
    for (i = 0; i < segments; i++)
    {
        // Display CPU idle time
        if (gantt_pid[i] == -1)
            printf(" | Idle | %d", gantt_time[i + 1]);
        else
            // Display process ID and ending time
            printf(" | P%d | %d", gantt_pid[i] + 1, gantt_time[i + 1]);
    }

    printf("\n");

    // End the program
    return 0;
}
