#include "M5_RoverC.h"

#if defined(ESP_PLATFORM)
#include <string.h>
#include "freertos/FreeRTOS.h"
#endif

static inline int8_t clampSpeed(int value) {
    if (value > 100) return 100;
    if (value < -100) return -100;
    return static_cast<int8_t>(value);
}

#if defined(ARDUINO)
/*! @brief Sets up the Hardware.*/
bool M5_RoverC::begin(TwoWire *wire, uint8_t sda, uint8_t scl, uint8_t addr) {
    _wire = wire;
    _addr = addr;
    _sda  = sda;
    _scl  = scl;
    _wire->begin((int)_sda, (int)_scl);
    delay(10);
    _wire->beginTransmission(_addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }
}
#elif defined(ESP_PLATFORM)
/*! @brief Sets up the Hardware.*/
bool M5_RoverC::begin(i2c_port_t port, gpio_num_t sda, gpio_num_t scl,
                      uint8_t addr, uint32_t clk_speed_hz, bool init_bus) {
    _port = port;
    _addr = addr;
    if (init_bus) {
        i2c_config_t conf = {};
        conf.mode         = I2C_MODE_MASTER;
        conf.sda_io_num   = sda;
        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
        conf.scl_io_num   = scl;
        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
        conf.master.clk_speed = clk_speed_hz;
        if (i2c_param_config(_port, &conf) != ESP_OK) return false;
        esp_err_t install_res = i2c_driver_install(_port, conf.mode, 0, 0, 0);
        if (install_res != ESP_OK && install_res != ESP_ERR_INVALID_STATE) {
            return false;
        }
    }

    uint8_t reg = 0x00;
    uint8_t probe = 0;
    return i2c_master_write_read_device(_port, _addr, &reg, 1, &probe, 1,
                                        pdMS_TO_TICKS(50)) == ESP_OK;
}
#endif

/*! @brief Write a certain length of data to the specified register address. */
void M5_RoverC::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                           uint8_t length) {
#if defined(ARDUINO)
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    _wire->endTransmission();
#elif defined(ESP_PLATFORM)
    uint8_t payload[17];
    if (length > 16) return;
    payload[0] = reg;
    memcpy(&payload[1], buffer, length);
    i2c_master_write_to_device(_port, addr, payload, length + 1, pdMS_TO_TICKS(50));
#endif
}

/*! @brief Read a certain length of data to the specified register address. */
void M5_RoverC::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                          uint8_t length) {
#if defined(ARDUINO)
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission();
    _wire->requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire->read();
    }
#elif defined(ESP_PLATFORM)
    i2c_master_write_read_device(_port, addr, &reg, 1, buffer, length,
                                 pdMS_TO_TICKS(50));
#endif
}

void M5_RoverC::setPulse(uint8_t pos, int8_t width) {
    writeBytes(_addr, pos, (uint8_t *)&width, 1);
}

void M5_RoverC::setAllPulse(int8_t width0, int8_t width1, int8_t width2,
                            int8_t width3) {
    setPulse(0, width0);
    setPulse(1, width1);
    setPulse(2, width2);
    setPulse(3, width3);
}

/*! @brief Set the speed of the motor. */
void M5_RoverC::setSpeed(int8_t x, int8_t y, int8_t z) {
    int8_t buffer[4];
    if (z != 0) {
        int az = z < 0 ? -z : z;
        x = static_cast<int8_t>(int(x * (100 - az) / 100));
        y = static_cast<int8_t>(int(y * (100 - az) / 100));
    }
    buffer[0] = clampSpeed(y + x - z);
    buffer[1] = clampSpeed(y - x + z);
    buffer[3] = clampSpeed(y + x + z);
    buffer[2] = clampSpeed(y - x - z);
    writeBytes(_addr, 0x00, (uint8_t *)buffer, 4);
}

/*! @brief Set the angle of the servo. */
void M5_RoverC::setServoAngle(uint8_t pos, uint8_t angle) {
    uint8_t reg = 0x10 + pos;
    writeBytes(_addr, reg, &angle, 1);
}

/*! @brief Set the pulse of the servo. */
void M5_RoverC::setServoPulse(uint8_t pos, uint16_t width) {
    uint8_t reg = 0x20 + pos;
    writeBytes(_addr, reg, (uint8_t *)&width, 1);
}
