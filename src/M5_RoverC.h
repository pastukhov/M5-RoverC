/*!
 * @brief A Digital Ambient Light Sensor From M5Stack
 * @copyright Copyright (c) 2022 by M5Stack[https://m5stack.com]
 *
 * @Links [RoverC-Pro](https://docs.m5stack.com/en/hat/hat_roverc_pro)
 * @version  V0.0.1
 * @date  2022-07-012
 */
#ifndef _M5_ROVERC_H_
#define _M5_ROVERC_H_

#if defined(ARDUINO)
#include <Arduino.h>
#include <Wire.h>
#elif defined(ESP_PLATFORM)
#include <stdint.h>
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_err.h"
#else
#error "Unsupported platform. Use Arduino or ESP-IDF."
#endif

#define ROVER_ADDRESS 0x38

class M5_RoverC {
   private:
    uint8_t _addr;
#if defined(ARDUINO)
    TwoWire *_wire;
    uint8_t _sda;
    uint8_t _scl;
#elif defined(ESP_PLATFORM)
    i2c_port_t _port;
#endif
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);

   public:
#if defined(ARDUINO)
    bool begin(TwoWire *wire = &Wire, uint8_t sda = 0, uint8_t scl = 26,
               uint8_t addr = ROVER_ADDRESS);
#elif defined(ESP_PLATFORM)
    bool begin(i2c_port_t port = I2C_NUM_0, gpio_num_t sda = GPIO_NUM_0,
               gpio_num_t scl = GPIO_NUM_26, uint8_t addr = ROVER_ADDRESS,
               uint32_t clk_speed_hz = 400000, bool init_bus = true);
#endif
    void setPulse(uint8_t pos, int8_t width);
    void setAllPulse(int8_t width0, int8_t width1, int8_t width2,
                     int8_t width3);
    void setSpeed(int8_t x, int8_t y, int8_t z);
    void setServoAngle(uint8_t pos, uint8_t angle);
    void setServoPulse(uint8_t pos, uint16_t width);
};

#endif
