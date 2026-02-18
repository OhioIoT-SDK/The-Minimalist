
#pragma once


// #include "beacon.h"
// #include "cred_utils.h"
// #include "counters.h"
// #include "monitor.h"
// #include "messages.h"
// #include "system_info.h"
#include "mqtt.h"
// #include "mqtt_tools.h"
// #include "ota.h"
// #include "sleep.h"
// #include "standard_config.h"
// #include "standard_controller.h"
// #include "feedback_pins.h"
// #include "storage.h"
// #include "utils.h"
// #include "provisioning.h"
#include "wifi_tools.h"


class OhioIoT {

    public:

        OhioIoT();

        void setup();
        void loop();
        
};

extern OhioIoT ohioiot;
