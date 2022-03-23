# LED_Blinker
Arduino LED blinker without using delay()

This is my 1st "useful" projects learning C++.
The LED_blinker class allows one to blink an LED without using the delay() function in Arduino.

The features include:

-Ability to set the duration of the ON phase
-Ability to set the duration of the OFF phase
-Ability to set the duration of the entire blinking phase. So we can set it to blink for 10 seconds and then turn off.

It simply returns `TRUE` whenever the LED is supposed to be ON, and `FALSE` when it should be OFF.

Planned for next update:
-Ability to have it blink indefinitely.
