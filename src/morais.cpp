#include "../include/morais.hpp"
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

struct ind{
    //representación clásica de individuo de pfs
    int n_jobs;
    vector<int> jobs;

    int makespan;

    //representación del paper MORAIS
    vector<double> posiciones;

    //factores de auto regulación
    double f;
    double c_r;

    //valores para DSEDA pfs2
    vector<double> c_r_{0.0, 0.0, 0.0, 0.0};

    ind(vector<double>posiciones_=vector<double>{}, vector<int>jobs_=vector<int>{}, int makespan_=0, double f_=0, double c_r_=0):n_jobs(posiciones_.size()){
        posiciones=posiciones_;
        jobs=jobs_;
        makespan=makespan_;
        f=f_;
        c_r=c_r_;
        n_jobs=posiciones_.size();
    }

    ind(int n_jobs_):n_jobs(n_jobs_){
        n_jobs=n_jobs_;
        posiciones=vector<double>(n_jobs, 0.0);
        jobs=vector<int>(n_jobs, 0);
        makespan=0;
        f=0.0;
        c_r=0.0;
    }
    
    ind operator+(const struct ind& a)const{
        struct ind c(*this);
        for(int i=0;i<n_jobs;i++){
            c.posiciones[i]+=a.posiciones[i];
        }
        return c;
    }

    ind operator-(const struct ind& a)const{
        struct ind c(*this);
        for(int i=0;i<n_jobs;i++){
            c.posiciones[i]-=a.posiciones[i];
        }
        return c;
    }

    ind operator*(double a){
        struct ind c(*this);
        for(int i=0;i<n_jobs;i++){
            c.posiciones[i]*=a;
        }
        return c;
    }

    /*
    ind* operator-(struct ind* a){
        struct ind *c(this);
        c->posiciones=vector<double>(n_jobs);
        for(int i=0;i<n_jobs;i++) c->posiciones[i]=posiciones[i]-a->posiciones[i];
        return c;
    }

    ind* operator*(double a){
        struct ind *c(this);
        c->posiciones=vector<double>(n_jobs);
        for(int i=0;i<n_jobs;i++) c->posiciones[i]=posiciones[i]*a;
        return c;
    }*/

    bool operator<(const ind* a){
        return a->makespan>makespan;
    }

    bool operator>(const ind* a){
        return a->makespan<makespan;
    }
    
    ~ind(){}
};

vector<struct ind*> struct_merge_sort(vector<struct ind*>& arr, const string& atributo){
    int n=arr.size();
    vector<int> temp(n);
    int i;

    for(i=0;i<n;i++){
        if(atributo=="makespan") temp[i]=arr[i]->makespan;
        else if(atributo=="f") temp[i]=arr[i]->f;
        else temp[i]=arr[i]->c_r;
    }
    i=0;
    
    vector<int> ord=b_u_merge_sort<int>(temp, false, false);

    vector<struct ind*> k(n);

    for(auto a:ord) k[i++]=arr[a];
    
    arr=k;

    return k;
}

void pfs_morais::makespan_cont(struct ind *ind_){
    vector<int> vect_ord=b_u_merge_sort<double>(ind_->posiciones, true, true);

    vector<int> pos(n_jobs);

    for(int i=0;i<n_jobs;i++) pos[vect_ord[i]]=i;

    ind_->jobs=pos;
    ind_->makespan=makespan(pos);
}

void pfs_morais::generar_poblacion_aleatoria_cont(){
    if(!poblacion_struct.empty()){
        for(int i=0;i<poblacion_struct.size();i++){
            delete poblacion_struct[i];
        }
        poblacion_struct.resize(0);
    }
    
    if(!poblacion.empty()){
        poblacion.resize(0);
    }
    
    poblacion_struct=vector<struct ind*>(n_inds, nullptr);
    poblacion=vector<vector<int> >(n_inds, vector<int>(n_jobs+1, 0));

    vector<double> posiciones_temp(n_jobs);
    
    for(int i=0;i<n_inds;i++){
        poblacion_struct[i]=new struct ind(n_jobs);
        for(int j=0;j<n_jobs;j++){
            poblacion_struct[i]->posiciones[j]=rand_dbl(rndm);
        }
        poblacion_struct[i]->f=rand_dbl(rndm);
        poblacion_struct[i]->c_r=rand_dbl(rndm);
        makespan_cont(poblacion_struct[i]);

        poblacion.push_back(poblacion_struct[i]->jobs);
        poblacion[poblacion.size()-1].push_back(poblacion_struct[i]->makespan);
    }

    poblacion_struct=struct_merge_sort(poblacion_struct, "makespan");
    poblacion=b_u_merge_sort<int>(poblacion, poblacion[0].size()-1);
}

void pfs_morais::ver(int n){
    if(n==0){
        for(int i=0;i<n_inds;i++){
            if(poblacion_struct[i]!=nullptr){
                /*
                cout<<"POS      ->"<<endl;
                for(int j=0;j<n_jobs-1;j++){
                    cout<<setprecision(2)<<poblacion_struct[i]->posiciones[j]<<", ";
                }
                cout<<poblacion_struct[i]->posiciones[n_jobs-1]<<endl;

                cout<<"JOBS     ->"<<endl;
                for(int j=0;j<n_jobs-1;j++){
                    cout<<poblacion_struct[i]->jobs[j]<<", ";
                }
                cout<<poblacion_struct[i]->jobs[n_jobs-1]<<endl;
                */
                cout<<"MAKESPAN -> "<<poblacion_struct[i]->makespan<<endl;
                /*
                cout<<"F        -> "<<poblacion_struct[i]->f<<endl;
                cout<<"C_R      -> "<<poblacion_struct[i]->c_r<<"\n"<<endl;*/
            }
        }
    }
    else{
        if(poblacion_struct[n]!=nullptr){
            cout<<"POS      ->"<<endl;
            for(int j=0;j<n_jobs-1;j++){
                cout<<poblacion_struct[n]->posiciones[j]<<", ";
            }
            cout<<poblacion_struct[n]->posiciones[n_jobs-1]<<endl;

            cout<<"JOBS     ->"<<endl;
            for(int j=0;j<n_jobs-1;j++){
                cout<<poblacion_struct[n]->jobs[j]<<", ";
            }
            cout<<poblacion_struct[n]->jobs[n_jobs-1]<<endl;

            cout<<"MAKESPAN -> "<<poblacion_struct[n]->makespan<<endl;
            cout<<"F        -> "<<poblacion_struct[n]->f<<endl;
            cout<<"C_R      -> "<<poblacion_struct[n]->c_r<<"\n"<<endl;
        }
    }
}

void pfs_morais::liberar_poblacion(){
    if(!poblacion_struct.empty()){
        for(int i=0;i<poblacion_struct.size();i++){
            delete poblacion_struct[i];
        }
        poblacion_struct.resize(0);
    }
}

vector<vector<double> > pfs_morais::get_params(){
    vector<vector<double> > params(n_inds, vector<double>(2, 0.0));
    for(int i=0;i<n_inds;i++){
        params[i][0]=poblacion_struct[i]->c_r;
        params[i][1]=poblacion_struct[i]->f;
    }
    return params;
}

int pfs_morais::DSADE_PFS_1(int n_iters,
                            const string& cruza,
                            int verbose,
                            double p,
                            vector<double>& promedios,
                            vector<double>& desvest,
                            vector<double>& diff_prom,
                            vector<double>& diff_desvest,
                            vector<int>& mejores,
                            FILE *file){
    

    if(file==nullptr) cout<<"ITERACION MEJOR PROMEDIO_MAKESPAN DESVEST_MAKESPAN PROMEDIO_DIFF DESVEST_DIFF\n";
    else fprintf(file, "ITERACION MEJOR PROMEDIO_MAKESPAN DESVEST_MAKESPAN PROMEDIO_DIFF DESVEST_DIFF\n");

    if(poblacion_struct.empty()) return -1;

    poblacion_struct=struct_merge_sort(poblacion_struct, "makespan");

    int mejor=poblacion_struct[0]->makespan;

    promedios.clear();
    desvest.clear();
    mejores.clear();
    diff_prom.clear();
    diff_desvest.clear();

    int ref, cand_1, cand_2, cand_3, cand_4, i, n_news=0;
    double c_r_=0.5, f_=0.5;
    vector<double> succesful_c_r;
    vector<double> succesful_f;

    for(int iter=0;iter<n_iters;iter++){
        normal_distribution<double> dist_c_r(c_r_, 0.1);
        cauchy_distribution<double> dist_f(f_, 0.1);

        for(int specimen=0;specimen<n_inds;specimen++){
            do poblacion_struct[specimen]->c_r=dist_c_r(rndm);
            while(poblacion_struct[specimen]->c_r<=0.0||poblacion_struct[specimen]->c_r>=1.0);

            do poblacion_struct[specimen]->f=dist_f(rndm);
            while(poblacion_struct[specimen]->f<=0.0||poblacion_struct[specimen]->f>=1.0);

            /*
            if(fabs(poblacion_struct[specimen]->c_r)>1.0){
                poblacion_struct[specimen]->c_r-=floor(poblacion_struct[specimen]->c_r);
            }

            if(fabs(poblacion_struct[specimen]->f)>1.0){
                poblacion_struct[specimen]->f-=floor(poblacion_struct[specimen]->f);
            }

            poblacion_struct[specimen]->c_r=(poblacion_struct[specimen]->c_r<0.0)?(-1.0*poblacion_struct[specimen]->c_r):((poblacion_struct[specimen]->c_r>1.0)?(poblacion_struct[specimen]->c_r-2.0*(poblacion_struct[specimen]->c_r-1.0)):(poblacion_struct[specimen]->c_r));
            poblacion_struct[specimen]->f=(poblacion_struct[specimen]->f<0.0)?(-1.0*poblacion_struct[specimen]->f):((poblacion_struct[specimen]->f>1.0)?(poblacion_struct[specimen]->f-2.0*(poblacion_struct[specimen]->f-1.0)):(poblacion_struct[specimen]->f));
            */
        }

        for(int specimen=0;specimen<n_inds;specimen++){
            struct ind* candidato=new struct ind(poblacion_struct[specimen]->posiciones, poblacion_struct[specimen]->jobs, poblacion_struct[specimen]->makespan, poblacion_struct[specimen]->f, poblacion_struct[specimen]->c_r);

            //mutations
            if(cruza=="SHADE"){
                //eligiendo los individuos 
                do ref=rand_int(rndm)%int(ceil(n_inds*p));
                while(ref==specimen);

                do cand_1=rand_int(rndm)%n_inds;
                while(cand_1==specimen||cand_1==ref);

                do cand_2=rand_int(rndm)%n_inds;
                while(cand_2==specimen||cand_2==ref||cand_2==cand_1);
                //haciendo la operación
                
                *candidato=*poblacion_struct[ref]+
                          (*poblacion_struct[cand_1]-*poblacion_struct[cand_2])*poblacion_struct[specimen]->f;
            }
            
            else if(cruza=="clasica 1bin"){
                //eligiendo los individuos 
                do ref=rand_int(rndm)%n_inds;
                while(ref==specimen);

                do cand_1=rand_int(rndm)%n_inds;
                while(cand_1==specimen||cand_1==ref);

                do cand_2=rand_int(rndm)%n_inds;
                while(cand_2==specimen||cand_2==ref||cand_2==cand_1);
                
                //haciendo la operación
                *candidato=*poblacion_struct[ref]+
                          (*poblacion_struct[cand_1]-*poblacion_struct[cand_2])*poblacion_struct[specimen]->f;
            }
            
            else if(cruza=="clasica 2bin"){
                //eligiendo los individuos 
                do ref=rand_int(rndm)%n_inds;
                while(ref==specimen);

                do cand_1=rand_int(rndm)%n_inds;
                while(cand_1==specimen||cand_1==ref);

                do cand_2=rand_int(rndm)%n_inds;
                while(cand_2==specimen||cand_2==ref||cand_2==cand_1);

                do cand_3=rand_int(rndm)%n_inds;
                while(cand_3==specimen||cand_3==ref||cand_3==cand_1||cand_3==cand_2);

                do cand_4=rand_int(rndm)%n_inds;
                while(cand_4==specimen||cand_4==ref||cand_4==cand_1||cand_4==cand_2||cand_4==cand_3);
                
                //haciendo la operación
                *candidato=*poblacion_struct[ref]+
                          (*poblacion_struct[cand_1]-*poblacion_struct[cand_2])*poblacion_struct[specimen]->f+
                          (*poblacion_struct[cand_3]-*poblacion_struct[cand_4])*poblacion_struct[specimen]->f;
            }

            
            //combination
            ref=rand_int(rndm)%n_jobs;
            for(i=0;i<n_jobs;i++){
                if(!(rand_dbl(rndm)<poblacion_struct[specimen]->c_r||i==ref)){
                    candidato->posiciones[i]=poblacion_struct[specimen]->posiciones[i];
                }
            }
            

            //selection
            makespan_cont(candidato);

            if(poblacion_struct[specimen]->makespan>candidato->makespan){
                succesful_c_r.push_back(candidato->c_r);
                succesful_f.push_back(candidato->f);

                n_news++;

                delete poblacion_struct[specimen];
                poblacion_struct[specimen]=candidato;

                poblacion[specimen]=candidato->jobs;
                poblacion[specimen].push_back(candidato->makespan);

                mejor=min(mejor, poblacion_struct[specimen]->makespan);
            }
            else{
                delete candidato;
            }

        }

        for(int specimen=0;specimen<n_inds;specimen++){
            makespan_cont(poblacion_struct[specimen]);
            poblacion[specimen]=poblacion_struct[specimen]->jobs;
            poblacion[specimen].push_back(poblacion_struct[specimen]->makespan);
        }

        poblacion_struct=struct_merge_sort(poblacion_struct, "makespan");
        poblacion=b_u_merge_sort<int>(poblacion, poblacion[0].size()-1);

        //params update
        if(!succesful_c_r.empty()){
            c_r_=(1.0-0.1)*c_r_+0.1*promedio<double>(succesful_c_r);
            succesful_c_r.resize(0);
        }
        if(!succesful_f.empty()){
            f_=(1.0-0.1)*f_+0.1*lehmer<double>(succesful_f, 2);
            succesful_f.resize(0);
        }
        
        



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
    return 0;
}

int pfs_morais::DSADE_PFS_2(int n_iters,
                            int verbose,
                            double p,
                            int LP, 
                            vector<double>& promedios,
                            vector<double>& desvest,
                            vector<double>& diff_prom,
                            vector<double>& diff_desvest,
                            vector<int>& mejores,
                            FILE *file){
    

    if(file==nullptr) cout<<"ITERACION MEJOR PROMEDIO_MAKESPAN DESVEST_MAKESPAN PROMEDIO_DIFF DESVEST_DIFF\n";
    else fprintf(file, "ITERACION MEJOR PROMEDIO_MAKESPAN DESVEST_MAKESPAN PROMEDIO_DIFF DESVEST_DIFF\n");

    if(poblacion_struct.empty()) return -1;

    poblacion_struct=struct_merge_sort(poblacion_struct, "makespan");

    int mejor=poblacion_struct[0]->makespan;

    promedios.clear();
    desvest.clear();
    mejores.clear();
    diff_prom.clear();
    diff_desvest.clear();

    int ref, cand_1, cand_2, cand_3, cand_4, i, n_news=0;
    double c_r_1=0.5, c_r_2=0.5, c_r_3=0.5, c_r_4=0.5;
    vector<double> succes_rate_cruza{0.25, 0.25, 0.25, 0.25};
    vector<vector<int> > aciertos_fallos(4);
    vector<vector<double> > historial_aciertos_c_r(4);

    vector<int> cuenta_mejoras(4, 0);
    vector<int> cuenta_mejoras_2(4, 0);

    vector<vector<int>> ventana_exitos(4, vector<int>(LP, 0));
    vector<vector<int>> ventana_fallos(4, vector<int>(LP, 0));

    vector<int> sum_exitos(4, 0);
    vector<int> sum_fallos(4, 0);
    /**/
    for(int iter=0;iter<n_iters;iter++){
        //parameter generation
        normal_distribution<double> dist_c_r_1(c_r_1, 0.1);
        normal_distribution<double> dist_c_r_2(c_r_2, 0.1);
        normal_distribution<double> dist_c_r_3(c_r_3, 0.1);
        normal_distribution<double> dist_c_r_4(c_r_4, 0.1);

        normal_distribution<double> dist_f(0.5, 0.3);

        for(int specimen=0;specimen<n_inds;specimen++){
            do poblacion_struct[specimen]->c_r_[0]=dist_c_r_1(rndm);
            while(poblacion_struct[specimen]->c_r_[0]<=0.0||poblacion_struct[specimen]->c_r_[0]>=1.0);

            do poblacion_struct[specimen]->c_r_[1]=dist_c_r_2(rndm);
            while(poblacion_struct[specimen]->c_r_[1]<=0.0||poblacion_struct[specimen]->c_r_[1]>=1.0);

            do poblacion_struct[specimen]->c_r_[2]=dist_c_r_3(rndm);
            while(poblacion_struct[specimen]->c_r_[2]<=0.0||poblacion_struct[specimen]->c_r_[2]>=1.0);
            
            do poblacion_struct[specimen]->c_r_[3]=dist_c_r_4(rndm);
            while(poblacion_struct[specimen]->c_r_[3]<=0.0||poblacion_struct[specimen]->c_r_[3]>=1.0);
            
            do poblacion_struct[specimen]->f=dist_f(rndm);
            while(poblacion_struct[specimen]->f<=0.0||poblacion_struct[specimen]->f>=1.0);
            
        }

        
        //proceso DDE
        for(int specimen=0;specimen<n_inds;specimen++){
            struct ind* candidato=new struct ind(poblacion_struct[specimen]->posiciones, poblacion_struct[specimen]->jobs, poblacion_struct[specimen]->makespan, poblacion_struct[specimen]->f, poblacion_struct[specimen]->c_r);
            candidato->c_r_=poblacion_struct[specimen]->c_r_;

            int cruza_elegida=ruleta<double>(succes_rate_cruza);

            
            if(cruza_elegida==0){
                //rand_1_bin

                //eligiendo los individuos 
                do ref=rand_int(rndm)%n_inds;
                while(ref==specimen);

                do cand_1=rand_int(rndm)%n_inds;
                while(cand_1==specimen||cand_1==ref);

                do cand_2=rand_int(rndm)%n_inds;
                while(cand_2==specimen||cand_2==ref||cand_2==cand_1);
                
                //haciendo la operación
                *candidato=*poblacion_struct[ref]+
                          (*poblacion_struct[cand_1]-*poblacion_struct[cand_2])*poblacion_struct[specimen]->f;

            }
            
            else if(cruza_elegida==1){
                //rand_2_bin
                
                //eligiendo los individuos 
                do ref=rand_int(rndm)%n_inds;
                while(ref==specimen);

                do cand_1=rand_int(rndm)%n_inds;
                while(cand_1==specimen||cand_1==ref);

                do cand_2=rand_int(rndm)%n_inds;
                while(cand_2==specimen||cand_2==ref||cand_2==cand_1);

                do cand_3=rand_int(rndm)%n_inds;
                while(cand_3==specimen||cand_3==ref||cand_3==cand_1||cand_3==cand_2);

                do cand_4=rand_int(rndm)%n_inds;
                while(cand_4==specimen||cand_4==ref||cand_4==cand_1||cand_4==cand_2||cand_4==cand_3);
                
                //haciendo la operación
                *candidato=*poblacion_struct[ref]+
                          (*poblacion_struct[cand_1]-*poblacion_struct[cand_2])*poblacion_struct[specimen]->f+
                          (*poblacion_struct[cand_3]-*poblacion_struct[cand_4])*poblacion_struct[specimen]->f;
            }
            
            else if(cruza_elegida==2){
                //rand_to_best_2_bin
                
                //eligiendo los individuos
                ref=0;

                do cand_1=rand_int(rndm)%n_inds;
                while(cand_1==specimen||cand_1==ref);

                do cand_2=rand_int(rndm)%n_inds;
                while(cand_2==specimen||cand_2==ref||cand_2==cand_1);

                do cand_3=rand_int(rndm)%n_inds;
                while(cand_3==specimen||cand_3==ref||cand_3==cand_1||cand_3==cand_2);

                do cand_4=rand_int(rndm)%n_inds;
                while(cand_4==specimen||cand_4==ref||cand_4==cand_1||cand_4==cand_2||cand_4==cand_3);
                
                //haciendo la operación
                *candidato=*poblacion_struct[ref]+
                          (*poblacion_struct[cand_1]-*poblacion_struct[cand_2])*poblacion_struct[specimen]->f+
                          (*poblacion_struct[cand_3]-*poblacion_struct[cand_4])*poblacion_struct[specimen]->f;
            }
            
            else{
                //current_to_rand_1

                //eligiendo los individuos 
                ref=specimen;

                do cand_1=rand_int(rndm)%n_inds;
                while(cand_1==specimen||cand_1==ref);

                do cand_2=rand_int(rndm)%n_inds;
                while(cand_2==specimen||cand_2==ref||cand_2==cand_1);
                
                //haciendo la operación
                *candidato=*poblacion_struct[ref]+
                          (*poblacion_struct[cand_1]-*poblacion_struct[cand_2])*poblacion_struct[specimen]->f;
            }
                      
            //combination
            ref=rand_int(rndm)%n_jobs;
            for(i=0;i<n_jobs;i++){
                if(!(rand_dbl(rndm)<poblacion_struct[specimen]->c_r_[cruza_elegida]||i==ref)){
                    candidato->posiciones[i]=poblacion_struct[specimen]->posiciones[i];
                }
            }
            

            //selection
            makespan_cont(candidato);

            if(poblacion_struct[specimen]->makespan>candidato->makespan){
                n_news++;

                delete poblacion_struct[specimen];
                poblacion_struct[specimen]=candidato;

                poblacion[specimen]=candidato->jobs;
                poblacion[specimen].push_back(candidato->makespan);

                if(aciertos_fallos[cruza_elegida].size()<LP){
                    aciertos_fallos[cruza_elegida].push_back(1);
                }
                else{
                    aciertos_fallos[cruza_elegida][(cuenta_mejoras_2[cruza_elegida]++)%LP]=1;
                }

                if(historial_aciertos_c_r[cruza_elegida].size()<LP){
                    historial_aciertos_c_r[cruza_elegida].push_back(candidato->c_r_[cruza_elegida]);
                }
                else{
                    historial_aciertos_c_r[cruza_elegida][(cuenta_mejoras[cruza_elegida]++)%LP]=candidato->c_r_[cruza_elegida];
                }
                mejor=min(mejor, poblacion_struct[specimen]->makespan);
                
            }
            else{
                delete candidato;

                if(aciertos_fallos[cruza_elegida].size()<LP){
                    aciertos_fallos[cruza_elegida].push_back(-1);
                }
                else{
                    aciertos_fallos[cruza_elegida][(cuenta_mejoras_2[cruza_elegida]++)%LP]=-1;
                }
            }
        }

        
        for(int i=0;i<4;i++){
            int aciertos=0;
            int fallos=0;
            for(int j=0;j<aciertos_fallos[i].size();j++){
                if(aciertos_fallos[i][j]==1){
                    aciertos++;
                }
                else{
                    fallos++;
                }
            }
            succes_rate_cruza[i]=(aciertos*1.0)/(aciertos+fallos+0.1);
        }

        c_r_1=promedio<double>(historial_aciertos_c_r[0]);
        c_r_2=promedio<double>(historial_aciertos_c_r[1]);
        c_r_3=promedio<double>(historial_aciertos_c_r[2]);
        c_r_4=promedio<double>(historial_aciertos_c_r[3]);

        poblacion_struct=struct_merge_sort(poblacion_struct, "makespan");
        poblacion=b_u_merge_sort<int>(poblacion, poblacion[0].size()-1);

        for(int specimen=0;specimen<n_inds;specimen++){
            makespan_cont(poblacion_struct[specimen]);
            poblacion[specimen]=poblacion_struct[specimen]->jobs;
            poblacion[specimen].push_back(poblacion_struct[specimen]->makespan);
        }
        
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
    return 0;
}

void experimento_DSADE_PFS_1(string name, string carpeta, int verbose, bool archivo, bool verbose_){
    cout<<"INICIO DE EXPERIMENTO DSADE_PFS_1"<<endl;
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

void experimento_DSADE_PFS_2(string name, string carpeta, int verbose, bool archivo, bool verbose_){
    cout<<"INICIO DE EXPERIMENTO DSADE_PFS_2"<<endl;
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
