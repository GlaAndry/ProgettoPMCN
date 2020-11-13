#include "stats.h"
#include "rvms.h"
#include "basic.h"
#include <math.h>
#include <stdlib.h>


void calculate_batch(double time_next,struct state state,struct area area,struct last_state*last_state,int*i
        ,double*tr_batch,double* tr_type1_batch,double* tr_type2_batch, double* tr_type3_batch){

    int num_job_completed = state.numberOfUsers - state.number_lost_users;

    tr_batch[*i]=(num_job_completed-last_state->last_num_job_completed)/(time_next-last_state->last_observed_time);//batch[i] del throughput

    tr_type1_batch[*i] = (double) (state.job1 - last_state->last_num_job_1_completed)/(time_next-last_state->last_observed_time);
    tr_type2_batch[*i] = (double) (state.job2 - last_state->last_num_job_2_completed)/(time_next-last_state->last_observed_time);
    tr_type3_batch[*i] = (double) (state.job3 - last_state->last_num_job_3_completed)/(time_next-last_state->last_observed_time);

    /*

    double complete_task_cloudlet_type1=state.num_task_type1_cloudlet;
    double complete_task_cloudlet_type2=state.num_task_type2_cloudlet;
    double complete_task_cloud_type1=state.num_task_type1_cloud;
    double complete_task_cloud_type2=state.num_task_type2_cloud;

    tr1_cloudlet_batch[*i] = (double) (complete_task_cloudlet_type1 - last_state->last_num_type1_cloudlet)/(time_next - last_state->last_obs);
    tr2_cloudlet_batch[*i] = (double) (complete_task_cloudlet_type2 - last_state->last_num_type2_cloudlet)/(time_next - last_state->last_obs);
    tr1_cloud_batch[*i] = (double) (complete_task_cloud_type1 - last_state->last_num_type1_cloud)/(time_next - last_state->last_obs);
    tr2_cloud_batch[*i] = (double) (complete_task_cloud_type2 - last_state->last_num_type2_cloud)/(time_next - last_state->last_obs);

    tr_cloudlet[*i] = (double) ((complete_task_cloudlet_type1 + complete_task_cloudlet_type2) - (last_state->last_num_type1_cloudlet + last_state->last_num_type2_cloudlet))/(time_next - last_state->last_obs);
    tr_cloud[*i] = (double) ((complete_task_cloud_type1 + complete_task_cloud_type2) - (last_state->last_num_type1_cloud + last_state->last_num_type2_cloud))/(time_next - last_state->last_obs);

     */

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



    /*
    last_state->last_num_type1_cloudlet = state.num_task_type1_cloudlet;
    last_state->last_num_type2_cloudlet = (state.num_task_type2_cloudlet);
    last_state->last_num_type1_cloud = state.num_task_type1_cloud;
    last_state->last_num_type2_cloud = (state.num_task_type2_cloud);
    last_state->old_area_cloud = area.cloud;
    last_state->old_area_cloudlet = area.cloudlet;
    last_state->last_area = area.type1 + area.type2;
    last_state->last_task_arrived = state.num_task_arrived;
    last_state->last_num_task1_arrived = state.num_task_type1;
    last_state->last_num_task2_arrived = state.num_task_type2;
    last_state->last_area_type1 = area.type1;
    last_state->last_area_type2 = area.type2;
    last_state->last_num_type1_completed = state.num_task_type1;
    last_state->last_num_type2_completed = state.num_task_type2;
    last_state->last_num_task_arrived = state.num_task_arrived;
    last_state->last_num_task_completed = state.num_task_completed;
    last_state->last_area_cloud_type1 = area.cloud_type1;
    last_state->last_area_cloud_type2 = area.cloud_type2;
    last_state->last_num_task_type1_cloud = state.num_task_type1_cloud;
    last_state->last_num_task_type2_cloud = state.num_task_type2_cloud;
    last_state->last_area_cloudlet_type1 = area.cloudlet_type1;
    last_state->last_area_cloudlet_type2 = area.cloudlet_type2_v;
    last_state->last_num_task_type1_cloudlet = state.num_task_type1_cloudlet;
    last_state->last_num_task_type2_cloudlet = state.num_task_type2_cloudlet;

    */

    (*i)++;//aumento batch i;
    last_state->last_observed_time = time_next;
}