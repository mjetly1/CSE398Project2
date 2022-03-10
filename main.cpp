#include "COBSdecoder.h"
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
	float checksum;
};

int main(void) {
	LibSerial::SerialPort arduino;

	ofstream pressureOut;
	ofstream accelerationOut;

	arduino.Open("/dev/ttyS0");
	arduino.SetBaudRate(LibSerial::BaudRate::BAUD_9600);
  arduino.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
	uint8_t c;
	float caughtChecksum;
	receive_packet pkt;
	cobSerial myCOB;

	while (1) {
		if (arduino.IsDataAvailable()) {
			arduino.ReadByte(c, 0);
			myCOB.addByte(c);
		}
		if ( myCOB.packetAvail() ) {
			int len = myCOB.getPacket((char*)&pkt);
			cout << endl;
			cout << "packet length " << len << endl;
			cout << "Header: " << pkt.header << " , " << pkt.measurement[0] << endl;
			for(int i = 0 ; i < 40 ; i++){

			}
			cout << "Value: " << pkt.measurement[23] << " , " << int(pkt.checksum) << endl;
		}
	}
	return 0;
}
