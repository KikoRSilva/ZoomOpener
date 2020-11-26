# ZoomOpener
This program written in C opens automatically your online classes. 
You just need to set your schedule with some specified format.
And then run it (in Linux at this time).
## Formatting your Schedule
### src Folder
So you have a folder called 'src' where there is 6 files: 
  - HORARIO.txt
  - Mon.txt
  - Tue.txt
  - Wen.txt
  - Thu.txt
  - Fri.txt

### HORARIO.txt file
The file **HORARIO.txt** is where you set the name of your classes per day.
For example:<br>
"
Sun=<br>
Mon=MATHS,SCIENCE,ARTS<br>
Tue=PE,ENGLISH, SPANISH, PHYSICS<br>
Wen=MATHS<br>
Thu=ARTS,SCIENCE,GEOGRAPHY<br>
Fri=ARTS,PE<br>
Sat=<br>
"

***Attention: The class names must be in CAPSLOCK.***

### Classes file
For each file class, like **Mon.txt**, you have to write:
  - name (CAPSLOCK)
  - starting hour (hh:mm:ss)
  - ending hour (hh:mm:ss)
  - url
  - password (*if necessary*)
The format in each line is: **"NAME|XX:XX:XX|XX:XX:XX|url|password"**

***Attention: You must use as delimiter this charcter '|'.***

## Project Info
**Author**: Francisco Ribeiro e Silva *aka* **@me**<br>
**Language**: C<br>
**Date**: 25/11/2020<br>
**Platform supported**: Linux<br>
**License**: This project is licensed under the terms of the MIT license.<br>

 
 
 

