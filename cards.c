#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <string.h>

#include "cards.h"

void startcards(CARDS *cards){
    cards->commum[0].id = 0;
    strcpy(cards->commum[0].texto, "diminuir o numero de demonios");
    cards->commum[1].id = 1;
    strcpy(cards->commum[1].texto, "aumentar o numero de baus");
    cards->commum[2].id = 2;
    strcpy(cards->commum[2].texto, "recuperar vida");
    cards->commum[3].id = 3;
    strcpy(cards->commum[3].texto, "aumentar o numero de flechas");
    cards->commum[4].id = 4;
    strcpy(cards->commum[4].texto, "aumentar o numero de poçoes de cura");
    cards->commum[5].id = 5;
    strcpy(cards->commum[5].texto,"aumentar o dano do heroi");
    cards->commum[6].id = 6;
    strcpy(cards->commum[6].texto,"aumenta a defesa do heroi");
    cards->commum[7].id = 7;
    strcpy(cards->commum[7].texto, "fazer carinho em um cachorro (voce nao ganha nada fazendo isso, confia)");
    cards->commum[8].id = 8;
    strcpy(cards->commum[8].texto, "diminuir o numero de fantasmas");

    cards->rare[0].id = 9;
    strcpy(cards->rare[0].texto, "aumentar a vida maxima"); 
    cards->rare[1].id = 10;
    strcpy(cards->rare[1].texto,"aumenta bastante o ataque"); 
    cards->rare[2].id = 11;
    strcpy(cards->rare[2].texto, "melhorar arco"); 
    cards->rare[3].id = 12;
    strcpy(cards->rare[3].texto, "diminuir numero de vampiros"); 
    cards->rare[4].id = 13;
    strcpy(cards->rare[4].texto, "ganhar agua benta");  
}

void callACard(PLAYER *st, CONTROL *gamecontrol, CARDS cards){
    CARD options[3];
    for(int i = 0; i <= 2; i++){
        int raridade = rand() % 10, cardn;
        
        if(raridade == 0){
            cardn = rand() % 5;
            options[i] = cards.rare[cardn];
        }else{
            cardn = rand() % 9;
            options[i] = cards.commum[cardn];
        }
    }

    int pass = 0;
    for(int j = 0; j <= 2 ; j++){
        if(options[j].id < 9){
            attron(COLOR_PAIR(COLOR_BLUE));
                printw("opçao %d: %s \n",j+1 ,options[j].texto);
            attroff(COLOR_PAIR(COLOR_BLUE));
        }else{
            attron(COLOR_PAIR(COLOR_MAGENTA));
                printw("opçao %d: %s \n",j+1 ,options[j].texto);
            attroff(COLOR_PAIR(COLOR_MAGENTA));
        }
    }
    
    while(pass == 0){
        int key = getch();
        switch (key){
            case '1':
                activecard(options[0].id,st, gamecontrol);
                pass = 1;
                break;

            case '2':
                activecard(options[1].id,st, gamecontrol);
                pass = 1;
                break;
                
            case '3':
                activecard(options[2].id,st, gamecontrol);
                pass = 1;
                break;
        }
    }
}

void activecard(int id, PLAYER *st, CONTROL *gamecontrol){
    if(id == 0) gamecontrol->qntdem -= 5;
    if(id == 1) gamecontrol->bauspawn += 2;
    if(id == 2) st->vida = st->vidamaxima;
    if(id == 3) st->flechas += 15;
    if(id == 4) st->pocoesvida += 3;
    if(id == 5) st->ataqueespada += 2;
    if(id == 6) st->defesa += 1;
    if(id == 7) gamecontrol->carinhos++;
    if(id == 8) gamecontrol->qntfnt -= 5;
    if(id == 9) st->vidamaxima += 50;
    if(id == 10)st->danoespada += 7;
    if(id == 11) st->ataquearco += 5;
    if(id == 12) gamecontrol->qntvam -= 3;
    if(id == 13) st->aguabenta += 2;
}