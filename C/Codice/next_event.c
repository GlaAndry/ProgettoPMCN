#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#include "next_event.h"
#include "distributions.h"


//inizializza la struct state
void initialize_state(struct state *state) {
    if (state == NULL) {
        handle_error_with_exit("error in initialize state\n");
    }
    memset(state, 0, sizeof(struct state));
}

//inizializza la struct area
void initialize_area(struct area *area) {
    if (area == NULL) {
        handle_error_with_exit("error in initialize area\n");
    }
    memset(area, 0, sizeof(struct area));
}
//inizializza la struct node
void initialize_area(struct node *node) {
    if (node == NULL) {
        handle_error_with_exit("error in initialize area\n");
    }
    memset(noed, 0, sizeof(struct node));
}

/**
* Questo metodo genera un arrivo di un 
* Job all'interno del Server Cassa
*/
double get_interarrival_cassa(char task_type){
    
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in get_arrival\n");
    }

    const double mean[3] = {1 / ARRIVALONE, 1 / ARRIVALTWO, 1/ARRIVALTHREE};//mean exp=1/freq di arrivo 
    static double arrivals[3] = {START, START, START}; //{0,0,0} è inizializzato a 0
    double arrival;

    if(task_type == TASK_TYPE1) {//task gelato 1 gusto

        SelectStream(STREAM_ARR1);
        arrivals[0] += Exponential(mean[0]);
        arrival = arrivals[0];

    }else if(task_type == TASK_TYPE2) {//task gelato 2 gusti

        SelectStream(STREAM_ARR2);
        arrivals[1] += Exponential(mean[1]);
        arrival = arrivals[1];

    }else {//task gelato 3 gusti

        SelectStream(STREAM_ARR3);
        arrivals[2] += Exponential(mean[2]);
        arrival = arrivals[2];

    }

    return arrival;
}

/**
* Il metodo va a determinare qunato impiega un task per essere completato
* nella cassa.
*/
double get_service_cassa(char task_type){
    
    double service;
    if(task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {

        handle_error_with_exit("error in get_time_service_cassa\n");
    }

    if(task_type == TASK_TYPE1) {//il job è di tipo 1

        SelectStream(STREAM_SERV_CASSA1);//selezionare stream servizio1 
        service = Exponential((double)1 / SERVICEONE_CASSA);//genera servizio

    }else if(task_type == TASK_TYPE2) {//il job è di tipo 2

        SelectStream(STREAM_SERV_CASSA2);//seleziona stream servizio2 
        service = Exponential((double)1 / SERVICETWO_CASSA);//genera servizio

    }else {

        SelectStream(STREAM_SERV_CASSA3);//seleziona stream servizio3 
        service = Exponential((double)1 / SERVICETHREE_CASSA);//genera servizio

    }

    return service;
}

/**
* Il metodo va a determinare qunato impiega un task per essere completato
* nella cassa.
*/
double get_service_verifica(char task_type){
    
    double service;

    if(task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {

        handle_error_with_exit("error in get_time_service_verifica\n");
    }

    if (task_type == TASK_TYPE1) {//il job è di tipo 1
    
        SelectStream(STREAM_SERV_VERIFY1);//selezionare stream servizio1 
        service = Exponential((double)1 / SERVICEONE_VERIFY);//genera servizio

    }else if(task_type == TASK_TYPE2) {//il job è di tipo 2

        SelectStream(STREAM_SERV_VERIFY2);//seleziona stream servizio2 
        service = Exponential((double)1 / SERVICETWO_VERIFY);//genera servizio
    }else {

        SelectStream(STREAM_SERV_VERIFY3);//seleziona stream servizio3 
        service = Exponential((double)1 / SERVICETHREE_VERIFY);//genera servizio
    }

    return service;
}

/**
* Il metodo va a determinare qunato impiega un task per essere completato
* nella cassa.
*/
double get_service_delay(char task_type){
    
    double service;
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {

        handle_error_with_exit("error in get_time_service_delay\n");
    }

    if(task_type == TASK_TYPE1) {//il job è di tipo 1

        SelectStream(STREAM_SERV_DELAY1);//selezionare stream servizio1 
        service = Exponential((double)1 / SERVICEONE_DELAY);//genera servizio

    }else if(task_type == TASK_TYPE2) {//il job è di tipo 2

        SelectStream(STREAM_SERV_DELAY2);//seleziona stream servizio2 
        service = Exponential((double)1 / SERVICETWO_DELAY);//genera servizio

    }else {

        SelectStream(STREAM_SERV_DELAY3);//seleziona stream servizio3 
        service = Exponential((double)1 / SERVICETHREE_DELAY);//genera servizio

    }

    return service;
}

/**
* Il metodo va a determinare quanto impiega un task per essere completato
* nella cassa.
*/
double get_service_multiserver(char task_type){
    
    double service;

    if(task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {

        handle_error_with_exit("error in get_time_service_multiserver\n");

    }
    if(task_type == TASK_TYPE1) {//il job è di tipo 1

        SelectStream(STREAM_SERV_MULTISERVER1);//selezionare stream servizio1 
        service = Exponential((double)1 / SERVICEONE_MULTI);//genera servizio

    }else if(task_type == TASK_TYPE2) {//il job è di tipo 2

        SelectStream(STREAM_SERV_MULTISERVER2);//seleziona stream servizio2 
        service = Exponential((double)1 / SERVICETWO_MULTI);//genera servizio

    }else {

        SelectStream(STREAM_SERV_MULTISERVER3);//seleziona stream servizio3 
        service = Exponential((double)1 / SERVICETHREE_MULTI);//genera servizio

    }

    return service;
}


/**
* il metodo assegna il task al server di verifica andando
* ad impostare il tempo di completamento del task stesso
*/
void assign_task_to_verify(double time_current, char task_type, struct node **head,struct node **tail){

    double time_end_service = time_current + get_service_verifica(task_type);
    
    insert_ordered(time_end_service, task_type, time_current, head, tail);

    return;

}

/**
* il metodo assegna il task al server di delay andando
* ad impostare il tempo di completamento del task stesso.
*/
void assign_task_to_delay(double time_current, char task_type, struct node **head,struct node **tail){

    double time_end_service = time_current + get_service_delay(task_type);

    insert_ordered(time_end_service, task_type, time_current, head, tail);

    return;

}
/**
* il metodo assegna il task al multi-server andando
* ad impostare il tempo di completamento del task stesso
*/
void assign_task_to_multiserver(double time_current, char task_type, struct node **head,struct node **tail){

    double time_end_service = time_current + get_service_multiserver(task_type);

    insert_ordered(time_end_service, task_type, time_current, head, tail);

    return;

}

/**
* Ritorna INF se la lista dinamica è vuota,
* altrimenti ritorna l'istante di completamento della testa della lista,
* ossia l'istante del prossimo completamento
*/
double find_next_termination(struct node *head, char *task_type_termination) {//

    double end_service;

    if(head == NULL) {

        return INF;
    }

    if (task_type_termination == NULL) {

        handle_error_with_exit("error in fin_next_termination\n");

    }

    end_service = get_instant_end_service_from_linked_list(head, task_type_termination);
    
    return end_service;
}

/**
* Esegue l'update delle variabili all'interno della struttura AREA
* per il calcolo delle statistiche necessarie.
* area_tipo=(time_next-time_current)*popolazione_tipo
*/
void update_area(struct state state, struct area *area, double time_current,double time_next){

    if(area == NULL) {

        handle_error_with_exit("error in update area: area is NULL\n");
        
    }

    if(time_current > time_next) {

        handle_error_with_exit("error in update area: time_current > time_next\n");

    }

    if(time_current < 0) {

        handle_error_with_exit("error in update area: time_current < 0\n");

    }

    if(time_next < 0) {

        handle_error_with_exit("error in update area: time_next < 0\n");

    }

    //calcolo il numero di Job nel nodo della rete  ??(server + coda)??
    area -> number_node_cassa += (time_next - time_current) * (state.number_of_user_cassa);
    area -> number_node_verify += (time_next - time_current) * (state.number_of_user_verify);
    area -> number_node_delay += (time_next - time_current) * (state.number_of_user_delay);
    area -> number_node_multi += (time_next - time_current) * (state.number_of_user_multiserver);

    //calcolo il numero di Job nella coda
    area -> number_queue_cassa += (time_next - time_current) * (state.number_of_user_cassa - 1);
    area -> number_queue_verify += (time_next - time_current) * (state.number_of_user_verify - 1);
    area -> number_queue_delay += (time_next - time_current) * (state.number_of_user_delay - 1);
    area -> number_queue_multi += (time_next - time_current) * (state.number_of_user_multiserver - 1);

    //calcolo il numero di Job in servizio
    area -> number_service_cassa += (time_next - time_current); 

    return;
}

/**
* Aggiorna le variabili del sistema quando 
* c'è un arrivo di tipo 1, 2 o 3
*/
void update_state(char task_type, char location, struct state *state) {

    if(state == NULL) {

        handle_error_with_exit("error in update state\n");

    }

    if(task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {

        handle_error_with_exit("error in update state task_type\n");

    }

    if(location != DIRECT_CASSA && location != DIRECT_DELAY && location != DIRECT_MULTISERVER && location != DIRECT_VERIFY) {

        handle_error_with_exit("error in update state location\n");

    }

    int numberOfTaste = atoi(task_type);

    state->numberOfUsers ++; //ogni volta che arriva un Job aumentiamo il numero di utenti totali che il sistema serve.

    if(location == DIRECT_CASSA) { //arrivo task gelato 1 gusto verso cassa

        state->number_of_user_cassa++;

    }else if(location == DIRECT_VERIFY) {//task type 1 e diretto sul  cloud(non interrotto)

        state->number_of_user_cassa--;
        state->number_of_user_verify++;
        state->number_balls_icecream - numberOfTaste; //per il gelato 1 gusto tolgo solo una pallina di gelato.
           
    }else if(location == DIRECT_MULTISERVER){ //arrivo task gelato 1 gusto verso multiserver

        state->number_of_user_verify--;
        state->number_of_user_multiserver++;

    }else if(location == DIRECT_DELAY){

        state->number_of_user_verify--;
        state->number_of_user_delay++;
        state->number_balls_icecream = MAX_ICECREAM_TUB;

    }else {//task type 1 e non diretto sul cloud(non interrotto)

        handle_error_with_exit("error\n");

    }

    return;
}