
#include <stdio.h>

int main()
{
    // Declare variables
    int n, i, time = 0, count = 0;

    // Declare arrays for process information
    int at[20], bt[20], pr[20], ct[20], tat[20], wt[20];
    int pid[20], completed[20] = {0};

    // Arrays for storing Gantt Chart information
    int gantt_pid[100], gantt_time[100];
    int segments = 0, highest, next;

    // Variables for average time and Throughput calculation
    float avg_wt = 0, avg_tat = 0, throughput;

    // Take number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Take Arrival Time, Burst Time and Priority
    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        // Take process information in the new input format
        printf("\nProcess P%d\n", pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority: ");
        scanf("%d", &pr[i]);
    }

    // Initialize starting time of Gantt Chart
    gantt_time[0] = 0;

    // Continue until all processes are completed
    while (count < n)
    {
        highest = -1;

        // Find the highest priority available process
        for (i = 0; i < n; i++)
        {
            // Check if process has arrived and is not completed
            if (at[i] <= time && completed[i] == 0)
            {
                // Select process with highest priority
                // Smaller priority number means higher priority
                if (highest == -1 || pr[i] < pr[highest])
                    highest = i;
            }
        }

        // Handle CPU idle time
        if (highest == -1)
        {
            next = -1;

            // Find the next arriving incomplete process
            for (i = 0; i < n; i++)
            {
                if (completed[i] == 0)
                {
                    if (next == -1 || at[i] < at[next])
                        next = i;
                }
            }

            // Record CPU idle time in Gantt Chart
            gantt_pid[segments] = -1;
            time = at[next];
            gantt_time[++segments] = time;

            continue;
        }

        // Store selected process ID in Gantt Chart
        gantt_pid[segments] = pid[highest];

        // Execute process completely
        time += bt[highest];

        // Calculate Completion Time
        ct[highest] = time;

        // Store ending time in Gantt Chart
        gantt_time[++segments] = time;

        // Calculate Turnaround Time
        tat[highest] = ct[highest] - at[highest];

        // Calculate Waiting Time
        wt[highest] = tat[highest] - bt[highest];

        // Mark process as completed
        completed[highest] = 1;
        count++;

        // Add times for average calculation
        avg_wt += wt[highest];
        avg_tat += tat[highest];
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

    // Print starting time
    printf("%d", gantt_time[0]);

    for (i = 0; i < segments; i++)
    {
        // Display CPU idle time
        if (gantt_pid[i] == -1)
            printf(" | Idle | %d", gantt_time[i + 1]);
        else
            // Display process ID and ending time
            printf(" | P%d | %d", gantt_pid[i], gantt_time[i + 1]);
    }

    printf("\n");

    return 0;
}
