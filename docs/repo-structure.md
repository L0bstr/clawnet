# Project Structure

This is an educational project.
Its goal is to document specific concepts and layers of abstraction by implementing them in isolated,
self-contained units called **sections**. Each section builds the same tools but may cover different features or approaches.

---

## Section Layout
```
.
├── core/       # Library code of sections the current branch builds on
├── app/
│   ├── server/ # Server source
│   └── client/ # Client source
```

`core/` is not a shared monolithic library. It contains only what the currently active section needs. `app/` consumes it.

---

## Branches
Each section lives on its **own branch**. Branches are independent and evolve separately. They are never merged into `main`.

```
main
section/a
section/b
section/c
...
```

### `main`
`main` does not contain runnable code for all sections. It serves two purposes:

1. **Index** - documents all sections and links to their branch or tag
2. **Showcase** - checks out one representative section as a concrete entry point for new readers

---

## Sections
A section is a self-contained implementation that documents a specific concept.
It lives on its own branch and is versioned independently.

### Section Variants and Subsections
A section may also represent a layer of abstraction explored at multiple levels. The pattern is:

1. Use an existing protocol/standard as the starting point (e.g. HTTP, TCP)
2. Use a public library to implement it — learn how it works from the outside
3. Build your own replica — implement the internals yourself
4. Invent a custom alternative — a separate section entirely

Each level of this exploration is a subsection: a branch forked from the parent section's branch, indexed under it.
```
section/http           ← parent section, documents the concept + indexes subsections
  section/http/parser-lib    ← subsection: use a public HTTP parser
  section/http/own-parser    ← subsection: implement your own HTTP parser

section/tcp            ← separate parent section
  section/tcp/os-api         ← subsection: use OS-provided TCP API
  section/tcp/own-impl       ← subsection: implement your own TCP stack

section/custom-protocol      ← fully custom invention, its own top-level section
```

The parent section acts as a documentation hub: it describes the concept, explains the exploration pattern,
and indexes its subsections. It may or may not contain runnable code itself.

Subsections follow the same rules as sections — they are independent branches, versioned with semver,
and tagged stable before being used as an origin.

The distinction between a subsection (variant of an existing protocol/concept) and a new section (custom invention)
is intentional: subsections deepen understanding of something that already exists; new sections introduce something novel.

### Versioning
Sections are tagged using [semver](https://semver.org/):

| Tag     | Meaning                                               |
|---------|-------------------------------------------------------|
| `v0.x`  | Unstable - do not use as an origin to another section |
| `v1.0+` | Stable - safe to use as an origin                     |

A tag is only considered **stable** when the section's public interface is intentionally defined and unlikely to change.
Stable tags are the contract.

### Interface Contract
Each section defines its public interface explicitly (e.g. in an `interface.md` or equivalent typed file).
This is reviewed before tagging stable. A change to the interface after a stable tag requires a **major version bump**.

---

## Origin Sections
Sections can be built on top of other sections.
This is means a section uses a stable tagged version of another section as its **starting point**.

```mermaid
stateDiagram-v2
    direction BT

    state "section/a@v1.0" as section_a
    state "section/b@v1.0" as section_b
    state "section/c@v1.2" as section_c
    state "section/d@v2.4" as section_d

    section_c --> section_a
    section_b --> section_a
    section_d --> section_c

    classDef highlight fill:#223760, stroke:#223760, color:#D3D7DF

    class section_a highlight
    class section_b highlight
    class section_c highlight
    class section_d highlight
```

This relationship is called an **origin**, not a dependency. It describes lineage, not a runtime requirement.

### Rules
- A section may only use a **stable tag** (`v1.0+`) as its origin
- The section with different origins across other versions will have documentation about the differences.
- If an origin section's interface changes after a major bump due to a critical bug,
dependent sections must be updated manually and re-documented

### Why Not `main`?
Because sections build on specific tagged versions of other sections -
not on whatever is currently on a branch - `main` cannot contain all of them simultaneously without conflict.
Each section's branch is the source of truth for that section.

---

## Documentation
Documentation is the primary deliverable of every section. <br>
If a section exists in two variants (e.g. built on different origin sections), the differences between those variants are documented explicitly.

---

## Lifecycle of a Section
```
1. Branch off from origin section at a stable tag (or from scratch)
2. Implement and document the concept
3. Define the public interface explicitly
4. Tag v0.x during development
5. Review interface → tag v1.0 when stable
6. Reference from main's index
```
