#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>

int main(){
BNO_Sensor sensor;
  sensor.initialize();
  sensor.Reading();
  return 0;
}
