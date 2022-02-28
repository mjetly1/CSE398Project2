#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

  
Adafruit_BNO055 bno = Adafruit_BNO055(55);
int aTemp = 0;
float q[40];
int count = 0;

void setup(void) 
{  
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);

  /*Euler orientation angle*/
  imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  
  /* Display the floating point data
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");
  */
  
  /*Display the acceleration points*/
  /*Serial.print("X: ");
  Serial.print(accel.x());
  Serial.print(" Y: ");
  Serial.print(accel.y());
  Serial.print(" Z: ");
  Serial.print(accel.z());   */
  
  
  /* calculating magnitude of acceleration*/
  int amag = pow((pow(accel.x(),2)+pow(accel.y(),2)+pow(accel.z(),2)), 0.5);
  int filterAMag = aTemp * 0.86  + amag * 0.14;
  
  /*Serial.print("Accel Mag: ");
  Serial.print(amag);*/

  aTemp = filterAMag;

  /*Serial.print("  Filter: ");
  Serial.print(filterAMag);
  Serial.println("");*/

  for( int i = 0; i<39 ; i++)
  {
    q[i]=q[i+1];
    //Serial.print(q[i]);
  }
  q[39] = amag;

  if (amag > 2.5 || count > 0) 
  {
    count++;
  }
  if(count == 20)
  {
    for( int i = 0; i<39 ; i++)
    {
      Serial.print(q[i]);
    }
    count = 0;
  }
}
