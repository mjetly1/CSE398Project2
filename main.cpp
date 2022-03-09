#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>
#include <iostream>
#include <ostream>


using namespace std;
using namespace LibSerial;

struct recieve_packet{
    char header;
    float measurement[40];
    float orient_yaw;
    float orient_pitch;
    float orient_roll;
    uint8_t checksum;

};

int main(void)
{
    char c;
    // Instantiate a Serial Port and a Serial Stream object.
    SerialPort serial_port;

    // Open the hardware serial ports.
    serial_port.Open( "/dev/ttyUSB0" );

    // Set the baud rates.
    serial_port.SetBaudRate( BaudRate::BAUD_9600);
    uint8_t c;
    recieve_packet pkt;
    cobSerial myCOB;

    while(1)
    {
        if (serial_port.IsDataAvailable())
        {
            serial.ReadByte(c, 0);

            myCOB.addByte(c);
        }
        if (myCOB.packetAvail())
        {
            int len = myCOB.getPacket((char*)&pkt);
            cout << endl;
            cout << "Packet Length " << len << endl;
            cout << "Header: " << pkt.header << ", " << pkt.measurement[0] << endl;
            cout << "Value: " << pkt.measurement[23] << ", " << int(pkt.checksum) << endl;
        }
    }

    // Close the Serial Port and Serial Stream.
    serial_port.Close();
    return 0;
}
