#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "system_types.h"
#include "fault_manager.h"
#include "state_machine.h"
#include "pid.h"
#include "cooling_control.h"
#include "can_sim.h"


int main(int argc, char *argv[])
{
    /* Temperature setpoint for the cooling system */
    float setpoint = 65.0f;

    /*
    * Check if a temperature setpoint was provided
    * through the command line.
    *
    * Example:
    * ./eae_firmware --setpoint 70
    */
    if (argc == 3)
    {
        if (strcmp(argv[1], "--setpoint") == 0)
        {
            setpoint = (float)atof(argv[2]);
        }
    }

    /* Simulation time step */
    float dt = 1.0f;

    /* Create the PID controller */
    PID_t fan_pid;

    /* Variables used during the simulation */
    SensorData_t sensor_data;
    FaultCode fault;
    SystemState state;
    CoolingOutput output;

    CAN_Message_t sensor_message;
    CAN_Message_t command_message;

    bool can_ok;


    /*
     * Initialize the fan PID controller.
     *
     * These values are only starting values for
     * the cooling system simulation.
     */
    PID_Init(&fan_pid,
             5.0f,
             0.1f,
             0.5f);


    printf("EAE Cooling Firmware Simulation\n");
    printf("--------------------------------\n");
    printf("Temperature Setpoint: %.1f C\n\n", setpoint);


    /*
     * -------------------------------------------------
     * Simulation 1
     * Normal operating condition
     * -------------------------------------------------
     */

    sensor_message = CAN_CreateSensorMessage(60.0f,
                                             true,
                                             true);

    can_ok = CAN_DecodeSensorMessage(&sensor_message,
                                     &sensor_data);

    fault = FaultManager_Check(sensor_data.coolant_level_ok,
                               can_ok,
                               sensor_data.temperature_c);

    state = StateMachine_Update(sensor_data.ignition_on,
                                sensor_data.coolant_level_ok,
                                can_ok,
                                sensor_data.temperature_c);

    output = CoolingControl_Update(state,
                                   &fan_pid,
                                   setpoint,
                                   sensor_data.temperature_c,
                                   dt);

    command_message = CAN_CreateCoolingCommand(output.pump_percent,
                                               output.fan_percent,
                                               state,
                                               fault);

    printf("Temperature: %.1f C\n", sensor_data.temperature_c);
    printf("Pump: %.1f %%\n", output.pump_percent);
    printf("Fan: %.1f %%\n", output.fan_percent);

    CAN_Send(&command_message);

    printf("\n");


    /*
     * -------------------------------------------------
     * Simulation 2
     * Temperature increases
     * -------------------------------------------------
     */

    sensor_message = CAN_CreateSensorMessage(72.0f,
                                             true,
                                             true);

    can_ok = CAN_DecodeSensorMessage(&sensor_message,
                                     &sensor_data);

    fault = FaultManager_Check(sensor_data.coolant_level_ok,
                               can_ok,
                               sensor_data.temperature_c);

    state = StateMachine_Update(sensor_data.ignition_on,
                                sensor_data.coolant_level_ok,
                                can_ok,
                                sensor_data.temperature_c);

    output = CoolingControl_Update(state,
                                   &fan_pid,
                                   setpoint,
                                   sensor_data.temperature_c,
                                   dt);

    command_message = CAN_CreateCoolingCommand(output.pump_percent,
                                               output.fan_percent,
                                               state,
                                               fault);

    printf("Temperature: %.1f C\n", sensor_data.temperature_c);
    printf("Pump: %.1f %%\n", output.pump_percent);
    printf("Fan: %.1f %%\n", output.fan_percent);

    CAN_Send(&command_message);

    printf("\n");


    /*
     * -------------------------------------------------
     * Simulation 3
     * High temperature warning
     * -------------------------------------------------
     */

    sensor_message = CAN_CreateSensorMessage(85.0f,
                                             true,
                                             true);

    can_ok = CAN_DecodeSensorMessage(&sensor_message,
                                     &sensor_data);

    fault = FaultManager_Check(sensor_data.coolant_level_ok,
                               can_ok,
                               sensor_data.temperature_c);

    state = StateMachine_Update(sensor_data.ignition_on,
                                sensor_data.coolant_level_ok,
                                can_ok,
                                sensor_data.temperature_c);

    output = CoolingControl_Update(state,
                                   &fan_pid,
                                   setpoint,
                                   sensor_data.temperature_c,
                                   dt);

    command_message = CAN_CreateCoolingCommand(output.pump_percent,
                                               output.fan_percent,
                                               state,
                                               fault);

    printf("Temperature: %.1f C\n", sensor_data.temperature_c);
    printf("Pump: %.1f %%\n", output.pump_percent);
    printf("Fan: %.1f %%\n", output.fan_percent);

    CAN_Send(&command_message);

    printf("\n");


    /*
     * -------------------------------------------------
     * Simulation 4
     * Low coolant fault
     * -------------------------------------------------
     */

    sensor_message = CAN_CreateSensorMessage(75.0f,
                                             true,
                                             false);

    can_ok = CAN_DecodeSensorMessage(&sensor_message,
                                     &sensor_data);

    fault = FaultManager_Check(sensor_data.coolant_level_ok,
                               can_ok,
                               sensor_data.temperature_c);

    state = StateMachine_Update(sensor_data.ignition_on,
                                sensor_data.coolant_level_ok,
                                can_ok,
                                sensor_data.temperature_c);

    output = CoolingControl_Update(state,
                                   &fan_pid,
                                   setpoint,
                                   sensor_data.temperature_c,
                                   dt);

    command_message = CAN_CreateCoolingCommand(output.pump_percent,
                                               output.fan_percent,
                                               state,
                                               fault);

    printf("Temperature: %.1f C\n", sensor_data.temperature_c);
    printf("Pump: %.1f %%\n", output.pump_percent);
    printf("Fan: %.1f %%\n", output.fan_percent);

    CAN_Send(&command_message);


    return 0;
}

