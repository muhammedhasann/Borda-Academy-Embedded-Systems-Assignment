//part a solution
#include <stdio.h>

// Define I2C Addresses of sensors
enum sensor_address_t
{
    SHT4x_I2C_ADDR = 0x44,
    PAS_CO2_I2C_ADDR = 0x61,
    BME680_I2C_ADDR = 0x76
};


// Define Sensor Types
enum sensor_type_t
{
    TEMPERATURE,
    HUMIDITY,
    CO2
};
