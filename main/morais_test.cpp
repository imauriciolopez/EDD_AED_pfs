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
    pfs_morais a(10);
    a.cargar_instancia(0);
    a.generar_poblacion_aleatoria_cont();

    a.ver();

    vector<double> promedios, desvest, diff_prom, diff_desvest;
    vector<int> mejores;

    int n_iters=10;
    int verbose=2;
    double p=0.8;
    int LP=50;

    
    int mejor=a.DSADE_PFS_1(n_iters,
                            "SHADE",
                            verbose,
                            p,
                            promedios,
                            desvest,
                            diff_prom,
                            diff_desvest,
                            mejores,
                            //CAMBIAR ESTO!!!!!!
                            nullptr);

    a.ver();
    
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

    a.liberar_poblacion();





    pfs_morais b(10);
    b.cargar_instancia(0);
    b.generar_poblacion_aleatoria_cont();

    b.ver();
    
    mejor=b.DSADE_PFS_2(n_iters,
                        verbose,
                        p,
                        LP, 
                        promedios,
                        desvest,
                        diff_prom,
                        diff_desvest,
                        mejores,
                        //CAMBIAR ESTO!!!!!!
                        nullptr);

    b.ver();
    
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

    b.liberar_poblacion();
}


