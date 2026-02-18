

#include "ohioiot.h"

#include "wifi_tools.h"

#include "ca_cert.h"
#include "credentials.h"


OhioIoT::OhioIoT() {}

OhioIoT ohioiot;


void OhioIoT::setup(const char * device_id) {

	wifi_tools.begin(WIFI_SSID, WIFI_PASS);

	#ifdef ALLOW_UNSECURED_MQTT
		mqtt.setup(MQTT_HOST, MQTT_PORT, device_id);
	#else
		mqtt.setup(MQTT_HOST, MQTT_PORT, MQTT_USER, MQTT_PASS, device_id, CA_CERTIFICATE);
	#endif
}


void OhioIoT::loop() {
	if (wifi_tools.is_connected) {
		mqtt.maintain();
	} else {
		wifi_tools.reconnect();
		mqtt.report_disconnect();
	}
}
