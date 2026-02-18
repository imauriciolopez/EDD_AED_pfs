#importando librerias

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from matplotlib.patches import Patch
import math
import seaborn as sns
import sys

#declarando clase

class experimento:
    def __init__(self, experimento_=0, tipo_='D', instancia_=0, n_inds_=1, n_its_=1, cruza_="SHADE", mu_=0.5, 
                 c_r_=0.5, p_=0.5, neh_=0.5, d_=10, reemplazos_=0, extra_="1", promedios_=[], desvest_=[],diff_proms_=[], 
                 diff_desvest_=[], mejores_=[], mejor_=10000, estado_="desconocido", performance_=0):
        self.inds=[]
        self.mejor_it=[]
        self.promedios_it=[]
        self.desvest_it=[]
        self.promedios_diff_it=[]
        self.desvest_diff_it=[]
        self.experimento=experimento_
        self.tipo=tipo_
        self.instancia=instancia_
        self.n_inds=n_inds_
        self.n_its=n_its_
        self.cruza=cruza_
        self.mu=mu_
        self.c_r=c_r_
        self.p=p_
        self.neh=neh_
        self.d=d_
        self.reemplazos=reemplazos_
        self.extra=extra_
        self.promedios=promedios_ if promedios_ is None else promedios_
        self.desvest=desvest_ if desvest_ is None else desvest_
        self.diff_proms=diff_proms_ if diff_proms_ is None else diff_proms_
        self.diff_desvest=diff_desvest_ if diff_desvest_ is None else diff_desvest_
        self.mejores=mejores_ if mejores_ is None else mejores_
        self.mejor=mejor_
        self.estado=estado_
        self.performance=performance_
    
    def ver(self):
        print(self.estado, self.experimento, self.tipo, self.instancia, self.n_inds,
              self.n_its, self.cruza, len(self.promedios), len(self.desvest), 
              len(self.diff_proms), len(self.diff_desvest), self.mu, self.c_r, 
              self.p, self.neh, self.d, self.extra, self.mejor)
        
#archivo txt con el plan de los experimentos
localidad_file_entrada=sys.argv[1]
#carpeta donde se encuentran los resultados en txt después de correr los programas
carpeta_resultados=sys.argv[2]
#carpeta donde se guardarán las gráficas ya creadas
donde_guardar_graficas=sys.argv[3]

#leyendo experimentos
file_entrada=open(localidad_file_entrada, "r")
partes=file_entrada.readline().split()
n_experimentos=partes[3]

linea=file_entrada.readline()
linea=file_entrada.readline()
experimentos=[]
i=0
for line in file_entrada:
    if line!="\n" and i<int(n_experimentos):
        partes=line.split()
        experimentos.append(experimento(experimento_=i,
                                        tipo_=partes[0], 
                                        instancia_=int(partes[1]), 
                                        n_inds_=int(partes[2]), 
                                        n_its_=int(partes[3]), 
                                        cruza_=partes[4],
                                        mu_=float(partes[5]), 
                                        c_r_=float(partes[6]), 
                                        p_=float(partes[7]), 
                                        reemplazos_=float(partes[8]), 
                                        d_=int(partes[9]),
                                        neh_=float(partes[10]), 
                                        extra_=partes[11]))
        i+=1
    
file_entrada.close()    

verbose=2
n_exps_por_inst=5

for a in experimentos:
    try:
        localidad_file_resultados=carpeta_resultados+f"/exp_{a.experimento}.txt"
        file_experimentos=open(localidad_file_resultados, "r")
    except:
        a.estado="no encontrado"

    if a.estado=="desconocido":
        line=file_experimentos.readline()

        for it in range(int(a.n_its/verbose)):
            line=file_experimentos.readline()
            partes=line.split()
            if(len(partes)!=6):
                a.estado="no terminado"
                break
            else:
                a.mejor_it.append(int(partes[1]))
                a.promedios_it.append(float(partes[2]))
                a.desvest_it.append(float(partes[3]))
                a.promedios_diff_it.append(float(partes[4]))
                a.desvest_diff_it.append(float(partes[5]))

        if a.estado!="no terminado":
            for ind in range(a.n_inds):
                temp=[]
                line=file_experimentos.readline()
                temp.extend(map(int, line.split(',')))
                a.inds.append(temp)

            for line in file_experimentos:
                if line=="PROMEDIOS:\n":
                    break
            
            #leyendo promedios
            line=file_experimentos.readline()
            partes=line.split()
            a.promedios=[float(p) for p in partes]

            #leyendo desvests
            line=file_experimentos.readline()
            line=file_experimentos.readline()
            partes=line.split()
            a.desvest=[float(p) for p in partes]
                
            #leyendo mejores
            line=file_experimentos.readline()
            line=file_experimentos.readline()
            partes=line.split()
            a.mejores=[int(p) for p in partes]
            
            #leyendo promedios de diferencias
            line=file_experimentos.readline()
            line=file_experimentos.readline()
            partes=line.split()
            a.diff_proms=[float(p) for p in partes]

            #leyendo desvest de diferencias
            line=file_experimentos.readline()
            line=file_experimentos.readline()
            partes=line.split()
            a.diff_desvest=[float(p) for p in partes]

            a.mejor=a.mejores[-1]

            a.estado="terminado"
            file_experimentos.close()

        else:
            file_experimentos.close()


#ver qué instancias están

instancias=[]
for a in experimentos:
    if a.estado=="terminado":
        if a.instancia not in instancias:
            instancias.append(a.instancia)

print("Las instancias incluidas en las gráfcias son: (n+1)\n", instancias)



mejores_conocidos=[1278, 1359, 1081, 1293, 1235, 1195, 1234, 1206, 1230, 1108, 
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
                   26040, 26500, 26371, 26456, 26334, 26469, 26389, 26560, 26005, 26457]



for i in range(len(instancias)):
    inst=[]
    mejor_valor_inst=experimentos[i*n_exps_por_inst].mejor
    mejor_it_=experimentos[i*n_exps_por_inst].mejor_it
    label_mejor_it=f"exp_{i*n_exps_por_inst}.txt"

    for j in range(i*n_exps_por_inst, (i+1)*n_exps_por_inst, 1):
        if experimentos[j].estado=="terminado":
            inst.append(experimentos[j].mejor_it)
            if experimentos[j].mejor<mejor_valor_inst:
                mejor_valor_inst=experimentos[j].mejor
                mejor_it_=experimentos[j].mejor_it
                label_mejor_it=f"exp_{j}.txt"
    
    datos=np.array(inst)
    media=np.mean(datos, axis=0)
    q1=np.percentile(datos, 25, axis=0)
    q3=np.percentile(datos, 75, axis=0)

    x=np.arange(datos.shape[1])  # iteraciones

    plt.plot([i*2 for i in range(datos.shape[1])], media, linewidth=1.5, color="teal", label="Valor promedio\npor iteracion")                # línea fuerte
    plt.plot([i*2 for i in range(datos.shape[1])], q1, linestyle='--', linewidth=1.5, alpha=0.5, color="teal")     # borde inferior
    plt.plot([i*2 for i in range(datos.shape[1])], q3, linestyle='--', linewidth=1.5, alpha=0.5, color="teal")     # borde superior

    plt.fill_between([i*2 for i in range(datos.shape[1])], q1, q3, alpha=0.2, color="teal", label="Cuartiles Q1 a Q3")         # zona sombreada

    plt.plot([i*2 for i in range(len(mejor_it_))], mejor_it_, linewidth=1.5, color="mediumpurple", label=label_mejor_it)

    plt.axhline(y=mejores_conocidos[i+instancias[0]], color='red', linestyle='--', linewidth=1.5, label="Mejor conocido")
  
    plt.title(f"Instancia: Ta{i+instancias[0]+1}")
    plt.xlabel("Iteraciones")
    plt.ylabel("Mejor valor encontrado")
    plt.legend(loc="upper right")
    
    filename = f"/boxplot_mejores_its_Ta{i+instancias[0]+1}.png"
    plt.savefig(donde_guardar_graficas+filename, dpi=300, bbox_inches="tight")
    plt.close()





#cargar los individuos
inds_=[[] for i in range(len(instancias))]

for i in range(len(instancias)*n_exps_por_inst):
    if experimentos[i].estado=="terminado":
        for j in range(experimentos[i].n_inds):
            inds_[int(math.floor(i/n_exps_por_inst))].append(experimentos[i].inds[j][-1]-mejores_conocidos[int(math.floor(i/n_exps_por_inst)+instancias[0])])


for i in range(len(instancias)):
    inds_[i]=np.sort(inds_[i])

 #cargar los individuos
inds=[[] for i in range(len(instancias))]

for i in range(len(instancias)*n_exps_por_inst):
    if experimentos[i].estado=="terminado":
        for j in range(experimentos[i].n_inds):
            inds[int(math.floor(i/n_exps_por_inst))].append(experimentos[i].inds[j][-1])


for i in range(len(instancias)):
    inds[i]=np.sort(inds[i])


#gráficas boxplot relativo
for i in range(0, len(instancias), 10):
    plt.figure(figsize=(8, 4))

    labels_2=[f"Ta{i+j+instancias[0]+1}" for j in range(len(inds[i:i+10]))]
    
    labels=[f"Ta{i+j+instancias[0]+1}: {inds_[i+j][0]} optimo encontrado" if inds_[i+j][0]==0 else f"Ta{i+j+instancias[0]+1}: {inds_[i+j][0]}" for j in range(len(inds[i:i+10]))]

    optimo_encontrado=False
    for j in range(len(inds[i:i+10])):
        if inds_[i+j][0]==0:
            optimo_encontrado=True
            break

    colors = ["blue", "orange", "green", "red", "purple", "brown", "pink", "gray", "olive", "cyan"]

    bp = plt.boxplot(inds_[i:i+10], tick_labels=labels_2, patch_artist=True)

    for box, c in zip(bp["boxes"], colors):
        box.set_facecolor(c)

    handles = [Patch(facecolor=c, label=l) for c, l in zip(colors, labels)]
    plt.legend(handles=handles, loc="upper right", title="Diferencia con el\n mejor conocido\n(por instancia)")
    plt.ylabel("Makespan obtenido")
    plt.title("Resultados de experimentos (relativo al mejor conocido)")
    plt.xlim(0, len(inds[i:i+10])+8 if optimo_encontrado else len(inds[i:i+10])+4)
    
    filename = f"/boxplot_relativo_Ta{i+instancias[0]}_Ta{i+len(inds[i:i+10])-1+instancias[0]}.png"
    plt.savefig(donde_guardar_graficas+filename, dpi=300, bbox_inches="tight")
    plt.close()



#-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
#graficando

#gráficas boxplot total
for i in range(0, len(instancias), 10):
    labels=[f"Ta{i+j+instancias[0]+1}" for j in range(len(inds[i:i+10]))]

    plt.figure(figsize=(8, 4))
    
    for j in range(len(inds[i:i+10])):
        plt.scatter(j+1, mejores_conocidos[i+j+instancias[0]], color="blue")

    plt.boxplot(inds[i:i+10], tick_labels=labels)

    min_len = min(len(fila) for fila in inds)
    datos_recortados = np.array([fila[:min_len] for fila in inds])

    media = np.mean(datos_recortados, axis=0)

    plt.scatter(12, media[0], color="blue", label="Mejor conocido")
    

    plt.title("Makespans por instancia")
    plt.ylabel("makespans")
    plt.xlabel("instancias")
    plt.xlim(0, 11)

    plt.legend(loc="upper right")

    filename = f"/boxplot_total_Ta{i+instancias[0]}_Ta{i+len(inds[i:i+10])-1+instancias[0]}.png"
    plt.savefig(donde_guardar_graficas+filename, dpi=300, bbox_inches="tight")
    plt.close()
