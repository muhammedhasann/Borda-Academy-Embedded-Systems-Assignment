
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h> // for sleep()
#include <time.h>   // for time()

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

// Define Sensor Data Ranges
struct sensor_range_t
{
    const float min;
    const float max;
};

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

// Struct to hold queue of sensor data
struct sensor_data_queue_t
{
    struct sensor_data_t *buffer;
    int head;
    int tail;
    int size;
    int max_size;
};

// Function to initialize sensor data queue
void sensor_data_queue_init(struct sensor_data_queue_t *queue, int max_size)
{
    queue->buffer = (struct sensor_data_t *)malloc(max_size * sizeof(struct sensor_data_t));
    memset(queue->buffer, 0, max_size * sizeof(struct sensor_data_t));
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
    queue->max_size = max_size;
}

// Function to add sensor data to queue
void sensor_data_queue_push(struct sensor_data_queue_t *queue, struct sensor_data_t data)
{
    // If queue is full, discard oldest data
    if (queue->size == queue->max_size)
    {
        queue->tail = (queue->tail + 1) % queue->max_size;
        queue->size--;
    }

    // Add new data to head of queue
    queue->buffer[queue->head] = data;
    queue->head = (queue->head + 1) % queue->max_size;
    queue->size++;
}

// Function to read data from a sensor
float i2c_sensor_read(enum sensor_address_t addr, enum sensor_type_t type)
{
    // Placeholder function - actual implementation would use I2C communication
    // Modify this function to use the actual sensor addresses and reading functions

    float value = 0.0;
    switch (type)
    {
    case TEMPERATURE:
        // read temperature from SHT4x sensor at address SHT4x_I2C_ADDR
        // store the value in the variable 'value'
        break;
    case HUMIDITY:
        // read humidity from SHT4x sensor at address SHT4x_I2C_ADDR
        // store the value in the variable 'value'
        break;
    case CO2:
        // read CO2 from PAS CO2 sensor at address PAS_CO2_I2C_ADDR
        // store the value in the variable 'value'
        break;
    default:
        break;
    }

    return value;
}

// Function to check if sensor data is within range
int sensor_data_within_range(float value, enum sensor_type_t type)
{
    return (value >= SENSOR_RANGES[type].min && value <= SENSOR_RANGES[type].max);
}

// Function to advertise sensor data over BLE
void advertise_sensor_data(struct sensor_data_t data)
{
    // Placeholder function - actual implementation would use BLE communication
    // Modify this function to advertise the sensor data over BLE at an interval of 30 seconds
}

int main()
{
    // Initialize sensor data queue
    struct sensor_data_queue_t queue;
    sensor_data_queue_init(&queue, 10);

    // Loop to continuously take sensor readings and push them onto the queue at a frequency of 1 Hz
    while (1)
    {
        // Get current time
        time_t current_time = time(NULL);

        // Read data from sensors
        struct sensor_data_t sensor_data = {
            .temperature = i2c_sensor_read(SHT4x_I2C_ADDR, TEMPERATURE),
            .humidity = i2c_sensor_read(SHT4x_I2C_ADDR, HUMIDITY),
            .co2 = i2c_sensor_read(PAS_CO2_I2C_ADDR, CO2)};

        // Check if sensor data is within range
        int is_temperature_within_range = sensor_data_within_range(sensor_data.temperature, TEMPERATURE);
        int is_humidity_within_range = sensor_data_within_range(sensor_data.humidity, HUMIDITY);
        int is_co2_within_range = sensor_data_within_range(sensor_data.co2, CO2);

        // Print sensor data and range check results
        printf("Sensor Data:\n");
        printf("Temperature: %.2f\n", sensor_data.temperature);
        printf("Humidity: %.2f\n", sensor_data.humidity);
        printf("CO2: %.2f\n", sensor_data.co2);

        printf("\nRange Check Results:\n");
        printf("Temperature within range: %s\n", is_temperature_within_range ? "true" : "false");
        printf("Humidity within range: %s\n", is_humidity_within_range ? "true" : "false");
        printf("CO2 within range: %s\n", is_co2_within_range ? "true" : "false");

        // Push sensor data onto queue
        sensor_data_queue_push(&queue, sensor_data);

        // Advertise sensor data over BLE at an interval of 30 seconds
        if (current_time % 30 == 0)
        {
            advertise_sensor_data(sensor_data);
        }

        // Wait for 1 second before taking next sensor reading
        sleep(1);
    }

    return 0;
}
