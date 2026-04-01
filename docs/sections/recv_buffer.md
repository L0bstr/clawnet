[< back](../../README.md)

## 📨 Receive buffer

### 🧠 Overview
Instead of handling every message immediately, data is accumulated in **controlled and larger chunks**.

---

### 🎯 Purpose
- Improve performance by reducing `SYSCALLS` from repeated OS buffer reads.
- Provide better control over incoming data.

---

### 👀 Visual / Mental Model

#### Before
```mermaid
stateDiagram-v2
    direction LR

    state "Network" as network {
        state "..." as other
    }

    state "Device" as dev {

        state "OS" as os
        state "Program" as program {

            state "recv()" as recv
            state "send()" as send
            state "Process data" as process
        }
    }

    other --> os
    os --> recv
    recv --> process : partial or excess data
    process --> send : may discard unused data
    send --> os
    os --> other
```

#### After
```mermaid
stateDiagram-v2
    direction LR

    state "Network" as network {
        state "..." as other
    }

    state "Device" as dev {
        state "OS" as os
        state "Program" as program {

            state "recv()" as recv
            state "Receive buffer" as recv_buf
            state "Process data" as process
            state "send()" as send
        }
    }

    other --> os
    os --> recv
    recv --> recv_buf : read available data
    recv_buf --> process : consume what is needed
    process --> recv_buf : wait for more data
    process --> send
    send --> os
    os --> other
```

---

### ⚙️ How it works
[needs implementation]

---

### 🔗 In the system
Part of the layer that uses it (5-7).

#### [OSI Model](https://en.wikipedia.org/wiki/OSI_model):
| Layer number | Layer        | Responsibility                                 | Protocol                 |
|--------------|--------------|------------------------------------------------|--------------------------|
| 🢂 7          | Application  | Data structuring                               | HTTP, FTP, DNS, SSH      |
| 🢂 6          | Presentation | Encoding, encryption, compression              | TLS/SSL, JPEG, ASCII     |
| 🢂 5          | Session      | Managing sessions between applications         | NetBIOS, RPC             |
| 4            | Transport    | End-to-end delivery, reliability, ports        | TCP, UDP                 |
| 3            | Network      | Logical addressing, routing between networks   | IP, ICMP, routing        |
| 2            | Data Link    | Node-to-node transfer, MAC addressing, framing | Ethernet, Wi-Fi (802.11) |
| 1            | Physical     | Raw bit transmission over physical medium      | Cables, radio, fiber     |

---

<!-- ### 🔎 Further reading -->
<!-- Links or references for deeper understanding -->
