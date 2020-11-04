#include <limits.h>
#ifndef PROG_BASIC_H
#define PROG_BASIC_H
//
struct state{//variabili di stato del sistema
    //Variabili globali
    double current;                 /* current time                        */
    double next;                    /* next (most imminent) event time     */
    double last;                    /* last arrival time                   */
    double numberOfUsers;           /* Numero di utenti nel sistema        */
    double number_lost_users;       /* Numero di utenti persi dal sistema  */
    double number_balls_icecream;   /* Numero attuale di palline di gelato 
                                       prima di essere riempite nuovamente */

    //Variabili Server Cassa
    double arrival;                 /* next arrival time server Cassa      */
    double completion;              /* next completion time  server Cassa */
    double number_of_user_cassa;

    //Variabili Server verifica
    double arrival_verifica;
    double completion_verifica;
    double number_of_user_verify;


    //Variabili Delay Server
    double arrival_delay;
    double completion_delay;
    double number_of_user_delay;

    //variabili Multi_server
    double arrival_multi;
    double completion_multi;
    double number_of_user_multiserver;
    
};

struct last_state{ //struttura che determina le variabili dello stato precedente rispetto a quello attuale del sistema.

    double last_completition_cassa;
};


struct area{ //tipi di aree (calcolo ottenuto non dall'integrale ma dalla forma esplicita) per il calcolo delle variabili di interesse
    
    //Variabili Cassa
    double number_node_cassa;
    double number_queue_cassa;
    double number_service_cassa;
    //Variabili verifica
    double number_node_verify;
    double number_queue_verify;
    double number_service_verify;
    //variabili Delay
    double number_node_delay;
    double number_queue_delay;
    double number_service_delay;
    //variabili multiserver
    double number_node_multi;
    double number_queue_multi;
    double number_service_multi;

    //vecchie variabili
    double node;                    /* time integrated number in the node  */
    double queue;                   /* time integrated number in the queue */
    double service;                 /* time integrated number in service   */
};

#define START 0.0 //istante inizio simulazione
//#define STOP_SIMULATION  2000000 //istante fine simulazione VECCHIO ISTANTE, quello nuovo è solo per test.
#define STOP_SIMULATION  500
#define INF (STOP_SIMULATION*10)
#define NO_TIME_LOST 0.0
#define NUM_BATCH 64 //k=numero di batch
#define LENGTH_BATCH_TIME (STOP/NUM_BATCH)

#define NUM_MAX_SERVER 3//NUM_MAX_SERVER==N,numero massimo di server della cloudlet

//arrival rate and service rate
#define ARRIVALONE	4.0 //lambda1 1 gusto gelato        [task/s]
#define ARRIVALTWO  6.25 //lambda2 2 gusti gelato       [task/s]
#define ARRIVALTHREE 5.50 //lamdbda3 3 gusti gelato     [task/s]

//tasso di servizio cassa
#define SERVICEONE_CASSA 5.25  //u1 1 gusto gelato            [task/s]
#define SERVICETWO_CASSA 6.37  //u2 2 gusti gelato            [task/s]
#define SERVICETHREE_CASSA 5.59  //u2 3 gusti gelato          [task/s]

//tasso di servizio verifica
#define SERVICEONE_VERIFY 12  //u1 1 gusto gelato            [task/s]
#define SERVICETWO_VERIFY 11  //u2 2 gusti gelato            [task/s]
#define SERVICETHREE_VERIFY 7  //u2 3 gusti gelato          [task/s]

//tasso di servizio delay
#define SERVICEONE_DELAY 5.25  //u1 1 gusto gelato            [task/s]
#define SERVICETWO_DELAY 6.37  //u2 2 gusti gelato            [task/s]
#define SERVICETHREE_DELAY 5.59  //u2 3 gusti gelato          [task/s]

//tasso di servizio Multiserver
#define SERVICEONE_MULTI 5.25  //u1 1 gusto gelato            [task/s]
#define SERVICETWO_MULTI 6.37  //u2 2 gusti gelato            [task/s]
#define SERVICETHREE_MULTI 5.59  //u2 3 gusti gelato          [task/s]

//streams per arrivi e servizi
#define STREAM_ARR1 0
#define STREAM_ARR2 1
#define STREAM_ARR3 2

#define STREAM_SERV_CASSA1 3
#define STREAM_SERV_CASSA2 4
#define STREAM_SERV_CASSA3 5

#define STREAM_SERV_DELAY1 6
#define STREAM_SERV_DELAY2 7
#define STREAM_SERV_DELAY3 8

#define STREAM_SERV_MULTISERVER1 9
#define STREAM_SERV_MULTISERVER2 10
#define STREAM_SERV_MULTISERVER3 11

#define STREAM_SERV_VERIFY1 12
#define STREAM_SERV_VERIFY2 13
#define STREAM_SERV_VERIFY3 14

#define STREAM_SETUP 15

//constants
#define TASK_TYPE1 1    //1 gusto gelato
#define TASK_TYPE2 2    //2 gusti gelato   
#define TASK_TYPE3 3    //3 gusti gelato

//valore massimo vaschetta di gelato
#define MAX_ICECREAM_TUB 30

//locazioni all'iterno della rete
#define DIRECT_CASSA 1          //task diretto alla cassa
#define DIRECT_VERIFY 2         //task diretto alla verifica dei gusti
#define DIRECT_MULTISERVER 3    //task diretto al multiserver
#define DIRECT_DELAY 4          //task diretto al server di Delay
#define DIRECT_QUIT 5           //task esce dal sistema senza gelato
#define DIRECT_EXIT 6           //task esce dal sistema con gelato

#define SEED_DEFAULT 991102
#define ALPHA 0.05 //ALPHA= 0.05 NECESSARIO PER INTERVALLO DI CONFIDENZA 

void handle_error_with_exit(char*error_string);
double min_array_associated_job(double arr[], int len, char *type);
double min_array(double arr[], int len);
double*alloc_array_double(int lenght);
void free_all_memory(double*tr_batch);
double max(double i,double j);
double min(double i,double j);
double* min_element(double *start, double *end);
void check_state_variables(int N, struct state state);
void check_state_variables_during_simulation(int N, struct state state);
void check_state_variables_after_simulation(struct state state);


/*
long*alloc_array_long(int lenght);
int*alloc_array_int(int lenght);
int**alloc_array_pointer_to_int(int lenght);
int**alloc_matrix_int(int num_row,int num_col);
char*alloc_array_char(int lenght);
void swap_row_matrix(int**matrix,int num_row,int num_col,int row1,int row2);

int index_max_in_array(int *array,int lenght);
double min2(double i,double j, double k);
double min3(double i,double j, double k);
double min_3_input(double i, double j, double k);
int index_min_in_array(int *array,int lenght);
double**alloc_array_pointer_to_double(int lenght);
double**alloc_matrix_double(int num_row,int num_col);
int**alloc_matrix_int(int num_row,int num_col);
*/

#endif