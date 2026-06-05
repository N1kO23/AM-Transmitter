# AM-Transmitter

A homebrew, micro-controlled Amplitude Modulation (AM) transmitter designed for experimental broadcasting and RF engineering in the 6 MHz shortwave band (49m band). This repository contains the microcontroller firmware used to interface with the frequency synthesizer, manage system states, and control the stable carrier frequency.

## Features

- **Precise VFO Generation:** Utilizes an Si5351A programmable clock generator for highly stable, drift-free carrier generation across the HF spectrum
- **Microcontroller Controlled:** Arduino-based firmware managing I2C communications, frequency offsets, and peripheral interfacing
- **Designed for HF Operation:** Tailored architecture for the 6 MHz shortwave spectrum with customizable tuning steps
- **Optimized for Hardware Integration:** Structured to easily interface with high-efficiency MOSFET power amplifiers (PA) and dedicated audio modulation stages

## Hardware Architecture Overview

This project serves as the control and exciter core of a complete RF transmission chain, which typically includes:

1. **Exciter / Controller:** Arduino (Nano/Uno or compatible) interfacing via I2C with an Si5351A clock generator breakout board
2. **Audio Processing & Modulator:** Audio conditioning circuit optimizing dynamic range and driving the modulation path (high-level or low-level modulation)
3. **Power Amplifier (PA):** High-efficiency MOSFET output stage designed for optimal output impedance matching into a 50Ω load
4. **Low-Pass Filter (LPF):** A dedicated output harmonic suppression network tailored for the 6 MHz band to clear unwanted emissions
5. **Antenna System:** Designed to feed a resonant, properly tuned dipole antenna or matching network

---

## Firmware Setup

### Prerequisites

To compile and flash this firmware, ensure you have the following installed:
- [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/)
- **Required Libraries:**
  - `Wire.h` (Built-in I2C support)
  - `Etherkit Si5351` library (by Jason Mildrum, NT7S) or equivalent register configuration library

### Installation & Configuration

1. Clone the repository to your local development environment:
   ```bash
   git clone https://github.com/N1kO23/AM-Transmitter.git
   cd AM-Transmitter
2. Open the project folder in your preferred IDE
3. Review the configuration parameters at the top of the main source file to set your operating frequency limits, I2C address, and crystal calibration offsets:
   ```cpp
   // Default configuration example
   #define DEFAULT_FREQ  6000000ULL // Operating frequency in Hz (6.000 MHz)
   #define XTAL_CAL_FREQ 0          // Calibration factor for your specific Si5351 crystal
4. Compile and upload the firmware to your microcontroller


## Safety, Tuning & Operation

### ⚠️ IMPORTANT NOTICE: Operating radio transmitters on shortwave frequencies requires proper licensing and strict adherence to spectral regulations. Always ensure compliance with your local telecommunications authority.

Always Use a Dummy Load: Initial testing, modulation tracking, and power amplifier tuning must be conducted into a non-inductive 50Ω dummy load to prevent accidental over-the-air interference and protect components.

Mandatory Harmonic Suppression: Because the Si5351A generates square waves, a robust Low-Pass Filter (LPF) must be installed immediately after the MOSFET PA stage to suppress high-power odd-order harmonics before they reach the antenna system. A simple pi network won't be sufficient.

Impedance Matching: Ensure proper output impedance calculations are performed for your specific MOSFET configuration to guarantee optimal power transfer, minimize high-SWR thermal stress, and maintain spectral purity.

## Contributing

Contributions, hardware schematic documentation, bug reports, and firmware optimization pull requests are welcome! Feel free to open an issue or submit an enhancement for VFO control modifications, efficiency improvements, or interface expansions.
