*This project has been created as part of the 42 curriculum by ralba-ji, isastre-, eldiaz-c.*

# ft_irc

## Description

ft_irc is a networking project focused on implementing an IRC (Internet Relay Chat) server in C++98.

The server handles multiple simultaneous client connections using non-blocking TCP sockets and I/O multiplexing with poll(). It supports user authentication, nickname management, channel creation and management, private and channel messaging, channel operator privileges, and channel modes (invite-only, topic restrictions, password protection, user limits).

Clients can connect to the server, authenticate themselves, join channels, communicate with other users, and perform channel operations depending on their permissions.

---

## Features

This project introduces concepts such as:

* TCP/IP networking
* Socket programming
* Non-blocking I/O
* Multiplexing with `poll()`
* IRC protocol
* Client and channel management
* Command parsing
* Server replies and error codes
* Operator permissions
* Channel modes and restrictions
* Object-oriented programming in C++98

---

## Instructions

### Compilation

```bash
git clone <repository-url>
cd ft_irc
make
```

### Execution

```bash
./ircserv <port> <password>
```

For example:

```bash
./ircserv 6667 password
```

The server will then listen for incoming TCP connections on port `6667`.

### Connecting with an IRC client

An IRC client such as `HexChat` can be used to connect to the server.

Once connected, clients can use IRC commands to interact with the server.

The server can also receive a connection from simple telnet TCP.

```bash
nc -C 127.0.0.1 6667
```

---

## Supported Commands

The server implements the main commands required by the project, including:

| Command | Description |
| :--- | :--- |
| `PASS` | Authenticate the client using the server password |
| `NICK` | Set or change the client's nickname |
| `USER` | Register the client's username and real name |
| `JOIN` | Join or create a channel |
| `PART` | Leave a channel |
| `PRIVMSG` | Send a private or channel message |
| `QUIT` | Disconnect from the server |
| `KICK` | Remove a user from a channel |
| `INVITE` | Invite a user to a channel |
| `TOPIC` | View or modify a channel topic |
| `PING` | Check whether the server is responding |
| `MODE` | Configure channel modes |

### Supported Channel Modes

| Mode | Description |
|:---:|:---|
| `i` | Invite-only channel |
| `t` | Restrict/Unrestrict changing topic to channel operators  |
| `k` | Channel password (key) |
| `o` | Give/take operator privilege |
| `l` | Set/remove user limit |

---

## What We Learned

- **Networking:** TCP sockets, client-server communication, handling multiple connections, and data fragmentation.
- **I/O Multiplexing:** `poll()` with non-blocking sockets, event-driven loops, and error handling.
- **IRC Protocol:** Command parsing, numeric replies, user/channel management, permissions, and broadcasting.
- **C++98:** OOP, inheritance, polymorphism, STL containers, and modular design.
- **Architecture:** Client-server separation, command execution patterns, and reusable utilities.
- **Teamwork:** Task division, code review, integration, and collaborative testing.

This project demonstrated building a real-time communication server using sockets, multiplexing, and event-driven architecture.

---

## Resources

### References

- [RFC 1459](https://datatracker.ietf.org/doc/html/rfc1459) — Internet Relay Chat Protocol
- [RFC 2812](https://datatracker.ietf.org/doc/html/rfc2812) — IRC Client Protocol
- [Modern IRC Documentation](https://modern.ircdocs.horse/)
    * `socket()` documentation
    * `bind()` documentation
    * `listen()` documentation
    * `accept()` documentation
    * `recv()` / `send()` documentation
    * `poll()` documentation
- Linux socket documentation
- C++98 Standard Library documentation

### Use of AI

AI tools were used as a learning aid during the development of the project for:

* Understanding the IRC protocol.
* Understanding TCP socket communication.
* Explaining `poll()` and non-blocking I/O.
* Debugging compilation and linker errors.
* Reviewing command implementations.
* Discussing server and client architecture.
* Reviewing command implementations
* Designing and debugging IRC command parsers.

All generated explanations and suggestions were reviewed, adapted and implemented manually by the authors.

---
