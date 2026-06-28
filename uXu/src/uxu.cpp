#include "uxu.hpp"
#include <algorithm>

namespace uXu {

    uint16_t ProtocolEngine::calculateCRC16(const uint8_t* data, uint8_t length) const {
        uint16_t crc = 0xFFFF;
        for (uint8_t i = 0; i < length; ++i) {
            crc ^= (static_cast<uint16_t>(data[i]) << 8);
            for (uint8_t bit = 0; bit < 8; ++bit) {
                if (crc & 0x8000) {
                    crc = (crc << 1) ^ 0x1021;
                } else {
                    crc <<= 1;
                }
            }
        }
        return crc;
    }

    std::vector<uint8_t> ProtocolEngine::serialize(const std::vector<uint8_t>& raw_payload) {
        std::lock_guard<std::mutex> lock(mtx);
        std::vector<uint8_t> frame;
        uint8_t length = static_cast<uint8_t>(std::min(raw_payload.size(), static_cast<size_t>(255)));
        frame.push_back(START_OF_FRAME);
        frame.push_back(length);
        frame.insert(frame.end(), raw_payload.begin(), raw_payload.begin() + length);
        std::vector<uint8_t> checksum_data;
        checksum_data.push_back(length);
        checksum_data.insert(checksum_data.end(), raw_payload.begin(), raw_payload.begin() + length);
        uint16_t crc = calculateCRC16(checksum_data.data(), checksum_data.size());
        frame.push_back(static_cast<uint8_t>(crc >> 8));
        frame.push_back(static_cast<uint8_t>(crc & 0xFF));
        frame.push_back(END_OF_FRAME);
        return frame;
    }

    bool ProtocolEngine::deserialize(const std::vector<uint8_t>& frame, Packet& out_packet) {
        std::lock_guard<std::mutex> lock(mtx);
        if (frame.size() < 5) return false;
        if (frame.front() != START_OF_FRAME || frame.back() != END_OF_FRAME) return false;
        uint8_t length = frame[1];
        if (frame.size() != static_cast<size_t>(length + 5)) return false;
        std::vector<uint8_t> payload(frame.begin() + 2, frame.end() - 3);
        uint16_t received_crc = (static_cast<uint16_t>(frame[frame.size() - 3]) << 8) | frame[frame.size() - 2];
        std::vector<uint8_t> checksum_data;
        checksum_data.push_back(length);
        checksum_data.insert(checksum_data.end(), payload.begin(), payload.end());
        uint16_t calculated_crc = calculateCRC16(checksum_data.data(), checksum_data.size());
        if (received_crc == calculated_crc) {
            out_packet.length = length;
            out_packet.payload = payload;
            out_packet.checksum = received_crc;
            return true;
        }
        return false;
    }

} // namespace uXu
