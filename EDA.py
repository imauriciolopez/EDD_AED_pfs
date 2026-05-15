#cargar librerías y ubicaciones de archivos
import random
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys
import time
import math as mt
import itertools

#definiciones de dónde están las carpetas y demás
#demo (5 trabajos 5 máquinas)
dict_ubicaciones={
"go_EXT_D_2":"./instancias/go/tai_demo_2.fsp",
#demo (20 trabajos 10 máquinas)
"go_EXT_D":"./instancias/go/tai_demo.fsp",

#instancias obtenidas de:
#https:#github.com/chneau/go-taillard
"go_EXT_0":"./instancias/go/tai20_5_0.fsp",
"go_EXT_1":"./instancias/go/tai20_5_1.fsp",
"go_EXT_2":"./instancias/go/tai20_5_2.fsp",
"go_EXT_3":"./instancias/go/tai20_5_3.fsp",
"go_EXT_4":"./instancias/go/tai20_5_4.fsp",
"go_EXT_5":"./instancias/go/tai20_5_5.fsp",
"go_EXT_6":"./instancias/go/tai20_5_6.fsp",
"go_EXT_7":"./instancias/go/tai20_5_7.fsp",
"go_EXT_8":"./instancias/go/tai20_5_8.fsp",
"go_EXT_9":"./instancias/go/tai20_5_9.fsp",

"go_EXT_10":"./instancias/go/tai20_10_0.fsp",
"go_EXT_11":"./instancias/go/tai20_10_1.fsp",
"go_EXT_12":"./instancias/go/tai20_10_2.fsp",
"go_EXT_13":"./instancias/go/tai20_10_3.fsp",
"go_EXT_14":"./instancias/go/tai20_10_4.fsp",
"go_EXT_15":"./instancias/go/tai20_10_5.fsp",
"go_EXT_16":"./instancias/go/tai20_10_6.fsp",
"go_EXT_17":"./instancias/go/tai20_10_7.fsp",
"go_EXT_18":"./instancias/go/tai20_10_8.fsp",
"go_EXT_19":"./instancias/go/tai20_10_9.fsp",

"go_EXT_20":"./instancias/go/tai20_20_0.fsp",
"go_EXT_21":"./instancias/go/tai20_20_1.fsp",
"go_EXT_22":"./instancias/go/tai20_20_2.fsp",
"go_EXT_23":"./instancias/go/tai20_20_3.fsp",
"go_EXT_24":"./instancias/go/tai20_20_4.fsp",
"go_EXT_25":"./instancias/go/tai20_20_5.fsp",
"go_EXT_26":"./instancias/go/tai20_20_6.fsp",
"go_EXT_27":"./instancias/go/tai20_20_7.fsp",
"go_EXT_28":"./instancias/go/tai20_20_8.fsp",
"go_EXT_29":"./instancias/go/tai20_20_9.fsp",

"go_EXT_30":"./instancias/go/tai50_5_0.fsp",
"go_EXT_31":"./instancias/go/tai50_5_1.fsp",
"go_EXT_32":"./instancias/go/tai50_5_2.fsp",
"go_EXT_33":"./instancias/go/tai50_5_3.fsp",
"go_EXT_34":"./instancias/go/tai50_5_4.fsp",
"go_EXT_35":"./instancias/go/tai50_5_5.fsp",
"go_EXT_36":"./instancias/go/tai50_5_6.fsp",
"go_EXT_37":"./instancias/go/tai50_5_7.fsp",
"go_EXT_38":"./instancias/go/tai50_5_8.fsp",
"go_EXT_39":"./instancias/go/tai50_5_9.fsp",

"go_EXT_40":"./instancias/go/tai50_10_0.fsp",
"go_EXT_41":"./instancias/go/tai50_10_1.fsp",
"go_EXT_42":"./instancias/go/tai50_10_2.fsp",
"go_EXT_43":"./instancias/go/tai50_10_3.fsp",
"go_EXT_44":"./instancias/go/tai50_10_4.fsp",
"go_EXT_45":"./instancias/go/tai50_10_5.fsp",
"go_EXT_46":"./instancias/go/tai50_10_6.fsp",
"go_EXT_47":"./instancias/go/tai50_10_7.fsp",
"go_EXT_48":"./instancias/go/tai50_10_8.fsp",
"go_EXT_49":"./instancias/go/tai50_10_9.fsp",

"go_EXT_50":"./instancias/go/tai50_20_0.fsp",
"go_EXT_51":"./instancias/go/tai50_20_1.fsp",
"go_EXT_52":"./instancias/go/tai50_20_2.fsp",
"go_EXT_53":"./instancias/go/tai50_20_3.fsp",
"go_EXT_54":"./instancias/go/tai50_20_4.fsp",
"go_EXT_55":"./instancias/go/tai50_20_5.fsp",
"go_EXT_56":"./instancias/go/tai50_20_6.fsp",
"go_EXT_57":"./instancias/go/tai50_20_7.fsp",
"go_EXT_58":"./instancias/go/tai50_20_8.fsp",
"go_EXT_59":"./instancias/go/tai50_20_9.fsp",

"go_EXT_60":"./instancias/go/tai100_5_0.fsp",
"go_EXT_61":"./instancias/go/tai100_5_1.fsp",
"go_EXT_62":"./instancias/go/tai100_5_2.fsp",
"go_EXT_63":"./instancias/go/tai100_5_3.fsp",
"go_EXT_64":"./instancias/go/tai100_5_4.fsp",
"go_EXT_65":"./instancias/go/tai100_5_5.fsp",
"go_EXT_66":"./instancias/go/tai100_5_6.fsp",
"go_EXT_67":"./instancias/go/tai100_5_7.fsp",
"go_EXT_68":"./instancias/go/tai100_5_8.fsp",
"go_EXT_69":"./instancias/go/tai100_5_9.fsp",

"go_EXT_70":"./instancias/go/tai100_10_0.fsp",
"go_EXT_71":"./instancias/go/tai100_10_1.fsp",
"go_EXT_72":"./instancias/go/tai100_10_2.fsp",
"go_EXT_73":"./instancias/go/tai100_10_3.fsp",
"go_EXT_74":"./instancias/go/tai100_10_4.fsp",
"go_EXT_75":"./instancias/go/tai100_10_5.fsp",
"go_EXT_76":"./instancias/go/tai100_10_6.fsp",
"go_EXT_77":"./instancias/go/tai100_10_7.fsp",
"go_EXT_78":"./instancias/go/tai100_10_8.fsp",
"go_EXT_79":"./instancias/go/tai100_10_9.fsp",

"go_EXT_80":"./instancias/go/tai100_20_0.fsp",
"go_EXT_81":"./instancias/go/tai100_20_1.fsp",
"go_EXT_82":"./instancias/go/tai100_20_2.fsp",
"go_EXT_83":"./instancias/go/tai100_20_3.fsp",
"go_EXT_84":"./instancias/go/tai100_20_4.fsp",
"go_EXT_85":"./instancias/go/tai100_20_5.fsp",
"go_EXT_86":"./instancias/go/tai100_20_6.fsp",
"go_EXT_87":"./instancias/go/tai100_20_7.fsp",
"go_EXT_88":"./instancias/go/tai100_20_8.fsp",
"go_EXT_89":"./instancias/go/tai100_20_9.fsp",

"go_EXT_90":"./instancias/go/tai200_10_0.fsp",
"go_EXT_91":"./instancias/go/tai200_10_1.fsp",
"go_EXT_92":"./instancias/go/tai200_10_2.fsp",
"go_EXT_93":"./instancias/go/tai200_10_3.fsp",
"go_EXT_94":"./instancias/go/tai200_10_4.fsp",
"go_EXT_95":"./instancias/go/tai200_10_5.fsp",
"go_EXT_96":"./instancias/go/tai200_10_6.fsp",
"go_EXT_97":"./instancias/go/tai200_10_7.fsp",
"go_EXT_98":"./instancias/go/tai200_10_8.fsp",
"go_EXT_99":"./instancias/go/tai200_10_9.fsp",

"go_EXT_100":"./instancias/go/tai200_20_0.fsp",
"go_EXT_101":"./instancias/go/tai200_20_1.fsp",
"go_EXT_102":"./instancias/go/tai200_20_2.fsp",
"go_EXT_103":"./instancias/go/tai200_20_3.fsp",
"go_EXT_104":"./instancias/go/tai200_20_4.fsp",
"go_EXT_105":"./instancias/go/tai200_20_5.fsp",
"go_EXT_106":"./instancias/go/tai200_20_6.fsp",
"go_EXT_107":"./instancias/go/tai200_20_7.fsp",
"go_EXT_108":"./instancias/go/tai200_20_8.fsp",
"go_EXT_109":"./instancias/go/tai200_20_9.fsp",

"go_EXT_110":"./instancias/go/tai500_20_0.fsp",
"go_EXT_111":"./instancias/go/tai500_20_1.fsp",
"go_EXT_112":"./instancias/go/tai500_20_2.fsp",
"go_EXT_113":"./instancias/go/tai500_20_3.fsp",
"go_EXT_114":"./instancias/go/tai500_20_4.fsp",
"go_EXT_115":"./instancias/go/tai500_20_5.fsp",
"go_EXT_116":"./instancias/go/tai500_20_6.fsp",
"go_EXT_117":"./instancias/go/tai500_20_7.fsp",
"go_EXT_118":"./instancias/go/tai500_20_8.fsp",
"go_EXT_119":"./instancias/go/tai500_20_9.fsp",

#instancias obtenidas de:
#https:#github.com/tamy0612/JSPLIB
"jsplib_EXT_0":"./instancias/jsplib/ta01",
"jsplib_EXT_1":"./instancias/jsplib/ta02",
"jsplib_EXT_2":"./instancias/jsplib/ta03",
"jsplib_EXT_3":"./instancias/jsplib/ta04",
"jsplib_EXT_4":"./instancias/jsplib/ta05",
"jsplib_EXT_5":"./instancias/jsplib/ta06",
"jsplib_EXT_6":"./instancias/jsplib/ta07",
"jsplib_EXT_7":"./instancias/jsplib/ta08",
"jsplib_EXT_8":"./instancias/jsplib/ta09",
"jsplib_EXT_9":"./instancias/jsplib/ta10",

"jsplib_EXT_10":"./instancias/jsplib/ta11",
"jsplib_EXT_11":"./instancias/jsplib/ta12",
"jsplib_EXT_12":"./instancias/jsplib/ta13",
"jsplib_EXT_13":"./instancias/jsplib/ta14",
"jsplib_EXT_14":"./instancias/jsplib/ta15",
"jsplib_EXT_15":"./instancias/jsplib/ta16",
"jsplib_EXT_16":"./instancias/jsplib/ta17",
"jsplib_EXT_17":"./instancias/jsplib/ta18",
"jsplib_EXT_18":"./instancias/jsplib/ta19",
"jsplib_EXT_19":"./instancias/jsplib/ta20",

"jsplib_EXT_20":"./instancias/jsplib/ta21",
"jsplib_EXT_21":"./instancias/jsplib/ta22",
"jsplib_EXT_22":"./instancias/jsplib/ta23",
"jsplib_EXT_23":"./instancias/jsplib/ta24",
"jsplib_EXT_24":"./instancias/jsplib/ta25",
"jsplib_EXT_25":"./instancias/jsplib/ta26",
"jsplib_EXT_26":"./instancias/jsplib/ta27",
"jsplib_EXT_27":"./instancias/jsplib/ta28",
"jsplib_EXT_28":"./instancias/jsplib/ta29",
"jsplib_EXT_29":"./instancias/jsplib/ta30",

"jsplib_EXT_30":"./instancias/jsplib/ta31",
"jsplib_EXT_31":"./instancias/jsplib/ta32",
"jsplib_EXT_32":"./instancias/jsplib/ta33",
"jsplib_EXT_33":"./instancias/jsplib/ta34",
"jsplib_EXT_34":"./instancias/jsplib/ta35",
"jsplib_EXT_35":"./instancias/jsplib/ta36",
"jsplib_EXT_36":"./instancias/jsplib/ta37",
"jsplib_EXT_37":"./instancias/jsplib/ta38",
"jsplib_EXT_38":"./instancias/jsplib/ta39",
"jsplib_EXT_39":"./instancias/jsplib/ta40",

"jsplib_EXT_40":"./instancias/jsplib/ta41",
"jsplib_EXT_41":"./instancias/jsplib/ta42",
"jsplib_EXT_42":"./instancias/jsplib/ta43",
"jsplib_EXT_43":"./instancias/jsplib/ta44",
"jsplib_EXT_44":"./instancias/jsplib/ta45",
"jsplib_EXT_45":"./instancias/jsplib/ta46",
"jsplib_EXT_46":"./instancias/jsplib/ta47",
"jsplib_EXT_47":"./instancias/jsplib/ta48",
"jsplib_EXT_48":"./instancias/jsplib/ta49",
"jsplib_EXT_49":"./instancias/jsplib/ta50",

"jsplib_EXT_50":"./instancias/jsplib/ta51",
"jsplib_EXT_51":"./instancias/jsplib/ta52",
"jsplib_EXT_52":"./instancias/jsplib/ta53",
"jsplib_EXT_53":"./instancias/jsplib/ta54",
"jsplib_EXT_54":"./instancias/jsplib/ta55",
"jsplib_EXT_55":"./instancias/jsplib/ta56",
"jsplib_EXT_56":"./instancias/jsplib/ta57",
"jsplib_EXT_57":"./instancias/jsplib/ta58",
"jsplib_EXT_58":"./instancias/jsplib/ta59",
"jsplib_EXT_59":"./instancias/jsplib/ta60",

"jsplib_EXT_60":"./instancias/jsplib/ta61",
"jsplib_EXT_61":"./instancias/jsplib/ta62",
"jsplib_EXT_62":"./instancias/jsplib/ta63",
"jsplib_EXT_63":"./instancias/jsplib/ta64",
"jsplib_EXT_64":"./instancias/jsplib/ta65",
"jsplib_EXT_65":"./instancias/jsplib/ta66",
"jsplib_EXT_66":"./instancias/jsplib/ta67",
"jsplib_EXT_67":"./instancias/jsplib/ta68",
"jsplib_EXT_68":"./instancias/jsplib/ta69",
"jsplib_EXT_69":"./instancias/jsplib/ta70",

"jsplib_EXT_70":"./instancias/jsplib/ta71",
"jsplib_EXT_71":"./instancias/jsplib/ta72",
"jsplib_EXT_72":"./instancias/jsplib/ta73",
"jsplib_EXT_73":"./instancias/jsplib/ta74",
"jsplib_EXT_74":"./instancias/jsplib/ta75",
"jsplib_EXT_75":"./instancias/jsplib/ta76",
"jsplib_EXT_76":"./instancias/jsplib/ta77",
"jsplib_EXT_77":"./instancias/jsplib/ta78",
"jsplib_EXT_78":"./instancias/jsplib/ta79",
"jsplib_EXT_79":"./instancias/jsplib/ta80"}

class pfssp:
    def __init__(self, n_jobs:int, n_machines:int, n_inds:int, tiempos:list[list[int]], poblacion:list[list[int]]):
        self.n_jobs=n_jobs
        self.n_machines=n_machines
        self.n_inds=n_inds
        self.tiempos=tiempos
        self.poblacion=poblacion if poblacion is not None else []

    def ver_poblacion(self, cant=None, f=None):
        if cant is not None:
            for i in range(cant):
                if f is None:
                    print(self.poblacion[i])
                else:
                    f.write(self.poblacion[i])
        else:
            for ind in self.poblacion:
                for _ in ind:
                    dato=_
                    if f is None:
                        print(dato)
                    else:
                        f.write(f"{dato} ")

                if f is None:
                    print("\n")
                else:
                    f.write("\n")
    
    def validez(self, ind):
        temp=np.zeros(self.n_jobs, dtype=int)
        for i in range(self.n_jobs):
            temp[ind[i]]+=1
        for i in range(self.n_jobs):
            if temp[i]>1 or temp[i]==0:
                return False
        return True

    def mutacion_aleatoria(self, ind):
        #cambia aleatoriamente 2 trabajos
        a, b=random.sample(range(self.n_jobs), 2)
        self.poblacion[ind][a], self.poblacion[ind][b]=self.poblacion[ind][b], self.poblacion[ind][a]
        #return perm
    
    def kendall_distance(self, ind_1, ind_2):
        # Posición de cada elemento en perm2
        pos2 = {elem: i for i, elem in enumerate(self.poblacion[ind_2][:-1])}

        # Convertir perm1 a los índices de perm2
        mapped = [pos2[elem] for elem in self.poblacion[ind_2][:-1]]

        # Contar inversiones (pares fuera de orden)
        dist = 0
        for i in range(len(mapped)):
            for j in range(i + 1, len(mapped)):
                if mapped[i] > mapped[j]:
                    dist += 1
        return dist
    
    def calcular_makespan(self, ind, ind_=None):
        
        if ind_ is None:
            individuo=self.poblacion[ind]
        else:
            individuo=ind_

        c=np.zeros((self.n_jobs+1, self.n_machines+1), dtype=int)

        for i in range(1, min(len(individuo), self.n_jobs)+1):
            job=int(individuo[i-1])
            for m in range(1, self.n_machines+1):
                c[i, m]=max(c[i-1,m], c[i,m-1])+self.tiempos[job][m-1]
        
        return int(c[self.n_jobs, self.n_machines])
    
    def permutacion_aleatoria(self):
        #genera una permutación aleatoria dada la cantidad de trabajos
        perm=list(range(self.n_jobs))
        random.shuffle(perm)
        perm.append(int(self.calcular_makespan(0, ind_=perm)))
        return perm
    
    def completar(self, ind):
        trabajos_ocupados=[-1]*self.n_jobs
        for i in ind:
            trabajos_ocupados[i]=1

        trabajos_faltantes=[]
        for i in range(len(trabajos_ocupados)):
            if(trabajos_ocupados[i]==-1):
                trabajos_faltantes.append(i)

        print(trabajos_faltantes)
        
        perms=[list(p) for p in itertools.permutations(trabajos_faltantes)]
        return [ind+p for p in perms]
        
    
    def NEH(self, cant=None):
        if(cant==None):
            cant=self.n_jobs
        if(cant>self.n_jobs):
            cant=self.n_jobs

        #1. ordenar los trabajos por suma de tiempos descendente
        sums = [(j, sum(self.tiempos[j])) for j in range(self.n_jobs)]
        
        ordenados = sorted(sums, key=lambda x: -x[1])
        orden = [j for j, _ in ordenados]

        #2. construir solución incremental con inserciones greedy
        seqs=[]
        seq=[]
        i=0
        
        for job in orden:
            i+=1
            best_seq = None
            best_mk = 1000000

            #probar todas las posiciones posibles
            for pos in range(len(seq)+1):
                
                nueva = seq[:pos] + [job] + seq[pos:]
                if i==cant-1:
                    seqs.append(nueva)
                
                mk = self.calcular_makespan(0, ind_=nueva)
                if mk < best_mk:
                    best_mk = mk
                    best_seq = nueva

            seq = best_seq  #actualizar mejor secuencia
            if(len(seq)>cant):
                break


        #al final, agregar el makespan como último elemento

        if cant==None or cant==self.n_jobs:
            seq.append(self.calcular_makespan(0, ind_=seq))
            return seq
        else:
            cand=[self.completar(s) for s in seqs]
            for c in cand:
                for r in c:
                    r.append(self.calcular_makespan(0, ind_=r))

            return cand

    def inicializar_poblacion(self, NEH_=False, cant=0):
        if NEH_:
            self.poblacion=[self.NEH() for ind in range(cant)]
        else:
            self.poblacion=[self.permutacion_aleatoria() for ind in range(cant)]

        self.poblacion.sort(key=lambda x: x[self.n_jobs])

    def evaluar_poblacion(self):
        return [self.calcular_makespan(ind) for ind in self.poblacion]
    
    def op_resta(self, ind_1, ind_2, verbose=False):
        sec=[]
        ind_prueba=self.poblacion[ind_2].copy()
        for i in range(self.n_jobs):
            if self.poblacion[ind_1][i]!=ind_prueba[i]:
                if(verbose): print("DIFF - ", self.poblacion[ind_1][i], ind_prueba[i])
                for j in range(i-1, self.n_jobs, 1):
                    if ind_prueba[j]==self.poblacion[ind_1][i]:
                        if(verbose): print("IGUAL - ", ind_prueba[j], self.poblacion[ind_1][i])
                        ind_prueba[i], ind_prueba[j] = ind_prueba[j], ind_prueba[i]
                        sec.append((i, j))
                        break

                if(verbose): print("res - ", self.poblacion[ind_1], ind_prueba)
                
        return sec
    
    def op_suma(self, sec, ind, frac):
        res=self.poblacion[ind].copy()
        for i in range(int(np.floor(len(sec)*frac))):
            res[sec[i][0]], res[sec[i][1]] = res[sec[i][1]], res[sec[i][0]]
            
        #res[-1]=self.calcular_makespan(ind)
        return res

    def op_two_cut_PTL_crossover(self, ind, new, verbose=False, cant=2):
        if cant>self.n_jobs: return new

        #se elige la ubicacion del corte aleatoriamente
        corte=np.random.randint(0, self.n_jobs-1, 1)[0]

        #si no vamos a poder agarrar todos los del corte que queremos, movemos a antes el corte
        if corte+cant>self.n_jobs-1:
            corte=self.n_jobs-cant

        #elegimos un lado 0 es der, 1 es izq
        lado=np.random.randint(0, 2, 1)

        #secuencia de datos del ind1
        d=[]
        for i in range(cant):
            d.append(self.poblacion[ind][corte+i])
            
        #si queremos que se imprima
        if(verbose):
            for i in d:
                print(i, end=", ")
        
        #armamos el resultado
        res=[]
        if lado==0:#si queremos que esté de la derecha
            for i in range(self.n_jobs):
                if new[i] not in d:
                    res.append(new[i])

            for _ in d:
                res.append(_)
        else:#si queremos que esté de la izquierda
            for _ in d:
                res.append(_)
            for i in range(self.n_jobs):
                if new[i] not in d:
                    res.append(new[i])
        return res
    
    def op_DE_rand_1_bin(self, v_1, v_2, specimen, mu):
        return self.op_suma(self.op_resta(v_1, v_2), specimen, mu)
    
    def op_DE_rand_to_p_best_1_bin(self, specimen, mu, p=0.2):
        return self.op_suma(self.op_resta(random.randint(0, int(self.n_inds*p)), specimen), specimen, mu)
    
    #shade 
    #mover el ptl de 2 a 3 a 5 y ya, ver que sucede
    def calcular_diferencias(self):
        diff=[]
        for i in range(self.n_inds-1):
            diff.append(len(self.op_resta(i, i+1)))
        return np.array(diff)
    
    def construir_referencia(self, cant=None):
        return self.NEH(cant)

    def evolucion_diferencial_discreta(self, n_iters=1000, mu=0.5, c_r=0.1, cruza="clasica", iters=100, verbose=100, f=None, p=0.2):
        historial=[]
        
        mejor=self.poblacion[0][-1]
        promedios=[]
        desvest=[]
        mejores=[]

        for specimen in range(self.n_inds):
            historial.append(specimen)

        for iter_ in range(n_iters):
            for specimen in range(self.n_inds):

                #tipo de cruza
                if cruza=="clasica":
                    #elegimos aleatoriamente 2 individuos
                    v_1, v_2=np.random.randint(0, self.n_inds, 2)
                    #mutacion diferencial
                    
                    w_1=self.op_DE_rand_1_bin(v_1, v_2, specimen, mu)

                if cruza=="SHADE":
                    w_1=self.op_DE_rand_to_p_best_1_bin(specimen, mu, p=p)

                #recombinacion
                new=self.op_two_cut_PTL_crossover(specimen, w_1, cant=max(1, int(self.n_jobs*c_r)))
                new.append(0)
                        
                new[-1]=self.calcular_makespan(0, ind_=new)

                historial.append(new)

                #seleccion
                if new[-1]<self.poblacion[specimen][-1]: # type: ignore
                    for i in range(self.n_jobs):
                        self.poblacion[specimen][i]=new[i] # type: ignore
                    self.poblacion[specimen][-1]=new[-1] # type: ignore
                    if new[-1]<mejor:
                        mejor=new[-1]


                self.poblacion.sort(key=lambda x: x[self.n_jobs])

            diff=self.calcular_diferencias()

            if(verbose):
                if(iter_%verbose==0):
                    if f is None:
                        print("\niter: ",iter_, " - mejor: ", mejor, " - promedio: ", np.mean(self.poblacion, axis=0)[-1], " - std: ", np.std(self.poblacion, axis=0)[-1], "\n")
                    else:
                        f.write(f"\niter: {iter_} - mejor: {mejor} - promedio: {np.mean(self.poblacion, axis=0)[-1]} - std: {np.std(self.poblacion, axis=0)[-1]} - c_r: {max(1, int(self.n_jobs*c_r))} - diferencias - mean: {np.mean(diff)} - std: {np.std(diff)}\n")
            
            promedios.append(np.mean(self.poblacion, axis=0)[-1])
            desvest.append(np.std(self.poblacion, axis=0)[-1])
            mejores.append(self.poblacion[0][-1])

        return promedios, desvest, mejores, mejor, historial


def cargar_jsplib_JSPLIB(path):
    with open(path, 'r') as f:
        lines = [line.strip() for line in f if line.strip()]

    n_jobs, n_machines = map(int, lines[0].split())
    tiempos = [[0]*n_machines for _ in range(n_jobs)]
    maquinas = [[0]*n_machines for _ in range(n_jobs)]

    for i, line in enumerate(lines[1:]):
        data=list(map(int, line.split()))
        
        for j in range(n_machines):
            maquinas[i][j] = data[2*j]
            tiempos[i][j] = data[2*j+1]

    return maquinas, tiempos

def convertir_a_fssp_JSPLIB(maquinas, tiempos):
    # asumimos que el orden de máquinas es [1..m]
    n_jobs = len(maquinas)
    n_machines = len(maquinas[0])
    orden = list(range(0, n_machines))

    tiempos_fssp = []
    for i in range(n_jobs):
        tiempos_por_maquina = []
        for m in orden:
            idx = maquinas[i].index(m)
            tiempos_por_maquina.append(tiempos[i][idx])
        tiempos_fssp.append(tiempos_por_maquina)
    return tiempos_fssp

def cargar_pfs_go(path):
    with open(path, 'r') as f:
        lines = [line.strip() for line in f]

    return [[_ for _ in l.split()] for l in lines[3:]]

def validez(ind, n_jobs):
    temp=np.zeros(n_jobs, dtype=int)
    for i in range(n_jobs):
        temp[ind[i]]+=1
    for i in range(n_jobs):
        if temp[i]>1 or temp[i]==0:
            return False
    return True

def calcular_makespan(ind, tiempos, n_jobs, n_machines):
    c=np.zeros((n_jobs+1, n_machines+1), dtype=int)

    for i in range(1, min(len(ind), n_jobs)+1):
        job=int(ind[i-1])
        for m in range(1, n_machines+1):
            c[i, m]=max(c[i-1,m], c[i,m-1])+tiempos[job][m-1]
    
    return int(c[n_jobs, n_machines]), c

def makespan_incremental(perm, job, pos, c, n_jobs, n_machines, tiempos):
    n = len(c)
    m = len(c[0])

    c_ = [fila[:] + [0] for fila in c]
    c_=np.array(c_)
    c_=c_.T

    for i in range(1, n_machines + 1):
        c_[i][pos + 1] = max(c_[i - 1][pos + 1], c_[i][pos]) + tiempos[job][i-1]

    for i in range(1, n_machines + 1):
        for j in range(pos + 2, min(len(perm) + 1, n_jobs) + 1):
            c_[i][j] = max(c_[i - 1][j], c_[i][j - 1]) + tiempos[perm[j - 2]][i-1]
            #c_[j][i] = max(c_[i - 1][j], c_[i][j - 1]) + tiempos[i - 1][perm[j - 2]]

    return c_[-1][-1]
   
def permutacion_aleatoria(n_jobs, n_machines=0, tiempos=None):
    #genera una permutación aleatoria dada la cantidad de trabajos
    perm=list(range(n_jobs))
    random.shuffle(perm)

    if tiempos!=None:
        mk, _=calcular_makespan(perm, tiempos, n_jobs, n_machines)
        perm.append(mk)

    return perm

def ONE_POINT_V1(perm1, perm2, p, n_jobs):
    nueva_1=[-1 for i in range(n_jobs)]
    nueva_2=[-1 for i in range(n_jobs)]
    usados=[False for i in range(n_jobs)]

    for i in range(n_jobs):
        if(i<p):
            nueva_1[i]=perm1[i]
            usados[perm1[i]]=True
        else:
            nueva_2[i]=perm1[i]

    count=0
    for i in range(n_jobs):
        if not usados[perm2[i]]:
            nueva_1[p]=perm2[i]
            p+=1
        else:
            nueva_2[count]=perm2[i]
            count+=1

    return nueva_1, nueva_2 
        
def TWO_POINT_V1(perm1, perm2, L, R, n_jobs):
    used_1=[False for i in range(n_jobs)]
    used_2=[False for i in range(n_jobs)]
    nueva_1=[-1 for i in range(n_jobs)]
    nueva_2=[-1 for i in range(n_jobs)]

    for i in range(0, L):
        nueva_1[i]=perm1[i]
        nueva_2[i]=perm2[i]
        used_1[ perm1[i] ]=True
        used_2[ perm2[i] ]=True

    for i in range(R+1, n_jobs):
        nueva_1[i]=perm1[i]
        nueva_2[i]=perm2[i]
        used_1[ perm1[i] ]=True
        used_2[ perm2[i] ]=True

    idx_1=L
    idx_2=L

    for i in range(n_jobs):
        if not used_1[perm2[i]]:
            nueva_1[idx_1] = perm2[i]
            idx_1+=1
        
        if not used_2[perm1[i]]:
            nueva_2[idx_2] = perm1[i]
            idx_2+=1
            
    return nueva_1, nueva_2

def op_two_cut_PTL_crossover(ind1, ind2, L, R, n_jobs, verbose=False, cant=2):
    nueva_1=[-1 for i in range(n_jobs)]
    nueva_2=[-1 for i in range(n_jobs)]
    usados=[False for i in range(n_jobs)]

    count_1=0
    count_2=n_jobs-(R-L)-1
    
    for i in range(L, R+1):
        nueva_1[count_1]=ind1[i]
        count_1+=1
        nueva_2[count_2]=ind1[i]
        count_2+=1
        usados[ind1[i]]=True

    for i in range(n_jobs):
        if usados[ind2[i]]: continue
        nueva_1[count_1]=ind2[i]
        nueva_2[count_2%n_jobs]=ind2[i]
        count_1+=1
        count_2+=1

    return nueva_1, nueva_2

def mutacion_aleatoria(ind, n_jobs):
    #cambia aleatoriamente 2 trabajos
    ind_c=ind.copy()
    a, b=random.sample(range(n_jobs), 2)
    ind_c[a], ind_c[b]=ind_c[b], ind_c[a]
    return ind_c

def op_resta(ind_1, ind_2, n_jobs, verbose=False):
    sec=[]
    ind_prueba=ind_2.copy()
    for i in range(n_jobs):
        if ind_1[i]!=ind_prueba[i]:
            if(verbose): print("DIFF - ", ind_1[i], ind_prueba[i])
            for j in range(i-1, n_jobs, 1):
                if ind_prueba[j]==ind_1[i]:
                    if(verbose): print("IGUAL - ", ind_prueba[j], ind_1[i])
                    ind_prueba[i], ind_prueba[j] = ind_prueba[j], ind_prueba[i]
                    sec.append((i, j))
                    break

            if(verbose): print("res - ", ind_1, ind_prueba)
            
    return sec, len(sec)

def completar(n_jobs, ind):
    trabajos_ocupados=[-1]*n_jobs
    for i in ind:
        trabajos_ocupados[i]=1

    trabajos_faltantes=[]
    for i in range(len(trabajos_ocupados)):
        if(trabajos_ocupados[i]==-1):
            trabajos_faltantes.append(i)

    print(trabajos_faltantes)
    
    perms=[list(p) for p in itertools.permutations(trabajos_faltantes)]
    return [ind+p for p in perms]

def NEH(n_jobs, n_machines, tiempos, cant=None):
    if(cant==None):
        cant=n_jobs
    if(cant>n_jobs):
        cant=n_jobs

    #1. ordenar los trabajos por suma de tiempos descendente
    sums = [(j, sum(tiempos[j])) for j in range(n_jobs)]
    
    ordenados = sorted(sums, key=lambda x: -x[1])
    orden = [j for j, _ in ordenados]

    #2. construir solución incremental con inserciones greedy
    seqs=[]
    seq=[]
    i=0
    
    for job in orden:
        i+=1
        best_seq = None
        best_mk = 1000000

        #probar todas las posiciones posibles
        for pos in range(len(seq)+1):
            
            nueva = seq[:pos] + [job] + seq[pos:]
            if i==cant-1:
                seqs.append(nueva)
            
            mk, _ = calcular_makespan(nueva, tiempos, n_jobs, n_machines)
            if mk < best_mk:
                best_mk = mk
                best_seq = nueva

        seq = best_seq  #actualizar mejor secuencia
        if(len(seq)>cant):
            break


    #al final, agregar el makespan como último elemento

    if cant==None or cant==n_jobs:
        mk, _=calcular_makespan(seq, tiempos, n_jobs, n_machines)
        seq.append(mk)
        return seq
    else:
        cand=[completar(n_jobs, s) for s in seqs]
        for c in cand:
            for r in c:
                mk, _=calcular_makespan(r, tiempos, n_jobs, n_machines)
                r.append(mk)

        return cand

def DestructConstruct(ind, d, n_jobs, n_machines, tiempos, verbose=False):
    # eliminamos d elementos
    d_pos_ = permutacion_aleatoria(n_jobs)
    d_pos = d_pos_[:d]
    ind_ = ind[:-1].copy()   # copia sin el makespan final
    d_elems = [0] * d

    # ordenamos las posiciones
    d_pos.sort()

    count=0
    for a in d_pos:
        d_elems[count] = ind_[a - count]
        del ind_[a - count]
        count += 1

    # reinsertamos de manera greedy los elementos eliminados
    mejor_makespan = 1000000

    for i in range(d):
        n = len(ind_)

        _, c_prev = calcular_makespan(ind_, tiempos, n_jobs, n_machines)

        mejor_pos = 0
        for j in range(n + 1):
            mk = makespan_incremental(ind_, d_elems[i], j, c_prev, n_jobs, n_machines, tiempos)

            if mk < mejor_makespan:
                mejor_pos = j
                mejor_makespan = mk

        ind_c = [0] * (n + 1)

        for j in range(mejor_pos):
            ind_c[j] = ind_[j]

        ind_c[mejor_pos] = d_elems[i]

        for j in range(mejor_pos, n):
            ind_c[j + 1] = ind_[j]

        ind_ = ind_c
        mejor_makespan = 1000000

    mk, _=calcular_makespan(ind_, tiempos, n_jobs, n_machines)
    ind_.append(mk)
    return ind_

def RIS(ind, ref, n_jobs, n_machines, tiempos, verbose=False):
    # guardamos el makespan actual
    mkspn_actual = ind[n_jobs]
    ind = ind[:-1].copy()

    no_mejoras = 0
    pos = 0
    ind_pi_1 = ind.copy()

    mejor_makespan = 1000000

    while no_mejoras < n_jobs or no_mejoras < 10:
        if(verbose): print("ITER: ", no_mejoras)
        if(verbose): print("IND_PI_1 PREV: ", ind_pi_1)

        # eliminar el elemento h-ésimo de ref en ind
        pos_ref = 0
        for i in range(n_jobs):
            if ind[i] == ref[pos % n_jobs]:
                pos_ref = i
                break

        if(verbose): print("ELEMENTO A ELIMINAR: ", ind[pos_ref])
        if(verbose): print("IND VIEJO: ", ind)
        del ind[pos_ref]
        if(verbose): print("IND NUEVO: ", ind)

        _, c_prev = calcular_makespan(ind, tiempos, n_jobs, n_machines)

        # determinar la mejor posición para el trabajo eliminado
        mejor_pos = 0
        for i in range(len(ind) + 1):
            mk=makespan_incremental(ind, ref[pos % n_jobs], i, c_prev, n_jobs, n_machines, tiempos)
            if mk < mejor_makespan:
                mejor_pos = i
                mejor_makespan = mk

        if(verbose): print("MEJOR MK: ", mejor_makespan, ", MEJOR POS: ", mejor_pos)

        # agregar el trabajo eliminado
        ind_c = [0] * n_jobs

        for i in range(mejor_pos):
            ind_c[i] = ind[i]

        ind_c[mejor_pos] = ref[pos % n_jobs]
        pos += 1

        for i in range(mejor_pos, n_jobs - 1):
            ind_c[i +1] = ind[i]

        if(verbose): print("IND ELEMENTO AGREGADO: ", ind_c)

        if mejor_makespan < mkspn_actual:
            if(verbose): print("MEJOR, ", len(ind))
            if(verbose): print("IGUAL A: ", ind_c)
            ind = ind_c.copy()
            mkspn_actual = mejor_makespan
            no_mejoras = 0
        else:
            if(verbose): print("PEOR, ", len(ind))
            if(verbose): print("IGUAL A: ", ind_pi_1)
            ind = ind_pi_1.copy()
            no_mejoras += 1

        ind_pi_1 = ind_c.copy()
        mejor_makespan = 1000000

        if(verbose): print("MK ACTUAL: ", mkspn_actual, "\nIND ACTUAL: ", ind)
        if(verbose): print("IND_PI_1: ", ind_pi_1)
        if(verbose): print("IND_C: ", ind_c)

        if(verbose): print("------")

    mk, _=calcular_makespan(ind, tiempos, n_jobs, n_machines)
    ind.append(mk)
    return ind

def RLS(ind, ref, d, n_jobs, n_machines, tiempos, iter=0, n_iters=0, verbose=False):
    if n_jobs < 101:
        pi = DestructConstruct(ind, d, n_jobs, n_machines, tiempos)
        pi_1 = RIS(pi, ref, n_jobs, n_machines, tiempos)

        if verbose:
            print("PI   - ", end="")
            if not validez(pi, n_jobs):
                print(" MAL ", end="")
            for a in pi:
                print(f"{a}, ", end="")
            print()

            print("PI_1 - ", end="")
            if not validez(pi_1, n_jobs):
                print(" MAL ", end="")
            for a in pi_1:
                print(f"{a}, ", end="")
            print("\n")

        # if pi_1[self.n_jobs] < pi[self.n_jobs] or rand_dbl(self.rndm) < self.temperatura(iter, 4.0 / n_iters):
        if pi_1[n_jobs] < pi[n_jobs]:
            return pi_1
        else:
            return pi
    else:
        return DestructConstruct(ind, d, n_jobs, n_machines, tiempos)

def distancia_manhattan(ind_1, ind_2, n_jobs):
    d=0
    sigma_a=[0 for i in range(n_jobs)]
    sigma_b=[0 for i in range(n_jobs)]

    for i in range(n_jobs):
        sigma_a[ ind_1[i] ] = i
        sigma_b[ ind_2[i] ] = i

    for i in range(n_jobs):
        d += abs(sigma_a[i] - sigma_b[i])
    
    return d

def getCurrentEntropyGene(gene_idx, pob, n_jobs):
    cnt_frequency=[0.0 for i in range(n_jobs)]
    for i in range(len(pob)):
        cnt_frequency[ pob[i][gene_idx] ]+=1


    entropy_gene = 0.0
    log_base = np.log(n_jobs)
    for i in range(n_jobs):
        if cnt_frequency[i]==0: continue
        
        pi=cnt_frequency[i]/n_jobs
        entropy_gene -= pi*np.log(pi)
    
    entropy_gene /= log_base
    return entropy_gene

def getCurrentEntropy(pob, n_jobs):
    entropy = 0.0
    for i in range(n_jobs):
        entropy += getCurrentEntropyGene(i, pob, n_jobs)

    entropy /= n_jobs
    return entropy

def todas_las_distancias(pob, n_jobs):
    distancias=np.array([[0 for i in range(len(pob))] for j in range(len(pob))])

    for i in range(len(pob)):
        for j in range(i):
            dist=distancia_manhattan(pob[i], pob[j], n_jobs)
            distancias[i][j]=dist
            distancias[j][i]=dist

    distancias=np.array(distancias)

    mask=~np.eye(distancias.shape[0], dtype=bool)

    valores = distancias[mask]

    return distancias, np.mean(np.array(valores)), np.std(np.array(valores))

def ver_metricas(res_dict, nombre_archivo="metricas.png"):

    fig, axs = plt.subplots(2, 2, figsize=(12, 8))
    metricas = ["Variedad", "Entropia", "Historial", "Calidad del modelo"]

    for ax, metrica in zip(axs.ravel(), metricas):
        x = range(len(res_dict[metrica]))
        y = res_dict[metrica]
        ax.plot(x, y)
        ax.set_title(metrica)
        ax.set_xlabel("Iteración")
        ax.set_ylabel(metrica)
        ax.grid(True)

    plt.tight_layout()
    fig.savefig(nombre_archivo, dpi=300, bbox_inches="tight")
    plt.close(fig)  # evita que se muestre en notebooks

    return fig

def BNP(pob, offspring, n_jobs, n_inds, n_iter_actual, n_iters, d_i):

    # Q = P_g U O_g
    all_inds = [ind.copy() for ind in pob] + [ind.copy() for ind in offspring]

    idx_all = len(all_inds)
    idx_population = 0
    n_pob = []

    # Distancia mínima de cada individuo candidato a la nueva población
    dists_all = [1e20 for _ in range(idx_all)]

    # Select best solution: menor makespan
    idx_best = 0
    for i in range(1, idx_all):
        if all_inds[i][-1] < all_inds[idx_best][-1]:
            idx_best = i

    # Insertar el mejor absoluto
    n_pob.append(all_inds[idx_best])
    idx_population += 1

    # Removerlo de los candidatos
    all_inds[idx_best] = all_inds[idx_all - 1]
    dists_all[idx_best] = dists_all[idx_all - 1]
    idx_all -= 1

    # Distancia umbral dinámica
    D = d_i - d_i * n_iter_actual / n_iters

    # Seleccionar los siguientes N - 1 individuos
    while idx_population != n_inds:

        # Update distances:
        # dists_all[i] guarda min distancia de all_inds[i]
        # contra cualquier individuo ya seleccionado en n_pob
        for i in range(idx_all):
            dists_all[i] = min(
                dists_all[i],
                distancia_manhattan(all_inds[i], n_pob[-1], n_jobs)
            )

        # Select best option
        idx_best = 0

        for i in range(1, idx_all):
            betterInDist = dists_all[i] > dists_all[idx_best]
            eqInDist = dists_all[i] == dists_all[idx_best]

            betterInFit = all_inds[i][-1] < all_inds[idx_best][-1]
            eqInFit = all_inds[i][-1] == all_inds[idx_best][-1]

            if dists_all[idx_best] < D:
                # El candidato actual idx_best NO cumple la distancia mínima.
                # Entonces priorizamos distancia.
                if betterInDist or (eqInDist and betterInFit):
                    idx_best = i

            else:
                # El candidato actual idx_best sí cumple.
                # Solo consideramos otros que también cumplan.
                if dists_all[i] >= D:
                    # Entre elegibles, priorizamos makespan.
                    if betterInFit or (eqInFit and betterInDist):
                        idx_best = i

        # Insertar mejor candidato
        n_pob.append(all_inds[idx_best])
        idx_population += 1

        # Remover de candidatos, copiando también su distancia
        all_inds[idx_best] = all_inds[idx_all - 1]
        dists_all[idx_best] = dists_all[idx_all - 1]

        idx_all -= 1

    return n_pob

def f_exp_dos_puntos(x, x1, y1, x2, y2, k):
    B = (y2 - y1) / (np.exp(k*x2) - np.exp(k*x1))
    A = y1 - B * (np.exp(k*x1) - 1)
    return A + B * (np.exp(k*x) - 1)

def modelo_precedencias(pob, n_bins, bins=None):
    #declarando cantidad de trabajos, individuos y bins (O(1))
    n_jobs=len(pob[0])-1
    n_inds=len(pob)
    if(bins==None):
        bins=[[i for i in range(int(((n_inds-1)/n_bins)*i+(0 if i==0 else 1)), int(((n_inds-1)/n_bins)*(i+1)+1), 1)] for i in range(n_bins)]

    #SOLAMENTE TOMAR EL MEJOR BIN
    #HACER 2 BINS NO SIMETRICOS 

    #construyendo las matrices de dependencias (O(n^3))
    matrices_precedencias_individuo=np.zeros((n_inds, n_jobs, n_jobs), dtype=int)
    matriz_precedencias_poblacion=np.zeros((n_jobs, n_jobs), dtype=float)

    for i in range(n_inds):
        for j in range(n_jobs):
            for k in range(len(pob[0])-2, j, -1):
                matrices_precedencias_individuo[i][pob[i][j]][pob[i][k]]+=1
                matriz_precedencias_poblacion[pob[i][j]][pob[i][k]]+=1

    matriz_precedencias_poblacion/=n_inds
    matriz_precedencias_poblacion=np.array([[0 if x==0 or x==1 else -x*mt.log2(x)-(1-x)*mt.log2(1-x) for x in y] for y in matriz_precedencias_poblacion])

    #O(n^4)
    #ahora contamos las frecuencias de x=0 cuando "y" pertenece a algun bin, y cuando
    #x=1 cuando pertenece al mismo bin, por todos los bins 
    probabilidades_conjuntas=[np.zeros((2, n_jobs, n_jobs), dtype=float) for bin_ in bins]
    probabilidades_conjuntas_2_bins=[np.zeros((2, n_jobs, n_jobs), dtype=float) for bin_ in range(2)]

    #iterando sobre cada individuo:

    #iteramos sobre los bins
    for i in range(n_bins):
        #iteramos sobre los elementos de los bins
        for j in range(len(bins[i])):

            #iteramos sobre la matriz de precedencia de cada individuo
            for k in range(n_jobs):
                for l in range(n_jobs):
                    if(k!=l):
                        #si en la permutación actual el trabajo k estuvo antes que el l (presencia de la variable)
                        probabilidades_conjuntas[i][matrices_precedencias_individuo[bins[i][j]][k][l]][k][l]+=1
                        #                          |                               | buscamos |      |
                        #                          |                               |en bin que|      |  
                        #                          |                               └corresponde┘     |
                        #                          └       presencia o ausencia de la variable       ┘          
                        
                        probabilidades_conjuntas_2_bins[0 if i<n_bins/2 else 1][matrices_precedencias_individuo[bins[i][j]][k][l]][k][l]+=1                     

        #probabilidades_conjuntas[i]/=len(bins[i])              


    #obteniendo las probabilidades conjuntas (# de casos/# de individuos)
    probabilidades_conjuntas=[[[[l/n_inds for l in k]for k in j]for j in i] for i in probabilidades_conjuntas]
    probabilidades_conjuntas_2_bins=[[[[l/n_inds for l in k]for k in j]for j in i] for i in probabilidades_conjuntas_2_bins]

    #calculando las probablidades marginales O(n^4)
    #probabilidades marginales variables
    probabilidades_marginales_x=np.zeros((2, n_jobs, n_jobs), dtype=float)
    #probabilidades marginales bins
    probabilidades_marginales_y=np.zeros((n_bins, n_jobs, n_jobs), dtype=float)

    for i in range(n_bins):
        for j in range(2):
            for k in range(n_jobs):
                for l in range(n_jobs):
                    probabilidades_marginales_x[j][k][l]+=probabilidades_conjuntas[i][j][k][l]
                    probabilidades_marginales_y[i][k][l]+=probabilidades_conjuntas[i][j][k][l]

    #calculando la información mutua entre variables y makespan O(n^4)
    informacion_mutua=np.zeros((n_jobs, n_jobs), dtype=float)

    for i in range(n_bins):
        for j in range(2):
            for k in range(n_jobs):
                for l in range(n_jobs):
                    if(probabilidades_conjuntas[i][j][k][l]!=0.0 and probabilidades_marginales_x[j][k][l]!=0.0 and probabilidades_marginales_y[i][k][l]!=0.0):
                        informacion_mutua[k][l]+=probabilidades_conjuntas[i][j][k][l]*mt.log2(probabilidades_conjuntas[i][j][k][l]/(probabilidades_marginales_x[j][k][l]*probabilidades_marginales_y[i][k][l]))


    #calculando la información normalizada mutua entre variables y makespan O(n^2)
    informacion_mutua_normalizada=np.zeros((n_jobs, n_jobs), dtype=float)

    for i in range(n_jobs):
        for j in range(n_jobs):
            if(i!=j and matriz_precedencias_poblacion[i][j]!=0.0):
                informacion_mutua_normalizada[i][j]=informacion_mutua[i][j]/matriz_precedencias_poblacion[i][j]

    #rankeando la información mutua por parejas  O(n^2)
    ranking_informacion_mutua_normalizada=[]
    for i in range(n_jobs):
        for j in range(i):
            ranking_informacion_mutua_normalizada.append([informacion_mutua_normalizada[i][j], i, j])

    ranking_informacion_mutua_normalizada=sorted(ranking_informacion_mutua_normalizada, key=lambda col: col[0], reverse=True)

    #eligiendo precededencias  O(n^2*n_bins)
    for im in ranking_informacion_mutua_normalizada:
        i=0
        while(i<n_bins/2):
            if(probabilidades_conjuntas[i][0][im[1]][im[2]]<probabilidades_conjuntas[i][0][im[2]][im[1]]):
                im[1], im[2]=im[2], im[1]
            elif(abs(probabilidades_conjuntas[i][0][im[1]][im[2]]-probabilidades_conjuntas[i][0][im[2]][im[1]])<1e-5):
                i+=1
            else:
                break
        while(i<n_bins):
            if(probabilidades_conjuntas[i][0][im[1]][im[2]]>probabilidades_conjuntas[i][0][im[2]][im[1]]):
                im[1], im[2]=im[2], im[1]
            elif(abs(probabilidades_conjuntas[i][0][im[1]][im[2]]-probabilidades_conjuntas[i][0][im[2]][im[1]])<1e-5):
                i+=1
            else:
                break

    return ranking_informacion_mutua_normalizada, informacion_mutua_normalizada, bins

def random_swap(ranking_informacion_mutua_normalizada, n_jobs, n_nuevos_inds, n_swaps):
    #dado el modelo, se genera un individuo con todas las características seleccionadas del modelo
    cantidad_precedencias_trabajo=[[0, i] for i in range(n_jobs)]
    for i in ranking_informacion_mutua_normalizada:
        cantidad_precedencias_trabajo[i[1]][0]+=1
    cantidad_precedencias_trabajo=sorted(cantidad_precedencias_trabajo, key=lambda col: col[0], reverse=True)

    #se genera una nueva población haciendo variaciones al indiiduo generado por el modelo
    individuo=[i[1] for i in cantidad_precedencias_trabajo]
    n_pob=[]
    for i in range(n_nuevos_inds):
        n_pob.append(individuo.copy())
        for j in range(n_swaps):
            n_pob[-1]=mutacion_aleatoria(n_pob[-1], n_jobs)

    return n_pob, individuo

def rank_swap(ranking_informacion_mutua_normalizada, n_jobs, n_nuevos_inds, n_swaps, eps=1e-5):
    #dado el modelo, se genera un individuo con todas las características seleccionadas del modelo
    cantidad_precedencias_trabajo=[[0, i] for i in range(n_jobs)]
    for i in ranking_informacion_mutua_normalizada:
        cantidad_precedencias_trabajo[i[1]][0]+=1
    cantidad_precedencias_trabajo=sorted(cantidad_precedencias_trabajo, key=lambda col: col[0], reverse=True)

    individuo=[i[1] for i in cantidad_precedencias_trabajo]

    posiciones={}
    for pos, trabajo in enumerate(individuo): posiciones[trabajo]=pos

    n_pob=[]
    probs=[0.0 for i in range(len(ranking_informacion_mutua_normalizada))]
    succes_rate=[0 for i in range(len(ranking_informacion_mutua_normalizada))]

    for i in range(n_nuevos_inds):
        n_ind=individuo.copy()
        for j in range(len(ranking_informacion_mutua_normalizada)):
            factor=(ranking_informacion_mutua_normalizada[j][0]/ranking_informacion_mutua_normalizada[0][0])
            probs[j]=(factor**0.2-(eps*factor**0.2))
            if random.random()<(factor**0.2-(eps*factor**0.2)):
                n_ind[posiciones[ranking_informacion_mutua_normalizada[j][1]]], n_ind[posiciones[ranking_informacion_mutua_normalizada[j][2]]] = n_ind[posiciones[ranking_informacion_mutua_normalizada[j][2]]], n_ind[posiciones[ranking_informacion_mutua_normalizada[j][1]]]
                posiciones[n_ind[ranking_informacion_mutua_normalizada[j][1]]] = ranking_informacion_mutua_normalizada[j][2]
                posiciones[n_ind[ranking_informacion_mutua_normalizada[j][2]]] = ranking_informacion_mutua_normalizada[j][1]

                succes_rate[j]+=1

        for j in range(n_swaps):
            n_ind=mutacion_aleatoria(n_ind, n_jobs)

        n_pob.append(n_ind)

    return n_pob, individuo, probs, succes_rate

def incremental_build(ranking_informacion_mutua_normalizada, n_jobs, n_nuevos_inds, eps=1e-5, gamma=1e-5, scores=[1.0, 1.0, 1.0, 1.0]):
    diccionario_precedencias={i:[[-1 for i in range(n_jobs)], [-1 for i in range(n_jobs)]] for i in range(n_jobs)}
    base_minima=0.0
    for i in ranking_informacion_mutua_normalizada:
        base_minima-=i[0]
        diccionario_precedencias[i[1]][0][i[2]]=i[0]
        diccionario_precedencias[i[2]][1][i[1]]=i[0]

    status_trabajos={i:-1 for i in range(n_jobs)}
    trabajos_disponibles_referencia=[i for i in range(n_jobs)]

    base=[]

    while len(trabajos_disponibles_referencia) != 0:

        scores_trabajos = {i: base_minima for i in range(n_jobs)}
        #for i in trabajos_disponibles_referencia:
            #scores_trabajos[i] = 0.0
        
        for i in range(n_jobs):
            if status_trabajos[i] == 1:
                continue

            for j in trabajos_disponibles_referencia:
                if i == j:
                    continue

                if diccionario_precedencias[i][0][j] != -1:
                    scores_trabajos[i] += diccionario_precedencias[i][0][j]*scores[0]
                    
                if diccionario_precedencias[i][1][j] != -1:
                    scores_trabajos[i] -= diccionario_precedencias[i][1][j]*scores[1]

            for j in range(len(base)):
                if i==base[j][0]:
                    continue

                if diccionario_precedencias[i][0][base[j][0]] != -1:
                    scores_trabajos[i] += diccionario_precedencias[i][0][base[j][0]]*scores[2]
                    
                if diccionario_precedencias[i][1][base[j][0]] != -1:
                    scores_trabajos[i] -= diccionario_precedencias[i][1][base[j][0]]*scores[3]


        mejor_pos = 0
        mejor_trabajo = trabajos_disponibles_referencia[0]

        for pos in range(1, len(trabajos_disponibles_referencia)):
            trabajo = trabajos_disponibles_referencia[pos]

            if scores_trabajos[trabajo] > scores_trabajos[mejor_trabajo]:
                mejor_pos = pos
                mejor_trabajo = trabajo

        trabajo_elegido = mejor_trabajo

        base.append([trabajo_elegido, scores_trabajos[trabajo_elegido]])

        status_trabajos[trabajo_elegido] = 1
        trabajos_disponibles_referencia.pop(mejor_pos)

    for i in range(len(base)):
        base[i][1]+=abs(base[-1][1])+eps

    n_pob=[]

    for i in range(n_nuevos_inds):
        trabajos_base=base.copy()
        n_ind=[]

        for j in range(n_jobs):
            pesos = [mt.exp(gamma * (k[1] - trabajos_base[0][1]))for k in trabajos_base]
            suma=sum(pesos)
            n_rand = random.random()*suma

            acumulado = 0.0
            indice = 0
            for idx, peso in enumerate(pesos):
                acumulado += peso
                if n_rand <= acumulado:
                    indice = idx
                    break

            n_ind.append(trabajos_base[indice][0])
            trabajos_base.pop(indice)

        if not validez(n_ind, n_jobs):
            print("MAAAAAAL")

        n_pob.append(n_ind)
    
    return n_pob, [i[0] for i in base], base

def EDA_random_swap(pob, n_iters, n_inds, n_jobs, n_machines, n_swaps, porcentaje_poblacion, n_bins, bins_simetricos, limites_bins=[0.0, 0.05, 0.1,  0.25, 0.4, 0.7, 1.0], verbose=0, tiempos=None):
    #2.-
    t=0
    #3.- 

    historial=[pob[0][-1]]
    mejor_previo=pob[0][-1]
    hist_modelo=[]
    distancias_promedio=[]
    entropias=[]

    while(t<n_iters):
        if(verbose!=0): 
            if(t%verbose==0):
                print(t)
        
        #generando bins
        if bins_simetricos==False:
            bins=[[i for i in range(int(limites_bins[j-1]*(n_inds*porcentaje_poblacion)), int(limites_bins[j]*(n_inds*porcentaje_poblacion)), 1)] for j in range(1, len(limites_bins), 1)]
        
            #4.- 
            ranking_informacion_mutua_normalizada, informacion_mutua_normalizada, bins=modelo_precedencias(pob[:min(n_inds, 500)], len(bins), bins)
        else:
            #4.- 
            ranking_informacion_mutua_normalizada, informacion_mutua_normalizada, bins=modelo_precedencias(pob[:500], n_bins)

        #5.- 
        n_pob, ind_modelo=random_swap(ranking_informacion_mutua_normalizada, n_jobs, n_inds, n_swaps)
        #n_pob, ind_modelo=rank_swap(ranking_informacion_mutua_normalizada, pfssp_taillard.n_jobs, n_inds)

        #6.- 
        for n_ind in n_pob:
            mk, _=calcular_makespan(n_ind, tiempos, n_jobs, n_machines)
            n_ind.append(mk)

        mk, _=calcular_makespan(ind_modelo, tiempos, n_jobs, n_machines)
        hist_modelo.append((mk-pob[0][-1])/(pob[-1][-1]-pob[0][-1]))

        for i in n_pob:
            pob.append(i)

        pob=sorted(pob, key=lambda col: col[-1])

        historial.append(pob[0][-1])
        
        entropias.append(getCurrentEntropy(pob[:500], n_jobs))
        dists, prom, std=todas_las_distancias(pob[:500], n_jobs)
        distancias_promedio.append(prom)
        #7.-
        t+=1

    mejor_encontrado=pob[0][-1]

    return {"Mejor previo":       mejor_previo, 
            "Mejor encontrado":   mejor_encontrado, 
            "Diferencia":         mejor_previo-mejor_encontrado, 
            "Historial":          historial, 
            "Calidad del modelo": hist_modelo, 
            "Variedad":           distancias_promedio,
            "Entropia":           entropias, 
            "Poblacion":          pob}

def EDA_rank_swap(pob, n_iters, n_inds, n_jobs, n_machines, porcentaje_poblacion, n_bins, bins_simetricos, n_swaps, limites_bins=[0.0, 0.05, 0.1,  0.25, 0.4, 0.7, 1.0], verbose=0, tiempos=None):
    #2.-
    t=0
    #3.- 

    historial=[pob[0][-1]]
    mejor_previo=pob[0][-1]
    hist_modelo=[]
    distancias_promedio=[]
    entropias=[]

    while(t<n_iters):
        if(verbose!=0): 
            if(t%verbose==0):
                print(t)
        
        #generando bins
        if bins_simetricos==False:
            bins=[[i for i in range(int(limites_bins[j-1]*(n_inds*porcentaje_poblacion)), int(limites_bins[j]*(n_inds*porcentaje_poblacion)), 1)] for j in range(1, len(limites_bins), 1)]
        
            #4.- 
            ranking_informacion_mutua_normalizada, informacion_mutua_normalizada, bins=modelo_precedencias(pob[:min(n_inds, 500)], len(bins), bins)
        else:
            #4.- 
            ranking_informacion_mutua_normalizada, informacion_mutua_normalizada, bins=modelo_precedencias(pob[:n_inds], n_bins)

        #5.-
        #n_pob, ind_modelo=rank_swap(ranking_informacion_mutua_normalizada, pfssp_taillard.n_jobs, n_inds, n_swaps)
        n_pob, ind_modelo, probs, succes_rate=rank_swap(ranking_informacion_mutua_normalizada, n_jobs, n_inds, n_swaps, eps=1e-5)

        #6.- 
        for n_ind in n_pob:
            mk, _=calcular_makespan(n_ind, tiempos, n_jobs, n_machines)
            n_ind.append(mk)

        mk, _=calcular_makespan(ind_modelo, tiempos, n_jobs, n_machines)
        hist_modelo.append((mk-pob[0][-1])/(pob[-1][-1]-pob[0][-1]))

        for i in n_pob:
            pob.append(i)

        pob=sorted(pob, key=lambda col: col[-1])

        historial.append(pob[0][-1])
        
        entropias.append(getCurrentEntropy(pob[:n_inds], n_jobs))
        dists, prom, desvest=todas_las_distancias(pob[:n_inds], n_jobs)
        distancias_promedio.append(prom)
        #7.-
        t+=1

    mejor_encontrado=pob[0][-1]

    return {"Mejor previo":       mejor_previo, 
            "Mejor encontrado":   mejor_encontrado, 
            "Diferencia":         mejor_previo-mejor_encontrado, 
            "Historial":          historial, 
            "Calidad del modelo": hist_modelo, 
            "Variedad":           distancias_promedio,
            "Entropia":           entropias, 
            "Poblacion":          pob}

def EDA_incremental_build(pob, 
                          n_iters, 
                          n_inds, 
                          n_jobs, 
                          n_machines, 
                          porcentaje_poblacion, 
                          n_bins, 
                          bins_simetricos, 
                          eps_valor=0.0, 
                          gamma_maximo=30.0, 
                          k_gamma=0.1, 
                          limites_bins=[0.0, 0.05, 0.1,  0.25, 0.4, 0.7, 1.0],
                          scores=[1.0, 1.0, 0.25, 1.0], 
                          verbose=0, 
                          tiempos=None):
    #2.-
    t=0
    historial=[pob[0][-1]]
    mejor_previo=pob[0][-1]
    hist_modelo=[]
    distancias_promedio=[]
    entropias=[]

    mat_dists_inicial, mean_inicial, std_inicial=todas_las_distancias(pob, n_jobs)

    eps=[eps_valor for i in range(n_iters)]
    gamma=f_exp_dos_puntos(np.arange(0.0, gamma_maximo, gamma_maximo/n_iters), 0.0, 0.0, gamma_maximo, gamma_maximo, k_gamma)
    


    while(t<n_iters):
        if(verbose!=0): 
            if(t%verbose==0):
                print(t)
        
        #generando bins
        if bins_simetricos==False:
            bins=[[i for i in range(int(limites_bins[j-1]*(n_inds*porcentaje_poblacion)), int(limites_bins[j]*(n_inds*porcentaje_poblacion)), 1)] for j in range(1, len(limites_bins), 1)]
        
            #4.- 
            ranking_informacion_mutua_normalizada, informacion_mutua_normalizada, bins=modelo_precedencias(pob[:min(n_inds, 500)], len(bins), bins)
        else:
            #4.- 
            ranking_informacion_mutua_normalizada, informacion_mutua_normalizada, bins=modelo_precedencias(pob[:n_inds], n_bins)

        #5.-
        n_pob, ind_modelo, base=incremental_build(ranking_informacion_mutua_normalizada, 
                                                  n_jobs, 
                                                  n_inds, 
                                                  eps=eps[t], 
                                                  gamma=gamma[t], 
                                                  scores=scores)
        
        #6.- 
        for n_ind in n_pob:
            mk, _=calcular_makespan(n_ind, tiempos, n_jobs, n_machines)
            n_ind.append(mk)

        mk, _=calcular_makespan(ind_modelo, tiempos, n_jobs, n_machines)
        hist_modelo.append((mk-pob[0][-1])/(pob[-1][-1]-pob[0][-1]))

        for i in n_pob:
            pob.append(i)

        #for i in range(len(pob)):
            #pob[i]=RLS(pob[i], ind_modelo, 5, n_jobs, n_machines, tiempos, iter=0, n_iters=0, verbose=False)

        pob=sorted(pob, key=lambda col: col[-1])

        historial.append(pob[0][-1])
        
        entropias.append(getCurrentEntropy(pob[:n_inds], n_jobs))
        dists, prom, desvest=todas_las_distancias(pob[:n_inds], n_jobs)
        distancias_promedio.append(prom)
        #7.-
        t+=1

    mejor_encontrado=pob[0][-1]

    return {"Mejor previo":       mejor_previo, 
            "Mejor encontrado":   mejor_encontrado, 
            "Diferencia":         mejor_previo-mejor_encontrado, 
            "Historial":          historial, 
            "Calidad del modelo": hist_modelo, 
            "Variedad":           distancias_promedio,
            "Entropia":           entropias, 
            "Poblacion":          pob}

#programa-------------------------------------------------------------------------------------

if __name__=="__main__":

    tipo_de_sampleo = int(sys.argv[1])
    n_swaps = int(sys.argv[2])
    inst = str(sys.argv[3])
    n_inds = int(sys.argv[4])
    n_iters = int(sys.argv[5])
    n_intentos = int(sys.argv[6])
    nombre_base = str(sys.argv[7])

    reses=[]
    
    for i in range(n_intentos):
        instancia=cargar_pfs_go(dict_ubicaciones[inst])
        pfssp_taillard=pfssp(n_jobs=len(instancia), n_machines=len(instancia[0]), n_inds=n_inds, tiempos=np.array(instancia, dtype=int), poblacion=[])
        pfssp_taillard.inicializar_poblacion(cant=n_inds)
        pob=pfssp_taillard.poblacion
        pob=sorted(pob, key=lambda col: col[-1])

        n_jobs=pfssp_taillard.n_jobs
        porcentaje_poblacion=0.7
        n_bins=10
        bins_simetricos=True

        if(tipo_de_sampleo==0):
            dict_res_rank=EDA_random_swap(pob, 
                                          n_iters, 
                                          n_inds, 
                                          n_jobs,
                                          pfssp_taillard.n_machines, 
                                          n_swaps, 
                                          porcentaje_poblacion, 
                                          n_bins, 
                                          bins_simetricos, 
                                          limites_bins=[0.0, 0.05, 0.1,  0.25, 0.4, 0.7, 1.0], 
                                          verbose=0, 
                                          tiempos=pfssp_taillard.tiempos)

        elif(tipo_de_sampleo==1):
            dict_res_rank=EDA_rank_swap(pob, 
                                        n_iters, 
                                        n_inds, 
                                        n_jobs, 
                                        pfssp_taillard.n_machines, 
                                        porcentaje_poblacion, 
                                        n_bins, 
                                        bins_simetricos, 
                                        n_swaps, 
                                        limites_bins=[0.0, 0.05, 0.1,  0.25, 0.4, 0.7, 1.0], 
                                        verbose=0, 
                                        tiempos=pfssp_taillard.tiempos)
        
        else:
            dict_res_rank=EDA_incremental_build(pob, 
                                    n_iters, 
                                    n_inds, 
                                    n_jobs, 
                                    pfssp_taillard.n_machines, 
                                    porcentaje_poblacion, 
                                    n_bins, 
                                    bins_simetricos, 
                                    eps_valor=0.5, 
                                    gamma_maximo=20.0, 
                                    k_gamma=0.2, 
                                    limites_bins=[0.0, 0.05, 0.1,  0.25, 0.4, 0.7, 1.0],
                                    scores=[1.0, 1.0, 0.0, 0.0], 
                                    verbose=0, 
                                    tiempos=pfssp_taillard.tiempos)
            
        reses.append(dict_res_rank)

        nombre=nombre_base+"_"+str(i)+".png"
        ver_metricas(dict_res_rank, nombre)

        nombre="./resultados/text/base_"+inst+"_"+str(i)+".txt"
        with open(nombre, "w") as f:
            
            f.write(f"Mejor previo {dict_res_rank['Mejor previo']} \n")
            f.write(f"Mejor encontrado {dict_res_rank['Mejor encontrado']}\n")
            f.write(f"Diferencia {dict_res_rank['Diferencia']}\n")
            f.write("Historial\n")
            for j in range(len(dict_res_rank["Historial"])):
                f.write(f"{dict_res_rank['Historial'][j]}, ")

            f.write("Historial\n")
            for j in range(len(dict_res_rank["Historial"])):
                f.write(f"{dict_res_rank['Historial'][j]}, ")

            f.write("Calidad del modelo\n")
            for j in range(len(dict_res_rank["Calidad del modelo"])):
                f.write(f"{dict_res_rank['Calidad del modelo'][j]}, ")

            f.write("Variedad\n")
            for j in range(len(dict_res_rank["Variedad"])):
                f.write(f"{dict_res_rank['Variedad'][j]}, ")

            f.write("Entropia\n")
            for j in range(len(dict_res_rank["Entropia"])):
                f.write(f"{dict_res_rank['Entropia'][j]}, ")
                
            f.write("Poblacion\n")
            for j in range(len(dict_res_rank["Poblacion"])):
                for k in range(len(dict_res_rank["Poblacion"][j])):
                    f.write(f"{dict_res_rank['Poblacion'][j][k]}, ")
                f.write(f"\n")
            