#!/usr/bin/env python

from math import sqrt


medie = open("medie.txt","w")
erro = open("err.txt","w")
seq = [1024,2048,4096]
for k in seq:	
    n=0
    somma=0.0
    err=0.0
    #medie.write('media (12 prove) per matrice di dim'+str(k))
    #medie.write('\n')
    with open('cleanmiss'+str(k)+'m') as file:
        for line in file:
            somma+=float(line)
            n+=1
        somma=somma/n
        medie.write(str(somma))
	medie.write('\n')
 	
    #medie.write('dev standard (12 prove) per matrice di dim'+str(k))
    #medie.write('\n')
    with open('cleanmiss'+str(k)+'m') as file:
        for line in file:
            err+=(float(line)-somma)*(float(line)-somma)
        err = (1./(n-1.))*sqrt(err)
        print err
        erro.write(str(err))
	erro.write('\n')
medie.close()
erro.close()

