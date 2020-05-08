CC=gcc
CFLAGS=-O3 -fPIC -march=native -pipe
CFLAGS_OMP=-O3 -fPIC -march=native -fopenmp -pipe

all: serial openmp

openmp: knn_openmp.o sort.o mnist.o util.o
	$(CC) $(CFLAGS_OMP) -o knn_openmp knn_openmp.o sort.o mnist.o util.o

serial: knn_serial.o sort.o mnist.o util.o
	$(CC) -o knn_serial knn_serial.o sort.o mnist.o util.o

knn_openmp.o: knn_openmp.c
	$(CC) $(CFLAGS_OMP) -c knn_openmp.c

knn_serial.o: knn_serial.c
	$(CC) $(CFLAGS) -c knn_serial.c

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c

mnist.o: mnist.c
	$(CC) $(CFLAGS) -c mnist.c

util.o: util.c
	$(CC) $(CFLAGS) -c util.c

clean:
	rm knn_openmp knn_serial *.o
