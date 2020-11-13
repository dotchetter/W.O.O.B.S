#include <StateMachine.h>


// compiler contract, we will define these later
void blinkLed();
void startStepperMotor();
void stopStepperMotor();
void checkMotorTemp();
void idle();

enum class MyArduinoStates
{
    IDLE, // MAIN state
    BLINK_LED,
    START_STEPPER_MOTOR,
    STOP_STEPPER_MOTOR,
    CHECK_MOTOR_TEMP
};

// Create a StateMachine
StateMachine<MyArduinoStates> sm = StateMachine<MyArduinoStates>(MyArduinoStates::IDLE, &idle);

void setup()
{
    // Add all the states which correlates to our functions
    sm.addState(MyArduinoStates::BLINK_LED, &blinkLed);
    sm.addState(MyArduinoStates::START_STEPPER_MOTOR, &startStepperMotor);
    sm.addState(MyArduinoStates::STOP_STEPPER_MOTOR, &stopStepperMotor);
    sm.addState(MyArduinoStates::CHECK_MOTOR_TEMP, &checkMotorTemp);
    
    // A chained mapping of state - the last one will run after the first one exhausts
    sm.setChainedState(MyArduinoStates::START_STEPPER_MOTOR, MyArduinoStates::STOP_STEPPER_MOTOR);
    
    Serial.begin(9600);
}

void blinkLed()
{
    Serial.println("Inside Blink Led function");
    sm.release();
}
void startStepperMotor()
{
    Serial.println("Inside startStepperMotor function");
    sm.release();
}
void stopStepperMotor()
{
    Serial.println("Inside stopStepperMotor function");
    sm.release();
}
void checkMotorTemp()
{
    Serial.println("Inside checkMotorTemp function");
    sm.release();
}

void idle()
{
    static unsigned long last_run_millis;

    Serial.println("Inside idle function");

    if (millis() - last_run_millis >= 250)
    {
        // The STOP_STEPPER_MOTOR state is chained - STOP_STEPPER_MOTOR will run after it, automatically.
        sm.transitionTo(MyArduinoStates::START_STEPPER_MOTOR);
        last_run_millis = millis();
    }
    else
    {
        // The state machine will return the pointer to this function next.
        sm.transitionTo(MyArduinoStates::CHECK_MOTOR_TEMP);
    }
    
    /*
        .. other code to perform during idle, like checking sensors etc.
    */
}


void loop()
{
    sm.next()();
}
