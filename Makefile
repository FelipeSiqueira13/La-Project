CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

jogo: main.o mapa.o movimento.o obstaculo.o bau.o gerarinimigodem.o gerabau.o gerarsaida.o ativarbau.o gerarinimigofant.o calcdist.o gerarmapa.o vision.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm jogo *.o
