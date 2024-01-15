#include "config.h"

ConfigData config = {
    // pins
    .LED_PIN = -1,
    .MOISTURE_PIN = -1,
    .SCL_PIN = -1,
    .SDA_PIN = -1,
    // wifi
    .wifi_ssid = "wifi_ssid",
    .wifi_password = "wifi_password",
    // mqtt
    .mqtt_client_id = "mqtt_client_id",
    .mqtt_server = "mqtt_server",
    .mqtt_topic_moisture = "mqtt_topic_moisture",
    .mqtt_topic_illuminance = "mqtt_topic_illuminance",
    .mqtt_topic_temperature = "mqtt_topic_temperature",
    .mqtt_topic_humidity = "mqtt_topic_humidity",
    .mqtt_user = "mqtt_user",
    .mqtt_password = "mqtt_password",
    .mqtt_port = 1883,
    // calibrated moisture values
    .dry = -1,
    .wet = -1,
    // only for mqtt test
    .test_mqtt_topic_set = "test_mqtt_topic_set",
    .test_mqtt_topic_get = "test_mqtt_topic_get",
};
