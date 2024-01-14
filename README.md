# ArduinoKeyboardClient
 
A little program to set up a keyboard using an Arduino board. It supports 32 different bindings. Supports **keybinds**.

## How it works

- Arduino board is supposed to send an index [0..32] of a binding via a COM port when a physical button is pressed.
- Before use one must scan the available COM ports first, and select the one the board is connected to (might require drivers).
- Then you should click on the field next to a chosen binding index, and press a key/keybinding that should be triggered when the board sends the index to the PC via the COM port.
- Click the "Connect" button.
- Press the buttons, and observe how the button essentially acts like a keyboard key(s). The keys are virtually pressed down **AND** up immediately.

---

The UI written with [**SFML 2.5.1**](https://www.sfml-dev.org/).
