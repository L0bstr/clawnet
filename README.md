# clawnet

An evolving TCP client-server implementation in C.

---

## About

`clawnet` is a hands-on networking project built to learn how servers, clients, and network communication work from the
ground up - in C.<br>
The documentation is structured in **levels**, each representing a level of abstraction.<br>
Starting from basic TCP communication and progresses toward:
- 🔼 higher-level abstractions
- 🔽 lower-level manual implementations<br>

Each level has its own documentation covering the relevant context and how things work.<br>
The project provides a server and a client tool you can build and run directly.

### Levels

| Level | Docs |
|-------|-------------|
| **0** | [Blocking, single-connection TCP server and client](./docs/lvl_0.md) |

---

## Dependencies
- [CMake](https://cmake.org/)
- Build system
- C compiler

---

## Build and run
```bash
cmake -B build
cmake --build build

# server
./build/bin/clawnetd --help

# client
./build/bin/clawnet --help
```
