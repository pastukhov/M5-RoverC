# Repository Guidelines

## Project Structure & Module Organization
- `src/` contains the library implementation: `M5_RoverC.h` (public API) and `M5_RoverC.cpp` (driver logic).
- `examples/` contains runnable Arduino sketches grouped by device and scenario (for example `examples/RunningRoverC/RunningRoverC.ino`).
- Root metadata files define Arduino Library Manager behavior:
  - `library.properties`
  - `library.json`
- `README.md` provides a high-level overview and hardware documentation link.

## Build, Test, and Development Commands
This repository has no standalone build system; validate changes with Arduino tooling.
- `arduino-cli lib install "M5-RoverC"`: install the library locally for sketch testing.
- `arduino-cli compile --fqbn esp32:esp32:m5stack_core_esp32 examples/RunningRoverC/RunningRoverC.ino`: compile a sample sketch.
- `arduino-cli compile --fqbn esp32:esp32:m5stick-c examples/RoverC_M5StickC/RunningRoverC/RunningRoverC.ino`: validate M5StickC-specific examples.
- `rg "RoverC" -n src examples`: quickly find API usage and references.

## Coding Style & Naming Conventions
- Use 2-space indentation and keep line endings as LF.
- Follow existing C++/Arduino style in `src/`; avoid large formatting-only diffs.
- Keep public symbols consistent with existing naming (`M5_RoverC`, `SetSpeed`, etc.).
- Prefer descriptive sketch names and preserve current example folder grouping by hardware target.

## Testing Guidelines
- There is no formal unit test suite in this repository.
- Treat successful compilation of affected examples as the primary smoke test.
- When modifying the library API, compile at least:
  - one generic example under `examples/RunningRoverC/`
  - one M5StickC or M5StickCPlus example under `examples/RoverC_*`
- In pull requests, list which sketches and board FQBNs were compiled.

## Commit & Pull Request Guidelines
- Write short, imperative commit messages, optionally scoped:
  - `src: fix motor speed clamp`
  - `examples: update remote control mapping`
- Keep commits focused and reversible.
- PRs should include:
  - purpose and change summary
  - manual verification steps (compile commands + target board)
  - linked issue (`#<id>`) when applicable
  - screenshots/videos only for behavior demos on hardware.

## Security & Configuration Tips
- Do not commit secrets, local machine paths, or board-specific credentials.
- Keep version metadata (`library.properties`, `library.json`) aligned when publishing updates.
