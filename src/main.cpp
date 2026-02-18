

#include "Arduino.h"

#include "ohioiot.h"


void setup() {

    Serial.begin(115200);
    Serial.println("\n\n\tawake..\n");

	ohioiot.setup();
	
	// YOUR CODE HERE
	
}


void loop() {

	ohioiot.loop();

	// YOUR CODE HERE
	
}

