/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;


void add_node (node_t **head){

    node_t *temp1, *temp2;
    
    temp1 = (node_t *) malloc(sizeof (node_t));
    if(!temp1){
        printf("\nError: malloc failed\n");
        return;
    }else{
        temp1->next = NULL;
    }

    printf("\nEnter the value of the node: ");
    scanf("%d", &(temp1->data));
 
    temp2 = *head;
    if(!temp2){
        *head = temp1;
    }else{
        while(temp2->next)
            temp2 = temp2->next;
        temp2->next = temp1;
    }

    printf("\nNode %d added to the List\n", temp1->data);

}

void delete_node (node_t **head){

    if(!*head){
        printf("\nList is Empty\n");
        return;
    }

    int data;
    printf("\nEnter the node to be deleted: ");
    scanf("%d", &data);
    
    node_t *temp1, *temp2;

    temp1 = (node_t *) *head;
    while(temp1){
        if(temp1->data != data){
            temp2 = temp1;
            temp1 = temp1->next;
            continue;
        }
        
        if (*head == temp1){
            *head = temp1->next;
        }else{
            temp2->next = temp1->next;
        }
        
        temp1->next = NULL;
        free(temp1);
        
        printf("\nNode %d deleted from the List\n", data);
        return;
    }
    
    printf("\nNode %d not found in the List\n", data);
 
}
    
void display_list (node_t *head){

    printf("\nList is : ");

    while(head){
        printf("%d -> ", head->data);
        head = head->next;
    }
    
    printf("NULL\n");
}

void clean_up (node_t **head){
    
    node_t *temp;

    while(*head){
        temp = *head;
        *head = (*head)->next;

        temp->next = NULL;
        printf("\nNode %d deleted from the List", temp->data);
        free(temp);
    }
    
}

void make_loop (node_t **head){

    if(!*head){
        printf("\nList is Empty\n");
        return;
    }

    node_t *temp1, *temp2;
    int node, count = 1;

    temp1 = (node_t *) *head;
    while(temp1->next){
        count++;
        temp1 = temp1->next;
    }
    
    printf("\nEnter the node location to make the loop: ");
    scanf("%d", &node);
    printf("Total Nodes = %d and requested Loop Node = %d", count, node);

    if (node > count){
        printf("Error : Total Nodes = %d and requested Loop Node = %d", count, node);
        return;
    }

    temp2 = (node_t *) *head;
    while(--node)
       temp2 = temp2->next;
    
    temp1->next = temp2;

    printf("\nLoop created from %d to %d\n", temp1->data, temp2->data);
}

void find_and_remove_loop (node_t *head){

    if(!head){
        printf("\nList is Empty\n");
        return;
    }

    node_t *slow, *fast;
    slow = fast = head;
    
    while (fast && fast->next){

        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast){
            break;
        }

    }

    if(!(fast && fast->next)){
        printf("\nNo loop found\n");
        return; 
    }
    
    while(slow->next != head){
        if(slow->next == fast)
            head = head->next;
        
        slow = slow->next;
    }
    slow->next = NULL;

    printf("\nLoop from %d to %d removed\n", slow->data, head->data);
}

int main()
{
    node_t *head = NULL;
    int choice;
    
    while(1){
        printf("\nMenu: \n");
        printf("1. Add Node\n");
        printf("2. Delete Node\n");
        printf("3. Display List\n");
        printf("4. Make Loop\n");
        printf("5. Remove Loop\n");
        printf("6. Exit\n");
        printf("\nEnter Choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                add_node(&head);
                break;
            case 2:
                delete_node(&head);
                break;
            case 3:
                display_list(head);
                break;
            case 4:
                make_loop(&head);
                break;
            case 5:
                find_and_remove_loop(head);
                break;
            case 6:
                clean_up(&head);
                goto end;            
            default:
            printf("\nInvalid choice\n");
                break;            
        }

    }
    
    end:
    return 0;
}

