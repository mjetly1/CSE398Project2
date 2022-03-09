#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>
#include <iostream>
#include <ostream>



using namespace LibSerial;
int main(void)
{
    char c;
     // Instantiate a Serial Port and a Serial Stream object.
     SerialPort serial_port;

     // Open the hardware serial ports.
     serial_port.Open( "/dev/ttyUSB0" );

     // Set the baud rates.
     serial_port.SetBaudRate( BaudRate::BAUD_115200 );

     char read_byte_1 = 'A';
     char read_byte_2 = 'B';

     // Read a character.
     serial_port.ReadByte(c, 1);

     std::cout << "serial_port read:   " << read_byte_1 << std::endl;

     // Close the Serial Port and Serial Stream.
     serial_port.Close();
     return 0;
}
