#ifndef SYSTEM_TYPES_H
#define SYSTEM_TYPES_H

/* Possible operating states of the cooling system */
typedef enum
{
    STATE_OFF = 0,
    STATE_NORMAL,
    STATE_WARNING,
    STATE_FAULT

} SystemState;


/* Possible faults in the cooling system */
typedef enum
{
    FAULT_NONE = 0,
    FAULT_LOW_COOLANT,
    FAULT_TEMP_SENSOR,
    FAULT_CAN_TIMEOUT

} FaultCode;

#endif