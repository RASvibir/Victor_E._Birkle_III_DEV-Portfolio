#include "uXu/include/uxu.hpp"
#include <iostream>
#include <iomanip>

void printHex(const std::vector<uint8_t>& data) {
    for (auto byte : data) {
        std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;
}

int main() {
    std::cout << "=== uXu Protocol Engine Integration Test ===" << std::endl;
    uXu::ProtocolEngine engine;
    std::vector<uint8_t> mock_telemetry = { 0x42, 0x01, 0x1A, 0x7C };
    std::cout << "Original Payload:\t"; printHex(mock_telemetry);
    std::vector<uint8_t> frame = engine.serialize(mock_telemetry);
    std::cout << "Serialized Frame:\t"; printHex(frame);
    uXu::Packet decoded_packet;
    bool success = engine.deserialize(frame, decoded_packet);
    std::cout << "Standard Deserialization: " << (success ? "\033[32mPASSED\033[0m" : "\033[31mFAILED\033[0m") << std::endl;
    std::vector<uint8_t> corrupted_frame = frame;
    corrupted_frame[3] ^= 0xFF;
    std::cout << "Corrupted Frame:\t"; printHex(corrupted_frame);
    uXu::Packet error_packet;
    bool error_check = engine.deserialize(corrupted_frame, error_packet);
    std::cout << "Corruption Detection Test: " << (!error_check ? "\033[32mSECURE (Rejected Corrupted Packet)\033[0m" : "\033[31mFAULT (Corrupted Packet Accepted)\033[0m") << std::endl;
    return 0;
}
