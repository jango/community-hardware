#define API_ENDPOINT "breadwinner.life"
#define API_PORT 80
#define API_PATH "/api/v1/"
#define HEALTH_ENDPOINT "/health"

#define DEVICE_ID 58

#define UPLOAD_BATCH_SIZE 25
#define UPLOADS_PER_HOUR 4
#define SAMPLES_PER_MINUTE 4

#define VITALS "vitals"
#define FEEDINGS "feedings"

void printBootMessages();
void connectToNet();
void initSensors();
void syncNTP();
void setupPins();
void resetUploadTimer();
void initializeSDCard();
void sampleAndRecordTimer();
void uploadTimer();
void feedingButtonCheck();
void defaultLED();
bool initVL6180();
bool initMCP9808();
void blinkLED(String color);
void recordFeeding();
bool uploadData(String dataName);
void sampleSensors();
void recordSensorData();
bool sampleMCP9808();
bool sampleVL6180();
bool endpointOnline();
bool sendMetric(String path);
void printTimeStamp();
String iso8601();
String printDigits(int digits);