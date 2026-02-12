/**
 * Example: Performance Profiling with Debug Macros
 *
 * This example demonstrates the performance profiling features:
 * - debug_micros() - capture timestamp
 * - debug_elapsed() - print elapsed time
 * - debug_stack() - show free stack space
 *
 * Instructions:
 * 1. Build and upload to ESP32
 * 2. Open serial monitor at 115200 baud
 * 3. Watch timing measurements
 */

#include <Arduino.h>
#include <debug.h>

// Simulate various operations
void simpleOperation() {
  delay(10);
}

void mediumOperation() {
  delay(50);
}

void expensiveOperation() {
  delay(200);
}

void setup() {
  Serial.begin(115200);
  delay(100);

  debugln("=== Performance Profiling Example ===");
  debugln("");

  // ========== SINGLE OPERATION TIMING ==========
  debugln("--- Timing Single Operations ---");

  // Time a simple operation
  unsigned long start1 = debug_micros();
  simpleOperation();
  debug_elapsed(start1, "Simple operation");

  // Time a medium operation
  unsigned long start2 = debug_micros();
  mediumOperation();
  debug_elapsed(start2, "Medium operation");

  // Time an expensive operation
  unsigned long start3 = debug_micros();
  expensiveOperation();
  debug_elapsed(start3, "Expensive operation");

  debugln("");

  // ========== MULTIPLE OPERATION PROFILING ==========
  debugln("--- Profiling Series of Operations ---");

  for (int i = 0; i < 5; i++) {
    unsigned long op_start = debug_micros();
    delay(i * 10);  // Increase delay each iteration
    debugf("[Iteration %d] ", i);
    debug_elapsed(op_start, "");
  }

  debugln("");

  // ========== STACK PROFILING ==========
  debugln("--- Stack Usage ---");

  debug_stack();

  debugln("");

  // ========== SETUP TIME ==========
  debugln("--- Startup Timing ---");

  // Simulate entire setup duration
  unsigned long setup_start = debug_micros();
  // Setup work would happen here
  delay(100);
  debug_elapsed(setup_start, "Total setup time");

  debugln("");
  debugln("=== Test Complete ===");
  debugln("");
  debugln("Watch the serial output for timing measurements.");
  debugln("Note: All debug output disabled when DEBUG=0 in platformio.ini");
}

void loop() {
  // Periodic profiling example
  static unsigned long last_profile = 0;

  if (millis() - last_profile > 10000) {  // Every 10 seconds
    last_profile = millis();

    debugln("");
    debug_tag("[PROFILE]", "System status");
    debug_stack();
    debugf("[Uptime] %lu ms\n", millis());
  }

  // Your main application code here
  delay(1000);
}
