#include "COB.h"
#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>
#include <iostream>

using namespace std;

struct receive_packet {
	char header;
	float measurement[40];
	float orient_yaw;
	float orient_pitch;
	float orient_roll;
	uint8_t checksum;
};
	
int main(void) { 
	LibSerial::SerialPort arduino;
	arduino.Open("/dev/ttyS0");
	arduino.SetBaudRate(LibSerial::BaudRate::BAUD_9600);
	uint8_t c;
	receive_packet pkt;
	cobSerial myCOB;
	while (1) {
		if (arduino.IsDataAvailable()) { 
			arduino.ReadByte(c, 0);
			myCOB.addByte(c);
		}
		if ( myCOB.packetAvail() ) {
			int len = myCOB.getPacket((char*)&pkt);
			cout << "packet length " << len << endl;
			cout << "Header: " << pkt.header << " , " << pkt.measurement[0] << endl;
			cout << "Value: " << pkt.measurement[23] << " , " << int(pkt.checksum) << endl;
		}
	}
	return 0;
}