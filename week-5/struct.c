#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person_struct {
    char name[50];
    int age;
} Person;

typedef struct ListNode_struct {
    Person p;
    struct ListNode_struct *previous;
    struct ListNode_struct *next;
} ListNode;

// takes in current node address, create new node and list current node to new node
// return new node address
ListNode *NewListNode(ListNode *curNode, const char name[], const int age) {
    ListNode *newNode = NULL;
    newNode = (ListNode *)calloc(1, sizeof(ListNode));
    if (newNode == NULL) {
        printf("Failed to reserve memory.");
        return NULL;
    }

    if (curNode != NULL) {
        curNode->next = newNode;
    }
    strcpy((newNode->p).name, name);
    (newNode->p).age = age;
    newNode->previous = curNode;
    newNode->next = NULL;

    return newNode;
}

// takes in name
// return the list node matching the name
ListNode *FindListNode(ListNode *head, const char name[]) {
    ListNode *cur = head;
    while (cur != NULL) {
        if (strcmp((*cur).p.name, name) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// takes in node to delete
// relink previous node
void DeleteListNode(ListNode *node) {
    if (node->previous != NULL) {
        (node->previous)->next = node->next;
    }
    if (node->next != NULL) {
        (node->next)->previous = node->previous;
    }
    free(node);
}

int main() {
    const char name[10][10] = {"Parker", "Thomas", "Kathleen", "Rawd", "Purva", "Paco"};
    const int age[10] = {20, 30, 40, 30, 30, 50};
    const int size = 6;

    ListNode *head = NewListNode(NULL, "HEAD", -1);

    ListNode *cur = head;
    for (int i = 1; i < size; i++) {
        cur = NewListNode(cur, name[i], age[i]);
    }

    printf("Initial list\n");
    cur = head->next;
    while (cur != NULL) {
        printf("%s, %d\n", (*cur).p.name, (*cur).p.age);
        cur = (*cur).next;
    }

    printf("\nFind purva\n");
    ListNode *purva = FindListNode(head, "Purva");
    printf("Purva is at %p\n", purva);
    printf("%s, %d\n", purva->p.name, purva->p.age);

    printf("\nNew list after deleting purva\n");
    DeleteListNode(purva);
    cur = head->next;
    while (cur != NULL) {
        printf("%s, %d\n", (*cur).p.name, (*cur).p.age);
        cur = (*cur).next;
    }

    printf("\nTry to get purva again?\n");
    printf("%s, %d\n", purva->p.name, purva->p.age);

    return 0;
}