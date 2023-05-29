#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *link;
}node;

int count_of_nodes(node *head){
    if(head->link==NULL){
        return 1;
    }
    else{
        return 1 + count_of_nodes(head->link);
    }
}

void print_data(node *head){
    if(head->link==NULL){
        printf("%d\n", head->data);
    }
    else{
        printf("%d ", head->data);
        print_data(head->link);
    }
}

node* insertAtEnd(node *head, int data){
    if (head->link==NULL)
    {
        node *new = malloc(sizeof(node));
        new->data = data;
        new->link=NULL;
        head->link = new;
        return new;
    }
    else{
        return insertAtEnd(head->link, data);
    }
}

node* insertAtBeginning(node* head, int data){
    node* temp = malloc(sizeof(node));
    temp->data = data;
    temp->link = head;
    return temp;
}

node* insertAtIndex(node* head, int data,int index){
    int count = count_of_nodes(head);
    if (index==0){
        return insertAtBeginning(head, data);
    }
    else if(index == count){
        insertAtEnd(head, data);
        return head;
    }
    else if (index < 0 || index > count)
    {
        printf("Out of index\n");
        return head;
    }
    else{
        node* ptr = head;
        node* new = malloc(sizeof(node));
        new->data = data;
        int cont = 1;
        while(cont<index){
            ptr = ptr->link;
            cont++;
        }
        new->link = ptr->link;
        ptr->link = new;
        return head;
    }
    

}

node* deleteFirst(node* head){
    if(head==NULL){
        printf("Empty List!");
    }
    else if(head->link == NULL){
        free(head);
        head = NULL;
    }
    else{
        node* temp = head;
        head = head->link;
        free(temp);
        temp=NULL;
    }
    return head;
}

node* deleteLast(node* head){
    if(head==NULL){
        printf("Empty List!");
    }
    else if(head->link == NULL){
        free(head);
        head == NULL;
    }
    if (head->link->link==NULL)
    {
        //node* temp = head->link;
        free(head->link);
        //temp=NULL;
        head->link = NULL;
        return head;   
    }
    else{
        deleteLast(head->link);
    }
    return head;
}

node* deleteAtIndex(node* head, int index){
    int count = count_of_nodes(head);
    if (index==0){
        return deleteFirst(head);
    }
    else if(index == count){
        return deleteLast(head);
    }
    else if (index < 0 || index > count)
    {
        printf("Out of index\n");
        return head;
    }
    else{
        node* ptr = head;
        int cont = 1;
        while(cont<index){
            ptr = ptr->link;
            cont++;
        }
        node* temp = ptr->link;
        ptr->link = ptr->link->link;
        free(temp);
        temp = NULL;
        return head;
    }
    

}


int main(){

    node *head = malloc(sizeof(node));
    head->data = 45;
    head->link= NULL;
    
    node *ptr = head;
    ptr = insertAtEnd(ptr, 98);

    ptr = insertAtEnd(ptr, 3);

    ptr = insertAtEnd(ptr, 18);
    head = insertAtBeginning(head, 55);
    print_data(head);
    ptr = insertAtIndex(head, 64, 1);
    print_data(head);
    head = deleteFirst(head);
    print_data(head);
    head = deleteLast(head);
    print_data(head);
    head = deleteAtIndex(head,2);
    printf("%d\n",count_of_nodes(head));
    print_data(head);
    free(head);
    return 0;
}