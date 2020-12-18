#include "basic.h"
#ifndef LINE_H
#define LINE_H
struct node  {//struttura di un nodo della lista dinamica ordianta
    double instant_end_service;
    char task_type;//tipo di job:1, 2 o 3
    double time_arrive;//istante di arrivo del job
    struct node* next;//puntatore al prossimo
    struct node* prev;//puntatore al precedente
};
#endif
void insert_first(struct node *new_node, struct node **head, struct node **tail);//inserisce il primo nodo

void insert_at_tail(struct node *new_node,struct node**head,struct node** tail);//inserisce un nodo in coda

//alloca e inizializza un nodo della lista dinamica ordinata
struct node* get_new_node(double instant_service,char task_type,double time_arrive);

void remove_after_node(struct node**ppos,struct node**tail);
void remove_prev_node(struct node**pprev,struct node**head);
void insert_at_head(struct node* new_node,struct node** head,struct node** tail);//inserisce un nodo in testa alla lista

char first_is_smaller(struct node node1, struct node node2);//verifica se il primo nodo contiene tempi più piccoli del secondo nodo

void insert_ordered(double instant_service,char task_type,double time_arrive, struct node** head, struct node** tail);
//inserisce ordinatamente un nodo nella lista ordinata per istanti temporali


int count_element_linked_list(struct node*head);
double get_instant_end_service_from_linked_list(struct node*head,char*task_type_termination);
//int delete_head(struct node** head);
int delete_head(struct node** head,double *time_arrive,double *time_lost_in_cloudlet);