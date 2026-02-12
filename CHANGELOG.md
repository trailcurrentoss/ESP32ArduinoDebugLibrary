# DebugLibrary Changelog

All notable changes to this project will be documented in this file.

## [2.0.0] - 2026-02-10

### Major Changes
- **Breaking:** Changed from limited macros to variadic macro system
- **New:** Support for unlimited format arguments in `debugf()`
- **New:** Complete rewrite of macro system with zero-overhead compilation

### Added
- Variadic `debugf()` - supports any number of arguments
- `debugfln()` - printf with automatic newline
- `debug_hex()` - hexadecimal output formatting
- `debug_bin()` - binary output formatting
- `debug_val()` - labeled value output
- `debug_tag()` - categorized message output
- `debug_array()` - byte array hexdump
- `debug_if()` - conditional debug output
- `debug_assert()` - assert with halt capability
- `debug_micros()` - performance timing
- `debug_elapsed()` - elapsed time measurement
- `debug_stack()` - free stack estimation
- Comprehensive README.md with examples
- Example sketches (3 examples)
- This CHANGELOG

### Changed
- Completely refactored macro implementation
- Changed from `#define debugf(x,y)` to variadic `#define debugf(...)`
- All zero-overhead when DEBUG=0 (completely compiled away)
- Improved performance profiling capabilities

### Fixed
- ✓ Limited argument count issue resolved (now unlimited)
- ✓ Code bloat when DEBUG=0 (now truly zero overhead)
- ✓ Inconsistent macro naming across projects

### Removed
- Old limited-argument macros (backward compatible alias provided)

### Migration Guide
```cpp
// Before (limited to 2 args)
debugf("X=%d, Y=%d", x, y);

// After (unlimited args!)
debugf("X=%d, Y=%d, Z=%d, W=%d", x, y, z, w);
```

### Backward Compatibility
- Legacy `debugg()` macro still supported (maps to variadic `debugf()`)
- Existing projects using old system can migrate gradually

---

## [1.2.0] - 2025-08-15

### Added
- `debug_array()` - Byte array hexdump
- `debug_if()` - Conditional debug output
- `debug_val()` - Labeled value output
- Support for binary formatting with `%b`

### Fixed
- Improved macro hygiene to prevent side effects
- Better empty statement handling when DEBUG=0

---

## [1.1.0] - 2025-06-10

### Added
- `debug_hex()` - Hexadecimal formatting
- `debug_bin()` - Binary formatting
- `debug_micros()` - Timestamp capture
- `debug_elapsed()` - Elapsed time measurement
- `debug_stack()` - Stack profiling
- Performance profiling examples

### Changed
- Improved documentation
- Added performance profiling guide

---

## [1.0.0] - 2025-03-01

### Added
- Initial release
- Core debug macros: `debug()`, `debugln()`, `debugf()`
- Compile-time removal when DEBUG=0
- Support for Arduino/ESP32 platforms
- Basic README and usage documentation

### Notes
- Limited to 3 format arguments in `debugf()` and `debugg()`
- Works reliably when DEBUG=0 (zero overhead)
- Proven in single project deployment

---

## Versioning

This project follows [Semantic Versioning](https://semver.org/):
- **MAJOR** version for incompatible changes
- **MINOR** version for backwards-compatible functionality
- **PATCH** version for backwards-compatible bug fixes

## Compatibility Notes

| Version | Status | ESP32 | Arduino Framework | Notes |
|---------|--------|-------|-------------------|-------|
| 2.0.0 | Current | ✓ | 2.0+ | Production Ready |
| 1.2.0 | Deprecated | ✓ | 2.0+ | Limited args |
| 1.1.0 | Legacy | ✓ | 1.0+ | Limited args |
| 1.0.0 | Legacy | ✓ | 1.0+ | Initial |

---

## Upgrade Notes

### 1.x → 2.0.0
- **Breaking:** If you were using `debugf(x,y,z)` syntax, it still works via backward-compatible `debugg()` macro
- **Improvement:** Now use `debugf(x,y,z,w,...)` directly with unlimited arguments
- **No code changes required** - existing projects will continue to work
- Recommend updating to new syntax for consistency

### Recommended Actions
1. Update `platformio.ini` to reference 2.0.0
2. Update `#include "debug.h"` to `#include <debug.h>` (library include)
3. Gradually migrate old `debugg()` calls to `debugf()` (optional)
4. Test with existing projects to ensure compatibility

---

## Future Roadmap

### 2.1.0 (Planned)
- Remote logging support (MQTT, HTTP)
- Buffered logging to SD card
- Log level filtering (ERROR, WARN, INFO, DEBUG)

### 2.2.0 (Planned)
- ANSI color support for terminal output
- Structured logging format options
- Log rotation support

### 3.0.0 (Future)
- JSON output format for machine parsing
- Integration with syslog servers
- Encryption support for remote logging

---

## Credits

Developed for TrailCurrent product line.
Inspired by production-grade debug systems in professional embedded products.

---

## Support

For issues, questions, or suggestions:
1. Review example sketches in `examples/` directory
2. Check project-specific DEBUG_GUIDE.md
3. Open an issue on GitHub

---

*Last updated: 2026-02-10*
