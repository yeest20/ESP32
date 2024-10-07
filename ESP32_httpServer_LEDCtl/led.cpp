#include "esp32-hal-gpio.h"
#include<Arduino.h>
#include"led.h"

void led_init(){
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  return;
}

void led_ctrl(int state){
  digitalWrite(LED_PIN, state ? HIGH : LOW);
  return;
}