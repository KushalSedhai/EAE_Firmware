#include "pid.h"

#define PID_OUTPUT_MIN   0.0f
#define PID_OUTPUT_MAX   100.0f


void PID_Init(PID_t *pid,
              float kp,
              float ki,
              float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->integral = 0.0f;
    pid->previous_error = 0.0f;
}


float PID_Update(PID_t *pid,
                 float setpoint,
                 float measured_temperature,
                 float dt)
{
    float error;
    float derivative;
    float output;

    /*
     * For a cooling system, we want more cooling
     * when the measured temperature is above the setpoint.
     */
    error = measured_temperature - setpoint;

    /*
     * Accumulate the error over time.
     */
    pid->integral += error * dt;

    /*
     * Calculate how quickly the error is changing.
     */
    derivative = (error - pid->previous_error) / dt;

    /*
     * Standard PID equation.
     */
    output = (pid->kp * error)
           + (pid->ki * pid->integral)
           + (pid->kd * derivative);

    /*
     * Fan command cannot be below 0%.
     */
    if (output < PID_OUTPUT_MIN)
    {
        output = PID_OUTPUT_MIN;
    }

    /*
     * Fan command cannot exceed 100%.
     */
    if (output > PID_OUTPUT_MAX)
    {
        output = PID_OUTPUT_MAX;
    }

    /*
     * Store the current error for the next control cycle.
     */
    pid->previous_error = error;

    return output;
}