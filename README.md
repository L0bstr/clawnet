# 🦞 clawnet

![Linux only](https://badgen.net/badge/Linux/only/D4A017?icon=terminal)

An evolving client and server implementation written in C.

---

### ℹ️ About
`clawnet` is a hands-on networking project built to learn how **servers**, **clients**, and **network communication** work
from the ground up written in **C**.

The documentation is organized into **sections**, each covering a specific concept or layer of abstraction. <br>

---

### 📚 Sections 
```mermaid
stateDiagram-v2
    direction BT

    state "🔌 TCP connections" as tcp
    state "🛠️ Custom application-layer protocol" as custom_app_prot
    state "📨 Receive buffer" as recv_buffer

    tcp --> custom_app_prot
    tcp --> recv_buffer

    classDef highlight fill:#4D8DFF, stroke:#4D8DFF, color:#000
    classDef normal fill:#A9C7FFB3, stroke:#, color:#000

    class tcp highlight
    class custom_app_prot highlight
    class recv_buffer normal
```

> [🛠️ Custom application-layer protocol](./docs/sections/custom_application-layer_protocol.md) <br>
> [🔌 TCP connections](./docs/sections/tcp_connections.md) <br>
> ([📨 Receive buffer](./docs/sections/recv_buffer.md))

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
