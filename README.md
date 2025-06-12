# Real Time Battery State Monitoring with Data Logging

A compact and feature-rich ESP32-based battery monitoring system designed for real-time tracking of battery performance, charging/discharging cycles, and data logging with timestamp support.

---

## Features

- **Power Supply**
  - 5V/5A input via USB Type-C
  - Onboard 3.3V LDO regulator for logic circuitry
  - 12V/2A battery backup support

- **Microcontroller**
  - ESP32 with WiFi and Bluetooth capabilities
  - Onboard TTL interface for programming

- **Sensors**
  - **Current Sensor**: ACS712 (5A)
  - **Voltage Sensor**: Voltage divider circuit
  - **Temperature Sensor**: MAX6675 (K-type thermocouple)

- **Indicators**
  - Charging plug indicator LED

- **Data Logging**
  - EEPROM for storing logs
  - RTC module for accurate timestamps

- **Communication Interfaces**
  - UART
  - SPI
  - I2C

---

## Applications

- Battery health monitoring
- IoT-enabled energy tracking
- Power usage analysis
- Renewable energy systems

---

## Hardware Components

| Component              | Description                      |
|------------------------|----------------------------------|
| ESP32 Module           | Microcontroller with WiFi & BT   |
| USB Type-C Connector   | Power input (5V/5A)              |
| LDO Regulator          | 3.3V output for ESP32 & sensors  |
| ACS712 Module          | Current sensing (5A max)         |
| Voltage Divider        | For battery voltage monitoring   |
| MAX6675 + Thermocouple | Temperature measurement          |
| RTC Module (e.g., DS3231) | Time tracking for logging     |
| EEPROM (e.g., 24C32)   | Non-volatile data storage        |
| LED Indicator          | Charging plug status             |
| TTL Interface          | ESP32 onboard programming        |
| 12V/2A Battery         | Backup power source              |

### Hardware Images

- **3D Model**: Contains the silkscreen, and designators for each element
              <img src="BMS Board Design/3D Full Board.jpg" width="500"/>
- **Fully Assembled**: Includes critical signal traces, high-speed differential pairs, and key components.
              <img src="BMS Board Design/Full Board.png" width="500"/>
- **Fully Assembled & Working Board**: A complete ground plane for signal return paths and noise suppression.
              <img src="BMS Board Design/Full with Battery.png" width="500"/>

---

## Setup Instructions

1. **Power the Circuit**  
   Connect a 5V/5A USB-C adapter or use the 12V battery backup.

2. **Programming the ESP32**  
   Use the onboard TTL interface or USB-to-TTL converter to upload firmware via Arduino IDE or PlatformIO.

3. **Sensor Connections**  
   - Connect ACS712 to an analog input on ESP32.  
   - Connect the voltage divider to another analog pin.  
   - Interface MAX6675 via SPI.  
   - Connect the RTC and EEPROM via I2C.

4. **Charging Indicator**  
   An LED lights up when the charging plug is connected.

---

## Communication

The ESP32 supports:
- **UART**: Serial debugging and communication
- **SPI**: For MAX6675 and EEPROM
- **I2C**: For RTC and EEPROM

---

## Data Logging

- Logs current, voltage, and temperature readings.
- Stores data with timestamps in EEPROM.
- Can be transmitted via UART or uploaded to cloud via WiFi (optional).

---

## License

This project is licensed under the MIT License.

---

## Contributing

Pull requests are welcome! Feel free to open an issue for feature suggestions or bug reports.

---

## Contact

For questions or support, please reach out to [abdelrahmankh2025@gmail.com].
