
#include <vector>
#include <cstdint>

struct memoria {
    std::vector<short> memory;

    memoria()  {
        memory.resize(256);
    } 
};