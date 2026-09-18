#ifndef CAN_SIM_H
#define CAN_SIM_H

#include <stdint.h>
#include <stdbool.h>

#include "system_types.h"

/* CAN message identifiers */
#define CAN_ID_SENSOR_DATA      0x100
#define CAN_ID_COOLING_COMMAND  0x200


/*
 * Basic CAN frame.
 * Standard CAN allows up to 8 data bytes.
 */
typedef struct
{
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8];

} CAN_Message_t;


/*
 * Decoded sensor information received over CAN.
 */
typedef struct
{
    float temperature_c;
    bool ignition_on;
    bool coolant_level_ok;

} SensorData_t;


/*
 * Creates a simulated sensor CAN message.
 */
CAN_Message_t CAN_CreateSensorMessage(float temperature,
                                      bool ignition_on,
                                      bool coolant_level_ok);


/*
 * Decodes CAN sensor data into usable values.
 *
 * Returns true if the message is valid.
 */
bool CAN_DecodeSensorMessage(const CAN_Message_t *message,
                             SensorData_t *sensor_data);


/*
 * Creates the outgoing pump/fan control CAN message.
 */
CAN_Message_t CAN_CreateCoolingCommand(float pump_percent,
                                       float fan_percent,
                                       SystemState state,
                                       FaultCode fault);


/*
 * Displays a transmitted CAN message.
 */
void CAN_Send(const CAN_Message_t *message);

#endif