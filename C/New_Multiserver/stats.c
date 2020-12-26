#include "stats.h"
#include "rvms.h"
#include "basic.h"
#include <math.h>
#include <stdlib.h>

void calculate_mean_and_deviation(double *array, int length, double *mean,
                                  double *deviation) {//calcola media e deviazione standard con un solo ciclo for
    if (array == NULL || length <= 0 || mean == NULL || deviation == NULL) {
        handle_error_with_exit("error in calculate mean_and_deviation\n");
    }
    double m = 0.0;
    double res = 0.0;
    for (int i = 0; i < length; i++) {
        m += array[i];
        res = res + ((array[i]) * (array[i]));

    }
    m = m / length;
    *mean = m;
    *deviation = res - length * m * m;
    return;

}

int fattoriale(int n) {
    if (n < 0) return -1; /* Fattoriale non e' definito per interi negativi! */

    if (n == 0) return 1;
    else return n * fattoriale(n - 1);
}

void calculate_and_print_interval(double *batch, char *string) {
    double alpha = 0.05;
    double t, delta;//t=valore critico della student,delta=lunghezza intervallo/2

    double mean = 0.0, s = 0.0;
    if (string == NULL) {
        handle_error_with_exit("error  in calculate and print interval");
    }
    t = idfStudent(NUM_BATCH - 1, 1 - alpha / 2);//calcolo del valore critico
    calculate_mean_and_deviation(batch, NUM_BATCH, &mean, &s);
    delta = (double) t * s / (sqrt(NUM_BATCH - 1));//calcolo di delta
    printf("%s:\n", string);
    printf("%lf +/- %lf = (%lf, %lf)\n\n", mean, delta, mean - delta, mean + delta);//stampa intervallo
}


void print_en(double *E_n_sys, double *E_n_sys1, double *E_n_sys2, double *E_n_sys3,
              double *E_n_ver, double *E_n_ver1, double *E_n_ver2, double *E_n_ver3,
              double *E_n_del, double *E_n_del1, double *E_n_del2, double *E_n_del3,
              double *E_n_ser, double *E_n_ser1, double *E_n_ser2, double *E_n_ser3) {

    printf("\nUtenti Medi E[N]:\n\n");
    calculate_and_print_interval(E_n_sys, "Average system E[N]");
    calculate_and_print_interval(E_n_sys1, "Average system E[N] type1");
    calculate_and_print_interval(E_n_sys2, "Average system E[N] type2");
    calculate_and_print_interval(E_n_sys3, "Average system E[N] type3");

    calculate_and_print_interval(E_n_ver, "Average verifica E[N]");
    calculate_and_print_interval(E_n_ver1, "Average verifica E[N] type1");
    calculate_and_print_interval(E_n_ver2, "Average verifica E[N] type2");
    calculate_and_print_interval(E_n_ver3, "Average verifica E[N] type3");

    calculate_and_print_interval(E_n_del, "Average delay E[N]");
    calculate_and_print_interval(E_n_del1, "Average delay E[N] type1");
    calculate_and_print_interval(E_n_del2, "Average delay E[N] type2");
    calculate_and_print_interval(E_n_del3, "Average delay E[N] type3");

    calculate_and_print_interval(E_n_ser, "Average multiserver E[N]");
    calculate_and_print_interval(E_n_ser1, "Average multiserver E[N] type1");
    calculate_and_print_interval(E_n_ser2, "Average multiserver E[N] type2");
    calculate_and_print_interval(E_n_ser3, "Average multiserver E[N] type3");
    printf("\n\n");

}

void print_all(double *tr_batch, double *tr_type1_batch, double *tr_type2_batch, double *tr_type3_batch,
               double *tr_verifica, double *tr_type1_verifica, double *tr_type2_verifica, double *tr_type3_verifica,
               double *tr_delay, double *tr_type1_delay, double *tr_type2_delay, double *tr_type3_delay,
               double *tr_multiserver, double *tr_type1_multiserver, double *tr_type2_multiserver,
               double *tr_type3_multiserver,
               double *response_batch, double *response_type1_batch, double *response_type2_batch,
               double *response_type3_batch,
               double *response_verifica, double *response_type1_verifica, double *response_type2_verifica,
               double *response_type3_verifica,
               double *response_delay, double *response_type1_delay, double *response_type2_delay,
               double *response_type3_delay,
               double *response_multiserver, double *response_type1_multiserver, double *response_type2_multiserver,
               double *response_type3_multiserver) {

    printf("\nTEMPI DI RISPOSTA\n\n");
    calculate_and_print_interval(response_batch, "Average system response time");
    calculate_and_print_interval(response_type1_batch, "Average system response time type1");
    calculate_and_print_interval(response_type2_batch, "Average system response time type2");
    calculate_and_print_interval(response_type3_batch, "Average system response time type3");

    calculate_and_print_interval(response_verifica, "Average verifica response time");
    calculate_and_print_interval(response_type1_verifica, "Average verifica response time type1");
    calculate_and_print_interval(response_type2_verifica, "Average verifica response time type2");
    calculate_and_print_interval(response_type3_verifica, "Average verifica response time type3");

    calculate_and_print_interval(response_delay, "Average delay response time");
    calculate_and_print_interval(response_type1_delay, "Average delay response time type1");
    calculate_and_print_interval(response_type2_delay, "Average delay response time type2");
    calculate_and_print_interval(response_type3_delay, "Average delay response time type3");

    calculate_and_print_interval(response_multiserver, "Average multiserver response time");
    calculate_and_print_interval(response_type1_multiserver, "Average multiserver response time type1");
    calculate_and_print_interval(response_type2_multiserver, "Average multiserver response time type2");
    calculate_and_print_interval(response_type3_multiserver, "Average multiserver response time type3");
    printf("\n\n");

    printf("\nTHROUGHPUT\n\n");
    calculate_and_print_interval(tr_batch, "Throughput system");
    calculate_and_print_interval(tr_type1_batch, "Throughput system type1");
    calculate_and_print_interval(tr_type2_batch, "Throughput system type2");
    calculate_and_print_interval(tr_type3_batch, "Throughput system type3");

    calculate_and_print_interval(tr_verifica, "Throughput verifica");
    calculate_and_print_interval(tr_type1_verifica, "Throughput verifica type1");
    calculate_and_print_interval(tr_type2_verifica, "Throughput verifica type2");
    calculate_and_print_interval(tr_type3_verifica, "Throughput verifica type3");

    calculate_and_print_interval(tr_delay, "Throughput delay");
    calculate_and_print_interval(tr_type1_delay, "Throughput delay type1");
    calculate_and_print_interval(tr_type2_delay, "Throughput delay type2");
    calculate_and_print_interval(tr_type3_delay, "Throughput delay type3");

    calculate_and_print_interval(tr_multiserver, "Throughput multiserver");
    calculate_and_print_interval(tr_type1_multiserver, "Throughput multiserver type1");
    calculate_and_print_interval(tr_type2_multiserver, "Throughput multiserver type2");
    calculate_and_print_interval(tr_type3_multiserver, "Throughput multiserver type3");
    printf("\n\n");


}


void calculate_batch(double time_next, struct state state, struct area area, struct last_state *last_state, int *i,
                     double *tr_batch, double *tr_type1_batch, double *tr_type2_batch, double *tr_type3_batch,
                     double *tr_verifica, double *tr_type1_verifica, double *tr_type2_verifica,
                     double *tr_type3_verifica,
                     double *tr_delay, double *tr_type1_delay, double *tr_type2_delay, double *tr_type3_delay,
                     double *tr_multiserver, double *tr_type1_multiserver, double *tr_type2_multiserver,
                     double *tr_type3_multiserver,
                     double *response_batch, double *response_type1_batch, double *response_type2_batch,
                     double *response_type3_batch,
                     double *response_verifica, double *response_type1_verifica, double *response_type2_verifica,
                     double *response_type3_verifica,
                     double *response_delay, double *response_type1_delay, double *response_type2_delay,
                     double *response_type3_delay,
                     double *response_multiserver, double *response_type1_multiserver,
                     double *response_type2_multiserver, double *response_type3_multiserver,
                     double *E_n_sys, double *E_n_sys_1, double *E_n_sys_2, double *E_n_sys_3,
                     double *E_n_ver, double *E_n_ver_1, double *E_n_ver_2, double *E_n_ver_3,
                     double *E_n_del, double *E_n_del_1, double *E_n_del_2, double *E_n_del_3,
                     double *E_n_serv, double *E_n_serv_1, double *E_n_serv_2, double *E_n_serv_3) {

    ///////CALCOLO THROUGHPUT////

    tr_batch[*i] = (state.total_completed - last_state->last_num_job_completed) /
                   (time_next - last_state->last_observed_time);//batch[i] del throughput
    tr_type1_batch[*i] = (double) (state.total_job1_completed - last_state->last_num_job_1_completed_total) /
                         (time_next - last_state->last_observed_time);
    tr_type2_batch[*i] = (double) (state.total_job2_completed - last_state->last_num_job_2_completed_total) /
                         (time_next - last_state->last_observed_time);
    tr_type3_batch[*i] = (double) (state.total_job3_completed - last_state->last_num_job_3_completed_total) /
                         (time_next - last_state->last_observed_time);


    tr_verifica[*i] = (double) ((state.total_job1_verify + state.total_job2_verify + state.total_job3_verify) -
                                (last_state->last_num_job_1_verifica_total + last_state->last_num_job_2_verifica_total +
                                 last_state->last_num_job_3_verifica_total)) /
                      (time_next - last_state->last_observed_time);
    tr_type1_verifica[*i] = (double) (state.total_job1_verify - last_state->last_num_job_1_verifica_total) /
                            (time_next - last_state->last_observed_time);
    tr_type2_verifica[*i] = (double) (state.total_job2_verify - last_state->last_num_job_2_verifica_total) /
                            (time_next - last_state->last_observed_time);
    tr_type3_verifica[*i] = (double) (state.total_job3_verify - last_state->last_num_job_3_verifica_total) /
                            (time_next - last_state->last_observed_time);

    tr_delay[*i] = (double) ((state.total_job1_delay + state.total_job2_delay + state.total_job3_delay) -
                             (last_state->last_num_job_1_delay_total + last_state->last_num_job_2_delay_total +
                              last_state->last_num_job_3_delay_total)) / (time_next - last_state->last_observed_time);
    tr_type1_delay[*i] = (double) (state.total_job1_delay - last_state->last_num_job_1_delay_total) /
                         (time_next - last_state->last_observed_time);
    tr_type2_delay[*i] = (double) (state.total_job2_delay - last_state->last_num_job_2_delay_total) /
                         (time_next - last_state->last_observed_time);
    tr_type3_delay[*i] = (double) (state.total_job3_delay - last_state->last_num_job_3_delay_total) /
                         (time_next - last_state->last_observed_time);

    tr_multiserver[*i] = (double) ((state.total_job1_multi + state.total_job2_multi + state.total_job3_multi) -
                                   (last_state->last_num_job_1_multiserver_total +
                                    last_state->last_num_job_2_multiserver_total +
                                    last_state->last_num_job_3_multiserver_total)) /
                         (time_next - last_state->last_observed_time);
    tr_type1_multiserver[*i] = (double) (state.total_job1_multi - last_state->last_num_job_1_multiserver_total) /
                               (time_next - last_state->last_observed_time);
    tr_type2_multiserver[*i] = (double) (state.total_job2_multi - last_state->last_num_job_2_multiserver_total) /
                               (time_next - last_state->last_observed_time);
    tr_type3_multiserver[*i] = (double) (state.total_job3_multi - last_state->last_num_job_3_multiserver_total) /
                               (time_next - last_state->last_observed_time);

    /////////////////////


    ////Utilizzazione ////////////

    double rho_verifica = area.service_v / time_next;
    double rho_delay = area.service_d / time_next;
    double rho_service = RHOS;

    //printf("rhos %f\n", rho_service);

    double rho_verifica_1 = area.service_v_1 / time_next;
    double rho_delay_1 = area.service_d_1 / time_next;
    double rho_service_1 = area.service_s_1 / (NUM_MAX_SERVER * time_next);

    double rho_verifica_2 = area.service_v_2 / time_next;
    double rho_delay_2 = area.service_d_2 / time_next;
    double rho_service_2 = area.service_s_2 / (NUM_MAX_SERVER * time_next);

    double rho_verifica_3 = area.service_v_3 / time_next;
    double rho_delay_3 = area.service_d_3 / time_next;
    double rho_service_3 = area.service_s_3 / (NUM_MAX_SERVER * time_next);

    ////Probabilità Multiserver Pieno

    double p_0;
    for (int i = 0; i < NUM_MAX_SERVER; i++) {
        p_0 += (pow(NUM_MAX_SERVER * rho_service, i)) / (fattoriale(i));
    }
    p_0 += (pow(NUM_MAX_SERVER * rho_service, NUM_MAX_SERVER) / (fattoriale(NUM_MAX_SERVER) * (1 - rho_service)));
    double Pq =
            ((pow(NUM_MAX_SERVER * rho_service, NUM_MAX_SERVER)) / (fattoriale(NUM_MAX_SERVER) * (1 - rho_service))) *
            (pow(p_0, -1));

    ////Numero Medio di JOB//////

    E_n_ver[*i] = rho_verifica / (1 - rho_verifica);
    E_n_del[*i] = rho_delay / (1 - rho_delay);
    E_n_serv[*i] = Pq * (rho_service / (1 - rho_service)) + (NUM_MAX_SERVER * rho_service);

    E_n_sys[*i] = E_n_ver[*i] + E_n_del[*i] + E_n_serv[*i];
    //printf("Ens %f\n", E_n_serv);

    E_n_ver_1[*i] = rho_verifica_1 / (1 - rho_verifica);
    E_n_del_1[*i] = rho_delay_1 / (1 - rho_delay);
    E_n_serv_1[*i] = Pq * (rho_service_1 / (1 - rho_service)) + (NUM_MAX_SERVER * rho_service_1);

    E_n_sys_1[*i] = E_n_ver_1[*i] + E_n_del_1[*i] + E_n_serv_1[*i];

    E_n_ver_2[*i] = rho_verifica_2 / (1 - rho_verifica);
    E_n_del_2[*i] = rho_delay_2 / (1 - rho_delay);
    E_n_serv_2[*i] = Pq * (rho_service_2 / (1 - rho_service)) + (NUM_MAX_SERVER * rho_service_2);

    E_n_sys_2[*i] = E_n_ver_2[*i] + E_n_del_2[*i] + E_n_serv_2[*i];

    E_n_ver_3[*i] = rho_verifica_3 / (1 - rho_verifica);
    E_n_del_3[*i] = rho_delay_3 / (1 - rho_delay);
    E_n_serv_3[*i] = Pq * (rho_service_3 / (1 - rho_service)) + (NUM_MAX_SERVER * rho_service_3);

    E_n_sys_3[*i] = E_n_ver_3[*i] + E_n_del_3[*i] + E_n_serv_3[*i];

    ////Tassi di Visita

    double const lambda_tot = ARRIVALONE + ARRIVALTWO + ARRIVALTHREE;

    double v_1_verifica = tr_type1_verifica[*i] / ARRIVALONE;
    double v_2_verifica = tr_type2_verifica[*i] / ARRIVALTWO;
    double v_3_verifica = tr_type3_verifica[*i] / ARRIVALTHREE;

    double v_1_delay = tr_type1_delay[*i] / ARRIVALONE;
    double v_2_delay = tr_type2_delay[*i] / ARRIVALTWO;
    double v_3_delay = tr_type3_delay[*i] / ARRIVALTHREE;

    double v_1_service = tr_type1_multiserver[*i] / ARRIVALONE;
    double v_2_service = tr_type2_multiserver[*i] / ARRIVALTWO;
    double v_3_service = tr_type3_multiserver[*i] / ARRIVALTHREE;

    double v_verifica = tr_verifica[*i] / lambda_tot;
    double v_delay = tr_delay[*i] / lambda_tot;
    double v_service = tr_multiserver[*i] / lambda_tot;

    ////CALCOLO TEMPI DI RISPOSTA

    response_verifica[*i] = E_n_ver[*i] / tr_verifica[*i];
    response_type1_verifica[*i] = E_n_ver_1[*i] / tr_type1_verifica[*i];
    response_type2_verifica[*i] = E_n_ver_2[*i] / tr_type2_verifica[*i];
    response_type3_verifica[*i] = E_n_ver_3[*i] / tr_type3_verifica[*i];

    response_delay[*i] = E_n_del[*i] / tr_delay[*i];
    response_type1_delay[*i] = E_n_del_1[*i] / tr_type1_delay[*i];
    response_type2_delay[*i] = E_n_del_2[*i] / tr_type2_delay[*i];
    response_type3_delay[*i] = E_n_del_3[*i] / tr_type3_delay[*i];

    response_multiserver[*i] = E_n_serv[*i] / tr_multiserver[*i];
    response_type1_multiserver[*i] = E_n_serv_1[*i] / tr_type1_multiserver[*i];
    response_type2_multiserver[*i] = E_n_serv_2[*i] / tr_type2_multiserver[*i];
    response_type3_multiserver[*i] = E_n_serv_3[*i] / tr_type3_multiserver[*i];

    response_type1_batch[*i] = (response_type1_verifica[*i] * v_1_verifica) + (response_type1_delay[*i] * v_1_delay) +
                               (response_type1_multiserver[*i] * v_1_service);
    response_type2_batch[*i] = (response_type2_verifica[*i] * v_2_verifica) + (response_type2_delay[*i] * v_2_delay) +
                               (response_type2_multiserver[*i] * v_2_service);
    response_type3_batch[*i] = (response_type3_verifica[*i] * v_3_verifica) + (response_type3_delay[*i] * v_3_delay) +
                               (response_type3_multiserver[*i] * v_3_service);
    response_batch[*i] = (response_verifica[*i] * v_verifica) + (response_delay[*i] * v_delay) +
                         (response_multiserver[*i] * v_service);

    //printf("rb %f\n", response_batch[*i]);

    last_state->last_num_job_completed = state.total_completed;
    last_state->last_numberOfUsers = state.total_system;

    ///TOTALI
    last_state->last_num_job_1_completed_total = state.total_job1_completed;
    last_state->last_num_job_2_completed_total = state.total_job2_completed;
    last_state->last_num_job_3_completed_total = state.total_job3_completed;

    last_state->last_num_job_1_verifica_total = state.total_job1_verify;
    last_state->last_num_job_2_verifica_total = state.total_job2_verify;
    last_state->last_num_job_3_verifica_total = state.total_job3_verify;

    last_state->last_num_job_1_delay_total = state.total_job1_delay;
    last_state->last_num_job_2_delay_total = state.total_job2_delay;
    last_state->last_num_job_3_delay_total = state.total_job3_delay;

    last_state->last_num_job_1_multiserver_total = state.total_job1_multi;
    last_state->last_num_job_2_multiserver_total = state.total_job2_multi;
    last_state->last_num_job_3_multiserver_total = state.total_job3_multi;

    last_state->last_num_job_1_arrived_total = state.total_job1;
    last_state->last_num_job_2_arrived_total = state.total_job2;
    last_state->last_num_job_3_arrived_total = state.total_job3;

    ///ATTUALI
    last_state->last_num_job_1_completed_actual = state.actual_job1;
    last_state->last_num_job_2_completed_actual = state.actual_job2;
    last_state->last_num_job_3_completed_actual = state.actual_job3;

    last_state->last_num_job_1_verifica_actual = state.actual_job1_verify;
    last_state->last_num_job_2_verifica_actual = state.actual_job2_verify;
    last_state->last_num_job_3_verifica_actual = state.actual_job3_verify;

    last_state->last_num_job_1_delay_actual = state.actual_job1_delay;
    last_state->last_num_job_2_delay_actual = state.actual_job2_delay;
    last_state->last_num_job_3_delay_actual = state.actual_job3_delay;

    last_state->last_num_job_1_multiserver_actual = state.actual_job1_multi;
    last_state->last_num_job_2_multiserver_actual = state.actual_job2_multi;
    last_state->last_num_job_3_multiserver_actual = state.actual_job3_multi;

    last_state->last_num_job_1_arrived_actual = state.actual_job1;
    last_state->last_num_job_2_arrived_actual = state.actual_job2;
    last_state->last_num_job_3_arrived_actual = state.actual_job3;


    ///AREA
    last_state->last_area = area.number_job_type1 + area.number_job_type2 + area.number_job_type3;
    last_state->last_area_type1 = area.number_job_type1;
    last_state->last_area_type2 = area.number_job_type2;
    last_state->last_area_type3 = area.number_job_type3;
    last_state->last_area_type1_verifica = area.number_job_type1_verify;
    last_state->last_area_type2_verifica = area.number_job_type2_verify;
    last_state->last_area_type3_verifica = area.number_job_type3_verify;
    last_state->last_area_type1_delay = area.number_job_type1_delay;
    last_state->last_area_type2_delay = area.number_job_type2_delay;
    last_state->last_area_type3_delay = area.number_job_type3_delay;
    last_state->last_area_type1_multiserver = area.number_job_type1_multiserver;
    last_state->last_area_type2_multiserver = area.number_job_type2_multiserver;
    last_state->last_area_type3_multiserver = area.number_job_type3_multiserver;


    last_state->last_area_service = area.service;


    (*i)++;//aumento batch i;
    last_state->last_observed_time = time_next;
}