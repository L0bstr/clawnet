## 📌 Repo structure

### Folders

`core/` where every section is implemented. `core` builds into a lib.<br>
`app/` where the **server** and the **client** source code is.
These use the `core` lib.

### Sections
The project is organized into sections, each covering a specific concept or layer of abstraction.
Sections are independent, they evolve on their own branches and are versioned with tags.

```bash
section/tcp@v1        # stable, others derive from this
section/recv_buffer@v1
section/protocol@v1
```

A section branch contains the full working repo at that section's level.
core/ holds only what that section introduces no accumulation across branches.
When a section reaches a stable point it gets tagged.
Other sections declare which tag they depend on, documented in their README, not enforced by the build.
