#include <SerialPort.h>

int main(){
BNO_Sensor sensor;
  sensor.initialize();
  sensor.Reading();
  return 0;
}
