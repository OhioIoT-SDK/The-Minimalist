#include "mqtt.h"

#define MAX_PAYLOAD_LENGTH 256

void Mqtt::set_callback(MessageHandler handler) {
    _stored_handler = handler;
    _mqtt_client.setCallback(_callback_wrapper);
}

void Mqtt::_callback_wrapper(char * topic, byte * payload, unsigned int length) {
    char message[MAX_PAYLOAD_LENGTH];
    memcpy(message, payload, length);
    message[length] = 0;
    mqtt._stored_handler(topic, message); 
}