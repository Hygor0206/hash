#include <stdlib.h>
#include <stdio.h>

typedef struct sNode{
    struct sNode *prev;
    struct sNode *next;
    int data;
} Node;

typedef struct sList{
    struct sNode* head;
    struct sNode* tail;
    int size;
} List;

Node* createNode(int);
List* createList();
int emptyList(List*);
void errors(int);
void insertNode(List*, Node*, int);
void removeNode(List*, Node*);
void search(List*, Node*);
void readList(List*);

int main(){
    List* myList;
    myList = createList();

    insertNode(myList, NULL, 10);
    readList(myList); 
    insertNode(myList, myList->head, 15);
    readList(myList); 
    insertNode(myList, myList->tail, 25);
    readList(myList); 
    insertNode(myList, NULL, 5);
    insertNode(myList, myList->tail, 35);
    readList(myList); 
}

Node* createNode(int data){
    Node* new;
    new = (Node*) malloc(sizeof(Node));
    if(new!=NULL){
        new->data = data;
        new->prev = NULL;
        new->next = NULL;
    }
}

List* createList(){
    List* list;
    list=(List*)malloc(sizeof(List));
    if(list!=NULL){
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}

int emptyList(List* list){
    if(list->size==0)
        return 1;
    return 0;
}

void errors(int error){
    if(error == -1)
        printf("List Underflow");
    else if(error == -2){
        printf("End of the list");
    }
}

void insertNode(List* list, Node* node, int data){
    Node* new_element;
    Node* element;
    new_element = createNode(data);

    if(node==NULL){
        if(emptyList(list)){
            list->tail=new_element;
        }else{
            element = list->head;
            element->prev = new_element;
        }
    
        new_element->next=list->head;
        list->head=new_element;
    }else{
        if(node->next==NULL){
            list->tail=new_element;
        }else{
            element=node->next;
            element->prev=new_element;
        }
            
        new_element->next=node->next;
        new_element->prev=node;
        node->next=new_element;
    }
    list->size++;
}

void removeNode(List* list, Node* node){
    Node* old_element;
    Node* element;

    if(emptyList(list))
        errors(-1);
    
    if(node==NULL){
        old_element = list->head;
        element= old_element->next;
        
        if(list->head == NULL)
            list->tail=NULL;
    }else{
        if(node->next==NULL)
            errors(-2);
        
        old_element = node->next;
        node->next=old_element->next;
        element=old_element->next;

        if(element!=NULL)
            element->prev=node;
        else
            list->tail=node;    
    }
    free(old_element);
    list->size--;
}

void readList(List* list){
    Node* node;

    if(emptyList(list))
        errors(-1);
    else{
        printf("\nElements da Lista: \n");
        node = list->head;
        while(node!=NULL){
            printf("%i, ", node->data);
            node = node->next;
        }
    }
    
}