#include <cstdint>

struct ControlUnit {

  bool sel;
  short sel_ula;
  bool carga_ac;
  bool incrementa_pc;
  bool carga_pc;
  bool carga_rem;
  bool read;
  bool write;
  bool carga_ri;
  bool carga_nz;
};
