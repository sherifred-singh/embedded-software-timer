# ⏱️ Embedded Non-Blocking Software Timer Queue in C

[![C/C++ Software Timer CI](https://github.com/Sherifred123/embedded-software-timer/actions/workflows/ci.yml/badge.svg)](https://github.com/Sherifred123/embedded-software-timer/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

A lightweight, deterministic **Tick-Based Software Timer Module** written in C99 for **Microchip PIC18**, **STM32**, and **ESP32** microcontrollers.

Allows running dozens of concurrent one-shot and periodic timers from a single hardware timer ISR (`SysTick` or Timer0/Timer1) without blocking the CPU with delay loops.

---

## ⚡ Features

- **Zero Dynamic Memory Allocation:** Static timer handles (`soft_timer_t`) for MISRA-C compliance.
- **Roll-over Safe:** Arithmetic handles 32-bit tick wrap-around cleanly.
- **One-Shot & Periodic Modes:** Auto-reloads period for recurring tasks (e.g. LED blink, sensor polling, watchdog feeding).
- **Callback Driven:** Executes non-blocking user callbacks upon expiration.

---

## 🧪 Running Unit Tests

```bash
make
```

---

## 📜 License
Released under the [MIT License](LICENSE). Designed and maintained by **Sherifred Singh**.
