# IoT Water Level Monitoring (ESP32 + HC-SR04)

Monitors a tank's water level using **HC-SR04** ultrasonic sensor on **ESP32**.
Sends readings over Serial and includes a template for pushing data to REST (e.g., Firebase).

> The REST upload is optional and disabled by default. Fill WiFi credentials and uncomment
> the `pushToREST()` call to enable.

## Hardware
- ESP32 DevKit
- HC-SR04 Ultrasonic sensor
  - VCC → 5V, GND → GND, TRIG → GPIO 5, ECHO → GPIO 18 (use a voltage divider to 3.3V if needed)

## Build
- Arduino IDE → Boards Manager: install **ESP32** by Espressif
- Select board: "ESP32 Dev Module"
- Install **WiFi** library (included with ESP32 core)
- Upload `firmware/esp32_water_level.ino`

## Serial Output (JSON):
```json
{"distance_cm": 23.7, "ts": 123456}
```

## License
MIT
