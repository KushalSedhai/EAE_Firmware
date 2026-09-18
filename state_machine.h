#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stdbool.h>
#include "system_types.h"

/* Warning temperature threshold in degrees Celsius */
#define WARNING_TEMP_C 80.0f

/*
 * Determines the current state of the cooling system.
 */
SystemState StateMachine_Update(bool ignition_on,
                                bool coolant_level_ok,
                                bool can_ok,
                                float temperature);

#endif
