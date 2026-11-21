
#include <stdio.h>

int main()
{
    // Declare variables
    int n, i, time = 0, count = 0;

    // Declare arrays for process information
    int at[20], bt[20], ct[20], tat[20], wt[20];

    // Store process ID and completion status
    int pid[20], completed[20] = {0};

    // Arrays to store Gantt Chart information
    int gantt_pid[100], gantt_start[100], gantt_end[100];

    // Declare variables for process selection and Gantt Chart
    int segments = 0, shortest, next;

    // Variables to calculate average times and Throughput
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

    // Repeat until all processes are completed
    while (count < n)
    {
        // Initialize shortest process
        shortest = -1;

        // Find the shortest available process
        for (i = 0; i < n; i++)
        {
            // Check if process has arrived and is not completed
            if (at[i] <= time && completed[i] == 0)
            {
                // Select the process with the shortest Burst Time
                if (shortest == -1 || bt[i] < bt[shortest])
                    shortest = i;
            }
        }

        // Handle CPU idle time
        if (shortest == -1)
        {
            // Initialize next process
            next = -1;

            // Find the next arriving incomplete process
            for (i = 0; i < n; i++)
            {
                if (completed[i] == 0)
                {
                    // Select the process with the earliest Arrival Time
                    if (next == -1 || at[i] < at[next])
                        next = i;
                }
            }

            // Store CPU idle information in Gantt Chart
            gantt_pid[segments] = -1;
            gantt_start[segments] = time;
            gantt_end[segments] = at[next];

            // Update current time to the next Arrival Time
            time = at[next];

            // Increase Gantt Chart segment count
            segments++;

            // Restart the loop
            continue;
        }

        // Store selected process information in Gantt Chart
        gantt_pid[segments] = pid[shortest];
        gantt_start[segments] = time;

        // Execute the selected process
        time += bt[shortest];

        // Calculate Completion Time
        ct[shortest] = time;

        // Store process ending time in Gantt Chart
        gantt_end[segments] = time;

        // Increase Gantt Chart segment count
        segments++;

        // Calculate Turnaround Time and Waiting Time
        tat[shortest] = ct[shortest] - at[shortest];
        wt[shortest] = tat[shortest] - bt[shortest];

        // Mark the process as completed
        completed[shortest] = 1;

        // Increase completed process count
        count++;

        // Add times for average calculation
        avg_wt += wt[shortest];
        avg_tat += tat[shortest];
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

    // Print the starting time of the first segment
    printf("%d", gantt_start[0]);

    // Display all Gantt Chart segments
    for (i = 0; i < segments; i++)
    {
        // Check if CPU was idle
        if (gantt_pid[i] == -1)
            printf(" | Idle | %d", gantt_end[i]);

        // Display process ID and ending time
        else
            printf(" | P%d | %d", gantt_pid[i], gantt_end[i]);
    }

    printf("\n");

    // End the program
    return 0;
}
