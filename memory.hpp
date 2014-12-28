#include <cstdint>
#include <memory>

namespace NES {

    class Memory {
    public:
        Memory();
        std::uint8_t read(std::uint16_t address);
        std::uint64_t write(std::uint16_t address, std::uint8_t value);

    private:
        std::unique_ptr<std::uint8_t[]> _memory;
    };

}  // namespace NES
