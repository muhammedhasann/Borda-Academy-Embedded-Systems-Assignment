
// psrt D - Sensor Data solution
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


        // Read data from sensors
        struct sensor_data_t sensor_data = {
            .temperature = i2c_sensor_read(SHT4x_I2C_ADDR, TEMPERATURE),
            .humidity = i2c_sensor_read(SHT4x_I2C_ADDR, HUMIDITY),
            .co2 = i2c_sensor_read(PAS_CO2_I2C_ADDR, CO2)};
