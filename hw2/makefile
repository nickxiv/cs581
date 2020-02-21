hw2: hw2.c
        gcc hw2.c -o hw2

hw2p2: hw2p2.c
        gcc hw2p2.c -o hw2p2

hw2B: hw2B.c
        gcc hw2B.c -o hw2B        

instant: hw2.c
	gcc hw2.c -o hw2
	
	./hw2 64
	./hw2 128
	./hw2 256

fast: hw2.c
	gcc hw2.c -o hw2
	
	./hw2 64
	./hw2 128
	./hw2 256
	./hw2 512

all: hw2.c
	gcc hw2.c -o hw2
	
	./hw2 64
	./hw2 128
	./hw2 256
	./hw2 512
	./hw2 1024
	./hw2 2048



submitp1: hw2.c
        gcc hw2.c -o hw2 
        sbatch hw2.job

submitp2: hw2p2.c
        gcc hw2p2.c -o hw2p2
        gcc hw2p2.c -o hwp2O0 -O0
        gcc hw2p2.c -o hwp2O1 -O1
        gcc hw2p2.c -o hwp2O2 -O2
        gcc hw2p2.c -o hwp2O3 -O3
        sbatch hw2p2.job

submitB: hw2B.c
        gcc hw2B.c -o hw2B
        sbatch hw2B.job

submitall: hw2.c hw2p2.c hw2B.c
        sbatch hw2.job
        sbatch hw2B.job
        sbatch hw2p2.job

clean:
        rm -f *.out
        rm -f *.error
        rm -f hw2
        rm -f hw2p2