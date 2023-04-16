Questions
Project
Description
An environmental sensing device will be designed in this project. Sensor device includes MCU, 
I2C sensors and BLE functionality. Project should include bunch of sensors for environmental 
monitoring. (Temperature, humidity, CO2 etc.) I2C peripheral of the MCU will be used to read
environmental sensor data and BLE peripheral of the MCU will be used to send measurements 
in BLE packet. The packets will be read from BLE scanner device. (Mobile phone, BLE MCU, 
etc.)
• Project consists of several steps. In case you struggle in any task, you may pass, and 
use given answers to move to the next step. To advance to the next step, you can 
use given function prototypes by assuming these functions work perfectly.
• You can use any MCU, any IDE, any API and any I2C sensor to perform given tasks. 
But please provide brief information about your tools and datasheet of the sensor.
• If you don’t have any I2C sensors for environmental monitoring and don’t want to buy 
them, you can simulate mock environmental sensor data.
Requirements
• When powered up, the device should start taking samples.
• Measurement sample frequency should be 1 Hz.
• The BLE packet advertisement interval should be 30 seconds. 
• Draw a flow chart that represents your algorithm. (You can use any flow chart 
application such as draw.io, Miro etc.)
Tasks
1. Design and write firmware for environmental sensing project.
a. You will choose 3 different I2C sensor devices. (Temperature, humidity, CO2 
etc.) Each sensor must have a unique I2C address. You should consult the 
datasheet of each sensor to determine the address options and select a unique 
address for each sensor.
i. Note that it's important to use appropriate pull-up resistors on the SDA 
and SCL lines to ensure proper communication on the I2C bus.
ii. Add links for sensor datasheets in your project report.
b. To communicate with the I2C sensors, you will implement a C function that 
reads data from the sensors. You can use this function for each sensor if you 
cannot achieve part a.
i. Bare metal programming or libraries can be used for peripheral. 
ii. If you could not answer this question, move to next one and use 
“float i2c_sensor_read(uint8_t device_address, enum 
sensor_t sensor_type);”.
Borda Academy 2023 7
This document is confidential.
c. Use a moving median filter to filter sensor reading results.
i. Write a moving median filter function to filter sensor reading results.
ii. If you could not answer this question, move to next one and use 
“float filter_sensor_value(float raw_sensor_value, uint8_t 
window_size);”.
d. Filtered data must be stored in memory. Queue filtered sensors’ data. 
i. Store desired amount of data in a static allocated buffer.
ii. Use LIFO method.
iii. If overflow occurs, discard oldest data.
iv. If you could not answer this question, move to next one and use 
“int buffer_get_value(struct buf_handle_t *p_handle, float 
*p_sensor_data);”. (Returns 0 on success)
e. By specifying an interval value for period send the measurement results stored 
in the buffer using Bluetooth Low Energy. 
i. Device should act as a peripheral (broadcaster) device that are 
responsible for sending the BLE Packets.
ii. Each sensor data should be stored in a different BLE packets.
Compress the packet with any method you choose for bonus points.
iii. Observe the BLE packet from your Bluetooth scanner device. (Phone, 
BLE MCU, etc.) Share the results in your report. 
2. Bonus Part 
a. Under RTOS, define two concurrent tasks. One of them (sensor task) reads 
sensor data from I2C and puts it into a buffer and the other one (filter task) 
sleeps on a semaphore. When new data is ready in the buffer, the sensor task 
signals semaphore and wakes the filter task up. Then, the filter task reads the 
value and apply filter operation (defined in other assignments) on it. After 
filtering, filtered data is going to be send with BLE packet.
b. Define race condition between two tasks and implement solution.
c. The sensor task is producer, and the filter task is consumer. Define a case that 
consumer can't reach the speed of the producer. Generate a log for this case, 
decide the fate of the last read sensor data, explain your solution and reasons 
for this case and finally implement your solution.
Note:
- You can freely increase the number of tasks if your design needs it