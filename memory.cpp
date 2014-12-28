#include "memory.hpp"

namespace NES {

    Memory::Memory()
        : _memory(std::make_unique<std::uint8_t[]>(0x800))
    {}

    std::uint8_t Memory::read(std::uint16_t address) {
        return _memory[address];
    }

    std::uint64_t Memory::write(std::uint16_t address, std::uint8_t value) {
        _memory[address] = value;
        return 0;
    }

}
