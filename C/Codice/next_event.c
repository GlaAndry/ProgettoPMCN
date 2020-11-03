#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#include "next_event.h"
#include "distributions.h"



void initialize_state(struct state *state) {//inizializza la struct state
    if (state == NULL) {
        handle_error_with_exit("error in initialize state\n");
    }
    memset(state, 0, sizeof(struct state));
}

void initialize_node(struct node *node) {//inizializza la struct state
    if (node == NULL) {
        handle_error_with_exit("error in initialize state\n");
    }
    memset(node, 0, sizeof(struct node));
}

void initialize_area(struct area *area) {//inizializza la struct area
    if (area == NULL) {
        handle_error_with_exit("error in initialize area\n");
    }
    memset(area, 0, sizeof(struct area));
}


double get_interarrival_cassa(char task_type){
    /**
     * Questo metodo genera un arrivo di un 
     * Job all'interno del Server Cassa
     */
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in get_arrival\n");
    }
    const double mean[3] = {1 / ARRIVALONE, 1 / ARRIVALTWO, 1/ARRIVALTHREE};//mean exp=1/freq di arrivo 
    static double arrivals[3] = {START, START, START}; //{0,0,0} è inizializzato a 0
    double arrival;
    if (task_type == TASK_TYPE1) {//task gelato 1 gusto
        SelectStream(STREAM_ARR1);
        arrivals[0] += Exponential(mean[0]);
        arrival = arrivals[0];
    } else if(task_type == TASK_TYPE2) { //task gelato 2 gusti
        SelectStream(STREAM_ARR2);
        arrivals[1] += Exponential(mean[1]);
        arrival = arrivals[1];
    }
    else {//task gelato 3 gusti
        SelectStream(STREAM_ARR3);
        arrivals[2] += Exponential(mean[2]);
        arrival = arrivals[2];
    }
    return arrival;
}

double get_service_cassa(char task_type){
    /**
     * Il metodo va a determinare qunato impiega un task per essere completato
     * nella cassa.
     */
    double service;
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in get_time_service_cassa\n");
    }
    if (task_type == TASK_TYPE1) {//il job è di tipo 1
        SelectStream(STREAM_SERV_CASSA1);//selezionare stream servizio1 
        service = Exponential((double)1 / SERVICEONE_CASSA);//genera servizio
    } else if(task_type == TASK_TYPE2) {//il job è di tipo 2
        SelectStream(STREAM_SERV_CASSA2);//seleziona stream servizio2 
        service = Exponential((double)1 / SERVICETWO_CASSA);//genera servizio
    } else {
        SelectStream(STREAM_SERV_CASSA3);//seleziona stream servizio3 
        service = Exponential((double)1 / SERVICETHREE_CASSA);//genera servizio
    }

    return service;
}

double get_service_verifica(char task_type){
    /**
     * Il metodo va a determinare qunato impiega un task per essere completato
     * nella cassa.
     */
    double service;
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in get_time_service_verifica\n");
    }
    if (task_type == TASK_TYPE1) {//il job è di tipo 1
        SelectStream(STREAM_SERV_VERIFY1);//selezionare stream servizio1 
        service = Exponential((double)1 / SERVICEONE_VERIFY);//genera servizio
    } else if(task_type == TASK_TYPE2) {//il job è di tipo 2
        SelectStream(STREAM_SERV_VERIFY2);//seleziona stream servizio2 
        service = Exponential((double)1 / SERVICETWO_VERIFY);//genera servizio
    } else {
        SelectStream(STREAM_SERV_VERIFY3);//seleziona stream servizio3 
        service = Exponential((double)1 / SERVICETHREE_VERIFY);//genera servizio
    }

    return service;
}

double get_service_delay(char task_type){
    /**
     * Il metodo va a determinare qunato impiega un task per essere completato
     * nella cassa.
     */
    double service;
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in get_time_service_delay\n");
    }
    if (task_type == TASK_TYPE1) {//il job è di tipo 1
        SelectStream(STREAM_SERV_DELAY1);//selezionare stream servizio1 
        service = Exponential((double)1 / SERVICEONE_DELAY);//genera servizio
    } else if(task_type == TASK_TYPE2) {//il job è di tipo 2
        SelectStream(STREAM_SERV_DELAY2);//seleziona stream servizio2 
        service = Exponential((double)1 / SERVICETWO_DELAY);//genera servizio
    } else {
        SelectStream(STREAM_SERV_DELAY3);//seleziona stream servizio3 
        service = Exponential((double)1 / SERVICETHREE_DELAY);//genera servizio
    }

    return service;
}

double get_service_multiserver(char task_type){
    /**
     * Il metodo va a determinare qunato impiega un task per essere completato
     * nella cassa.
     */
    double service;
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in get_time_service_multiserver\n");
    }
    if (task_type == TASK_TYPE1) {//il job è di tipo 1
        SelectStream(STREAM_SERV_MULTISERVER1);//selezionare stream servizio1 
        service = Exponential((double)1 / SERVICEONE_MULTI);//genera servizio
    } else if(task_type == TASK_TYPE2) {//il job è di tipo 2
        SelectStream(STREAM_SERV_MULTISERVER2);//seleziona stream servizio2 
        service = Exponential((double)1 / SERVICETWO_MULTI);//genera servizio
    } else {
        SelectStream(STREAM_SERV_MULTISERVER3);//seleziona stream servizio3 
        service = Exponential((double)1 / SERVICETHREE_MULTI);//genera servizio
    }

    return service;
}

void assign_task_to_cassa(double time_current, char task_type, struct node **head,struct node **tail){
    //il metodo assegna il task di eseguire al server verifica andando
    //ad impostare il tempo di completamento di quel task.

    double time_end_service = time_current + get_service_cassa(task_type);
    insert_ordered(time_end_service, task_type, time_current, head, tail);
    return;
}

void assign_task_to_verify(double time_current, char task_type, struct node **head,struct node **tail){
    //il metodo assegna il task di eseguire al server verifica andando
    //ad impostare il tempo di completamento di quel task.

    double time_end_service = time_current + get_service_verifica(task_type);
    insert_ordered(time_end_service, task_type, time_current, head, tail);
    return;

}

void assign_task_to_delay(double time_current, char task_type, struct node **head,struct node **tail){
    //il metodo assegna il task di eseguire al server verifica andando
    //ad impostare il tempo di completamento di quel task.

    double time_end_service = time_current + get_service_delay(task_type);
    insert_ordered(time_end_service, task_type, time_current, head, tail);
    return;

}

void assign_task_to_multiserver(double time_current, char task_type, struct node **head,struct node **tail){
    //il metodo assegna il task di eseguire al server verifica andando
    //ad impostare il tempo di completamento di quel task.

    double time_end_service = time_current + get_service_multiserver(task_type);
    insert_ordered(time_end_service, task_type, time_current, head, tail);
    return;

}


double find_next_termination(struct node *head, char *task_type_termination) {//ritorna INF se la lista dinamica è vuota,
// altrimenti ritorna l'istante di completamento della testa della lista,ossia l'istante del prossimo completamento
    double end_service;
    if (head == NULL) {
        return INF;
    }
    if (task_type_termination == NULL) {
        handle_error_with_exit("error in fin_next_termination\n");
    }
    end_service = get_instant_end_service_from_linked_list(head, task_type_termination);
    return end_service;
}


void update_area(struct state state, struct area *area, double time_current,double time_next){
    //Esegue lupdate delle variabili all'interno della struttura AREA.
    //Per il calcolo delle statistiche necessarie.
    //area_tipo=(time_next-time_current)*popolazione_tipo

    if (area == NULL) {
        handle_error_with_exit("error in update area: area is NULL\n");
    }
    if (time_current > time_next) {
        handle_error_with_exit("error in update area: time_current > time_next\n");
    }
    if (time_current < 0) {
        handle_error_with_exit("error in update area: time_current < 0\n");
    }
    if (time_next < 0) {
        handle_error_with_exit("error in update area: time_next < 0\n");
    }

    //calcolo numero di Job nel nodo della rete  ??(server + coda)??
    area -> number_node_cassa += (time_next - time_current) * (state.number_of_user_cassa);
    area -> number_node_verify += (time_next - time_current) * (state.number_of_user_verify);
    area -> number_node_delay += (time_next - time_current) * (state.number_of_user_delay);
    area -> number_node_multi += (time_next - time_current) * (state.number_of_user_multiserver);


    //calcolo numero di Job nella coda
    area -> number_queue_cassa += (time_next - time_current) * (state.number_of_user_cassa - 1);
    area -> number_queue_verify += (time_next - time_current) * (state.number_of_user_verify - 1);
    area -> number_queue_delay += (time_next - time_current) * (state.number_of_user_delay - 1);
    area -> number_queue_multi += (time_next - time_current) * (state.number_of_user_multiserver - 1);

    //calcolo del numero di Job in servizio
    area -> number_service_cassa += (time_next - time_current); 

    return;
}

void update_state(char task_type, char location, struct state *state) {
    //aggiorna le variabili del sistema quando c'è un arrivo di tipo 1, di tipo 2 o di tipo 3
    if (state == NULL) {
        handle_error_with_exit("error in update state\n");
    }
    if (task_type != TASK_TYPE1 && task_type != TASK_TYPE2 && task_type != TASK_TYPE3) {
        handle_error_with_exit("error in update state task_type\n");
    }
    if (location != DIRECT_CASSA && location != DIRECT_DELAY && location != DIRECT_MULTISERVER && location != DIRECT_VERIFY) {
        handle_error_with_exit("error in update state location\n");
    }

    state->numberOfUsers ++; //ogni volta che arriva un Job aumentiamo il numero di utenti totali che il sistema serve.

    if (task_type == TASK_TYPE1) {//task 1 gusto gelato.
        if(location == DIRECT_CASSA) { //arrivo task gelato 1 gusto verso cassa
            state->number_of_user_cassa++;
        } else if(location == DIRECT_VERIFY) {//task type 1 e diretto sul  cloud(non interrotto)
            state->number_of_user_cassa--;
            state->number_of_user_verify++;
            state->number_balls_icecream--; //per il gelato 1 gusto tolgo solo una pallina di gelato.
        } else if(location == DIRECT_MULTISERVER){ //arrivo task gelato 1 gusto verso multiserver
            state->number_of_user_verify--;
            state->number_of_user_multiserver++;
        } else if(location == DIRECT_DELAY){
            state->number_of_user_verify--;
            state->number_of_user_delay++;
            state->number_balls_icecream = MAX_ICECREAM_TUB;
        } else {//task type 1 e non diretto sul cloud(non interrotto)
            handle_error_with_exit("error\n");
        }
    } else if (task_type == TASK_TYPE2) { //task gelato 2 gusti
        if(location == DIRECT_CASSA) { //arrivo task gelato 1 gusto verso cassa
            state->number_of_user_cassa++;
        } else if(location == DIRECT_VERIFY) {//task type 1 e diretto sul  cloud(non interrotto)
            state->number_of_user_cassa--;
            state->number_of_user_verify++;
            state->number_balls_icecream -= 2; //per il gelato 1 gusto tolgo solo una pallina di gelato.
        } else if(location == DIRECT_MULTISERVER){ //arrivo task gelato 1 gusto verso multiserver
            state->number_of_user_verify--;
            state->number_of_user_multiserver++;
        } else if(location == DIRECT_DELAY){
            state->number_of_user_verify--;
            state->number_of_user_delay++;
            state->number_balls_icecream = MAX_ICECREAM_TUB;
        } else {//task type 1 e non diretto sul cloud(non interrotto)
            handle_error_with_exit("error\n");
        }
    } else if (task_type == TASK_TYPE3) { //task gelato 2 gusti
        if(location == DIRECT_CASSA) { //arrivo task gelato 1 gusto verso cassa
            state->number_of_user_cassa++;
        } else if(location == DIRECT_VERIFY) {//task type 1 e diretto sul  cloud(non interrotto)
            state->number_of_user_cassa--;
            state->number_of_user_verify++;
            state->number_balls_icecream -= 3; //per il gelato 1 gusto tolgo solo una pallina di gelato.
        } else if(location == DIRECT_MULTISERVER){ //arrivo task gelato 1 gusto verso multiserver
            state->number_of_user_verify--;
            state->number_of_user_multiserver++;
        } else if(location == DIRECT_DELAY){
            state->number_of_user_verify--;
            state->number_of_user_delay++;
            state->number_balls_icecream = MAX_ICECREAM_TUB;
        } else {//task type 1 e non diretto sul cloud(non interrotto)
            handle_error_with_exit("error\n");
        }
    }
    return;
}