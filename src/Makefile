CC=gcc
LIBS=-lm -lsquid 
INCLUDE=-I. 
CFLAGS=-O3

randfold: energy_par.o params.o fold.o fold_vars.o utils.o randfold.c
	$(CC) $(CFLAGS) $(INCLUDE) -o randfold params.o energy_par.o fold.o fold_vars.o utils.o randfold.c $(LIBS)

energy_par.o: energy_par.c
	$(CC) -c energy_par.c

fold.o: fold.c
	$(CC) -c fold.c

fold_vars.o: fold_vars.c
	$(CC) -c fold_vars.c

utils.o: utils.c
	$(CC) -c utils.c

params.o: params.c
	$(CC) -c params.c

clean:
	rm -f *.o randfold
