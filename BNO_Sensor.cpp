#include <BNO_Sensor.h>

void::BNO_Sensor initialize()
{
  SerialPort sensor;
  sensor.Open("/dev/ttyS0");
  sensor.SetBaudRate( BaudRate::BAUD_9600 );

}

void::BNO_Sensor Reading()
{
  float amag;
  SerialPort sensor;
  amag = ReadByte(amag,0)
}
