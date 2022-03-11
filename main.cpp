#include "COBSdecoder.h"
#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>

using namespace std;
using namespace LibSerial;

struct receive_packet {
	char header;
	float measurement[40];
	float orient_yaw;
	float orient_pitch;
	float orient_roll;
	uint8_t checksum;
};

int main(void) {
	SerialPort arduino;
	arduino.Open("/dev/ttyS0");
	arduino.SetBaudRate(BaudRate::BAUD_115200);
  //arduino.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
	ofstream pressureOut;
	ofstream accelerationOut;
	uint8_t c;
	float receiverChecksum;
	receive_packet pkt;
	cobSerial myCOB;

	while (1) {
		pressureOut.open("pressure.csv", ios_base::app);
		accelerationOut.open("acceleration.csv", ios_base::app);
		receiverChecksum = 0;
	   accelerationOut << "4" << ", ";
						accelerationOut << "4" << ", ";
						accelerationOut << "4" << ", ";
						accelerationOut << endl;

		pressureOut.close();
		accelerationOut.close();
	}
 }
}
		return 0;
}
