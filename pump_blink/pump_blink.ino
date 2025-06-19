#define BLYNK_TEMPLATE_ID "TMPL3tNZWwYkE"
#define BLYNK_TEMPLATE_NAME "Smart IoT"
#define BLYNK_AUTH_TOKEN "o0zhLvRmADkNmG7nrJ0cBuorRjMNsph6"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <BlynkTimer.h>

// WiFi credentials
char ssid[] = "OnePlus 6";
char pass[] = "siya2204";

// Pin definitions (ESP32 GPIOs)
#define TRIG_PIN 14     // GPIO14
#define ECHO_PIN 27     // GPIO27
#define PUMP_PIN 26     // GPIO26 (active-low relay)

// Constants
#define FULL_THRESHOLD_CM 5
#define MAX_DISTANCE_CM 30

// Variables
long duration;
float distanceCM;
int waterLevelPercent;

BlynkTimer timer;

void measureAndControl() {
  // Clear previous trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send 10us pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read pulse from ECHO_PIN
  duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout in 30ms

  if (duration == 0) {
    Serial.println("[WARNING] No pulse received (timeout).");
    distanceCM = MAX_DISTANCE_CM;
  } else {
    distanceCM = duration * 0.034 / 2;
  }

  // Clamp outliers
  if (distanceCM > MAX_DISTANCE_CM) distanceCM = MAX_DISTANCE_CM;

  // Calculate level %
  waterLevelPercent = 100 - ((distanceCM * 100) / MAX_DISTANCE_CM);
  waterLevelPercent = constrain(waterLevelPercent, 0, 100);

  // Control Pump
  if (distanceCM <= FULL_THRESHOLD_CM) {
    digitalWrite(PUMP_PIN, HIGH);  // Pump OFF
    Blynk.virtualWrite(V0, 0);     // LED OFF
    Serial.println("[STATUS] Water level HIGH — Pump OFF");
  } else {
    digitalWrite(PUMP_PIN, LOW);   // Pump ON
    Blynk.virtualWrite(V0, 255);   // LED ON
    Serial.println("[STATUS] Water level LOW — Pump ON");
  }

  // Serial and Blynk output
  Serial.print("[DISTANCE] ");
  Serial.print(distanceCM);
  Serial.print(" cm | [LEVEL] ");
  Serial.print(waterLevelPercent);
  Serial.println(" %");

  Blynk.virtualWrite(V1, waterLevelPercent); // Send to Blynk Gauge
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Pin config
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, HIGH); // Relay OFF (default)

  Serial.println("[BOOT] Connecting to WiFi...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Schedule sensor check every 2 seconds
  timer.setInterval(2000L, measureAndControl);
}

void loop() {
  Blynk.run();
  timer.run();
}
