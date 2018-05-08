#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//struct for the store input file information with corresponding list
typedef struct node
{
    struct node *next;
    int arrival_time;
    int cylinder;
    int exec_start;
    int waiting_time;
} node;
//erdem
//headers
void readfile(char **argv);
void fcfs(node *requestlist, int *totalBlockChange, double *averageWaitingTime, double *stdWaitTime);
void sstf(node *requestlist, int *totalBlockChange, double *averageWaitingTime, double *stdWaitTime);
void look(node *requestlist, int *totalBlockChange, double *averageWaitingTime, double *stdWaitTime);
void clook(node *requestlist, int *totalBlockChange, double *averageWaitingTime, double *stdWaitTime);
void addNode(node **head, int time, int cylinder);
double stdDeviation(node* list, double average);

//addnode for linkedlist
void addNode(node **head, int time, int cylinder)
{
    //printf("adding val:  %d %d ",time,cylinder;);
    if ((*head) == NULL)
    {
        (*head) = malloc(sizeof(node));
        (*head)->arrival_time = time;
        (*head)->cylinder = cylinder;
        (*head)->exec_start = 0;
        (*head)->waiting_time = 0;
        (*head)->next = NULL;
    }
    else
    {
        node *temp = (*head);
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        node *newNode = malloc(sizeof(node));
        newNode->arrival_time = time;
        newNode->cylinder = cylinder;
        newNode->exec_start = 0;
        newNode->next = NULL;
        temp->next = newNode;
    }
}

//lists for input readings
node *requestList = NULL;
int main(int argc, char **argv)
{
    readfile(argv);
    //passing parameters
    int totalBlockChange;
    double averageWaitingTime;
    double stdWaitTime;

    //function calls
    fcfs(requestList, &totalBlockChange, &averageWaitingTime, &stdWaitTime);

    //printing results
    printf("FCFS result= %d \t %.2f\t%f\n", totalBlockChange, averageWaitingTime, stdWaitTime);
    return 0;
}
//reading from file
int numberofrequest = 0;
void readfile(char **argv)
{
    //printf("Reading file\n");
    FILE *handler;
    handler = fopen(argv[2], "r");
    int t;

    int cnt = 0;
    while (fscanf(handler, "%d", &t) == 1)
    {
        int cylinder;
        if (fscanf(handler, "%d", &cylinder) == 1)
        {
            //printf("t: %d blk: %d \n",t,cylinder;);
            addNode(&requestList, t, cylinder);
            numberofrequest++;
        }
        cnt++;
    }
    //printf("closing file");
    fclose(handler);
}

double stdDeviation(node* list, double average)
{
    double sum = 0;
    node* temp = list;
    while(temp!=NULL)
    {
        sum += pow(temp->waiting_time - average,2);
        temp = temp->next;
    }
   
    return sqrt(sum/numberofrequest);
}

void fcfs(node *requestlist, int *totalBlockChange, double *averageWaitingTime, double *stdWaitTime){ //assuming we're at 1 initial. So first comer is also included in calculation.
    node *temp = requestlist;
    (*totalBlockChange) = 0;
    (*averageWaitingTime) = 0;
    (*stdWaitTime) = 0;
    int prev = 1;
    int passedTime = 0;
    while (temp != NULL)
    {
        (*totalBlockChange) += abs(prev - temp->cylinder);
        if (passedTime <= temp->arrival_time)
        {
            passedTime = abs(prev - temp->cylinder) + temp->arrival_time;
        }
        else
        {   
            temp->waiting_time = (passedTime - temp->arrival_time);
            (*averageWaitingTime) += temp->waiting_time;
            passedTime += abs(prev - temp->cylinder);
        }
        prev = temp->cylinder;
        temp = temp->next;
    }
    (*averageWaitingTime) /= numberofrequest;
    (*stdWaitTime) = stdDeviation(requestList,(*averageWaitingTime));
}

void look(node *requestlist, int *totalBlockChange, double *averageWaitingTime, double *stdWaitTime)
{ //assuming we're 0 initial. So first comer is also included in calculation.
    node *temp = requestlist;
    (*totalBlockChange) = 0;
    (*averageWaitingTime) = 0;
    (*stdWaitTime) = 0;
    int prev = 0;
    while (temp != NULL)
    {
        (*totalBlockChange) += abs(prev - temp->cylinder);
        prev = temp->cylinder;

        temp = temp->next;
    }
}
void clook(node *requestlist, int *totalBlockChange, double *averageWaitingTime, double *stdWaitTime)
{ //assuming we're 0 initial. So first comer is also included in calculation.
    node *temp = requestlist;
    (*totalBlockChange) = 0;
    (*averageWaitingTime) = 0;
    (*stdWaitTime) = 0;
    int prev = 0;
    while (temp != NULL)
    {
        (*totalBlockChange) += abs(prev - temp->cylinder);
        prev = temp->cylinder;

        temp = temp->next;
    }
}
