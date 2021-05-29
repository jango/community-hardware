#include "Led.h"

/**
 * Initialize led class.
 * 
 * @param pin the pin to which the ledi s connected.
 */
Led::Led(byte pin) {
  this->pin = pin;
  this->defaultRed = 0;
  this->defaultGreen = 0;
  this->defaultBlue = 0;
  this->defaultBrightness = 100;
  this->pixels = Adafruit_NeoPixel(1, pin, NEO_RGB + NEO_KHZ800);
}

/**
 * Blinks a specified number of times with specified color.
 *
 * @param red value of the red component.
 * @param blue value of the blue component.
 * @param green value of the green component.
 * @param brightness value of the brightness component.
 * @param delayms how long to keep the led on.
 * @param times how many time to blink.
 */
void Led::blink(int red, int green, int blue, int brightness, int delayms, int times){
  off();

  for (int i = 0; i < times; i++){
    on(red, green, blue, brightness);
    delay(delayms);
    off();  
  }
}

/**
 * Inits the led strip.
 */
void Led::init() {
  pixels.begin();
  pixels.show();
}

/**
 * Updates default colors and brightness of led.
 * 
 * @param defaultRed value of the red component.
 * @param defaultBlue value of the blue component.
 * @param defaultGreen value of the green component.
 * @param defaultBrightness value of the brightness component.
 */
void Led::updateDefaults(int defaultRed, int defaultGreen, int defaultBlue, int defaultBrightness){
  this->defaultRed = defaultRed;
  this->defaultGreen = defaultGreen;
  this->defaultBlue = defaultBlue;
  this->defaultBrightness = defaultBrightness;
}

/**
 * Uses an led sequence to illuminate the sensor.
 */
void Led::illuminateSensor(){
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

/**
 * Displays a pre-defined led "message".
 * 
 * @param msgType the message to display.
 */
void Led::displayLedMessage(LED_MSG_TYPE msgType) {
  pixels.setBrightness(defaultBrightness);

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

/**
 * Turns on and keeps on led using saved default values. 
 *
 * @param defaultRed value of the red component.
 * @param defaultBlue value of the blue component.
 * @param defaultGreen value of the green component.
 * @param defaultBrightness value of the brightness component.
 */
void Led::onDefault() {
  on(defaultRed, defaultGreen, defaultBlue, defaultBrightness);
}

/**
 * Turns led on with specified color and brightness values.
 * 
 * @param red value of the red component.
 * @param blue value of the blue component.
 * @param green value of the green component.
 * @param brightness value of the brightness component.
 */
void Led::on(int red, int green, int blue, int brightness) {
  pixels.setBrightness(brightness);
  pixels.setPixelColor(0, pixels.Color(red, green, blue));
  pixels.show();
}

/**
 * Turns led off.
 */
void Led::off() {
  pixels.clear();
}