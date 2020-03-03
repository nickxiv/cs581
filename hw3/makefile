sieve1: sieve1.c
	mpicc -o sieve1 sieve1.c -lm

submit1: sieve1.c
	mpicc -o sieve1 sieve1.c -lm
	sbatch sieve1-32.job
	sbatch sieve1-64.job
	sbatch sieve1-128.job

submit2: sieve2.c
	mpicc -o sieve2 sieve2.c -lm
	sbatch sieve2-32.job
	sbatch sieve2-64.job
	sbatch sieve2-128.job

submit3: sieve3.c
	mpicc -o sieve3 sieve3.c -lm
	sbatch sieve3-32.job
	sbatch sieve3-64.job
	sbatch sieve3-128.job

clean: 
	rm *out
	rm *error
	rm sieve1
	rm sieve2
	rm sieve3
