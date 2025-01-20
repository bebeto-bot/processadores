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
    for(int i = 0;i<11;i++){
      mem.memory[i] = i;
    }
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
    if (ri.ri == 0) { // STA
    printState();
     print_UnitControl();
      busca();
      uc.sel = 0;
      uc.carga_rem=1;
      printState();
       print_UnitControl();
      mux();
       uc.carga_rem=0;
       uc.read = 1;
      rdm.dado = read();
      uc.read = 0;
      uc.incrementa_pc = 1;
       pc.pc = pc.pc + 1;
       printState();
        print_UnitControl();
      uc.incrementa_pc=0;
       uc.carga_rem=1;
       printState();
        print_UnitControl();
      rem.adress = rdm.dado; // Store value from memory to AC
       uc.carga_rem=0;
       printState();
        print_UnitControl();
      ac.ac = rdm.dado;
      // Write back
      uc.write = 1;
      printState();
       print_UnitControl();
      mem.memory[rem.adress] = rdm.dado;
      uc.write = 0;
      printState();
       print_UnitControl();

    } else if (ri.ri == 1) {
      busca();
      uc.sel = 0;
      uc.carga_rem=1;
     rem.adress = pc.pc;
     uc.read = 1;
    uc.read;
    uc.read = 0;
     uc.incrementa_pc=1;
    pc.pc = pc.pc +1;
     uc.incrementa_pc=0;
    uc.sel=1;
    uc.carga_rem=1;
    mux();
    uc.carga_rem=0;
    uc.sel=0;
    uc.carga_ac=1;
    rdm.dado =  ac.ac;
     uc.carga_ac=0;     
      
     
     
  
    } else if (ri.ri == 2) {
      busca();
      rem.adress = pc.pc;
      pc.pc = pc.pc+1;
      rem.adress=rdm.dado;
      ac.ac=rdm.dado;

    } else if (ri.ri == 3) {
      busca();

    } else if (ri.ri == 4) {
      busca();

    } else if (ri.ri == 5) {
      busca();

    } else if (ri.ri == 6) {
      busca();

    } else if (ri.ri == 7) {
      busca();

    } else if (ri.ri == 8) {
      busca();

    } else if (ri.ri == 9) {
      busca();

    } else if (ri.ri == 10) {
      busca();

    } else if (ri.ri == 11) {
      busca();
    }
  }
  void busca() {
    uc.carga_pc=1;
    uc.carga_rem=1;
    uc.sel = 0;
    printState();
    print_UnitControl();
    mux();
    printState();
     print_UnitControl();
    uc.carga_pc=0;
    uc.carga_rem=0;
    uc.read = 1;
    printState();
     print_UnitControl();
    rdm.dado = read(); // Read memory
    uc.read = 0;
    uc.incrementa_pc = 1;
    printState();
     print_UnitControl();
    pc.pc = pc.pc + 1;
    uc.incrementa_pc=0;
    printState();
     print_UnitControl();
    uc.carga_ri = 1;
    printState();
     print_UnitControl();
    ri.ri = rdm.dado;
    uc.carga_ri = 0;
    printState();
     print_UnitControl();
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

 std::uint8_t read() {
        
        return mem.memory[rem.adress];
  }
};