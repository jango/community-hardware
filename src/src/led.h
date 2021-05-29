#ifndef MY_LED_H
#define MY_LED_H

// Led pin number.
#define LED_PIN 15

// Default value for how long the led stays on when blinking.
#define LED_BLINK_DELAY 200

/**
 * Defines message types.
 */
enum class LED_MSG_TYPE {
    INFO_OK,
    INFO_PING_OK,
    INFO_BTN_PRESSED,
    INFO_SEND_METRICS,
    INFO_SAMPLING_STARTED,
    ERROR_UPLOAD,
    ERROR_NETWORK,
    ERROR_FS
};

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Led {
  private:
    byte pin;
    int defaultRed;
    int defaultGreen;
    int defaultBlue;
    int defaultBrightness;
    Adafruit_NeoPixel pixels;
    
    void blink(int red, int green, int blue, int brightness, int delayms, int times);
    
  public:
    Led(byte pin);
    void init();
    void updateDefaults(int defaultRed, int defaultGreen, int defaultBlue, int defaultBrightness);
    void illuminateSensor();
    void displayLedMessage(LED_MSG_TYPE msgType);
    void onDefault();
    void on(int red, int green, int blue, int brightness);
    void off();
};

#endif