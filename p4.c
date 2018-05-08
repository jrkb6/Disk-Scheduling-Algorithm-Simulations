#include <stdio.h>
#include <stdlib.h>


//struct for the store input file information with corresponding list
typedef struct node{
    struct node *next;
    int arrival_time;
    int cylinder;
}node;
//dsflad
//headers
void readfile(char **argv);
void fcfs(node *requestlist,int *totalBlockChange, int *averageWaitingTime,int *stdWaitTime);
void sstf(node *requestlist,int *totalBlockChange, int *averageWaitingTime,int *stdWaitTime);
void look(node *requestlist,int *totalBlockChange, int *averageWaitingTime,int *stdWaitTime);
void clook(node *requestlist,int *totalBlockChange, int *averageWaitingTime,int *stdWaitTime);
void addNode(node **head,int time,int cylinder;);


void addNode(node **head,int time,int cylinder){
    //printf("adding val:  %d %d ",time,cylinder;);
    if ((*head) == NULL){
        (*head) = malloc(sizeof(node));
        (*head)->arrival_time = time;
        (*head)->cylinder = cylinder;
        (*head)->next = NULL;
    }
    else{
        node *temp = (*head);
        while(temp->next != NULL){
            temp = temp->next;
        }
        node *newNode =malloc(sizeof(node));
        newNode->arrival_time = time;
        newNode->cylinder = cylinder;
        newNode->next = NULL;
        temp->next = newNode;
    }
}

//lists for input readings
node *requestList = NULL;
int main(int argc, char **argv){
    readfile(argv);
    node *temp = requestList;
    //passing parameters
    int totalBlockChange;
    int averageWaitingTime;
    int stdWaitTime;

    //function calls
    fcfs(requestList,&totalBlockChange,&averageWaitingTime,&stdWaitTime);

    //printing results
    printf("FCFS result= %d \t%d\t%d\n",totalBlockChange,averageWaitingTime,stdWaitTime);
    return 0;
}
//reading from file
int numberofrequest= 0;
void readfile(char **argv){
    //printf("Reading file\n");
    FILE *handler;
    handler= fopen(argv[2],"r");
    int t;
    
    int cnt = 0;
    while(fscanf(handler,"%d",&t) == 1){
        int cylinder;
        if(fscanf(handler,"%d",&cylinder) == 1){
            //printf("t: %d blk: %d \n",t,cylinder;);
            addNode(&requestList,t,cylinder);
            numberofrequest++;
        }
        cnt++;
    }
    //printf("closing file");
    fclose(handler);
}
void fcfs(node *requestlist,int *totalBlockChange, int *averageWaitingTime,int *stdWaitTime){    //assuming we're 0 initial. So first comer is also included in calculation.
    node *temp  = requestlist;
    (*totalBlockChange) = 0;
    (*averageWaitingTime) = 0;
    (*stdWaitTime) = 0;
    int prev = 0;
    int passedTime = 0;
    while ( temp != NULL){
        (*totalBlockChange)  += abs(prev-temp->cylinder);
        prev = temp->cylinder;


        temp = temp->next;
    }   
}
void sstf(node *requestlist,int *totalBlockChange, int *averageWaitingTime,int *stdWaitTime){    //assuming we're 0 initial. So first comer is also included in calculation.
    node *temp  = requestlist;
    (*totalBlockChange) = 0;
    (*averageWaitingTime) = 0;
    int initial = 0;
    (*stdWaitTime) = 0;
    int prev = 0;
    int differences[numberofrequest];
    int index = 0;
    while(temp != NULL && index < numberofrequest){
        differences[index] = abs(initial - temp->next);
        initial = temp->cylinder;
        temp = temp->next;
        index++;
    }
}
//return the nearest next distance for the given node.
int findShortest(node *reqlist){
    node *temp;
    if(reqlist->next){
         temp = reqList->next;
    }
    else {
        return 0;
    }
    int min = __INT_MAX__;

    while(temp != NULL){
        if(abs(temp->cylinder - reqlist->cylinder) < min){
            min = abs(temp->cylinder - reqlist->cylinder);
        }
        temp = temp->next;
        return min;

    }
}
void look(node *requestlist,int *totalBlockChange, int *averageWaitingTime,int *stdWaitTime){    //assuming we're 0 initial. So first comer is also included in calculation.
    node *temp  = requestlist;
    (*totalBlockChange) = 0;
    (*averageWaitingTime) = 0;
    (*stdWaitTime) = 0;
    int prev = 0;
    while ( temp != NULL){
        (*totalBlockChange)  += abs(prev-temp->cylinder);
        prev = temp->cylinder;


        temp = temp->next;
    }   
    
}
void clook(node *requestlist,int *totalBlockChange, int *averageWaitingTime,int *stdWaitTime){    //assuming we're 0 initial. So first comer is also included in calculation.
    node *temp  = requestlist;
    (*totalBlockChange) = 0;
    (*averageWaitingTime) = 0;
    (*stdWaitTime) = 0;
    int prev = 0;
    while ( temp != NULL){
        (*totalBlockChange)  += abs(prev-temp->cylinder);
        prev = temp->cylinder;


        temp = temp->next;
    }   
}
