/**
 * Example: Basic Debug Usage
 *
 * This example demonstrates the core debug macros:
 * - debug() - print without newline
 * - debugln() - print with newline
 * - debugf() - printf-style with unlimited arguments
 *
 * Instructions:
 * 1. Build and upload to ESP32
 * 2. Open serial monitor at 115200 baud
 * 3. Watch debug output
 * 4. Try changing DEBUG=0 in platformio.ini to disable all output
 */

#include <Arduino.h>
#include <debug.h>

void setup() {
  Serial.begin(115200);
  delay(100);

  // ========== BASIC PRINTING ==========
  debugln("=== Debug Macro Examples ===");
  debugln("");

  // Simple printing
  debug("Hello ");
  debugln("World");

  debugln("");
  debugln("--- Printf-style Formatting ---");

  // Formatted printing with single argument
  debugf("Integer: %d\n", 42);
  debugf("Float: %.2f\n", 3.14159);
  debugf("Hex: 0x%X\n", 255);
  debugf("Binary: %b\n", 0b1010);

  debugln("");
  debugln("--- Multiple Arguments (Variadic) ---");

  // Multiple arguments - this is where the new system shines!
  int x = 10, y = 20, z = 30;
  debugf("Single: X=%d\n", x);
  debugf("Double: X=%d, Y=%d\n", x, y);
  debugf("Triple: X=%d, Y=%d, Z=%d\n", x, y, z);  // ✓ Works!

  // Four arguments - would fail with old system
  int a = 1, b = 2, c = 3, d = 4;
  debugf("Quad: A=%d, B=%d, C=%d, D=%d\n", a, b, c, d);  // ✓ Works!

  // Many arguments
  debugf("Six: %d, %d, %d, %d, %d, %d\n", a, b, c, d, 5, 6);  // ✓ Works!

  debugln("");
  debugln("--- Labeled Output ---");

  // Print with labels
  debug_val("temperature", 23);
  debug_val("humidity", 65);
  debug_val("pressure", 1013);

  debugln("");
  debugln("--- Tagged Output ---");

  // Output with category tags
  debug_tag("[INFO]", "System initialized");
  debug_tag("[CAN]", "Bus ready");
  debug_tag("[WiFi]", "Connected");
  debug_tag("[ERROR]", "Something went wrong");

  debugln("");
  debugln("--- Hex and Binary ---");

  // Hex and binary output
  uint8_t value = 0xAB;
  debug("Hex value: 0x");
  debug_hex(value);
  debugln("");

  debug("Binary value: ");
  debug_bin(0b11001100);
  debugln("");

  debugln("");
  debugln("=== Test Complete ===");
}

void loop() {
  // In a real application, you might have periodic debug output
  delay(5000);
  debugf("Loop iteration at: %lu ms\n", millis());
}
