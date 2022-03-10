#include <PacketSerial.h>

// Arduino code to test sending a packet
// the packet fields are defined as a struc

// Global Declarartions
Adafruit_BNO055 bno = Adafruit_BNO055(55);
float aTemp = 0;       //Temporary Acceleration Magnitude Data
float accel[40];       //Array of Accelration Data
float pressure[40];    //Array of Pressure Data
int pressureADC;       //ADC value for Pressure Sensor
float Force;           //Force data
float pressureGrams;   //Force data converted to pressure in grams
float eulerx;          //Euler x-component
float eulery;          //"    "y-component
float eulerz;          //"    "z-component
float checksum;        //Packet Checksum
const float m = -.561; //Slope of pressure sensor
const float b = 5.943; //x-interecept of pressure sensor

int count = 0;

PacketSerial myPacketSerial;

struct send_packet {
  char header;
  float measurement[40];
  float orient_yaw;
  float orient_pitch;
  float orient_roll;
  float checksum;
};

send_packet pkt;

void setup()
{
    Serial1.begin(9600);
    myPacketSerial.setStream(&Serial1);

    //Our code
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

void loop()
{
  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /*Linear Acceleration*/
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  eulerx = euler.x();
  eulery = euler.y();
  eulerz = euler.z();
  imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

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
    accel[i] = accel[i+1];
    pressure[i] = pressure[i+1];
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
      pkt.header = 'b';
      for (int i=0; i<40; i++)
      {
        pkt.measurement[i] = accel[i];
        checksum += accel[i];
      }
      pkt.orient_yaw = eulerx;
      pkt.orient_pitch = eulery;
      pkt.orient_roll = eulerz;
      pkt.checksum = checksum;
      myPacketSerial.send((uint8_t*)&pkt, sizeof(pkt));
    }
    if (pressure[19] > 0.00){
      Serial.print("Push");
      pkt.header = 'p';
      for (int i=0; i<40; i++)
      {
        pkt.measurement[i] = pressure[i] ;
        checksum = pressure[i];
      }
      pkt.orient_yaw = eulerx;
      pkt.orient_pitch = eulery;
      pkt.orient_roll = eulerz;
      pkt.checksum = checksum;
      myPacketSerial.send((uint8_t*)&pkt, sizeof(pkt));
    }
  delay(2000);
  }
}
