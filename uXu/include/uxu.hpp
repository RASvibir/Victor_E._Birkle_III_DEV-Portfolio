#ifndef UXU_HPP
#define UXU_HPP

#include <cstdint>
#include <vector>
#include <mutex>

namespace uXu {

    constexpr uint8_t START_OF_FRAME = 0xAA;
    constexpr uint8_t END_OF_FRAME   = 0x55;

    struct Packet {
        uint8_t length;
        std::vector<uint8_t> payload;
        uint16_t checksum;
    };

    class ProtocolEngine {
    private:
        mutable std::mutex mtx;
        uint16_t calculateCRC16(const uint8_t* data, uint8_t length) const;

    public:
        ProtocolEngine() = default;
        ~ProtocolEngine() = default;
        std::vector<uint8_t> serialize(const std::vector<uint8_t>& raw_payload);
        bool deserialize(const std::vector<uint8_t>& frame, Packet& out_packet);
    };

} // namespace uXu

#endif // UXU_HPP
