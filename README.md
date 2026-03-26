# 🦞 clawnet

![Linux only](https://badgen.net/badge/Linux/only/D4A017?icon=terminal)

An evolving client and server implementation written in C.

---

### ℹ️ About
`clawnet` is a hands-on networking project built to learn how **servers**, **clients**, and **network communication** work
from the ground up written in **C**. <br>
The documentation is organized into **sections**, each covering a specific concept or layer of abstraction. <br>

---

### 📚 Sections 
```mermaid
flowchart TD
    tcp(["🔌 TCP connections"]):::normal

    classDef normal fill:#3498db, stroke:#3498db, color:#000

    click tcp "https://github.com/L0bstr/clawnet/blob/main/docs/tcp_connections.md"
```
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
```

```bash
# server
./build/bin/clawnetd --help

# client
./build/bin/clawnet --help
```

## 🐳 Dockerize
```bash
docker build -t clawnet-server .
```

```bash
docker run -d -p 3000:3000 --name clawnet-server clawnet-server:latest
```
