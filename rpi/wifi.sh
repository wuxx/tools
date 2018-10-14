#!/bin/bash

sudo iwlist wlan0 scan | grep ESSID

if [ ${#WIFI_SSID} -eq 0 ]; then
    WIFI_SSID="USR-123456"
fi

if [ ${#WIFI_PASSWD} -eq 0 ]; then
    WIFI_PASSWD="123456"
fi

echo "ssid: ${WIFI_SSID}; passwd: ${WIFI_PASSWD}"

sleep 100

sudo cat << EOF > /etc/wpa_supplicant/wpa_supplicant.conf
country=GB
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1

network={
  ssid="${WIFI_SSID}"
  psk="${WIFI_PASSWD}"
}

EOF

ifup wlan0

