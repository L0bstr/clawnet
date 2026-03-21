# 🦞 clawnet

An evolving TCP client-server implementation in C.

---

### ℹ️ About

`clawnet` is a hands-on networking project built to learn how servers, clients, and network communication work from the
ground up in C.<br>
The documentation is structured in **sections**, each representing a level of abstraction.<br>
Starting from basic TCP communication and progresses toward:
- ⬆️ higher-level abstractions
- ⬇️ lower-level manual implementations<br>

Each **section** has its own documentation covering the relevant context and how the code works.<br>
The project provides a `server` and a `client` tool you can build and run directly.

### 📚 Sections 

- [🚀 **Starting point**](./docs/starting_point.md)

---

## 📦 Dependencies
- [CMake](https://cmake.org/)
- Build system
- C compiler

---

## 🔧 Build and run
```bash
cmake -B build
cmake --build build

# server
./build/bin/clawnetd --help

# client
./build/bin/clawnet --help
```
