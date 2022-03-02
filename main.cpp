#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>

SerialPort  serial_port;

serial_port.SetBaudRate( BaudRate::BAUD__9600);

char c;
int timeout = 0;
ReadByte(c, timeout);
