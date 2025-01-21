#include <cstdint>
#include <iostream>
#include <iomanip>
#include "AC.hpp"
#include "PC.hpp"
#include "RDM.hpp"
#include "REM.hpp"
#include "RI.hpp"
#include "ULA.hpp"
#include "control_unit.hpp"
#include "memoria.hpp"
#include "NCZ.hpp"
#include "AC1.hpp"
#include "AC2.hpp"
#include <vector> 
#include <string>
#include <fstream>


class Ramses {
private:

  AC ac;
  AC1 ac1;
  AC2 ac2;
  PC pc;
  RDM rdm;
  REM rem;
  RI ri;
  ControlUnit uc;
  ULA ula;
  NZC nzc;
  memoria mem;
  int index;
public:
  Ramses(){
    ac.ac = 0;
ac1.ac1 = 0;
ac2.ac2 = 0; 
    pc.pc = 0;
    rdm.dado = 0;
    rem.adress = 0;
    ri.ri = 0;
    ula.y = 0;
    ula.x = 0;
    nzc.N = 0;
    nzc.Z = 0;
    nzc.carry=0;
    nzc.result = 0;
    uc.carga_ac=0;
    uc.s1 = 0;
    uc.s2 = 0;
    uc.s3 = 0;
    uc.s4 = 0;
    uc.s5 = 0;
    uc.s6 = 0;
    uc.sel_ula=0;
    uc.carga_nz=0;
    uc.carga_pc=0;
    uc.carga_rem=0;
    uc.carga_ri=0;
    uc.incrementa_pc=0;
    uc.read=0;
    uc.write=0;  
    for(int i = 0;i<mem.memory.size();i++)
    mem.memory[i]=0;
  }
  void operatio() {
    if (uc.sel_ula == 0) {
      nzc.result = ula.x + ula.y;
    } else if (uc.sel_ula == 1) {
      nzc.result = ula.x and ula.y;
    } else if (uc.sel_ula == 2) {
      nzc.result = ula.x or ula.y;
    } else if (uc.sel_ula == 3) {
      nzc.result = ula.y;
    }
    else if(uc.sel_ula==4){
      nzc.result = -ula.x-1;
    }
    else if(uc.sel_ula==5){
        nzc.result=ula.x-ula.y;
    }
  }
  void mux() {
    uc.carga_rem = 1;
    if (uc.s3 == false) {
      rem.adress = pc.pc;
    } else if (uc.s4 == false) {
      rem.adress = rdm.dado;
    }
    else{
        rem.adress=ac.ac;
    }
    uc.carga_rem = 0;
  }
  void mux1(){
    if(uc.s1==false and uc.s2==false){
        ula.x = ac.ac;
    }
    else if(uc.s1==false and uc.s2==true){
        ula.x = ac1.ac1;
    }
    else if (uc.s1==true and uc.s2==false){
        ula.x = ac2.ac2;
    }
    else{
        ula.x=pc.pc;
    }
  }
  void mux2(){
    if(uc.s5==false){
        pc.pc=rem.adress;
    }
    else if(uc.s5){
        pc.pc=ac.ac;
    }
    }
  
  void selecao() {
    busca();
    if (ri.ri == 00) { 
      std::cout << "NOP" << std::endl;
      printState();
      print_UnitControl();
      selecao();
    } else if (ri.ri == 32) { // LDR
      std::cout << "LDR" << std::endl;
      exec_LDR();
      selecao();
    } else if (ri.ri == 48) { // ADD
      std::cout << "ADD" << std::endl;
      exec_ADD();
      selecao();
    } else if (ri.ri == 16) { // STR
      std::cout << "STR" << std::endl;
      exec_STR();
      selecao();
    } else if (ri.ri == 240) { // HLT
      std::cout << "HLT" << std::endl;
      printState();
      print_UnitControl();
    } else if (ri.ri == 96) { // NOT
      std::cout << "NOT" << std::endl;
      exec_NOT();
      selecao();
    } else if (ri.ri == 128) { // JMP
      std::cout << "JMP" << std::endl;
      exec_JMP();
      selecao();
    } else if (ri.ri == 144) { // JN
      std::cout << "JN" << std::endl;
      exec_JN();
      selecao();
    } else if (ri.ri == 160) { // JZ
      std::cout << "JZ" << std::endl;
      exec_JZ();
      selecao();
    } else if (ri.ri == 112) { // SUB
      std::cout << "SUB" << std::endl;
      exec_SUB();
      selecao(); }else if (ri.ri == 176) { // JC
      std::cout << "JC" << std::endl;
      exec_JC();
      selecao();
    } else if (ri.ri == 192) { // JSR
      std::cout << "JSR" << std::endl; 
      selecao();
    } else {
      std::cerr << "Instrução inválida: " << ri.ri << std::endl;
    }
  }

void exec_JC() {
    if (nzc.carry) {  // Verifica se a flag Carry está ativada
        exec_JMP();  // Se Carry estiver ativo, faz o salto
    } else {
        increment_PC();  // Caso contrário, incrementa o PC
    }
    printState();
    print_UnitControl();
}
  void exec_LDR() {
   
    mux();
    increment_PC();
    read();
    uc.s3 = 1;
    mux();
    uc.s3 = 0;
    read();
    uc.carga_ac = 1;
    ac.ac = rdm.dado;
    uc.carga_ac = 0;
    printState();
    print_UnitControl();
  }

  void exec_ADD() {
   
    mux();
    increment_PC();
    read();
    uc.s3 = 1;
    mux();
    uc.s3 = 0;
    read();
    ula.y = rdm.dado;
    ula.x = ac.ac;
    uc.sel_ula = 0;
    operatio();
    uc.carga_nz = 1;
    operation();
    ac.ac = nzc.result;
    uc.carga_nz = 0;
    printState();
    print_UnitControl();
  }

  void exec_STR() {
    
    mux();
    increment_PC();
    read();
    uc.s3 = 1;
    mux();
    uc.s3 = 0;
    uc.write = 1;
    rdm.dado = ac.ac;
    write();
    uc.write = 0;
    printState();
    print_UnitControl();
  }

  void exec_NOT() {
    uc.sel_ula = 4;
    ula.x=ac.ac;
    operatio();
    ac.ac = nzc.result;
    printState();
    print_UnitControl();
  }

  void exec_JMP() {
    
    mux();
    increment_PC();
    read();
    pc.pc = rdm.dado;
    printState();
    print_UnitControl();
  }

  void exec_JN() {
    if (nzc.N) {
      exec_JMP();
    } else {
      increment_PC();
      printState();
      print_UnitControl();
    }
  }

  void exec_JZ() {
    if (nzc.Z) {
      exec_JMP();
    } else {
      increment_PC();
      printState();
      print_UnitControl();
    }
  }

  void increment_PC() {
    uc.incrementa_pc = 1;
    pc.pc += 1;
    uc.incrementa_pc = 0;
  }
  void exec_SUB(){
    
    mux();
    increment_PC();
    read();
    uc.s3 = 1;
    mux();
    uc.s3 = 0;
    read();
    ula.y = rdm.dado;
    ula.x = ac.ac;
    uc.sel_ula = 5;
    operatio();
    uc.carga_nz = 1;
    operation();
    ac.ac = nzc.result;
    uc.carga_nz = 0;
    printState();
    print_UnitControl();
  }
  void busca() {
    
   uc.carga_pc=1;
   uc.s3=0;
   mux();
   uc.carga_rem=1;
////////////////////////////
   uc.incrementa_pc=1;
   pc.pc++;
   uc.incrementa_pc=0;
////////////////////////////
    uc.read=1;
   read();
   uc.read=0;
   uc.carga_rdm=0;
////////////////////////////
    uc.carga_ri=1;   
    ri.ri=rdm.dado;
    uc.carga_ri=0;
/////////////////////////////    
  }

  void operation() {

    if (nzc.result > 0) {
      nzc.N = false;
      nzc.Z = false;
    } else if (nzc.result < 0) {
      nzc.N = true;
      nzc.Z = false;
    } else {
      nzc.N = false;
      nzc.Z = true;
    }
  }

  void printState (){
    std::cout << "STATUS: \n";
    std:: cout << std::setw(30) << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    std::cout << "┃ PC:  " << pc.pc << " |  RI: " << ri.ri << " |  REM: " << rem.adress <<  " ┃" << std::endl;
       std::cout << "┃ RA: " << ac.ac << "  |  RX: " << ac1.ac1 << " |  RB: " << ac2.ac2 <<  "   ┃" << std::endl;
    std::cout << "┃ RDM: " << rdm.dado << " |  AC: " << ac.ac <<  "           ┃" << std::endl;
    std:: cout << std::setw(30) << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
  }

  void print_UnitControl (){
    std::cout << "UNIDADE DE CONTROLE: \n";
    std:: cout << std::setw(60) << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    std::cout << "┃ CARGA_PC: " << uc.carga_pc << "  |  CARGA_RI: " << uc.carga_ri << " |  CARGA_REM: " << uc.carga_rem <<  " ┃" << std::endl;
    std::cout << "┃ READ: " << uc.read << "  |  WRITE: " << uc.write << " |  SINAL_ULA: " << uc.sel_ula <<  "        ┃" << std::endl;
   
    std::cout << "┃ CARGA_NZ: " << uc.carga_nz << "  |  CARGA_RI: " << uc.carga_ri << " |  SEL_MUX: " << uc.sel_ula <<  "   ┃" << std::endl;
    std::cout << "┃ INCREMENTA_PC: " << uc.incrementa_pc << "                            ┃" << std::endl;
    std:: cout << std::setw(60) << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
  }

 void read() {
        uc.carga_rdm=1;
        rdm.dado= mem.memory[rem.adress];
        
  }
  void write(){
      mem.memory[rem.adress]=rdm.dado;
  }

  void lertudo(const std::string& arquivoInstrucoes) {
 
    std::ifstream arquivo(arquivoInstrucoes);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de instruções: " << arquivoInstrucoes << "\n";
        return;
    }

    int instrucao;
    int endereco;
    int modo; 
    while (arquivo >> endereco>> modo >> instrucao ) {
        mem.memory[endereco]=instrucao;
    }

    arquivo.close();
    
}
void zerar(){
  pc.pc = 0;
}

int findMaxMemoryValue() {
    int max_value = -2147483648;  // Valor muito baixo para garantir que qualquer valor será maior inicialmente.
    
    // Inicializando o PC para o começo da memória
    pc.pc = 0;
    
    // Percorre a memória acessando cada endereço uma vez.
    while (pc.pc < 32) {
        // Simula a busca pela instrução armazenada no PC
        rem.adress = pc.pc;  // O REM recebe o valor do PC (endereço de memória)
        rdm.dado = mem.memory[rem.adress];  // RDM recebe o valor da memória no endereço REM
        
        // Compara o valor lido na memória com o maior valor encontrado até agora
        if (rdm.dado > max_value) {
            max_value = rdm.dado;  // Atualiza o valor máximo
        }
        
        // Incrementa o PC para "andar" pela memória
        increment_PC();
    }
    
    return max_value;
}

void printMemory() {
    std::cout << "Conteúdo da Memória: \n";
    std::cout << "━━━━━━━━━━━━━━━━━━━━┓\n";
    
    // Percorre todos os endereços de memória e imprime os valores armazenados
    for (int i = 0; i < mem.memory.size(); ++i) {
        std::cout << "Endereço " << std::setw(2) << i << ": " << std::setw(4) << mem.memory[i] << "\n";
    }
    
    std::cout << "━━━━━━━━━━━━━━━━━━━━┛\n";
}

};
/*int main(int argc, char *argv[]) {


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

}*/