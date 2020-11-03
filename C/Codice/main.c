#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "basic.h"
#include "distributions.h"
#include "next_event.h"
#include "parser.h"
//#include "stats.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

int main(int argc,char *argv[]){

    argc = argc;
    argv = argv;

    //definizione delle variabili
    struct state state;
    struct area area;
    initialize_area(&area);
    initialize_state(&state);

    double STOP=STOP_SIMULATION;
    int i=0;//indice di batch
    state.number_balls_icecream = MAX_ICECREAM_TUB; //imposto il valore massimo 
    //alle palline di gelato quando inzia la simulazione.

    //Queste variabili assumono il valore 1,2 o 3 a seconda del Job processato.

    char task_type_next_arrival = 0;//tipo di job del prossimo arrivo
    char task_type_next_termination = 0;
    char task_type_next_cassa_termination = 0;//tipo di job del prossimo completamento in cassa
    char task_type_next_verifica_termination = 0;//tipo di job del prossimo completamento in verifica
    char task_type_next_delay_termination = 0;//tipo di job del prossimo completamento in delay
    char task_type_next_multiserver_termination = 0;//tipo di job del prossimo completamento in multiserver

    //definizione delle liste dinamiche
    struct node *cassa_head = NULL;
    struct node *cassa_tail = NULL;

    struct node *verifica_head = NULL;
    struct node *verifica_tail = NULL;

    struct node *delay_head = NULL;
    struct node *delay_tail = NULL;

    struct node *multiserver_head = NULL;
    struct node *multiserver_tail = NULL;

    

    printf("----------------------------------------------------------\n");
    printf("START SIMULATION\n");
    printf("----------------------------------------------------------\n");
    PlantSeeds(123456789);

    //variabili del sistema

    double current_time = 0.0; //Tempo iniziale della simulazione
    double arrive_time = 0.0;  //tempo inizile di arrivo dei Job.
    double next_event_time = 0.0; //tempo del prossimo evento


    //Arrivi
    double next_arrival;
    double next_arrival_gelato_1_gusto = get_interarrival_cassa(1);
    double next_arrival_gelato_2_gusti = get_interarrival_cassa(2);
    double next_arrival_gelato_3_gusti = get_interarrival_cassa(3);

    //Completamenti
    double next_completion; //istante del prossimo completamento 

    double next_completion_cassa = INF;     //istante prossimo completamento server cassa
    double next_completion_cassa_1 = INF;
    double next_completion_cassa_2 = INF;
    double next_completion_cassa_3 = INF;

    double next_completion_verifica = INF;  //istante prossimo completamento server verifica
    double next_completion_verifica_1 = INF;
    double next_completion_verifica_2 = INF;
    double next_completion_verifica_3 = INF;

    double next_completion_delay = INF;     //istante prossimo completamento server delay
    double next_completion_delay_1 = INF;
    double next_completion_delay_2 = INF;
    double next_completion_delay_3 = INF;

    double next_completion_multiserver = INF;   //istante prossimo completamento multiserver
    double next_completion_multiserver_1 = INF;
    double next_completion_multiserver_2 = INF;
    double next_completion_multiserver_3 = INF;

    while ((current_time < STOP || state.number_of_user_cassa > 0 || state.number_of_user_verify > 0 || state.number_of_user_delay > 0 || state.number_of_user_multiserver > 0)) {

        //verifico la scadenza del timer in modo da terminare la simulazione
        if(current_time > STOP){
            state.next = INF;
        } else { 
            //determino il prossimo arrivo come l'evento che possiede il tempo minimo tra tutti.
            //andando anche a scrivere il tipo di Job che è arrivato nella varibile task_type_next_arrival
            printf("gusto1 %f\n", next_arrival_gelato_1_gusto);
            printf("gusto2 %f\n", next_arrival_gelato_2_gusti);
            printf("gusto3 %f\n", next_arrival_gelato_3_gusti);
            double array_arrival[] = {next_arrival_gelato_1_gusto, next_arrival_gelato_2_gusti, next_arrival_gelato_3_gusti}; //array contentente gli arrivi dei Job
            next_arrival = (double) min_array_associated_job(array_arrival, 3, &task_type_next_arrival);
            printf("next_arrival: %f\n", next_arrival);
            printf("Tipologia di Task attuale: %d\n", task_type_next_arrival);

        }

        //verifico le prossime terminazioni. si va ad aggiornare anche il valore delle variabili 
        // task_type_next_..._termination per andare a determinare quale tipo di Job ha terminato.

        /*
        next_completion_cassa = find_next_termination(cassa_head, &task_type_next_cassa_termination);
        next_completion_delay = find_next_termination(delay_head, &task_type_next_delay_termination);
        next_completion_verifica = find_next_termination(verifica_head, &task_type_next_verifica_termination);
        next_completion_multiserver = find_next_termination(multiserver_head, &task_type_next_multiserver_termination);
        */

        
        //calcolo inizialmente tutti i tempi di servizio e verifico quelli con tempo minore dello stesso tipo

        next_completion_cassa_1 = get_service_cassa(TASK_TYPE1);
        next_completion_cassa_2 = get_service_cassa(TASK_TYPE2);
        next_completion_cassa_3 = get_service_cassa(TASK_TYPE3);
        double array_cassa[] = {next_completion_cassa_1,next_completion_cassa_2,next_completion_cassa_3};
        next_completion_cassa = (double) min_array(array_cassa,3);

        next_completion_verifica_1 = get_service_verifica(TASK_TYPE1);
        next_completion_verifica_2 = get_service_verifica(TASK_TYPE2);
        next_completion_verifica_3 = get_service_verifica(TASK_TYPE3);
        double array_verifica[] = {next_completion_verifica_1,next_completion_verifica_2,next_completion_verifica_3};
        next_completion_verifica = (double) min_array(array_verifica,3);

        next_completion_delay_1 = get_service_delay(TASK_TYPE1);
        next_completion_delay_2 = get_service_delay(TASK_TYPE2);
        next_completion_delay_3 = get_service_delay(TASK_TYPE3);
        double array_delay[] = {next_completion_delay_1,next_completion_delay_2,next_completion_delay_3};
        next_completion_delay = (double) min_array(array_delay,3);

        next_completion_multiserver_1 = get_service_multiserver(TASK_TYPE1);
        next_completion_multiserver_2 = get_service_multiserver(TASK_TYPE2);
        next_completion_multiserver_3 = get_service_multiserver(TASK_TYPE3);
        double array_multiserver[] = {next_completion_multiserver_1,next_completion_multiserver_2,next_completion_multiserver_3};
        next_completion_multiserver = (double) min_array(array_multiserver,3);


        printf("compl cassa: %f\n", next_completion_cassa_1);
        printf("%d nome cassa\n", task_type_next_cassa_termination);
        printf("compl d: %f\n", next_completion_delay);
        printf("%d nome d\n", task_type_next_delay_termination);
        printf("compl v: %f\n", next_completion_verifica);
        printf("%d nome v\n", task_type_next_verifica_termination);
        printf("compl m: %f\n", next_completion_multiserver);

        //controllo il minimo tra gli istanti di completamento.
        //e determino dove è avvenuto il completamento.
        double array_completion[] = {next_completion_cassa, next_completion_delay, next_completion_verifica, next_completion_multiserver};
        next_completion = min_array_associated_job(array_completion, 3, &task_type_next_termination);
        printf("next_completion: %f\n", next_completion);
        printf("valore task type term %d\n", task_type_next_termination);  
        if(next_completion == next_completion_cassa){
            task_type_next_cassa_termination == task_type_next_termination;
        } else if (next_completion == next_completion_delay){
            task_type_next_delay_termination == task_type_next_termination;
        } else if (next_completion == next_completion_verifica){
             task_type_next_verifica_termination == task_type_next_termination;
        } else {
             task_type_next_multiserver_termination == task_type_next_termination;
        }

        //determino l'istante del prossimo evento
        next_event_time = min(next_arrival, next_completion);

        //aggiornamento dei valori dell'area
        update_area(state, &area, current_time, next_event_time);

        //aggiorno il clock
        current_time = next_event_time;

        printf("current time: %f\n", current_time);


        printf("\n\n\n");
        sleep(5);

        //FINO A QUI CORRETTO 



        //GESTIONE DEGLI EVENTI

        if(current_time == next_arrival){ //gestisco l'evento di arrivo nel sistema
            if(task_type_next_arrival == TASK_TYPE1){ //Arriva un job di tipo 1
                next_arrival_gelato_1_gusto = get_interarrival_cassa(TASK_TYPE1);

                //Aggiorno le variabili del sistema tramite la funzione update.
                update_state(TASK_TYPE1, DIRECT_VERIFY, &state);

                //Assegno il task al server verifica
                assign_task_to_verify(current_time, TASK_TYPE1, &verifica_head, &verifica_tail);
            }else if(task_type_next_arrival == TASK_TYPE2) {
                next_arrival_gelato_1_gusto = get_interarrival_cassa(TASK_TYPE2);

                //Aggiorno le variabili del sistema
                update_state(TASK_TYPE2, DIRECT_VERIFY, &state);

                //Assegno il task al server verifica
                assign_task_to_verify(current_time, TASK_TYPE2, &verifica_head, &verifica_tail);
            } else {
                next_arrival_gelato_1_gusto = get_interarrival_cassa(TASK_TYPE3);

                //Aggiorno le variabili del sistema
                update_state(TASK_TYPE3, DIRECT_VERIFY, &state);

                //Assegno il task al server verifica
                assign_task_to_verify(current_time, TASK_TYPE3, &verifica_head, &verifica_tail);
            }
        } else if (current_time == next_completion){ //gestisco l'evento di completamento

            //gestione evento completamento server verifica.
            //possibili redirezioni a delay o al multiserver.
            if (current_time == next_completion_verifica){
                state.completion_verifica++;
                //elimino dalla testa della coda verifica il JOB
                //aggiornando la variabile arrive_time.
                delete_head(&verifica_head, &arrive_time);
                if(task_type_next_verifica_termination == TASK_TYPE1){
                    //if(condizione per andare in delay)

                    //else condizione per andare in multiserver
                    assign_task_to_multiserver(current_time, TASK_TYPE1, &multiserver_head, &multiserver_tail);
                } else if (task_type_next_verifica_termination == TASK_TYPE2){
                    

                    assign_task_to_multiserver(current_time, TASK_TYPE2, &multiserver_head, &multiserver_tail);
                } else {
                    

                    assign_task_to_multiserver(current_time, TASK_TYPE3, &multiserver_head, &multiserver_tail);
                }
            }

            //gestione dell'evento completamento multiserver
            //l'utente esce dal sistema.
            if (current_time == next_completion_multiserver){

                delete_head(&multiserver_head, &arrive_time);
            }
        }
    }

}