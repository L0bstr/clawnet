# Ideas

- [ ] Multiplexing
- [ ] Cross platform

# Links

- [my_tcp_not_reliable](https://blog.netherlabs.nl/articles/2009/01/18/the-ultimate-so_linger-page-or-why-is-my-tcp-not-reliable)

# Project definition

Trawl is a C project for learning and implementing network stack layers from the ground up.
Goal: Build a deep understanding of networking concepts by implementing them — not just reading about them. Every section is both documentation and working code.
core/ is a collection of self-contained modules, each implementing a network layer or abstraction (tcp, http, recv_buffer, etc.). Modules are versioned, expose a stable API via headers, and can depend on other modules as origins. Where a concept has multiple valid implementations, they live as subsections under a parent — all interchangeable behind the same API contract.
app/ is a real server and client built entirely from core/ modules. It is a runtime that loads, wires, and validates modules at startup based on user-provided flags or a config file. It detects what each module provides and requires, resolves the dependency graph, and connects compatible layers together. Invalid or missing combinations are caught and reported clearly.
The long term vision is that app/ becomes a modular network runtime — where you can swap any layer independently and observe how different implementations behave against each other in a real running system.
