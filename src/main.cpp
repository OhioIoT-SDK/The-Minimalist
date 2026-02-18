

#include "Arduino.h"

#include "ohioiot.h"

#define DEVICE_ID "some_client_id"


void my_subscriptions() {
	mqtt.subscribe("larry/hello");
	mqtt.subscribe("larry/goodbye");
}

void on_message(const char * topic, const char * payload) {
	Serial.print("\tmessage received - \ttopic: ");
	Serial.print(topic);
	Serial.print("  \t/ payload: ");
	Serial.print(payload);
}


void setup() {

    Serial.begin(115200);
    Serial.println("\n\n\tawake..\n");

	ohioiot.setup(DEVICE_ID);
	

	mqtt.set_subscriptions = my_subscriptions;
	mqtt.set_callback(on_message);
}


void loop() {

	ohioiot.loop();

	mqtt.publish("larry/hello", "goodbye");
	delay(1000);

}

