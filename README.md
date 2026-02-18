# OhioIoT ESP32 SDK (Arduino / PlatformIO)

A lightweight helper library for ESP32 projects that need WiFi and MQTT up and running fast.

The intended usage is simple:

```cpp
ohioiot.setup(DEVICE_ID);   // call once in setup()
ohioiot.loop();              // call every pass through loop()
```

That's it. WiFi connect, reconnect, MQTT connect, reconnect, and TLS are all handled for you.

---

## Project Structure

```
config/
  config/
    ca_cert.h
    credentials.h              <-- your secrets (DO NOT COMMIT)
    credentials_template       <-- copy this to credentials.h
    user_config.h

ohioiot_lib/
  _ohioiot/
    ohioiot.h / ohioiot.cpp    <-- main entry point
  mqtt/
    mqtt.h / mqtt.cpp
    mqtt_pub_sub.cpp
    mqtt_handler.cpp
  wifi_tools/
    wifi_tools.h / wifi_tools.cpp
```

---

## Dependencies

- ESP32 Arduino framework
- PlatformIO (recommended)
- PubSubClient (`knolleary/PubSubClient`)

---

## PlatformIO Setup

```ini
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
    ohioiot_lib

[env:dev]
build_flags =
    ; -DALLOW_UNSECURED_MQTT
```

---

## Credentials Setup

Copy:

```
config/config/credentials_template
```

to:

```
config/config/credentials.h
```

Fill in:

- `WIFI_SSID`
- `WIFI_PASS`
- `MQTT_HOST`
- `MQTT_PORT`
- `MQTT_USER`
- `MQTT_PASS`

Add to `.gitignore`:

```
config/config/credentials.h
```

---

## Full Usage Example

```cpp
#include "Arduino.h"
#include "ohioiot.h"

#define DEVICE_ID "my_device"


// called automatically every time MQTT connects (or reconnects)
void my_subscriptions() {
    mqtt.subscribe("mydevice/command");
    mqtt.subscribe("mydevice/config");
}

// called automatically when a message arrives on any subscribed topic
void on_message(const char * topic, const char * payload) {
    Serial.print("topic: ");
    Serial.print(topic);
    Serial.print("  payload: ");
    Serial.println(payload);
}


void setup() {
    Serial.begin(115200);

    ohioiot.setup(DEVICE_ID);

    mqtt.set_subscriptions = my_subscriptions;
    mqtt.set_callback(on_message);
}


void loop() {
    ohioiot.loop();

    // publish a message
    mqtt.publish("mydevice/status", "online");
    delay(5000);
}
```

---

## MQTT API

| Call | Description |
|---|---|
| `mqtt.set_subscriptions = my_fn` | Point to a function that calls `mqtt.subscribe()` for each topic. Called on every connect/reconnect. |
| `mqtt.set_callback(on_message)` | Set the handler for incoming messages. Signature: `void fn(const char* topic, const char* payload)` |
| `mqtt.subscribe("topic")` | Subscribe to a topic. Call this inside your `set_subscriptions` function. |
| `mqtt.publish("topic", "payload")` | Publish a message. |
| `mqtt.is_connected` | `bool` — true if MQTT is currently connected. |

---

## TLS Mode (default)

When `ALLOW_UNSECURED_MQTT` is **not** defined, the library uses `WiFiClientSecure` and validates the broker against the CA certificate in `ca_cert.h`. Replace the certificate in that file with your broker's CA if needed.

---

## Unsecured MQTT Mode

Enable by uncommenting in `platformio.ini`:

```ini
build_flags =
    -DALLOW_UNSECURED_MQTT
```

This uses plain `WiFiClient` and connects without TLS or credentials.

---

## Device ID

`DEVICE_ID` is a string you define and pass to `ohioiot.setup()`. It is used as the MQTT client ID, which must be unique per device on your broker. Typically you'd store a unique ID in NVS and load it at boot, or derive it from the ESP32's MAC address.

---

## License

MIT License — Copyright (c) 2026 Ohioiot, LLC

Permission is hereby granted, free of charge, to any person obtaining a copy of this software to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies, subject to the copyright notice and this permission notice appearing in all copies.
