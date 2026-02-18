#include <iostream>

using namespace std;

#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <unordered_map>

#include <typeinfo>


//funciones que no pertenecen a ninguna clase
template <typename T> void juntar(vector<T>& arr, int izq, int med, int der){
    //medimos los tamaños de los subarrays
    int n1=med-izq+1;
    int n2=der-med;
    
    //creamos 2 vectores para que almacenen el subarray derecho e izquierdo
    vector<T> arr1(n1), arr2(n2);
    
    //los copiamos
    for(int i=0;i<n1;i++) arr1[i]=arr[izq+i];
    for(int j=0;j<n2;j++) arr2[j]=arr[med+1+j];
    
    //declaramos e inicializamos los índices
    int i=0, j=0, k=izq; 
    
    //juntamos los vectores temporales
    while(i<n1&&j<n2){
        if(arr1[i]<=arr2[j]){
            arr[k]=arr1[i];
            i++;
        } 
        else{
            arr[k]=arr2[j];
            j++;
        }
        k++;
    }
    
    //copiamos lo que resta de arr1 en arr, si es que sobra algo
    while(i<n1){
        arr[k]=arr1[i];
        i++;
        k++;
    }
    
    //copiamos lo que resta de arr2 en arr, si es que sobra algo
    while(j<n2){
        arr[k]=arr2[j];
        j++;
        k++;
    }
}

//key nos dice si queremos que regrese el vector ordenado, o los índices ordenados del vector original, independientemente del valor que tenga key
//ejemplo:
//b_u_merge_sort({1, 3, 2}) -> {1, 2, 3} (regresa el vector ordenado)
//                             ┌-----┐
//b_u_merge_sort({1, 3, 2}, key=true ) -> {0, 2, 1} (regresa los índices ordenados para "ordenar" el vector)
//b_u_merge_sort({1, 3, 2}, key=false) -> {0, 2, 1}

//                                                                 false=pequeño->grande, true=grande->pequeño
template <typename T> vector<T> b_u_merge_sort(vector<T> arr, bool orden=false){
    vector<T> arr_c=arr;

    int n=arr_c.size();
    
    //iteramos sobre subarrays de tamaños cada vez mas grandes (el doble de grandes)
    //       ┌tamaño actual
    //       |          ┌hasta que tenga el tamaño del vector a ordenar 
    //       |          |                      ┌duplicamos el tamaño y seguimos
    for (int t_actual=1;t_actual<=n-1;t_actual=2*t_actual){

        //       ┌empezamos con la izquerda
        //                 ┌hasta que tenga el tamaño del vector a ordenar
        //                          ┌vamos a ir de 2 en 2 tamaños, seleccionandolos para juntar
        for (int izq=0;izq<n-1;izq+=2*t_actual){

            //elegimos puntos de inicio diferentes para izq y der
            int med=min(izq+t_actual-1, n-1);
            int der=min(izq+2*t_actual-1, n-1);
            
            //juntamos los vectores
            juntar<T>(arr_c, izq, med, der);
        }
    }
    
    if(orden){
        vector<T> arr_c_v;
        for(int i=0;i<arr_c.size();i++) arr_c_v.insert(arr_c_v.begin(), arr_c[i]);
        return arr_c_v;
    }
    else{
        return arr_c;
    }
}

template <typename T>vector<int> mapeo_posiciones(vector<T>& arr, vector<T>& arr_c){
    int n=arr.size();
    int m=arr_c.size();
    vector<int> orden(m);

    //usamos un unordered map para ordenar los elementos de el arreglo original
    //tipo T, int para que reciba el valor de arr o arr_c como key y regrese un entero
    unordered_map<T, vector<int>> posiciones;
    for (int i=0;i<arr.size();i++){
        posiciones[arr[i]].push_back(i);
    }

    //usamos otro unordered map para registrar los repetidos
    unordered_map<T, int> usado;

    //para cada elemento en arr_c, toma la siguiente posición disponible
    for (int i = 0; i < m; ++i) {
        T val=arr_c[i];

        //┌aquí usamos auto para que el iterador "it" no tenga problemas
        auto it=posiciones.find(val);
        if(it==posiciones.end()){
            cout<<"\nERROR: NO SE ENCUENTRA EL ELEMENTO DENTRO DEL ARREGLO"<<endl;
            return {};
        }

        //cuál ocurrencia usar
        int k=usado[val]++;
        if(k>=(int)(it->second.size())){
            cout<<"\nERROR: NO COINCIDEN LOS DOS VECTORES"<<endl;
            return {};
        }

        //guardamos el valor asociado a la key k
        orden[i]=it->second[k];
    }

    return orden;
}

template <typename T> vector<int> b_u_merge_sort(vector<T> arr, bool key, bool orden_=false){
    vector<T> arr_c=arr;

    int n=arr_c.size();
    
    //iteramos sobre subarrays de tamaños cada vez mas grandes (el doble de grandes)
    //       ┌tamaño actual
    //       |          ┌hasta que tenga el tamaño del vector a ordenar 
    //       |          |                      ┌duplicamos el tamaño y seguimos
    for (int t_actual=1;t_actual<=n-1;t_actual=2*t_actual){

        //       ┌empezamos con la izquerda
        //       |         ┌hasta que tenga el tamaño del vector a ordenar
        //       |         |        ┌vamos a ir de 2 en 2 tamaños, seleccionandolos para juntar
        for (int izq=0;izq<n-1;izq+=2*t_actual){

            //elegimos puntos de inicio diferentes para izq y der
            int med=min(izq+t_actual-1, n-1);
            int der=min(izq+2*t_actual-1, n-1);
            
            //juntamos los vectores
            juntar<T>(arr_c, izq, med, der);
        }
    }

    vector<int> orden=mapeo_posiciones(arr, arr_c);

    if(orden_){
        vector<int> arr_c_v;
        for(int i=0;i<orden.size();i++) arr_c_v.insert(arr_c_v.begin(), orden[i]);
        return arr_c_v;
    }
    else{
        return orden;
    }
}

template <typename T> vector<vector<T> > b_u_merge_sort(vector<vector<T> > m, int pos=0, bool orden=false, bool verbose=false){
    vector<T> v;
    for(int i=0;i<m.size();i++) v.push_back(m[i][pos]);
    vector<T> r=b_u_merge_sort(v, orden, false);
    vector<vector<T> > res;
    for(int i=0;i<r.size();i++){
        res.push_back(m[r[i]]);
    }
    if(orden){
        vector<vector<T> > arr_c_v;
        for(int i=0;i<res.size();i++) arr_c_v.insert(arr_c_v.begin(), res[i]);
        return arr_c_v;
    }
    else{
        return res;
    }
}

vector<struct ind*> struct_merge_sort(vector<struct ind*>& arr, const string& atributo);

template <typename T> bool contiene(vector<T> v, T a){
    for(int i=0;i<v.size();i++) if(v[i]==a) return true;
    return false;
}

template <typename T> T maximo(vector<T> v){
    T m=-100;
    bool cambiado=false;
    int count=0;
    while(cambiado==false&&count<10000000){
        for(int i=0;i<v.size();i++){
            if(v[i]>m){
                m=v[i];
                cambiado=true;
            }
        }
        if(!cambiado){
            m*=10;
        }
        count++;
    }
    return (cambiado)?(m):(v[0]);
}

template <typename T> T minimo(vector<T> v){
    T m=100;
    bool cambiado=false;
    int count=0;
    while(cambiado==false&&count<10000000){
        for(int i=0;i<v.size();i++){
            if(v[i]<m){
                m=v[i];
                cambiado=true;
            }
        }
        if(!cambiado){
            m*=10;
        }
        count++;
    }
    return (cambiado)?(m):(v[0]);
}

template <typename T> int where(vector<T> &v, T x){
    for(int i=0;i<v.size();i++) if(v[i]==x) return i;
    return -1;
}

template <typename T> vector<vector<T> > posibilidades(vector<T> v, T obj){
    if(v.size()==0) return vector<vector<T> > {{obj}};

    vector<vector<T> > res;

    for(int i=0;i<v.size()+1;i++){
        vector<T> temp=v;
        temp.insert(temp.begin()+i, obj);
        res.push_back(temp);
    }
    return res;
}

template <typename T> T suma(vector<T> v){
    T sum=0;
    for(auto _:v) sum+=_;
    return sum;
}

template <typename T> T lehmer(vector<T> v, int n){
    T sum=0.0, sum_n=0.0;
    for(auto a:v){
        sum+=pow(a, n-1);
        sum_n+=pow(a, n);
    }
    return sum_n/sum;
}

template <typename T> int ruleta(vector<T> v){
    if(v.empty()) return 0;

    T suma=0.0;
    for(int i=0;i<v.size();i++){
        if(v[i]<0) return 0;
        else suma+=v[i];
    }

    static thread_local mt19937 gen(random_device{}());
    uniform_real_distribution<long double> dist(0.0, (long double)suma);

    long double r=dist(gen);
    long double acumulado=0.0;

    for(int i=0;i<v.size();i++){
        acumulado+=v[i];
        if(r<=acumulado) return i;
    }

    return 0;
}

template <typename T> vector<vector<T>> combinatoria(vector<T> v){
    //casos base
    if(v.size()==2) return vector<vector<T> >{{v[0], v[1]}, {v[1], v[0]}};
    else if(v.size()<2){
        if(v.size()==1) return vector<vector<T> >{{v[0]}};
        else if(v.size()==0) return vector<vector<T> > {{}};
    }

    //recursivo
    vector<vector<T> > res;
    //iteramos sobre todos los elementos de v
    for(int i=0;i<v.size();i++){
        vector<T> restantes;
        for(int j=0;j<v.size();j++) if(j!=i) restantes.push_back(j);
        vector<vector<T> > r=combinatoria(restantes);
        for(auto lr:r){
            vector<T> temp{v[i]};
            for(auto _:lr){
                temp.push_back(v[_]);
            }
            res.push_back(temp);
        }
    }

    return res;
}

template <typename T> vector<double> mean_desv_est(vector<T> v){
    int n=v.size();
    //caso trivial
    if(n<=1) return vector<double>{0.0, 0.0};

    //promedio
    T suma=0;
    for(auto x:v) suma+=x;
    double promedio=(suma*1.0)/n;

    //varianza
    double var=0.0;
    for(double x:v) var+=(x-promedio)*(x-promedio);
    var/=(n-1);

    return vector<double>{promedio, sqrt(var)};
}

template <typename T> T promedio(vector<T> v){
    int n=v.size(), i;
    if(n<=1){
        if(n==0) return 0.0;
        else return v[0];
    }
    
    T suma=0.0;
    for(i=0;i<n;i++){
        suma+=v[i];
    }
    return (suma*1.0)/n;
}

template <typename T> T promedio(vector<vector<T> > v){
    int n=v.size(), i, j, count=0;
    if(n<=1){
        if(n==0) return 0.0;
        else return v[0];
    }
    
    T suma=0.0;
    for(i=0;i<n;i++){
        for(j=0;j<v[i].size();j++){
            if(v[i][j]!=-1){
                count++;
                suma+=v[i][j];
            }
        }
    }
    if(count!=0){
        return (suma*1.0)/count;
    }
    else{
        return 0.0;
    }
}


void experimento(string name, string carpeta, int verbose, bool archivo=true, bool verbose_=false);

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


//clases
class pfs{
public:
    //info de la instancia
    int n_jobs;
    int n_machines;
    vector<vector<int> > tiempos;

    //info de la corrida del algoritmo
    int n_inds;
    vector<vector<int> > poblacion;

    //vi en un video de youtube, que para propósitos de velocidad, si vas a usar números aleatorios
    //de mersene twistter (mt19937) es mejor declararlos como variable global de la clase en los que vas a usar los números aleatorios
    //además, se hace thread_local porque tengo la intención de paralelizar las corridas con OMP
    //no se si me vaya a dar el tiempo para eso, pero es la intención
    //en el video se menciona que tienes que hacer local para cada hilo, para evitar conflictos de carrera (que puede generar comportamientos indefinidos)
    //soy conciente que el código no es suficientemente rápido como para que eso sea un problema real, pero mas vale prevenir
    //link del video:
    //https://youtu.be/hp4Nlf8IRgs?si=HOWr0-bX2cKB8d0t , minuto->7:59

    //también decidí usar mt19937 porque tiene la capacidad de generar números aleatorios flotantes de una, con su precisión
    //a comparación de srand, que solo genera enteros y tienes que "armar" los dobles manualmente
    //si quieres una precisión de 5 decimales, entonces tienes que generar al menos 5 números aleatorios con srand
    //lo que hace que sea 11% mas rápido
    //estos son los tests que se hicieron para tomar la decisión:

    /*
    int main(){
        static thread_local mt19937 rndm(10);
        uniform_real_distribution<double> rand_(0.0, 1.0);
        double temp;
        unsigned t0=clock();
        for(int i=0;i<10000000;i++) temp=rand_(rndm);
        cout<<(double(clock()-t0)/CLOCKS_PER_SEC)<<" , "<<temp;
        return 0;
    } ->0.309 segundos

    int main(){
        srand(time(NULL));
        double temp;
        unsigned t0=clock();
        for(int i=0;i<10000000;i++) for(int j=0;j<5;j++) temp=rand()%1000;
        cout<<(double(clock()-t0)/CLOCKS_PER_SEC)<<" , "<<temp;
        return 0;
    } ->0.348 segundos*/

    //se ponen en esta clase los atributos para que las otras clases los hereden
    static thread_local mt19937 rndm;
    uniform_real_distribution<double> rand_dbl;
    uniform_int_distribution<int> rand_int;

    //constructor
    pfs(int n_inds=100, int n_jobs=20, int n_machines=20):n_jobs(n_jobs), n_machines(n_machines), n_inds(n_inds), tiempos({{}}), poblacion({{}}), rand_dbl(0.0, 1.0), rand_int(0, 100000){}
    //destructor
    ~pfs(){}

    //funciones
    void cargar_instancia(int inst);
    vector<vector<int> > _cargar_instancia_jsplib(const char *archivo);
    vector<vector<int> > _cargar_instancia_go(const char *archivo);
    int makespan(int ind);
    int makespan(vector<int>& ind, bool verbose=false);
    vector<int> permutacion_aleatoria();
    void generar_poblacion_aleatoria();
    vector<vector<int> > generar_poblacion_aleatoria(int n);
    void ver_poblacion(FILE *file=NULL);
    vector<vector<int> > _op_resta(vector<int> ind_1, vector<int> ind_2, bool verbose=false);
    vector<vector<int> > op_resta(int ind_1, int ind_2, bool verbose=false);
    vector<vector<int> > op_resta(vector<int> ind_1, int ind_2, bool verbose=false);
    vector<vector<int> > op_resta(int ind_1, vector<int> ind_2, bool verbose=false);
    vector<vector<int> > op_resta(vector<int> ind_1, vector<int> ind_2, bool verbose=false);

    vector<int> _op_suma(vector<vector<int> > sec, vector<int> ind, double frac);
    vector<int> op_suma(vector<vector<int> > sec, vector<int> ind, double frac, bool verbose=false);
    vector<int> op_suma(vector<vector<int> > sec, int ind, double frac, bool verbose=false);

    vector<int> faltantes(vector<int> ind);
    bool valido(vector<int> ind);
    vector<int> calcular_diferencias();

    vector<vector<int> > NEH(int cant, FILE *file=nullptr);

    void agregar_individuos(int n);

    double temperatura(int iter, double theta);

    vector<vector<int> > makespan_incremental(vector<int>& ind, bool verbose=false);

    int makespan_incremental(vector<int>& perm, int job, int pos, vector<vector<int> >& c);
};

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

void experimento_PGS_EDA(string name, string carpeta, int verbose, bool archivo, bool verbose_);

void experimento_DDE_RLS(string name, string carpeta, int verbose, bool archivo, bool verbose_);

#endif
