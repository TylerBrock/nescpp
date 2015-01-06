#include "cpu.hpp"
#include "memory.hpp"

namespace NES {

    // Power up state info:
    // http://wiki.nesdev.com/w/index.php/CPU_power_up_state
    CPU::CPU(Memory* mem)
        : _accumulator(0x00)
        , _x_register(0x00)
        , _y_register(0x00)
        , _processor_status(0x34)
        , _stack_pointer(0xFD)
        , _memory(mem)
    {
        _program_counter = _readVector(Vector::RESET);
        _opcode_map = {
            { 0x69, { "ADC", std::bind(&CPU::_adc, this), 2, 0, AddressingMode::Immediate } },
            { 0x65, { "ADC", std::bind(&CPU::_adc, this), 3, 0, AddressingMode::ZeroPage  } },
            { 0x75, { "ADC", std::bind(&CPU::_adc, this), 4, 0, AddressingMode::ZeroPageX } },
            { 0x6D, { "ADC", std::bind(&CPU::_adc, this), 4, 0, AddressingMode::Absolute  } },
            { 0x7D, { "ADC", std::bind(&CPU::_adc, this), 4, 1, AddressingMode::AbsoluteX } },
            { 0x79, { "ADC", std::bind(&CPU::_adc, this), 4, 1, AddressingMode::AbsoluteY } },
            { 0x61, { "ADC", std::bind(&CPU::_adc, this), 6, 0, AddressingMode::IndirectX } },
            { 0x71, { "ADC", std::bind(&CPU::_adc, this), 5, 1, AddressingMode::IndirectY } },
        };
    }

    // Reset state info:
    // http://wiki.nesdev.com/w/index.php/CPU_power_up_state
    void CPU::reset() {
        _program_counter = _readVector(Vector::RESET);
        _stack_pointer -= 3;
        _setFlag(StatusFlag::I, true);
    }

    std::uint16_t CPU::_readVector(Vector vec) {
        std::uint16_t address = static_cast<std::uint16_t>(vec);
        std::uint16_t result;
        result = _memory->read(address);
        result |= (std::uint16_t(_memory->read(address + 1)) << 8);
        return result;
    }

    /*
     *  ADC               Add memory to accumulator with carry                ADC
     *
     *  Operation:  A + M + C -> A, C                         N Z C I D V
     *                                                        / / / _ _ /
     */
    void CPU::_adc() {
        std::uint16_t op_data = 0;
        std::uint16_t result = _accumulator + op_data;

        if (_getFlag(StatusFlag::C))
            result++;

        _setFlag(StatusFlag::N, result <  0x00);
        _setFlag(StatusFlag::Z, result == 0x00);
        _setFlag(StatusFlag::C, result >  0xFF);

        _accumulator = op_data;
    }

    /*
     *  AND                  "AND" memory with accumulator                    AND
     *
     *  Operation:  A /\ M -> A                               N Z C I D V
     *                                                        / / _ _ _ _
     */
    void CPU::_and() {
    }

}
