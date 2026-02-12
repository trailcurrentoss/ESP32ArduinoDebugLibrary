/**
 * Example: Conditional Debug Output and Error Handling
 *
 * This example demonstrates advanced debug features:
 * - debug_if() - conditional debug output
 * - debug_assert() - assert with halt
 * - debug_tag() - categorized output
 * - debug_array() - hex dump
 *
 * Instructions:
 * 1. Build and upload to ESP32
 * 2. Open serial monitor at 115200 baud
 * 3. Watch conditional output based on sensor values
 */

#include <Arduino.h>
#include <debug.h>

// Simulated sensor values
struct SensorData {
  float temperature;
  float humidity;
  int pressure;
  bool error;
};

// Simulated device state
enum DeviceState {
  STATE_INIT,
  STATE_IDLE,
  STATE_ACTIVE,
  STATE_ERROR
};

DeviceState current_state = STATE_INIT;

void stateTransition(DeviceState new_state) {
  const char* state_names[] = {"INIT", "IDLE", "ACTIVE", "ERROR"};

  debugf("[STATE] Transition: %s -> %s\n",
         state_names[current_state],
         state_names[new_state]);

  current_state = new_state;
}

bool initializeHardware() {
  debug_tag("[INIT]", "Starting hardware initialization");

  // Simulate hardware check
  debugf("  Checking I2C... ");
  delay(100);
  debugln("OK");

  debugf("  Checking WiFi... ");
  delay(100);
  debugln("OK");

  debugf("  Checking CAN... ");
  delay(100);
  debugln("OK");

  debug_tag("[INIT]", "Hardware initialization complete");
  return true;
}

void readSensors(SensorData& data) {
  // Simulate sensor readings
  data.temperature = 22.5 + (rand() % 10);
  data.humidity = 45.0 + (rand() % 30);
  data.pressure = 1013 + (rand() % 10);
  data.error = false;

  debugf("[SENSOR] T=%.1f°C, H=%.1f%%, P=%d hPa\n",
         data.temperature, data.humidity, data.pressure);

  // Conditional warnings
  debug_if(data.temperature > 30.0,
           "  ⚠️ WARNING: High temperature: %.1f°C", data.temperature);

  debug_if(data.temperature < 15.0,
           "  ⚠️ WARNING: Low temperature: %.1f°C", data.temperature);

  debug_if(data.humidity > 70.0,
           "  ⚠️ WARNING: High humidity: %.1f%%", data.humidity);

  debug_if(data.humidity < 30.0,
           "  ⚠️ WARNING: Low humidity: %.1f%%", data.humidity);
}

void processCAN(uint8_t* frame, uint8_t length) {
  debug_tag("[CAN]", "Frame received");
  debugf("  Length: %d bytes\n", length);

  debug("  Data: ");
  for (int i = 0; i < length; i++) {
    debugf("%02X ", frame[i]);
  }
  debugln("");

  // Check for error frames
  debug_if(frame[0] == 0xFF,
           "  ⚠️ Error frame detected: 0x%02X", frame[0]);
}

void setup() {
  Serial.begin(115200);
  delay(100);

  debugln("=== Conditional Debug Example ===");
  debugln("");

  // Initialize hardware with assertions
  debug_tag("[STARTUP]", "Initializing system");

  if (!initializeHardware()) {
    debug_tag("[ERROR]", "Hardware initialization failed!");
    debug_assert(false, "Cannot continue without hardware!");
    // If DEBUG=1, this will halt. If DEBUG=0, it compiles away.
  }

  stateTransition(STATE_IDLE);

  debugln("");
}

void loop() {
  static unsigned long last_read = 0;
  static int iteration = 0;

  if (millis() - last_read > 5000) {  // Every 5 seconds
    last_read = millis();
    iteration++;

    debugln("");
    debugf("=== Iteration %d ===\n", iteration);

    // Read sensors and check values
    SensorData data;
    readSensors(data);

    // Simulate CAN reception
    uint8_t test_frame[] = {0x42, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE};
    processCAN(test_frame, 8);

    // Simulate occasional errors
    if (iteration % 4 == 0) {
      debug_tag("[ERROR]", "Simulated error condition");
      stateTransition(STATE_ERROR);
      delay(1000);
      stateTransition(STATE_IDLE);
    }

    // Memory status
    debug_stack();

    debugf("Uptime: %lu ms\n", millis());
  }

  // Your main application loop here
  yield();
}

/*
 * OUTPUT EXAMPLE:
 *
 * === Conditional Debug Example ===
 *
 * [STARTUP] Initializing system
 * [INIT] Starting hardware initialization
 *   Checking I2C... OK
 *   Checking WiFi... OK
 *   Checking CAN... OK
 * [INIT] Hardware initialization complete
 * [STATE] Transition: INIT -> IDLE
 *
 * === Iteration 1 ===
 * [SENSOR] T=26.5°C, H=62.0%, P=1018 hPa
 * [CAN] Frame received
 *   Length: 8 bytes
 *   Data: 42 12 34 56 78 9A BC DE
 * [STACK] ~8192 bytes free
 * Uptime: 5234 ms
 *
 * === Iteration 2 ===
 * [SENSOR] T=31.2°C, H=45.0%, P=1015 hPa
 *   ⚠️ WARNING: High temperature: 31.2°C
 * [CAN] Frame received
 *   Length: 8 bytes
 *   Data: 42 12 34 56 78 9A BC DE
 * [STACK] ~8192 bytes free
 * Uptime: 10456 ms
 *
 * When DEBUG=0 in platformio.ini, ALL debug output is compiled away!
 */
