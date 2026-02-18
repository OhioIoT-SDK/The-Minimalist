
#pragma once

#include "mqtt.h"

class OhioIoT {

    public:

        OhioIoT();

        void setup(const char *);
        void loop();
        
};

extern OhioIoT ohioiot;
