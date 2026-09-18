#include <gtest/gtest.h>

extern "C"
{
#include "system_types.h"
#include "state_machine.h"
#include "fault_manager.h"
#include "pid.h"
}


/*
 * Test that ignition OFF places the system
 * in the OFF state.
 */
TEST(StateMachineTest, IgnitionOff)
{
    SystemState state;

    state = StateMachine_Update(false,
                                true,
                                true,
                                70.0f);

    EXPECT_EQ(state, STATE_OFF);
}


/*
 * Test normal operating conditions.
 */
TEST(StateMachineTest, NormalOperation)
{
    SystemState state;

    state = StateMachine_Update(true,
                                true,
                                true,
                                70.0f);

    EXPECT_EQ(state, STATE_NORMAL);
}


/*
 * Test low coolant fault detection.
 */
TEST(FaultManagerTest, LowCoolant)
{
    FaultCode fault;

    fault = FaultManager_Check(false,
                               true,
                               70.0f);

    EXPECT_EQ(fault, FAULT_LOW_COOLANT);
}


/*
 * Test that the PID output does not
 * exceed 100 percent.
 */
TEST(PIDTest, OutputLimitedTo100Percent)
{
    PID_t pid;

    PID_Init(&pid,
             5.0f,
             0.1f,
             0.5f);

    float output = PID_Update(&pid,
                              65.0f,
                              100.0f,
                              1.0f);

    EXPECT_LE(output, 100.0f);
}