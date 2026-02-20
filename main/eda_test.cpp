#include "../include/pfs.hpp"
#include "../include/edd.hpp"
#include "../include/eda.hpp"
#include "../include/morais.hpp"
#include "../include/utils.hpp"

#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <cmath>

#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]){
    pgs_eda a(10);
    a.cargar_instancia(0);
    double selec=0.1, eps=0.4, iters=10;
    int verbose=2;

    a.generar_poblacion_aleatoria();

    vector<double> promedios, desvest, diff_prom, diff_desvest;
    vector<int> mejores;

    int mejor;

    vector<int> res=a.EDA(selec, 
                          eps, 
                          iters, 
                          verbose, 
                          promedios,
                          desvest,
                          diff_prom,
                          diff_desvest,
                          mejores,
                          //CAMBIAR ESTO!!!!!!
                          nullptr);

    printf("PROMEDIOS:\n");
    for(int i=0;i<promedios.size();i++){
        printf("%lf ", promedios[i]);
    }
    printf("\nDESVEST:\n");
    for(int i=0;i<desvest.size();i++){
        printf("%lf ", desvest[i]);
    }
    printf("\nMEJORES:\n");
    for(int i=0;i<mejores.size();i++){
        printf("%d ", mejores[i]);
    }
    printf("\nDIFERENCIAS PROMEDIOS:\n");
    for(int i=0;i<diff_prom.size();i++){
        printf("%lf ", diff_prom[i]);
    }
    printf("\nDIFERENCIAS DESVIACIÓN ESTANDAR:\n");
    for(int i=0;i<diff_desvest.size();i++){
        printf("%lf ", diff_desvest[i]);
    }
    
    return 0;
}


