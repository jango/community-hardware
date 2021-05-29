#include "Led.h"

Led::Led(byte pin) {
  this->pin = pin;
  this->defaultRed = 0;
  this->defaultGreen = 0;
  this->defaultBlue = 0;
  this->defaultBrightness = 100;
  this->pixels = Adafruit_NeoPixel(1, pin, NEO_RGB + NEO_KHZ800);
}

void Led::blink(int red, int green, int blue, int brightness, int delayms, int times){
  off();

  for (int i = 0; i < times; i++){
    on(red, green, blue, brightness);
    delay(delayms);
    off();  
  }
}

void Led::init() {
  this->pixels.begin();
  this->pixels.show();
}

void Led::updateDefaults(int defaultRed, int defaultGreen, int defaultBlue, int defaultBrightness){
  this->defaultRed = defaultRed;
  this->defaultGreen = defaultGreen;
  this->defaultBlue = defaultBlue;
  this->defaultBrightness = defaultBrightness;
}

void Led::illuminateSensor(){
  // Turn on Lux LED to illuminate sensor:
  // pixels.setPixelColor(0, pixels.Color(255, 75, 0));

  for (int x = 0; x <= 128; x++) {
    pixels.setPixelColor(0, pixels.Color(255, 75, 0));
    pixels.setBrightness(x);
    pixels.show();
    delay(5);
  }

  for (int x = 32; x <= 64; x += 4) {
    pixels.clear();
    pixels.show();
    delay(pow(1.1, x));

    pixels.setPixelColor(0, pixels.Color(255, 75, 0));
    pixels.show();
    delay(pow(1.1, x));
  }
}

void Led::displayLedMessage(LED_MSG_TYPE msgType) {
  this->pixels.setBrightness(this->defaultBrightness);

  switch(msgType){
    case LED_MSG_TYPE::INFO_OK:
      blink(0, 255, 0, 100, LED_BLINK_DELAY, 1);
    break;
    case LED_MSG_TYPE::ERROR_UPLOAD:
      blink(255, 0, 0, 100, LED_BLINK_DELAY, 1);
    break;
    case LED_MSG_TYPE::ERROR_NETWORK:
      blink(255, 0, 0, 100, LED_BLINK_DELAY, 2);
    break;
    case LED_MSG_TYPE::ERROR_FS:
      blink(255, 0, 0, 100, LED_BLINK_DELAY, 3);
    break;
    case LED_MSG_TYPE::INFO_PING_OK:
      blink(0, 0, 255, 100, LED_BLINK_DELAY, 2);
    break;
    case LED_MSG_TYPE::INFO_BTN_PRESSED:
      blink(0, 0, 255, 100, LED_BLINK_DELAY, 3);
    break;
    case LED_MSG_TYPE::INFO_SEND_METRICS:
      blink(0, 0, 255, 100, LED_BLINK_DELAY, 1);
    break;
    case LED_MSG_TYPE::INFO_SAMPLING_STARTED:
      blink(255, 75, 0, 100, LED_BLINK_DELAY, 1);
    break;
  }
}

void Led::onDefault() {
  on(this->defaultRed, this->defaultGreen, this->defaultBlue, this->defaultBrightness);
}

void Led::on(int red, int green, int blue, int brightness) {
  this->pixels.setBrightness(brightness);
  this->pixels.setPixelColor(0, pixels.Color(red, green, blue));
  this->pixels.show();
}

void Led::off() {
  this->pixels.clear();
}