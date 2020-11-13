# StateMachineEmbedded

### TLDR: How do I download ZIP library for Arduino IDE?
0. Click *Releases* to the right
2. Download the .zip file
3. Open Arduino IDE and click **Sketch -> Include Library -> Import ZIP library**
4. To use the library in a project click **Sketch -> Include Library -> StateMachineEmbedded**
5. To see examples, click **File -> Examples -> StateMachineEmbedded**

### What it does

This project is the result of an attempt to develop a function-pointer-managing-final-statemachine,
which makes it easier to develop code with transitions between states in embedded systems.

### Memory safe
It can map up to `128` functions as states, and due to memory restrictions on small devices, these are statically allocated arrays of fixed size.

### Key/Value pair-like syntax
To add a state to the machine, you bind a function pointer to an object of your choice. The StateMachine uses templates, so you can use enums, strings, integers or anything of your liking to access your functions in the machine. *demo below* 

### Provides a good design, helping to keep the project clean
The StateMachine allows you to outsource the order of states and which is next in line. At the end of an implementation, the main loop could look like this:

```c
void loop()
{
    mystateMachine.next()();
}
```
.. or if you don't fancy the double (), like this:
```c
fp_t func;

void loop()
{
    func = mystateMachine.next();
    func();
}
```


### The problem it aims to solve

Developing for IOT and embedded systems can usually generate lots of undesired spaghetti code.

Due to the nature of the environment on a small system where memory is limited and the `loop` function where you continuously want to be listening for input/outputs from sensors or devices and not be blocking, the fact that the device can listen to these devices is **crucial.**

A function which calls a function... which, calls a function. But only if that other function did something... hmmm.. global variables.  And then  a call to main. right? 

See, this is dangerous and a quick path to stack overflow where the stack never gets the opportunity to return stack memory from it's previous execution. 

The StateMachine will allow the `loop` function to continuously call **one** function which will point to the correct function, at the right time. Every function will return stack memory, and at the end of the call stack, the `main` method (state) will always be defaulted to, automatically, for your device to keep listening to radio, check buttons and perform other crucial tasks. 

### How to use it

The idea here is that you have one function which is *not* looping and blocking but rather the default function that will be called, over and over and over. In this function, you can use `millis` or equivalent technique to determine whether it's time to check key presses or perform other tasks. 

When it's time, from this **main state**, you use the `transitionTo()` method to tell the machine which state you want to be next in order. When your main method is out of scope (exhausted), the State Machine will automatically point the `loop` to the right function. 

When this is performed and done, your **main state** function will automatically be defaulted to and called over and over again until it calls `transitionTo()` again. 

The **StateMachine** will automatically revert to the idle function where you have code that read sensors, send things to WiFi or whatever else. Recursion is also taken care of - no risk of a function assigning itself as next in line - it's not allowed to.

Inside of a state function you can ask the **StateMachine** instance which state it is in at the moment, if it is not evident. You cannot however alter the state manually outside of the `main method` which is defined upon instantiation.

Each state is responsible of letting go of it's own state by caling `StateMachineInstance.release()` before they run out of scope. If a function misbehaves and skips this,
the StateMachine instance will revert to it's mainstate automatically as to prevent endless loops and blocking code. This, however will interrupt the method's chained state, if it had one defined, which will not run in that case.

### Chained states

Automatically returning to the main state is great and all, but sometimes we need one state to transition to another automatically and bypassing the main state, for a pre-defined sequence. 

This can be attained by "chaining" a state with another one in the State Machine.

### Here's a full example also demonstrating Chained states:

```c
#include "StateMachine.h"

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
    sm.setChainedState(MyArduinoStates::STOP_STEPPER_MOTOR, MyArduinoStates::STOP_STEPPER_MOTOR);
    
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
```



The following sketch is just a small example, without buttons or sensors obviously. 

It yields the following output in the Serial monitor:

```
...
22:36:28.999 -> Inside idle function
22:36:29.046 -> Inside startStepperMotor function
22:36:29.046 -> Inside stopStepperMotor function
22:36:29.092 -> Inside idle function
22:36:29.138 -> Inside checkMotorTemp function
22:36:29.138 -> Inside idle function
22:36:29.185 -> Inside checkMotorTemp function
22:36:29.185 -> Inside idle function
22:36:29.231 -> Inside checkMotorTemp function
22:36:29.276 -> Inside idle function
22:36:29.276 -> Inside startStepperMotor function
22:36:29.322 -> Inside stopStepperMotor function

....

As you can see, it will automatically revert to the main state and perform the check. 
Every quarter second it will run the motor. The StartStepperMotor is chained to the StopStepperMotor function,
so the motors stop. In the meantime, the device can check the temperature of the motor. 

This is maybe not the best state alteration design for a motor control device but it's just to illustrate
how to develop with this library. 
```



### Author

Simon Olofsson, dotchetter



### Contributions

Contributions to this project is more than welcome. Arduino and embedded is not my main domain but I really enjoy it and I hope this library makes it as much more easy and fun for you as it did for me! 
