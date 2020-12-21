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

//double p000000 = 0.1712334898801322335959441;
//double p010100 = 0.0978477085029327009468858;
//double p100100 = 0.0733857813771995187712704;
//double p001100 = 0.1223096356286658692447133;
//double p010010 = 0.0438330336734757686212305;
//double p010001 = 0.1369890932822097617815871;
//double p100010 = 0.0328747752551068264659229;
//double p100001 = 0.1284272749520716516702379;
//double p001010 = 0.0547912920918447038376442;
//double p001001 = 0.1383079153563609720034577;

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

int main(){

    //statistiche Server Verifica tipo 1

    //probabilità di avere 0/1 Job all'interno del server verifica
    double p_0_verifica = p000000 + p010010 + p010001 + p100010 + p100001 + p001010 + p001001 + p010100 + p001100;
    double p_1_verifica = p100100 ;

    //utilizzazione del Server verifica
    double u_verifica = 1 - p_0_verifica;

    //throughput
    double x0_verifica = u_verifica * mu_verifica;

    //popolazione media
    double E_n_verifica = p_1_verifica;

    //Tempo di risposta medio
    double E_ts_verifica = E_n_verifica / x0_verifica;

    printf("\n");
    printf("p10 - Verifica: %f\n", p_0_verifica);
    printf("p11 - Verifica:%f\n", p_1_verifica);
    printf("Utilizzazione verifica: %f\n", u_verifica);
    printf("THR Verifica: %f\n", x0_verifica);
    printf("E_n_verifica %f\n", E_n_verifica);
    printf("E_ts_verifica %f\n", E_ts_verifica);

    //statistiche Server Delay

    //probabilità di avere 0/1 Job all'interno del server
    double p_0_delay = p000000 + p010100 + p100100 + p001100 + p010001 + p100001 + p001001;
    double p_1_delay = p010010 + p100010 + p001010;

    //utilizzazione del Server verifica
    double u_delay = 1 - p_0_delay;

    //throughput
    double x0_delay = u_delay * mu_delay;

    //popolazione media
    double E_n_delay = p_1_delay;

    //Tempo di risposta medio
    double E_ts_delay = E_n_delay / x0_delay;

    printf("\n");
    printf("p10 - Delay: %f\n", p_0_delay);
    printf("p11 - Delay: %f\n", p_1_delay);
    printf("Utilizzazione delay: %f\n", u_delay);
    printf("THR Delay:%f\n", x0_delay);
    printf("E_n_delay %f\n", E_n_delay);
    printf("E_ts_delay %f\n", E_ts_delay);


    //statistiche Service Server tipo 1

    //probabilità di avere 0/1 Job all'interno del server
    double p_0_service1 = p000000 + p010100 + p100100 + p001100 + p010010 + p100010 + p100001 + p001010 + p001001;
    double p_1_service1 = p100001 ;

    //utilizzazione del Server verifica
    double u_service1 = 1 - p_0_service1;

    //throughput
    double x0_service1 = u_service1 * mu1_service;

    //popolazione media
    double E_n_service1 = p_1_service1;

    //Tempo di risposta medio
    double E_ts_service1 = E_n_service1 / x0_service1;

    printf("\n");
    printf("p10 - Service1: %f\n", p_0_service1);
    printf("p11 - Service1: %f\n", p_1_service1);
    printf("Utilizzazione Service1: %f\n", u_service1);
    printf("THR Service1:%f\n", x0_service1);
    printf("E_n_Service1: %f\n", E_n_service1);
    printf("E_ts_Service1: %f\n", E_ts_service1);

    //statistiche Service Server tipo 2

    //probabilità di avere 0/1 Job all'interno del server
    double p_0_service2 = p000000 + p010100 + p100100 + p001100 + p010010 + p010001 + p100010 + p001010 + p001001;
    double p_1_service2 = p010001 ;

    //utilizzazione del Server verifica
    double u_service2 = 1 - p_0_service2;

    //throughput
    double x0_service2 = u_service2 * mu2_service;

    //popolazione media
    double E_n_service2 = p_1_service2;

    //Tempo di risposta medio
    double E_ts_service2 = E_n_service2 / x0_service2;

    printf("\n");
    printf("p10 - Service2: %f\n", p_0_service2);
    printf("p11 - Service2: %f\n", p_1_service2);
    printf("Utilizzazione Service2: %f\n", u_service2);
    printf("THR Service2:%f\n", x0_service2);
    printf("E_n_Service2: %f\n", E_n_service2);
    printf("E_ts_Service2: %f\n", E_ts_service2);

    //statistiche Service Server tipo 3

    //probabilità di avere 0/1 Job all'interno del server
    double p_0_service3 = p000000 + p010100 + p100100 + p001100 + p010010 + p010001 + p100010 + p100001 + p001010;
    double p_1_service3 = p001001 ;

    //utilizzazione del Server verifica
    double u_service3 = 1 - p_0_service3;

    //throughput
    double x0_service3 = u_service3 * mu3_service;

    //popolazione media
    double E_n_service3 = p_1_service3;

    //Tempo di risposta medio
    double E_ts_service3 = E_n_service3 / x0_service3;

    printf("\n");
    printf("p10 - Service3: %f\n", p_0_service3);
    printf("p11 - Service3: %f\n", p_1_service3);
    printf("Utilizzazione Service3: %f\n", u_service3);
    printf("THR Service3:%f\n", x0_service3);
    printf("E_n_Service3: %f\n", E_n_service3);
    printf("E_ts_Service3: %f\n", E_ts_service3);

    return 0;
}