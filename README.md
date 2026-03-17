# UOBC
universal on-board computer for every vehicle with wheels(UOBC)


# main features
1. WebUI on esp8266
2. Hall sensor for calculating speed
3. PWM Led controller on MOSFET
4. OLED display


# main controller
Brain of UOBC is stm32f103c8(blue pill), for web esp8266 is used. Their connection is is carried out by UART

# drivers
all drivers is self-writed, there is no libraryes(only CMSIS headers)

