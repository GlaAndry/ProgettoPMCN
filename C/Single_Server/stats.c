#include "stats.h"
#include "rvms.h"
#include "basic.h"
#include <math.h>
#include <stdlib.h>

void calculate_mean_and_deviation(double*array,int length,double*mean,double*deviation){//calcola media e deviazione standard con un solo ciclo for
    if(array==NULL || length<=0|| mean== NULL || deviation==NULL){
        handle_error_with_exit("error in calculate mean_and_deviation\n");
    }
    double m=0.0;
    double  res= 0.0;
    for(int i = 0; i <length; i++){
        m+=array[i];
        res = res + ((array[i])*(array[i]));

    }
    m=m/length;
    *mean=m;
    *deviation= res - length*m*m;
    return;

}

void calculate_and_print_interval(double* batch,char*string)
{
    double alpha = 0.05;
    double t,delta;//t=valore critico della student,delta=lunghezza intervallo/2

    double mean = 0.0, s = 0.0;
    if(string==NULL){
        handle_error_with_exit("error  in calculate and print interval");
    }
    t  = idfStudent(NUM_BATCH-1, 1-alpha/2);//calcolo del valore critico
    calculate_mean_and_deviation(batch,NUM_BATCH,&mean,&s);
    delta = (double) t*s/(sqrt(NUM_BATCH-1));//calcolo di delta
    printf("%s:\n",string);
    printf("%lf +/- %lf = (%lf, %lf)\n\n",mean,delta,mean-delta,mean+delta);//stampa intervallo
}

void print_all(double*tr_batch,double* tr_type1_batch,double* tr_type2_batch, double* tr_type3_batch,
               double *tr_verifica, double *tr_type1_verifica, double *tr_type2_verifica, double *tr_type3_verifica,
               double *tr_delay, double *tr_type1_delay, double *tr_type2_delay,double *tr_type3_delay,
               double *tr_multiserver, double *tr_type1_multiserver, double *tr_type2_multiserver,double *tr_type3_multiserver,
               double *response_batch, double *response_type1_batch, double *response_type2_batch, double *response_type3_batch,
               double *response_verifica, double *response_type1_verifica, double *response_type2_verifica,double *response_type3_verifica,
               double *response_delay, double *response_type1_delay, double *response_type2_delay, double *response_type3_delay,
               double *response_multiserver, double *response_type1_multiserver, double *response_type2_multiserver, double *response_type3_multiserver){

    printf("\nTEMPI DI RISPOSTA\n\n");
    calculate_and_print_interval(response_batch,"Average system response time");
    calculate_and_print_interval(response_type1_batch,"Average system response time type1");
    calculate_and_print_interval(response_type2_batch,"Average system response time type2");
    calculate_and_print_interval(response_type3_batch,"Average system response time type3");

    calculate_and_print_interval(response_verifica,"Average verifica response time");
    calculate_and_print_interval(response_type1_verifica,"Average verifica response time type1");
    calculate_and_print_interval(response_type2_verifica,"Average verifica response time type2");
    calculate_and_print_interval(response_type3_verifica,"Average verifica response time type3");

    calculate_and_print_interval(response_delay,"Average delay response time");
    calculate_and_print_interval(response_type1_delay,"Average delay response time type1");
    calculate_and_print_interval(response_type2_delay,"Average delay response time type2");
    calculate_and_print_interval(response_type3_delay,"Average delay response time type3");

    calculate_and_print_interval(response_multiserver,"Average multiserver response time");
    calculate_and_print_interval(response_type1_multiserver,"Average multiserver response time type1");
    calculate_and_print_interval(response_type2_multiserver,"Average multiserver response time type2");
    calculate_and_print_interval(response_type3_multiserver,"Average multiserver response time type3");
    printf("\n\n");

    printf("\nTHROUGHPUT\n\n");
    calculate_and_print_interval(tr_batch,"Throughput system");
    calculate_and_print_interval(tr_type1_batch,"Throughput system type1");
    calculate_and_print_interval(tr_type2_batch,"Throughput system type2");
    calculate_and_print_interval(tr_type3_batch,"Throughput system type3");

    calculate_and_print_interval(tr_verifica,"Throughput verifica");
    calculate_and_print_interval(tr_type1_verifica,"Throughput verifica type1");
    calculate_and_print_interval(tr_type2_verifica,"Throughput verifica type2");
    calculate_and_print_interval(tr_type3_verifica,"Throughput verifica type3");

    calculate_and_print_interval(tr_delay,"Throughput delay");
    calculate_and_print_interval(tr_type1_delay,"Throughput delay type1");
    calculate_and_print_interval(tr_type2_delay,"Throughput delay type2");
    calculate_and_print_interval(tr_type3_delay,"Throughput delay type3");

    calculate_and_print_interval(tr_multiserver,"Throughput multiserver");
    calculate_and_print_interval(tr_type1_multiserver,"Throughput multiserver type1");
    calculate_and_print_interval(tr_type2_multiserver,"Throughput multiserver type2");
    calculate_and_print_interval(tr_type3_multiserver,"Throughput multiserver type3");
    printf("\n\n");




/*
    printf("tr_batch:%f\n", *tr_batch);
    printf("tr_type1_batch:%f\n", *tr_type1_batch);
    printf("tr_type2_batch:%f\n", *tr_type2_batch);
    printf("tr_type3_batch:%f\n", *tr_type3_batch);
    printf("tr_verifica:%f\n", *tr_verifica);
    printf("tr_type1_verifica:%f\n", *tr_type1_verifica);
    printf("tr_type2_verifica:%f\n", *tr_type2_verifica);
    printf("tr_type3_verifica:%f\n", *tr_type3_verifica);
    printf("tr_delay:%f\n", *tr_delay);
    printf("tr_type1_delay:%f\n", *tr_type1_delay);
    printf("tr_type2_delay:%f\n", *tr_type2_delay);
    printf("tr_type3_delay:%f\n", *tr_type3_delay);
    printf("tr_multiserver:%f\n", *tr_multiserver);
    printf("tr_type1_multiserver:%f\n", *tr_type1_multiserver);
    printf("tr_type2_multiserver:%f\n", *tr_type2_multiserver);
    printf("tr_type3_multiserver:%f\n", *tr_type3_multiserver);
    printf("response_batch:%f\n", *response_batch);
    printf("response_type1_batch:%f\n", *response_type1_batch);
    printf("response_type2_batch:%f\n", *response_type2_batch);
    printf("response_type3_batch:%f\n", *response_type3_batch);
    printf("response_verifica:%f\n", *response_verifica);
    printf("response_type1_verifica:%f\n", *response_type1_verifica);
    printf("response_type2_verifica:%f\n", *response_type2_verifica);
    printf("response_type3_verifica:%f\n", *response_type3_verifica);
    printf("response_delay:%f\n", *response_delay);
    printf("response_type1_delay:%f\n", *response_type1_delay);
    printf("response_type2_delay:%f\n", *response_type2_delay);
    printf("response_type3_delay:%f\n", *response_type3_delay);
    printf("response_multiserver:%f\n", *response_multiserver);
    printf("response_type1_multiserver:%f\n", *response_type1_multiserver);
    printf("response_type2_multiserver:%f\n", *response_type2_multiserver);
    printf("response_type3_multiserver:%f\n", *response_type3_multiserver);
*/
}

void calculate_batch(double time_next,struct state state,struct area area,struct last_state*last_state,int*i
        ,double*tr_batch,double* tr_type1_batch,double* tr_type2_batch, double* tr_type3_batch,
        double *tr_verifica, double *tr_type1_verifica, double *tr_type2_verifica, double *tr_type3_verifica,
        double *tr_delay, double *tr_type1_delay, double *tr_type2_delay,double *tr_type3_delay,
        double *tr_multiserver, double *tr_type1_multiserver, double *tr_type2_multiserver,double *tr_type3_multiserver,
        double *response_batch, double *response_type1_batch, double *response_type2_batch, double *response_type3_batch,
        double *response_verifica, double *response_type1_verifica, double *response_type2_verifica,double *response_type3_verifica,
        double *response_delay, double *response_type1_delay, double *response_type2_delay, double *response_type3_delay,
        double *response_multiserver, double *response_type1_multiserver, double *response_type2_multiserver, double *response_type3_multiserver){

    int num_job_completed = state.numberOfUsers - state.number_lost_users;

    ///////CALCOLO THROUGHPUT////

    tr_batch[*i]=(num_job_completed-last_state->last_num_job_completed)/(time_next-last_state->last_observed_time);//batch[i] del throughput

    tr_type1_batch[*i] = (double) (state.job1 - last_state->last_num_job_1_completed)/(time_next-last_state->last_observed_time);
    tr_type2_batch[*i] = (double) (state.job2 - last_state->last_num_job_2_completed)/(time_next-last_state->last_observed_time);
    tr_type3_batch[*i] = (double) (state.job3 - last_state->last_num_job_3_completed)/(time_next-last_state->last_observed_time);

    tr_verifica[*i] = (double) ((state.job1_verify + state.job2_verify + state.job3_verify) - (last_state -> last_num_job_1_verifica + last_state -> last_num_job_2_verifica + last_state -> last_num_job_3_verifica))/(time_next-last_state->last_observed_time);
    tr_type1_verifica[*i] = (double) (state.job1_verify - last_state->last_num_job_1_verifica)/(time_next-last_state->last_observed_time);
    tr_type2_verifica[*i] = (double) (state.job2_verify - last_state->last_num_job_2_verifica)/(time_next-last_state->last_observed_time);
    tr_type3_verifica[*i] = (double) (state.job3_verify - last_state->last_num_job_3_verifica)/(time_next-last_state->last_observed_time);

    tr_delay[*i] = (double) ((state.job1_delay + state.job2_delay + state.job3_delay) - (last_state -> last_num_job_1_delay + last_state -> last_num_job_2_delay + last_state -> last_num_job_3_delay))/(time_next-last_state->last_observed_time);
    tr_type1_delay[*i] = (double) (state.job1_delay - last_state->last_num_job_1_delay)/(time_next-last_state->last_observed_time);
    tr_type2_delay[*i] = (double) (state.job2_delay - last_state->last_num_job_2_delay)/(time_next-last_state->last_observed_time);
    tr_type3_delay[*i] = (double) (state.job3_delay - last_state->last_num_job_3_delay)/(time_next-last_state->last_observed_time);

    tr_multiserver[*i] = (double) ((state.job1_multiserver + state.job2_multiserver + state.job3_multiserver) - (last_state -> last_num_job_1_multiserver + last_state -> last_num_job_2_multiserver + last_state -> last_num_job_3_multiserver))/(time_next-last_state->last_observed_time);
    tr_type1_multiserver[*i] = (double) (state.job1_multiserver - last_state->last_num_job_1_multiserver)/(time_next-last_state->last_observed_time);
    tr_type2_multiserver[*i] = (double) (state.job2_multiserver - last_state->last_num_job_2_multiserver)/(time_next-last_state->last_observed_time);
    tr_type3_multiserver[*i] = (double) (state.job3_multiserver - last_state->last_num_job_3_multiserver)/(time_next-last_state->last_observed_time);

    /////////////////////

    ////CALCOLO TEMPI DI RISPOSTA

    //sistema
    response_batch[*i] = (double) ((area.number_job_type1 + area.number_job_type2 + area.number_job_type3) - last_state->last_area)/(state.numberOfUsers - last_state->last_numberOfUsers);

    //tipi di Job
    response_type1_batch[*i] = (double) ((area.number_job_type1 - last_state->last_area_type1)/(state.job1 - last_state->last_num_job_1_arrived));
    response_type2_batch[*i] = (double) ((area.number_job_type2 - last_state->last_area_type2)/(state.job2 - last_state->last_num_job_2_arrived));
    response_type3_batch[*i] = (double) ((area.number_job_type3 - last_state->last_area_type3)/(state.job3 - last_state->last_num_job_3_arrived));

    //server
    response_verifica[*i] = (double) (area.number_verify - (last_state->last_area_type1_verifica + last_state->last_area_type2_verifica + last_state->last_area_type3_verifica))/((state.job1_verify + state.job2_verify + state.job3_verify)-(last_state->last_num_job_1_verifica + last_state->last_num_job_2_verifica + last_state->last_num_job_3_verifica));
    response_type1_verifica[*i] = (double) ((area.number_job_type1_verify - last_state->last_area_type1_verifica)/(state.job1_verify - last_state->last_num_job_1_verifica));
    response_type2_verifica[*i] = (double) ((area.number_job_type2_verify - last_state->last_area_type2_verifica)/(state.job2_verify - last_state->last_num_job_2_verifica));
    response_type3_verifica[*i] = (double) ((area.number_job_type3_verify - last_state->last_area_type3_verifica)/(state.job3_verify - last_state->last_num_job_3_verifica));

    response_delay[*i] = (double) (area.number_delay - (last_state->last_area_type1_delay + last_state->last_area_type2_delay + last_state->last_area_type3_delay))/((state.job1_delay + state.job2_delay + state.job3_delay)-(last_state->last_num_job_1_delay + last_state->last_num_job_2_delay + last_state->last_num_job_3_delay));
    response_type1_delay[*i] = (double) ((area.number_job_type1_verify - last_state->last_area_type1_delay)/(state.job1_delay - last_state->last_num_job_1_delay));
    response_type2_delay[*i] = (double) ((area.number_job_type2_verify - last_state->last_area_type2_delay)/(state.job2_delay - last_state->last_num_job_2_delay));
    response_type3_delay[*i] = (double) ((area.number_job_type3_verify - last_state->last_area_type3_delay)/(state.job3_delay - last_state->last_num_job_3_delay));

    response_multiserver[*i] = (double) (area.number_multi - (last_state->last_area_type1_multiserver + last_state->last_area_type2_multiserver + last_state->last_area_type3_multiserver))/((state.job1_multiserver + state.job2_multiserver + state.job3_multiserver)-(last_state->last_num_job_1_multiserver + last_state->last_num_job_2_multiserver + last_state->last_num_job_3_multiserver));
    response_type1_multiserver[*i] = (double) ((area.number_job_type1_multiserver - last_state->last_area_type1_multiserver)/(state.job1_multiserver - last_state->last_num_job_1_multiserver));
    response_type2_multiserver[*i] = (double) ((area.number_job_type2_multiserver - last_state->last_area_type2_multiserver)/(state.job2_multiserver - last_state->last_num_job_2_multiserver));
    response_type3_multiserver[*i] = (double) ((area.number_job_type3_multiserver - last_state->last_area_type3_multiserver)/(state.job3_multiserver - last_state->last_num_job_3_multiserver));


    last_state -> last_num_job_completed = num_job_completed;

    last_state -> last_num_job_1_completed = state.job1;
    last_state -> last_num_job_2_completed = state.job2;
    last_state -> last_num_job_3_completed = state.job3;

    last_state -> last_num_job_1_verifica = state.job1_verify;
    last_state -> last_num_job_2_verifica = state.job2_verify;
    last_state -> last_num_job_3_verifica = state.job3_verify;

    last_state -> last_num_job_1_delay = state.job1_delay;
    last_state -> last_num_job_2_delay = state.job2_delay;
    last_state -> last_num_job_3_delay = state.job3_delay;

    last_state -> last_num_job_1_multiserver = state.job1_multiserver;
    last_state -> last_num_job_2_multiserver = state.job2_multiserver;
    last_state -> last_num_job_3_multiserver = state.job3_multiserver;

    last_state -> last_area = area.number_job_type1 + area.number_job_type2 + area.number_job_type3;
    last_state -> last_area_type1 = area.number_job_type1;
    last_state -> last_area_type2 = area.number_job_type2;
    last_state -> last_area_type3 = area.number_job_type3;
    last_state -> last_area_type1_verifica = area.number_job_type1_verify;
    last_state -> last_area_type2_verifica = area.number_job_type2_verify;
    last_state -> last_area_type3_verifica = area.number_job_type3_verify;
    last_state -> last_area_type1_delay = area.number_job_type1_delay;
    last_state -> last_area_type2_delay = area.number_job_type2_delay;
    last_state -> last_area_type3_delay = area.number_job_type3_delay;
    last_state -> last_area_type1_multiserver = area.number_job_type1_multiserver;
    last_state -> last_area_type2_multiserver = area.number_job_type2_multiserver;
    last_state -> last_area_type3_multiserver = area.number_job_type3_multiserver;

    last_state -> last_numberOfUsers = state.numberOfUsers;
    last_state -> last_num_job_1_arrived = state.job1;
    last_state -> last_num_job_2_arrived = state.job2;
    last_state -> last_num_job_3_arrived = state.job3;

    (*i)++;//aumento batch i;
    last_state->last_observed_time = time_next;
}