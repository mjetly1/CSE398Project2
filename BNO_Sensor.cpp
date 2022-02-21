#include <BNO_Sensor.h>

void::BNO_Sensor initialize()
{
  SerialPort sensor;
  sensor.Open("/dev/ttyS0");
  sensor.SetBaudRate( BaudRate::BAUD_9600 );
}
