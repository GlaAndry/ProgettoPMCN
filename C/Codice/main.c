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
#include "multiserver_func.h"
#include "rvms.h"

int main(int argc, char *argv[]) {

    argc = argc;
    argv = argv;

    //definizione delle variabili
    struct state state;
    struct area area;
    struct state_multiserver multiserver[NUM_MAX_SERVER];
    initialize_area(&area);
    initialize_state(&state);

    double STOP = STOP_SIMULATION;
    int i = 0;//indice di batch
    state.number_balls_icecream = MAX_ICECREAM_TUB; //imposto il valore massimo 
    //di palline di gelato quando inzia la simulazione.

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

    double current_time = 0.0;      //Tempo iniziale della simulazione
    double arrive_time = 0.0;       //tempo iniziale di arrivo dei Job.
    double next_event_time = 0.0;   //tempo del prossimo evento


    //Arrivi
    double next_arrival;
    double next_arrival_gelato_1_gusto = 0.0;
    double next_arrival_gelato_2_gusti = 0.0;
    double next_arrival_gelato_3_gusti = 0.0;

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

    //Inizializzazione del multiserver
    for (int s = 0; s <= NUM_MAX_SERVER; s++) {
        multiserver[s].next_event_time = START;           /* this value is arbitrary because */
        multiserver[s].type_event = 0;                  /* all servers are initially idle  */
    }

    //se il tempo corrente è minore di quello massimo o ci sono ancora job in servizio
    // multiserver[0].type_event != 0 significa che il primo server del multiserver è idle
    while ((current_time < STOP || state.number_of_user_cassa > 0 || state.number_of_user_verify > 0 ||
            state.number_of_user_delay > 0 || state.number_of_user_multiserver > 0 || multiserver[0].type_event != 0)) {

        printf("Valore palline di gelato: %f\n", state.number_balls_icecream);

        //verifico la scadenza del timer in modo da terminare la simulazione
        if (current_time > STOP) {
            state.next = INF;
        } else {
            //determino il prossimo arrivo come l'evento che possiede il tempo minimo tra tutti.
            //andando anche a scrivere il tipo di Job che è arrivato nella varibile task_type_next_arrival
            double next_arrival_gelato_1_gusto = get_interarrival_cassa(1);
            double next_arrival_gelato_2_gusti = get_interarrival_cassa(2);
            double next_arrival_gelato_3_gusti = get_interarrival_cassa(3);
            //printf("gusto1 %f\n", next_arrival_gelato_1_gusto);
            //printf("gusto2 %f\n", next_arrival_gelato_2_gusti);
            //printf("gusto3 %f\n", next_arrival_gelato_3_gusti);
            double array_arrival[] = {next_arrival_gelato_1_gusto, next_arrival_gelato_2_gusti,
                                      next_arrival_gelato_3_gusti}; //array contentente gli arrivi dei Job
            next_arrival = (double) min_array_associated_job(array_arrival, 3, &task_type_next_arrival);
            printf("next_arrival: %f\n", next_arrival);
            printf("Tipologia di Task attuale: %d\n", task_type_next_arrival);
        }

        //verifico le prossime terminazioni. si va ad aggiornare anche il valore delle variabili 
        // task_type_next_..._termination per andare a determinare quale tipo di Job ha terminato.



        next_completion_cassa = find_next_termination(cassa_head, &task_type_next_termination);
        next_completion_delay = find_next_termination(delay_head, &task_type_next_termination);
        next_completion_verifica = find_next_termination(verifica_head, &task_type_next_termination);
        next_completion_multiserver = find_next_termination(multiserver_head, &task_type_next_termination);

        double array_compl[] = {next_completion_cassa, next_completion_delay, next_completion_verifica,
                                next_completion_multiserver};


        printf("\n\n\n");
        //printf("next_completion_cassa: %f\n", next_completion_cassa);
        //printf("next_completion_verifica: %f\n", next_completion_verifica);
        //printf("next_completion_delay: %f\n", next_completion_delay);
        //printf("next_completion_multiserver: %f\n", next_completion_multiserver);

        next_completion = min_array(array_compl, 4);

        printf("next min compl: %f\n", next_completion);



        //calcolo inizialmente tutti i tempi di servizio e verifico quelli con tempo minore dello stesso tipo
        //determino l'istante del prossimo evento
        next_event_time = min(next_arrival, next_completion);

        //aggiornamento dei valori dell'area
        update_area(state, &area, current_time, next_event_time);

        //aggiorno il clock
        current_time = next_event_time;

        printf("current time: %f\n", current_time);
        //printf("%d: numero nella lista verifica\n", count_element_linked_list(verifica_head));


        printf("Palline di gelato totali: %f\n", area.ice_cream_balls);
        sleep(2);


        //GESTIONE DEGLI EVENTI

        //se il prossimo evento è un arrivo
        if (current_time == next_arrival) {

            update_state(task_type_next_arrival, DIRECT_VERIFY, &state);
            printf("Sono in next_arrival e completo nella cassa\n");

            //definisco il nodo da inserire
            struct node *newNode;
            //definisco il tempo di completamento nel server cassa
            double time_completion = current_time + get_service_cassa(task_type_next_arrival);
            newNode = get_new_node(time_completion, task_type_next_arrival, current_time);
            //inserisco il Job all'interno della coda del server Cassa.
            //insert_at_tail(newNode, &verifica_head, &verifica_tail);
            insert_ordered(time_completion,task_type_next_arrival,current_time,&verifica_head,&verifica_tail);


            //se il prossimo evento è un completamento
        } else if (current_time == next_completion) { //gestisco l'evento di completamento


            double time_completion = 0.0;
            struct node *new_completion_node;

            //gestione evento completamento server verifica.
            //possibili redirezioni a delay o al multiserver.
            if (current_time == next_completion_verifica) {
                printf("Sono in next_completion_verifica\n");
                printf("Valore di current: %f\n", current_time);
                printf("Valore di get_service: %f\n", get_service_verifica(task_type_next_termination));

                //determino il numero attuale di palline di gelato
                int actual_number_of_icecream_balls = state.number_balls_icecream;

                //calcolo il tempo di completamento del Task
                time_completion = current_time + get_service_verifica(task_type_next_termination);
                //creazione del nodo
                new_completion_node = get_new_node(time_completion, task_type_next_termination, current_time);
                //aggiorno il tempo corrente
                //current_time += time_completion;
                //elimino la testa dalla lista dinamica della cassa
                delete_head(&verifica_head);

                //determino se andare verso il multiserver o verso il server di delay.
                if (actual_number_of_icecream_balls - task_type_next_termination < 0) {
                    update_state(task_type_next_termination, DIRECT_DELAY, &state);
                    //ci dirigiamo verso il server delay
                    //aggiungo il task appena calcolato nella lista dinamica della verifica
                    //insert_at_tail(new_completion_node, &delay_head, &delay_tail);
                    insert_ordered(time_completion,task_type_next_termination, current_time, &delay_head, &delay_tail);
                    printf("%d: numero nella lista delay\n", count_element_linked_list(delay_head));

                    //aggiornamento delle variabili di stato.
                } else {
                    //andiamo nel multiserver //multiserver arriva = completion verifica
                    //aggiungo il task appena calcolato nella lista dinamica della verifica

                    //aggiornamento delle variabili di stato.
                    update_state(task_type_next_termination, DIRECT_MULTISERVER, &state);
                    //insert_at_tail(new_completion_node, &multiserver_head, &multiserver_tail);
                    insert_ordered(time_completion,task_type_next_termination, current_time, &multiserver_head, &multiserver_tail);


                    int server = find_idle_server(multiserver);
                    int num_task = count_element_linked_list(multiserver_head);
                    if (num_task <= NUM_MAX_SERVER) {

                        multiserver[server].type_event = 1;
                        multiserver[server].next_event_time = current_time;

                    }

                    printf("%d: numero nella lista multiserver\n", count_element_linked_list(multiserver_head));

                }


            } else if (current_time == next_completion_delay) { //processamento Job nel server di verifica

                printf("Sono in next_completion_delay\n");
                printf("Valore di current: %f\n", current_time);
                printf("Valore di get_service: %f\n", get_service_delay(task_type_next_termination));

                //definisco la variabile di probabilità
                //tramite la funzione radom della libreria rngs
                //che sfrutta il generatore di Lehmer.
                double prob = Random();

                //calcolo il tempo di completamento del Task
                time_completion = current_time + get_service_delay(task_type_next_termination);
                //creazione del nodo
                new_completion_node = get_new_node(time_completion, task_type_next_termination, current_time);
                //aggiorno il tempo corrente
                //current_time += time_completion;
                //elimino la testa dalla lista dinamica della cassa
                delete_head(&delay_head);
                //aggiungo il task appena calcolato nella lista dinamica della verifica

                //determino se il Job esce dal sistema oppure va nel multiserver
                if (prob < PROBABILITY) { //probabilità del 20% di uscire dal sistema
                    //il job esce dal sistema
                    //aggiornamento delle variabili di stato.
                    printf("Ho rosicato zi\n");
                    update_state(task_type_next_termination, DIRECT_EXIT, &state);
                } else { //probabilità dell'80% di rientrare nel multiserver
                    //Job diretto verso il multiserver
                    printf("Diretto al multiserver\n");

                    //aggiornamento delle variabili di stato.
                    update_state(task_type_next_termination, DIRECT_MULTISERVER, &state);
                    //insert_at_tail(new_completion_node, &multiserver_head, &multiserver_tail);
                    insert_ordered(time_completion,task_type_next_termination, current_time, &delay_head, &delay_tail);


                    int server = find_idle_server(multiserver);
                    int num_task = count_element_linked_list(multiserver_head);
                    if (num_task <= NUM_MAX_SERVER) {

                        multiserver[server].type_event = 1;
                        multiserver[server].next_event_time = current_time;

                    }

                    printf("%d: numero nella lista multiserver\n", count_element_linked_list(multiserver_head));

                }

            } else {    //processamento Job multiserver

                printf("Sono in next_completion multi\n");
                printf("Valore di current: %f\n", current_time);
                printf("Valore di get_service: %f\n", get_service_multiserver(task_type_next_termination));

                //aggiornamento delle variabili di stato.
                update_state(task_type_next_termination, DIRECT_EXIT, &state);

                //verifico i task all'interno della lista dinamica
                int num_task = count_element_linked_list(multiserver_head);
                printf("Numero di elementi multi %d\n", num_task);
                int server = find_completion_server(multiserver);

                time_completion = current_time + get_service_multiserver(task_type_next_termination);
                //current_time += time_completion;

                //elimino la testa dalla lista dinamica della cassa
                delete_head(&multiserver_head);

                if(num_task >= NUM_MAX_SERVER){
                    //aggiornamento delle variabili di stato.
                    update_state(task_type_next_termination, DIRECT_EXIT, &state);
                    //calcolo il tempo di completamento del Task
                    time_completion = current_time + get_service_multiserver(task_type_next_termination);
                    multiserver[server].next_event_time = time_completion;
                    //creazione del nodo
                    new_completion_node = get_new_node(time_completion, task_type_next_termination, current_time);
                    //aggiorno il tempo corrente
                    //current_time += time_completion;
                    //elimino la testa dalla lista dinamica della cassa
                    delete_head(&multiserver_head);
                } else{
                    multiserver[server].type_event = 0;
                }

            }


        }
    }

}