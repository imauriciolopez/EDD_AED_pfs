#include "funciones.hpp"

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

//definiciones de dónde están las carpetas y demás
//demo (5 trabajos 5 máquinas)
#define GO_EXT_D_2 "instancias/go/tai_demo_2.fsp"
//demo (20 trabajos 10 máquinas)
#define GO_EXT_D "instancias/go/tai_demo.fsp"

//instancias obtenidas de:
//https://github.com/chneau/go-taillard
#define GO_EXT_0  "instancias/go/tai20_5_0.fsp"
#define GO_EXT_1  "instancias/go/tai20_5_1.fsp"
#define GO_EXT_2  "instancias/go/tai20_5_2.fsp"
#define GO_EXT_3  "instancias/go/tai20_5_3.fsp"
#define GO_EXT_4  "instancias/go/tai20_5_4.fsp"
#define GO_EXT_5  "instancias/go/tai20_5_5.fsp"
#define GO_EXT_6  "instancias/go/tai20_5_6.fsp"
#define GO_EXT_7  "instancias/go/tai20_5_7.fsp"
#define GO_EXT_8  "instancias/go/tai20_5_8.fsp"
#define GO_EXT_9  "instancias/go/tai20_5_9.fsp"

#define GO_EXT_10 "instancias/go/tai20_10_0.fsp"
#define GO_EXT_11 "instancias/go/tai20_10_1.fsp"
#define GO_EXT_12 "instancias/go/tai20_10_2.fsp"
#define GO_EXT_13 "instancias/go/tai20_10_3.fsp"
#define GO_EXT_14 "instancias/go/tai20_10_4.fsp"
#define GO_EXT_15 "instancias/go/tai20_10_5.fsp"
#define GO_EXT_16 "instancias/go/tai20_10_6.fsp"
#define GO_EXT_17 "instancias/go/tai20_10_7.fsp"
#define GO_EXT_18 "instancias/go/tai20_10_8.fsp"
#define GO_EXT_19 "instancias/go/tai20_10_9.fsp"

#define GO_EXT_20 "instancias/go/tai20_20_0.fsp"
#define GO_EXT_21 "instancias/go/tai20_20_1.fsp"
#define GO_EXT_22 "instancias/go/tai20_20_2.fsp"
#define GO_EXT_23 "instancias/go/tai20_20_3.fsp"
#define GO_EXT_24 "instancias/go/tai20_20_4.fsp"
#define GO_EXT_25 "instancias/go/tai20_20_5.fsp"
#define GO_EXT_26 "instancias/go/tai20_20_6.fsp"
#define GO_EXT_27 "instancias/go/tai20_20_7.fsp"
#define GO_EXT_28 "instancias/go/tai20_20_8.fsp"
#define GO_EXT_29 "instancias/go/tai20_20_9.fsp"

#define GO_EXT_30 "instancias/go/tai50_5_0.fsp"
#define GO_EXT_31 "instancias/go/tai50_5_1.fsp"
#define GO_EXT_32 "instancias/go/tai50_5_2.fsp"
#define GO_EXT_33 "instancias/go/tai50_5_3.fsp"
#define GO_EXT_34 "instancias/go/tai50_5_4.fsp"
#define GO_EXT_35 "instancias/go/tai50_5_5.fsp"
#define GO_EXT_36 "instancias/go/tai50_5_6.fsp"
#define GO_EXT_37 "instancias/go/tai50_5_7.fsp"
#define GO_EXT_38 "instancias/go/tai50_5_8.fsp"
#define GO_EXT_39 "instancias/go/tai50_5_9.fsp"

#define GO_EXT_40 "instancias/go/tai50_10_0.fsp"
#define GO_EXT_41 "instancias/go/tai50_10_1.fsp"
#define GO_EXT_42 "instancias/go/tai50_10_2.fsp"
#define GO_EXT_43 "instancias/go/tai50_10_3.fsp"
#define GO_EXT_44 "instancias/go/tai50_10_4.fsp"
#define GO_EXT_45 "instancias/go/tai50_10_5.fsp"
#define GO_EXT_46 "instancias/go/tai50_10_6.fsp"
#define GO_EXT_47 "instancias/go/tai50_10_7.fsp"
#define GO_EXT_48 "instancias/go/tai50_10_8.fsp"
#define GO_EXT_49 "instancias/go/tai50_10_9.fsp"

#define GO_EXT_50 "instancias/go/tai50_20_0.fsp"
#define GO_EXT_51 "instancias/go/tai50_20_1.fsp"
#define GO_EXT_52 "instancias/go/tai50_20_2.fsp"
#define GO_EXT_53 "instancias/go/tai50_20_3.fsp"
#define GO_EXT_54 "instancias/go/tai50_20_4.fsp"
#define GO_EXT_55 "instancias/go/tai50_20_5.fsp"
#define GO_EXT_56 "instancias/go/tai50_20_6.fsp"
#define GO_EXT_57 "instancias/go/tai50_20_7.fsp"
#define GO_EXT_58 "instancias/go/tai50_20_8.fsp"
#define GO_EXT_59 "instancias/go/tai50_20_9.fsp"

#define GO_EXT_60 "instancias/go/tai100_5_0.fsp"
#define GO_EXT_61 "instancias/go/tai100_5_1.fsp"
#define GO_EXT_62 "instancias/go/tai100_5_2.fsp"
#define GO_EXT_63 "instancias/go/tai100_5_3.fsp"
#define GO_EXT_64 "instancias/go/tai100_5_4.fsp"
#define GO_EXT_65 "instancias/go/tai100_5_5.fsp"
#define GO_EXT_66 "instancias/go/tai100_5_6.fsp"
#define GO_EXT_67 "instancias/go/tai100_5_7.fsp"
#define GO_EXT_68 "instancias/go/tai100_5_8.fsp"
#define GO_EXT_69 "instancias/go/tai100_5_9.fsp"

#define GO_EXT_70 "instancias/go/tai100_10_0.fsp"
#define GO_EXT_71 "instancias/go/tai100_10_1.fsp"
#define GO_EXT_72 "instancias/go/tai100_10_2.fsp"
#define GO_EXT_73 "instancias/go/tai100_10_3.fsp"
#define GO_EXT_74 "instancias/go/tai100_10_4.fsp"
#define GO_EXT_75 "instancias/go/tai100_10_5.fsp"
#define GO_EXT_76 "instancias/go/tai100_10_6.fsp"
#define GO_EXT_77 "instancias/go/tai100_10_7.fsp"
#define GO_EXT_78 "instancias/go/tai100_10_8.fsp"
#define GO_EXT_79 "instancias/go/tai100_10_9.fsp"

#define GO_EXT_80 "instancias/go/tai100_20_0.fsp"
#define GO_EXT_81 "instancias/go/tai100_20_1.fsp"
#define GO_EXT_82 "instancias/go/tai100_20_2.fsp"
#define GO_EXT_83 "instancias/go/tai100_20_3.fsp"
#define GO_EXT_84 "instancias/go/tai100_20_4.fsp"
#define GO_EXT_85 "instancias/go/tai100_20_5.fsp"
#define GO_EXT_86 "instancias/go/tai100_20_6.fsp"
#define GO_EXT_87 "instancias/go/tai100_20_7.fsp"
#define GO_EXT_88 "instancias/go/tai100_20_8.fsp"
#define GO_EXT_89 "instancias/go/tai100_20_9.fsp"

#define GO_EXT_90 "instancias/go/tai200_10_0.fsp"
#define GO_EXT_91 "instancias/go/tai200_10_1.fsp"
#define GO_EXT_92 "instancias/go/tai200_10_2.fsp"
#define GO_EXT_93 "instancias/go/tai200_10_3.fsp"
#define GO_EXT_94 "instancias/go/tai200_10_4.fsp"
#define GO_EXT_95 "instancias/go/tai200_10_5.fsp"
#define GO_EXT_96 "instancias/go/tai200_10_6.fsp"
#define GO_EXT_97 "instancias/go/tai200_10_7.fsp"
#define GO_EXT_98 "instancias/go/tai200_10_8.fsp"
#define GO_EXT_99 "instancias/go/tai200_10_9.fsp"

#define GO_EXT_100 "instancias/go/tai200_20_0.fsp"
#define GO_EXT_101 "instancias/go/tai200_20_1.fsp"
#define GO_EXT_102 "instancias/go/tai200_20_2.fsp"
#define GO_EXT_103 "instancias/go/tai200_20_3.fsp"
#define GO_EXT_104 "instancias/go/tai200_20_4.fsp"
#define GO_EXT_105 "instancias/go/tai200_20_5.fsp"
#define GO_EXT_106 "instancias/go/tai200_20_6.fsp"
#define GO_EXT_107 "instancias/go/tai200_20_7.fsp"
#define GO_EXT_108 "instancias/go/tai200_20_8.fsp"
#define GO_EXT_109 "instancias/go/tai200_20_9.fsp"

#define GO_EXT_110 "instancias/go/tai500_20_0.fsp"
#define GO_EXT_111 "instancias/go/tai500_20_1.fsp"
#define GO_EXT_112 "instancias/go/tai500_20_2.fsp"
#define GO_EXT_113 "instancias/go/tai500_20_3.fsp"
#define GO_EXT_114 "instancias/go/tai500_20_4.fsp"
#define GO_EXT_115 "instancias/go/tai500_20_5.fsp"
#define GO_EXT_116 "instancias/go/tai500_20_6.fsp"
#define GO_EXT_117 "instancias/go/tai500_20_7.fsp"
#define GO_EXT_118 "instancias/go/tai500_20_8.fsp"
#define GO_EXT_119 "instancias/go/tai500_20_9.fsp"

//instancias obtenidas de:
//https://github.com/tamy0612/JSPLIB
#define JSPLIB_EXT_0 "instancias/jsplib/ta01"
#define JSPLIB_EXT_1 "instancias/jsplib/ta02"
#define JSPLIB_EXT_2 "instancias/jsplib/ta03"
#define JSPLIB_EXT_3 "instancias/jsplib/ta04"
#define JSPLIB_EXT_4 "instancias/jsplib/ta05"
#define JSPLIB_EXT_5 "instancias/jsplib/ta06"
#define JSPLIB_EXT_6 "instancias/jsplib/ta07"
#define JSPLIB_EXT_7 "instancias/jsplib/ta08"
#define JSPLIB_EXT_8 "instancias/jsplib/ta09"
#define JSPLIB_EXT_9 "instancias/jsplib/ta10"

#define JSPLIB_EXT_10 "instancias/jsplib/ta11"
#define JSPLIB_EXT_11 "instancias/jsplib/ta12"
#define JSPLIB_EXT_12 "instancias/jsplib/ta13"
#define JSPLIB_EXT_13 "instancias/jsplib/ta14"
#define JSPLIB_EXT_14 "instancias/jsplib/ta15"
#define JSPLIB_EXT_15 "instancias/jsplib/ta16"
#define JSPLIB_EXT_16 "instancias/jsplib/ta17"
#define JSPLIB_EXT_17 "instancias/jsplib/ta18"
#define JSPLIB_EXT_18 "instancias/jsplib/ta19"
#define JSPLIB_EXT_19 "instancias/jsplib/ta20"

#define JSPLIB_EXT_20 "instancias/jsplib/ta21"
#define JSPLIB_EXT_21 "instancias/jsplib/ta22"
#define JSPLIB_EXT_22 "instancias/jsplib/ta23"
#define JSPLIB_EXT_23 "instancias/jsplib/ta24"
#define JSPLIB_EXT_24 "instancias/jsplib/ta25"
#define JSPLIB_EXT_25 "instancias/jsplib/ta26"
#define JSPLIB_EXT_26 "instancias/jsplib/ta27"
#define JSPLIB_EXT_27 "instancias/jsplib/ta28"
#define JSPLIB_EXT_28 "instancias/jsplib/ta29"
#define JSPLIB_EXT_29 "instancias/jsplib/ta30"

#define JSPLIB_EXT_30 "instancias/jsplib/ta31"
#define JSPLIB_EXT_31 "instancias/jsplib/ta32"
#define JSPLIB_EXT_32 "instancias/jsplib/ta33"
#define JSPLIB_EXT_33 "instancias/jsplib/ta34"
#define JSPLIB_EXT_34 "instancias/jsplib/ta35"
#define JSPLIB_EXT_35 "instancias/jsplib/ta36"
#define JSPLIB_EXT_36 "instancias/jsplib/ta37"
#define JSPLIB_EXT_37 "instancias/jsplib/ta38"
#define JSPLIB_EXT_38 "instancias/jsplib/ta39"
#define JSPLIB_EXT_39 "instancias/jsplib/ta40"

#define JSPLIB_EXT_40 "instancias/jsplib/ta41"
#define JSPLIB_EXT_41 "instancias/jsplib/ta42"
#define JSPLIB_EXT_42 "instancias/jsplib/ta43"
#define JSPLIB_EXT_43 "instancias/jsplib/ta44"
#define JSPLIB_EXT_44 "instancias/jsplib/ta45"
#define JSPLIB_EXT_45 "instancias/jsplib/ta46"
#define JSPLIB_EXT_46 "instancias/jsplib/ta47"
#define JSPLIB_EXT_47 "instancias/jsplib/ta48"
#define JSPLIB_EXT_48 "instancias/jsplib/ta49"
#define JSPLIB_EXT_49 "instancias/jsplib/ta50"

#define JSPLIB_EXT_50 "instancias/jsplib/ta51"
#define JSPLIB_EXT_51 "instancias/jsplib/ta52"
#define JSPLIB_EXT_52 "instancias/jsplib/ta53"
#define JSPLIB_EXT_53 "instancias/jsplib/ta54"
#define JSPLIB_EXT_54 "instancias/jsplib/ta55"
#define JSPLIB_EXT_55 "instancias/jsplib/ta56"
#define JSPLIB_EXT_56 "instancias/jsplib/ta57"
#define JSPLIB_EXT_57 "instancias/jsplib/ta58"
#define JSPLIB_EXT_58 "instancias/jsplib/ta59"
#define JSPLIB_EXT_59 "instancias/jsplib/ta60"

#define JSPLIB_EXT_60 "instancias/jsplib/ta61"
#define JSPLIB_EXT_61 "instancias/jsplib/ta62"
#define JSPLIB_EXT_62 "instancias/jsplib/ta63"
#define JSPLIB_EXT_63 "instancias/jsplib/ta64"
#define JSPLIB_EXT_64 "instancias/jsplib/ta65"
#define JSPLIB_EXT_65 "instancias/jsplib/ta66"
#define JSPLIB_EXT_66 "instancias/jsplib/ta67"
#define JSPLIB_EXT_67 "instancias/jsplib/ta68"
#define JSPLIB_EXT_68 "instancias/jsplib/ta69"
#define JSPLIB_EXT_69 "instancias/jsplib/ta70"

#define JSPLIB_EXT_70 "instancias/jsplib/ta71"
#define JSPLIB_EXT_71 "instancias/jsplib/ta72"
#define JSPLIB_EXT_72 "instancias/jsplib/ta73"
#define JSPLIB_EXT_73 "instancias/jsplib/ta74"
#define JSPLIB_EXT_74 "instancias/jsplib/ta75"
#define JSPLIB_EXT_75 "instancias/jsplib/ta76"
#define JSPLIB_EXT_76 "instancias/jsplib/ta77"
#define JSPLIB_EXT_77 "instancias/jsplib/ta78"
#define JSPLIB_EXT_78 "instancias/jsplib/ta79"
#define JSPLIB_EXT_79 "instancias/jsplib/ta80"

using namespace std;

#include <omp.h>

//funciones generales de pfs

//se ve un poco raro que esto se declare fuera de la clase, pero saqué que se hace así de aquí:
//https://en.cppreference.com/w/cpp/language/static.html
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

thread_local mt19937 pfs::rndm(random_device{}());

void pfs::cargar_instancia(int inst){
    switch(inst){
        case(-2):{tiempos=_cargar_instancia_go(GO_EXT_D_2);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(-1):{tiempos=_cargar_instancia_go(GO_EXT_D);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        //INSTANCIAS GO
        case(0):{tiempos=_cargar_instancia_go(GO_EXT_0);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(1):{tiempos=_cargar_instancia_go(GO_EXT_1);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(2):{tiempos=_cargar_instancia_go(GO_EXT_2);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(3):{tiempos=_cargar_instancia_go(GO_EXT_3);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(4):{tiempos=_cargar_instancia_go(GO_EXT_4);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(5):{tiempos=_cargar_instancia_go(GO_EXT_5);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(6):{tiempos=_cargar_instancia_go(GO_EXT_6);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(7):{tiempos=_cargar_instancia_go(GO_EXT_7);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(8):{tiempos=_cargar_instancia_go(GO_EXT_8);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(9):{tiempos=_cargar_instancia_go(GO_EXT_9);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(10):{tiempos=_cargar_instancia_go(GO_EXT_10);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(11):{tiempos=_cargar_instancia_go(GO_EXT_11);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(12):{tiempos=_cargar_instancia_go(GO_EXT_12);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(13):{tiempos=_cargar_instancia_go(GO_EXT_13);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(14):{tiempos=_cargar_instancia_go(GO_EXT_14);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(15):{tiempos=_cargar_instancia_go(GO_EXT_15);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(16):{tiempos=_cargar_instancia_go(GO_EXT_16);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(17):{tiempos=_cargar_instancia_go(GO_EXT_17);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(18):{tiempos=_cargar_instancia_go(GO_EXT_18);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(19):{tiempos=_cargar_instancia_go(GO_EXT_19);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(20):{tiempos=_cargar_instancia_go(GO_EXT_20);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(21):{tiempos=_cargar_instancia_go(GO_EXT_21);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(22):{tiempos=_cargar_instancia_go(GO_EXT_22);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(23):{tiempos=_cargar_instancia_go(GO_EXT_23);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(24):{tiempos=_cargar_instancia_go(GO_EXT_24);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(25):{tiempos=_cargar_instancia_go(GO_EXT_25);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(26):{tiempos=_cargar_instancia_go(GO_EXT_26);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(27):{tiempos=_cargar_instancia_go(GO_EXT_27);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(28):{tiempos=_cargar_instancia_go(GO_EXT_28);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(29):{tiempos=_cargar_instancia_go(GO_EXT_29);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(30):{tiempos=_cargar_instancia_go(GO_EXT_30);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(31):{tiempos=_cargar_instancia_go(GO_EXT_31);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(32):{tiempos=_cargar_instancia_go(GO_EXT_32);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(33):{tiempos=_cargar_instancia_go(GO_EXT_33);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(34):{tiempos=_cargar_instancia_go(GO_EXT_34);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(35):{tiempos=_cargar_instancia_go(GO_EXT_35);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(36):{tiempos=_cargar_instancia_go(GO_EXT_36);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(37):{tiempos=_cargar_instancia_go(GO_EXT_37);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(38):{tiempos=_cargar_instancia_go(GO_EXT_38);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(39):{tiempos=_cargar_instancia_go(GO_EXT_39);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(40):{tiempos=_cargar_instancia_go(GO_EXT_40);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(41):{tiempos=_cargar_instancia_go(GO_EXT_41);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(42):{tiempos=_cargar_instancia_go(GO_EXT_42);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(43):{tiempos=_cargar_instancia_go(GO_EXT_43);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(44):{tiempos=_cargar_instancia_go(GO_EXT_44);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(45):{tiempos=_cargar_instancia_go(GO_EXT_45);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(46):{tiempos=_cargar_instancia_go(GO_EXT_46);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(47):{tiempos=_cargar_instancia_go(GO_EXT_47);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(48):{tiempos=_cargar_instancia_go(GO_EXT_48);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(49):{tiempos=_cargar_instancia_go(GO_EXT_49);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(50):{tiempos=_cargar_instancia_go(GO_EXT_50);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(51):{tiempos=_cargar_instancia_go(GO_EXT_51);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(52):{tiempos=_cargar_instancia_go(GO_EXT_52);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(53):{tiempos=_cargar_instancia_go(GO_EXT_53);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(54):{tiempos=_cargar_instancia_go(GO_EXT_54);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(55):{tiempos=_cargar_instancia_go(GO_EXT_55);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(56):{tiempos=_cargar_instancia_go(GO_EXT_56);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(57):{tiempos=_cargar_instancia_go(GO_EXT_57);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(58):{tiempos=_cargar_instancia_go(GO_EXT_58);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(59):{tiempos=_cargar_instancia_go(GO_EXT_59);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(60):{tiempos=_cargar_instancia_go(GO_EXT_60);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(61):{tiempos=_cargar_instancia_go(GO_EXT_61);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(62):{tiempos=_cargar_instancia_go(GO_EXT_62);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(63):{tiempos=_cargar_instancia_go(GO_EXT_63);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(64):{tiempos=_cargar_instancia_go(GO_EXT_64);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(65):{tiempos=_cargar_instancia_go(GO_EXT_65);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(66):{tiempos=_cargar_instancia_go(GO_EXT_66);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(67):{tiempos=_cargar_instancia_go(GO_EXT_67);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(68):{tiempos=_cargar_instancia_go(GO_EXT_68);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(69):{tiempos=_cargar_instancia_go(GO_EXT_69);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(70):{tiempos=_cargar_instancia_go(GO_EXT_70);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(71):{tiempos=_cargar_instancia_go(GO_EXT_71);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(72):{tiempos=_cargar_instancia_go(GO_EXT_72);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(73):{tiempos=_cargar_instancia_go(GO_EXT_73);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(74):{tiempos=_cargar_instancia_go(GO_EXT_74);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(75):{tiempos=_cargar_instancia_go(GO_EXT_75);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(76):{tiempos=_cargar_instancia_go(GO_EXT_76);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(77):{tiempos=_cargar_instancia_go(GO_EXT_77);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(78):{tiempos=_cargar_instancia_go(GO_EXT_78);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(79):{tiempos=_cargar_instancia_go(GO_EXT_79);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(80):{tiempos=_cargar_instancia_go(GO_EXT_80);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(81):{tiempos=_cargar_instancia_go(GO_EXT_81);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(82):{tiempos=_cargar_instancia_go(GO_EXT_82);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(83):{tiempos=_cargar_instancia_go(GO_EXT_83);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(84):{tiempos=_cargar_instancia_go(GO_EXT_84);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(85):{tiempos=_cargar_instancia_go(GO_EXT_85);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(86):{tiempos=_cargar_instancia_go(GO_EXT_86);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(87):{tiempos=_cargar_instancia_go(GO_EXT_87);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(88):{tiempos=_cargar_instancia_go(GO_EXT_88);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(89):{tiempos=_cargar_instancia_go(GO_EXT_89);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(90):{tiempos=_cargar_instancia_go(GO_EXT_90);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(91):{tiempos=_cargar_instancia_go(GO_EXT_91);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(92):{tiempos=_cargar_instancia_go(GO_EXT_92);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(93):{tiempos=_cargar_instancia_go(GO_EXT_93);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(94):{tiempos=_cargar_instancia_go(GO_EXT_94);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(95):{tiempos=_cargar_instancia_go(GO_EXT_95);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(96):{tiempos=_cargar_instancia_go(GO_EXT_96);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(97):{tiempos=_cargar_instancia_go(GO_EXT_97);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(98):{tiempos=_cargar_instancia_go(GO_EXT_98);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(99):{tiempos=_cargar_instancia_go(GO_EXT_99);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(100):{tiempos=_cargar_instancia_go(GO_EXT_100);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(101):{tiempos=_cargar_instancia_go(GO_EXT_101);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(102):{tiempos=_cargar_instancia_go(GO_EXT_102);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(103):{tiempos=_cargar_instancia_go(GO_EXT_103);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(104):{tiempos=_cargar_instancia_go(GO_EXT_104);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(105):{tiempos=_cargar_instancia_go(GO_EXT_105);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(106):{tiempos=_cargar_instancia_go(GO_EXT_106);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(107):{tiempos=_cargar_instancia_go(GO_EXT_107);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(108):{tiempos=_cargar_instancia_go(GO_EXT_108);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(109):{tiempos=_cargar_instancia_go(GO_EXT_109);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(110):{tiempos=_cargar_instancia_go(GO_EXT_110);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(111):{tiempos=_cargar_instancia_go(GO_EXT_111);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(112):{tiempos=_cargar_instancia_go(GO_EXT_112);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(113):{tiempos=_cargar_instancia_go(GO_EXT_113);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(114):{tiempos=_cargar_instancia_go(GO_EXT_114);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(115):{tiempos=_cargar_instancia_go(GO_EXT_115);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(116):{tiempos=_cargar_instancia_go(GO_EXT_116);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(117):{tiempos=_cargar_instancia_go(GO_EXT_117);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(118):{tiempos=_cargar_instancia_go(GO_EXT_118);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(119):{tiempos=_cargar_instancia_go(GO_EXT_119);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}


        //INSTANCIAS JSPLIB
        case(200):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_0);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(201):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_1);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(202):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_2);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(203):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_3);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(204):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_4);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(205):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_5);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(206):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_6);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(207):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_7);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(208):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_8);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(209):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_9);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(210):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_10);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(211):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_11);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(212):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_12);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(213):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_13);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(214):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_14);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(215):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_15);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(216):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_16);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(217):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_17);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(218):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_18);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(219):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_19);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(220):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_20);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(221):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_21);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(222):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_22);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(223):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_23);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(224):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_24);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(225):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_25);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(226):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_26);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(227):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_27);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(228):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_28);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(229):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_29);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(230):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_30);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(231):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_31);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(232):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_32);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(233):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_33);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(234):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_34);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(235):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_35);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(236):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_36);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(237):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_37);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(238):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_38);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(239):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_39);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(240):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_40);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(241):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_41);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(242):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_42);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(243):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_43);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(244):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_44);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(245):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_45);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(246):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_46);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(247):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_47);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(248):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_48);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(249):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_49);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(250):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_50);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(251):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_51);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(252):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_52);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(253):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_53);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(254):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_54);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(255):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_55);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(256):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_56);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(257):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_57);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(258):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_58);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(259):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_59);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(260):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_60);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(261):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_61);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(262):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_62);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(263):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_63);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(264):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_64);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(265):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_65);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(266):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_66);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(267):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_67);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(268):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_68);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(269):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_69);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        case(270):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_70);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(271):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_71);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(272):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_72);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(273):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_73);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(274):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_74);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(275):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_75);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(276):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_76);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(277):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_77);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(278):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_78);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}
        case(279):{tiempos=_cargar_instancia_jsplib(JSPLIB_EXT_79);n_machines=tiempos.size();n_jobs=tiempos[0].size();poblacion.resize(0);break;}

        default:{cout<<"NO SE ENCONTRÓ LA INSTANCIA"<<endl;}
    }
}

vector<vector<int> > pfs::_cargar_instancia_jsplib(const char *archivo){
    //abriendo el archivo
    FILE *file=fopen(archivo, "r");

    //declarando variables
    int n_jobs, n_machines, indice, i, j, k, t, m;
    fscanf(file, "%d %d\n", &n_jobs, &n_machines);
    //se utiliza la sobrecarga de vector<T> name(n cant, obj T)
    vector<vector<int> > tiempos_(n_machines, vector<int>(n_jobs, 0));
    vector<vector<int> > maquinas(n_machines, vector<int>(n_jobs, 0));

    //escaneando todas las maquinas y tiempos
    for(t=0;t<n_machines;t++){
        for(m=0;m<n_jobs;m++){
            fscanf(file, "%d ", &maquinas[t][m]);
            fscanf(file, "%d ", &tiempos_[t][m]);
        }
    }
    
    //generando la matriz de tiempos
    vector<vector<int> > tiempos;
    vector<int> temp;
    
    for(i=0;i<n_machines;i++){
        for(j=0;j<n_jobs;j++){
            for(k=0;k<maquinas[i].size();k++) if(maquinas[i][k]==j) break;
            temp.push_back(tiempos_[i][k]);
        }
        tiempos.push_back(temp);
        temp.resize(0);
    }
    fclose(file);
    return tiempos;
}

vector<vector<int> > pfs::_cargar_instancia_go(const char *archivo){
    FILE *file=fopen(archivo, "r");
    if(file==NULL){
        cout<<"NO SE ENCONTRÓ EL ARCHIVO\n"<<endl;
        return {};
    }

    int n_jobs, n_machines, temp;
    fscanf(file, "number of jobs, number of machines, initial seed, upper bound and lower bound :\n %d %d ", &n_jobs, &n_machines);
    for(int i=0;i<3;i++) fscanf(file, "%d ", &temp);
    fscanf(file, "processing times :\n");
    vector<vector<int> > tiempos(n_machines, vector<int>(n_jobs, 0));

    for(int i=0;i<n_machines;i++){
        for(int j=0;j<n_jobs;j++){
            fscanf(file, "%d ", &tiempos[i][j]);
        }
    }
    fclose(file);

    return tiempos;
}

int pfs::makespan(int ind){
    //le quitamos el makespan que ya trae, en caso de ser necesario
    while(poblacion[ind].size()>n_jobs) poblacion[ind].pop_back();

    vector<vector<int> > c(n_machines+1, vector<int>(n_jobs+1, 0));
    for(int i=1;i<n_machines+1;i++){
        for(int j=1;j<n_jobs+1;j++){
            c[i][j]=max(c[i-1][j], c[i][j-1])+tiempos[poblacion[ind][i-1]][j-1];
        }
    }
    return c[n_machines][n_jobs];
}

int pfs::makespan(vector<int>& ind, bool verbose){
    //                   ┌creamos la matriz c que va a guardar todos lso tiempos secuencialmente
    //                   |                           ┌en la heurística NEH se van formando los individuos trabajo por trabajos, por lo que
    //                   |                           |no siempre los individuos van a ser del "tamaño completo"
    //                   |                           |también en caso de que el individuo ya traiga el makespan, solo tomamos en cuenta 
    //                   |                           |máximo la cantidad de trabajos que hay
    vector<vector<int> > c(n_machines+1, vector<int>(min(int(ind.size()), n_jobs)+1, 0));
    if(verbose) cout<<min(int(ind.size()), n_jobs+1)<<endl;

    //iteramos sobre todas las máquinas
    for(int i=1;i<n_machines+1;i++){
        //iteramos sobre todos los trabajos del individuo
        for(int j=1;j<min(int(ind.size()), n_jobs)+1;j++){
            //guardamos el tiempo que tomó
            c[i][j]=max(c[i-1][j], c[i][j-1])+tiempos[i-1][ind[j-1]];
        }
    }
    //tomamos el último elemento de c
    return c[n_machines][min(int(ind.size()), n_jobs)];
}

vector<vector<int> > pfs::makespan_incremental(vector<int>& ind, bool verbose){
    //                   ┌creamos la matriz c que va a guardar todos lso tiempos secuencialmente
    //                   |                           ┌en la heurística NEH se van formando los individuos trabajo por trabajos, por lo que
    //                   |                           |no siempre los individuos van a ser del "tamaño completo"
    //                   |                           |también en caso de que el individuo ya traiga el makespan, solo tomamos en cuenta 
    //                   |                           |máximo la cantidad de trabajos que hay
    vector<vector<int> > c(n_machines+1, vector<int>(min(int(ind.size()), n_jobs)+1, 0));
    if(verbose) cout<<min(int(ind.size()), n_jobs+1)<<endl;

    //iteramos sobre todas las máquinas
    for(int i=1;i<n_machines+1;i++){
        //iteramos sobre todos los trabajos del individuo
        for(int j=1;j<min(int(ind.size()), n_jobs)+1;j++){
            //guardamos el tiempo que tomó
            c[i][j]=max(c[i-1][j], c[i][j-1])+tiempos[i-1][ind[j-1]];
        }
    }

    return c;
}

int pfs::makespan_incremental(vector<int>& perm, int job, int pos, vector<vector<int> >& c){
    //hacemos una copia con espacio extra de c, para poder calcular el makespan
    int n=c.size(), m=c[0].size(), i, j;
    vector<vector<int> > c_(n, vector<int>(m+1, 0));
    for(i=0;i<n;i++) memcpy(c_[i].data(), c[i].data(), m*sizeof(int));
    
    //rellenamos la fila de la posición que nos interesa
    for(i=1;i<n_machines+1;i++){
        c_[i][pos+1]=max(c_[i-1][pos+1], c_[i][pos])+tiempos[i-1][job];
    }
    
    //rellenamos el resto
    for(i=1;i<n_machines+1;i++){
        for(j=pos+2;j<min(int(perm.size()+1), n_jobs)+1;j++){
            c_[i][j]=max(c_[i-1][j], c_[i][j-1])+tiempos[i-1][perm[j-2]];
        }
    }
    
    //regresamos el ultimo valor
    /*
    for(auto a:c_){
        for(auto b:a){
            cout<<b<<", ";
        }
        cout<<endl;
    }
    cout<<c_[c_.size()-1][c_[0].size()-1]<<endl;*/

    return c_[c_.size()-1][c_[0].size()-1];
}

vector<int> pfs::permutacion_aleatoria(){
    vector<int> res(n_jobs);
    for(int i=0;i<n_jobs;i++) res[i]=i;

    //                        ┌número arbitrariamente grande
    int veces=rand_int(rndm)%(3*(n_jobs)+poblacion.size()), a, b;

    for(int i=0;i<veces;i++){
        a=rand_int(rndm)%n_jobs;
        while((b=rand_int(rndm)%n_jobs)==a) b=rand_int(rndm)%n_jobs;
        res[a]=res[a]^res[b];
        res[b]=res[a]^res[b];
        res[a]=res[a]^res[b];
    }
    return res;
}

void pfs::generar_poblacion_aleatoria(){
    poblacion.resize(0);
    //generamos los individuos de manera aleatoria
    for(int i=0;i<n_inds;i++) poblacion.push_back(this->permutacion_aleatoria());

    //les damos su makespan
    for(int i=0;i<n_inds;i++) poblacion[i].push_back(this->makespan(poblacion[i]));

    //lo ordenamos con respecto del makespan
    poblacion=b_u_merge_sort<int>(poblacion, poblacion[0].size()-1);
}

vector<vector<int> > pfs::generar_poblacion_aleatoria(int n){
    vector<vector<int> > pob;

    for(int i=0;i<n;i++) pob.push_back(this->permutacion_aleatoria());

    //les damos su makespan
    for(int i=0;i<n;i++) pob[i].push_back(this->makespan(pob[i]));

    //lo ordenamos con respecto del makespan
    pob=b_u_merge_sort<int>(pob, pob[0].size()-1);

    return pob;
}

void pfs::ver_poblacion(FILE *file){
    int i, j;
    if(file==NULL){
        for(i=0;i<poblacion.size();i++){
            cout<<"[";
            for(j=0;j<poblacion[i].size()-1;j++){
                cout<<poblacion[i][j]<<", ";
            }
            cout<<poblacion[i][j]<<"]"<<endl;
        }
    }
    //hello there
    else{
        cout<<"-----------------------"<<poblacion.size()<<"-----------------------"<<endl;
        for(i=0;i<poblacion.size();i++){
            for(j=0;j<poblacion[i].size()-1;j++){
                fprintf(file, "%d, ", poblacion[i][j]);
            }
            fprintf(file, "%d\n", poblacion[i][j]);
        }
    }
}

vector<vector<int> > pfs::_op_resta(vector<int> ind_1, vector<int> ind_2, bool verbose){
    vector<vector<int> > sec;
    vector<int> ind_prueba=ind_2;
    if(verbose) cout<<"RESTA"<<endl;
    for(int i=1;i<n_jobs;i++){
        if(verbose) cout<<"DIFF - "<<ind_1[i]<<", "<<ind_prueba[i]<<endl;
        if(ind_1[i]!=ind_prueba[i]){
            if(verbose) cout<<"SI HAY DIFERENCIA"<<endl;
            for(int j=i-1;j<n_jobs;j++){
                if(verbose) cout<<i<<", "<<j<<endl;
                if(ind_prueba[j]==ind_1[i]){
                    if(verbose) cout<<"IGUAL - "<<ind_prueba[j]<<", "<<ind_1[i]<<endl;
                    ind_prueba[i]=ind_prueba[i]^ind_prueba[j];
                    ind_prueba[j]=ind_prueba[i]^ind_prueba[j];
                    ind_prueba[i]=ind_prueba[i]^ind_prueba[j];
                    sec.push_back(vector<int>{i, j});
                    break;
                }
            }
        }
        if(verbose){
            cout<<"res - "<<endl;
            for(int i=0;i<ind_1.size();i++){
                cout<<ind_1[i]<<", ";
            }
            cout<<endl;
            for(int i=0;i<ind_prueba.size();i++){
                cout<<ind_prueba[i]<<", ";
            }
            cout<<endl;
            cout<<"------------------------"<<endl;
        }
    }

    return sec;
}

vector<vector<int> > pfs::op_resta(int ind_1, int ind_2, bool verbose){return this->_op_resta(poblacion[ind_1], poblacion[ind_2], verbose);}

vector<vector<int> > pfs::op_resta(vector<int> ind_1, int ind_2, bool verbose){return this->_op_resta(ind_1, poblacion[ind_2], verbose);}

vector<vector<int> > pfs::op_resta(int ind_1, vector<int> ind_2, bool verbose){return this->_op_resta(poblacion[ind_1], ind_2, verbose);}

vector<vector<int> > pfs::op_resta(vector<int> ind_1, vector<int> ind_2, bool verbose){return this->_op_resta(ind_1, ind_2, verbose);}

vector<int> pfs::_op_suma(vector<vector<int> > sec, vector<int> ind, double frac){
    //acotando
    if(frac>1.0) frac=1.0;
    else if(frac<0.0) frac=0.0;

    //calculando la cantidad de cambios
    int cant=frac*(int)sec.size();
    if(cant<0) cant=0;
    else if(cant>(int)sec.size()) cant=(int)sec.size();

    //haciendo los cambios
    int count=0;
    vector<int> res=ind;
    for(auto cambio:sec){
        if(count==cant) break;
        swap(res[cambio[0]], res[cambio[1]]);
        count++;
    }

    return (valido(res))?(res):(ind);
}

vector<int> pfs::op_suma(vector<vector<int> > sec, vector<int> ind, double frac, bool verbose){return this->_op_suma(sec, ind, frac);}

vector<int> pfs::op_suma(vector<vector<int> > sec, int ind, double frac, bool verbose){return this->_op_suma(sec, poblacion[ind], frac);}

vector<int> pfs::faltantes(vector<int> ind){
    vector<int> faltantes{};
    for(int i=0;i<n_jobs;i++) if(!contiene<int>(ind, i)) faltantes.push_back(i);
    return faltantes;
}

vector<int> pfs::calcular_diferencias(){
    vector<int> res;
    for(int i=0;i<n_inds-1;i++){
        res.push_back(op_resta(i, i+1).size());
    }
    return res;
}

bool pfs::valido(vector<int> ind){
    vector<int> base;
    if(ind.size()>n_jobs+1||ind.size()<n_jobs) return false;

    for(int i=0;i<n_jobs;i++) if(!contiene(ind, i)) return false;

    return true;
}

vector<vector<int> > pfs::NEH(int cant, FILE *file){
    //acotamos la cantidad
    if(cant<0) return {};
    if(cant>n_jobs) cant=n_jobs;

    //creamos un orden descendente de los tiempos de cada trabajo 
    vector<vector<int> > sumas;

    for(int i=0;i<n_jobs;i++){
        vector<int> col_tiempos(n_machines);
        for(int j=0;j<n_machines;j++){
            col_tiempos.push_back(tiempos[j][i]);
        }
        sumas.push_back(vector<int>{i, suma<int>(col_tiempos)});
    }

    vector<vector<int>> ordenados=b_u_merge_sort<int>(sumas, 1, true);
    vector<int> orden;
    for(auto _:ordenados){
        orden.push_back(_[0]);
    }
    

    //construimos la solución de manera incremental con inserciones greedy
    vector<int> seq;

    int i=0;
    for(int job:orden){
        vector<int> mejor_secuencia;
        int mejor_makespan=10000000;

        //probamos todas las posiciones para ver dónde lo pones (el trabajo actual)
        vector<vector<int> > posibles=posibilidades<int>(seq, job);
        
        //checas cuál de las posibilidades es la mejor
        for(auto posibilidad:posibles){
            //comparando
            int mk=makespan(posibilidad);
            if(mk<mejor_makespan){
                mejor_secuencia=posibilidad;
                mejor_makespan=mk;
            }
        }

        //actualización
        seq=mejor_secuencia;
        if(seq.size()>=cant){
            break;
        }
    }
    
    
    vector<int> faltan=faltantes(seq);
    if(faltan.size()>8){
        if(file!=nullptr) fprintf(file, "DEMASIADAS COMBINACIONES, SALIENDO\n");
        else cout<<"DEMASIADAS COMBINACIONES, SALIENDO\n"<<faltan.size()<<endl;
        return {};
    }

    vector<vector<int> > perms=combinatoria<int>(faltan);

    vector<vector<int> > res;
    for(auto _:perms){
        vector<int> temp=seq;
        temp.insert(temp.end(), _.begin(), _.end());
        temp.push_back(makespan(temp));
        if(this->valido(temp)) res.push_back(temp);
    }

    vector<vector<int> > r=b_u_merge_sort<int>(res, res[0].size()-1);
    return r;
}

void pfs::agregar_individuos(int n){
    if(n>0){
        cout<<"MAYORR"<<endl;
        for(int i=0;i<n;i++){
            vector<int> temp=this->permutacion_aleatoria();
            temp.push_back(this->makespan(temp));
            poblacion.push_back(temp);
        }
        n_inds=poblacion.size();
    }
    else if(n<0){
        cout<<"MENORRR"<<endl;
        int cant=poblacion.size();
        for(int i=0;i<n;i++) poblacion.erase(poblacion.begin()+cant-i);
        n_inds=poblacion.size();
    }
}

double pfs::temperatura(int iter, double theta){
    return exp(-iter*theta);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
        cout<<"-------"<<iter_<<endl;
    }
    
    this->ver_poblacion(file);
    
    return mejor;
}

void experimento(string name, string carpeta, int verbose, bool archivo, bool verbose_){
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

    fclose(resumen);
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

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//funciones morais

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

    fclose(resumen);
}

void experimento_DSADE_PFS_2(string name, string carpeta, int verbose, bool archivo, bool verbose_){
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

    fclose(resumen);
}

void experimento_PGS_EDA(string name, string carpeta, int verbose, bool archivo, bool verbose_){
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

    fclose(resumen);
}

void experimento_DDE_RLS(string name, string carpeta, int verbose, bool archivo, bool verbose_){
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

    fclose(resumen);
}

//gatito