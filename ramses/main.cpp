#include <iostream>
#include <iomanip>
#include <vector>

#include "ramses.hpp"

/*class Registrador {
public:
    int valor;
    Registrador() : valor(0) {}
    void setValor(int v) { valor = v; }
    int getValor() { return valor; }
};

class ControlUnit {
public:
    bool cargaRA, cargaRB, cargaRX, cargaPC, incrementaPC, cargaRI, cargaREM, cargaRDM, write, read;
    bool s1, s2, s3, s4, s5, s6, s7, cargaNZ, cargaC, selUAL;

    ControlUnit() : cargaRA(false), cargaRB(false), cargaRX(false), cargaPC(false), incrementaPC(false), cargaRI(false), 
                    cargaREM(false), cargaRDM(false), write(false), read(false), s1(false), s2(false), s3(false), s4(false),
                    s5(false), s6(false), s7(false), cargaNZ(false), cargaC(false), selUAL(false) {}
};

class ULA {
public:
    int x, y, resultado;

    ULA() : x(0), y(0), resultado(0) {}

    void operar(int operacao) {
        switch (operacao) {
            case 0:  // Soma
                resultado = x + y;
                break;
            case 1:  // Subtração
                resultado = x - y;
                break;
            case 2:  // AND
                resultado = x & y;
                break;
            case 3:  // OR
                resultado = x | y;
                break;
            case 4:  // NOT
                resultado = ~x;
                break;
            default:
                resultado = 0;
                break;
        }
    }
};

class Memoria {
public:
    std::vector<int> memory;
    Memoria() : memory(256, 0) {}
    
    int ler(int endereco) {
        return memory[endereco];
    }

    void escrever(int endereco, int valor) {
        memory[endereco] = valor;
    }
};

class ProcessadorRamses {
private:
    Registrador RA, RB, RX, RI, PC, REM, RDM, NZ, C;
    ControlUnit UC;
    ULA ula;
    Memoria mem;
    
public:
    ProcessadorRamses() {
        PC.setValor(0);
        REM.setValor(0);
        RDM.setValor(0);
        NZ.setValor(0);
        C.setValor(0);
    }

    // Micro-instruções para a execução das instruções do processador Ramsés

    void LDR(int endereco) {
        UC.cargaREM = 1;
        UC.s1 = 0; // seleciona o endereço de PC
        UC.incrementaPC = 1;
        UC.read = 1;
        RDM.setValor(mem.ler(endereco));
        UC.cargaRB = 1;
        RB.setValor(RDM.getValor());
    }

    void ADD(int valor) {
        UC.s1 = 1; // Seleciona RA
        UC.s2 = 0; // Seleciona valor imediato
        UC.selUAL = 0; // Operação de soma
        ula.x = RA.getValor();
        ula.y = valor;
        ula.operar(0);
        RA.setValor(ula.resultado);
    }

    void ADD_Rx(int valor) {
        UC.s1 = 1; // Seleciona RX
        UC.s2 = 0; // Seleciona valor imediato
        UC.selUAL = 0; // Operação de soma
        ula.x = RX.getValor();
        ula.y = valor;
        ula.operar(0);
        RX.setValor(ula.resultado);
    }

    void STR() {
        UC.cargaREM = 1;
        UC.s1 = 0;
        UC.write = 1;
        mem.escrever(REM.getValor(), RX.getValor());
    }

    void SUB(int valor) {
        UC.s1 = 1; // Seleciona RB
        UC.s2 = 0; // Seleciona valor imediato
        UC.selUAL = 1; // Operação de subtração
        ula.x = RB.getValor();
        ula.y = valor;
        ula.operar(1);
        RB.setValor(ula.resultado);
    }

    void AND(int valor) {
        UC.s1 = 1; // Seleciona RB
        UC.s2 = 0; // Seleciona valor imediato
        UC.selUAL = 2; // Operação AND
        ula.x = RB.getValor();
        ula.y = valor;
        ula.operar(2);
        RB.setValor(ula.resultado);
    }

    void OR(int valor) {
        UC.s1 = 1; // Seleciona RX
        UC.s2 = 0; // Seleciona valor imediato
        UC.selUAL = 3; // Operação OR
        ula.x = RX.getValor();
        ula.y = valor;
        ula.operar(3);
        RX.setValor(ula.resultado);
    }

    void NOT() {
        UC.s1 = 1; // Seleciona RX
        UC.selUAL = 4; // Operação NOT
        ula.x = RX.getValor();
        ula.operar(4);
        RX.setValor(ula.resultado);
    }

    void JMP(int endereco) {
        PC.setValor(endereco);
    }

    void JZ(int endereco) {
        if (NZ.getValor() == 0) {
            PC.setValor(endereco);
        }
    }

    void JSR(int endereco) {
        int retorno = PC.getValor() + 1;
        mem.escrever(retorno, RDM.getValor());  // Armazena o retorno na pilha
        PC.setValor(endereco);
    }

    void execucao(int instrucao, int endereco) {
        switch (instrucao) {
            case 1: LDR(endereco); break;
            case 2: ADD(endereco); break;
            case 3: ADD_Rx(endereco); break;
            case 4: STR(); break;
            case 5: SUB(endereco); break;
            case 6: AND(endereco); break;
            case 7: OR(endereco); break;
            case 8: NOT(); break;
            case 9: JMP(endereco); break;
            case 10: JZ(endereco); break;
            case 11: JSR(endereco); break;
            default: std::cerr << "Instrução desconhecida!" << std::endl; break;
        }
    }

    void imprimirEstado() {
        std::cout << "PC: " << PC.getValor() << " | RA: " << RA.getValor() << " | RB: " << RB.getValor() << std::endl;
        std::cout << "RX: " << RX.getValor() << " | RI: " << RI.getValor() << " | REM: " << REM.getValor() << std::endl;
        std::cout << "RDM: " << RDM.getValor() << std::endl;
    }

    void carregarMemoria() {
        mem.memory[12] = 1;  // Exemplo: instrução de LDR
        mem.memory[20] = 2;  // Exemplo: instrução de ADD
        mem.memory[50] = 5;  // Exemplo: instrução de SUB
    }

    void executarPrograma() {
        carregarMemoria();
        execucao(1, 12);  // LDR (carregar RB)
        execucao(2, 10);  // ADD (adicionar valor imediato)
        imprimirEstado();
    }
};

/*int main() {
    ProcessadorRamses processador;
    processador.executarPrograma();
    return 0;
}*/

int main(int argc, char *argv[]) {


Ramses processor;

std::cout << "SUBTRAÇÃO:" << std::endl;
processor.zerar();
processor.lertudo("sub.txt");
processor.selecao();
std::cout << std::endl << std::endl << std::endl;
std::cout << "SOMA:" << std::endl;
processor.zerar();
processor.lertudo("str.txt");
processor.selecao();
processor.printMemory();
std::cout << "Valor máximo da memória: " << processor.findMaxMemoryValue() << std::endl;
    return 0;

}