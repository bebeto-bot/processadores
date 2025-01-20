#include <cstdlib>
#include <iostream>
#include "neander.hpp"

int main(int argc, char *argv[]) {


Neander processor;
  
/*
2+3=
2 = REGISTRADOR 15
3 = REGISTRADOR 23
LDA 15(CARREGA)
ADD 23(soma do acumulador)
STA 25(CARREGA O ACUMULADOR NA MEMORIA)
NOP (para o programa)
*/

processor.lertudo("str.txt");
processor.selecao();
processor.print_UnitControl();
processor.printState();

    return 0;
}
