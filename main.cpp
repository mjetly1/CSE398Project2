#include <SerialPort.h>
#include <BNO_Sensor.h>

int main(){
new BNO_Sensor sensor;
  sensor.initialize();
  sensor.Reading();
  return 0;
}
