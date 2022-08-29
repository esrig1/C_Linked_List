#include <stdio.h>
#include <stdlib.h>

// struct definitions
typedef struct NODE {int data; struct NODE* next;} NODE; // nodes of the linked list
typedef struct LINKED_LIST {struct NODE *head;} LINKED_LIST; // struct to act as the head of the list


// ***************************************
// *** provided functions  ****************
// ***************************************

// this function returns a LINKED_LIST struct to
// act as the head of the linked list.
LINKED_LIST Create_List(void) {LINKED_LIST list = {NULL}; return list;}

void Verify_Malloc(NODE *node) {if (node == NULL) {printf("Malloc Failed\n"); exit(1);} return;}

// this function prints out all of the nodes in the linked list
void Print_List(FILE *out, LINKED_LIST list) {
    if (list.head == NULL) {printf("\n"); return;} //empty list
    NODE *current = list.head;
    while (current->next != NULL) {
        fprintf(out, "%d -> ",current->data);
        current = current->next;
    }
    fprintf(out, "%d\n",current->data);
    return;
}

// this function returns the number 
// of elements in the linked list
int Size(LINKED_LIST list){
    NODE* head = list.head;
    int count = 0;
    while(head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// this function adds an element to
// the front of the list
void Push_Front(LINKED_LIST *list, int data){
    struct NODE* newNode;
    newNode = malloc(sizeof(struct NODE));
    Verify_Malloc(newNode);
    newNode->data = data;
    newNode->next = NULL;
    if(list->head == NULL) {
        list->head = newNode;
        newNode->next = NULL;
        return;
    }
    
    struct NODE* tempHead = list->head;
    newNode->next = tempHead;
    list->head = newNode;
    return;
}

// this function adds an element 
// to the end of the linked list 
void Push_Back(LINKED_LIST *list, int data) {
    struct NODE* newNode;
    newNode = malloc(sizeof(struct NODE));
    Verify_Malloc(newNode);
    newNode->data = data;
    newNode->next = NULL;
    if(list->head == NULL) {
        list->head = newNode;
        return;
    }
    struct NODE* end = list->head;
    while(end->next != NULL) {
      end = end->next;
    }
    end->next = newNode;
    return;
}


// if the list is not empty
// the value of the first element of the list is returned by reference in the parameter data
// the first element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Front(LINKED_LIST *list, int *data) {
    if(list->head == NULL) {
    return 0;
    }
    struct NODE* head = list->head;
    int num = head->data;
    *data = num;
    struct NODE* newHead = head->next;
    free(head);
    list->head = newHead;
    return 1;
}


// if the list is not empty
// the value of the last element of the list is returned by reference in the parameter data
// the last element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Back(LINKED_LIST *list, int *data) {
   struct NODE* ndLast = list->head;
   if(ndLast == NULL){
     return 0;
   }
   while(ndLast->next->next != NULL) {
     ndLast = ndLast->next;
   }
   struct NODE* last = ndLast->next;
   *data = last->data;
   free(last);
   ndLast->next = NULL;
   return 1;
   
   
}

// this function returns the number 
// of times that the value of the parameter 
// data appears in the list
int Count_If(LINKED_LIST list, int data) {
    struct NODE* head = list.head;
    int count = 0;
    while(head != NULL) {
      if(head->data == data) {
        count+=1;
      }
      head = head->next;
    }
    return count;
}

// delete the first node containing the data value
// return 1 if something was deleted otherwise 0
// remember to free the deleted node
int Delete(LINKED_LIST *list, int data) {
    NODE* head = list->head;
    NODE* prev;
    int* temp;
    if(head->data == data) { //if front element contains data, remove
      list->head = head -> next;
      free(head);
      return 1;
    }
    
    while(head->next != NULL) {
        if(head->data == data) {
          break;
        }
      prev = head;  
      head = head->next;
    }
    if(head->next == NULL && head->data != data){ //if loop has iterated to last node, and it doesn't match data. Returns 0
      return 0;
    }
    prev->next = head->next;
    free(head);
    return 1;
}

// return 1 if the list is empty otherwise returns 0
int Is_Empty(LINKED_LIST list) {
    if(list.head == NULL) {
      return 1;
    }
    return 0;
}

// delete all elements of the list
// remember to free the nodes
void Clear(LINKED_LIST *list) {
    NODE* head = list->head;
    NODE* next = NULL; 
    while(head != NULL) {
      next = head ->next;
      free(head);
      head = next;
    }
    list->head = NULL;
}


// if an element appears in the list 
// retain the first occurance but
// remove all other nodes with the same 
// data value
void Remove_Duplicates(LINKED_LIST *list) {
      NODE* head = list->head;
      NODE* temp;
      NODE* remove;
      while(head != NULL && head->next != NULL) {
        temp = head;
        while(temp->next != NULL) {
          if(head->data == temp->next->data) {
            remove = temp->next;
            temp->next = remove->next;
            free(remove);
            continue;
          }
          temp = temp->next;
        }
        head = head->next;
      }
    }
    


// tests for function
int main() {
    // create a linked list
    printf("creating linked list\n");
    LINKED_LIST list = Create_List();
   
    // add some data (hardcoded for testing)
    printf("hardcoding some data\n");
    NODE *first  = malloc(sizeof(NODE)); Verify_Malloc(first);
    NODE *second = malloc(sizeof(NODE)); Verify_Malloc(second);
    first->data  = 1;
    second->data = 2;
    list.head = first;
    first->next = second;
    second->next = NULL;
    // print the list
    printf("Testing Print_List\n");
    Print_List(stdout, list);
    // write a better test for Size
    printf("Testing Size\n");
    printf("size = %d\n",Size(list));
    // write a better test for Push_Front
    printf("Testing Push_Front\n");
    Push_Front(&list, 0);
    Print_List(stdout, list);
    
    // write a better test for Push_Back
    printf("Testing Push_Back\n");
    Push_Back(&list, 3);
    Print_List(stdout, list);
    // write a better test for Pop_Front
    printf("Testing Pop_Front\n");
    {
        int x; 
        int not_empty = Pop_Front(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }
    // write a better test for Pop_Back
    printf("Testing Pop_Back\n");
    {
        int x; 
        int not_empty = Pop_Back(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    Push_Front(&list, 5);
    Push_Front(&list, 5);
    Print_List(stdout, list);
    printf("5 count = %d\n",Count_If(list, 5));
    
    // write a test for Delete 
    printf("Testing Delete\n");
    Print_List(stdout, list);
    Delete(&list, 5); 
    Print_List(stdout, list);

    printf("Testing Is_Empty\n");
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\
n");
    

    Clear(&list);
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\
n");

    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 2);
    Push_Back(&list, 2);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Remove_Duplicates(&list);
    Print_List(stdout, list);
    return 0;
}
