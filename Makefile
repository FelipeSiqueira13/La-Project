CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

jogo: main.o movimento.o bau.o gerarinimigo.o calcdist.o gerarmapa.o vision.o iniciarcontrol.o cards.o combatemonstro.o combateplayer.o movimentoinimigo.o usarpocao.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm jogo *.o
