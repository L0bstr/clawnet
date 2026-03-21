[< back](../README.md)

## 🚀Starting point 
Blocking, single-connection TCP server and client

---

### Context
environment knowledge needed to understand this abstraction level.

---

### Server pipeline

1. [Create server socket](#1-create-server-socket)
2. [Create server address](#2-create-server-address)
3. [Bind address to socket](#3-bind-address-to-socket)
4. [Set socket as listening](#4-set-socket-as-listening)
5. [Accept client connection](#5-accept-client-connection)
6. [Receive data from client](#6-receive-data-from-client)

---

#### 1. Create server socket
```cpp
int server_socket = socket(AF_INET, SOCK_STREAM, 0);
``` 
🔗 [`socket()`](https://man7.org/linux/man-pages/man2/socket.2.html) <br>
> `AF` - **A**ddress **F**amily <br>
> `INET` - IPv4

---

#### 2. Create server address
```cpp
struct sockaddr_in server_address;
server_address.sin_family = AF_INET;
server_address.sin_port   = htons(SERVER_PORT);
inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);
```
🔗 [`sockaddr`](https://man7.org/linux/man-pages/man3/sockaddr.3type.html) [`htons()`](https://man7.org/linux/man-pages/man3/htonl.3p.html) [`inet_pton()`](https://man7.org/linux/man-pages/man3/inet_pton.3.html)

> `htons` - **h**ost **to** **n**etwork **s**hort (16-bit) <br>
> `pton` - **p**resentation **to** **n**etwork <br>
> `INET` - IPv4

---

#### 3. Bind address to socket
```cpp
bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
```
🔗 [`bind()`](https://man7.org/linux/man-pages/man2/bind.2.html)

---

#### 4. Set socket as listening
```cpp
listen(server_socket, SOMAXCONN);
```
🔗 [`listen()`](https://man7.org/linux/man-pages/man2/listen.2.html)<br>
> `SOMAXCONN` - **S**ocket **O**ption **Max** **Conn**ections

---

#### 5. Accept client connection

```cpp
int client_socket;
struct sockaddr_in client_address;
socklen_t client_address_length = sizeof(client_address);

client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
```
📖 [`accept()`](https://man7.org/linux/man-pages/man2/accept.2.html)

---

#### 6. Receive data from client

**Header** - contains the body length
```cpp
uint16_t buffer;
recv(client_socket, &buffer, sizeof(buffer), MSG_WAITALL);
int request_body_length = ntohs(buffer);
```

**Body** - the actual data
```cpp
char *buffer = malloc(request_body_length + 1);
recv(client_socket, buffer, request_body_length, MSG_WAITALL);
buffer[request_body_length] = '\0';
```

📖 [`recv()`](https://man7.org/linux/man-pages/man2/recv.2.html)<br>
> `ntohs` - **n**etwork **to** **h**ost **s**hort (16-bit)

---

### Client pipeline
step-by-step flow of the client

---

### Protocol stack
information about the layers of protocols wrapping your data at this level

---

### More

---
