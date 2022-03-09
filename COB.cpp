#include "COB.h"
#include <cstring>

using namespace std;

cobSerial::cobSerial() {
	buffIdx = 0;
	decodeIdx = 0;
	bAvail = false;
}

cobSerial::~cobSerial() {
}

void cobSerial::addByte(uint8_t c) {
	if ( c == 0 ) {
		decode();
		bAvail = true;
		buffIdx = 0;
	} else {
		buff[buffIdx] = c;
		buffIdx++;
	}
}

bool cobSerial::packetAvail() {
	return bAvail;
}
int cobSerial::getPacket(char* ptrOutput) {
	if (bAvail) {
		memcpy(ptrOutput, decodedBuff, decodeIdx);
		bAvail = false;
		return decodeIdx;
	} else {
		return -1;
	}
}

void cobSerial::decode() {
	int i = 0;
	int l = 0;
	decodeIdx = 0;
	while ( i < buffIdx) {
		l = i + buff[i];
		i++;
		while ( i < l ) {
			decodedBuff[decodeIdx] = buff[i];
			i++;
			decodeIdx++;
		}
		if ( l < buffIdx) {
			decodedBuff[decodeIdx] = 0;
			decodeIdx++;
		}
	}
}