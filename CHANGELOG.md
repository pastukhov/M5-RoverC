# Changelog

All notable changes to this project are documented in this file.

## [0.0.2] - 2026-02-21

### Added
- Native ESP-IDF support alongside Arduino support.
- `CMakeLists.txt` for ESP-IDF component integration.
- ESP-IDF usage section in `README.md`.
- Contributor guide in `AGENTS.md`.

### Changed
- `M5_RoverC` API now provides platform-specific `begin(...)` overloads for Arduino and ESP-IDF.
- Internal speed clamping logic is now platform-agnostic.
- PlatformIO metadata now declares both `arduino` and `espidf` frameworks.

