

#include "mqtt.h"

void Mqtt::publish(const char * topic, const char * payload) {
    _mqtt_client.publish(topic, payload);
}

void Mqtt::subscribe(const char * topic) {
    _mqtt_client.subscribe(topic);
}