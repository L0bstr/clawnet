# 🦞 trawl

![Linux only](https://badgen.net/badge/Linux/only/D4A017?icon=terminal)

Exploring networking layers in **C** through **client–server** implementations.

---

### ℹ️ About
`trawl` is a hands-on networking project built to learn how **servers**, **clients**, and **network communication**
works in different layers, written in **C**. <br>

[**Read More**](./docs/repo-structure.md)

---

### 📚 Sections 
The project is organized into **sections**, each covering a specific concept or layer of abstraction. <br>
Sections can be **studied independently** in their **own branches**.

```mermaid
stateDiagram-v2
    direction BT

    state "🔌 TCP connections" as tcp
    state "📨 Receive buffer" as recv_buffer
    state "🛠️ Custom protocol" as custom_prot
    state "🌐 HTTP" as http

    state "Application Layer" as application_layer {
        custom_prot
        http
    }

    state "Transport Layer" as transport_layer {
        tcp
    }

    tcp --> custom_prot
    tcp --> recv_buffer
    recv_buffer --> http

    classDef current fill:#223760, stroke:#D3D7DF, color:#D3D7DF, stroke-width:2px
    classDef normal fill:#223760, stroke:#223760, color:#D3D7DF

    class tcp normal
    class recv_buffer normal
    class custom_prot normal
    class http current
```

> [🛠️ Custom application-layer protocol](./docs/sections/custom_application-layer_protocol.md) <br>
> [🔌 TCP connections](./docs/sections/tcp_connections.md) <br>
> [📨 Receive buffer](./docs/sections/recv_buffer.md) <br>
> [🌐 HTTP](./docs/sections/picohttpparser_http_parser.md)

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
