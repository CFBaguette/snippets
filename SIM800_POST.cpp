void sendData() {
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
    
    dlog.printf("Send data\r\n");
    
    ATParser parser = ATParser(sim800);
    parser.debugOn(1);

    char *cmd = "AT";
    char *ok_status = "OK";
    
    if (parser.send(cmd) && parser.recv(ok_status)) {
        dlog.printf("AT OK\r\n");
    }
    
    // For Kyivstar, use "www.ab.kyivstar.net"
    cmd = "AT+SAPBR=3,1,\"APN\",\"YOUR_APN\"";
    if (parser.send(cmd) && parser.recv(ok_status)) {
        dlog.printf("set ap\r\n");
    }


    cmd = "AT+SAPBR=1,1";
    if (parser.send(cmd) && parser.recv(ok_status)) {
        dlog.printf("some select\r\n");
    }
        
    cmd = "AT+HTTPINIT";
    if (parser.send(cmd) && parser.recv(ok_status)) {
        dlog.printf("http init\r\n");
    }

    cmd = "AT+HTTPPARA=\"CID\",1";
    if (parser.send(cmd) && parser.recv(ok_status)) {
        dlog.printf("set param\r\n");
    }
    
    // For example "api.thingspeak.com/update?api_key=API_KEY&field1=30"
    cmd = "AT+HTTPPARA=\"URL\",\"YOUR_URL\"";
    if (parser.send(cmd) && parser.recv(ok_status)) {
        dlog.printf("set url\r\n");
    }

    cmd = "AT+HTTPPARA=\"REDIR\",1";
    if (parser.send(cmd) && parser.recv(ok_status)) {
        dlog.printf("allow redir\r\n");
    }

    cmd = "AT+HTTPSSL=1";
    if (parser.send(cmd) && parser.recv(ok_status)) {
        dlog.printf("enable ssl\r\n");
    }

    cmd = "AT+HTTPACTION=0";
    if (parser.send(cmd) && parser.recv(ok_status)) {
        dlog.printf("post method\r\n");
    }

    cmd = "AT+HTTPREAD";
    if (parser.send(cmd) && parser.recv(ok_status)) {
        dlog.printf("read response\r\n");
    }

    cmd = "AT+HTTPTERM";
    if (parser.send(cmd) && parser.recv(ok_status)) {
        dlog.printf("terminate\r\n");
    }
}
