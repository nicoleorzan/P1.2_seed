#!/usr/bin/env python

from math import sqrt


medie = open("medie.txt","w")
errfile = open("err.txt","w")	
n=0
somma=0.0
err=0.0
with open('allnode') as file:
    for line in file:
        somma+=float(line)
        n+=1
    somma=somma/n
    medie.write(str(somma))
    medie.write('\n')
 	

with open('allnode') as file:
    for line in file:
        err+=(float(line)-somma)*(float(line)-somma)
    err = (1./(n-1.))*sqrt(err)
    print err
    errfile.write(str(err))
    errfile.write('\n')
    
medie.close()
errfile.close()

