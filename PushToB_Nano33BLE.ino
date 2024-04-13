  // NanoBLE33

#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>
//#include <Arduino_HTS221.h>
#include <math.h>

// UUIDs created using https://www.uuidgenerator.net/
#define IMU_SERVICE_UUID "468c28f3-35a2-4fe8-9e68-be7942c4f152" 
#define IMU_TEMP_CHARACTERISTIC_UUID "66fbf839-f54e-4162-91a7-8c41464d4b0e"
#define IMU_XYZ_CHARACTERISTIC_UUID "bd38d6a4-d815-4e50-a9c0-7b9420043151"
#define IMU_SOUTH_CHARACTERISTIC_UUID "c8ed185c-25d9-4507-a6ad-7aeefcf6cc5e"

// IMU data is registered as a BLE service
BLEService imuService(IMU_SERVICE_UUID);

// Data characteristics
// The accelerometer XYZ data points are combined in one characteristic
BLECharacteristic imuXYZChar(IMU_XYZ_CHARACTERISTIC_UUID, BLERead | BLENotify,16);
// The magnetometer South data point (direction or heading - arc degrees) is one characteristic
BLECharacteristic imuSouthChar(IMU_SOUTH_CHARACTERISTIC_UUID, BLERead | BLENotify,16);
// The temperature (deg C) is one characteristic
BLECharacteristic imuTempChar(IMU_TEMP_CHARACTERISTIC_UUID, BLERead | BLENotify,16);

int Ax, Ay, Az;
int Mx, My, Mz; 

void setup(){
  
  Serial.begin(9600);
  
  // Activate and initialize BLE peripheral
  BLE.begin();
  BLE.setLocalName("IMUB");
  BLE.setAdvertisedService(imuService);
  imuService.addCharacteristic(imuXYZChar);
  imuService.addCharacteristic(imuTempChar);
  imuService.addCharacteristic(imuSouthChar);
  BLE.addService(imuService);
  BLE.advertise(); // start advertising
  
  // Activate the IMU accelerometer and magnetometer sensors
  IMU.begin();
  
  // Activate the temperature sensor
  // HTS.begin(); deactivated. Non Sense for Nano 33 BLE
}

void loop() {
  // Run sensors if the connection to the phone is active
  BLEDevice central = BLE.central();
  if(central){
    updateImuData();
    delay(50);
  }
}

void updateImuData(){
  int x, y, z;
  float temp;
  float mx, my, mz;
  float ax, ay, az; 
  
  // Read IMU sensor temperature deactivated. Non Sense for Nano 33 BLE
  temp = 0 ; //int(10*(HTS.readTemperature()/512 + 23)); simulated temp
  Thermometer(temp);

  // Read QMC5883 magnetometer
  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(mx, my, mz);
  }
  x = int(300*mx);
  y = int(300*my);
  z = int(300*mz);
  Magnetometer(x,y,z);

  // read IMU accelerometer
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }
  x = int(10000*ax);
  y = int(10000*ay);
  z = int(10000*az);
  Accelerometer(x,y,z);
}

// Reorient, filter and format IMU sensor characteristics

// Format IMU temperature characteristic
void Thermometer(int temp){
  String tempString = "";
  char tempBuf[10] = "";

  tempString = "+"+String(temp,HEX)+"-";
  tempString.toCharArray(tempBuf,10);
  imuTempChar.setValue((unsigned char*)tempBuf, 10);
}

// Reorient, filter and format compass South (heading) characteristic
void Magnetometer(int x,int y,int z){
  int xyz[4] = {x,y,z};
  int south = 0;
  String southString = "";
  char southBuf[10] = "";
  int rateConstant = 5;
  int threshold = 300;

  // Adjust magnetometer data for sensor orientation
  reOrient(xyz);

  // Filter reoriented magnetometer data
  Mx=Filter(Mx,xyz[0],threshold,rateConstant);
  My=Filter(My,xyz[1],threshold,rateConstant);
  Mz=Filter(Mz,xyz[2],threshold,rateConstant);

  // Format magnetometer data to transmit one signed four digit Hex number
  south = atan2(Mx,Mz)*180/PI;
  southString = Sign(south) + String(abs(south),HEX) + "-";
  southString.toCharArray(southBuf, 10);
  imuSouthChar.setValue((unsigned char*)southBuf,10);
}

// Reorient, filter and format accelerometer vector characteristic
void Accelerometer(int x, int y, int z){
  int xyz[4] = {x,y,z};
  String xString="", yString="", zString="";
  String xSign="", ySign="", zSign="";
  String xyzString  = "";
  char xyzBuf[21]="";
  int rateConstant = 15;
  int threshold = 30;
    
  // Adjust accelerometer data for sensor orientation
  reOrient(xyz);
  
  // Filter reoriented accelerometer data
  Ax=Filter(Ax,xyz[0],threshold,rateConstant);
  Ay=Filter(Ay,xyz[1],threshold,rateConstant);
  Az=Filter(Az,xyz[2],threshold,rateConstant);

  // Format to transmit three signed four digit Hex numbers
  xString = String(abs(Ax),HEX);
  yString = String(abs(Ay),HEX);
  zString = String(abs(Az),HEX);
  xSign = Sign(Ax);
  ySign = Sign(Ay);
  zSign = Sign(Az);
  xyzString = xSign+xString+ySign+yString+zSign+zString+"-";
  xyzString.toCharArray(xyzBuf, 21);
  imuXYZChar.setValue((unsigned char*)xyzBuf,21);
}

// Filter responds to small changes in value in dynamic environments
// values below a threshold are averaged with a rate constant of 'n'
float Filter(int oldVal,int newVal,int threshold, int rateConstant){
  if(abs(oldVal-newVal)<threshold){
    newVal = ((rateConstant*oldVal)+newVal)/(rateConstant+1);
  }
  return newVal;
}

// Convert value signs to strings
String Sign(int val){
  String valSign;
  if (val<0){
    valSign = "-";
  } else {
    valSign = "+";
  }
  return valSign;
}

// Adjusts xyz vector for IMU sensor orientation on telescope
// The reference xyz axes are as defined by the Hungarian Research Centre 
// for Astronomy and Earth Sciences, see also reference and diagram in notes
void reOrient(int xyz[]){
  int x=xyz[0], y=xyz[1], z=xyz[2];
  xyz[0]=x; // reoriented x = x'
  xyz[1]=y;  // reoriented y = y'
  xyz[2]=z;  // reoriented z = z'
} 
