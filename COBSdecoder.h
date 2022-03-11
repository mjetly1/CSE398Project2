#include <iostream>

class cobSerial {
	public:
		cobSerial();
		~cobSerial();
		void addByte(uint8_t c);
		bool packetAvail();
		int getPacket(char* ptrOutput);
		static const int constMaxPacketSize = 512;
	private:
		void decode();
		bool bAvail;
		char buff[constMaxPacketSize];
		int buffIdx;
		char decodedBuff[constMaxPacketSize];
        int decodeIdx;
};
