#include "can_sim.h"

#include <stdio.h>


CAN_Message_t CAN_CreateSensorMessage(float temperature,
                                      bool ignition_on,
                                      bool coolant_level_ok)
{
    CAN_Message_t message;

    /*
     * Convert temperature into 0.1 degree units.
     *
     * Example:
     * 72.5 C becomes 725.
     */
    int16_t temperature_raw = (int16_t)(temperature * 10.0f);

    message.id = CAN_ID_SENSOR_DATA;
    message.dlc = 4;

    /*
     * Store the 16-bit temperature value
     * using two CAN data bytes.
     */
    message.data[0] = (uint8_t)(temperature_raw & 0xFF);
    message.data[1] = (uint8_t)((temperature_raw >> 8) & 0xFF);

    /*
     * Boolean values are represented using 0 or 1.
     */
    message.data[2] = ignition_on ? 1 : 0;
    message.data[3] = coolant_level_ok ? 1 : 0;

    return message;
}



bool CAN_DecodeSensorMessage(const CAN_Message_t *message,
                             SensorData_t *sensor_data)
{
    int16_t temperature_raw;

    /*
     * Make sure this is the message we expect.
     */
    if (message->id != CAN_ID_SENSOR_DATA)
    {
        return false;
    }

    /*
     * Make sure the message contains enough bytes.
     */
    if (message->dlc < 4)
    {
        return false;
    }

    /*
     * Rebuild the 16-bit temperature value
     * from the two CAN bytes.
     */
    temperature_raw =
        (int16_t)((uint16_t)message->data[0] |
                 ((uint16_t)message->data[1] << 8));

    /*
     * Convert back to degrees Celsius.
     */
    sensor_data->temperature_c =
        (float)temperature_raw / 10.0f;

    sensor_data->ignition_on =
        message->data[2] != 0;

    sensor_data->coolant_level_ok =
        message->data[3] != 0;

    return true;
}

CAN_Message_t CAN_CreateCoolingCommand(float pump_percent,
                                       float fan_percent,
                                       SystemState state,
                                       FaultCode fault)
{
    CAN_Message_t message;

    message.id = CAN_ID_COOLING_COMMAND;
    message.dlc = 4;

    /*
     * Pump and fan commands are already limited
     * between 0 and 100 percent.
     */
    message.data[0] = (uint8_t)pump_percent;
    message.data[1] = (uint8_t)fan_percent;

    /*
     * System state and fault values come
     * directly from their enum values.
     */
    message.data[2] = (uint8_t)state;
    message.data[3] = (uint8_t)fault;

    return message;
}

void CAN_Send(const CAN_Message_t *message)
{
    uint8_t i;

    printf("CAN TX | ID: 0x%03X | Data: ",
           (unsigned int)message->id);

    for (i = 0; i < message->dlc; i++)
    {
        printf("%02X ", message->data[i]);
    }

    printf("\n");
}