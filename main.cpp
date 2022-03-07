#include <libserial/SerialPort.h>
#include<iostream>
#include<ostream>
using namespace LibSerial;

int main()
{

     // Instantiate a Serial Port and a Serial Stream object.
     SerialPort serial_port;

     // Open the hardware serial ports.
     serial_port.Open( "/dev/ttyUSB0" );

     // Set the baud rates.
     serial_port.SetBaudRate( BaudRate::BAUD_115200 );

     char write_byte_1 = 'a';
     char write_byte_2 = 'b';

     char read_byte_1 = 'A';
     char read_byte_2 = 'B';

     // Write a character.
     serial_port.Write(&write_byte_1, 1);

     // Read a character.
     serial_port.Read(read_byte_1, 1);

     std::cout << "serial_port read:   " << read_byte_1 << std::endl;

     // Close the Serial Port and Serial Stream.
     serial_port.Close();
}
