#include <libserial/SerialPort.h>
#include<iostream>
#include<ostream>

int main()
{
    char c;
     // Instantiate a Serial Port and a Serial Stream object.
     LibSerial::SerialPort serial_port;

     // Open the hardware serial ports.
     serial_port.Open( "/dev/ttyUSB0" );

     // Set the baud rates.
     serial_port.SetBaudRate( LibSerial::BaudRate::BAUD_115200 );

     char read_byte_1 = 'A';
     char read_byte_2 = 'B';

     // Read a character.
     serial_port.ReadByte(c, 1);

     std::cout << "serial_port read:   " << read_byte_1 << std::endl;

     // Close the Serial Port and Serial Stream.
     serial_port.Close();
}
