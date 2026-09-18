#include "state_machine.h"

/*
 * Valid operating range of the temperature sensor.
 * Values outside this range are treated as a sensor fault.
 */
#define TEMP_MIN_C   (-40.0f)
#define TEMP_MAX_C   150.0f


SystemState StateMachine_Update(bool ignition_on,
                                bool coolant_level_ok,
                                bool can_ok,
                                float temperature)
{
    /* Ignition OFF means the cooling system should be OFF */
    if (!ignition_on)
    {
        return STATE_OFF;
    }

    /* Low coolant is considered a critical fault */
    if (!coolant_level_ok)
    {
        return STATE_FAULT;
    }

    /* Loss of CAN communication is considered a fault */
    if (!can_ok)
    {
        return STATE_FAULT;
    }

    /* Check whether the temperature sensor reading is reasonable */
    if ((temperature < TEMP_MIN_C) || (temperature > TEMP_MAX_C))
    {
        return STATE_FAULT;
    }

    /* High temperature places the system into warning mode */
    if (temperature > WARNING_TEMP_C)
    {
        return STATE_WARNING;
    }

    /* All normal operating conditions are satisfied */
    return STATE_NORMAL;
}