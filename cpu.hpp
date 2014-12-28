#include <cstdint>
#include <functional>
#include <string>

namespace NES {

    class Memory;

    class CPU {
    public:
        CPU(Memory* mem);

        void interpret();
        void reset();

    private:
        // Status register layout:
        //    7 6 5 4 3 2 1 0
        //   [N V   B D I Z C]
        //
        //   Carry Flag (C)
        //   The carry flag is set if the last instruction resulted in an overflow from bit 7 or an
        //   underflow from bit 0. For example performing 255 + 1 would result in an answer of 0
        //   with the carry bit set. This allows the system to perform calculations on numbers
        //   longer than 8-bits by performing the calculation on the first byte, storing the carry
        //   and then using that carry when performing the calculation on the second byte. The
        //   carry flag can be set by the SEC (Set Carry Flag) instruction and cleared by the CLC
        //   (Clear Carry Flag) instruction.
        //
        //   Zero Flag (Z)
        //   The zero flag is set if the result of the last instruction was zero. So for example 128
        //   - 127 does not set the zero flag, whereas 128 - 128 does.
        //
        //   Interrupt Disable Flag (I)
        //   The interrupt disable flag can be used to prevent the system responding to IRQs. It
        //   is set by the SEI (Set Interrupt Disable) instruction and IRQs will then be ignored
        //   until execution of a CLI (Clear Interrupt Disable) instruction.
        //
        //   Decimal Mode Flag (D)
        //   The decimal mode flag is used to switch the 6502 into BCD mode. However the 2A03 does
        //   not support BCD mode so although the flag can be set, its value will be ignored. This
        //   flag can be set SED (Set Decimal Flag) instruction and cleared by CLD (Clear Decimal
        //   Flag).
        //
        //   Break Command (B)
        //   The break command flag is used to indicate that a BRK (Break) instruction has been
        //   executed, causing an IRQ.
        //
        //   Overflow Flag (V)
        //   The overflow flag is set if an invalid two’s complement result was obtained by the
        //   previous instruction. This means that a negative result has been obtained when a
        //   positive one was expected or vice versa. For example, adding two positive numbers
        //   should give a positive answer. However 64 + 64 gives the result -128 due to the sign
        //   bit. Therefore the overflow flag would be set. The overflow flag is determined by
        //   taking the exclusive-or of the carry from between bits 6 and 7 and between bit 7 and
        //   the carry flag.
        //
        //   Negative Flag (N)
        //   Bit 7 of a byte represents the sign of that byte, with 0 being positive and 1 being
        //   negative. The negative flag (also known as the sign flag) is set if this sign bit is 1.
        enum class StatusFlag: std::uint8_t {
            C = 0x01, // Cary Flag
            Z = 0x02, // Zero Flag
            I = 0x04, // Interrupt Disable
            D = 0x08, // Decimal Mode
            B = 0x10, // Break Command
            A = 0x20, // Always On
            V = 0x40, // Overflow Flag
            N = 0x80, // Negative Flag
        };

        // TODO: check if these are what we need
        enum class AddressingMode: std::uint8_t {
            Implicit,
            ZeroPage,
            ZeroPageX,
            ZeroPageY,
            Absolute,
            AbsoluteX,
            AbsoluteY,
            Immediate,
            Relative
        };

        struct Operation {
            std::string name;
            std::function<void(void)> exec_func;
            std::uint64_t standard_cycles;
            std::uint64_t extra_cycles;
            AddressingMode addressing_mode;
        }

        // Add with Carry
        void _adc();

        // Bitwise AND with Accumulator
        void _and();

        // Arithmetic Shift Left
        void _asl();

        // Branch on Carry Clear
        void _bcc();

        // Branch on Carry Set
        void _bcs();

        // Branch on Equal
        void _beq();

        // Test Bits
        void _bit();

        // Branch on Minus
        void _bmi();

        // Branch not Equal
        void _bne();

        // Branch on Plus
        void _bpl();

        // Break
        void _brk();

        // Branch on Overflow Clear
        void _bvc();

        // Branch on Overflow Set
        void _bvs();

        // Cleary Carry
        void _clc();

        // Clear Decimal
        void _cld();

        // Clear Interrupt
        void _cli();

        // Clear Overflow
        void _clv();

        // Compare to Accumulator
        void _cmp();

        // Compare to X Register
        void _cpx();

        // Compare to Y Register
        void _cpy();

        // Decrement Memory
        void _dec();

        // Decrement X Register
        void _dex();

        // Decrement Y Register
        void _dey();

        // Bitwise Exclusive OR
        void _eor();

        // Increment Memory
        void _inc();

        // Increment Register X
        void _inx();

        // Increment Register Y
        void _iny();

        // Jump
        void _jmp();

        // Jump to Subroutine
        void _jsr();

        // Load Accumulator
        void _lda();

        // Load Register X
        void _ldx();

        // Load Register Y
        void _ldy();

        // Logical Shift Right
        void _lsr();

        // No Operation
        void _nop();

        // Bitwise OR with Accumulator
        void _ora();

        // Push Accumulator
        void _pha();

        // Push Processor Status
        void _php();

        // Pull Accumulator
        void _pla();

        // Pull Processor Status
        void _plp();

        // Rotate Left
        void _rol();

        // Rotate Right
        void _ror();

        // Return from Interrupt
        void _rti();

        // Return from Subroutine
        void _rts();

        // Subtract with Carry
        void _sbc();

        // Set Carry
        void _sec();

        // Set Decimal
        void _sed();

        // Set Interrupt
        void _sei();

        // Store Accumulator
        void _sta();

        // Store Register X
        void _stx();

        // Store Register Y
        void _sty();

        // Transfer A to X
        void _tax();

        // Transfer A to Y
        void _tay();

        // Transfer Stack Pointer to X
        void _tsx();

        // Transfer X to A
        void _txa();

        // Transfer X to Stack Pointer
        void _txs();

        // Transfer Y to A
        void _tya();

        std::uint8_t _accumulator;
        std::uint8_t _x_register;
        std::uint8_t _y_register;
        std::uint8_t _processor_status;
        std::uint8_t _stack_pointer;
        std::uint16_t _program_counter;

        bool _debug;
        Memory* _memory;
    };

}  // namespace NES
