## 🛠️ Custom application protocol

### 🧠 Overview
This topic builds on top of the knowladge from
**[TCP connections](./tcp_connections.md)** section.

---

### 🎯 Purpose
Define rules between the **server** and the **client** to allow reliable data exchange.

---

### 👀 Visual / Mental Model
```mermaid
sequenceDiagram
    participant C as Client
    participant S as Server

    Note over S, C: --Establish connection--

    loop
        C->>S: Send request header + body
        Note over S: Process request header
        Note over S: Process request body
        S->>C: Send response header + body
        Note over C: Process response header
        Note over C: Process response body
    end

    Note over S, C: --Close connection--
```

---

### ⚙️ How it works
Technical explanation (clear but deeper)

---

### 🔗 In the system
Where this fits in the bigger picture

---

### 🔎 Further reading
Links or references for deeper understanding

