CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

jogo: main.o movimento.o bau.o gerarinimigo.o calcdist.o gerarmapa.o vision.o cards.o combate.o movimentoinimigo.o usarpocao.o gamecontrol.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm jogo *.o
