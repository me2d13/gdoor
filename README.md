# gdoor
Arduino c code - client of tcpardu

# accepted MQTT messages
- /garage/ard1/command/led on
- /garage/ard1/command/led off
- /garage/ard1/command/led set:254
- /garage/ard1/command/audio beep
- /garage/ard1/command/audio doublebeep
- /garage/ard1/command/door push
- /garage/ard1/command/door get
- /garage/ard1/command/acpower get
- /garage/ard1/command/temperature get


# produced MQTT messages
- /garage/ard1/status/led 0-255
- /garage/ard1/status/door 0-3
- /garage/ard1/status/acpower 0-1
- /garage/ard1/status/temperature 12.3
- /garage/ard1/status/humidity 12.3
