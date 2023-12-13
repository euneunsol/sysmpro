#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void enqueue(struct node **front, struct node **rear, int data);
int dequeue(struct node **front, struct node **rear);
void printQueue(struct node *front);

int main() {
    struct node *front = NULL;
    struct node *rear = NULL;
    int data;

    while (1) {
        if (scanf("%d", &data) == 1) {
            enqueue(&front, &rear, data);
        } else {
            printQueue(front);
            break;
        }
    }

    return 0;
}

void enqueue(struct node **front, struct node **rear, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = NULL;

    if (*rear == NULL) {
        *front = *rear = newNode;
    } else {
        (*rear)->next = newNode;
        *rear = newNode;
    }
}

int dequeue(struct node **front, struct node **rear) {
    if (*front == NULL) {
        printf("Queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    struct node *temp = *front;
    int dequeuedValue = temp->data;

    *front = temp->next;
    if (*front == NULL) {
        *rear = NULL;
    }

    free(temp);
    return dequeuedValue;
}

void printQueue(struct node *front) {
    if (front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Print queue\n");
    while (front != NULL) {
        printf("%d\n", front->data);
        front = front->next;
    }
    //printf("\n");
}

