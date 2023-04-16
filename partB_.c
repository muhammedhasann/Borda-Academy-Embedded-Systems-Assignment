// part b solution 
// since I am not using any real I2c sensors I am just using random numbers for the sensor data

#include <stdlib.h>

// Define Sensor Data Ranges
struct sensor_range_t
{
    const float min;
    const float max;
};

// Define Sensor Types and their ranges 

const struct sensor_range_t SENSOR_RANGES[] = {
    [TEMPERATURE] = {20.0, 120.0},
    [HUMIDITY] = {0.0, 100.0},
    [CO2] = {400.0, 10400.0},
};

// Struct to hold sensor data
struct sensor_data_t
{
    float temperature;
    float humidity;
    float co2;
};