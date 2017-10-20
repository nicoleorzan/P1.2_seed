D3-hands-on-and-exercise
=========================


hands-on tools 
=============================

please download all codes and play with them 


Exercise 0
===========

execute and take times of all the implementations provided in directory loop_optimization

Exercise 1
============

profile the code provide (distribute particle), identify the hotspot and start thinking how to optimize


Exercise 2:  download a code and then profile it by means of gprof
===================================================================

A code you should become familiar during this course is hpl benchmark.
You can get it here:  http://www.netlib.org/benchmark/hpl/
So download it, try to compile it and then make a simple run 

once done this try to profile the code::

 - gcc –[my.optimizations] –pg –o myprogram.x myprogram.c

Note: don’t u se the option –p. It provides less information than –pg.After that, run your program normally. Profiling infos will be written in the file gmon-out. 
 
You can read (read the man pages for options and details) the informations bygprof myprogram.x
You can visualize the call graph by (read the man pages…)::

 gprof myprogram.x | gprof2dot.py | dot –T png –o callgraph.png 

Once produced the png with the call tree and push it the master branch of your fork 


