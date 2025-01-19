
#include <array>
#include <cstdint>

struct memoria {
  std::array<std::uint8_t, 256> memory;
  memoria() {}
  std::uint8_t read(std::uint8_t address) { return memory[address]; }
};
