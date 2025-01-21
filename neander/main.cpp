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
std::cout << "SUBTRAÇÃO:" << std::endl;
processor.zerar();
processor.lertudo("sub.txt");
processor.selecao();
std::cout << std::endl << std::endl << std::endl;
std::cout << "SOMA:" << std::endl;
processor.zerar();
processor.lertudo("str.txt");
processor.selecao();
    return 0;
}
