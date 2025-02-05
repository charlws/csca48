#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person_struct {
    char name[50];
    int age;
} Person;

typedef struct ListNode_struct {
    Person p;
    struct ListNode_struct *next;
} ListNode;

ListNode *NewListNode(ListNode *curNode, char name[], int age) {
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
    newNode->next = NULL;

    return newNode;
}

int main() {
    ListNode *parker = NewListNode(NULL, "Parker", 50);
    ListNode *thomas = NewListNode(parker, "Thomas", 100);
    ListNode *kathleen = NewListNode(thomas, "Kathleen", 60);

    ListNode *curNode = parker;
    while (curNode != NULL) {
        printf("%s, %d\n", (*curNode).p.name, (*curNode).p.age);
        curNode = (*curNode).next;
    }
    return 0;
}