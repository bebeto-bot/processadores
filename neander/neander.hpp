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
#include "NZ.hpp"

#include <vector> 
#include <string>
#include <fstream>

class Neander {
private:
  AC ac;
  PC pc;
  RDM rdm;
  REM rem;
  RI ri;
  ControlUnit uc;
  ULA ula;
  NZ nz;
  memoria mem;
public:
  Neander(){
    ac.ac = 0;
    pc.pc = 0;
    rdm.dado = 0;
    rem.adress = 0;
    ri.ri = 0;
    ula.y = 0;
    ula.x = 0;
    nz.N = 0;
    nz.Z = 0;
    nz.result = 0;
    uc.carga_ac=0;
    uc.sel = 0;
    uc.sel_ula=0;
    uc.carga_nz=0;
    uc.carga_pc=0;
    uc.carga_rem=0;
    uc.carga_ri=0;
    uc.incrementa_pc=0;
    uc.read=0;
    uc.write=0;  
    
  }
  void operatio() {
    if (uc.sel_ula == 0) {
      nz.result = ula.x + ula.y;
    } else if (uc.sel_ula == 1) {
      nz.result = ula.x and ula.y;
    } else if (uc.sel_ula == 2) {
      nz.result = ula.x or ula.y;
    } else if (uc.sel_ula == 3) {
      nz.result = ula.y;
    }
    else if(uc.sel_ula==4){
      nz.result = ~(ula.y);
    }
  }
  void mux() {
    uc.carga_rem = 1;
    if (uc.sel == false) {
      rem.adress = pc.pc;
    } else if (uc.sel == true) {
      rem.adress = rdm.dado;
    }
    uc.carga_rem = 0;
  }
  void selecao() {
    busca();
    if (ri.ri == 00) { 
      std::cout << "NOP" << std::endl;
      printState();
      print_UnitControl();
      selecao();
    } else if (ri.ri == 32) { // LDA
      std::cout << "LDA" << std::endl;
      exec_LDA();
      selecao();
    } else if (ri.ri == 48) { // ADD
      std::cout << "ADD" << std::endl;
      exec_ADD();
      selecao();
    } else if (ri.ri == 16) { // STA
      std::cout << "STA" << std::endl;
      exec_STA();
      selecao();
    } else if (ri.ri == 240) { // HLT
      std::cout << "HLT" << std::endl;
      printState();
      print_UnitControl();
    } else if (ri.ri == 96) { // NOT
      std::cout << "NOT" << std::endl;
      exec_NOT();
      selecao();
    } else if (ri.ri == 64) { // JMP
      std::cout << "JMP" << std::endl;
      exec_JMP();
      selecao();
    } else if (ri.ri == 80) { // JN
      std::cout << "JN" << std::endl;
      exec_JN();
      selecao();
    } else if (ri.ri == 112) { // JZ
      std::cout << "JZ" << std::endl;
      exec_JZ();
      selecao();
    } else {
      std::cerr << "Instrução inválida: " << ri.ri << std::endl;
    }
  }

  void exec_LDA() {
    uc.sel = 0;
    mux();
    increment_PC();
    read();
    uc.sel = 1;
    mux();
    read();
    uc.carga_ac = 1;
    ac.ac = rdm.dado;
    uc.carga_ac = 0;
    printState();
    print_UnitControl();
  }

  void exec_ADD() {
    uc.sel = 0;
    mux();
    increment_PC();
    read();
    uc.sel = 1;
    mux();
    read();
    ula.y = rdm.dado;
    ula.x = ac.ac;
    uc.sel_ula = 0;
    operatio();
    uc.carga_nz = 1;
    operation();
    ac.ac = nz.result;
    uc.carga_nz = 0;
    printState();
    print_UnitControl();
  }

  void exec_STA() {
    uc.sel = 0;
    mux();
    increment_PC();
    read();
    uc.sel = 1;
    mux();
    uc.write = 1;
    rdm.dado = ac.ac;
    write();
    uc.write = 0;
    printState();
    print_UnitControl();
  }

  void exec_NOT() {
    uc.sel_ula = 4;
    operatio();
    ac.ac = nz.result;
    printState();
    print_UnitControl();
  }

  void exec_JMP() {
    uc.sel = 0;
    mux();
    increment_PC();
    read();
    pc.pc = rdm.dado;
    printState();
    print_UnitControl();
  }

  void exec_JN() {
    if (nz.N) {
      exec_JMP();
    } else {
      increment_PC();
      printState();
      print_UnitControl();
    }
  }

  void exec_JZ() {
    if (nz.Z) {
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
  void busca() {
    
   uc.carga_pc=1;
   uc.sel=0;
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

    if (nz.result > 0) {
      nz.N = false;
      nz.Z = false;
    } else if (nz.result < 0) {
      nz.N = true;
      nz.Z = false;
    } else {
      nz.N = false;
      nz.Z = true;
    }
  }

  void printState (){
    std::cout << "STATUS: \n";
    std:: cout << std::setw(30) << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    std::cout << "┃ PC:  " << pc.pc << " |  RI: " << ri.ri << " |  REM: " << rem.adress <<  " ┃" << std::endl;
    std::cout << "┃ RDM: " << rdm.dado << " |  AC: " << ac.ac <<  "           ┃" << std::endl;
    std:: cout << std::setw(30) << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
  }

  void print_UnitControl (){
    std::cout << "UNIDADE DE CONTROLE: \n";
    std:: cout << std::setw(60) << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    std::cout << "┃ CARGA_PC: " << uc.carga_pc << "  |  CARGA_RI: " << uc.carga_ri << " |  CARGA_REM: " << uc.carga_rem <<  " ┃" << std::endl;
    std::cout << "┃ READ: " << uc.read << "  |  WRITE: " << uc.write << " |  SINAL_ULA: " << uc.sel_ula <<  "        ┃" << std::endl;
    std::cout << "┃ CARGA_NZ: " << uc.carga_nz << "  |  CARGA_RI: " << uc.carga_ri << " |  SEL_MUX: " << uc.sel <<  "   ┃" << std::endl;
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
    while (arquivo >> endereco>> instrucao ) {
        mem.memory[endereco]=instrucao;
    }

    arquivo.close();
    
}
};