#pragma once

#ifdef ALLOW_UNSECURED_MQTT
    #include <WiFiClient.h>
#else
    #include <WiFiClientSecure.h>
#endif
#include <PubSubClient.h>


#define RETRY_INTERVAL 3000

using MessageHandler = void (*)(char *, char *);

class Mqtt {

    public:

        Mqtt();

        PubSubClient client;

        // connect
        void setup(const char *, int, const char *, const char *, const char *, const char *);
        void setup(const char *, int, const char *);
        void maintain();

        void report_disconnect();
        bool is_connected = false;

        // publish
        void publish(const char *, const char *);
        void publish(const char *, float);
        void publish(const char *, int);
        void publish(const char *);

        // subscribe
        void set_subscriptions(const char **, int);

        // handle
        void set_callback(MessageHandler);

    private:

        #ifdef ALLOW_UNSECURED_MQTT
            WiFiClient _wifi_client;
        #else
            WiFiClientSecure _wifi_client;
        #endif
        


        // connect
        char _mqtt_username[32];    // not used if using an unsecured connection
		char _mqtt_password[32];    // not used if using an unsecured connection

        unsigned long _retry_timer;
        bool _is_first_connect = true;
        char _device_id[9];

        // publish
        void _publish(const char *, const char *);

        // subscribe
        const char ** _subscription_list = nullptr;
        int _sub_list_length = 0;
        void _subscribe_to_all();

        // handle
        MessageHandler _stored_handler;
        static void _callback_wrapper(char *, byte *, unsigned int);

};

extern Mqtt mqtt;
