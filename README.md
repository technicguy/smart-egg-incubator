# 🥚 Smart Egg Incubator & Hatching Controller

[![Arduino](https://img.shields.io/badge/Arduino-UNO%2FMega-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![EEPROM](https://img.shields.io/badge/EEPROM-Persistent--Storage-FF6F00?style=for-the-badge)](https://www.arduino.cc/en/Reference/EEPROM)

**Smart Egg Incubator** is an automated micro-climate controller firmware built for poultry egg incubation, environmental regulation, and automated hatching management using Arduino microcontrollers and LCD Keypad Shields.

---

## 📺 Video Demonstration

Watch the complete project setup, hardware testing, and LCD keypad menu walkthrough:

<iframe width="100%" height="400" src="https://www.youtube.com/embed/8psR3K1-Nto" title="Smart Egg Incubator Demonstration" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

<br>

[![Smart Egg Incubator Demonstration](https://img.youtube.com/vi/8psR3K1-Nto/maxresdefault.jpg)](https://youtu.be/8psR3K1-Nto)

▶️ **Watch on YouTube:** [https://youtu.be/8psR3K1-Nto](https://youtu.be/8psR3K1-Nto)

---

## 🌟 Key Features

| Feature | Description |
| :--- | :--- |
| 🌡️ **Temperature Control** | Precise reading via **DHT22** sensor with configurable threshold limits stored in non-volatile **EEPROM**. |
| 💧 **Humidity Regulation** | Real-time relative humidity tracking (%) with custom threshold alerts and humidifier relay toggling. |
| 🌀 **Cooling Fan Automation** | Automatic thermal overload control activating cooling fans when temperatures exceed target limits. |
| 🔄 **Egg Turner Timer** | Scheduled motor control for egg turning cycles (configurable turns per day). |
| 🐣 **Hatching Days Counter** | Built-in hatch day counter tracking remaining incubation days. |
| 🖥️ **Interactive LCD Keypad Menu** | 16x2 LCD UI with custom graphics (temperature, humidity drop, egg, fan, chicken icons) and 5-button analog keyboard input. |
| 💾 **Non-Volatile Memory** | Preserves all user settings (target temp, humidity, fan thresholds, hatch countdown) across power loss via Arduino **EEPROM**. |

---

## 🛠️ Required Hardware Components & Bill of Materials (BOM)

| Component | Quantity | Specification | Description |
| :--- | :---: | :---: | :--- |
| **Arduino Board** | 1 | UNO R3 or Mega 2560 | Primary microcontroller running the control logic. |
| **LCD Keypad Shield** | 1 | 16x2 LCD + 5 Analog Buttons | User interface shield with UP, DOWN, LEFT, RIGHT, SELECT buttons on Pin A0. |
| **DHT22 Sensor** | 1 | Digital Pin 11 | High-accuracy temperature and relative humidity sensor. |
| **Relay Module** | 1 | 4-Channel 5V Relay | Controls Heating element, Humidifier, Cooling Fan, and Egg Turning Motor. |
| **Power Supply** | 1 | 12V 2A DC Adapter | Powers Arduino board, relays, and environmental loads. |

---

## 🖥️ LCD Custom Icons & Menu Navigation

The interface features custom pixel-art icons loaded directly into the LCD's CGRAM:

```
[Temp: 37.5°C]    <-- Live Status Screen
[Hum : 60.0% ]    

[-- VALUES --]    <-- EEPROM Memory Save Screen
[-- STORED --]
```

### Menu Structure
1. **Temperature (`saveTemp`)**: Set target incubation temperature (°C).
2. **Humidity (`saveHum`)**: Set target relative humidity (%).
3. **Cooling Fan (`saveFan`)**: Set cooling fan activation offset temperature.
4. **Egg Turner (`saveTurn`)**: Configure egg turning frequency per day (0 - 96 turns/day).
5. **Hatching Days (`saveHatch`)**: Set incubation countdown period in days.
6. **Setting Status**: Displays current EEPROM configured values.
7. **Live Status**: Displays real-time DHT22 sensor readings.
8. **About Us**: System credits.

---

## ⚙️ Hardware Wiring & Pin Mapping

| Peripheral | Arduino Pin | Description |
| :--- | :---: | :--- |
| **LCD RS** | Pin 8 | LCD Register Select |
| **LCD Enable** | Pin 9 | LCD Enable Pin |
| **LCD Data D4-D7** | Pins 4, 5, 6, 7 | 4-bit LCD Data Bus |
| **Keypad Buttons** | Pin A0 | Analog Voltage Divider Keypad Input |
| **DHT22 Data** | Pin 11 | Temperature & Humidity Sensor Signal |

---

## 🚀 Setup & Flashing Guide

1. Download and open [`incoubator.ino`](file:///D:/Backup/Arduino/Incubator/incoubator/incoubator.ino) in the Arduino IDE.
2. Install required Arduino libraries:
   - `LiquidCrystal` (Built-in)
   - `EEPROM` (Built-in)
   - `DHT sensor library` by Adafruit
3. Select board target (`Arduino Uno` or `Arduino Mega 2560`) under **Tools -> Board**.
4. Upload sketch to board.

---

## 📬 Contact & Support

For support, inquiries, or collaboration, feel free to reach out across any of these channels:

- 📧 **Email:** [technicguy@gmail.com](mailto:technicguy@gmail.com)
- 🌐 **Website:** [https://esanshar.com.np/](https://esanshar.com.np/)
- 📞 **Phone:** [+977 986 445 0173](tel:+9779864450173)
- 💬 **WhatsApp:** [+977 984 470 7950](https://wa.me/9779844707950)
- 💼 **LinkedIn:** [linkedin.com/in/technicguy](https://www.linkedin.com/in/technicguy/)
- 👤 **Facebook:** [facebook.com/imakashgc](https://www.facebook.com/imakashgc)
- 📺 **YouTube Channels:**
  - 🎵 **Sound & Frequency:** [Mystic Sound Journeys](https://www.youtube.com/@MysticSoundJourneys?sub_confirmation=1)
  - 👶 **Kids Content:** [MummaBaba](https://www.youtube.com/@MummaBaba?sub_confirmation=1)
