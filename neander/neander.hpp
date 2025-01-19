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

  AC ac;
  PC pc;
  RDM rdm;
  REM rem;
  RI ri;
  ControlUnit uc;
  ULA ula;
  NZ nz;
  memoria mem;

  /*void operation() {
    if (a.sel_ula == 0) {

      result.result = x + y;
    } else if (a.sel_ula == 1) {
      result.result = x and y;
    } else if (a.sel_ula == 2) {
      result.result = x or y;
    } else if (a.sel_ula == 3) {
      result.result = y;
    }
  }*/
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
      // ciclo de execução (execution cycle)
      ac.ac = rdm.dado; // Store value from memory to AC
      rem.adress = pc.pc;

      // Write back
      mem.memory[rem.adress] = ac.ac;

    } else if (ri.ri == 1) {

    } else if (ri.ri == 2) {

    } else if (ri.ri == 3) {

    } else if (ri.ri == 4) {

    } else if (ri.ri == 5) {

    } else if (ri.ri == 6) {

    } else if (ri.ri == 7) {

    } else if (ri.ri == 8) {

    } else if (ri.ri == 9) {

    } else if (ri.ri == 10) {

    } else if (ri.ri == 11) {
    }
  }
  void busca(RDM rdm, REM rem, NZ nz, memoria mem, RI ri, PC pc, AC ac) {

    rem.adress = pc.pc;
    rdm.dado = mem.read(rem.adress); // Read memory
    pc.pc = pc.pc + 1;
    ri.ri = rdm.dado;
  }

  void operation() {

    if (result > 0) {
      N = false;
      Z = false;
    } else if (result < 0) {
      N = true;
      Z = false;
    } else {
      N = false;
      Z = true;
    }
  }
};
