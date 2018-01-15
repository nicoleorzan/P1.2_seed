#!/usr/bin/env python
"""
Questo script riceve in input i 12 valori dei tempi impiegati dai diversi step di ottimizzazione di avoid_avoidable_(numstep) comtenuti nei file tempi_loop_(numstep), per i loop da 0 a 6, e per ognuno dei essi calcola la media dei tempi. Le medie ottenuto vengono poi scritte nel file risultati.txt

"""
from math import sqrt


risultati = open("risultati.txt","w")
seq = [0, 1, 2, 3, 4, 5, 6]
for k in seq:
     n=0
     somma=0.0
     err=0.0
     with open('tempi_loop'+str(k)) as file:
        
         for line in file:
             somma+=float(line)
             n+=1
            
         somma+=somma/n
     risultati.write(str(somma))
     risultati.write('\n')
         
print n
a = 1.0/(n-1.0)
for k in seq:
     with open('tempi_loop' + str(k)) as file:
         for line in file:
            err+=(float(line)-somma)*(float(line)-somma)
            err = sqrt(err)*a
         print err
         
    # risultati.write(str(somma))
    # risultati.write('\n')
risultati.close()



