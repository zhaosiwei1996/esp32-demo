## esp32开发板demo

开发环境:vscode+platformio

已实现功能:

显示屏

温湿度检测

Wifi

时钟同步

mqtt数据上行温湿度

mqtt数据下行控制主板led灯开关

通信协议:

wifi+mqtt

## 上行数据格式
{"unix_time":1725611636,"source_ip_address":"192.168.0.100","client_mac_address":"A0:A3:B3:A9:E9:CC","temperature":26,"humidity":53}
unix_time：时间戳

source_ip_address：数据发送方的ip地址

client_mac_address：监控设备的mac地址

temperature: 温度

humidity: 湿度



## 下行数据格式
{"unix_time":1725611503,"source_ip_address":"192.168.0.107","client_mac_address":"A0:A3:B3:A9:E9:CC","device":"led","action":"on"}

unix_time：时间戳

source_ip_address：数据发送方的ip地址

client_mac_address：被控设备的mac地址

device：被控设备的设备类型

action：被控设备执行动作