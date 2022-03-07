#include <SerialPort.h>
#include <SerialStream.h>

int main(){
BNO_Sensor sensor;
  sensor.initialize();
  sensor.Reading();
  return 0;
}
