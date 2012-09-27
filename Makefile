all: fase0 fase1 fase2

fase0: fase0.c
	gcc fase0.c -o fase0

fase1: fase1.c
	gcc fase1.c -fopenmp -o fase1

fase2: fase2.c
	gcc fase2.c -fopenmp -o fase2

fase3: fase3.c
	gcc fase3.c -o fase3 -lpthread

clean:
	rm fase0 fase1 fase2 fase3