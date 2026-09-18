#include "fault_manager.h"

/* Valid temperature sensor range */
#define TEMP_MIN_C   (-40.0f)
#define TEMP_MAX_C   150.0f


FaultCode FaultManager_Check(bool coolant_level_ok,
                             bool can_ok,
                             float temperature)
{
    /* Low coolant could damage the cooling system */
    if (!coolant_level_ok)
    {
        return FAULT_LOW_COOLANT;
    }

    /* Temperature outside the expected sensor range */
    if ((temperature < TEMP_MIN_C) || (temperature > TEMP_MAX_C))
    {
        return FAULT_TEMP_SENSOR;
    }

    /* Communication with the CAN device has been lost */
    if (!can_ok)
    {
        return FAULT_CAN_TIMEOUT;
    }

    /* No faults detected */
    return FAULT_NONE;
}