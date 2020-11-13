#include "basic.h"
#include <stdio.h>

double idf_student(long k);
double standard_dev(double* array_mean,double mean,int length);
//void print_batch(struct throughput_node* head,int count);
void print_p1_p2(struct state state);
void print_prob_dir_cloud_and_cloudlet(struct state state);
void print_throughput_type1_and_type2(struct state state,double time_current);
void print_throughput_cloudlet_type1_and_type2(struct state state,double time_current);
void print_throughput_cloud_and_cloudlet(struct state state,double time_current);
void print_throughput_system(struct state state,double time_current);
void print_throughput(struct state state,double time_current);
void print_average_population_cloudlet_type1_and_type2(struct area area,double time_current);
void print_average_population_cloud_type1_and_type2(struct area area,double time_current);
void print_average_population_cloud_and_cloudlet(struct area area,double time_current);
void print_average_population_type1_and_type2(struct area area,double time_current);
void print_average_population_system(struct area area,double time_current);
void print_average_population(struct area area,double time_current);
void print_response_time_cloudlet_type1_and_type2(struct state state,struct area area);
void print_response_time_cloud_type1_and_type2(struct state state,struct area area);
void print_response_time_type1_and_type2(struct state state,struct area area);
void print_response_time_cloudlet_and_cloud(struct state state,struct area area);
void print_response_time_system(struct state state,struct area area);
void print_response_time(struct state state,struct area area);
void print_stats(struct state state,struct area area,double time_current);
void print_tr_batch(double* tr_batch);
void calculate_batch(double time_next,struct state state,struct area area,struct last_state*last_state,int*i
        ,double*tr_batch,double* tr_type1_batch,double* tr_type2_batch, double* tr_type3_batch);
void calculate_mean_and_deviation(double*array,int length,double*mean,double*deviation);
void print_confidence_interval(double*tr_batch,double* tr1_batch,double* tr2_batch,double* tr_cloudlet,double* tr_cloud,double* tr_cloudlet_type1,double* tr_cloudlet_type2,double* tr_cloud_type1,double* tr_cloud_type2,double*response_batch,double* response_batch_type1,double* response_batch_type2,double*resp_1_cloud,double*resp_2_cloud,double*resp_cloud
        ,double*resp_1_cloudlet,double*resp_2_cloudlet,double*resp_cloudlet,double*average_pop_cloud,double*average_pop_cloudlet);