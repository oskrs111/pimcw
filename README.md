# pimcw
pi Meets Craftwork, some fun tools to be used in a hobby enviroment!

-- Remote MIDI and/or WEB PWM LED control for Raspberry Pi --

Up to now this is a hobby project to build a simple application to control some LED using a Raspberry Pi board plus an
Ardafruit PCA9685 Board (https://www.adafruit.com/products/815), plus a custom mosfet-to-led interface.

All the applications has been built using Qt5.

In the early beginning the main goal was to have a built in sequencer to be able to perform some light choreographies 
but later I realised that maybe MIDI driven led control back-light, will be a better, and more versatile choice.

Finally MIDI driven LED control is developed. So the 'toolset' is composed by 2 applications; One is the MIDI-to-Ethenet
application that runs in Windows environment, called 'discoFever', and on the server side there is the Ethernet-to-PCA9685 
application that runs on a Raspberry Pi B+ (RASPBIAN distribution), called 'toniManero' (... yes toni not tony i know ...).

'discoFever' uses a great Virtual MIDI interface (http://www.tobias-erichsen.de/software/virtualmidi.html) from Tobias Erichsen that runs perfectly on a Windows machine (it allows you to send MIDI to RasPi from your favourite sequencer!!!). 
Due its license restrictions you have to download the Virtual MIDI SDK from his web in order to can compile the application. 
What you will find here is a 'qtkvirtualmidi' Qt Style class for VirtualMIDI driver usage.

Note that MIDI-to-Ethernet protocol is fairly simple and straightforward. Just receive MIDI events from driver and send via UDP to Raspbery Pi. Only a redundance mechanism is added to protocol because unfortunately (and unexpected) Raspberry Pi is
loosing UDP frames. No plans for MIDI over RTP support because is too much sophisticated protocol to just control a simple LED.

'toniManero' is the Ethernet-to-PCA9685 server for RasPi, that also has a WEB server that allows also to control the LED directly. So you can feed 'toniMAnero' via MIDI or RPC commands via WEB.

Binary files for Raspberry Pi (RASPBIAN) are on /release/arm/ folder. 
Just copy on /home/tonimanero/ folder at Raspberry Pi and follow README instructions to setup and run.

Enjoy.

November 2016 Update:
Added some interesting piece of hardware to drive incandescent light bulbs from PCA9685 pwm outputs.
Schematic is available on /hardware/schematics/ folder. 





