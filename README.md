# 🦞 trawl

![Linux only](https://badgen.net/badge/Linux/only/D4A017?icon=terminal)

Exploring networking layers in **C** through **client–server** implementation.

---

### ℹ️ About
`trawl` is a hands-on networking project built to learn how **servers**, **clients**, and **network communication**
works in different layers, written in **C**. <br>

[**Project Structure**](/docs/repo-structure.md)

---

### 📚 Sections
The project is organized into **sections**, each covering a specific concept or layer of abstraction. <br>

```mermaid
stateDiagram-v2
    direction BT

    state "🔌 TCP" as tcp
    state "📨 Receive buffer" as recv_buffer
    state "🛠️ Custom protocol" as custom_application_protocol
    state "🌐 HTTP" as http

    state "Application Layer" as application_layer {
        custom_application_protocol
        http
    }

    state "Transport Layer" as transport_layer {
        tcp
    }

    tcp --> custom_application_protocol
    tcp --> recv_buffer
    recv_buffer --> http
```

[🛠️ Custom protocol](/docs/sections/custom_application_layer_protocol/custom_application-layer_protocol.md) |
[🌐 HTTP](/docs/sections/http/readme.md) <br>
[📨 Receive buffer](./docs/sections/recv_buffer.md) <br>
[🔌 TCP](/docs/sections/tcp/readme.md)

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
./build/bin/trawld --help

# client
./build/bin/trawl --help
```

## 🐳 Dockerize
```bash
docker build -t trawl-server .
```

```bash
docker run -d -p 3000:3000 --name trawl-server trawl-server:latest
```
