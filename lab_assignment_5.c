#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char letter;
    struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
    int len = 0;
    if(head == NULL){
        return 0;
    }
    node* tmp = head;
    while(tmp->next != NULL){
        len++;
        tmp = tmp->next;
    }
    return len;
}

// parses the string in the linkedList
// if the linked list is head -> |a|->|b|->|c|
// then toCString function wil return "abc"
char* toCString(node* head)
{
    int len = length(head);
    char* output = malloc(sizeof(char)*(len+1));
    node* tmp = head;
    for(int i = 0; i <= len; i++){
        output[i] = tmp->letter;
        tmp = tmp->next;
    }
    output[len+1] = '\0';
    return output;
    
}

// inserts character to the linkedlist
// if the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
    
    node* tmp = *pHead;

    node* newNode = (node*)malloc(sizeof(node));
    newNode->letter = c;
    newNode->next = NULL;
    if((*pHead) == NULL){
        *pHead = newNode;
    }
    //traverse until end
    else{
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = newNode;
    }
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
    if(*pHead == NULL) {
        printf("exited line 70");
        return;
    }
    node* tmp = *pHead;

    if(tmp->next == NULL){
        free(tmp);
        printf("exited line 77");
        return;
    }

    node* tmp2 = tmp->next;
    if(tmp2 == NULL){
        free(tmp2);
        printf("exited line 84");
        return;
    }
    
    //traverse, deleting nodes along the way
    /*
    demo:
    STEP 1: head -> tmp -> tmp2 -> ...
    STEP 2: head -> FREED -> tmp -> tmp2 -> ...
    */
    while(tmp2->next != NULL){
        free(tmp);
        tmp = tmp2;
        tmp2 = tmp2->next;
    }
    
    //deallocate final nodes
    free(tmp);
    free(tmp2);
    *pHead = NULL;
    free(*pHead);
}

int main(void)
{
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt","r");
    fscanf(inFile, " %d\n", &numInputs);
    while (numInputs-- > 0)
    {
        fscanf(inFile, " %d\n", &strLen);
        for (i = 0; i < strLen; i++)
        {
            fscanf(inFile," %c", &c);
            insertChar(&head, c);
        }
        str = toCString(head);
        printf("String is : %s\n", str);
        free(str);
        deleteList(&head);
        if (head != NULL)
        {
            printf("deleteList is not correct!");
        }
    }
    fclose(inFile);
}

