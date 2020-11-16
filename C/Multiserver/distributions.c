//probability's distributions
#include <math.h>
#include "rngs.h"                      /* the multi-stream generator */
#include "basic.h"

double Exponential(double m){//ritorna un numero in modo esponenziale con media m
    if(m<=0){
        handle_error_with_exit("error in exponential\n");
    }
    return (-m * log(1.0 - Random()));
}


double Uniform(double a, double b){//ritorna numero tra a e b in modo uniforme
    if(a>b){
        handle_error_with_exit("error in uniform\n");
    }
    return (a + (b - a) * Random());
}

double Hyperexponential(double m){
    if(m <= 0)
        handle_error_with_exit( "error in hyperexponential\n");
    double p = 0.5;
    double P = Random();
    if( P <= p )
        return Exponential(2*p*m);
    else
        return Exponential(2*(1-p)*m);
}
