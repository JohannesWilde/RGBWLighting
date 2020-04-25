ARDUINO_DIR  = /usr/share/arduino

BOARD_TAG = mega
BOARD_SUB = atmega2560

TARGET       = main
ARDUINO_LIBS = Adafruit_NeoPixel
USER_LIB_PATH := ../libraries

CPPFLAGS += -std=gnu++1y

MCU          = atmega2560
F_CPU        = 16000000
 
# Avrdude code
ARDUINO_PORT = /dev/ttyUSB0
AVRDUDE_ARD_PROGRAMMER = wiring
AVRDUDE_ARD_BAUDRATE = 115200

include /usr/share/arduino/Arduino.mk
