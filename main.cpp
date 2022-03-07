#include <SerialPort.h>

int main(){
new BNO_Sensor sensor;
  sensor.initialize();
  sensor.Reading();
  return 0;
}
