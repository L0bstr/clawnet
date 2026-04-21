# 🦞 trawl

![Linux only](https://badgen.net/badge/Linux/only/D4A017?icon=terminal)

Exploring networking layers in **C** through **client–server** implementations.

---

### ℹ️ About
`trawl` is a hands-on networking project built to learn how **servers**, **clients**, and **network communication**
works in different layers written in **C**. <br>

[**Read More**](/docs/repo-structure.md)

---

### 📚 Sections 
The project is organized into **sections**, each covering a specific concept or layer of abstraction. <br>
Sections can be **viewed independently** in their **own branches**.

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

> #### 🔗 Read more
> [🛠️ Custom application-layer protocol](./docs/sections/custom_application-layer_protocol.md) <br>
> [🔌 TCP connections](./docs/sections/tcp_connections.md) <br>
> [📨 Receive buffer](./docs/sections/recv_buffer.md)

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
