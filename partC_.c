// part c solution


int sensor_data_within_range(float value, enum sensor_type_t type)
{
    return (value >= SENSOR_RANGES[type].min && value <= SENSOR_RANGES[type].max);
    .co2 = i2c_sensor_read(PAS_CO2_I2C_ADDR, CO2)
};

// Check if sensor data is within range
int is_temperature_within_range = sensor_data_within_range(sensor_data.temperature, TEMPERATURE);
int is_humidity_within_range = sensor_data_within_range(sensor_data.humidity, HUMIDITY);
int is_co2_within_range = sensor_data_within_range(sensor_data.co2, CO2);

printf("\nRange Check Results:\n");
printf("Temperature within range: %s\n", is_temperature_within_range ? "true" : "false");
printf("Humidity within range: %s\n", is_humidity_within_range ? "true" : "false");
printf("CO2 within range: %s\n", is_co2_within_range ? "true" : "false");