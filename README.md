# ArduinoKeyboardClient
 
A little program to set up a keyboard using an Arduino board. It supports 32 different bindings.
Arduino board is supposed to send an index [0..32] of a binding via a COM port when a physical button is pressed.
Each value sent triggers the binded keys being virtually pressed down and up.
Supports keybinds.
UI written in SFML.
