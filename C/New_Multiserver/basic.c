#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "basic.h"
#include "parser.h"
#include <unistd.h>

double*alloc_array_double(int lenght){
    if(lenght<=0){
        handle_error_with_exit("error in parameter\n");
    }
    double *array=malloc(sizeof(double)*(lenght));
    if(array==NULL){
        handle_error_with_exit("error in malloc\n");
    }
    memset(array,0,sizeof(double)*lenght);
    return array;
}

void free_all_memory(double*tr_batch){ //necessario indicare tutte le variabili del sistema.
    free(tr_batch);
}

void handle_error_with_exit(char*error_string){//uccide il processo dopo essersi accorto di un errore
    if(error_string==NULL){
        printf("error string is NULL\n");
        exit(EXIT_FAILURE);
    }
    printf("%s",error_string);
    exit(EXIT_FAILURE);
}

double max(double i,double j){//ritorna il valore massimo tra i e j
    if(i<=j){
        return j;
    }
    return i;
}

double min(double i,double j){
    if(i<=j){
        return i;
    }
    return j;
}

double min_array_associated_job(double arr[], int len, char *type){
    //Ritorna il valore minimo ed assegna la tipologia di Job.
    
    double min = arr[0];
    *type = 1;

    for ( int i = 1; i < len; i++ ){
        if ( arr[i] < min ) {
            min = arr[i];
            *type = i+1;
        }
    }

    return min;
}

double min_array(double arr[], int len){

    double min = arr[0];

    for ( int i = 1; i < len; i++ ){
        if ( arr[i] < min ) {
            min = arr[i];
        }
    }

    return min;
}

double* min_element(double *start, double *end){
    
    if (start == end) return end;

    double *min = start++;
    for (; start != end; ++start)
        if (*start < *min) min = start;

    return min;
}

void check_state_variables_during_simulation(struct state state){ //da modificare per aggiungere i controlli da eseguire durante la simulazione.
    if(state.actual_job1 < 0 || state.actual_job2 < 0 || state.actual_job3 < 0){
        handle_error_with_exit("Error in Job total Count (Negative)\n");
    }
    if(state.actual_job1 + state.actual_job2 + state.actual_job3 != state.actual_system){
        handle_error_with_exit("Error in Job total Count\n");
    }
    if(state.actual_job1_verify + state.actual_job2_verify + state.actual_job3_verify != state.actual_verify){
        handle_error_with_exit("Error in Verify Job total Count\n");
    }
    if(state.actual_job1_delay + state.actual_job2_delay + state.actual_job3_delay != state.actual_delay){
        handle_error_with_exit("Error in Delay Job total Count\n");
    }
    if(state.actual_job1_multi + state.actual_job2_multi + state.actual_job3_multi != state.actual_multi){
        handle_error_with_exit("Error in Multi Job total Count\n");
    }
    return;
}

void check_state_variables_after_simulation(struct state state){
    if(state.actual_system != 0 || state.actual_job1 != 0 || state.actual_job2 != 0 || state.actual_job3 != 0){ //da modificare per aggiungere i controlli da eseguire dopo la simulazione
        handle_error_with_exit("Actual Job Different from 0\n");
    }
    if(state.actual_verify != 0 || state.actual_job1_verify != 0 || state.actual_job2_verify != 0 || state.actual_job3_verify != 0){ //da modificare per aggiungere i controlli da eseguire dopo la simulazione
        handle_error_with_exit("Actual Job Verify different from 0\n");
    }
    if(state.actual_delay != 0 || state.actual_job1_delay != 0 || state.actual_job2_delay != 0 || state.actual_job3_delay != 0){ //da modificare per aggiungere i controlli da eseguire dopo la simulazione
        handle_error_with_exit("Actual Job Delay different from 0\n");
    }
    if(state.actual_multi != 0 || state.actual_job1_multi != 0 || state.actual_job2_multi != 0 || state.actual_job3_multi != 0){ //da modificare per aggiungere i controlli da eseguire dopo la simulazione
        handle_error_with_exit("Actual Job Multiserver different from 0\n");
    }
    if(state.total_system != (state.total_job1 + state.total_job2 + state.total_job3)){ //da modificare per aggiungere i controlli da eseguire dopo la simulazione
        handle_error_with_exit("total Job System different from sum of types\n");
    }
    if(state.total_verify != (state.total_job1_verify + state.total_job2_verify + state.total_job3_verify)){ //da modificare per aggiungere i controlli da eseguire dopo la simulazione
        handle_error_with_exit("total Job Verify different from sum of types\n");
    }
    if(state.total_delay != (state.total_job1_delay + state.total_job2_delay + state.total_job3_delay)){ //da modificare per aggiungere i controlli da eseguire dopo la simulazione
        handle_error_with_exit("total Job Delay different from sum of types\n");
    }
    if(state.total_multi != (state.total_job1_multi + state.total_job2_multi + state.total_job3_multi)){ //da modificare per aggiungere i controlli da eseguire dopo la simulazione
        handle_error_with_exit("total Job Multiserver different from sum of types\n");
    }
    return;
}