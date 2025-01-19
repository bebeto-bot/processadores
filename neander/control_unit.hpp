#include <cstdint>

struct ControlUnit {

  bool sel;
  std::uint8_t sel_ula;
  bool carga_ac;
  bool incrementa_pc;
  bool carga_pc;
};
