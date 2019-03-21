# -*- coding: utf-8 -*-  
import paho.mqtt.client as mqtt
import RPi.GPIO as GPIO
import json
 
# BCM GPIO编号
pins = [17,18,27,22,23,24,25,4]
def gpio_setup():
    # 采用BCM编号
    GPIO.setmode(GPIO.BCM)
    # 设置所有GPIO为输出状态，且输出低电平
    for pin in pins:
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, GPIO.LOW)
        
def gpio_destroy():
    for pin in pins:
        GPIO.output(pin, GPIO.LOW)
        GPIO.setup(pin, GPIO.IN)
        
# 连接成功回调函数
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    # 连接完成之后订阅gpio主题
    client.subscribe("gpio")
 
# 消息推送回调函数
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    # 获得负载中的pin 和 value
    gpio = json.loads(str(msg.payload))
 
    if gpio['pin'] in pins:
        if gpio['value'] == 0:
            GPIO.output(gpio['pin'], GPIO.LOW)
        else:
            GPIO.output(gpio['pin'], GPIO.HIGH)
 
if __name__ == '__main__':
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    gpio_setup()
    
    try:
        # 请根据实际情况改变MQTT代理服务器的IP地址
        client.connect("192.168.1.110", 1883, 60)
        client.loop_forever()
    except KeyboardInterrupt:
        client.disconnect()
        gpio_destroy()
