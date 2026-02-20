#include <iostream>

using namespace std;

#ifndef PFS_HPP
#define PFS_HPP

#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <unordered_map>

#include <typeinfo>


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



#endif