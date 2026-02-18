#include "mqtt.h"


void Mqtt::set_callback(MessageHandler handler) {
    _stored_handler = handler;
    client.setCallback(_callback_wrapper);
}

void Mqtt::_callback_wrapper(char * topic, byte * payload, unsigned int length) {
    char message[length+1];
    memcpy(message, payload, length);
    message[length] = 0;
    mqtt._stored_handler(topic, message);
}