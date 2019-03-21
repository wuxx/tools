sudo apt-get install mosquitto mosquitto-clients
pip install paho-mqtt

mosquitto -h 123.56.12.242 -t "topic_test" -m "test"

mosquitto_sub -v -t "gpio" -h 192.168.1.110
mosquitto_pub -h 123.56.12.242 -t "topic_test" -u mqtt_user -P wujianhua -m "testab"
