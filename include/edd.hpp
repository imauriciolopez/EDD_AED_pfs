#include <iostream>

#include "../include/pfs.hpp"
#include "../include/utils.hpp"

using namespace std;

#ifndef EDD_HPP
#define EDD_HPP

#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <unordered_map>

#include <typeinfo>

void experimento(string name, string carpeta, int verbose, bool archivo=true, bool verbose_=false);

class pfs_edd: public pfs{
public:
    //constructor
    pfs_edd(int n_inds=100, int n_jobs=20, int n_machines=20): pfs(n_inds, n_jobs, n_machines){}
    //destructor
    ~pfs_edd(){}


    template <typename T> vector<vector<T> > M(vector<vector<int> > poblacion, double selection_size, T epsilon){
        //ordenamos todos los individuos por makespan (el makespan de cada individuo está al mero final del infividuo)
        poblacion=b_u_merge_sort<int>(poblacion, poblacion[0].size()-1);
    
        //armamos la matriz P(k)
        //P(k) solo tiene los n mejores individuos
        vector<vector<int> > p_k;
        vector<int> temp;
        for(int i=0;i<int(selection_size*poblacion.size());i++){
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

    vector<int> op_two_cut_PTL_crossover(int ind, vector<int> nuevo, bool verbose=false, int cant=2);

    vector<int> op_DE_rand_1_bin(int v_1, int v_2, int specimen, double mu);

    vector<int> op_DE_rand_to_p_best_1_bin(int specimen, double mu, double p);

    int evolucion_diferencial_discreta(int n_iters,
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
                                       FILE *file=nullptr);

    vector<int> DestructConstruct(int ind, int d);

    vector<int> DestructConstruct(vector<int> ind, int d, bool verbose=false);

    vector<int> RIS(vector<int> ind, vector<int> ref, bool verbose=false);

    vector<int> RLS(vector<int> ind, vector<int> ref, int d, int iter, int n_iters, bool verbose=false);
};

#endif