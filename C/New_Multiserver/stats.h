#include "basic.h"
#include <stdio.h>

double idf_student(long k);
double standard_dev(double* array_mean,double mean,int length);

void print_en(double*E_n_sys,double*E_n_sys_1,double* E_n_sys_2, double* E_n_sys_3,
              double*E_n_ver,double*E_n_ver_1,double* E_n_ver_2, double* E_n_ver_3,
              double*E_n_del,double*E_n_del_1,double* E_n_del_2, double* E_n_del_3,
              double*E_n_serv,double*E_n_serv_1,double* E_n_serv_2, double* E_n_serv_3);

void print_all(double*tr_batch,double* tr_type1_batch,double* tr_type2_batch, double* tr_type3_batch,
               double *tr_verifica, double *tr_type1_verifica, double *tr_type2_verifica, double *tr_type3_verifica,
               double *tr_delay, double *tr_type1_delay, double *tr_type2_delay,double *tr_type3_delay,
               double *tr_multiserver, double *tr_type1_multiserver, double *tr_type2_multiserver,double *tr_type3_multiserver,
               double *response_batch, double *response_type1_batch, double *response_type2_batch, double *response_type3_batch,
               double *response_verifica, double *response_type1_verifica, double *response_type2_verifica,double *response_type3_verifica,
               double *response_delay, double *response_type1_delay, double *response_type2_delay, double *response_type3_delay,
               double *response_multiserver, double *response_type1_multiserver, double *response_type2_multiserver, double *response_type3_multiserver);

void calculate_batch(double time_next,struct state state,struct area area,struct last_state*last_state,int*i
        ,double*tr_batch,double* tr_type1_batch,double* tr_type2_batch, double* tr_type3_batch,
                     double *tr_verifica, double *tr_type1_verifica, double *tr_type2_verifica, double *tr_type3_verifica,
                     double *tr_delay, double *tr_type1_delay, double *tr_type2_delay,double *tr_type3_delay,
                     double *tr_multiserver, double *tr_type1_multiserver, double *tr_type2_multiserver,double *tr_type3_multiserver,
                     double *response_batch, double *response_type1_batch, double *response_type2_batch, double *response_type3_batch,
                     double *response_verifica, double *response_type1_verifica, double *response_type2_verifica,double *response_type3_verifica,
                     double *response_delay, double *response_type1_delay, double *response_type2_delay, double *response_type3_delay,
                     double *response_multiserver, double *response_type1_multiserver, double *response_type2_multiserver, double *response_type3_multiserver,
                     double*E_n_sys,double*E_n_sys_1,double* E_n_sys_2, double* E_n_sys_3,
                     double*E_n_ver,double*E_n_ver_1,double* E_n_ver_2, double* E_n_ver_3,
                     double*E_n_del,double*E_n_del_1,double* E_n_del_2, double* E_n_del_3,
                     double*E_n_serv,double*E_n_serv_1,double* E_n_serv_2, double* E_n_serv_3);

void calculate_mean_and_deviation(double*array,int length,double*mean,double*deviation);
void calculate_and_print_interval(double* batch,char*string);

void print_confidence_interval(double*tr_batch,double* tr1_batch,double* tr2_batch,double* tr_cloudlet,double* tr_cloud,double* tr_cloudlet_type1,double* tr_cloudlet_type2,double* tr_cloud_type1,double* tr_cloud_type2,double*response_batch,double* response_batch_type1,double* response_batch_type2,double*resp_1_cloud,double*resp_2_cloud,double*resp_cloud
        ,double*resp_1_cloudlet,double*resp_2_cloudlet,double*resp_cloudlet,double*average_pop_cloud,double*average_pop_cloudlet);