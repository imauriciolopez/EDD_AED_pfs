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

//definiciones de dónde están las carpetas y demás
//demo (5 trabajos 5 máquinas)
#define GO_EXT_D_2 "../instancias/go/tai_demo_2.fsp"
//demo (20 trabajos 10 máquinas)
#define GO_EXT_D "../instancias/go/tai_demo.fsp"

//instancias obtenidas de:
//https://github.com/chneau/go-taillard
#define GO_EXT_0  "../instancias/go/tai20_5_0.fsp"
#define GO_EXT_1  "../instancias/go/tai20_5_1.fsp"
#define GO_EXT_2  "../instancias/go/tai20_5_2.fsp"
#define GO_EXT_3  "../instancias/go/tai20_5_3.fsp"
#define GO_EXT_4  "../instancias/go/tai20_5_4.fsp"
#define GO_EXT_5  "../instancias/go/tai20_5_5.fsp"
#define GO_EXT_6  "../instancias/go/tai20_5_6.fsp"
#define GO_EXT_7  "../instancias/go/tai20_5_7.fsp"
#define GO_EXT_8  "../instancias/go/tai20_5_8.fsp"
#define GO_EXT_9  "../instancias/go/tai20_5_9.fsp"

#define GO_EXT_10 "../instancias/go/tai20_10_0.fsp"
#define GO_EXT_11 "../instancias/go/tai20_10_1.fsp"
#define GO_EXT_12 "../instancias/go/tai20_10_2.fsp"
#define GO_EXT_13 "../instancias/go/tai20_10_3.fsp"
#define GO_EXT_14 "../instancias/go/tai20_10_4.fsp"
#define GO_EXT_15 "../instancias/go/tai20_10_5.fsp"
#define GO_EXT_16 "../instancias/go/tai20_10_6.fsp"
#define GO_EXT_17 "../instancias/go/tai20_10_7.fsp"
#define GO_EXT_18 "../instancias/go/tai20_10_8.fsp"
#define GO_EXT_19 "../instancias/go/tai20_10_9.fsp"

#define GO_EXT_20 "../instancias/go/tai20_20_0.fsp"
#define GO_EXT_21 "../instancias/go/tai20_20_1.fsp"
#define GO_EXT_22 "../instancias/go/tai20_20_2.fsp"
#define GO_EXT_23 "../instancias/go/tai20_20_3.fsp"
#define GO_EXT_24 "../instancias/go/tai20_20_4.fsp"
#define GO_EXT_25 "../instancias/go/tai20_20_5.fsp"
#define GO_EXT_26 "../instancias/go/tai20_20_6.fsp"
#define GO_EXT_27 "../instancias/go/tai20_20_7.fsp"
#define GO_EXT_28 "../instancias/go/tai20_20_8.fsp"
#define GO_EXT_29 "../instancias/go/tai20_20_9.fsp"

#define GO_EXT_30 "../instancias/go/tai50_5_0.fsp"
#define GO_EXT_31 "../instancias/go/tai50_5_1.fsp"
#define GO_EXT_32 "../instancias/go/tai50_5_2.fsp"
#define GO_EXT_33 "../instancias/go/tai50_5_3.fsp"
#define GO_EXT_34 "../instancias/go/tai50_5_4.fsp"
#define GO_EXT_35 "../instancias/go/tai50_5_5.fsp"
#define GO_EXT_36 "../instancias/go/tai50_5_6.fsp"
#define GO_EXT_37 "../instancias/go/tai50_5_7.fsp"
#define GO_EXT_38 "../instancias/go/tai50_5_8.fsp"
#define GO_EXT_39 "../instancias/go/tai50_5_9.fsp"

#define GO_EXT_40 "../instancias/go/tai50_10_0.fsp"
#define GO_EXT_41 "../instancias/go/tai50_10_1.fsp"
#define GO_EXT_42 "../instancias/go/tai50_10_2.fsp"
#define GO_EXT_43 "../instancias/go/tai50_10_3.fsp"
#define GO_EXT_44 "../instancias/go/tai50_10_4.fsp"
#define GO_EXT_45 "../instancias/go/tai50_10_5.fsp"
#define GO_EXT_46 "../instancias/go/tai50_10_6.fsp"
#define GO_EXT_47 "../instancias/go/tai50_10_7.fsp"
#define GO_EXT_48 "../instancias/go/tai50_10_8.fsp"
#define GO_EXT_49 "../instancias/go/tai50_10_9.fsp"

#define GO_EXT_50 "../instancias/go/tai50_20_0.fsp"
#define GO_EXT_51 "../instancias/go/tai50_20_1.fsp"
#define GO_EXT_52 "../instancias/go/tai50_20_2.fsp"
#define GO_EXT_53 "../instancias/go/tai50_20_3.fsp"
#define GO_EXT_54 "../instancias/go/tai50_20_4.fsp"
#define GO_EXT_55 "../instancias/go/tai50_20_5.fsp"
#define GO_EXT_56 "../instancias/go/tai50_20_6.fsp"
#define GO_EXT_57 "../instancias/go/tai50_20_7.fsp"
#define GO_EXT_58 "../instancias/go/tai50_20_8.fsp"
#define GO_EXT_59 "../instancias/go/tai50_20_9.fsp"

#define GO_EXT_60 "../instancias/go/tai100_5_0.fsp"
#define GO_EXT_61 "../instancias/go/tai100_5_1.fsp"
#define GO_EXT_62 "../instancias/go/tai100_5_2.fsp"
#define GO_EXT_63 "../instancias/go/tai100_5_3.fsp"
#define GO_EXT_64 "../instancias/go/tai100_5_4.fsp"
#define GO_EXT_65 "../instancias/go/tai100_5_5.fsp"
#define GO_EXT_66 "../instancias/go/tai100_5_6.fsp"
#define GO_EXT_67 "../instancias/go/tai100_5_7.fsp"
#define GO_EXT_68 "../instancias/go/tai100_5_8.fsp"
#define GO_EXT_69 "../instancias/go/tai100_5_9.fsp"

#define GO_EXT_70 "../instancias/go/tai100_10_0.fsp"
#define GO_EXT_71 "../instancias/go/tai100_10_1.fsp"
#define GO_EXT_72 "../instancias/go/tai100_10_2.fsp"
#define GO_EXT_73 "../instancias/go/tai100_10_3.fsp"
#define GO_EXT_74 "../instancias/go/tai100_10_4.fsp"
#define GO_EXT_75 "../instancias/go/tai100_10_5.fsp"
#define GO_EXT_76 "../instancias/go/tai100_10_6.fsp"
#define GO_EXT_77 "../instancias/go/tai100_10_7.fsp"
#define GO_EXT_78 "../instancias/go/tai100_10_8.fsp"
#define GO_EXT_79 "../instancias/go/tai100_10_9.fsp"

#define GO_EXT_80 "../instancias/go/tai100_20_0.fsp"
#define GO_EXT_81 "../instancias/go/tai100_20_1.fsp"
#define GO_EXT_82 "../instancias/go/tai100_20_2.fsp"
#define GO_EXT_83 "../instancias/go/tai100_20_3.fsp"
#define GO_EXT_84 "../instancias/go/tai100_20_4.fsp"
#define GO_EXT_85 "../instancias/go/tai100_20_5.fsp"
#define GO_EXT_86 "../instancias/go/tai100_20_6.fsp"
#define GO_EXT_87 "../instancias/go/tai100_20_7.fsp"
#define GO_EXT_88 "../instancias/go/tai100_20_8.fsp"
#define GO_EXT_89 "../instancias/go/tai100_20_9.fsp"

#define GO_EXT_90 "../instancias/go/tai200_10_0.fsp"
#define GO_EXT_91 "../instancias/go/tai200_10_1.fsp"
#define GO_EXT_92 "../instancias/go/tai200_10_2.fsp"
#define GO_EXT_93 "../instancias/go/tai200_10_3.fsp"
#define GO_EXT_94 "../instancias/go/tai200_10_4.fsp"
#define GO_EXT_95 "../instancias/go/tai200_10_5.fsp"
#define GO_EXT_96 "../instancias/go/tai200_10_6.fsp"
#define GO_EXT_97 "../instancias/go/tai200_10_7.fsp"
#define GO_EXT_98 "../instancias/go/tai200_10_8.fsp"
#define GO_EXT_99 "../instancias/go/tai200_10_9.fsp"

#define GO_EXT_100 "../instancias/go/tai200_20_0.fsp"
#define GO_EXT_101 "../instancias/go/tai200_20_1.fsp"
#define GO_EXT_102 "../instancias/go/tai200_20_2.fsp"
#define GO_EXT_103 "../instancias/go/tai200_20_3.fsp"
#define GO_EXT_104 "../instancias/go/tai200_20_4.fsp"
#define GO_EXT_105 "../instancias/go/tai200_20_5.fsp"
#define GO_EXT_106 "../instancias/go/tai200_20_6.fsp"
#define GO_EXT_107 "../instancias/go/tai200_20_7.fsp"
#define GO_EXT_108 "../instancias/go/tai200_20_8.fsp"
#define GO_EXT_109 "../instancias/go/tai200_20_9.fsp"

#define GO_EXT_110 "../instancias/go/tai500_20_0.fsp"
#define GO_EXT_111 "../instancias/go/tai500_20_1.fsp"
#define GO_EXT_112 "../instancias/go/tai500_20_2.fsp"
#define GO_EXT_113 "../instancias/go/tai500_20_3.fsp"
#define GO_EXT_114 "../instancias/go/tai500_20_4.fsp"
#define GO_EXT_115 "../instancias/go/tai500_20_5.fsp"
#define GO_EXT_116 "../instancias/go/tai500_20_6.fsp"
#define GO_EXT_117 "../instancias/go/tai500_20_7.fsp"
#define GO_EXT_118 "../instancias/go/tai500_20_8.fsp"
#define GO_EXT_119 "../instancias/go/tai500_20_9.fsp"

//instancias obtenidas de:
//https://github.com/tamy0612/JSPLIB
#define JSPLIB_EXT_0 "../instancias/jsplib/ta01"
#define JSPLIB_EXT_1 "../instancias/jsplib/ta02"
#define JSPLIB_EXT_2 "../instancias/jsplib/ta03"
#define JSPLIB_EXT_3 "../instancias/jsplib/ta04"
#define JSPLIB_EXT_4 "../instancias/jsplib/ta05"
#define JSPLIB_EXT_5 "../instancias/jsplib/ta06"
#define JSPLIB_EXT_6 "../instancias/jsplib/ta07"
#define JSPLIB_EXT_7 "../instancias/jsplib/ta08"
#define JSPLIB_EXT_8 "../instancias/jsplib/ta09"
#define JSPLIB_EXT_9 "../instancias/jsplib/ta10"

#define JSPLIB_EXT_10 "../instancias/jsplib/ta11"
#define JSPLIB_EXT_11 "../instancias/jsplib/ta12"
#define JSPLIB_EXT_12 "../instancias/jsplib/ta13"
#define JSPLIB_EXT_13 "../instancias/jsplib/ta14"
#define JSPLIB_EXT_14 "../instancias/jsplib/ta15"
#define JSPLIB_EXT_15 "../instancias/jsplib/ta16"
#define JSPLIB_EXT_16 "../instancias/jsplib/ta17"
#define JSPLIB_EXT_17 "../instancias/jsplib/ta18"
#define JSPLIB_EXT_18 "../instancias/jsplib/ta19"
#define JSPLIB_EXT_19 "../instancias/jsplib/ta20"

#define JSPLIB_EXT_20 "../instancias/jsplib/ta21"
#define JSPLIB_EXT_21 "../instancias/jsplib/ta22"
#define JSPLIB_EXT_22 "../instancias/jsplib/ta23"
#define JSPLIB_EXT_23 "../instancias/jsplib/ta24"
#define JSPLIB_EXT_24 "../instancias/jsplib/ta25"
#define JSPLIB_EXT_25 "../instancias/jsplib/ta26"
#define JSPLIB_EXT_26 "../instancias/jsplib/ta27"
#define JSPLIB_EXT_27 "../instancias/jsplib/ta28"
#define JSPLIB_EXT_28 "../instancias/jsplib/ta29"
#define JSPLIB_EXT_29 "../instancias/jsplib/ta30"

#define JSPLIB_EXT_30 "../instancias/jsplib/ta31"
#define JSPLIB_EXT_31 "../instancias/jsplib/ta32"
#define JSPLIB_EXT_32 "../instancias/jsplib/ta33"
#define JSPLIB_EXT_33 "../instancias/jsplib/ta34"
#define JSPLIB_EXT_34 "../instancias/jsplib/ta35"
#define JSPLIB_EXT_35 "../instancias/jsplib/ta36"
#define JSPLIB_EXT_36 "../instancias/jsplib/ta37"
#define JSPLIB_EXT_37 "../instancias/jsplib/ta38"
#define JSPLIB_EXT_38 "../instancias/jsplib/ta39"
#define JSPLIB_EXT_39 "../instancias/jsplib/ta40"

#define JSPLIB_EXT_40 "../instancias/jsplib/ta41"
#define JSPLIB_EXT_41 "../instancias/jsplib/ta42"
#define JSPLIB_EXT_42 "../instancias/jsplib/ta43"
#define JSPLIB_EXT_43 "../instancias/jsplib/ta44"
#define JSPLIB_EXT_44 "../instancias/jsplib/ta45"
#define JSPLIB_EXT_45 "../instancias/jsplib/ta46"
#define JSPLIB_EXT_46 "../instancias/jsplib/ta47"
#define JSPLIB_EXT_47 "../instancias/jsplib/ta48"
#define JSPLIB_EXT_48 "../instancias/jsplib/ta49"
#define JSPLIB_EXT_49 "../instancias/jsplib/ta50"

#define JSPLIB_EXT_50 "../instancias/jsplib/ta51"
#define JSPLIB_EXT_51 "../instancias/jsplib/ta52"
#define JSPLIB_EXT_52 "../instancias/jsplib/ta53"
#define JSPLIB_EXT_53 "../instancias/jsplib/ta54"
#define JSPLIB_EXT_54 "../instancias/jsplib/ta55"
#define JSPLIB_EXT_55 "../instancias/jsplib/ta56"
#define JSPLIB_EXT_56 "../instancias/jsplib/ta57"
#define JSPLIB_EXT_57 "../instancias/jsplib/ta58"
#define JSPLIB_EXT_58 "../instancias/jsplib/ta59"
#define JSPLIB_EXT_59 "../instancias/jsplib/ta60"

#define JSPLIB_EXT_60 "../instancias/jsplib/ta61"
#define JSPLIB_EXT_61 "../instancias/jsplib/ta62"
#define JSPLIB_EXT_62 "../instancias/jsplib/ta63"
#define JSPLIB_EXT_63 "../instancias/jsplib/ta64"
#define JSPLIB_EXT_64 "../instancias/jsplib/ta65"
#define JSPLIB_EXT_65 "../instancias/jsplib/ta66"
#define JSPLIB_EXT_66 "../instancias/jsplib/ta67"
#define JSPLIB_EXT_67 "../instancias/jsplib/ta68"
#define JSPLIB_EXT_68 "../instancias/jsplib/ta69"
#define JSPLIB_EXT_69 "../instancias/jsplib/ta70"

#define JSPLIB_EXT_70 "../instancias/jsplib/ta71"
#define JSPLIB_EXT_71 "../instancias/jsplib/ta72"
#define JSPLIB_EXT_72 "../instancias/jsplib/ta73"
#define JSPLIB_EXT_73 "../instancias/jsplib/ta74"
#define JSPLIB_EXT_74 "../instancias/jsplib/ta75"
#define JSPLIB_EXT_75 "../instancias/jsplib/ta76"
#define JSPLIB_EXT_76 "../instancias/jsplib/ta77"
#define JSPLIB_EXT_77 "../instancias/jsplib/ta78"
#define JSPLIB_EXT_78 "../instancias/jsplib/ta79"
#define JSPLIB_EXT_79 "../instancias/jsplib/ta80"

using namespace std;

#include <omp.h>

//funciones generales de pfs

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

