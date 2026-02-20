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

    vector<int> mejores_conocidos{1278, 1359, 1081, 1293, 1235, 1195, 1234, 1206, 1230, 1108, 
                                1582, 1659, 1496, 1377, 1419, 1397, 1484, 1538, 1593, 1591, 
                                2297, 2099, 2326, 2223, 2291, 2226, 2273, 2200, 2237, 2178, 
                                2724, 2834, 2621, 2751, 2863, 2829, 2725, 2683, 2552, 2782, 
                                2991, 2867, 2839, 3063, 2976, 3006, 3093, 3037, 2897, 3065, 
                                3771, 3699, 3640, 3635, 3553, 3679, 3704, 3691, 3645, 3696, 
                                5493, 5268, 5175, 5014, 5250, 5135, 5246, 5094, 5448, 5322, 
                                5770, 5349, 5676, 5781, 5467, 5303, 5595, 5617, 5871, 5845, 
                                6134, 6183, 6252, 6254, 6270, 6311, 6216, 6316, 6232, 6404, 
                                10862, 10480, 10922, 10889, 10524, 10329, 10854, 10730, 10438, 10675, 
                                11158, 11153, 11281, 11275, 11259, 11176, 11337, 11301, 11146, 11284, 
                                26040, 26500, 26371, 26456, 26334, 26469, 26389, 26560, 26005, 26457};

    
    int inst=10;
    int n_inds=10;
    double porcentaje_NEH=0.75;
    int n_iters=10;
    double mu=0.7;
    double c_r=0.1;
    string cruza="SHADE";
    int verbose=2;
    double p=0.8;
    int d=18;
    int reemps=2;

    pfs_edd a(n_inds);
    
    a.cargar_instancia(inst);
    
    
    vector<vector<int> > inds_NEH=a.NEH((int)floor(porcentaje_NEH*a.n_jobs));
    
    int resta=n_inds-inds_NEH.size();

    if(resta<0){
        for(int j=0;j<n_inds;j++){
            a.poblacion.push_back(inds_NEH[j]);
        }
    }
    else{
        for(int j=0;j<inds_NEH.size();j++){
            a.poblacion.push_back(inds_NEH[j]);
        }

        for(int j=0;j<resta;j++){
            a.poblacion.push_back(a.permutacion_aleatoria());
            a.poblacion[a.poblacion.size()-1].push_back(a.makespan(a.poblacion[a.poblacion.size()-1]));
        }
    }


    a.generar_poblacion_aleatoria();

    vector<double> promedios, desvest, diff_prom, diff_desvest;
    vector<int> mejores;

    int mejor;

    int mej__=a.evolucion_diferencial_discreta(n_iters,
                                               mu,
                                               c_r,
                                               cruza,
                                               verbose,
                                               p,
                                               d,
                                               reemps, 
                                               promedios,
                                               desvest,
                                               diff_prom, 
                                               diff_desvest,
                                               mejores,
                                               mejor,
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




