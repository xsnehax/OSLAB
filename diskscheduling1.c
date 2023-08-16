#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to implement FCFS scheduling algorithm
void fcfs(int queue[], int n, int head) {
    int totalMovement = 0;

    printf("FCFS Scheduling\n");
    printf("Sequence of movement: %d ", head);

    for (int i = 0; i < n; i++) {
        totalMovement += abs(queue[i] - head);
        head = queue[i];
        printf("-> %d ", head);
    }

    printf("\nTotal head movement: %d\n\n", totalMovement);
}

// Function to implement SSTF scheduling algorithm
void sstf(int queue[], int n, int head) {
    int totalMovement = 0;
    int visited[n];

    for (int i = 0; i < n; i++) {
        visited[i] = 0;  //initialise entire visited array to 0(all unvisited initially)
    }

    printf("SSTF Scheduling\n");
    printf("Sequence of movement: %d ", head);

    for (int i = 0; i < n; i++) {
        int minDistance = 9999;
        int index = -1;

       //for loop to find min dist from each point
        for (int j = 0; j < n; j++) {
            if (visited[j]==0 && abs(queue[j] - head) < minDistance) {
                minDistance = abs(queue[j] - head);
                index = j;
            }
        }

        visited[index] = 1;
        totalMovement += minDistance;
        head = queue[index];
        printf("-> %d ", head);
    }

    printf("\nTotal head movement: %d\n\n", totalMovement);
}

// Function to implement SCAN scheduling algorithm
void scan(int queue[], int n, int head, int direction) {
    int totalMovement = 0;

    printf("SCAN Scheduling\n");
    printf("Sequence of movement: %d ", head);

   int t1,t2,t3,i;

    int pos=0,pos1,pos2=0;//pos of element left of head
    for(i=0;i<n;i++)
    {
        if(queue[i]>head)
        {
            pos=i-1; break;  //pos=1 here
        }
    }
    if(direction==1)
    {
        printf("SCAN Scheduling\n");
        printf("Sequence of movement: %d ", head);
        t1=199-head;
        pos2=pos;
        t3=199-queue[0];

        totalMovement=t1+t3;
        pos1=pos+1;
        while(pos1<=n-1)
        printf("->%d",queue[pos1++]);
        printf("->199");
        while(pos2>=0)
        printf("->%d",queue[pos2--]);
    }
    else
    {
        t1=head;
        t2=199;
        totalMovement=t1+t2;
        pos1=pos; pos2=pos+1;
        printf("SCAN Scheduling\n");
        printf("Sequence of movement: %d ", head);
        while(pos1>=0)
        printf("->%d",queue[pos1--]);
        while(pos2<=n-1)
        printf("->%d",queue[pos2++]);
        printf("->199");
    }
    printf("\nTotal head movement: %d\n\n", totalMovement);
}

// Function to implement C-SCAN scheduling algorithm
void cscan(int queue[], int n, int head, int direction) {
    int t1,t2,i;
    int totalMovement = 0; int pos=0,pos1,pos2=0;//pos of element left of head
    for(i=0;i<n;i++)
    {
        if(queue[i]>head)
        {
            pos=i-1; break;  //pos=1 here
        }
    }
    if(direction==1)
    {   printf("CSCAN Scheduling\n");
        printf("Sequence of movement: %d ", head);
        t1=199-head;
        t2=queue[pos];
        totalMovement=t1+t2;
        pos1=pos+1;
        while(pos1<=n-1)
        printf("->%d",queue[pos1++]);
        printf("->199->0");
        while(pos2<=pos)
        printf("->%d",queue[pos2++]);
    }
    else
    {
        t1=head;
        t2=199-queue[pos+1];
        totalMovement=t1+t2;
        pos1=pos; pos2=n-1;
        printf("CSCAN Scheduling\n");
        printf("Sequence of movement: %d ", head);
        while(pos1>=0)
        printf("->%d",queue[pos1--]);
        printf("->0->199");
        while(pos2>pos)
        printf("->%d",queue[pos2--]);
    }
    printf("\nTotal head movement: %d\n\n", totalMovement);
}

int main() {
    int n, head, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int queue[n];

    int queue1[n];

    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &queue[i]);
        queue1[i]=queue[i];
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);
    for(int u=0;u<n;u++)
        queue1[u]=queue[u];
    //sort
    for (int k=0;k<n-1;k++)
    {
        for(int y=0;y<n-k-1;y++)
        {
            if(queue[y]>queue[y+1])
            {
                int temp= queue[y];
                queue[y]=queue[y+1];
                queue[y+1]=temp;
            }
        }
    }//sorted

    printf("Enter the direction (1 for right, -1 for left): ");
    scanf("%d", &direction);


    while (1) {
        printf("\nDisk Scheduling Algorithms:\n");
        printf("1. FCFS\n");
        printf("2. SCAN\n");
        printf("3. C-SCAN\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(queue1, n, head);
                break;

            case 2:
                scan(queue, n, head, direction);
                break;
            case 3:
                cscan(queue, n, head, direction);
                break;

            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
