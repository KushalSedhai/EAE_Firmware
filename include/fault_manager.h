#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H

#include <stdbool.h>
#include "system_types.h"

/*
 * Checks the cooling system inputs and returns
 * the active fault code.
 */
FaultCode FaultManager_Check(bool coolant_level_ok,
                             bool can_ok,
                             float temperature);

#endif