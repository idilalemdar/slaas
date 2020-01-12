This is the term project of CENG713 Evolutionary Computing course. 
I tried to reimplement the research conducted in the paper "Slice as an Evolutionary Service: Genetic Optimization for Inter-Slice Resource Management in 5G Networks", which can be found in the papers folder as main.pdf.
To run the program on a Unix machine, run:

make \
./main n c1 c2 u1 u2

where: \
n = number of experiment \
c1 = cost of slice type 1 \
c2 = cost of slice type 2 \
u1 = utility of slice type 1 \
u2 = utility of slice type 2 \

The experiment results will be reported in a file expn_report.txt, where n is the experiment number.
The Poisson and exponential distribution parameters are #define'd in the main.cpp files. 
If you want to try with different parameters, change those values, recompile and rerun the program.
