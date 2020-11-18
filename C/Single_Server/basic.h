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
    int num_job_completed;

    ///Numero di Job attuali nel sistema////
    double actual_system;
    double actual_job1;
    double actual_job2;
    double actual_job3;

    double actual_verify;
    double actual_job1_verify;
    double actual_job2_verify;
    double actual_job3_verify;

    double actual_delay;
    double actual_job1_delay;
    double actual_job2_delay;
    double actual_job3_delay;

    double actual_multi;
    double actual_job1_multi;
    double actual_job2_multi;
    double actual_job3_multi;

    ///Numero di Job totali del sistema////

    double total_system;
    double total_job1;
    double total_job2;
    double total_job3;

    double total_verify;
    double total_job1_verify;
    double total_job2_verify;
    double total_job3_verify;

    double total_delay;
    double total_job1_delay;
    double total_job2_delay;
    double total_job3_delay;

    double total_multi;
    double total_job1_multi;
    double total_job2_multi;
    double total_job3_multi;

    /////


    double job1;        //numero di Job totali di tipo 1 completati
    double job2;
    double job3;

    //Variabili Server Cassa
    double arrival;                 /* next arrival time server Cassa      */
    double completion;              /* next completion time  server Cassa */
    double number_of_user_cassa;

    //Variabili Server verifica
    double arrival_verifica;
    double completion_verifica;
    double number_of_user_verify;
    double job1_verify;     //numero di job di tipo 1 completati dal server verifica
    double job2_verify;
    double job3_verify;


    //Variabili Delay Server
    double arrival_delay;
    double completion_delay;
    double number_of_user_delay;
    double job1_delay;     //numero di job di tipo 1 completati dal server delay
    double job2_delay;
    double job3_delay;


    //variabili Multi_server
    double arrival_multi;
    double completion_multi;
    double number_of_user_multiserver;
    double job1_multiserver;   //numero di job di tipo 1 completati dal server multiserver
    double job2_multiserver;
    double job3_multiserver;

};

struct state_multiserver{
    //variabili Multi_server
    int type_event;                     //determina se il server è idle o meno (1: Esegue il job , 0:idle)
    double next_event_time;             //Prossimo evento temporale nel multiserver
};

struct last_state{ //struttura che determina le variabili dello stato precedente rispetto a quello attuale del sistema.

    int last_num_job_completed;

    ///attuali
    int last_num_job_1_completed_actual;
    int last_num_job_2_completed_actual;
    int last_num_job_3_completed_actual;

    int last_num_job_1_arrived_actual;
    int last_num_job_2_arrived_actual;
    int last_num_job_3_arrived_actual;

    int last_num_job_1_verifica_actual;
    int last_num_job_2_verifica_actual;
    int last_num_job_3_verifica_actual;

    int last_num_job_1_multiserver_actual;
    int last_num_job_2_multiserver_actual;
    int last_num_job_3_multiserver_actual;

    int last_num_job_1_delay_actual;
    int last_num_job_2_delay_actual;
    int last_num_job_3_delay_actual;

    ///totali

    int last_num_job_1_completed_total;
    int last_num_job_2_completed_total;
    int last_num_job_3_completed_total;

    int last_num_job_1_arrived_total;
    int last_num_job_2_arrived_total;
    int last_num_job_3_arrived_total;

    int last_num_job_1_verifica_total;
    int last_num_job_2_verifica_total;
    int last_num_job_3_verifica_total;

    int last_num_job_1_multiserver_total;
    int last_num_job_2_multiserver_total;
    int last_num_job_3_multiserver_total;

    int last_num_job_1_delay_total;
    int last_num_job_2_delay_total;
    int last_num_job_3_delay_total;

    /////

    double last_area;
    double last_area_type1;
    double last_area_type2;
    double last_area_type3;

    double last_area_type1_verifica;
    double last_area_type2_verifica;
    double last_area_type3_verifica;

    double last_area_type1_delay;
    double last_area_type2_delay;
    double last_area_type3_delay;

    double last_area_type1_multiserver;
    double last_area_type2_multiserver;
    double last_area_type3_multiserver;

    int last_numberOfUsers;

    double last_observed_time;

};


struct area{ //tipi di aree (calcolo ottenuto non dall'integrale ma dalla forma esplicita) per il calcolo delle variabili di interesse
    
    //Variabili Cassa
    double number_node_cassa;
    double number_job_type1_cassa;
    double number_job_type2_cassa;
    double number_job_type3_cassa;

    //double number_queue_cassa;
    //double number_service_cassa;
    //Variabili verifica
    double number_verify;
    double number_job_type1_verify;
    double number_job_type2_verify;
    double number_job_type3_verify;
    //double number_queue_verify;
    //double number_service_verify;
    //variabili Delay
    double number_delay;
    double number_job_type1_delay;
    double number_job_type2_delay;
    double number_job_type3_delay;
    //double number_queue_delay;
    //double number_service_delay;
    //variabili multiserver
    double number_multi;
    double number_job_type1_multiserver;
    double number_job_type2_multiserver;
    double number_job_type3_multiserver;
    //double number_queue_multi;
    //double number_service_multi;

    //variabili globali
    double total_node;                    /* time integrated number in the node  */
    double number_job_type1;
    double number_job_type2;
    double number_job_type3;

    //altre variabili
    double users_lost;
    double ice_cream_balls;

    //double total_queue;                   /* time integrated number in the queue */
    //double total_service;                 /* time integrated number in service   */
};

#define START 0.0 //istante inizio simulazione
//istante fine simulazione VECCHIO ISTANTE, quello nuovo è solo per test.
#define STOP_SIMULATION  2000000
#define INF (STOP_SIMULATION*10)
#define NO_TIME_LOST 0.0
#define NUM_BATCH 64 //k=numero di batch
#define LENGTH_BATCH_TIME (STOP/NUM_BATCH)


//arrival rate and service rate
#define ARRIVALONE	0.05 //lambda1 1 gusto gelato        [task/s]*[1/60 s] = task/min
#define ARRIVALTWO  0.066667 //lambda2 2 gusti gelato       [task/s]
#define ARRIVALTHREE 0.083333 //lamdbda3 3 gusti gelato     [task/s]

//tasso di servizio cassa
#define SERVICEONE_CASSA 0.066667         //u1 1 gusto gelato            [task/s]
#define SERVICETWO_CASSA 0.066667  //u2 2 gusti gelato            [task/s]
#define SERVICETHREE_CASSA 0.066667  //u2 3 gusti gelato          [task/s]

//tasso di servizio verifica
#define SERVICEONE_VERIFY 0.116667        //u1 1 gusto gelato            [task/s]
#define SERVICETWO_VERIFY 0.116667        //u2 2 gusti gelato            [task/s]
#define SERVICETHREE_VERIFY 0.116667      //u2 3 gusti gelato          [task/s]

//tasso di servizio delay
#define SERVICEONE_DELAY 0.016667  //u1 1 gusto gelato            [task/s]
#define SERVICETWO_DELAY 0.016667  //u2 2 gusti gelato            [task/s]
#define SERVICETHREE_DELAY 0.016667  //u2 3 gusti gelato          [task/s]

//tasso di servizio Multiserver
#define SERVICEONE_MULTI 0.066667           //u1 1 gusto gelato            [task/s]
#define SERVICETWO_MULTI 0.083333    //u2 2 gusti gelato            [task/s]
#define SERVICETHREE_MULTI 0.1  //u2 3 gusti gelato          [task/s]

//streams per arrivi e servizi
#define STREAM_ARR1 0
#define STREAM_ARR2 10
#define STREAM_ARR3 20

#define STREAM_SERV_CASSA1 30
#define STREAM_SERV_CASSA2 40
#define STREAM_SERV_CASSA3 50

#define STREAM_SERV_DELAY1 60
#define STREAM_SERV_DELAY2 70
#define STREAM_SERV_DELAY3 80

#define STREAM_SERV_MULTISERVER1 90
#define STREAM_SERV_MULTISERVER2 100
#define STREAM_SERV_MULTISERVER3 110

#define STREAM_SERV_VERIFY1 120
#define STREAM_SERV_VERIFY2 130
#define STREAM_SERV_VERIFY3 140

#define STREAM_SETUP 150

//constants
#define TASK_TYPE1 1    //1 gusto gelato
#define TASK_TYPE2 2    //2 gusti gelato   
#define TASK_TYPE3 3    //3 gusti gelato

//valore massimo vaschetta di gelato
#define MAX_ICECREAM_TUB 30

//locazioni all'iterno della rete
#define DIRECT_CASSA 1          //task diretto alla cassa
#define DIRECT_VERIFY 2         //task diretto alla verifica dei gusti
#define DIRECT_MULTISERVER_FROM_VER 3    //task diretto al multiserver
#define DIRECT_MULTISERVER_FROM_DEL 4
#define DIRECT_DELAY 5          //task diretto al server di Delay
#define DIRECT_QUIT 6           //task esce dal sistema senza gelato
#define DIRECT_EXIT 7           //task esce dal sistema con gelato

#define SEED_DEFAULT 991102
#define ALPHA 0.05                //ALPHA= 0.05 NECESSARIO PER INTERVALLO DI CONFIDENZA
#define PROBABILITY 0.8           //Valore di lamda per la probabilità di routing
                                  //del server delay.

void handle_error_with_exit(char*error_string);
double min_array_associated_job(double arr[], int len, char *type);
double min_array(double arr[], int len);
double*alloc_array_double(int lenght);
void free_all_memory(double*tr_batch);
double max(double i,double j);
double min(double i,double j);
double* min_element(double *start, double *end);
void check_state_variables(int N, struct state state);
void check_state_variables_during_simulation(struct state state);
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