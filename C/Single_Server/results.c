#include <stdio.h>
#include <stdlib.h>

double lambda1 = 3.0;//frequenza arrivi di tipo 1
double lambda2 = 4.0;//frequenza arrivi di tipo 2
double lambda3 = 5.0;
double lambda_tot = 12.0;//frequenza arrivi totale

double mu_verifica = 0.25; //frequenza di servizio job cassa+Verifica
double mu_delay = 0.10;    //frequenza di servizio job Delay Server
double mu1_service = 0.45; //frequenza di servizio job di tipo 1 Service Server
double mu2_service = 0.40; //frequenza di servizio job di tipo 2 Service Server
double mu3_service = 0.35;

//valori delle probabilità
double p = 0.8;
double pDelay = 0.063996;
double pService = 0.948820;

//soluzioni al sistema ottenuto dalla catena di markov per N=2
//double p000 = 0.0340107401391916072674881;
//double p100 = 0.0290753523120670237522845;
//double p010 = 0.0011753250343715447405468;
//double p001 = 0.0789471903219532283868531;
//double p200 = 0.0498434611064006091729617;
//double p110 = 0.0251609667667710631966393;
//double p101 = 0.1059482904340488806926857;
//double p002 = 0.2070393537539734485353193;
//double p020 = 0.0112714086044439654871185;
//double p011 = 0.4575279115267786300691455;

double p000000 = 0.0114688085653344047643021;
double p010100 = 0.1835009370453504762288333;
double p100100 = 0.1376257027840128710494128;
double p001100 = 0.2293761713066881091638294;
double p010010 = 0.0293583149178856216143796;
double p010001 = 0.1369890932822097617815871;
double p100010 = 0.0220187361884142188128699;
double p100001 = 0.0764600082754553489472471;
double p001010 = 0.0366978936473570313547832;
double p001001 = 0.1588034148563188807656843;


int main() {

    //percentuale di job di tipo 1
    double p1 = lambda1 / lambda_tot;

    //percentuale di job di tipo 2
    double p2 = lambda2 / lambda_tot;

    //percentuale di job di tipo3
    double p3 = lambda3 / lambda_tot;

    //popolazione media del Sistema
    double E_n = 0*p000000 + 1*(p010100 + p100100 + p001100 + p010010 + p010001 + p100010 + p100001 + p001010 + p001001) ;

    //percentuale di arrivi diretti verso i server del sistema
    double p_direct_verifica = 1; //tasso di visita server verifica
    double p_direct_delay = pDelay; //tasso di visita delay Server
    double p_direct_service = pService; //tasso di visita Service Server

    //lambda percentuali
    ///////////
    double lambda_verifica_p = lambda_tot*p000000; ////////////////////////
    double lambda_delay_p = mu_verifica*((lambda1 * p100100) + (lambda2 * p010100) + (lambda3*p001100))*p_direct_delay;
    double lambda_service_p = mu_verifica*((lambda1 * p100100) + (lambda2 * p010100) + (lambda3*p001100) + (mu_delay*p010010*p) + (mu_delay*p100010*p) + (mu_delay*p001010*p))*p_direct_service;

    printf("lambdap %f\n", lambda_tot*p000000);


    //utilizzazione
    double utilization = 1 - p000000; //rho
    double rho_verifica = lambda_verifica_p/(mu_verifica);
    double rho_delay = lambda_delay_p/(mu_delay);
    double rho1_service = lambda_service_p*p1/mu1_service;
    double rho2_service = lambda_service_p*p2/mu2_service;
    double rho3_service = lambda_service_p*p3/mu3_service;
    double rho_service = rho1_service*p1 + rho2_service*p2 + rho3_service*p3;


    /////////Statistiche Job tipo1///////////////////////////////
    //flusso di job di tipo 1 che entrano in verifica
    double lambda1_verifica = lambda1 * (p000000);
    //flusso di job di tipo 1 che entrano in delay
    double lambda1_delay = mu_verifica * (p100100) * p_direct_delay;
    //flusso di job di tipo 1 che entrano in Service
    double lambda1_service = mu_verifica * (p100100) * p_direct_service + mu_delay * (p100010) * p;

    //percentuale di job di tipo 1 che entrano nel server rispetto al totale dei job nel server
    double p1_verifica = lambda1_verifica / lambda_verifica_p;
    double p1_delay = lambda1_delay / lambda_delay_p;
    double p1_service = lambda1_service / lambda_service_p;

    //percentuale di job di tipo 1 che vanno nel server rispetto al totale dei job di tipo 1
    double p1_verifica_global = lambda1_verifica / lambda1;
    double p1_delay_global = lambda1_delay / lambda1;
    double p1_service_global = lambda1_service / lambda1;

    //tassi di visita
    double v1_verifica = p1_verifica_global;
    double v1_delay = p1_delay_global;
    double v1_service = p1_service_global;

    //tempo medio dei Job
    double E_s1_verifica = 1/ mu_verifica;
    double E_s1_delay = 1/ mu_delay;
    double E_s1_service = 1/ mu1_service;

    //tempo di attesa in coda
    double E_tq1_verifica = (rho_verifica*E_s1_verifica)/(1-rho_verifica);
    double E_tq1_delay = (rho_delay*E_s1_delay)/(1-rho_delay);
    double E_tq1_service = (rho_service*E_s1_service)/(1-rho_service);

    //tempo medio di risposta
    double E_ts1_verifica = E_s1_verifica + E_tq1_verifica;
    double E_ts1_delay = E_s1_delay + E_tq1_delay;
    double E_ts1_service = E_s1_service + E_tq1_service;
    //tempo medio di risposta job tipo 1
    double E_ts1 = v1_verifica * E_ts1_verifica + v1_delay * E_ts1_delay + v1_service * E_ts1_service;

    //popolazione media
    double E_n1_verifica = lambda1_verifica * E_ts1_verifica;
    double E_n1_delay = lambda1_delay * E_ts1_delay;
    double E_n1_service = lambda1_service * E_ts1_service;
    double E_n1 = E_n1_service + E_n1_delay + E_n1_verifica;

    //throughput
    double x1_verifica = mu_verifica * (p100100);
    double x1_delay = mu_delay * (p100010);
    double x1_service = mu1_service * (p100001);

    double x1_verifica_little = E_n1_verifica * mu_verifica;
    double x1_delay_little = E_n1_delay * mu_delay;
    double x1_service_little = E_n1_service * mu1_service;

    //double x1 = x1_service + x1_delay + x1_verifica;
    double x1 = x1_service;
    double x1_little = x1_service_little;
    //////////////////////////////////

    /////////Statistiche Job tipo2////
    //flusso di job di tipo 2 che entrano in verifica
    double lambda2_verifica = lambda2 * (p000000);
    //flusso di job di tipo 2 che entrano in delay
    double lambda2_delay = lambda2 * (p010100);
    //flusso di job di tipo 2 che entrano in Service
    double lambda2_service = lambda2 * (p010100 + p010010);

    //percentuale di job di tipo 2 che entrano nella server rispetto al totale dei job nel server
    double p2_verifica = lambda2_verifica / lambda_verifica_p;
    double p2_delay = lambda2_delay / lambda_delay_p;
    double p2_service = lambda2_service / lambda_service_p;

    //percentuale di job di tipo 1 che vanno nel server rispetto al totale dei job di tipo 1
    double p2_verifica_global = lambda2_verifica / lambda2;
    double p2_delay_global = lambda2_delay / lambda2;
    double p2_service_global = lambda2_service / lambda2;

    //tassi di visita
    double v2_verifica = p2_verifica_global;
    double v2_delay = p2_delay_global;
    double v2_service = p2_service_global;

    //tempo medio dei Job
    double E_s2_verifica = 1/ mu_verifica;
    double E_s2_delay = 1/ mu_delay;
    double E_s2_service = 1/ mu1_service;

    //tempo di attesa in coda
    double E_tq2_verifica = (rho_verifica*E_s2_verifica)/(1-rho_verifica);
    double E_tq2_delay = (rho_delay*E_s2_delay)/(1-rho_delay);
    double E_tq2_service = (rho_service*E_s2_service)/(1-rho_service);

    //tempo medio di risposta
    double E_ts2_verifica = E_s2_verifica;
    double E_ts2_delay = E_s2_delay;
    double E_ts2_service = E_s2_service;
    //tempo medio di risposta job tipo 1
    double E_ts2 = v2_verifica * E_ts2_verifica + v2_delay * E_ts2_delay + v2_service * E_ts2_service;

    //popolazione media
    double E_n2_verifica = lambda2_verifica * E_ts2_verifica;
    double E_n2_delay = lambda2_delay * E_ts2_delay;
    double E_n2_service = lambda2_service * E_ts2_service;
    double E_n2 = E_n2_service + E_n2_delay + E_n2_verifica;

    //throughput
    double x2_verifica = mu_verifica * (p000000);
    double x2_delay = mu_delay * (p010100);
    double x2_service = mu2_service * (p010100 + p010010);

    double x2_verifica_little = E_n2_verifica * mu_verifica;
    double x2_delay_little = E_n2_delay * mu_delay;
    double x2_service_little = E_n2_service * mu1_service;

    //double x2 = x2_service + x2_delay + x2_verifica;
    double x2 = x2_service;
    double x2_little = x2_service_little;
    //////////////////////////////////

    /////////Statistiche Job tipo2////
    //flusso di job di tipo 3 che entrano in verifica
    double lambda3_verifica = lambda3 * (p000000);
    //printf("lambda3ver %f\n", lambda3_verifica);
    //flusso di job di tipo 3 che entrano in delay
    double lambda3_delay = lambda3 * (p001100);
    //flusso di job di tipo 3 che entrano in Service
    double lambda3_service = lambda3 * (p001100 + p001010);

    //percentuale di job di tipo 3 che entrano nella server rispetto al totale dei job nel server
    double p3_verifica = lambda3_verifica / lambda_verifica_p;
    double p3_delay = lambda3_delay / lambda_delay_p;
    double p3_service = lambda3_service / lambda_service_p;

    //percentuale di job di tipo 3 che vanno nel server rispetto al totale dei job di tipo 3
    double p3_verifica_global = lambda3_verifica / lambda3;
    double p3_delay_global = lambda3_delay / lambda3;
    double p3_service_global = lambda3_service / lambda3;

    //tassi di visita
    double v3_verifica = p3_verifica_global;
    double v3_delay = p3_delay_global;
    double v3_service = p3_service_global;

    //tempo medio dei Job
    double E_s3_verifica = 1/ mu_verifica;
    double E_s3_delay = 1/ mu_delay;
    double E_s3_service = 1/ mu3_service;

    //tempo di attesa in coda
    double E_tq3_verifica = (rho_verifica*E_s3_verifica)/(1-rho_verifica);
    double E_tq3_delay = (rho_delay*E_s3_delay)/(1-rho_delay);
    double E_tq3_service = (rho_verifica*E_s3_verifica)/(1-rho_verifica);

    //tempo medio di risposta
    double E_ts3_verifica = E_s3_verifica;
    double E_ts3_delay = E_s3_delay;
    double E_ts3_service = E_s3_service;
    //tempo medio di risposta job tipo 3
    double E_ts3 = v3_verifica * E_ts3_verifica + v3_delay * E_ts3_delay + v3_service * E_ts3_service;

    //popolazione media
    double E_n3_verifica = lambda3_verifica * E_ts3_verifica;
    double E_n3_delay = lambda3_delay * E_ts3_delay;
    double E_n3_service = lambda3_service * E_ts3_service;
    double E_n3 = E_n3_service + E_n3_delay + E_n3_verifica;

    //throughput
    double x3_verifica = mu_verifica * (p000000);
    double x3_delay = mu_delay * (p001100);
    double x3_service = mu3_service * (p001100 + p001010);

    double x3_verifica_little = E_n3_verifica * mu_verifica;
    double x3_delay_little = E_n3_delay * mu_delay;
    double x3_service_little = E_n3_service * mu1_service;

    //double x3 = x3_service + x3_delay + x3_verifica;
    double x3 = x3_service;
    double x3_little = x3_service_little;
    //////////////////////////////////

    /////////Statistiche Sistema  ////
    //percentuale di job di tipo 1 che entrano nel server rispetto al totale dei job nel server
    //double p1_verifica = lambda1_verifica / lambda_verifica_p;
    //double p1_delay = lambda1_delay / lambda_delay_p;
    //double p1_service = lambda1_service / lambda_service_p;

    //percentuale di job di tipo 2 che entrano nel server rispetto al totale dei job nel server
    //double p2_verifica = lambda2_verifica / lambda_verifica_p;
    //double p2_delay = lambda2_delay / lambda_delay_p;
    //double p2_service = lambda2_service / lambda_service_p;

    //percentuale di job di tipo 2 che entrano nel server rispetto al totale dei job nel server
    //double p3_verifica = lambda3_verifica / lambda_verifica_p;
    //double p3_delay = lambda3_delay / lambda_delay_p;
    //double p3_service = lambda3_service / lambda_service_p;

    //tempo di risposta
    double E_ts_verifica = p1_verifica * E_s1_verifica + p2_verifica * E_s2_verifica + p3_verifica * E_s3_verifica;
    double E_ts_delay = p1_delay * E_s1_delay + p2_delay * E_s2_delay + p3_delay * E_s3_delay;
    double E_ts_service = p1_service * E_s1_service + p2_service * E_s2_service + p3_service * E_s3_service;
    double E_ts_system = E_ts_verifica * p_direct_verifica + E_ts_delay * p_direct_delay + E_ts_service * p_direct_service;

    //popolazione media del sistema
    double E_n_verifica = (lambda1_verifica + lambda2_verifica + lambda3_verifica) * E_ts_verifica;
    double E_n_delay = (lambda1_delay + lambda2_delay + lambda3_delay) * E_ts_delay;
    double E_n_Service = (lambda1_service + lambda2_service + lambda3_service) * E_ts_service;
    double E_n_system = E_n_verifica + E_n_delay + E_n_Service;

    //throughput
    double x0_verifica = x1_verifica + x2_verifica + x3_verifica;
    double x0_delay = x1_delay + x2_delay + x3_delay;
    double x0_service = x1_service + x2_service + x3_service;
    double x0 = x1 + x2 + x3;

    double x0_verifica_little = E_n1_verifica * mu_verifica + E_n2_verifica * mu_verifica + E_n3_verifica * mu_verifica;
    double x0_delay_little = E_n1_delay * mu_delay + E_n2_delay * mu_delay + E_n3_delay * mu_delay;
    double x0_service_little = E_n1_service * mu1_service + E_n2_service * mu2_service + E_n3_service * mu3_service;
    double x0_little = x0_service_little;
    //////////////////////////////////


    //printf("Valore di E_n:  %f\n", E_n);
    //printf("Valore dell'utilizzazione:  %f\n", utilization);

    printf("Statistiche Tipo 1 \n");
    printf("lambda1_verifica: %f\n", lambda1_verifica);
    printf("lambda1_delay: %f\n", lambda1_delay);
    printf("lambda1_service: %f\n", lambda1_service);
    printf("p1_verific:a %f\n", p1_verifica);
    printf("p1_delay: %f\n", p1_delay);
    printf("p1_service: %f\n", p1_service);
    printf("p1_verifica_global: %f\n", p1_verifica_global);
    printf("p1_delay_global: %f\n", p1_delay_global);
    printf("p1_service_global: %f\n", p1_service_global);
    printf("v1_verifica: %f\n", v1_verifica);
    printf("v1_delay: %f\n", v1_delay);
    printf("v1_service: %f\n", v1_service);
    printf("E_s1_verifica: %f\n", E_s1_verifica);
    printf("E_s1_delay: %f\n", E_s1_delay);
    printf("E_s1_service: %f\n", E_s1_service);
    printf("E_tq1_verifica: %f\n", E_tq1_verifica);
    printf("E_tq1_delay: %f\n", E_tq1_delay);
    printf("E_tq1_service: %f\n", E_tq1_service);
    printf("E_ts1_verifica: %f\n", E_ts1_verifica);
    printf("E_ts1_delay: %f\n", E_ts1_delay);
    printf("E_ts1_service: %f\n", E_ts1_service);
    printf("E_ts1: %f\n", E_ts1);
    printf("E_n1_verifica: %f\n", E_n1_verifica);
    printf("E_n1_delay: %f\n", E_n1_delay);
    printf("E_n1_service: %f\n", E_n1_service);
    printf("E_n1: %f\n", E_n1);
    printf("x1_verifica: %f\n", x1_verifica);
    printf("x1_delay: %f\n", x1_delay);
    printf("x1_service: %f\n", x1_service);
    printf("x1_verifica_little: %f\n", x1_verifica_little);
    printf("x1_delay_little: %f\n", x1_delay_little);
    printf("x1_service_little: %f\n", x1_service_little);
    printf("x1: %f\n", x1);
    printf("x1_little: %f\n", x1_little);


    printf("\nStatistiche Tipo 2 \n");

    printf("lambda2_verifica: %f\n", lambda2_verifica);
    printf("lambda2_delay: %f\n", lambda2_delay);
    printf("lambda2_service: %f\n", lambda2_service);
    printf("p2_verific:a %f\n", p2_verifica);
    printf("p2_delay: %f\n", p2_delay);
    printf("p2_service: %f\n", p2_service);
    printf("p2_verifica_global: %f\n", p2_verifica_global);
    printf("p2_delay_global: %f\n", p2_delay_global);
    printf("p2_service_global: %f\n", p2_service_global);
    printf("v2_verifica: %f\n", v2_verifica);
    printf("v2_delay: %f\n", v2_delay);
    printf("v2_service: %f\n", v2_service);
    printf("E_s2_verifica: %f\n", E_s2_verifica);
    printf("E_s2_delay: %f\n", E_s2_delay);
    printf("E_s2_service: %f\n", E_s2_service);
    printf("E_tq2_verifica: %f\n", E_tq2_verifica);
    printf("E_tq2_delay: %f\n", E_tq2_delay);
    printf("E_tq2_service: %f\n", E_tq2_service);
    printf("E_ts2_verifica: %f\n", E_ts2_verifica);
    printf("E_ts2_delay: %f\n", E_ts2_delay);
    printf("E_ts2_service: %f\n", E_ts2_service);
    printf("E_ts2: %f\n", E_ts2);
    printf("E_n2_verifica: %f\n", E_n2_verifica);
    printf("E_n2_delay: %f\n", E_n2_delay);
    printf("E_n2_service: %f\n", E_n2_service);
    printf("E_n2: %f\n", E_n2);
    printf("x2_verifica: %f\n", x2_verifica);
    printf("x2_delay: %f\n", x2_delay);
    printf("x2_service: %f\n", x2_service);
    printf("x2_verifica_little: %f\n", x2_verifica_little);
    printf("x2_delay_little: %f\n", x2_delay_little);
    printf("x2_service_little: %f\n", x2_service_little);
    printf("x2: %f\n", x2);
    printf("x2_little: %f\n", x2_little);

    printf("\nStatistiche Tipo 3 \n");

    printf("lambda3_verifica: %f\n", lambda3_verifica);
    printf("lambda3_delay: %f\n", lambda3_delay);
    printf("lambda3_service: %f\n", lambda3_service);
    printf("p3_verific:a %f\n", p3_verifica);
    printf("p3_delay: %f\n", p3_delay);
    printf("p3_service: %f\n", p3_service);
    printf("p3_verifica_global: %f\n", p3_verifica_global);
    printf("p3_delay_global: %f\n", p3_delay_global);
    printf("p3_service_global: %f\n", p3_service_global);
    printf("v3_verifica: %f\n", v3_verifica);
    printf("v3_delay: %f\n", v3_delay);
    printf("v3_service: %f\n", v3_service);
    printf("E_s3_verifica: %f\n", E_s3_verifica);
    printf("E_s3_delay: %f\n", E_s3_delay);
    printf("E_s3_service: %f\n", E_s3_service);
    printf("E_tq3_verifica: %f\n", E_tq3_verifica);
    printf("E_tq3_delay: %f\n", E_tq3_delay);
    printf("E_tq3_service: %f\n", E_tq3_service);
    printf("E_ts3_verifica: %f\n", E_ts3_verifica);
    printf("E_ts3_delay: %f\n", E_ts3_delay);
    printf("E_ts3_service: %f\n", E_ts3_service);
    printf("E_ts3: %f\n", E_ts3);
    printf("E_n3_verifica: %f\n", E_n3_verifica);
    printf("E_n3_delay: %f\n", E_n3_delay);
    printf("E_n3_service: %f\n", E_n3_service);
    printf("E_n3: %f\n", E_n3);
    printf("x3_verifica: %f\n", x3_verifica);
    printf("x3_delay: %f\n", x3_delay);
    printf("x3_service: %f\n", x3_service);
    printf("x3_verifica_little: %f\n", x3_verifica_little);
    printf("x3_delay_little: %f\n", x3_delay_little);
    printf("x3_service_little: %f\n", x3_service_little);
    printf("x3: %f\n", x3);
    printf("x3_little: %f\n", x3_little);


    printf("\nStatistiche Sistema \n");

    printf("E_ts_verifica: %f\n", E_ts_verifica);
    printf("E_ts_delay: %f\n", E_ts_delay);
    printf("E_ts_service: %f\n", E_ts_service);
    printf("E_ts_system: %f\n", E_ts_system);
    printf("E_n_verifica: %f\n", E_n_verifica);
    printf("E_n_delay: %f\n", E_n_delay);
    printf("E_n_Service: %f\n", E_n_Service);
    printf("E_n_system: %f\n", E_n_system);
    printf("x0_verifica: %f\n", x0_verifica);
    printf("x0_delay: %f\n", x0_delay);
    printf("x0_service: %f\n", x0_service);
    printf("x0: %f\n", x0);
    printf("x0_verifica_little: %f\n", x0_verifica_little);
    printf("x0_delay_little: %f\n", x0_delay_little);
    printf("x0_service_little: %f\n", x0_service_little);
    printf("x0_little: %f\n", x0_little);
    printf("rho: %f\n", utilization);
    printf("rho_verifica: %f\n", rho_verifica);
    printf("rho_delay: %f\n", rho_delay);
    printf("rho_service: %f\n", rho_service);


    printf("FEEEENE\n");

    return 0;
}