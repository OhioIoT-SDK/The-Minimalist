
#include "wifi_tools.h"

WiFi_Tools::WiFi_Tools() {}

WiFi_Tools wifi_tools;



void WiFi_Tools::begin(const char * ssid, const char * pass) {
	WiFi.setAutoReconnect(false);
	WiFi.persistent(false);
	WiFi.onEvent(_event_handler);
	Serial.println("\n\twifi connecting...");
	WiFi.begin(ssid, pass);
}



void WiFi_Tools::reconnect() {
	
	if ((millis() - _reconnect_timer > RECONNECT_INTERVAL) && _should_reconnect) {
		Serial.println("\twifi reconnecting...\n");
		WiFi.reconnect();
		_reconnect_timer = millis();
	}
}



void WiFi_Tools::_event_handler(WiFiEvent_t event, WiFiEventInfo_t info) {

	if (event == ARDUINO_EVENT_WIFI_STA_DISCONNECTED) {
		if (wifi_tools.is_connected) Serial.println("\n\twifi disconnected...\n");
		wifi_tools.is_connected = false;
		bool user_disconnected = info.wifi_sta_disconnected.reason == WIFI_REASON_ASSOC_LEAVE;
		wifi_tools._should_reconnect = !(user_disconnected || wifi_tools._first_disconnect);
		wifi_tools._first_disconnect = false;
	}

	if (event == ARDUINO_EVENT_WIFI_STA_GOT_IP) {
		if (!wifi_tools.is_connected) Serial.println("\twifi connected...\n");
		wifi_tools.is_connected = true;
	}

}
