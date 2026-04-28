[< back](/README.md)

# Project Structure

## Layout

```
.
├── sections/
│   ├── tcp/                        ← leaf
│   │   ├── app/
│   │   │   ├── client/
│   │   │   └── server/
│   │   ├── core/
│   │   └── CMakeLists.txt
│   ├── http/                       ← parent
│   │   ├── public-parser/          ← leaf
│   │   │   ├── app/
│   │   │   │   ├── client/
│   │   │   │   └── server/
│   │   │   ├── core/
│   │   │   ├── resources/
│   │   │   └── CMakeLists.txt
│   │   └── own-parser/             ← leaf
│   │       ├── app/
│   │       │   ├── client/
│   │       │   └── server/
│   │       ├── core/
│   │       ├── resources/
│   │       └── CMakeLists.txt
│   └── .../
├── docs/
│   ├── sections/
│   │   ├── tcp.md
│   │   ├── http/
│   │   │   ├── README.md
│   │   │   ├── public-parser.md
│   │   │   └── own-parser.md
│   │   └── .../
│   ├── repo-structure.md
│   └── section-template.md
├── vendor/
│   └── picohttpparser/
├── CMakeLists.txt
└── README.md
```

---

## Sections

A **section** is either a **leaf** or a **parent**.

| Type | Has code | Description |
|------|----------|-------------|
| Leaf | Yes | A single implementation of a concept |
| Parent | No | Groups multiple leaf implementations of the same concept |

Leaf folders: `core/`, `app/`, optional `resources/`, `CMakeLists.txt`, and a corresponding doc under `docs/sections/`.

`resources/` holds static files served or used at runtime (e.g. HTML pages, assets). Only present when a section needs it.

Sections depend only on OS-provided APIs and `vendor/`. They do not depend on each other.

---

## vendor/

Shared across all sections. Sections reference vendor libs directly from the top-level `vendor/`.

Own utilities shared between sections are duplicated per section. If duplication becomes painful, a `sections/shared/` will be introduced.

---

## Build System

The top-level `CMakeLists.txt` uses `add_subdirectory()` to load each leaf section. Each leaf's `CMakeLists.txt` defines its own targets and links against `vendor/` as needed.

Default build compiles everything. To target a specific section:

```bash
cmake --build . -t tcp
cmake --build . -t http-public-parser
cmake --build . -t http-own-parser
cmake --build . -t http              # builds all leaves under http
```

Parent sections are grouping targets only — they aggregate their leaves but produce no binaries themselves.

---

## Versioning

No versioned folders. Section history is tracked by git:

```bash
git log sections/tcp/
```

Git tags mark stable milestones.
