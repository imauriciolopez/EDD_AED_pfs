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

class pgs_eda: public pfs{
public:
    //constructor
    pgs_eda(int n_inds=100, int n_jobs=20, int n_machines=20): pfs(n_inds, n_jobs, n_machines){}
    //destructor
    ~pgs_eda(){}

    //funciones
    template <typename T> vector<vector<T> > M(double selection_size, T epsilon){
        //ordenamos todos los individuos por makespan (el makespan de cada individuo está al mero final del infividuo)
        poblacion=b_u_merge_sort<int>(poblacion, poblacion[0].size()-1);
    
        //armamos la matriz P(k)
        //P(k) solo tiene los n mejores individuos
        vector<vector<int> > p_k;
        vector<int> temp;
        for(int i=0;i<int(selection_size*n_inds);i++){
            for(int j=0;j<poblacion[i].size()-1;j++){
                temp.push_back(poblacion[i][j]);
            }
            p_k.push_back(temp);
            temp.resize(0);
        }

        //armamos la matriz M(k)
        vector<vector<T> > m_k(n_jobs, vector<T>(n_jobs, epsilon));

        return m_k;
    }

    template <typename T> vector<int> vector_de_secuencia(vector<vector<T> > M){
        //transponemos la matriz para manejar las columnas mas facil
        vector<vector<T> > M_T(n_jobs, vector<T>(n_jobs, 0));
        
        for(int i=0;i<n_jobs;i++) for(int j=0;j<n_jobs;j++) M_T[j][i]=M[i][j];

        
        //sacamos los mayores por columna
        vector<T> mayores_por_columna(n_jobs);
        for(int i=0;i<M_T.size();i++) mayores_por_columna[i]=maximo<T>(M_T[i]);

        
        //ya tenemos el orden de las columnas
        vector<int> posiciones_maximas=b_u_merge_sort<T>(mayores_por_columna, true, true);

        vector<int> sv;
        //aquí tenemos que ir colocando en sv la secuencia, que 
        //va a empezar con la posición en la columna de M que tenga el valor mas alto de repetición, 
        //pero si hay empates, colocamos el trabajo con indice mas grande
        //lo bueno es que Bottom Up Merge Sort es un algoritmo estable
        //entonces solo tenemos que recorrer posiciones_maximas, y poner las posiciones 
        //en las que se encuentran dentro de las columnas cada uno de los elementos de posiciones_maximas
        
        int temp;

        for(int i=0;i<posiciones_maximas.size();i++){
            temp=where(M_T[posiciones_maximas[i]], mayores_por_columna[posiciones_maximas[i]]);

            
            if(temp==-1){
                cout<<"ERROR: NO SE ENCUENTRA EL VALOR DENTRO DEL VECTOR "<<mayores_por_columna[posiciones_maximas[i]]<<endl;
                return {};
            }
            if(!contiene(sv, temp)) sv.push_back(temp);
        }

        
        vector<int> faltan=this->faltantes(sv);
        for(int i=0;i<faltan.size();i++) sv.push_back(faltan[i]);
        
        return sv;
    }

    vector<vector<int> > muestreo(vector<vector<double> > M, vector<int> sv, int n, bool verbose=false){
        double sum=0.0;
        vector<vector<double> > M_c=M;
        vector<double> pv(n_jobs, 0);
        int elegido;
        vector<int> offspring(n_jobs, 0);
        vector<vector<int> > candidatos;

        for(int cand=0;cand<n;cand++){
            for(int i=0;i<sv.size();i++){
                //sabemos que M es cuadrada, entonces no importa qué size de M tomemos
                for(int j=0;j<M.size();j++){
                    sum+=M_c[sv[i]][j];
                }
                if(verbose){
                    for(auto ind:M_c){
                        for(auto x:ind){
                            cout<<x<<", ";
                        }
                        cout<<endl;
                    }
                    cout<<"sum "<<sum<<endl;
                }


                for(int j=0;j<M_c.size();j++){
                    pv[j]=M_c[sv[i]][j];
                }
                
                for(int j=0;j<pv.size();j++){
                    pv[j]/=sum;
                }
                sum=0.0;
                
                if(verbose) for(auto x:pv) cout<<x<<endl;

                //se elige por ruleta un número dadas las probabilidades de pv
                double r=rand_dbl(rndm);
                double acumulado=0.0;
                for(int j=0;j<(int)pv.size();j++){
                    acumulado+=pv[j];
                    if(r<=acumulado){
                        elegido=j;
                        break;
                    }
                }

                if(verbose) cout<<"ELEGIDO: "<<elegido<<" -> "<<r<<endl;

                //armamos el offspring
                offspring[elegido]=sv[i];

                //eliminamos la probabilidad del elemento elegido de M
                for(int j=0;j<M_c.size();j++){
                    M_c[j][elegido]=0.0;
                    //M_c[elegido][j]=0.0;
                }
                if(verbose) cout<<"-----------------------"<<endl;
            }
            if(this->valido(offspring)){
                candidatos.push_back(offspring);
            }
            else{
                if(verbose){
                    cout<<"NO VALIDO"<<endl;
                    for(int i=0;i<offspring.size();i++){
                        cout<<offspring[i]<<", ";
                    }
                    cout<<endl;
                }
            }
            offspring=vector<int>(n_jobs, 0);
            M_c=M;
        }
        
        for(int i=0;i<candidatos.size();i++){
            candidatos[i].push_back(this->makespan(candidatos[i], false));
        }
        //candidatos=b_u_merge_sort<int>(candidatos, candidatos[0].size());
        return candidatos;
    }

    vector<int> EDA(double selection_size, 
                    double epsilon, 
                    int n_iters, 
                    int verbose, 
                    vector<double>& promedios,
                    vector<double>& desvest,
                    vector<double>& diff_prom,
                    vector<double>& diff_desvest,
                    vector<int>& mejores,
                    FILE *file){

        if(file==nullptr) cout<<"ITERACION MEJOR PROMEDIO_MAKESPAN DESVEST_MAKESPAN PROMEDIO_DIFF DESVEST_DIFF\n";
        else fprintf(file, "ITERACION MEJOR PROMEDIO_MAKESPAN DESVEST_MAKESPAN PROMEDIO_DIFF DESVEST_DIFF\n");

        if(poblacion.empty()) return {};

        poblacion=b_u_merge_sort<int>(poblacion, poblacion[0].size()-1);

        int mejor=poblacion[0][poblacion[0].size()-1];



        promedios.clear();
        desvest.clear();
        mejores.clear();
        diff_prom.clear();
        diff_desvest.clear();

        int iter=0;
        vector<int> res;
        for(int iter=0;iter<n_iters;iter++){
            vector<vector<double> > M=this->M<double>(0.1, 0.4);
            vector<int> sv=this->vector_de_secuencia<double>(M);
            vector<vector<int> > candidatos=this->muestreo(M, sv, 10);
            
            for(int i=0;i<candidatos.size();i++){
                if(candidatos[i][candidatos[i].size()-1]<poblacion[poblacion.size()-1][poblacion[0].size()-1]){
                    
                    poblacion[poblacion.size()-1]=candidatos[i];
                    poblacion=b_u_merge_sort<int>(poblacion, poblacion[0].size()-1);
                }
            }
            poblacion=b_u_merge_sort<int>(poblacion, poblacion[0].size()-1);
            mejor=poblacion[0][poblacion[0].size()-1];
            res.push_back(poblacion[0][poblacion[0].size()-1]);


            // cálculo de promedio y std de los makespan
            vector<int> diff=this->calcular_diferencias();

            vector<int> makespans(n_inds);
            for(int i=0;i<n_inds;i++) makespans[i]=poblacion[i][n_jobs];

            vector<double> mean_desvest_diffs=mean_desv_est<int>(diff);
            vector<double> mean_desvest_mkspn=mean_desv_est<int>(makespans);

            promedios.push_back(mean_desvest_mkspn[0]);
            desvest.push_back(mean_desvest_mkspn[1]);
            diff_prom.push_back(mean_desvest_diffs[0]);
            diff_desvest.push_back(mean_desvest_diffs[1]);
            mejores.push_back(poblacion[0][n_jobs]);


            if(verbose>0&&(iter%verbose==0)){
                if(file==nullptr){
                    cout<<iter
                        <<" "<<mejor
                        <<" "<<mean_desvest_mkspn[0]
                        <<" "<<mean_desvest_mkspn[1]
                        <<" "<<mean_desvest_diffs[0]
                        <<" "<<mean_desvest_diffs[1]
                        <<"\n";
                }
                else{
                    fprintf(file, "%d %d %lf %lf %lf %lf\n", iter, mejor, mean_desvest_mkspn[0], mean_desvest_mkspn[1], mean_desvest_diffs[0], mean_desvest_diffs[1]);
                }
            }
        
        }
        return res;
    }
};

#endif