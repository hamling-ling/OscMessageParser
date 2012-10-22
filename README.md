OscMessageParser
================

Simple C++ implementation of OSC message parsing functionality.

how to use
<pre><code>
#include <IOscMessageParser.h>

IOscMessageParser *pPsr;
OscMessage msg;

void setup() {
  Serial.begin(9600);
  pPsr = IOscMessageParser::Create();
}

void loop() {
  while(Serial.available()) {
    // read 1 letter from serial port
    char c = Serial.read();
    // push every received character
    // when the message is complete, it returns true
    if(pPsr->Push(c)) {
      // read message into msg
      pPsr->Read(&msg);
    }
  }
}
</code></pre>

refs
http://opensoundcontrol.org/spec-1_0-examples#OSCaddress
