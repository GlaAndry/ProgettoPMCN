#include "dynamic_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//conta gli elementi nella lista dinamica
int count_element_linked_list(struct node*head){
    int count=0;
    if (head==NULL){
        handle_error_with_exit("head is NULL\n");
    }
    struct node *p=head;
    while(p!=NULL){
        count++;
        p=p->next;
    }
    return count;
}

//ottiene istante fine servizio del nodo,e informazioni riguardo al task:tipo
double get_instant_end_service_from_linked_list(struct node*head,char*task_type_termination){
    if(head==NULL){
        handle_error_with_exit("linked list is empty\n");
    }
    struct node*p=head;
    *task_type_termination=p->task_type;
    return p->instant_end_service;
}

//rimuovi il nodo a cui punta il puntatore a nodo(*pos),*pos deve essere un puntatore next appartenente ad un nodo valido
void remove_after_node(struct node**ppos,struct node**tail){
    if(ppos==NULL || tail==NULL){
        handle_error_with_exit("error in remove_after_node\n");
    }
    if(*ppos==NULL || *tail==NULL){
        handle_error_with_exit("impossible remove node,empty list\n");
    }
    struct node *r = *ppos;
    struct node*q=r->next;
    if(q==NULL){//fine della lista,bisogna aggiornare la coda
        *ppos=r->next;
        *tail=r->prev;
        free(r);
    }
    else {
        q->prev = r->prev;
        *ppos = r->next;
        free(r);
    }
    return;
}

//rimuovi il nodo a cui punta il puntatore a nodo(*pos),*pos deve essere un puntatore prev appartenente ad un nodo valido
void remove_prev_node(struct node**pprev,struct node**head){
    if(pprev==NULL || head==NULL){
        handle_error_with_exit("error in remove_after_node\n");
    }
    if(*pprev==NULL || *head==NULL){
        handle_error_with_exit("impossible remove node,empty list\n");
    }
    struct node *r = *pprev;
    struct node*q=r->prev;
    if(q==NULL){//fine della lista,bisogna aggiornare la testa
        *pprev=r->prev;
        *head=r->next;
        free(r);
    }
    else {
        q->next = r->next;
        *pprev = r->prev;
        free(r);
    }
    return;
}

//rimuove il primo elemento dalla lista dinamica,non è importante il valore iniziale di head
int delete_head(struct node** head,double *time_arrive){
    if(head==NULL || time_arrive==NULL){
        handle_error_with_exit("error in delete head\n");
    }
    if(*head == NULL){//nessuna testa da eliminare
        return -1;
    }
    if ((*head)-> next == NULL){//c'è un solo nodo in lista
        *time_arrive=(*head)->time_arrive;
        free(*head);
        *head = NULL;
    }else{
        struct node*temp=(*head)->next;
        *time_arrive=(*head)->time_arrive;
        free(*head);
        *head=temp;
        (*head)-> prev = NULL;
    }
    return 0;
}

//inserisce il primo nodo nella lista
void insert_first(struct node *new_node, struct node **head, struct node **tail){
    if(new_node==NULL || head==NULL || tail==NULL){
        handle_error_with_exit("error in insert_first\n");
    }
    *head = new_node;
    *tail = new_node;
    return;
}

//inserisce un nodo in coda
void insert_at_tail(struct node *new_node,struct node**head,struct node** tail){
    if(head==NULL){
        handle_error_with_exit("error in insert_at_head **head is NULL\n");
    }
    if(tail==NULL){
        handle_error_with_exit("error in insert_at_head **tail is NULL\n");
    }
    if(*head == NULL) {
        insert_first(new_node, head, tail);
        return;
    }
    (*tail)->next = new_node;
    new_node->prev = *tail;
    *tail = new_node;
}


//alloca e inizializza un nodo della lista dinamica ordinata
struct node* get_new_node(double instant_end_service,char task_type,double time_arrive) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if(new_node==NULL){
        handle_error_with_exit("error in malloc get_new_node\n");
    }
    new_node->instant_end_service = instant_end_service;
    new_node->task_type=task_type;
    new_node->time_arrive=time_arrive;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}


void insert_at_head(struct node* new_node,struct node** head,struct node** tail) {//inserisce un nodo in testa alla lista
    if(head==NULL){
        handle_error_with_exit("error in insert_at_head **head is NULL\n");
    }
    if(tail==NULL){
        handle_error_with_exit("error in insert_at_head **tail is NULL\n");
    }
    if(*head == NULL) {
        insert_first(new_node, head, tail);
        return;
    }
    (*head)->prev = new_node;
    new_node->next = *head;
    *head = new_node;
    return;
}

//verifica se il primo nodo contiene tempi più piccoli del secondo nodo
char first_is_smaller(struct node node1, struct node node2){
    if(node1.instant_end_service>=node2.instant_end_service){
        return 0;
    }
    return 1;
}

//inserisce ordinatamente un nodo nella lista ordinata per istanti temporali,partendo dalla coda
void insert_ordered(double instant_end_service,char task_type,double time_arrive, struct node** head, struct node** tail){
    struct node* temp = *tail;
    struct node* next_node = NULL;
    struct node* new_node = get_new_node(instant_end_service,task_type,time_arrive);
    if(head==NULL || tail==NULL){
        handle_error_with_exit("error in insert_ordered,head or tail are NULL\n");
    }
    if(*head == NULL){
        insert_first(new_node, head, tail);
        return;
    }
    if(first_is_smaller((**tail),*new_node)){
        insert_at_tail(new_node,head, tail);
    }else{
        while(!first_is_smaller(*temp,*new_node)){
            if(temp->prev != NULL){
                temp = temp->prev;
            }else{
                insert_at_head(new_node, head, tail);
                return;
            }
        }
        next_node = temp->next;
        new_node->prev = temp;
        new_node->next = next_node;
        temp->next = new_node;
        next_node->prev = new_node;
    }
    return;
}