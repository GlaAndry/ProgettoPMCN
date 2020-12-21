#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double const lambda1 = 3.0;//frequenza arrivi di tipo 1
double const lambda2 = 4.0;//frequenza arrivi di tipo 2
double const lambda3 = 5.0;
double lambda_tot = lambda1+lambda2+lambda3;//frequenza arrivi totale

double mu_verifica = 13; //frequenza di servizio job cassa+Verifica
double mu_delay = 2;    //frequenza di servizio job Delay Server
double mu_service = 13; //frequenza di servizio job di tipo 1 Service Server
//double mu2_service = 6; //frequenza di servizio job di tipo 2 Service Server
//double mu3_service = 7;

//valori delle probabilità
double p = 0.8;
double const pDelay = 0.063996;
double pService = (1.0-pDelay);

double m = 2; //num Servers

int fattoriale(int n)
{
    if (n < 0) return -1; /* Fattoriale non e' definito per interi negativi! */

    if (n == 0) return 1;
    else return n*fattoriale(n-1);
}

int main(){

    double lambda_v = lambda_tot;
    double lambda_d = pDelay*lambda_v;
    double lambda_s = pService*lambda_v + p*lambda_d;

    double E_s_v = 1/mu_verifica;
    double E_s_d = 1/mu_delay;
    double E_s_s_m = 1/mu_service;
    double E_s_s = E_s_s_m/m;

    double rho_v = lambda_v/mu_verifica;
    double rho_d = lambda_d/mu_delay;
    double rho_s = lambda_s/(m*mu_service);

    double p_0;
    for(int i = 0; i < m; i++){
        p_0 += (pow(m*rho_s, i))/(fattoriale(i));
    }
    p_0 += (pow(m*rho_s,m)/(fattoriale(m)*(1-rho_s)));
    //double Pq = (((pow(m,m))/(fattoriale(m)))*pow(p_0,-1)*(pow(rho_s,m)))/(1-rho_s);
    double Pq = ((pow(m*rho_s,m))/(fattoriale(m)*(1-rho_s)))*(pow(p_0,-1));

    double E_t_q_v = (rho_v*E_s_v)/(1-rho_v);
    double E_t_q_d = (rho_d*E_s_d)/(1-rho_d);
    double E_t_q_s = (Pq*E_s_s)/(1-rho_s);

    double E_n_v = rho_v/(1-rho_v);
    double E_n_d = rho_d/(1-rho_d);
    double E_n_s = m*rho_s/(1-rho_s);
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

    printf("Statistiche Sistema \n\n");
    printf("lambda_v :%f\n",lambda_v);
    printf("lambda_d :%f\n",lambda_d);
    printf("lambda_s :%f\n",lambda_s);
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


    ////statistiche tipo 1

    double lambda_v_1 = lambda1;
    double lambda_d_1 = pDelay*lambda1;
    double lambda_s_1 = pService*lambda1 + p*lambda_d_1;

    double E_s_v_1 = 1/mu_verifica;
    double E_s_d_1 = 1/mu_delay;
    double E_s_s_1_m = 1/mu_service;
    double E_s_s_1 = E_s_s_1_m/m;

    double rho_v_1 = lambda_v_1/mu_verifica;
    double rho_d_1 = lambda_d_1/mu_delay;
    double rho_s_1 = lambda_s_1/m*mu_service;

    double E_t_q_v_1 = (rho_v_1*E_s_v_1)/(1-rho_v_1);
    double E_t_q_d_1 = (rho_d_1*E_s_d_1)/(1-rho_d_1);
    double E_t_q_s_1 = (rho_s_1*E_s_s_1)/(1-rho_s_1);

    double E_n_v_1 = rho_v_1/(1-rho_v_1);
    double E_n_d_1 = rho_d_1/(1-rho_d_1);
    double E_n_s_1 = rho_s_1/(1-rho_s_1);
    double E_n_tot_1 = E_n_v_1+E_n_s_1+E_n_d_1;

    double visit_v_1 = lambda_v_1/lambda1;
    double visit_d_1 = lambda_d_1/lambda1;
    double visit_s_1 = lambda_s_1/lambda1;

    double E_t_s_v_1 = E_t_q_v_1 + E_s_v_1;
    double E_t_s_d_1 = E_t_q_d_1 + E_s_d_1;
    double E_t_s_s_1 = E_t_q_s_1 + E_s_s_1;
    double E_t_s_tot_1 = visit_v_1*E_t_s_v_1 + visit_d_1*E_t_s_d_1 + visit_s_1*E_t_s_s_1;

    double X_v_1 = E_n_v_1/E_t_s_v_1;
    double X_d_1 = E_n_d_1/E_t_s_d_1;
    double X_s_1 = E_n_s_1/E_t_s_s_1;

    printf("Statistiche tipo 1 \n\n");
    printf("rho_v_1 :%f\n",rho_v_1);
    printf("rho_d_1 :%f\n",rho_d_1);
    printf("rho_s_1 :%f\n",rho_s_1);
    printf("E_n_v_1 :%f\n",E_n_v_1);
    printf("E_n_d_1 :%f\n",E_n_d_1);
    printf("E_n_s_1 :%f\n",E_n_s_1);
    printf("E_n_tot_1 :%f\n",E_n_tot_1);
    printf("visit_v_1 :%f\n",visit_v_1);
    printf("visit_d_1 :%f\n",visit_d_1);
    printf("visit_s_1 :%f\n",visit_s_1);
    printf("E_t_s_v_1 :%f\n",E_t_s_v_1);
    printf("E_t_s_d_1 :%f\n",E_t_s_d_1);
    printf("E_t_s_s_1 :%f\n",E_t_s_s_1);
    printf("E_t_s_tot_1 :%f\n",E_t_s_tot_1);
    printf("X_v_1 :%f\n",X_v_1);
    printf("X_d_1 :%f\n",X_d_1);
    printf("X_s_1 :%f\n",X_s_1);

    ////statistiche tipo 2

    double lambda_v_2 = lambda2;
    double lambda_d_2 = pDelay*lambda2;
    double lambda_s_2 = pService*lambda2 + p*lambda_d_2;

    double E_s_v_2 = 1/mu_verifica;
    double E_s_d_2 = 1/mu_delay;
    double E_s_s_2_m = 1/mu_service;
    double E_s_s_2 = E_s_s_2_m/m;

    double rho_v_2 = lambda_v_2/mu_verifica;
    double rho_d_2 = lambda_d_2/mu_delay;
    double rho_s_2 = lambda_s_2/m*mu_service;

    double E_t_q_v_2 = (rho_v_2*E_s_v_2)/(1-rho_v_2);
    double E_t_q_d_2 = (rho_d_2*E_s_d_2)/(1-rho_d_2);
    double E_t_q_s_2 = (rho_s_2*E_s_s_2)/(1-rho_s_2);

    double E_n_v_2 = rho_v_2/(1-rho_v_2);
    double E_n_d_2 = rho_d_2/(1-rho_d_2);
    double E_n_s_2 = rho_s_2/(1-rho_s_2);
    double E_n_tot_2 = E_n_v_2+E_n_s_2+E_n_d_2;

    double visit_v_2 = lambda_v_2/lambda2;
    double visit_d_2 = lambda_d_2/lambda2;
    double visit_s_2 = lambda_s_2/lambda2;

    double E_t_s_v_2 = E_t_q_v_2 + E_s_v_2;
    double E_t_s_d_2 = E_t_q_d_2 + E_s_d_2;
    double E_t_s_s_2 = E_t_q_s_2 + E_s_s_2;
    double E_t_s_tot_2 = visit_v_2*E_t_s_v_2 + visit_d_2*E_t_s_d_2 + visit_s_2*E_t_s_s_2;

    double X_v_2 = E_n_v_2/E_t_s_v_2;
    double X_d_2 = E_n_d_2/E_t_s_d_2;
    double X_s_2 = E_n_s_2/E_t_s_s_2;

    printf("Statistiche tipo 2 \n\n");
    printf("rho_v_2 :%f\n",rho_v_2);
    printf("rho_d_2 :%f\n",rho_d_2);
    printf("rho_s_2 :%f\n",rho_s_2);
    printf("E_n_v_2 :%f\n",E_n_v_2);
    printf("E_n_d_2 :%f\n",E_n_d_2);
    printf("E_n_s_2 :%f\n",E_n_s_2);
    printf("E_n_tot_2 :%f\n",E_n_tot_2);
    printf("visit_v_2 :%f\n",visit_v_2);
    printf("visit_d_2 :%f\n",visit_d_2);
    printf("visit_s_2 :%f\n",visit_s_2);
    printf("E_t_s_v_2 :%f\n",E_t_s_v_2);
    printf("E_t_s_d_2 :%f\n",E_t_s_d_2);
    printf("E_t_s_s_2 :%f\n",E_t_s_s_2);
    printf("E_t_s_tot_2 :%f\n",E_t_s_tot_2);
    printf("X_v_2 :%f\n",X_v_2);
    printf("X_d_2 :%f\n",X_d_2);
    printf("X_s_2 :%f\n",X_s_2);

    ////statistiche tipo 2

    double lambda_v_3 = lambda3;
    double lambda_d_3 = pDelay*lambda3;
    double lambda_s_3 = pService*lambda3 + p*lambda_d_3;

    double E_s_v_3 = 1/mu_verifica;
    double E_s_d_3 = 1/mu_delay;
    double E_s_s_3_m = 1/mu_service;
    double E_s_s_3 = E_s_s_3_m/m;

    double rho_v_3 = lambda_v_3/mu_verifica;
    double rho_d_3 = lambda_d_3/mu_delay;
    double rho_s_3 = lambda_s_3/m*mu_service;

    double E_t_q_v_3 = (rho_v_3*E_s_v_3)/(1-rho_v_3);
    double E_t_q_d_3 = (rho_d_3*E_s_d_3)/(1-rho_d_3);
    double E_t_q_s_3 = (rho_s_3*E_s_s_3)/(1-rho_s_3);

    double E_n_v_3 = rho_v_3/(1-rho_v_3);
    double E_n_d_3 = rho_d_3/(1-rho_d_3);
    double E_n_s_3 = rho_s_3/(1-rho_s_3);
    double E_n_tot_3 = E_n_v_3+E_n_s_3+E_n_d_3;

    double visit_v_3 = lambda_v_3/lambda3;
    double visit_d_3 = lambda_d_3/lambda3;
    double visit_s_3 = lambda_s_3/lambda3;

    double E_t_s_v_3 = E_t_q_v_3 + E_s_v_3;
    double E_t_s_d_3 = E_t_q_d_3 + E_s_d_3;
    double E_t_s_s_3 = E_t_q_s_3 + E_s_s_3;
    double E_t_s_tot_3 = visit_v_3*E_t_s_v_3 + visit_d_3*E_t_s_d_3 + visit_s_3*E_t_s_s_3;

    double X_v_3 = E_n_v_3/E_t_s_v_3;
    double X_d_3 = E_n_d_3/E_t_s_d_3;
    double X_s_3 = E_n_s_3/E_t_s_s_3;

    printf("Statistiche tipo 3 \n\n");
    printf("rho_v_3 :%f\n",rho_v_3);
    printf("rho_d_3 :%f\n",rho_d_3);
    printf("rho_s_3 :%f\n",rho_s_3);
    printf("E_n_v_3 :%f\n",E_n_v_3);
    printf("E_n_d_3 :%f\n",E_n_d_3);
    printf("E_n_s_3 :%f\n",E_n_s_3);
    printf("E_n_tot_3 :%f\n",E_n_tot_3);
    printf("visit_v_3 :%f\n",visit_v_3);
    printf("visit_d_3 :%f\n",visit_d_3);
    printf("visit_s_3 :%f\n",visit_s_3);
    printf("E_t_s_v_3 :%f\n",E_t_s_v_3);
    printf("E_t_s_d_3 :%f\n",E_t_s_d_3);
    printf("E_t_s_s_3 :%f\n",E_t_s_s_3);
    printf("E_t_s_tot_3 :%f\n",E_t_s_tot_3);
    printf("X_v_3 :%f\n",X_v_3);
    printf("X_d_3 :%f\n",X_d_3);
    printf("X_s_3 :%f\n",X_s_3);
}