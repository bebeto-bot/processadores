
#include <vector>
#include <cstdint>

struct memoria {
    std::vector<short> memory;

    memoria() : memory(256, 0) {}  // Constructor to initialize the vector with 256 elements, all set to 0
};