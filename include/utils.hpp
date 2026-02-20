#include <iostream>

using namespace std;

#ifndef UTILS_HPP
#define UTILS_HPP

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


#endif