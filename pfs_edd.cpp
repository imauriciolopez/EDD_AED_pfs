#include "funciones.hpp"

#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <cmath>

#include <stdlib.h>
#include <time.h>

using namespace std;

/*
int main(int argc, char *argv[]){
    experimento(argv[1], argv[2], 2, true, true);
    printf("\a");
    return 0;
}*/

/*
int main(int argc, char *argv[]){
    //experimento(argv[1], argv[2], 2, true, false);
    FILE *file=fopen("/Users/imauriciolopez/Downloads/Taillard_UB_Schedules OBrunner v6.csv", "r");

    char c;
    for(int i=0;i<46;i++) c=fgetc(file);

    vector<int> temp(5);
    vector<int> mejores(120);
    vector<int> n_jobs(120);

    for(int i=0;i<120;i++){
        fscanf(file, "Ta%d,%d,%d,%d,%d,%d,%d, ", &temp[0], &n_jobs[i], &temp[1], &mejores[i], &temp[2], &temp[3], &temp[4]);
        vector<int> mejores_inds(n_jobs[i]);
        for(int j=0;j<n_jobs[i];j++){
            fscanf(file, "%d ", &mejores_inds[j]);
        }
    }

    for(int i=0;i<120;i++){
        cout<<mejores[i]<<", ";
    }
}
*/


int main(int argc, char *argv[]){
    //experimento(argv[1], argv[2], 2, true, false);
    //printf("\a");
    
    
    pfs_morais a(75);
    pfs_morais b(75);
    pfs_edd    c(75);
    pgs_eda    d(75);

    a.cargar_instancia(45);
    b.cargar_instancia(45);
    c.cargar_instancia(45);
    d.cargar_instancia(45);

    
    a.generar_poblacion_aleatoria_cont();
    b.generar_poblacion_aleatoria_cont();

    a.poblacion=vector<vector<int> >(75);
    for(int i=0;i<75;i++){
        a.makespan_cont(a.poblacion_struct[i]);
        a.poblacion[i]=a.poblacion_struct[i]->jobs;
        a.poblacion[i].push_back(a.poblacion_struct[i]->makespan);
    }
    
    
    for(int i=0;i<75;i++){
        b.poblacion_struct[i]=new struct ind(a.poblacion_struct[i]->posiciones, a.poblacion_struct[i]->jobs, a.poblacion_struct[i]->makespan, a.poblacion_struct[i]->f, a.poblacion_struct[i]->c_r);

        //representación clásica de individuo de pfs
        b.poblacion_struct[i]->n_jobs=a.poblacion_struct[i]->n_jobs;
    }

    c.poblacion=a.poblacion;
    d.poblacion=a.poblacion;

    //en este punto, los 4 tienen la misma población





    
    vector<double> promedios, desvest, diff_prom, diff_desvest;
    vector<int> mejores;
    
    a.ver();

    FILE *file=fopen("/Users/imauriciolopez/Library/CloudStorage/GoogleDrive-mauricio.lopez@cimat.mx/Mi unidad/TESIS/DSADE_pfs_2/DSADE_pfs_2.txt", "w");
    cout<<"\n-------------------DSADE_PFS_2-----------------------\n\n\n\n";
    int mejor=a.DSADE_PFS_2(500,
                            2,
                            0.8,
                            50, 
                            promedios,
                            desvest,
                            diff_prom,
                            diff_desvest,
                            mejores,
                            file);
    a.ver();
    a.ver_poblacion(file);
    fprintf(file, "PROMEDIOS:\n");
    for(int i=0;i<promedios.size();i++){
        fprintf(file, "%lf ", promedios[i]);
    }
    fprintf(file, "\nDESVEST:\n");
    for(int i=0;i<desvest.size();i++){
        fprintf(file, "%lf ", desvest[i]);
    }
    fprintf(file, "\nMEJORES:\n");
    for(int i=0;i<mejores.size();i++){
        fprintf(file, "%d ", mejores[i]);
    }
    fprintf(file, "\nDIFERENCIAS PROMEDIOS:\n");
    for(int i=0;i<diff_prom.size();i++){
        fprintf(file, "%lf ", diff_prom[i]);
    }
    fprintf(file, "\nDIFERENCIAS DESVIACIÓN ESTANDAR:\n");
    for(int i=0;i<diff_desvest.size();i++){
        fprintf(file, "%lf ", diff_desvest[i]);
    }
    fclose(file);
    a.liberar_poblacion();








    
    vector<double> promedios_2, desvest_2, diff_prom_2, diff_desvest_2;
    vector<int> mejores_2;
    
    b.ver();

    FILE *file_2=fopen("/Users/imauriciolopez/Library/CloudStorage/GoogleDrive-mauricio.lopez@cimat.mx/Mi unidad/TESIS/DSADE_pfs_1/DSADE_pfs_1.txt", "w");
    cout<<"\n------------------DSADE_PFS_1------------------------\n\n\n\n";
    mejor=b.DSADE_PFS_1(500,
                        "SHADE",
                        2,
                        0.8,
                        promedios_2,
                        desvest_2,
                        diff_prom_2,
                        diff_desvest_2,
                        mejores_2,
                        file_2);
    
    b.ver();
    b.ver_poblacion(file_2);
    fprintf(file_2, "PROMEDIOS:\n");
    for(int i=0;i<promedios_2.size();i++){
        fprintf(file_2, "%lf ", promedios_2[i]);
    }
    fprintf(file_2, "\nDESVEST:\n");
    for(int i=0;i<desvest_2.size();i++){
        fprintf(file_2, "%lf ", desvest_2[i]);
    }
    fprintf(file_2, "\nMEJORES:\n");
    for(int i=0;i<mejores_2.size();i++){
        fprintf(file_2, "%d ", mejores_2[i]);
    }
    fprintf(file_2, "\nDIFERENCIAS PROMEDIOS:\n");
    for(int i=0;i<diff_prom_2.size();i++){
        fprintf(file_2, "%lf ", diff_prom_2[i]);
    }
    fprintf(file_2, "\nDIFERENCIAS DESVIACIÓN ESTANDAR:\n");
    for(int i=0;i<diff_desvest_2.size();i++){
        fprintf(file_2, "%lf ", diff_desvest_2[i]);
    }
    fclose(file_2);
    b.liberar_poblacion();






    
    vector<double> promedios_3, desvest_3, diff_prom_3, diff_desvest_3;
    vector<int> mejores_3;
    FILE *file_3=fopen("/Users/imauriciolopez/Library/CloudStorage/GoogleDrive-mauricio.lopez@cimat.mx/Mi unidad/TESIS/PGS_EDA/PGS_EDA.txt", "w");
    
    cout<<"\n------------------EDA-----------------------\n\n\n\n";
    double selec=0.1, eps=0.4, iters=1000;

    vector<int>mejor_alaberga=d.EDA(selec,
                            eps,
                            500,
                            2,
                            promedios_3,
                            desvest_3,
                            diff_prom_3,
                            diff_desvest_3,
                            mejores_3,
                            file_3);

    d.ver_poblacion(file_3);
    fprintf(file_3, "PROMEDIOS:\n");
    for(int i=0;i<promedios_3.size();i++){
        fprintf(file_3, "%lf ", promedios_3[i]);
    }
    fprintf(file_3, "\nDESVEST:\n");
    for(int i=0;i<desvest_3.size();i++){
        fprintf(file_3, "%lf ", desvest_3[i]);
    }
    fprintf(file_3, "\nMEJORES:\n");
    for(int i=0;i<mejores_3.size();i++){
        fprintf(file_3, "%d ", mejores_3[i]);
    }
    fprintf(file_3, "\nDIFERENCIAS PROMEDIOS:\n");
    for(int i=0;i<diff_prom_3.size();i++){
        fprintf(file_3, "%lf ", diff_prom_3[i]);
    }
    fprintf(file_3, "\nDIFERENCIAS DESVIACIÓN ESTANDAR:\n");
    for(int i=0;i<diff_desvest_3.size();i++){
        fprintf(file_3, "%lf ", diff_desvest_3[i]);
    }
    
    fclose(file_3);



    



    vector<double> promedios_4, desvest_4, diff_prom_4, diff_desvest_4;
    vector<int> mejores_4;
    FILE *file_4=fopen("/Users/imauriciolopez/Library/CloudStorage/GoogleDrive-mauricio.lopez@cimat.mx/Mi unidad/TESIS/eed_python/kkck700aadasdasd.txt", "w");
    int finfinf;
    cout<<"\n------------------evolucion_diferencial_discreta-----------------------\n\n\n\n";
    int inininin=c.evolucion_diferencial_discreta(500,
                                                   0.7,
                                                   0.1,
                                                   "SHADE",
                                                   2,
                                                   0.8,
                                                   18,
                                                   20, 
                                                   promedios_4,
                                                   desvest_4,
                                                   diff_prom_4, 
                                                   diff_desvest_4,
                                                   mejores_4,
                                                   finfinf,
                                                   //CAMBIAR ESTO!!!!!!
                                                   file_4);
    
    
    d.ver_poblacion(file_4);
    fprintf(file_4, "PROMEDIOS:\n");
    for(int i=0;i<promedios_4.size();i++){
        fprintf(file_4, "%lf ", promedios_4[i]);
    }
    fprintf(file_4, "\nDESVEST:\n");
    for(int i=0;i<desvest_4.size();i++){
        fprintf(file_4, "%lf ", desvest_4[i]);
    }
    fprintf(file_4, "\nMEJORES:\n");
    for(int i=0;i<mejores_4.size();i++){
        fprintf(file_4, "%d ", mejores_4[i]);
    }
    fprintf(file_4, "\nDIFERENCIAS PROMEDIOS:\n");
    for(int i=0;i<diff_prom_4.size();i++){
        fprintf(file_4, "%lf ", diff_prom_4[i]);
    }
    fprintf(file_4, "\nDIFERENCIAS DESVIACIÓN ESTANDAR:\n");
    for(int i=0;i<diff_desvest_4.size();i++){
        fprintf(file_4, "%lf ", diff_desvest_4[i]);
    }
    
    fclose(file_4);

    return 0;

}

/*
int main(int argc, char *argv[]){
    pgs_eda a(150);

    vector<double> promedios, desvest, diff_prom, diff_desvest;
    vector<int> mejores;
    

    FILE *file=fopen("/Users/imauriciolopez/Library/CloudStorage/GoogleDrive-mauricio.lopez@cimat.mx/Mi unidad/TESIS/PGS_EDA/kkck7000_4.txt", "w");

    a.cargar_instancia(45);
    double selec=0.1, eps=0.4, iters=1000;
    cout<<"control:\n";

    a.generar_poblacion_aleatoria();
    vector<int>res=a.EDA(selec, eps, iters, 
                    2, 
                    promedios,
                    desvest,
                    diff_prom,
                    diff_desvest,
                    mejores,
                    file);

    a.ver_poblacion(file);

    fprintf(file, "PROMEDIOS:\n");
    for(int i=0;i<promedios.size();i++){
        fprintf(file, "%lf ", promedios[i]);
    }
    fprintf(file, "\nDESVEST:\n");
    for(int i=0;i<desvest.size();i++){
        fprintf(file, "%lf ", desvest[i]);
    }
    fprintf(file, "\nMEJORES:\n");
    for(int i=0;i<mejores.size();i++){
        fprintf(file, "%d ", mejores[i]);
    }
    fprintf(file, "\nDIFERENCIAS PROMEDIOS:\n");
    for(int i=0;i<diff_prom.size();i++){
        fprintf(file, "%lf ", diff_prom[i]);
    }
    fprintf(file, "\nDIFERENCIAS DESVIACIÓN ESTANDAR:\n");
    for(int i=0;i<diff_desvest.size();i++){
        fprintf(file, "%lf ", diff_desvest[i]);
    }
    
    fclose(file);
}*/



