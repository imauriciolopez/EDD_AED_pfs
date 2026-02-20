#include "../include/eda.hpp"
#include "../include/pfs.hpp"
#include "../include/utils.hpp"


#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <omp.h>

void experimento_PGS_EDA(string name, string carpeta, int verbose, bool archivo, bool verbose_){
    /*
    FILE *file_stream=fopen(name.c_str(), "r");
    int n_exps, n_threads;
    fscanf(file_stream, "Cantidad de experimentos: %d\n", &n_exps);
    fscanf(file_stream, "Cantidad de threads: %d\n", &n_threads);
    fscanf(file_stream, "TIPO INSTANCIA NUMERO_INDIVIDUOS NUMERO_ITERACIONES TIPO_CRUZA MU  C_R P   D  REEMPLAZOS NEH EXTRA\n");
    vector<char> tipos;
    vector<int> instancias;
    vector<int> n_indss;
    vector<int> n_iterss;
    vector<string> cruzas;
    vector<double> mus;
    vector<double> c_rs;
    vector<double>  ps;
    vector<int> ds;
    vector<int> reemps;
    vector<double>  NEHs;
    vector<string>  extras;
    for(int i=0;i<n_exps;i++){
        char tipo;
        int instancia;
        int n_inds;
        int n_iters;
        char cruza_[1000];
        string cruza;
        double mu;
        double c_r;
        double p;
        int d;
        int remp;
        double NEH;
        char extra[1000];
        string extra_;
        fscanf(file_stream, "%c %d %d %d %s %lf %lf %lf %d %d %lf %s\n", &tipo, &instancia, &n_inds, &n_iters, cruza_, &mu, &c_r, &p, &d, &remp, &NEH, extra);
        
        if(verbose_){
            cout<<"LECTURA: "<<tipo<<", "<<instancia<<", "<<n_inds<<", "<<n_iters<<", "<<cruza_<<", "<<mu<<", "<<c_r<<", "<<p<<", "<<d<<", "<<NEH<<", "<<extra<<endl;
        }
        
        extra_=extra;
        cruza=cruza_;
        tipos.push_back(tipo);
        instancias.push_back(instancia);
        n_indss.push_back(n_inds);
        n_iterss.push_back(n_iters);
        cruzas.push_back(cruza);
        mus.push_back(mu);
        c_rs.push_back(c_r);
        ps.push_back(p);
        ds.push_back(d);
        reemps.push_back(remp);
        NEHs.push_back(NEH);
        extras.push_back(extra);
    }

    fclose(file_stream);
    
    //-------------------------------------------------------------------------------------------------------------------------------------------
    vector<double> tiempos(n_exps);
    
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

                                  
    vector<int> performance(n_exps);
    vector<int> makespan(n_exps);

    
    omp_set_num_threads(n_threads);
    #pragma omp parallel for schedule(dynamic)
    for(int i=0;i<n_exps;i++){

        pfs_edd a(n_indss[i]);

        a.cargar_instancia(instancias[i]);
        
        
        vector<vector<int> > inds_NEH=a.NEH((int)floor(NEHs[i]*a.n_jobs));
        
        int resta=n_indss[i]-inds_NEH.size();

        if(resta<0){
            for(int j=0;j<n_indss[i];j++){
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

        //cout<<"SIZE->"<<a.poblacion.size()<<endl;

        a.generar_poblacion_aleatoria();

        vector<double> promedios, desvest, diff_prom, diff_desvest;
        vector<int> mejores;

        int mejor;

        unsigned t0=clock();

        string archivo_=carpeta;
        string archivo=archivo_+"/exp_"+to_string(i)+".txt";
        
        FILE *file=fopen(archivo.c_str(), "w");

        int mej__=a.evolucion_diferencial_discreta(n_iterss[i],
                                                   mus[i],
                                                   c_rs[i],
                                                   cruzas[i],
                                                   verbose,
                                                   ps[i],
                                                   ds[i],
                                                   reemps[i], 
                                                   promedios,
                                                   desvest,
                                                   diff_prom, 
                                                   diff_desvest,
                                                   mejores,
                                                   mejor,
                                                   //CAMBIAR ESTO!!!!!!
                                                   file);

        tiempos[i]=(double(clock()-t0)/CLOCKS_PER_SEC);
        
        performance[i]=mej__-mejores_conocidos[instancias[i]];
        makespan[i]=mej__;
        
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
    }
    string archivo__=carpeta;

    string archivo_resumen=archivo__+"/resumen.txt";

    FILE *resumen=fopen(archivo_resumen.c_str(), "w");

    for(int i=0;i<n_exps;i++){
        fprintf(resumen, "EXP: %d\n", i);
        fprintf(resumen, "T TOTAL: %lf\n", tiempos[i]);
        fprintf(resumen, "T POR ITERACION: %lf\n", tiempos[i]/n_iterss[i]);
        fprintf(resumen, "DESEMPEÑO REAL: %d\n", makespan[i]);
        fprintf(resumen, "DESEMPEÑO RELATIVO: %d\n\n", performance[i]);
    }

    fclose(resumen);*/
}

