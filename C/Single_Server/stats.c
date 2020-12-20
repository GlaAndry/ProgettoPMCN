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

    ///////CALCOLO THROUGHPUT////

    tr_batch[*i]=(state.total_completed-last_state->last_num_job_completed)/(time_next-last_state->last_observed_time);//batch[i] del throughput
    tr_type1_batch[*i] = (double) (state.total_job1_completed - last_state->last_num_job_1_completed_total)/(time_next-last_state->last_observed_time);
    tr_type2_batch[*i] = (double) (state.total_job2_completed - last_state->last_num_job_2_completed_total)/(time_next-last_state->last_observed_time);
    tr_type3_batch[*i] = (double) (state.total_job3_completed - last_state->last_num_job_3_completed_total)/(time_next-last_state->last_observed_time);


    tr_verifica[*i] = (double) ((state.total_job1_verify + state.total_job2_verify + state.total_job3_verify) - (last_state -> last_num_job_1_verifica_total + last_state -> last_num_job_2_verifica_total + last_state -> last_num_job_3_verifica_total))/(time_next-last_state->last_observed_time);
    tr_type1_verifica[*i] = (double) (state.total_job1_verify - last_state->last_num_job_1_verifica_total)/(time_next-last_state->last_observed_time);
    tr_type2_verifica[*i] = (double) (state.total_job2_verify - last_state->last_num_job_2_verifica_total)/(time_next-last_state->last_observed_time);
    tr_type3_verifica[*i] = (double) (state.total_job3_verify - last_state->last_num_job_3_verifica_total)/(time_next-last_state->last_observed_time);

    tr_delay[*i] = (double) ((state.total_job1_delay + state.total_job2_delay + state.total_job3_delay) - (last_state -> last_num_job_1_delay_total + last_state -> last_num_job_2_delay_total + last_state -> last_num_job_3_delay_total))/(time_next-last_state->last_observed_time);
    tr_type1_delay[*i] = (double) (state.total_job1_delay - last_state->last_num_job_1_delay_total)/(time_next-last_state->last_observed_time);
    tr_type2_delay[*i] = (double) (state.total_job2_delay - last_state->last_num_job_2_delay_total)/(time_next-last_state->last_observed_time);
    tr_type3_delay[*i] = (double) (state.total_job3_delay - last_state->last_num_job_3_delay_total)/(time_next-last_state->last_observed_time);

    tr_multiserver[*i] = (double) ((state.total_job1_multi + state.total_job2_multi + state.total_job3_multi) - (last_state -> last_num_job_1_multiserver_total + last_state -> last_num_job_2_multiserver_total + last_state -> last_num_job_3_multiserver_total))/(time_next-last_state->last_observed_time);
    tr_type1_multiserver[*i] = (double) (state.total_job1_multi - last_state->last_num_job_1_multiserver_total)/(time_next-last_state->last_observed_time);
    tr_type2_multiserver[*i] = (double) (state.total_job2_multi - last_state->last_num_job_2_multiserver_total)/(time_next-last_state->last_observed_time);
    tr_type3_multiserver[*i] = (double) (state.total_job3_multi - last_state->last_num_job_3_multiserver_total)/(time_next-last_state->last_observed_time);

    /////////////////////

    /////////Numero medio de gente/////////////////



//    printf("1 %f\n", area.number_job_type1_verify);
//    printf("t %f\n", time_next);

    ////utilizzazione
    //double rho_sys = 0.99;

    double rho_verifica = area.service_v/time_next;
    double rho_delay = area.service_d/time_next;
    double rho_service = area.service_s/time_next;

    double rho_verifica_1 = area.service_v_1/time_next;
    double rho_delay_1 = area.service_d_1/time_next;
    double rho_service_1 = area.service_s_1/time_next;

    double rho_verifica_2 = area.service_v_2/time_next;
    double rho_delay_2 = area.service_d_2/time_next;
    double rho_service_2 = area.service_s_2/time_next;

    double rho_verifica_3 = area.service_v_3/time_next;
    double rho_delay_3 = area.service_d_3/time_next;
    double rho_service_3 = area.service_s_3/time_next;
//    printf("rho_v: %f\n", rho_verifica);
//    printf("rho_d: %f\n", rho_delay);
//    printf("rho_s: %f\n", rho_service);
    //printf("rho_sys: %f\n", rho_sys);

    //double E_n_sys = rho_sys/(1-rho_sys);

    double E_n_ver = rho_verifica/(1-rho_verifica);
    double E_n_del = rho_delay/(1-rho_delay);
    double E_n_serv = rho_service/(1-rho_service);

    double E_n_ver_1 = rho_verifica_1/(1-rho_verifica_1);
    double E_n_del_1 = rho_delay_1/(1-rho_delay_1);
    double E_n_serv_1 = rho_service_1/(1-rho_service_1);

    double E_n_ver_2 = rho_verifica_2/(1-rho_verifica_2);
    double E_n_del_2 = rho_delay_2/(1-rho_delay_2);
    double E_n_serv_2 = rho_service_2/(1-rho_service_2);

    double E_n_ver_3 = rho_verifica_3/(1-rho_verifica_3);
    double E_n_del_3 = rho_delay_3/(1-rho_delay_3);
    double E_n_serv_3 = rho_service_3/(1-rho_service_3);
//    printf("En_v %f\n", E_n_ver);
//    printf("En_d %f\n", E_n_del);
//    printf("En_s %f\n", E_n_serv);
    //printf("En_sys %f\n", E_n_sys);


    ////CALCOLO TEMPI DI RISPOSTA

    //response_batch[*i] = E_n_sys/tr_batch[*i];

    //sistema
    //response_batch[*i] = (double) ((area.service - last_state->last_area_service))/(state.total_completed - last_state->last_num_job_completed);
    response_batch[*i] = (double) ((area.number_job_type1 + area.number_job_type2 + area.number_job_type3) - last_state->last_area)/(state.total_completed - last_state->last_num_job_completed);
    response_type1_batch[*i] = (double) ((area.number_job_type1 - last_state->last_area_type1)/(state.total_job1 - last_state->last_num_job_1_arrived_total));
    //response_type1_batch[*i] = (double) ((area.service - last_state->last_area_service)/(state.total_job1 - last_state->last_num_job_1_arrived_total));
    response_type2_batch[*i] = (double) ((area.number_job_type2 - last_state->last_area_type2)/(state.total_job2 - last_state->last_num_job_2_arrived_total));
    response_type3_batch[*i] = (double) ((area.number_job_type3 - last_state->last_area_type3)/(state.total_job3 - last_state->last_num_job_3_arrived_total));

    //server
    //response_verifica[*i] = (double) (area.number_verify - (last_state->last_area_type1_verifica + last_state->last_area_type2_verifica + last_state->last_area_type3_verifica))/((state.total_job1_verify + state.total_job2_verify + state.total_job3_verify)-(last_state->last_num_job_1_verifica_total + last_state->last_num_job_2_verifica_total + last_state->last_num_job_3_verifica_total));
    //response_verifica[*i] = (double) (area.service_v)/((state.total_job1_verify + state.total_job2_verify + state.total_job3_verify));
    response_verifica[*i] = E_n_ver/tr_verifica[*i];
    response_type1_verifica[*i] = E_n_ver_1/tr_type1_verifica[*i];
    response_type2_verifica[*i] = E_n_ver_2/tr_type2_verifica[*i];
    response_type3_verifica[*i] = E_n_ver_3/tr_type3_verifica[*i];
//    response_type1_verifica[*i] = (double) ((area.number_job_type1_verify - last_state->last_area_type1_verifica)/(state.total_job1_verify - last_state->last_num_job_1_verifica_total));
//    response_type2_verifica[*i] = (double) ((area.number_job_type2_verify - last_state->last_area_type2_verifica)/(state.total_job2_verify - last_state->last_num_job_2_verifica_total));
//    response_type3_verifica[*i] = (double) ((area.number_job_type3_verify - last_state->last_area_type3_verifica)/(state.total_job3_verify - last_state->last_num_job_3_verifica_total));

    response_delay[*i] = E_n_del/tr_delay[*i];
    response_type1_delay[*i] = E_n_del_1/tr_type1_delay[*i];
    response_type2_delay[*i] = E_n_del_2/tr_type2_delay[*i];
    response_type3_delay[*i] = E_n_del_3/tr_type3_delay[*i];
    //response_delay[*i] =  (double) (area.number_delay - (last_state->last_area_type1_delay + last_state->last_area_type2_delay + last_state->last_area_type3_delay))/((state.total_job1_delay + state.total_job2_delay + state.total_job3_delay)-(last_state->last_num_job_1_delay_total + last_state->last_num_job_2_delay_total + last_state->last_num_job_3_delay_total));
    //response_delay[*i] =  (double) (area.service_d)/((state.total_job1_delay + state.total_job2_delay + state.total_job3_delay));
//    response_type1_delay[*i] = (double) ((area.number_job_type1_delay - last_state->last_area_type1_delay)/(state.total_job1_delay - last_state->last_num_job_1_delay_total));
//    response_type2_delay[*i] =  (double) ((area.number_job_type2_delay - last_state->last_area_type2_delay)/(state.total_job2_delay - last_state->last_num_job_2_delay_total));
//    response_type3_delay[*i] =  (double) ((area.number_job_type3_delay - last_state->last_area_type3_delay)/(state.total_job3_delay - last_state->last_num_job_3_delay_total));

//    response_multiserver[*i] = (double) (area.number_multi - (last_state->last_area_type1_multiserver + last_state->last_area_type2_multiserver + last_state->last_area_type3_multiserver))/((state.total_job1_multi + state.total_job2_multi + state.total_job3_multi)-(last_state->last_num_job_1_multiserver_total + last_state->last_num_job_2_multiserver_total + last_state->last_num_job_3_multiserver_total));
//    response_type1_multiserver[*i] =  (double) ((area.number_job_type1_multiserver - last_state->last_area_type1_multiserver)/(state.total_job1_multi - last_state->last_num_job_1_multiserver_total));
//    response_type2_multiserver[*i] =  (double) ((area.number_job_type2_multiserver - last_state->last_area_type2_multiserver)/(state.total_job2_multi - last_state->last_num_job_2_multiserver_total));
//    response_type3_multiserver[*i] =  (double) ((area.number_job_type3_multiserver - last_state->last_area_type3_multiserver)/(state.total_job3_multi - last_state->last_num_job_3_multiserver_total));
    response_multiserver[*i] = E_n_serv/tr_multiserver[*i];
    response_type1_multiserver[*i] = E_n_serv_1/tr_type1_multiserver[*i];
    response_type2_multiserver[*i] = E_n_serv_2/tr_type2_multiserver[*i];
    response_type3_multiserver[*i] = E_n_serv_3/tr_type3_multiserver[*i];

    last_state -> last_num_job_completed = state.total_completed;
    last_state -> last_numberOfUsers = state.total_system;

    ///TOTALI
    last_state -> last_num_job_1_completed_total = state.total_job1_completed;
    last_state -> last_num_job_2_completed_total = state.total_job2_completed;
    last_state -> last_num_job_3_completed_total = state.total_job3_completed;

    last_state -> last_num_job_1_verifica_total = state.total_job1_verify;
    last_state -> last_num_job_2_verifica_total = state.total_job2_verify;
    last_state -> last_num_job_3_verifica_total = state.total_job3_verify;

    last_state -> last_num_job_1_delay_total = state.total_job1_delay;
    last_state -> last_num_job_2_delay_total = state.total_job2_delay;
    last_state -> last_num_job_3_delay_total = state.total_job3_delay;

    last_state -> last_num_job_1_multiserver_total = state.total_job1_multi;
    last_state -> last_num_job_2_multiserver_total = state.total_job2_multi;
    last_state -> last_num_job_3_multiserver_total = state.total_job3_multi;

    last_state -> last_num_job_1_arrived_total = state.total_job1;
    last_state -> last_num_job_2_arrived_total = state.total_job2;
    last_state -> last_num_job_3_arrived_total = state.total_job3;

    ///ATTUALI
    last_state -> last_num_job_1_completed_actual = state.actual_job1;
    last_state -> last_num_job_2_completed_actual = state.actual_job2;
    last_state -> last_num_job_3_completed_actual = state.actual_job3;

    last_state -> last_num_job_1_verifica_actual = state.actual_job1_verify;
    last_state -> last_num_job_2_verifica_actual = state.actual_job2_verify;
    last_state -> last_num_job_3_verifica_actual = state.actual_job3_verify;

    last_state -> last_num_job_1_delay_actual = state.actual_job1_delay;
    last_state -> last_num_job_2_delay_actual = state.actual_job2_delay;
    last_state -> last_num_job_3_delay_actual = state.actual_job3_delay;

    last_state -> last_num_job_1_multiserver_actual = state.actual_job1_multi;
    last_state -> last_num_job_2_multiserver_actual = state.actual_job2_multi;
    last_state -> last_num_job_3_multiserver_actual = state.actual_job3_multi;

    last_state -> last_num_job_1_arrived_actual = state.actual_job1;
    last_state -> last_num_job_2_arrived_actual = state.actual_job2;
    last_state -> last_num_job_3_arrived_actual = state.actual_job3;


    ///AREA
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


    last_state -> last_area_service = area.service;


    (*i)++;//aumento batch i;
    last_state->last_observed_time = time_next;
}