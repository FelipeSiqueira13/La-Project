CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

jogo: main.o mapa.o movimento.o obstaculo.o bau.o gerarinimigodem.o gerabau.o gerarsaida.o ativarbau.o calcdist.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm jogo *.o
