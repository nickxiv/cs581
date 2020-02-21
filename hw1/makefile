hw1: hw1.c
	gcc hw1.c -o hw1
        

instant: hw1.c
	gcc hw1.c -o hw1
	
	./hw1 64
	./hw1 128
	./hw1 256

fast: hw1.c
	gcc hw1.c -o hw1
	
	./hw1 64
	./hw1 128
	./hw1 256
	./hw1 512

all: hw1.c
	gcc hw1.c -o hw1
	
	./hw1 64
	./hw1 128
	./hw1 256
	./hw1 512
	./hw1 1024
	./hw1 2048

submit: hw1.c
	gcc hw1.c -o hw1 
	sbatch hw1.job
