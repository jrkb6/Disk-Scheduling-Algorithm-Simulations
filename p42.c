#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//struct for the store input file information with corresponding list
typedef struct node{
    struct node *next;
    int arrival_time;
    int cylinder;
    int exec_start;
    int visited;
    int waiting_time;
}node;
//erdem
//headers
void readfile(char **argv);
void fcfs(node *requestlist,int *totalBlockChange, double *averageWaitingTime,double *stdWaitTime);
void sstf(node *requestlist,int *totalBlockChange, double *averageWaitingTime,double *stdWaitTime);
void look(node *requestlist,int *totalBlockChange, double *averageWaitingTime,double *stdWaitTime);
void clook(node *requestlist,int *totalBlockChange, double *averageWaitingTime,double *stdWaitTime);
void addNode(node **head,int time,int cylinder);
void resetNodes(node * requestlist);
double stdDeviation(node* list, double average);
//addnode for linkedlist
void addNode(node **head,int time,int cylinder){
    //printf("adding val:  %d %d ",time,cylinder;);
    if ((*head) == NULL){
        (*head) = malloc(sizeof(node));
        (*head)->arrival_time = time;
        (*head)->cylinder = cylinder;
        (*head)->exec_start = 0;
        (*head)->next = NULL;
        (*head)->visited = 0;
        (*head)->waiting_time = 0;
    }
    else{
        node *temp = (*head);
        while(temp->next != NULL){
            temp = temp->next;
        }
        node *newNode =malloc(sizeof(node));
        newNode->arrival_time = time;
        newNode->cylinder = cylinder;
        newNode->exec_start = 0;
        newNode->next = NULL;
        newNode->visited=0;
        newNode->waiting_time = 0;
        temp->next = newNode;
        

    }
}

//lists for input readings
int N;
node *requestList = NULL;
int main(int argc, char **argv){
    
    N = atoi(argv[1]);
    readfile(argv);
    node *temp = requestList;
    //passing parameters
    int totalBlockChange;
    double averageWaitingTime;
    double stdWaitTime;

    //function calls
    
    fcfs(requestList,&totalBlockChange,&averageWaitingTime,&stdWaitTime);
    resetNodes(requestList);
    //printing results
    printf("FCFS :  %d \t%f\t%f\n",totalBlockChange,averageWaitingTime,stdWaitTime);
    
    //resetNodes(requestList);

    sstf(requestList,&totalBlockChange,&averageWaitingTime,&stdWaitTime);

    printf("SSTF :     %d \t%f\t%f\n",totalBlockChange,averageWaitingTime,stdWaitTime);    

    resetNodes(requestList);

    look(requestList,&totalBlockChange,&averageWaitingTime,&stdWaitTime);

    printf("LOOK :      %d \t%f\t%f\n",totalBlockChange,averageWaitingTime,stdWaitTime);

    resetNodes(requestList);

    clook(requestList,&totalBlockChange,&averageWaitingTime,&stdWaitTime);

    printf("CLOOK:      %d \t%f\t%f\n",totalBlockChange,averageWaitingTime,stdWaitTime);


    return 0;
}

void resetNodes(node*requestlist)
{
    node * temp = requestlist;
    while(temp!=NULL)
    {
        temp->visited=0;
        temp->exec_start=0;
        temp->waiting_time=0;
        temp = temp->next;
    }
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
            
            addNode(&requestList,t,cylinder);
            //printf("t: %d blk: %d \n",t,cylinder);
            numberofrequest++;
        }
        cnt++;
    }
    //printf("closing file");
    fclose(handler);
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
double stdDeviation(node* list, double average)
{
   
    double sum = 0;
    node* temp = list;
    while(temp!=NULL)
    {   
        
       
        sum += pow(abs(temp->waiting_time-average),2);    

        temp = temp->next;   
    }
    //printf("std : %d %f \n",numberofrequest,sum);
    return (double)sqrt(sum/(numberofrequest-1));
}

double averageWaiting(node* list)
{
    node* temp = list;
    
    double sum = 0;
    while(temp!=NULL)
    {
       
        temp->waiting_time = temp->exec_start-temp->arrival_time;
        sum+=temp->waiting_time;
        temp=temp->next;
    }
   
    return (double)(sum/numberofrequest);

}
//return the nearest next distance for the given node.
int allVisited(node* list)
{
    int visited = 1;
    node* temp = list;
    while(temp!=NULL)
    {
        visited = visited && temp->visited;
        temp=temp->next;
    }
    return visited;

}
node* findShortest(node *reqlist, int currentCylinder,int currentTime){
    int finded=0; 
    node *temp = reqlist;
    node* closest = reqlist;
    int shortestDistance=N+1;

    while(temp!=NULL)
    {
        if(!temp->visited&&abs(temp->cylinder-currentCylinder)<shortestDistance&&currentTime>=temp->arrival_time)
        {
            
                closest = temp;
                shortestDistance = abs(temp->cylinder-currentCylinder);
                finded = 1;
            
        }
        if(temp->arrival_time>currentTime)
        {

            break;
        }
        temp = temp->next;

    }
    if(!finded){
        node* re = NULL;
        return re;
    }
    return closest;
    
}
void sstf(node *requestlist,int *totalBlockChange, double *averageWaitingTime,double *stdWaitTime){    //assuming we're 1 initial. So first comer is also included in calculation.
    node *temp  = requestlist;
    (*totalBlockChange) = 0;
    int startCylinder=1;
    int currentTime=0;
    node *closest = findShortest(requestlist,startCylinder,currentTime);
    while(closest==NULL)
    {
        
        currentTime++;
        closest = findShortest(requestlist,startCylinder,currentTime);

    }
    closest->visited = 1;
    closest->exec_start = currentTime;
    currentTime+=abs(closest->cylinder-startCylinder);
    
    (*totalBlockChange)=abs(closest->cylinder-startCylinder);
    //printf("move to %d\n",closest->cylinder);
    temp=closest;
    while(!allVisited(requestlist))
    {
       
        closest = findShortest(requestlist,temp->cylinder,currentTime);
        while(closest==NULL)
        {
            currentTime++;
            closest = findShortest(requestlist,temp->cylinder,currentTime);

         }
        closest->visited = 1;
        closest->exec_start = currentTime;
        currentTime+=abs(closest->cylinder-temp->cylinder);
        
        (*totalBlockChange)+=abs(closest->cylinder-temp->cylinder);
        //printf("move to %d\n",closest->cylinder);
        temp=closest;
    }

    (*averageWaitingTime) = averageWaiting(requestlist);
    (*stdWaitTime)= stdDeviation(requestlist,(*averageWaitingTime));

    
}

node* lookForLeft(node * requestlist,int currentCylinder,int currentTime)
{
    int finded=0; 
    node *temp = requestlist;
    node* closest = requestlist;
    int shortestDistance=N+1;
    while(temp!=NULL)
    {
        if(!temp->visited&&(currentCylinder-temp->cylinder)>=0 && abs(currentCylinder-temp->cylinder)<shortestDistance && currentTime >= temp->arrival_time)
        {
            
            closest = temp;
            shortestDistance = abs(currentCylinder-temp->cylinder);
            finded = 1;
            
        }
        if(temp->arrival_time>currentTime)
        {

            break;
        }
        temp = temp->next;
    }
    if(!finded){
        node* re = NULL;
        return re;
    }
    return closest;
}

node* lookForRight(node * requestlist,int currentCylinder,int currentTime)
{
    int finded=0; 
    node *temp = requestlist;
    node* closest = requestlist;
    int shortestDistance=N+1;
    while(temp!=NULL)
    {
        if(!temp->visited&&(temp->cylinder-currentCylinder)>=0&&abs(temp->cylinder-currentCylinder)<shortestDistance && currentTime >= temp->arrival_time)
        {
            
            closest = temp;
            shortestDistance = abs(temp->cylinder-currentCylinder);
            finded = 1;
            
        }
        if(temp->arrival_time>currentTime)
        {

            break;
        }
        temp = temp->next;

    }
    if(!finded){
        node* re = NULL;
        return re;
    }
    return closest;
}


void look(node *requestlist,int *totalBlockChange, double *averageWaitingTime,double *stdWaitTime)
{   
    node *temp  = requestlist;
    (*totalBlockChange) = 0;
    int startCylinder=1;
    int currentTime=0;
    int direction = 1; //1 for right, 0 for left
    int start = 0;
    node * closestRight;
    node * closestLeft;
    int currentCylinder = 1;

    while(!allVisited(requestlist))
    {
        if(!start)
        {
           
            currentCylinder = 1;
        }
        else if(start)
        {
            currentCylinder = temp->cylinder;
        }
        
        closestRight = lookForRight(requestlist,currentCylinder,currentTime);
        closestLeft = lookForLeft(requestlist,currentCylinder,currentTime);

        if(closestRight==NULL&&closestLeft==NULL)
        {
        
            currentTime++; 
        }

        else if(direction==1 && closestRight!=NULL)
        {
            if(start==0)
                start=1;
            //printf("---right%d\n",closestRight->cylinder );
            closestRight->visited = 1;
            closestRight->exec_start = currentTime;
            currentTime+=abs(closestRight->cylinder-currentCylinder);
            
            (*totalBlockChange)+=abs(closestRight->cylinder-currentCylinder);
            temp=closestRight;
        }
        else if(direction==0 && closestLeft!=NULL)
        {   
            // printf("---left%d\n",closestLeft->cylinder );
            closestLeft->visited = 1;
            closestLeft->exec_start = currentTime;
            currentTime+=abs(closestLeft->cylinder-currentCylinder);
            
            (*totalBlockChange)+=abs(closestLeft->cylinder-currentCylinder);
            temp=closestLeft;
        }

        else
        {
            
            if(direction==1)
                {direction=0;}
            else if(direction==0)
                {direction=1;}
        }



    }

    (*averageWaitingTime) = averageWaiting(requestlist);
    (*stdWaitTime)= stdDeviation(requestlist,(*averageWaitingTime));
 
}

node* findLeftest(node *  requestlist, int currentTime)
{
    int finded=0; 
    node *temp = requestlist;
    node* closest = requestlist;
    int smallest=N+1;
    while(temp!=NULL)
    {
        if(!temp->visited && temp->cylinder<smallest && currentTime >= temp->arrival_time)
        {
            
            closest = temp;
            smallest = temp->cylinder;
            finded = 1;
            
        }
        if(temp->arrival_time>currentTime)
        {

            break;
        }
        temp = temp->next;
    }

    if(!finded){
        node* re = NULL;
        return re;
    }
    return closest;  
}

void clook(node *requestlist,int *totalBlockChange, double *averageWaitingTime,double *stdWaitTime){    //assuming we're 0 initial. So first comer is also included in calculation.
    node *temp  = requestlist;
    (*totalBlockChange) = 0;
    int startCylinder=1;
    int currentTime=0;
    int direction = 1; //1 for right, 0 for left
    int start = 0;
    node * closest1;
    node * leftest;
    int currentCylinder = 1;

    while(!allVisited(requestlist))
    {
        if(!start)
        {
           
            currentCylinder = 1;
        }
        else if(start)
        {
            currentCylinder = temp->cylinder;
        }
        
        closest1 = lookForRight(requestlist,currentCylinder,currentTime);
        leftest = findLeftest(requestlist,currentTime);

        if(closest1==NULL&&leftest==NULL)
        {
            
            currentTime++; 
        }

        else if(closest1!=NULL)
        {
            if(start==0)
                start=1;
            //printf("---right%d\n",closest1->cylinder );
            closest1->visited = 1;
            closest1->exec_start = currentTime;
            currentTime+=abs(closest1->cylinder-currentCylinder);
            
            (*totalBlockChange)+=abs(closest1->cylinder-currentCylinder);
            temp=closest1;
        }
        else if(leftest!=NULL)
        {   
            // printf("---restart%d\n",leftest->cylinder );
            leftest->visited = 1;
            leftest->exec_start = currentTime;
            currentTime+=abs(leftest->cylinder-currentCylinder);
            
            (*totalBlockChange)+=abs(leftest->cylinder-currentCylinder);
            temp=leftest;
        }

      
        


    }

    (*averageWaitingTime) = averageWaiting(requestlist);
    (*stdWaitTime)= stdDeviation(requestlist,(*averageWaitingTime));
 

}
