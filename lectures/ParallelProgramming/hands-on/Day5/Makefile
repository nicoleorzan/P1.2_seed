CPP_FLAGS = -I/u/shared/programs/x86_64/mkl/11.1.3/composer_xe_2013_sp1.3.174/mkl/include 
LD_FLAGS = -L/u/shared/programs/x86_64/mkl/11.1.3/composer_xe_2013_sp1.3.174/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core
CC = mpicc 
C_FLAGS = -O3
C_FLAGS_DEBUG = -O0 -g -D__DEBUG

all: mpi_matmul_allgather.x mpi_matmul_blocks_noblocking.x

mpi_matmul_allgather.x: mpi_matmul_allgather.o
	$(CC) $(C_FLAGS) -o mpi_matmul_allgather.x mpi_matmul_allgather.o $(LD_FLAGS)

mpi_matmul_allgather.o: mpi_matmul_allgather.c
	$(CC) $(C_FLAGS) $(CPP_FLAGS) -c mpi_matmul_allgather.c

mpi_matmul_blocks_noblocking.x: mpi_matmul_blocks_noblocking.o
	$(CC) $(C_FLAGS) -o mpi_matmul_blocks_noblocking.x mpi_matmul_blocks_noblocking.o $(LD_FLAGS)

mpi_matmul_blocks_noblocking.o: mpi_matmul_blocks_noblocking.c
	$(CC) $(C_FLAGS) $(CPP_FLAGS) -c mpi_matmul_blocks_noblocking.c

debug: 
	$(CC) $(C_FLAGS_DEBUG) -o mpi_matmul_blocks_noblocking.x mpi_matmul_blocks_noblocking.c -D__DEBUG $(CPP_FLAGS) $(LD_FLAGS)
	$(CC) $(C_FLAGS_DEBUG) -o mpi_matmul_allgather.x mpi_matmul_allgather.c -D__DEBUG $(CPP_FLAGS) $(LD_FLAGS)

clean:
	rm *~ *.x *.o *.btr