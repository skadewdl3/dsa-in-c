#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct station 
{
    char name[25];
    int station_no;
    float distance;
    struct station *prev;
    struct station *next;
};
struct station PCMC, STN, BHOSARI, KASARWADI, PHUGEWADI ,DAPODI ,BOPODI ,KHADKI ,RANGE_HILL ,SHIVAJINAGAR, CIVIL_COURT, BP, MANDAI, SWARGATE;
struct station *head;
struct station *tail;
struct station *temp;
struct station *start_st;
struct station *end_st;
char start[25], end[25];

void to_UpperCase(char *str);
struct station *station_search(char *destination);
void assign_destinations(char *tart, char *end);
void print_route(char *start, char *end);
void travel(char *start, char *end);
void dist_fare(char *start, char *end);
int fare(float distance);

int main()
{
    strcpy(PCMC.name, "PCMC");
    PCMC.station_no = 0;
    PCMC.distance = 2;
    PCMC.prev = NULL;
    PCMC.next = &STN;

    strcpy(STN.name, "Sant Tukaram Nagar");
    STN.station_no = 1;
    STN.distance = 0.65;
    STN.prev = &PCMC;
    STN.next = &BHOSARI;
    
    strcpy(BHOSARI.name, "BHOSARI");
    BHOSARI.station_no=2;
    BHOSARI.distance = 1.5;
    BHOSARI.prev = &STN;
    BHOSARI.next = &KASARWADI;
    
    strcpy(KASARWADI.name, "KASARWADI");
    KASARWADI.station_no = 3;
    KASARWADI.distance = 1.1;
    KASARWADI.prev = &BHOSARI;
    KASARWADI.next = &PHUGEWADI;
    
    strcpy(PHUGEWADI.name, "PHUGEWADI");
    PHUGEWADI.station_no = 4;
    PHUGEWADI.distance = 0.8;
    PHUGEWADI.prev = &KASARWADI;
    PHUGEWADI.next = &DAPODI;
    
    strcpy(DAPODI.name , "DAPODI");
    DAPODI.station_no = 5;
    DAPODI.distance = 1.6;
    DAPODI.prev = &PHUGEWADI;
    DAPODI.next = &BOPODI;
    
    strcpy(BOPODI.name, "BOPODI");
    BOPODI.station_no = 6;
    BOPODI.distance = 1.4;
    BOPODI.prev = &DAPODI;
    BOPODI.next = &KHADKI;
    
    strcpy(KHADKI.name, "KHADKI");
    KHADKI.station_no = 7;
    KHADKI.distance = 1.4;
    KHADKI.prev = &BOPODI;
    KHADKI.next = &RANGE_HILL;

    strcpy(RANGE_HILL.name, "RANGE HILL");
    RANGE_HILL.station_no = 8;
    RANGE_HILL.distance = 5.5;
    RANGE_HILL.prev = &KHADKI;
    RANGE_HILL.next = &SHIVAJINAGAR;

    strcpy(SHIVAJINAGAR.name, "SHIVAJINAGAR");
    SHIVAJINAGAR.station_no = 9;
    SHIVAJINAGAR.distance = 1.4;
    SHIVAJINAGAR.prev = &RANGE_HILL;
    SHIVAJINAGAR.next = &CIVIL_COURT;

    strcpy(CIVIL_COURT.name, "CIVIL COURT");
    CIVIL_COURT.station_no = 10;
    CIVIL_COURT.distance = 1.7;
    CIVIL_COURT.prev = &SHIVAJINAGAR;
    CIVIL_COURT.next = &BP;

    strcpy(BP.name, "BP");
    BP.station_no = 11;
    BP.distance = 0.6;
    BP.prev = &CIVIL_COURT;
    BP.next = &MANDAI;

    strcpy(MANDAI.name, "MANDAI");
    MANDAI.station_no = 12;
    MANDAI.distance = 1.5;
    MANDAI.prev = &BP;
    MANDAI.next = &SWARGATE;

    strcpy(SWARGATE.name, "SWARGATE");
    SWARGATE.station_no = 13;
    SWARGATE.distance = 0;
    SWARGATE.prev = &MANDAI;
    SWARGATE.next = NULL;

    head = &PCMC;
    tail = &SWARGATE;

    int choice; 
    do
    {  
        printf("1. \n2. Fare\n3. Print Route\n4. Exit\n");
        scanf("%d%*c", &choice);
        switch(choice)
        {
            case 1:
                break;
            case 2:
                printf("Enter the starting station: ");
                scanf("%[^\n]%*c", start);
                printf("Enter the destination station: ");
                scanf("%[^\n]", end);
                dist_fare(start, end);
                break;
            case 3:
                printf("Enter the starting station:");
                scanf("%s", start);
                // gets(start);
                printf("Enter the destination station:");
                scanf("%s", end);
                // gets(end);
                print_route(start, end);
                break;
            case 4:
                exit(0);
        }
    }while(choice!=4);
    return 0;
}

void to_UpperCase(char *str)
{
    int i;
    for(i=0;str[i]!='\0';i++)
        if(str[i]>='a'&& str[i]<='z')
            str[i] = str[i]-32;
}

struct station *station_search(char *destination)
{
    to_UpperCase(destination);
    temp = head;
    while(temp!=NULL)
    {
        if(strcmp(temp->name, destination)==0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void assign_destinations(char *start, char *end)
{
    start_st = station_search(start);
    end_st = station_search(end);
}

void print_route(char *start, char *end)
{
    assign_destinations(start, end);
    temp = start_st;
    if(start_st->station_no < end_st->station_no)
    {
        while(temp!=end_st)
        {
            printf("%s ==> ", temp->name);
            temp = temp->next;
        }
        printf("%s", temp->name);
        printf("\n");
    }
    else if(start_st->station_no > end_st->station_no)
    {
        while(temp!=end_st)
        {
            printf("%s ==> ", temp->name);
            temp = temp->prev;
        }
        printf("%s", temp->name);
        printf("\n");
    }
    else
        printf("You are already at %s\n", start);
}

int fare(float distance)
{
    if (distance<=2)
        return 10;
    else if(distance>2 && distance<=4)
        return 20;
    else if(distance>4 && distance<=12)
        return 30;
    else if(distance>12 && distance<=18)
        return 40;
    else if(distance>18)
        return 50;
    else
        return 0;  
}

void dist_fare(char *start, char *end)
{
    int money = 0;
    float total_distance = 0;
    assign_destinations(start, end);
    temp = start_st;
    if(start_st->station_no < end_st->station_no)
    {
        printf("down case \n");
        while(temp!=end_st)
        {
            total_distance = total_distance + temp->distance;
            temp = temp->next;
        }
        printf("Distance = %.2f km\n", total_distance);
        money = fare(total_distance);
        printf("Fare = Rs %d\n", money);
    }
    else if(start_st->station_no > end_st->station_no)
    {
        printf("up case\n");
        while(temp!=end_st)
        {
            temp = temp->prev;
            total_distance = total_distance + temp->distance;
        }
        printf("Distance of your journey is %.2f\n", total_distance);
        money = fare(total_distance);
        printf("Fare = Rs %d\n", money);
    }
    else
        printf("You are already at %s\n", start);
}

// void travel(char start[], char end[])
// {
//     print_route(char start[], char end[]);
//     dist_fare(char start[], char end[]);
// }

/*
USE A MULTI DIMENSIONAL ARRAY TO STORE THE STATIONS

void creation(int j,char name1[][50])
{//printf("flag=5\n");
    head[j]=NULL;
     int i=0;
   for(i=0;i<size[j];i++)
    {
struct station *new;
new=(struct station*)malloc(sizeof(struct station));
strcpy(new->name,name1[i]);
new->number=i;
new->next=NULL;
new->right=NULL;
if(head[j]==NULL)
    {
        head[j]=new;
    }
else
    {

    temp=head[j];
    while(temp->right!=NULL)
        {
        temp=temp->right;
        }
        temp->right=new;


        }
    }
}
*/