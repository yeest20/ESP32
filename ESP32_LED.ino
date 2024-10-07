#define LED_PIN 2
#define LED_ON HIGH
#define LED_OFF LOW
void led_ctl(int t){
  digitalWrite(LED_PIN, LED_ON);
  delay(t);
  digitalWrite(LED_PIN, LED_OFF);
  delay(t);
}
// put your setup code here, to run once:
void setup() {
  //LED setup
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_OFF);
}

// put your main code here, to run repeatedly:
void loop() {
  #define LED_DELAY 500
  led_ctl(1000);
  delay(2000);
  led_ctl(500);
  delay(2000);
  led_ctl(200);
  delay(2000);
  #undef LED_DELAY
}
