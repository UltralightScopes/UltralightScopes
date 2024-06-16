# Using_Gravity_to_Find_Stars 

THE CODE AND OPERATING MANUAL FOR THIS REPOSITORY WILL BE UPDATED IN JULY 2024. IT WILL HAVE SIMPLIFIED CALIBRATION AND MORE GENERAL STAR FINDER ALGORITHMS 
THE CURRENT CODE AND MANUAL HAS BEEN REMOVED BUT CAN BE SUPPLIED ON REQUEST

This App uses the Earth’s gravity vector to point telescopes on equatorial mounts at stars.

The system uses the accelerometers on two Arduino boards to sense gravity and they are attached to a telescope using 3M Extreme fasteners. It can be used on both PushTo or motorised mounts.

Parts required include two Arduino Nano 33 BLE boards, two small enclosures to contain them, a roll of foam tape, a pack of 3M extreme stickers, and an Android mobile phone.

Tools required include strong scissors, a Phillips head screwdriver, and ideally some basic astronomy, high school geometry, and trigonometry knowledge.

The PDF document *Using Gravity to Find Stars* provides an overview, operating manual, calibration manual, and maths background. See also the video [Using gravity to find stars](https://youtu.be/bQ3izaqIlxg)]

**The source code and files include:**

- PushToA_NanoBLE33.ino

  *Code for compilation and installation on an Arduino Nano 33 BLE board to act as a declination sensor.*
- PushToB_NanoBLE33.ino.

  *Code for compilation and installation on an Arduino Nano 33 BLE board  to act as an hour-angle sensor.*
- PushTo_v1_2.aia.

  *Code for compilation using MIT AppInventor, for installation as an APK file on an Android phone.*
- CalibrationTemplate.txt

  *An empty text file to hold the calibration values*
- DatabaseTemplate.csv

  *An empty CSV file to hold the star database*

**To install the software:**
  - Set up a PushTo directory on the Android phone and copy the text and CSV files into the directory.
  - Import PushTo_v1_2.aia into App Inventor, compile, then transfer the App to the phone using Google Drive.
  - Compile and install the Arduino code in the A and B sensors.
  
**Links to the compilers for these programs are at:**
  - https://appinventor.mit.edu/explore/get-started
  - https://www.arduino.cc/

