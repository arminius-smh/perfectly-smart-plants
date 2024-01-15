#ifndef CONFIG_H
#define CONFIG_H

struct ConfigData {
    const int LED_PIN;
    const int MOISTURE_PIN;
    const int SCL_PIN;
    const int SDA_PIN;
    const char *wifi_ssid;
    const char *wifi_password;
    const char *mqtt_client_id;
    const char *mqtt_server;
    const char *mqtt_topic_moisture;
    const char *mqtt_topic_illuminance;
    const char *mqtt_topic_temperature;
    const char *mqtt_topic_humidity;
    const char *mqtt_user;
    const char *mqtt_password;
    const int mqtt_port;
    const int dry;
    const int wet;
    const char *test_mqtt_topic_set;
    const char *test_mqtt_topic_get;
};

extern ConfigData config;

#endif
