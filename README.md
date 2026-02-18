# OhioIoT ESP32 SDK (Arduino / PlatformIO)

A lightweight helper library for ESP32 projects that need:

-   Persistent device ID (stored in ESP32 NVS via `Preferences`)
-   Event-driven WiFi connect + reconnect
-   MQTT connect + maintain (PubSubClient)
-   Optional TLS support (CA certificate)

The intended usage is simple:

``` cpp
ohioiot.setup();   // call once in setup()
ohioiot.loop();    // call every pass through loop()
```

------------------------------------------------------------------------

## Project Structure

    config/
      config/
        ca_cert.h
        credentials.h              <-- your secrets (DO NOT COMMIT)
        credentials_template       <-- copy to credentials.h
        user_config.h

    ohioiot/
      _ohioiot/
        ohioiot.h / ohioiot.cpp    <-- main entry object
      mqtt/
        mqtt.h / mqtt.cpp
        mqtt_publish.cpp
        mqtt_subscribe.cpp
        mqtt_handler.cpp
      storage/
        storage.h / storage.cpp
      wifi_tools/
        wifi_tools.h / wifi_tools.cpp
        wifi_tools_debug.cpp

------------------------------------------------------------------------

## Dependencies

-   ESP32 Arduino framework
-   PlatformIO (recommended)
-   PubSubClient (`knolleary/PubSubClient`)
-   ESP32 Preferences (built-in)

------------------------------------------------------------------------

## PlatformIO Setup

Example `platformio.ini`:

``` ini
[platformio]
default_envs = dev

[env]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200

lib_deps =
    knolleary/PubSubClient@^2.8

lib_extra_dirs =
    config
    ohioiot

[env:dev]
build_flags =
    ; -DALLOW_UNSECURED_MQTT
```

> NOTE: If you use `default_envs = dev`, you must have an `[env:dev]`
> section.

------------------------------------------------------------------------

## Credentials Setup

Copy:

    config/config/credentials_template

to:

    config/config/credentials.h

Fill in:

-   `WIFI_SSID`
-   `WIFI_PASS`
-   `MQTT_HOST`
-   `MQTT_PORT`
-   `MQTT_USER`
-   `MQTT_PASS` (if not using unsecured mode)

Add to `.gitignore`:

    config/config/credentials.h

------------------------------------------------------------------------

## TLS Mode

When **not** defining `ALLOW_UNSECURED_MQTT`, the library:

-   Uses `WiFiClientSecure`
-   Calls `setCACert()`
-   Requires `ca_cert.h` to contain your PEM CA certificate

------------------------------------------------------------------------

## Unsecured MQTT Mode

Enable by adding:

``` ini
build_flags = -DALLOW_UNSECURED_MQTT
```

This will:

-   Use `WiFiClient`
-   Connect without username/password
-   Skip CA certificate loading

Preprocessor directives must use lowercase:

``` cpp
#ifdef ALLOW_UNSECURED_MQTT
#else
#endif
```

------------------------------------------------------------------------

## Basic Usage Example

``` cpp
#include <Arduino.h>
#include "ohioiot.h"

void setup() {
    Serial.begin(115200);
    ohioiot.setup();
}

void loop() {
    ohioiot.loop();
    delay(10);
}
```

------------------------------------------------------------------------

## Device ID Behavior

-   Generated once on first boot
-   Stored in NVS (`Preferences` namespace "id")
-   Reused on future boots
-   8-character lowercase alphanumeric string

------------------------------------------------------------------------

## License

Add your license here (MIT, Apache-2.0, etc.).
