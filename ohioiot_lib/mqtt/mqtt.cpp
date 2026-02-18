#include "mqtt.h"



Mqtt::Mqtt() {}

Mqtt mqtt;


void Mqtt::setup(const char * mqtt_host, int mqtt_port, const char * mqtt_username, const char * mqtt_password, const char * device_id, const char* ca_cert) {
    client.setClient(_wifi_client);
    client.setServer(mqtt_host, mqtt_port);

 	strcpy(_mqtt_username, mqtt_username);
	strcpy(_mqtt_password, mqtt_password);
    strcpy(_device_id, device_id);

    _wifi_client.setCACert(ca_cert);
}



void Mqtt::setup(const char * mqtt_host, int mqtt_port, const char * device_id) {
    client.setClient(_wifi_client);
    client.setServer(mqtt_host, mqtt_port);

    strcpy(_device_id, device_id);
}



void Mqtt::maintain() {

    if (!client.connected() || !is_connected) {
        bool should_reconnect = _is_first_connect || millis() - _retry_timer > RETRY_INTERVAL;
        if (should_reconnect) {
            Serial.println("\tmqtt connecting...");

            bool connected = false;

            #ifdef ALLOW_UNSECURED_MQTT
                connected = client.connect(_device_id);
            #else
                connected = client.connect(_device_id, _mqtt_username, _mqtt_password);
            #endif

            if (connected) {

                Serial.println("\tmqtt connected...");
                is_connected = true;

                _subscribe_to_all();

            } else {
                Serial.println("\txx failed to connect to mqtt");
                is_connected = false;
            }
            _retry_timer = millis();
            _is_first_connect = false;
        }
    } else {
        client.loop();       
    }
  
}



void Mqtt::report_disconnect() {
    is_connected = false;
}
