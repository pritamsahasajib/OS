
#include <stdio.h>

int main()
{
    // Declare variables
    int n, i, j, time = 0, tq;

    // Declare arrays for process information
    int at[20], bt[20], rem[20], ct[20], tat[20], wt[20];
    int pid[20], queue[10000];

    // Initialize ready queue pointers
    int front = 0, rear = 0;

    // Variables for queue and execution
    int next = 0, current, run;

    // Arrays for storing Gantt Chart information
    int gantt_pid[10000], gantt_start[10000], gantt_end[10000];
    int segments = 0, temp;

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

    // Take Time Quantum
    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    // Sort processes by arrival time
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            // Check if processes are in the wrong order
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

                // Swap Remaining Time
                temp = rem[i];
                rem[i] = rem[j];
                rem[j] = temp;

                // Swap Process ID
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    // Continue until all processes are completed
    while (next < n || front < rear)
    {
        // Check if ready queue is empty and next process has not arrived
        if (front == rear && next < n && time < at[next])
        {
            // Record CPU idle time in Gantt Chart
            gantt_pid[segments] = -1;
            gantt_start[segments] = time;
            gantt_end[segments] = at[next];
            segments++;

            // Move time to the next process arrival
            time = at[next];
        }

        // Add arrived processes to ready queue
        while (next < n && at[next] <= time)
        {
            queue[rear++] = next;
            next++;
        }

        // If ready queue is empty, continue
        if (front == rear)
            continue;

        // Select the first process from ready queue
        current = queue[front++];

        // Select execution time based on Time Quantum
        run = (rem[current] < tq) ? rem[current] : tq;

        // Record process and starting time in Gantt Chart
        gantt_pid[segments] = pid[current];
        gantt_start[segments] = time;

        // Execute process and update remaining time
        time += run;
        rem[current] -= run;

        // Record ending time in Gantt Chart
        gantt_end[segments] = time;
        segments++;

        // Add newly arrived processes to ready queue
        while (next < n && at[next] <= time)
        {
            queue[rear++] = next;
            next++;
        }

        // Check if process is not completed
        if (rem[current] > 0)
            // Add process back to ready queue
            queue[rear++] = current;
        else
            // Calculate Completion Time
            ct[current] = time;
    }

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

    for (i = 0; i < segments; i++)
    {
        // Print starting time of the Gantt Chart
        if (i == 0)
            printf("%d", gantt_start[i]);

        // Display CPU idle time
        if (gantt_pid[i] == -1)
            printf(" | Idle | %d", gantt_end[i]);
        else
            // Display process ID and ending time
            printf(" | P%d | %d", gantt_pid[i], gantt_end[i]);
    }

    printf("\n");

    return 0;
}
