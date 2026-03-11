# Digital Clock
An arduino based digital clock built inside the shell of an old diaphanoscope for dentists. With fun lamp options activated through the switches, a manual bright mode and automatic dimming for the night time and a color + brightness change in very bright environments thanks to a photoresistor. 
Necessary components are: 
 - Arduino nano board,
 - RTC external component for Serial communication,
 - a configurable number of programmable multicolor leds,
 - 2 toggle swithces,
 - 5 10k resistors,
 - 1 photoresistor.
 
<img width="640" height="520" alt="circuit" src="https://github.com/user-attachments/assets/56992882-4fb9-4fb8-ac2d-e708db960241" />

I strongly reccomend the use of an external power supply, and not to power the whole project thorough the arduino usb input (I used 40W one, even if it's a bit an overkill).

![PXL_20260311_185833964](https://github.com/user-attachments/assets/b49aa912-26b0-4f55-bd64-a8d93ffbf0db)

![PXL_20260311_185816040](https://github.com/user-attachments/assets/c2874f43-18b6-42fb-b020-74646128af78)

![PXL_20260311_185841173](https://github.com/user-attachments/assets/df9ebe18-d171-4d64-926c-04016a404a75)

The clock has 4 different modes encoded through the position of the two switches:
 - Orange clock with automatic brightness adjustement
 - Bright clock
 - Lamp
 - Off
In order to set the time, simply run the project SetTime that you find in the folder Utils. This snipet will communicate through the arduino serial with the rtc, setting the time in the rtc chip. The set time will be kept in memory even after uploading the clock-lamp code. 


Freely inspired by : https://www.instructables.com/Ping-Pong-Ball-LED-Clock/
