// Convert an S.T.C. arcade trackball into a USB mouse. (No buttons.)

#include <Mouse.h>

const int X1 = 2;
const int X2 = 3;
const int Y1 = 4;
const int Y2 = 5;
const int ACCELERATION = 5;  // Factor to accelerate the mouse movement by.
const int SEND_INTERVAL = 100;  // How many read loops before we send a mouse movement.

int X1State = 0;
int X2State = 0;
int Y1State = 0;
int Y2State = 0;
int X1Prev = 0;
int X2Prev = 0;
int Y1Prev = 0;
int Y2Prev = 0;
int delta_X = 0;
int delta_Y = 0;
int counter = 0;

void setup() {
  // Intialise the digital input pins.
  pinMode(X1, INPUT);
  pinMode(X2, INPUT);
  pinMode(Y1, INPUT);
  pinMode(Y2, INPUT);
  // Make us pretend to be a USB mouse.
  Mouse.begin();
}

void loop() {
  // Read the values of the trackball opto-receptors.
  X1State = digitalRead(X1);
  X2State = digitalRead(X2);
  Y1State = digitalRead(Y1);
  Y2State = digitalRead(Y2);

  // If the X-axis states have changed
  if ((X1State ^ X1Prev) || (X2State ^ X2Prev)) {
    // Calculate the direction and inc/dev the delta.
    delta_X += ((X1State ^ X2State) ? -1 : 1) * ((X1State ^ X1Prev) ? 1 : -1);
  }
  // If the Y-axis states have changed
  if ((Y1State ^ Y1Prev) || (Y2State ^ Y2Prev)) {
    // Calculate the direction and inc/dev the delta.
    delta_Y += ((Y1State ^ Y2State) ? -1 : 1) * ((Y1State ^ Y1Prev) ? 1 : -1);
  }

  // Is it time to move the mouse?
  if (counter >= SEND_INTERVAL) {
    // Move the mouse.
    Mouse.move(delta_X * ACCELERATION, delta_Y * ACCELERATION, 0);
    // Reset the deltas and counter.
    delta_X = 0;
    delta_Y = 0;
    counter = 0;
  }

  // We are done, so save the state and inc the counter.
  X1Prev = X1State;
  X2Prev = X2State;
  Y1Prev = Y1State;
  Y2Prev = Y2State;
  counter += 1;
}
