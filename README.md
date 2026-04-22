# 🦞 trawl

![Linux only](https://badgen.net/badge/Linux/only/D4A017?icon=terminal)

Exploring networking layers in **C** through **client–server** implementations.

---

### ℹ️ About
`trawl` is a hands-on networking project built to learn how **servers**, **clients**, and **network communication**
works in different layers, written in **C**. <br>

[**Read More**](/docs/repo-structure.md)

---

### 📚 Sections 
The project is organized into **sections**, each covering a specific concept or layer of abstraction. <br>
Sections can be **studied independently** in their **own branches**.

```mermaid
stateDiagram-v2
    direction BT

    state "🔌 TCP connections" as tcp
    state "📨 Receive buffer" as recv_buffer
    state "🛠️ Custom application-layer protocol" as custom_app_prot
    state "🌐 picohttpparser http parser" as picohttpparser

    state "Application Layer" as application_layer {
        custom_app_prot
        picohttpparser
    }

    state "Transport Layer" as transport_layer {
        tcp
    }

    tcp --> custom_app_prot
    tcp --> recv_buffer
    recv_buffer --> picohttpparser

    classDef current fill:#4D8DFF, stroke:#4D8DFF, color:#000
    classDef normal fill:#A9C7FFB3, stroke:#A9C7FFB3, color:#000

    class tcp normal
    class recv_buffer normal
    class custom_app_prot normal
    class picohttpparser current
```

> [🛠️ Custom application-layer protocol](./docs/sections/custom_application-layer_protocol.md) <br>
> [🔌 TCP connections](./docs/sections/tcp_connections.md) <br>
> [📨 Receive buffer](./docs/sections/recv_buffer.md) <br>
> [🌐 picohttpparser http parser](./docs/sections/picohttpparser_http_parser.md)

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
