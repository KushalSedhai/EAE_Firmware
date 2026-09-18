#ifndef PID_H
#define PID_H

typedef struct
{
    float kp;
    float ki;
    float kd;

    float integral;
    float previous_error;

} PID_t;


/*
 * Initializes the PID controller.
 */
void PID_Init(PID_t *pid,
              float kp,
              float ki,
              float kd);


/*
 * Calculates a new PID output.
 *
 * Output is limited from 0% to 100%.
 */
float PID_Update(PID_t *pid,
                 float setpoint,
                 float measured_temperature,
                 float dt);

#endif