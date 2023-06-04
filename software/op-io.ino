#include <MIDI.h>  // Add Midi Library

#define LED 13    // Arduino Board LED is on Pin 13

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

boolean on = false;

void setup() {
  Serial.begin(31250);
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output
  pinMode(5, OUTPUT);
  MIDI.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library.
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  MIDI.setHandleClock(myClock); // This is important!! This command
//  MIDI.setHandleStart(myStart);
//  MIDI.setHandleStop(myStop);
//  MIDI.setHandleContinue(myContinue);

  Serial.println("Set up MIDI listeners");

  // USB MIDI stuff
//  usbMIDI.setHandleStop(myUSBStop);
//  usbMIDI.setHandleStart(myUSBStart);
//  usbMIDI.setHandleContinue(myUSBContinue);
//  usbMIDI.setHandleClock(myUSBClock);
}

void loop() { // Main loop
  MIDI.read(); // Continuously check if Midi data has been received.
//  usbMIDI.read(); // Continuously check if MIDI data on USB
}

void myClock() {
  Serial.println("Clock");
//  usbMIDI.sendRealTime(usbMIDI.Clock);
}

void myUSBClock() {
  // do nothing
  on = !on;
  if(on) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}

void myStart() {
  Serial.println("Start");
  usbMIDI.sendRealTime(usbMIDI.Start);
  digitalWrite(13, HIGH);
}

void myContinue() {
  Serial.println("Continue");
  usbMIDI.sendRealTime(usbMIDI.Continue);
  digitalWrite(13, HIGH);
}

void myStop() {
  Serial.println("Stop");
  usbMIDI.sendRealTime(usbMIDI.Stop);
}

void myUSBStop() {
  digitalWrite(13, LOW);
  Serial.println("Stop");
  MIDI.sendStop();
}

void myUSBStart() {
  digitalWrite(13, HIGH);
}

void myUSBContinue() {
  digitalWrite(13, HIGH);
}

// MyHandleNoteON is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOn(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED,HIGH);  //Turn LED on
  Serial.println("Note On");
}

// MyHandleNoteOFF is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOff(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED,LOW);  //Turn LED off
  Serial.println("Note Off");
}
