#include <cstdint>

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
      busca();
      uc.sel = 0;
      uc.carga_rem=1;
      mux();
       uc.carga_rem=0;
      rdm.dado = read();
      uc.incrementa_pc = 1;
       pc.pc = pc.pc + 1;
      uc.incrementa_pc=0;
       uc.carga_rem=1;
      rem.adress = rdm.dado; // Store value from memory to AC
       uc.carga_rem=0;
      ac.ac = rdm.dado;
      // Write back
      uc.write = 1;
      mem.memory[rem.adress] = rdm.dado;
      uc.write = 0;

    } else if (ri.ri == 1) {
      busca();

    } else if (ri.ri == 2) {
      busca();

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
    mux();
    uc.carga_pc=0;
    uc.carga_rem=0;
    uc.read = 1;
    
    rdm.dado = read(); // Read memory
    uc.read = 0;
    uc.incrementa_pc = 1;
    pc.pc = pc.pc + 1;
    uc.incrementa_pc=0;
    uc.carga_ri = 1;
    ri.ri = rdm.dado;
    uc.carga_ri = 0;
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
    std::cout << "PC: " << pc.pc << " |  RI: " << ri.ri << " |  REM: " << rem.adress;
  }

 std::uint8_t read() {
        
        return mem.memory[rem.adress];
  }
};