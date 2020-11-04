#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#include "dynamic_list.h"
#include <string.h>

void initialize_state(struct state*state);
void initialize_area(struct area*area);
void initialize_node(struct node *node);


double get_interarrival_cassa(char task_type);


double get_service_cassa(char task_type);
double get_service_delay(char task_type);
double get_service_verifica(char task_type);
double get_service_multiserver(char task_type);

double find_next_termination(struct node *head, char *task_type_termination);

//assegnamento dei task alle altre code

void assign_task_to_cassa(double time_current, char task_type, struct node **head,struct node **tail);
void assign_task_to_verify(double time_current, char task_type, struct node **head,struct node **tail);
void assign_task_to_delay(double time_current, char task_type, struct node **head,struct node **tail);
void assign_task_to_multiserver(double time_current, char task_type, struct node **head,struct node **tail);


//funzioni di update
void update_area(struct state state, struct area *area, double time_current,double time_next);
void update_state(char task_type, char location, struct state *state);