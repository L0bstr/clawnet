[< back](/README.md#-sections)

## 🔌 TCP

### 🧠 Overview
TCP (Transmission Control Protocol) is a connection-oriented protocol that provides reliable,
ordered delivery of bytes between two endpoints over a network.

---

### 🎯 Purpose
Why this concept exists.

---

### 👀 Visual / Mental Model
```mermaid
sequenceDiagram
    participant C as Client
    participant S as Server

    rect rgb(60, 60, 60)
        Note over C, S: Three-way handshake
        C->>S: SYN
        S->>C: SYN-ACK
        C->>S: ACK
    end

    rect rgb(60, 60, 60)
        Note over C, S: Data exchange
        C->>S: Data
        S->>C: ACK
    end

    rect rgb(60, 60, 60)
        Note over C, S: Connection teardown
        C->>S: FIN
        S->>C: ACK
        S->>C: FIN
        C->>S: ACK
    end
```
> SYN (Synchronize) — "I want to connect, here's my starting sequence number" <br>
> SYN-ACK — server agrees and sends its own starting sequence number <br>
> ACK (Acknowledge) — "got it" <br>
> Data — actual payload <br>
> FIN (Finish) — "I'm done sending, want to close"

#### Data exchnage
Data is broken down into smaller packets.

```mermaid
sequenceDiagram
    participant C as Client
    participant S as Server

    S->>C: SEQ=1 [packet 1] ✅
    S->>C: SEQ=2 [packet 2] ❌
    S->>C: SEQ=3 [packet 3] ✅

    Note over C: Missing SEQ=2
    C-->>S: ACK=2 (request SEQ=2)
    C-->>S: ACK=2 (request SEQ=2)
    C-->>S: ACK=2 (request SEQ=2)

    Note over S: 3 duplicated ACK=2 triggers a retransmit for SEQ=2
    S->>C: SEQ=2 [retransmit]

    C-->>S: ACK=4 (3 packets recieved)
```
> SEQ - Sequence number <br>
> ACK - Acknowledgement number

---

### ⚙️ How it works
TCP is a stream protocol - it has no concept of messages or boundaries. When you call `recv()`,
you may get more or less bytes than expected.
It is the application's responsibility to define where one message ends and the next begins.

---

### 🧩 In the system
TCP sits at the transport layer - it handles how data gets there reliably, so higher layers don't have to.

#### [OSI Model](https://en.wikipedia.org/wiki/OSI_model):
|   | Layer number | Layer           | Responsibility                                 | Protocol                 |
|---|--------------|-----------------|------------------------------------------------|--------------------------|
|   | 7            | Application     | Data structuring                               | HTTP, FTP, DNS, SSH      |
|   | 6            | Presentation    | Encoding, encryption, compression              | TLS/SSL, JPEG, ASCII     |
|   | 5            | Session         | Managing sessions between applications         | NetBIOS, RPC             |
| 🢂 | **4**        | **Transport**   | **End-to-end delivery, reliability, ports**    | **TCP, UDP**             |
|   | 3            | Network         | Logical addressing, routing between networks   | IP, ICMP, routing        |
|   | 2            | Data Link       | Node-to-node transfer, MAC addressing, framing | Ethernet, Wi-Fi (802.11) |
|   | 1            | Physical        | Raw bit transmission over physical medium      | Cables, radio, fiber     |

---

### 🔎 Further reading
[Transmission Control Protocol (TCP)](https://www.rfc-editor.org/rfc/rfc9293)
