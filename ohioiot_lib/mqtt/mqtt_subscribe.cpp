#include "mqtt.h"


void Mqtt::set_subscriptions(const char ** topics, int count) {
    _subscription_list = topics;
    _sub_list_length = count;
}

void Mqtt::_subscribe_to_all() {
    if (_subscription_list) {
        for (int i=0; i<_sub_list_length; i++) {
            Serial.print("\t.. subscribing to: ");
            Serial.println(_subscription_list[i]);
            client.subscribe(_subscription_list[i]);
        }
    }
}

