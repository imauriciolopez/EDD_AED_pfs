#include "../include/edd.hpp"
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

using namespace std;

vector<int> pfs_edd::op_two_cut_PTL_crossover(int ind, vector<int> nuevo, bool verbose, int cant){
    if (cant > n_jobs) {
        return nuevo;
    }

    uniform_int_distribution<int> dist_corte(0, n_jobs-2);
    int corte=dist_corte(rndm);

    if (corte+cant>n_jobs-1){
        corte = n_jobs - cant;
    }

    uniform_int_distribution<int> dist_lado(0, 1);
    int lado = dist_lado(rndm); // 0 = derecha, 1 = izquierda

    // secuencia d
    vector<int> d(cant);
    for (int i = 0; i < cant; ++i) {
        d[i]=poblacion[ind][corte + i];
    }

    if (verbose) {
        for (int i = 0; i < (int)d.size(); ++i) {
            cout << d[i] << ", ";
        }
        cout <<endl;
    }

    vector<int> res;
    res.reserve(n_jobs);

    if (lado == 0) {
        // queremos d al final (derecha)
        for (int i = 0; i < n_jobs; ++i) {
            // si nuevo[i] no está en d
            bool found = false;
            for (int j = 0; j < (int)d.size(); ++j) {
                if (nuevo[i] == d[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                res.push_back(nuevo[i]);
            }
        }
        // luego concatenamos d
        for (int i = 0; i < (int)d.size(); ++i) {
            res.push_back(d[i]);
        }
    } 
    else {
        // queremos d al inicio (izquierda)
        for (int i = 0; i < (int)d.size(); ++i) {
            res.push_back(d[i]);
        }
        for (int i = 0; i < n_jobs; ++i) {
            bool found = false;
            for (int j = 0; j < (int)d.size(); ++j) {
                if (nuevo[i] == d[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                res.push_back(nuevo[i]);
            }
        }
    }

    return res;
}

vector<int> pfs_edd::op_DE_rand_1_bin(int v_1, int v_2, int specimen, double mu){
    return this->op_suma(this->op_resta(v_1, v_2), specimen, mu);
}

vector<int> pfs_edd::op_DE_rand_to_p_best_1_bin(int specimen, double mu, double p){
    // asumimos que la población está ordenada por makespan ascendente:
    int n_best = (int)floor((double)n_inds * p);
    if (n_best < 1) {
        n_best = 1;
    }

    uniform_int_distribution<int> dist_best(0, n_best - 1);
    int best_idx = dist_best(rndm);

    vector<vector<int> > diff = this->op_resta(best_idx, specimen);
    vector<int> res  = this->op_suma(diff, specimen, mu);

    return res;
}

int pfs_edd::evolucion_diferencial_discreta(int n_iters,
                                            double mu,
                                            double c_r,
                                            const string& cruza,
                                            int verbose,
                                            double p,
                                            int d, 
                                            int n_iters_mejora, 
                                            vector<double>& promedios,
                                            vector<double>& desvest,
                                            vector<double>& diff_prom,
                                            vector<double>& diff_desvest,
                                            vector<int>& mejores,
                                            int& mejor, 
                                            FILE *file){

    if(file==nullptr){
        cout<<"EXP: "<<n_iters<<", "<<mu<<", "<<c_r<<", "<<cruza<<endl;
    }

    if(file==nullptr){
        cout<<"ITERACION MEJOR PROMEDIO_MAKESPAN DESVEST_MAKESPAN PROMEDIO_DIFF DESVEST_DIFF\n";
    }
    else{
        fprintf(file, "ITERACION MEJOR PROMEDIO_MAKESPAN DESVEST_MAKESPAN PROMEDIO_DIFF DESVEST_DIFF\n");
    }

    if(poblacion.empty()){
        return -1;
    }

    poblacion=b_u_merge_sort<int>(poblacion, n_jobs-1);

    mejor=poblacion[0][poblacion[0].size()-1];

    promedios.clear();
    desvest.clear();
    mejores.clear();
    diff_prom.clear();
    diff_desvest.clear();

    int n_mejoras=0, indice_mejora=0;
    
    for(int iter_=0;iter_<n_iters;iter_++){
        for(int specimen=0;specimen<n_inds;specimen++){

            vector<int> w_1;
            //cout<<"CRUZA"<<endl;
            if(cruza!="SHADE"){
                int v_1=rand_int(rndm)%(n_inds-1), v_2=rand_int(rndm)%(n_inds-1);
                while(v_2==v_1) v_2=rand_int(rndm)%(n_inds-1);
                
                w_1=op_DE_rand_1_bin(v_1, v_2, specimen, mu);
            }
            else{
                w_1=op_DE_rand_to_p_best_1_bin(specimen, mu, p);
            }
            //cout<<"CROSOVER"<<endl;
            vector<int> candidato=op_two_cut_PTL_crossover(specimen, w_1, false, max((int)floor((double)n_jobs * c_r), 1));
            
            //agregar makespan
            candidato.push_back(this->makespan(candidato));


            //Referenced Local Search
            //cout<<"RLS 1"<<endl;
            candidato=this->RLS(candidato, poblacion[0], d, iter_, n_iters);
            //cout<<"RLS 2"<<endl;
            vector<int> candidato_2=this->RLS(poblacion[specimen], poblacion[0], d, iter_, n_iters);
            
            if(candidato_2[n_jobs]<candidato[n_jobs]){
                candidato=candidato_2;
            }

            //selección
            if(candidato[n_jobs]<poblacion[specimen][n_jobs]){
                poblacion[specimen]=candidato;
                if(poblacion[specimen][n_jobs]<mejor){
                    indice_mejora=specimen;
                    mejor=poblacion[specimen][n_jobs];
                }
            }
        }
        //cout<<"ITER"<<endl;
        
        //ordenar por makespan (última posición)
        poblacion=b_u_merge_sort<int>(poblacion, n_jobs);

        if(iter_%n_iters_mejora==0&&iter_>0){
            //población que se regenera desde cero (peor 25%)
            int n_nuevos_inds=int(floor(n_inds*0.25));
            vector<vector<int> > nueva_pob=generar_poblacion_aleatoria(n_nuevos_inds);
            for(int i=0;i<n_nuevos_inds;i++) poblacion[n_inds-1-i]=nueva_pob[i];
            
            //población que se copia del mejor 5% (del 50% peor hasta el 25% peor)
            vector<vector<int> > pob_vieja;
            n_nuevos_inds=int(ceil(n_inds*0.05));
            int offset=int(ceil(n_inds*0.5));
            for(int i=0;i<n_nuevos_inds;i++) pob_vieja.push_back(poblacion[offset+i]);
            
            
            vector<vector<double> > M=this->M<double>(pob_vieja, 0.1, 0.4);
            vector<int> sv=this->vector_de_secuencia<double>(M);
            vector<vector<int> > candidatos=this->muestreo(M, sv, n_nuevos_inds);
            for(int i=0;i<n_nuevos_inds;i++) poblacion[offset+i]=candidatos[i];
        }
    
        poblacion=b_u_merge_sort<int>(poblacion, n_jobs);

        //estadísticas
        // diferencias entre individuos consecutivos
        vector<int> diff=this->calcular_diferencias();
        
        // cálculo de promedio y std de los makespan
        vector<int> makespans(n_inds);
        for(int i=0;i<n_inds;i++) makespans[i]=poblacion[i][n_jobs];

        vector<double> mean_desvest_diffs=mean_desv_est<int>(diff);
        vector<double> mean_desvest_mkspn=mean_desv_est<int>(makespans);

        promedios.push_back(mean_desvest_mkspn[0]);
        desvest.push_back(mean_desvest_mkspn[1]);
        diff_prom.push_back(mean_desvest_diffs[0]);
        diff_desvest.push_back(mean_desvest_diffs[1]);
        mejores.push_back(poblacion[0][n_jobs]);


        if(verbose>0&&(iter_%verbose==0)){
            if(file==nullptr){
                cout<<iter_
                    <<" "<<mejor
                    <<" "<<mean_desvest_mkspn[0]
                    <<" "<<mean_desvest_mkspn[1]
                    <<" "<<mean_desvest_diffs[0]
                    <<" "<<mean_desvest_diffs[1]
                    <<"\n";
            }
            else{
                fprintf(file, "%d %d %lf %lf %lf %lf\n", iter_, mejor, mean_desvest_mkspn[0], mean_desvest_mkspn[1], mean_desvest_diffs[0], mean_desvest_diffs[1]);
            }
        }
    }
    
    this->ver_poblacion(file);
    
    return mejor;
}

vector<int> pfs_edd::DestructConstruct(int ind, int d){
    return this->DestructConstruct(poblacion[ind], d);
}

vector<int> pfs_edd::DestructConstruct(vector<int> ind, int d, bool verbose){
    //eliminamos d elementos
    vector<int> d_pos_=this->permutacion_aleatoria();
    vector<int> d_pos(d), ind_(n_jobs), d_elems(d);

    //hacemos una copia de ind
    copy(ind.begin(), ind.end()-1, ind_.begin());
    //copiamos los primeros d elementos de una permutación aleatoria
    copy(d_pos_.begin(), d_pos_.begin()+d, d_pos.begin());

    //los ordenamos
    d_pos=b_u_merge_sort<int>(d_pos);
    
    int count=0;
    for(auto a:d_pos){
        d_elems[count]=ind_[a-count];
        ind_.erase(ind_.begin()+a-count++);
    }

    //insertamos los d elementos de manera greedy
    int mk, i, j, mejor_makespan=1000000, mejor_pos=0, n;
    vector<int> mejor_secuencia(n_jobs);
    
    //reinsertamos de manera greedy los elementos eliminados
    for(i=0;i<d;i++){
        n=ind_.size();

        vector<vector<int> > c_prev=this->makespan_incremental(ind_);

        for(j=0;j<n+1;j++){
            mk=this->makespan_incremental(ind_, d_elems[i], j, c_prev);

            if(mk<mejor_makespan){
                mejor_pos=j;
                mejor_makespan=mk;
            }
        }
        
        vector<int> ind_c(n+1);
   
        for(j=0;j<mejor_pos;j++){
            ind_c[j]=ind_[j];
        }
        
        ind_c[mejor_pos]=d_elems[i];
        for(j=mejor_pos;j<n;j++){
            ind_c[j+1]=ind_[j];
        }

        ind_=ind_c;

        mejor_makespan=1000000;
    }
    
    //cout<<endl;
    ind_.push_back(makespan(ind_));

    return ind_;
}

vector<int> pfs_edd::RIS(vector<int> ind, vector<int> ref, bool verbose){
    //gurdamos el makespan actual
    int mkspn_actual=ind[n_jobs];
    ind.pop_back();

    int no_mejoras=0, pos=0;
    vector<int> ind_pi_1(n_jobs);
    copy(ind.begin(), ind.end(), ind_pi_1.begin());

    int pos_ref=0, i, mejor_makespan=1000000, mk;
    
    while(no_mejoras<n_jobs||no_mejoras<50){
        //eliminar el elemento h-ésimo de ref en ind y precalcular el makespan
        for(i=0;i<n_jobs;i++) 
            if(ind[i]==ref[(pos)%n_jobs]){
                pos_ref=i;
                break;
            }
            
        ind.erase(ind.begin()+pos_ref);

        vector<int> mejor_sec(n_jobs);
        vector<vector<int> > c_prev=this->makespan_incremental(ind);

        //determinar la mejor posición para el trabajo eliminado
        int mejor_pos=0;
        for(i=0;i<ind.size()+1;i++){
            //CHECAR ESTO TAMBIEN
            mk=this->makespan_incremental(ind, ref[(pos)%n_jobs], i, c_prev);

            if(mk<mejor_makespan){
                mejor_pos=i;
                mejor_makespan=mk;
            }
        }

        //agregar el trabajo eliminado
        vector<int> ind_c(n_jobs);

        for(i=0;i<mejor_pos;i++) ind_c[i]=ind[i];
        ind_c[mejor_pos]=ref[(pos++)%n_jobs];
        for(i=mejor_pos;i<n_jobs-1;i++) ind_c[i+1]=ind[i];


        
        if(mejor_makespan<mkspn_actual){

            ind=ind_c;
            mkspn_actual=mejor_makespan;
            no_mejoras=0;
        }
        else{

            ind=ind_pi_1;
            no_mejoras++;
        }

        ind_pi_1=ind_c;

        mejor_makespan=1000000;
    }

    ind.push_back(makespan(ind));

    return ind;
}

vector<int> pfs_edd::RLS(vector<int> ind, vector<int> ref, int d, int iter, int n_iters, bool verbose){
    if(n_jobs<101){
        vector<int> pi=this->DestructConstruct(ind, d);
        vector<int> pi_1=this->RIS(pi, ref);
        

        if(verbose){
            cout<<"PI   - ";
            if(!this->valido(pi)) cout<<" MAL ";
            for(auto a:pi) cout<<a<<", ";
            cout<<endl;
            cout<<"PI_1 - ";
            if(!this->valido(pi_1)) cout<<" MAL ";
            for(auto a:pi_1) cout<<a<<", ";
            cout<<"\n"<<endl;
        }

        //if(pi_1[n_jobs]<pi[n_jobs]||rand_dbl(rndm)<this->temperatura(iter, 4.0/n_iters)){


        if(pi_1[n_jobs]<pi[n_jobs]){
            return pi_1;
        }
        else{
            return pi;
        }
    }
    else return this->DestructConstruct(ind, d);
}

void experimento(string name, string carpeta, int verbose, bool archivo, bool verbose_){
    FILE *file_stream=fopen(name.c_str(), "r");
    
    int n_exps, n_threads;
    
    fscanf(file_stream, "Cantidad de experimentos: %d\n", &n_exps);
    
    fscanf(file_stream, "Cantidad de threads: %d\n", &n_threads);
    fscanf(file_stream, "TIPO INSTANCIA NUMERO_INDIVIDUOS NUMERO_ITERACIONES TIPO_CRUZA MU  C_R P   D  REEMPLAZOS NEH  EXTRA\n");
    
    vector<char>   tipos;
    vector<int>    instancias;
    vector<int>    n_indss;
    vector<int>    n_iterss;
    vector<string> cruzas;
    vector<double> mus;
    vector<double> c_rs;
    vector<double> ps;
    vector<int>    ds;
    vector<int>    reemps;
    vector<double> NEHs;
    vector<string> extras;
    
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

    fclose(resumen);
}
