#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#define MAX 100

int totalTime=0;
int userProcess=0,systemProcess=0;

// Structure to represent a process
typedef struct
{
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority; // 0 for system process, 1 for user process
} Process;

// Function to execute a process
void executeProcess(Process process)
{
    int i;
    printf("Executing Process %d\n", process.processID);
    // Simulating the execution time of the process
    for (i = 1; i <= process.burstTime; i++)
    {
            printf("Process %d: %d/%d\n", process.processID, i, process.burstTime);
    }
    printf("Process %d executed\n", process.processID);
}

// Function to perform FCFS scheduling for a queue of processes
void scheduleFCFS(Process system[],Process user[])
{
    int i,j;
    for(i=0;i<systemProcess;i++)
    {
        for(j=i+1;j<systemProcess;j++)
        {
            if(system[i].arrivalTime>system[j].arrivalTime)
            {
                Process temp=system[i];
                system[i]=system[j];
                system[j]=temp;
            }
        }
    }
    for(i=0;i<userProcess;i++)
    {
        for(j=i+1;j<userProcess;j++)
        {
            if(user[i].arrivalTime>user[j].arrivalTime)
            {
                Process temp=user[i];
                user[i]=user[j];
                user[j]=temp;
            }
        }
    }
    int completed=0;
    int currentProcess=-1;
    bool isUserProcess=false;
    int size=userProcess+systemProcess;
    while(1)
    {
        int count=0;
        for(i=0;i<systemProcess;i++)
        {
            if(system[i].remainingTime<=0)
            {
                count++;
            }
        }
        for(j=0;j<userProcess;j++)
        {
            if(user[j].remainingTime<=0)
            {
                count++;
            }
        }
        if(count==size)
        {
            printf("\n end of processess");
            exit(0);
        }
        for(i=0;i<systemProcess;i++)
        {
            if(totalTime>=system[i].arrivalTime && system[i].remainingTime>0)
            {
                currentProcess=i;
                isUserProcess=false;
                break;
            }
        }
        if(currentProcess==-1)
        {
            for(j=0;j<userProcess;j++)
            {
                if(totalTime>=user[j].arrivalTime && user[j].remainingTime>0)
                {
                    currentProcess=j;
                    isUserProcess=true;
                    break;
                }
            }
        }
        if(currentProcess==-1)
        {
            totalTime++;
            printf("\n %d idle time...",totalTime);
            if(totalTime==1000)
            {
                exit(0);
            }
            continue;
        }
        if(isUserProcess==true)
        {
            user[currentProcess].remainingTime--;
            printf("\n User process %d will excecute at %d",user[currentProcess].processID,(totalTime));
            totalTime++;
            isUserProcess=false;
            currentProcess=-1;
            if(user[currentProcess].remainingTime==0)
            {
                completed++;
            }
        }
        else
        {
            int temp=totalTime;
            while(system[currentProcess].remainingTime--)
            {
                totalTime++;
            }
            if(system[currentProcess].remainingTime==0)
            {
                completed++;
            }
            printf("\n System process %d will excecute from %d to %d ",system[currentProcess].processID,temp,(totalTime));
            isUserProcess=false;
            currentProcess=-1;
        }
    }
}

int main()
{
    int numProcesses,i;
    Process processes[MAX];
    // Reading the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    // Reading process details
    for (i = 0; i < numProcesses; i++)
    {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        printf("System(0)/User(1): ");
        scanf("%d", &processes[i].priority);
        processes[i].processID = i + 1;
        processes[i].remainingTime=processes[i].burstTime;
        if(processes[i].priority==1)
        {
            userProcess++;
        }
        else
        {
            systemProcess++;
        }
    }
    Process systemQueue[MAX];
    int systemQueueSize = 0;
    Process userQueue[MAX];
    int userQueueSize = 0;
    for (i = 0; i < numProcesses; i++)
    {
        if (processes[i].priority == 0)
        {
            systemQueue[systemQueueSize++] = processes[i];
        }
        else
        {
            userQueue[userQueueSize++] = processes[i];
        }
    }
    printf("Order of Excecution :\n");
    scheduleFCFS(systemQueue,userQueue);
    return 0;
}
