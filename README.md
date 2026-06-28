# Victor E. Birkle III — Systems Engineering Portfolio

**Live Portfolio:** https://rasvibir.github.io/Victor_E._Birkle_III_DEV-Portfolio/

Software Engineering student combining a rigorous foundation in Electronics Engineering Technology with real-time systems programming. This repository contains the source code for my interactive engineering portfolio, targeting the SpaceX Fall 2026 Software Engineering Internship.

---

## Repository Structure
├── index.html                  # Interactive portfolio (GitHub Pages entry point)

├── uXu/

│   ├── include/uxu.hpp         # uXu protocol header — CRC-16, packet framing

│   └── src/uxu.cpp             # uXu protocol implementation

├── emulators/

│   ├── dsp_fft_visualizer.js   # DSP signal engine module

│   ├── telemetry_sync_engine.js# Offline-first telemetry pipeline module

│   └── hitl_logic_analyzer.js  # HITL logic analyzer module

├── main.cpp                    # C++ integration test harness

└── .gitignore
---

## uXu — Micro-Exchange Utility Protocol

A lightweight, deterministic packet framing protocol engineered for bare-metal microcontroller telemetry streams (Teensy 4.0 / STM32). Features:

- Bitwise frame sync markers (`0xAA` start, `0x55` end)
- CCITT CRC-16 checksum validation (polynomial `0x1021`)
- Thread-safe serialization via `std::mutex`
- Cosmic ray bit-flip corruption detection

### Build & Test

```bash
g++ -std=c++17 -I./uXu/include uXu/src/uxu.cpp main.cpp -o uXu_test_runner -lpthread
./uXu_test_runner
```

Expected output:
=== uXu Protocol Engine Integration Test ===

Original Payload:       0x42 0x01 0x1a 0x7c

Serialized Frame:       0xaa 0x04 0x42 0x01 0x1a 0x7c 0x7f 0x6d 0x55

Standard Deserialization: PASSED

Corruption Detection Test: SECURE (Rejected Corrupted Packet)
---

## Interactive Portfolio Features

Three live engineering simulators embedded in `index.html`:

- **DSP Signal Engine** — Real-time sine, square, and sawtooth waveform generator with FFT frequency bar emulation
- **Offline-First Telemetry Pipeline** — Toggle network connectivity to simulate SQLite staging and async PostgreSQL sync
- **HITL Logic Analyzer** — Interactive SPI/ISR conflict timing diagram with double-buffer patch toggle

---

## Tech Stack

| Layer | Technologies |
|---|---|
| Embedded Protocol | C++17, CCITT CRC-16, pthreads |
| Microcontrollers | STM32, Teensy 4.0, ESP32, Arduino |
| Bus Protocols | SPI, I2C, CAN, UART, RS-485 |
| Data Pipeline | Python, SQLite, PostgreSQL |
| Portfolio UI | HTML, Tailwind CSS, Vanilla JS, Canvas API |

---

## Contact

**Email:** victor.birkle@students.maestrocolleg.edu  
**Phone:** (205) 828-0420  
**GitHub:** https://github.com/RASvibir  
**LinkedIn:** https://linkedin.com/in/victor-birkle
