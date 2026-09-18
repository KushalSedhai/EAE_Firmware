#include "cooling_control.h"

#define NORMAL_PUMP_PERCENT    60.0f
#define WARNING_PUMP_PERCENT  100.0f


CoolingOutput CoolingControl_Update(SystemState state,
                                    PID_t *fan_pid,
                                    float setpoint,
                                    float temperature,
                                    float dt)
{
    CoolingOutput output;

    /*
     * Start with both outputs OFF.
     * The state machine will determine whether
     * they should be enabled.
     */
    output.pump_percent = 0.0f;
    output.fan_percent = 0.0f;

    switch (state)
    {
        case STATE_OFF:

            /*
             * Ignition is OFF.
             * Cooling system remains OFF.
             */
            output.pump_percent = 0.0f;
            output.fan_percent = 0.0f;

            break;


        case STATE_NORMAL:

            /*
             * During normal operation the pump runs
             * at a fixed speed and the fan is
             * controlled by the PID.
             */
            output.pump_percent = NORMAL_PUMP_PERCENT;

            output.fan_percent = PID_Update(fan_pid,
                                            setpoint,
                                            temperature,
                                            dt);

            break;


        case STATE_WARNING:

            /*
             * High temperature detected.
             * Run the pump at full speed while the
             * PID continues controlling the fan.
             */
            output.pump_percent = WARNING_PUMP_PERCENT;

            output.fan_percent = PID_Update(fan_pid,
                                            setpoint,
                                            temperature,
                                            dt);

            break;


        case STATE_FAULT:

            /*
             * A critical fault has been detected.
             * Stop the pump and fan for safety.
             */
            output.pump_percent = 0.0f;
            output.fan_percent = 0.0f;

            break;


        default:

            /*
             * Unexpected state.
             * Use the safest output condition.
             */
            output.pump_percent = 0.0f;
            output.fan_percent = 0.0f;

            break;
    }

    return output;
}