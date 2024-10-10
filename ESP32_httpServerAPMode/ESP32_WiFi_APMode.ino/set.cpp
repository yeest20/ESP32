#include<Arduino.h>
#include "esp32-hal-gpio.h"
#include"set.h"

void led_init(){
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  return;
}

void led_ctrl(int state){
  digitalWrite(LED_PIN, state ? HIGH : LOW);
  return;
}