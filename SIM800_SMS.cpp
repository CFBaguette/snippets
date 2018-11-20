// Send SMS using SIM800 GSM module, using ATParser library.

#include "ATParser.h"

void sendSMS() {
    PinName debug_tx = ...
    PinName debug_rx = ...
    int debug_baud_rate = ...
    
    Serial dlog = Serial(debug_tx, debug_rx);
    dlog.baud(debug_baud_rate);

    PinName modem_tx = ...
    PinName modem_rx = ...
    int baud_rate = ...
    BufferedSerial sim800 = BufferedSerial(modem_tx, modem_rx);
    sim800.baud(baud_rate);
    
    ATParser parser = ATParser(sim800);
    parser.debugOn(1);

    char *ok_status = "OK";
  
    dlog.printf("Send SMS\r\n");
    if (parser.send("AT") && parser.recv(ok_status)) {
        dlog.printf("AT OK\r\n");
    }

    if (parser.send("AT+CMGF=1") && parser.recv(ok_status)) {
        dlog.printf("TEXT MODE OK\r\n");
    }
    
    if (parser.send("AT+CMGS=\"+############\"")) {
        dlog.printf("PREPARE OK\r\n");
    }
        
    if (parser.send("hello\r\n%c", 26) && parser.recv(ok_status)) {
        dlog.printf("SEND OK\r\n");
    }
    
    dlog.printf("Maybe sent\r\n");
}
