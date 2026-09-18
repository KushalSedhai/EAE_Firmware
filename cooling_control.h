#ifndef COOLING_CONTROL_H
#define COOLING_CONTROL_H

#include "system_types.h"
#include "pid.h"

/*
 * Stores the output commands for the cooling system.
 */
typedef struct
{
    float pump_percent;
    float fan_percent;

} CoolingOutput;


/*
 * Calculates the pump and fan commands
 * based on the current system state.
 */
CoolingOutput CoolingControl_Update(SystemState state,
                                    PID_t *fan_pid,
                                    float setpoint,
                                    float temperature,
                                    float dt);

#endif