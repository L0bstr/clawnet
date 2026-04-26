[< back](/README.md#-sections)

# Project Structure

## Overview

The project explores and implements network stack layers and abstractions.

- `core/` - all implementations, organized as sections
- `app/` - a real server and client built from `core/` modules, selectable at runtime via flags

```
./build/bin/client --http=public-parser@v1
./build/bin/server --http=own-parser@v1
```

---

## Layout

```
.
├── core/
│   ├── include/
│   │   └── trawl/
│   │       ├── http_v1.h       ← API contract for all http/*/v1 modules
│   │       ├── tcp_v1.h
│   │       └── ...
│   └── src/
│       ├── http/
│       │   ├── public-parser/
│       │   │   └── v1/
│       │   └── own-parser/
│       │       └── v1/
│       └── tcp/
│           └── berkeley/
│               └── v1/
└── app/
    ├── server/
    └── client/
```

---

## Sections

A **section** is a network concept or abstraction (e.g. `http`, `tcp`, `recv_buffer`).

### Two types of sections

| Type | Has `vX/` folders | Purpose |
|------|-------------------|---------|
| **Parent** | No | Groups related subsections, contains only a `README.md` |
| **Leaf** | Yes | Actual implementation, exposes an API to `app/` |

A parent section exists only when there are multiple implementations of the same concept.

```
src/
  http/               ← parent: grouping only
    public-parser/    ← leaf: implements http using a public lib
      v1/
    own-parser/       ← leaf: implements http from scratch
      v1/
```

A standalone concept with one implementation is just a leaf directly:

```
src/
  recv_buffer/        ← leaf directly, no parent needed
    v1/
```

---

## API Contract

Every leaf section must expose an API that `app/` can consume.

The contract is defined as a header in `core/include/trawl/`:

- One header per **parent section + major version**: `http_v1.h`, `tcp_v1.h`
- All sibling leaves at the same version **must implement the same header**
- `app/` only includes the contract header - never the implementation

This means all `http/*/v1/` modules are interchangeable from `app/`'s perspective.

---

## Versioning

| Segment | Tracked by | Notes |
|---------|------------|-------|
| Major | Folder (`v1/`, `v2/`) | Stable, permanent |
| Minor/patch | Git tag (`v1.2`) | No folder, tagged on main |

- A **breaking change** → new major folder + new contract header version
- Each major version copies the previous as a starting point
- Only `v1.0+` may be used as an origin by other sections

### Lifecycle
```
1. Implement under v0/ (unstable, no contract required)
2. Define the contract header
3. Promote to v1.0 when stable
```

---

## Origins

A section may build on another section from `core/`. That section is its **origin**.

- Only stable versions (`v1.0+`) may be used as origins
- Origin updates are manual and opt-in

```
http/own-parser/v1  →  tcp/berkeley/v1  →  recv_buffer/v1
```

---

## Future: Cross-Platform Support

Some sections are inherently OS-specific (e.g. `tcp`, platform I/O). Others are pure logic (e.g. `http` parsing)
and require no changes per platform.

For OS-specific sections, platform support is added as subsections:

```
src/
  tcp/
    linux/
      v1/
    windows/
      v1/
```

The build system detects the target OS and selects the correct subsection automatically. Sections with no platform variants
(like `http`) are untouched.

This means cross-platform support is **additive** - only the OS-specific sections gain new subsections. Nothing else changes.

A `platform/` section would also be introduced to abstract OS-level APIs (`dlopen`, timers, signals etc.), with the same per-OS
subsection pattern. Everything above it remains portable.
