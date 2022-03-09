#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <PacketSerial.h>


Adafruit_BNO055 bno = Adafruit_BNO055(55);
float aTemp = 0;       //Temporary Acceleration Magnitude Data
float accel[40];       //Array of Accelration Data
float pressure[40];    //Array of Pressure Data
float orientation;          //Orientation Data
int pressureADC;       //ADC value for Pressure Sensor
float Force;           //Force data
float pressureGrams;   //Force data converted to pressure in grams
const float m = -.561; //Slope of pressure sensor
const float b = 5.943; //x-interecept of pressure sensor

int count = 0;

/* COBS packet struct*/
struct send_packet{
  char header;
  float measurement[40];
  float orient;
  uint8_t checksum;
};

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

  /*Linear Acceleration*/
  imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

  /*Euler orientation angle*/
  imu::Vector<3> orientation = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

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
  float amag = pow((pow(accel.x(),2)+pow(accel.y(),2)+pow(accel.z(),2)), 0.5);
  float filterAMag = aTemp * 0.86  + amag * 0.14;

  /*calculating force in grams on pressure sensor*/
  pressureADC = analogRead(A0);
  Force = (100000/(pressureADC/204.8))-20000;
  pressureGrams = (pow(10,b/-m) / pow(Force , 1/-m));

  /*Storing filtered Amag value for calculation in next loop*/
  aTemp = filterAMag;

  /*Addes raw amag and pressureGrams data to an array with 40 data points*/
  for( int i = 0; i<39 ; i++)
  {
    accel[i]=accel[i+1];
    pressure[i]= pressure[i+1];
  }
  accel[39] = amag;
  pressure[39] = pressureGrams;

  if (filterAMag > 2.5 || count > 0 || pressureGrams > 0.00)
  {
    count++;
  }

  if(count == 20)
  {
    if (accel[19] > 2.5){
      Serial.print("Bump");

    }
    if (pressure[19] > 0.00){
      Serial.print("Push");
    }


    for( int i = 0; i<39 ; i++)
    {
      //Serial.print(accel[i]);
      //Serial.print(" ");
      //Serial.print(pressure[i]);
      //Serial.print(" ");
    }
    count = 0;
  }
}
