#!/usr/bin/env python

from math import sqrt


medie = open("medie.txt","w")
seq = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512]
for k in seq:
     n=0
     somma=0.0
     err=0.0
     with open('output1024'+str(k)) as file:
        
         for line in file:
             somma+=float(line)
             n+=1
            
         somma+=somma/n
            
     with open('output1024' + str(k)) as file:
         for line in file:
            err+=(float(line)-somma)*(float(line)-somma)

         err = (1./(n-1.))*sqrt(err)
         print err
         
     medie.write(str(somma))
     medie.write('\n')
medie.close()

