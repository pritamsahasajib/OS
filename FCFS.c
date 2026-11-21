
#include <stdio.h>

int main()
{
    // Declare variables
    int n, i, j;

    // Declare arrays for process information
    int at[20], bt[20], ct[20], tat[20], wt[20], pid[20];

    // temp is used for swapping, time stores current CPU time
    int temp, time = 0;

    // Variables to calculate average times
    float avg_wt = 0, avg_tat = 0, throughput;

    // Take the number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Take Arrival Time and Burst Time of each process
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
    }

    // Sort processes by Arrival Time
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            // Check if the current process arrives later
            if (at[i] > at[j])
            {
                // Swap Arrival Time
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap Burst Time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap Process ID
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    // Calculate CT, TAT and WT
    for (i = 0; i < n; i++)
    {
        // Handle CPU idle time
        if (time < at[i])
            time = at[i];

        // Calculate Completion Time
        time += bt[i];
        ct[i] = time;

        // Calculate Turnaround Time and Waiting Time
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        // Add times for average calculation
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    // Display process table heading
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    // Display process information
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

    // Reset time to zero for Gantt Chart
    time = 0;
    printf("%d", time);

    // Generate Gantt Chart for each process
    for (i = 0; i < n; i++)
    {
        // Check if CPU is idle
        if (time < at[i])
        {
            time = at[i];
            printf("    %d", time);
        }

        // Execute process and update time
        time += bt[i];

        // Display process ID and completion time
        printf(" | P%d | %d", pid[i], time);
    }

    printf("\n");

    // End the program
    return 0;
}
