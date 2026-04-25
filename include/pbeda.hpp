#include <iostream>

#include "../include/pfs.hpp"
#include "../include/utils.hpp"

using namespace std;

#ifndef EDA_HPP
#define EDA_HPP

#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <unordered_map>

#include <typeinfo>

void experimento_PGS_EDA(string name, string carpeta, int verbose, bool archivo, bool verbose_);

class pb_eda: public pfs{
public:
    //constructor
    pb_eda(int n_inds=100, int n_jobs=20, int n_machines=20): pfs(n_inds, n_jobs, n_machines){}
    //destructor
    ~pb_eda(){}

    
};

#endif