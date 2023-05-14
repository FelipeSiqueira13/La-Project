#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#include "iniciarcontrol.h"

void iniciarcontrol(CONTROL *controlo){
    controlo->nivel = 1;
    controlo->bauspawn = 3;
    controlo->qntdem = 4;
    controlo->qntfnt = 2;
    controlo->qntvmp = 0;
}