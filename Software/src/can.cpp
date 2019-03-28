#include "can.h"
#include "lidar_info.h"

#define CAN0_INT 4                              // Set INT to pin 2
MCP_CAN CAN0(8);                               // Set CS to pin 10

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                       

bool can_init(int baud) {
    if(CAN0.begin(MCP_ANY, baud, MCP_16MHZ) == CAN_OK) {
        //Serial.println("can: MCP2515 Initialized Successfully!");
        CAN0.setMode(MCP_NORMAL);
        return true;
    } else {
        Serial.println("can: Error Initializing MCP2515...");
        return false;
    }
}

void can_loop() {
    if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
    {
        CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    
        if(rxId == CAN_LIDAR_ID) {
            switch(rxBuf[0]) {
                case 'c':   // control
                    if(rxBuf[1] == 's') {
                        // stopping 
                        lidar_set_status(0);
                    } else if(rxBuf[1] == 'S') {
                        // start
                        lidar_set_status(1);
                    }
                    break;
                case 'r':
                    byte data[8];

                    data[0] = (byte)(lidar_get_detected());

                    byte sndStat = CAN0.sendMsgBuf(GLAVNA_CAN_ID, 0, 8, data);
                    if(sndStat == CAN_OK){
                        Serial.println("can: Message Sent Successfully!");
                    } else {
                        Serial.println("can: Error Sending Message...");
                    }
                    break;
            }
        }
    }
}

void can_test() {

    // CAN TX Variables
    unsigned long prevTX = 0;                                        // Variable to store last execution time
    const unsigned int invlTX = 1000;                                // One second interval constant
    byte data[] = {0xAA, 0x55, 0x01, 0x10, 0xFF, 0x12, 0x34, 0x56};  // Generic CAN data to send

    // CAN RX Variables
    long unsigned int rxId;
    unsigned char len;
    unsigned char rxBuf[8];

    // Serial Output String Buffer
    char msgString[128];

    while(1) {
        if(!digitalRead(CAN0_INT))                          // If CAN0_INT pin is low, read receive buffer
        {
            CAN0.readMsgBuf(&rxId, &len, rxBuf);              // Read data: len = data length, buf = data byte(s)
            
            if((rxId & 0x80000000) == 0x80000000)             // Determine if ID is standard (11 bits) or extended (29 bits)
            sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
            else
            sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
        
            Serial.print(msgString);
        
            if((rxId & 0x40000000) == 0x40000000){            // Determine if message is a remote request frame.
            sprintf(msgString, " REMOTE REQUEST FRAME");
            Serial.print(msgString);
            } else {
            for(byte i = 0; i<len; i++){
                sprintf(msgString, " 0x%.2X", rxBuf[i]);
                Serial.print(msgString);
            }
            }
                
            Serial.println();
        }
        
        if(millis() - prevTX >= invlTX){                    // Send this at a one second interval. 
            prevTX = millis();
            byte sndStat = CAN0.sendMsgBuf(0x100, 8, data);
            
            if(sndStat == CAN_OK)
            Serial.println("Message Sent Successfully!");
            else
            Serial.println("Error Sending Message...");

        }
    }

}