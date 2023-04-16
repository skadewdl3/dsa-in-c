#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 4

int queue[MAX];
int front = -1;
int rear = -1;

void insert() {
    int element;
    if ((rear+1)%MAX == front) {
        printf("full ");
       
    }
    else {
        if (front == -1) {
            front = 0;
        }
        scanf("%d", &element);
        rear = (rear+1)%MAX;
        queue[rear] = element;
        
    }
}

void delete() {
    int element;
    if (front == -1 &&  rear == -1) {
        printf("empty ");
        
    }
    else {
        element = queue[front];
        printf("%d ",element);
        front=(front+1)%MAX;
         
        
    }
}

void display() {
    int i;
    if (front == -1) {
        printf("empty ");
        
    }
    else {
        for (i = front; i <= rear; i++) {
            printf("%d  ", queue[i]);
        }
        
    }
}


void isFull() {
    if ((rear+1)%MAX == front) {
        printf("full ");
    }
    }

void isEmpty() {
    if (front == -1) {
        printf("empty ");
    }
}

int main() {
    int choice;
    while (1) {
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                insert();
                break;
            case 2:
                delete();
                break;
            case 3:
                display();
                break;
                case 4:
                printf("%d ",queue[rear]);
                break;
             case 5:
                printf("%d ",queue[front]);
                break;
            case 6:
                isFull();
                break;
            case 7:
                isEmpty();
                break;
            case 8:
                exit(0);
            default:
                printf("Error");
        }
    }
    return 0;
}