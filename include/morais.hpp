#include <iostream>

#include "../include/pfs.hpp"

using namespace std;

#ifndef MORAIS_HPP
#define MORAIS_HPP

#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <unordered_map>

#include <typeinfo>

class pfs_morais: public pfs{
public:
    pfs_morais(int n_inds=100, int n_jobs=20, int n_machines=20): pfs(n_inds, n_jobs, n_machines){}
    //destructor
    ~pfs_morais(){}

    vector<struct ind*> poblacion_struct;

    void generar_poblacion_aleatoria_cont();

    void makespan_cont(struct ind *ind_);

    void ver(int n=0);

    void liberar_poblacion();

    int DSADE_PFS_1(int n_iters,
                    const string& cruza,
                    int verbose,
                    double p,
                    vector<double>& promedios,
                    vector<double>& desvest,
                    vector<double>& diff_prom,
                    vector<double>& diff_desvest,
                    vector<int>& mejores,
                    FILE *file);

    int DSADE_PFS_2(int n_iters,
                    int verbose,
                    double p,
                    int LP, 
                    vector<double>& promedios,
                    vector<double>& desvest,
                    vector<double>& diff_prom,
                    vector<double>& diff_desvest,
                    vector<int>& mejores,
                    FILE *file);

    vector<vector<double> > get_params();
};

void experimento_DSADE_PFS_1(string name, string carpeta, int verbose, bool archivo, bool verbose_);

void experimento_DSADE_PFS_2(string name, string carpeta, int verbose, bool archivo, bool verbose_);


#endif