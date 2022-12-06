# lcdHelper platform.io example
This is an example of how to use all lcdHelper functions, packaged inside an PIO environment so you can try it out as easily as possible (if you are using PIO (which you should, it's amazing)).  

The example is made for an 4x20 HD44780 LCD display so if you are using a smaller version this won't work out of the box (or you just won't see everything).  
Customize the `platformio.ini` config if you are using a different board than an ESP8266 devkit.  

I included a copy of `LiquidCrystal_I2C` in the `lib` folder, the include path of `arduino-lcdHelper-library` however is local and points to the `project_root/src` folder, so you can only use this example in the given folder structure.  
To use the lib like in the example in your own project, put the library into the `lib` folder like explained in the README.

&nbsp;

Open the example folder inside VsCode with PlatformIO installed.  
If your board and upload_port in `platformio.ini` are correct and your 4x20 display is connected to D1 and D2 (aka the same as mine) then you should be able to just press the PlatformIO Upload button.  

&nbsp;

And if you don't have a PlatformIO setup or don't want to bother with configuring if you don't have the same setup then you can ofc just look at the implementations of each function inside `example.cpp` and use them in your own project.

&nbsp;
&nbsp;

This text is a mess.