# Using_Gravity_to_Find_Stars

The software provided here is for an App that uses the Earth’s gravity vector to set up digital setting circles for pointing telescopes on equatorial mounts at stars.

The system uses the accelerometers on two Arduino boards to sense gravity and they are attached to a telescope using 3M Extreme fasteners. It can be used on both PushTo or GoTo mounts.

Parts required include the two Arduino Nano 33 BLE boards, two small enclosures to contain them, a small roll of foam tape, a pack of 3M extreme stickers, and an Android mobile phone.

Tools required include strong scissors, a Phillips head screwdriver, and ideally some knowledge of basic astronomy, high school geometry, and trigonometry.

The PDF document *PushTo - Using Gravity to Find Stars* provides an overview, operating manual, calibration manual, and maths background. See also the video [PushTo](https://youtu.be/6MyYuS1f6ZM).

**The source code and files include:**

- PushToA_NanoBLE33.ino

  *Code for compilation and installation on an Arduino Nano 33 BLE board to act as a declination sensor.*
- PushToB_NanoBLE33.ino.

  *Code for compilation and installation on an Arduino Nano 33 BLE board  to act as an hour-angle sensor.*
- PushTo_v1.aia.

  *Code for compilation using MIT AppInventor, for installation as an APK file on an Android phone.*
- CalibrationTemplate.txt

  *An empty text file to hold the calibration values*
- DatabaseTemplate.csv

  *An empty CSV file to hold the star database*

**To install the software:**
  - Set up a directory called PushTo on the Android phone and copy the text and CSV files into the directory.
  - Import PushTo.aia into App Inventor, compile, then transfer the App to the phone using Google Drive.
  - Compile and install the Arduino code in the Arduino A and B sensors.
  
**Links to the compilers for these programs are at:**
  - https://appinventor.mit.edu/explore/get-started
  - https://www.arduino.cc/

