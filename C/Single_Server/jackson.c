#include <stdio.h>
#include <stdlib.h>

double lambda1 = 3.0;//frequenza arrivi di tipo 1
double lambda2 = 3.0;//frequenza arrivi di tipo 2
double lambda3 = 3.0;
double lambda_tot = 9.0;//frequenza arrivi totale

double mu_verifica = 13; //frequenza di servizio job cassa+Verifica
double mu_delay = 2;    //frequenza di servizio job Delay Server
double mu_service = 13; //frequenza di servizio job di tipo 1 Service Server
//double mu2_service = 6; //frequenza di servizio job di tipo 2 Service Server
//double mu3_service = 7;

//valori delle probabilità
double p = 0.8;
double pDelay = 0.063996;
double pService = 0.948820;

int main(){

    double lambda_v = lambda_tot;
    double lambda_d = pDelay*lambda_v;
    double lambda_s = pService*lambda_v + p*lambda_d;

    double E_s_v = 1/mu_verifica;
    double E_s_d = 1/mu_delay;
    double E_s_s = 1/mu_service;

    double rho_v = lambda_v/mu_verifica;
    double rho_d = lambda_d/mu_delay;
    double rho_s = lambda_s/mu_service;

    double E_t_q_v = (rho_v*E_s_v)/(1-rho_v);
    double E_t_q_d = (rho_d*E_s_d)/(1-rho_d);
    double E_t_q_s = (rho_s*E_s_s)/(1-rho_s);

    double E_n_v = rho_v/(1-rho_v);
    double E_n_d = rho_d/(1-rho_d);
    double E_n_s = rho_s/(1-rho_s);
    double E_n_tot = E_n_v+E_n_s+E_n_d;

    double visit_v = lambda_v/lambda_tot;
    double visit_d = lambda_d/lambda_tot;
    double visit_s = lambda_s/lambda_tot;

//    double E_t_s_v = 1/(mu_verifica - lambda_v);
//    double E_t_s_d = 1/(mu_delay - lambda_d);
//    double E_t_s_s = 1/(mu_service - lambda_s);
    double E_t_s_v = E_t_q_v + E_s_v;
    double E_t_s_d = E_t_q_d + E_s_d;
    double E_t_s_s = E_t_q_s + E_s_s;
    double E_t_s_tot = visit_v*E_t_s_v + visit_d*E_t_s_d + visit_s*E_t_s_s;

    double X_v = E_n_v/E_t_s_v;
    double X_d = E_n_d/E_t_s_d;
    double X_s = E_n_s/E_t_s_s;

    printf("rho_v :%f\n",rho_v);
    printf("rho_d :%f\n",rho_d);
    printf("rho_s :%f\n",rho_s);
    printf("E_n_v :%f\n",E_n_v);
    printf("E_n_d :%f\n",E_n_d);
    printf("E_n_s :%f\n",E_n_s);
    printf("E_n_tot :%f\n",E_n_tot);
    printf("visit_v :%f\n",visit_v);
    printf("visit_d :%f\n",visit_d);
    printf("visit_s :%f\n",visit_s);
    printf("E_t_s_v :%f\n",E_t_s_v);
    printf("E_t_s_d :%f\n",E_t_s_d);
    printf("E_t_s_s :%f\n",E_t_s_s);
    printf("E_t_s_tot :%f\n",E_t_s_tot);
    printf("X_v :%f\n",X_v);
    printf("X_d :%f\n",X_d);
    printf("X_s :%f\n",X_s);

}