#pragma once

#ifdef ALLOW_UNSECURED_MQTT
    #include <WiFiClient.h>
#else
    #include <WiFiClientSecure.h>
#endif
#include <PubSubClient.h>


#define RETRY_INTERVAL 3000

using MessageHandler = void (*)(const char *, const char *);

class Mqtt {

    public:

        Mqtt();



        // connect
        void setup(const char *, int, const char *, const char *, const char *, const char *);
        void setup(const char *, int, const char *);
        void maintain();


        bool is_connected = false;

        // publish
        void publish(const char *, const char *);

        // subscribe
        void subscribe(const char *);
        void (*set_subscriptions)() = nullptr; 

        // handle
        void set_callback(MessageHandler);

    private:

        #ifdef ALLOW_UNSECURED_MQTT
            WiFiClient _wifi_client;
        #else
            WiFiClientSecure _wifi_client;
        #endif
        
        PubSubClient _mqtt_client;

        // connect
        char _mqtt_username[32];    // not used if using an unsecured connection
		char _mqtt_password[32];    // not used if using an unsecured connection

        void report_disconnect();
        friend class OhioIoT;

        unsigned long _retry_timer;
        bool _is_first_connect = true;
        char _device_id[32];

        // publish

        // subscribe

        // handle
        MessageHandler _stored_handler;
        static void _callback_wrapper(char *, byte *, unsigned int);

};

extern Mqtt mqtt;
