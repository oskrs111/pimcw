DEPENDENCES:
toniManero app has been tested on 'Linux raspberrypi 4.4.11+ #888 Mon May 23 20:02:58 BST 2016 armv6l GNU/Linux'
without problems.
You will need also a hardware part PCA9685 board like 'Adafruit 16-Channel 12-bit PWM/Servo Driver - I2C interface -' check
hardware.setup.pdf file for wiring details.

SETUP:
In order to get access to I2C module on Raspi is need to enable it on /boot/config.txt find and uncomment this line:

  dtparam=i2c_arm=on
  
Also you will need to add these lines on /etc/modules file

  i2c-bcm2708
  i2c-dev
  
Alternatively you have a 'raspi.config.txt' and 'raspi.modules' that are the files I am using on mine as a sample.

Next just copy this folder contents on Raspberry Pi tree, /home/tonimanero/ and reboot. Note that default state of PCA9685 will get
outputs to HIGH so leds or lights will be ON until toniManero starts.

As an option there are some parameters that can be set on toniManero.cfg file:

    "toniManero.i2c.i2cAddr": "64" --> Sets the PCA9685 i2c address.
    "toniManero.i2c.i2cBus": "1" --> Sets the i2c bus on Raspi
    "toniManero.midi.noteOffset": "0" --> Sets a value to substract from midi note number, used to offset the note vs channel.
    "toniManero.network.httpPort": "80" --> Sets the embedded http listening port.
    "toniManero.network.udpPort": "12340" --> Sets the 'discoFever' udp port.

RUN:
After reboot start the application with /home/tonimanero/ sudo toniManero. If everything worked fine lights should turn OFF.
If not check i2c driver state on Raspi and wiring with PCA9685 board. This is the current /dev/ devices on my Raspi

  user@raspberrypi:~ $ ls /dev | grep i2
  i2c-1
  
The fastest way to check the application is to open the embedded web interface. 
On a web browser type Raspi IPv4 local address, and 'toniManero Control' should appear. 

Enjoy.

