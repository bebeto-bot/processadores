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
      // ciclo de execução (execution cycle)
      ac.ac = rdm.dado; // Store value from memory to AC
      rem.adress = pc.pc;

      // Write back
      mem.memory[rem.adress] = ac.ac;

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

    rem.adress = pc.pc;
    rdm.dado = read(); // Read memory
    pc.pc = pc.pc + 1;
    ri.ri = rdm.dado;
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

 std::uint8_t read() {
        
        return mem.memory[rem.adress];
  }
};