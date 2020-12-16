#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "basic.h"
#include "distributions.h"
#include "next_event.h"
#include "parser.h"
#include "stats.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include "rvms.h"



int main(int argc, char *argv[]) {

    argc = argc;
    argv = argv;

    //definizione delle variabili
    struct state state;
    struct area area;
    struct last_state last_state;

    initialize_area(&area);
    initialize_state(&state);
    initialize_last_state(&last_state);


    double STOP = STOP_SIMULATION;
    state.number_balls_icecream = MAX_ICECREAM_TUB; //imposto il valore massimo
    //di palline di gelato quando inzia la simulazione.

    //Variabili Batch means
    int i = 0;//indice di batch

    ///variabili THR
    double* tr_batch=alloc_array_double(NUM_BATCH);
    double* tr_type1_batch = alloc_array_double(NUM_BATCH);
    double* tr_type2_batch = alloc_array_double(NUM_BATCH);
    double* tr_type3_batch = alloc_array_double(NUM_BATCH);
    double* tr_verifica = alloc_array_double(NUM_BATCH);
    double* tr_type1_verifica = alloc_array_double(NUM_BATCH);
    double* tr_type2_verifica = alloc_array_double(NUM_BATCH);
    double* tr_type3_verifica = alloc_array_double(NUM_BATCH);
    double* tr_delay = alloc_array_double(NUM_BATCH);
    double* tr_type1_delay = alloc_array_double(NUM_BATCH);
    double* tr_type2_delay = alloc_array_double(NUM_BATCH);
    double* tr_type3_delay = alloc_array_double(NUM_BATCH);
    double* tr_multiserver = alloc_array_double(NUM_BATCH);
    double* tr_type1_multiserver = alloc_array_double(NUM_BATCH);
    double* tr_type2_multiserver = alloc_array_double(NUM_BATCH);
    double* tr_type3_multiserver = alloc_array_double(NUM_BATCH);

    ///variabili tempo di risposta
    double *response_batch = alloc_array_double(NUM_BATCH);
    double *response_type1_batch = alloc_array_double(NUM_BATCH);
    double *response_type2_batch = alloc_array_double(NUM_BATCH);
    double *response_type3_batch = alloc_array_double(NUM_BATCH);
    double *response_verifica = alloc_array_double(NUM_BATCH);
    double *response_type1_verifica = alloc_array_double(NUM_BATCH);
    double *response_type2_verifica = alloc_array_double(NUM_BATCH);
    double *response_type3_verifica = alloc_array_double(NUM_BATCH);
    double *response_delay = alloc_array_double(NUM_BATCH);
    double *response_type1_delay = alloc_array_double(NUM_BATCH);
    double *response_type2_delay = alloc_array_double(NUM_BATCH);
    double *response_type3_delay = alloc_array_double(NUM_BATCH);
    double *response_multiserver = alloc_array_double(NUM_BATCH);
    double *response_type1_multiserver = alloc_array_double(NUM_BATCH);
    double *response_type2_multiserver = alloc_array_double(NUM_BATCH);
    double *response_type3_multiserver = alloc_array_double(NUM_BATCH);
    ///////////////////

    char task_type_next_arrival = 0;//tipo di job del prossimo arrivo
    char task_type_next_termination = 0;//tipo di job del prossimo completamento
    char task_type_next_termination_cassa = 0;
    char task_type_next_termination_verifica = 0;
    char task_type_next_termination_multiserver = 0;
    char task_type_next_termination_delay = 0;

    //definizione delle liste dinamiche
    struct node *cassa_head = NULL;
    //struct node *cassa_tail = NULL;

    struct node *verifica_head = NULL;
    struct node *verifica_tail = NULL;

    struct node *delay_head = NULL;
    struct node *delay_tail = NULL;

    struct node *multiserver_head = NULL;
    struct node *multiserver_tail = NULL;

    printf("----------------------------------------------------------\n");
    printf("START SIMULATION\n");
    printf("----------------------------------------------------------\n");
    PlantSeeds(989757435);

    //variabili del sistema

    double current_time = 0.0;      //Tempo iniziale della simulazione
    double next_event_time = 0.0;   //tempo del prossimo evento

    int counter = 0;


    //Arrivi
    double next_arrival;
    double next_arrival_gelato_1_gusto = get_interarrival_cassa(TASK_TYPE1, 1);
    double next_arrival_gelato_2_gusti = get_interarrival_cassa(TASK_TYPE2, 0);
    double next_arrival_gelato_3_gusti = get_interarrival_cassa(TASK_TYPE3, 0);

    //Completamenti
    double next_completion; //istante del prossimo completamento
    double next_completion_cassa = INF;     //istante prossimo completamento server cassa
    double next_completion_verifica = INF;  //istante prossimo completamento server verifica
    double next_completion_delay = INF;     //istante prossimo completamento server delay
    double next_completion_multiserver = INF;   //istante prossimo completamento multiserver


    char task_type_term_temp = 0;


    //se il tempo corrente è minore di quello massimo o ci sono ancora job in servizio
    while (current_time < STOP || state.actual_verify > 0 || state.actual_delay > 0 || state.actual_multi > 0) {
        check_state_variables_during_simulation(state);

        //verifico la scadenza del timer in modo da terminare la simulazione
        if (current_time > STOP) {
            //state.next = INF;
            next_arrival = INF;
        } else {
            //determino il prossimo arrivo come l'evento che possiede il tempo minimo tra tutti.
            //andando anche a scrivere il tipo di Job che è arrivato nella varibile task_type_next_arrival
            double array_arrival[] = {next_arrival_gelato_1_gusto, next_arrival_gelato_2_gusti,
                                      next_arrival_gelato_3_gusti}; //array contentente gli arrivi dei Job
            next_arrival = (double) min_array_associated_job(array_arrival, 3, &task_type_next_arrival);
        }

        //verifico le prossime terminazioni. si va ad aggiornare anche il valore delle variabili 
        // task_type_next_..._termination per andare a determinare quale tipo di Job ha terminato.

        //next_completion_cassa = find_next_termination(cassa_head, &task_type_next_termination_cassa);
        next_completion_delay = find_next_termination(delay_head, &task_type_next_termination_delay);
        next_completion_verifica = find_next_termination(verifica_head, &task_type_next_termination_verifica);
        next_completion_multiserver = find_next_termination(multiserver_head, &task_type_next_termination_multiserver);

        double array_compl[] = {next_completion_delay, next_completion_verifica,next_completion_multiserver};

        next_completion = min_array(array_compl, 3);



        //calcolo inizialmente tutti i tempi di servizio e verifico quelli con tempo minore dello stesso tipo
        //determino l'istante del prossimo evento
        next_event_time = min(next_arrival, next_completion);


        //aggiornamento dei valori dell'area

        if(next_completion == next_completion_verifica){
            task_type_term_temp = task_type_next_termination_verifica;
            update_area_delay(state, &area, current_time, next_event_time, task_type_term_temp);
            update_area_service(state, &area, current_time, next_event_time, task_type_term_temp);
            update_area(state, &area, current_time, next_event_time, task_type_term_temp);
        } else if (next_completion == next_completion_delay){
            task_type_term_temp = task_type_next_termination_delay;
            update_area_verifica(state, &area, current_time, next_event_time, task_type_term_temp);
            update_area_service(state, &area, current_time, next_event_time, task_type_term_temp);
            update_area(state, &area, current_time, next_event_time, task_type_term_temp);
        } else {
            task_type_term_temp = task_type_next_termination_multiserver;
            update_area_verifica(state, &area, current_time, next_event_time, task_type_term_temp);
            update_area_delay(state, &area, current_time, next_event_time, task_type_term_temp);
            update_area(state, &area, current_time, next_event_time, task_type_term_temp);
        }




        //calcolo batch means
        if(next_event_time-last_state.last_observed_time >= LENGTH_BATCH_TIME) {

            calculate_batch(next_event_time,state,area,&last_state,&i,
                            tr_batch,tr_type1_batch,tr_type2_batch,tr_type3_batch,
                            tr_verifica, tr_type1_verifica, tr_type2_verifica, tr_type3_verifica,
                            tr_delay, tr_type1_delay, tr_type2_delay, tr_type3_delay,
                            tr_multiserver, tr_type1_multiserver, tr_type2_multiserver, tr_type3_multiserver,
                            response_batch, response_type1_batch, response_type2_batch,response_type3_batch,
                            response_verifica, response_type1_verifica, response_type2_verifica, response_type3_verifica,
                            response_delay, response_type1_delay, response_type2_delay, response_type3_delay,
                            response_multiserver, response_type1_multiserver, response_type2_multiserver, response_type3_multiserver);

        }

        //aggiorno il clock
        current_time = next_event_time;


        //GESTIONE DEGLI EVENTI
        //se il prossimo evento è un arrivo
        if (current_time == next_arrival) {

            if (task_type_next_arrival == TASK_TYPE1){
                next_arrival_gelato_1_gusto = get_interarrival_cassa(TASK_TYPE1, 0);
                assign_task_to_verify(current_time, TASK_TYPE1, &verifica_head, &verifica_tail);
                //insert_ordered(next_arrival_gelato_1_gusto,task_type_next_arrival,current_time,&verifica_head,&verifica_tail);
            } else if (task_type_next_arrival == TASK_TYPE2){
                next_arrival_gelato_2_gusti = get_interarrival_cassa(TASK_TYPE2, 0);
                //insert_ordered(next_arrival_gelato_2_gusti,task_type_next_arrival,current_time,&verifica_head,&verifica_tail);
                assign_task_to_verify(current_time, TASK_TYPE2, &verifica_head, &verifica_tail);

            } else {
                next_arrival_gelato_3_gusti = get_interarrival_cassa(TASK_TYPE3, 0);
                //insert_ordered(next_arrival_gelato_3_gusti,task_type_next_arrival,current_time,&verifica_head,&verifica_tail);
                assign_task_to_verify(current_time, TASK_TYPE3, &verifica_head, &verifica_tail);

            }


            update_state(task_type_next_arrival, DIRECT_VERIFY, &state);

            //definisco il tempo di completamento nel server cassa
            //double time_completion = current_time + get_service_cassa(task_type_next_arrival);
            //inserisco il Job all'interno della coda del server Cassa.
            //insert_ordered(time_completion,task_type_next_arrival,current_time,&verifica_head,&verifica_tail);
            //se il prossimo evento è un completamento
        } else if (current_time == next_completion) { //gestisco l'evento di completamento
            double time_completion = 0.0;
            //gestione evento completamento server verifica.
            //possibili redirezioni a delay o al multiserver.
            if (current_time == next_completion_verifica) {
                //determino il numero attuale di palline di gelato
                int actual_number_of_icecream_balls = state.number_balls_icecream;

                ///update del tipo di task
                task_type_next_termination = task_type_next_termination_verifica;
                //calcolo il tempo di completamento del Task
                //time_completion = current_time + get_service_verifica(task_type_next_termination);

                //elimino la testa dalla lista dinamica della cassa
                delete_head(&verifica_head);


                //determino se andare verso il multiserver o verso il server di delay.
                if (actual_number_of_icecream_balls - task_type_next_termination < 0) {
                    //update_area_verifica(state, &area, current_time, time_completion, task_type_next_termination);
                    update_state(task_type_next_termination, DIRECT_DELAY, &state);
                    //ci dirigiamo verso il server delay
                    //aggiungo il task appena calcolato nella lista dinamica della verifica
                    //insert_ordered(time_completion,task_type_next_termination, current_time, &delay_head, &delay_tail);
                    if(task_type_next_termination == TASK_TYPE1){
                        assign_task_to_delay(current_time, TASK_TYPE1, &delay_head, &delay_tail);
                    } else if (task_type_next_termination == TASK_TYPE2){
                        assign_task_to_delay(current_time, TASK_TYPE2, &delay_head, &delay_tail);
                    } else {
                        assign_task_to_delay(current_time, TASK_TYPE3, &delay_head, &delay_tail);
                    }

                    continue;
                    //aggiornamento delle variabili di stato.
                } else {
                    //andiamo nel multiserver //multiserver arriva = completion verifica
                    //aggiungo il task appena calcolato nella lista dinamica della verifica

                    //aggiornamento delle variabili di stato.
                    update_state(task_type_next_termination, DIRECT_MULTISERVER_FROM_VER, &state);
                    //update_area_verifica(state, &area, current_time, time_completion, task_type_next_termination);

                    //insert_at_tail(new_completion_node, &multiserver_head, &multiserver_tail);
                    //insert_ordered(time_completion,task_type_next_termination, current_time, &multiserver_head, &multiserver_tail);

                    if(task_type_next_termination == TASK_TYPE1){
                        assign_task_to_multiserver(current_time, TASK_TYPE1, &multiserver_head, &multiserver_tail);
                    } else if (task_type_next_termination == TASK_TYPE2){
                        assign_task_to_multiserver(current_time, TASK_TYPE2, &multiserver_head, &multiserver_tail);
                    } else {
                        assign_task_to_multiserver(current_time, TASK_TYPE3, &multiserver_head, &multiserver_tail);
                    }

                    continue;
                }


            } else if (current_time == next_completion_delay) { //processamento Job nel server di verifica

                ///Update del tipo di task
                task_type_next_termination = task_type_next_termination_delay;
                //definisco la variabile di probabilità
                //tramite la funzione radom della libreria rngs
                //che sfrutta il generatore di Lehmer.

                double prob = Random();

                //calcolo il tempo di completamento del Task
                //time_completion = current_time + get_service_delay(task_type_next_termination);

                //elimino la testa dalla lista dinamica della cassa
                delete_head(&delay_head);
                //aggiungo il task appena calcolato nella lista dinamica della verifica
                //determino se il Job esce dal sistema oppure va nel multiserver
                if (prob < PROBABILITY) { //probabilità del 20% di uscire dal sistema
                    //il job esce dal sistema
                    //aggiornamento delle variabili di stato.
                    update_state(task_type_next_termination, DIRECT_QUIT, &state);
                    continue;
                } else { //probabilità dell'80% di rientrare nel multiserver
                    //Job diretto verso il multiserver
                    //aggiornamento delle variabili di stato.
                    update_state(task_type_next_termination, DIRECT_MULTISERVER_FROM_DEL, &state);
                    //insert_ordered(time_completion,task_type_next_termination, current_time, &multiserver_head, &multiserver_tail);

                    if(task_type_next_termination == TASK_TYPE1){
                        assign_task_to_multiserver(current_time, TASK_TYPE1, &multiserver_head, &multiserver_tail);
                    } else if (task_type_next_termination == TASK_TYPE2){
                        assign_task_to_multiserver(current_time, TASK_TYPE2, &multiserver_head, &multiserver_tail);
                    } else {
                        assign_task_to_multiserver(current_time, TASK_TYPE3, &multiserver_head, &multiserver_tail);
                    }

                    continue;
                }

            } else {    //processamento Job multiserver

                ///update del tipo di task
                task_type_next_termination = task_type_next_termination_multiserver;

                //aggiornamento delle variabili di stato.
                update_state(task_type_next_termination, DIRECT_EXIT, &state);

                //time_completion = current_time + get_service_multiserver(task_type_next_termination);


                //elimino la testa dalla lista dinamica della cassa
                delete_head(&multiserver_head);

                continue;
            }


        }
    }



    print_all(tr_batch,tr_type1_batch,tr_type2_batch,tr_type3_batch,
              tr_verifica, tr_type1_verifica, tr_type2_verifica, tr_type3_verifica,
              tr_delay, tr_type1_delay, tr_type2_delay, tr_type3_delay,
              tr_multiserver, tr_type1_multiserver, tr_type2_multiserver, tr_type3_multiserver,
              response_batch, response_type1_batch, response_type2_batch,response_type3_batch,
              response_verifica, response_type1_verifica, response_type2_verifica, response_type3_verifica,
              response_delay, response_type1_delay, response_type2_delay, response_type3_delay,
              response_multiserver, response_type1_multiserver, response_type2_multiserver, response_type3_multiserver);

    //printf("pd %f\n", state.total_delay/state.total_system);


    check_state_variables_after_simulation(state);
    exit(0);
}