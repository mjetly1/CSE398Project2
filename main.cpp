#include "COBSdecoder.h"
#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>

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
	arduino.SetBaudRate(LibSerial::BaudRate::BAUD_115200);
  //arduino.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
	ofstream pressureOut;
	ofstream accelerationOut;
	uint8_t c;
	float receiverChecksum;
	receive_packet pkt;
	cobSerial myCOB;

	while (1) {
		//pressureOut.open("pressure.csv", ios_base::app);
		//accelerationOut.open("acceleration.csv", ios_base::app);
		//caughtChecksum = 0;

		if ( arduino.IsDataAvailable() ) {
			arduino.ReadByte(c, 0);
			myCOB.addByte(c);
			cout << int(c) << endl;
		}

		if ( myCOB.packetAvail() ) {
			int len = myCOB.getPacket((char*)&pkt);
			cout << "packet length " << len << endl;
			cout << "Header: " << pkt.header << " , " << pkt.measurement[0] << endl;
			cout << "Value: " << pkt.measurement[23] << " , " << int(pkt.checksum) << endl;
			/*
			int len = myCOB.getPacket((char*)&pkt);
			cout << "packet length " << len << endl;
			cout << "Header: " << pkt.header << " , " << pkt.measurement[0] << endl;
			for(int i = 0 ; i < 40 ; i++){
          caughtChecksum += pkt.measurement[i];
			}
				if (pkt.header == 'b'){
						for(int i = 0 ; i < 40 ; i++){
							accelerationOut << to_string(pkt.measurement[i]) << ", ";
						}
						accelerationOut << to_string(pkt.orient_yaw) << ", ";
						accelerationOut << to_string(pkt.orient_pitch) << ", ";
						accelerationOut << to_string(pkt.orient_roll) << ", ";
						accelerationOut << endl;
					}
					else if (pkt.header == 'p'){
						for(int i = 0 ; i < 40 ; i++){
							pressureOut << pkt.measurement[i] << ", ";
						}
						pressureOut << pkt.orient_yaw << ", ";
						pressureOut << pkt.orient_pitch << ", ";
						pressureOut << pkt.orient_roll << ", ";
						pressureOut << endl;
						*/



		//pressureOut.close();
		//accelerationOut.close();
	}
}
		return 0;
}
