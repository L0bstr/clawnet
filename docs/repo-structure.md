## 📌 Repo structure

### Folders

`core/` where every section is implemented. `core` builds into a lib.<br>
`app` where the **server** and the **client** source code is.
These use the `core` lib.

### Branching

The project implements and documents sections. <br>
*"The documentation is organized into **sections**, each covering a specific concept or layer of abstraction."*

Ech section can evolve independently on its own branch into versions.

> until this the repo is pretty clear

### Goal

> optional but not sure its possible: <br>
> The main branch contains every sections latest version with its documentation.
> It might be enough to just contain the documentation and a link to the latest version where he can exame the code

### Ideas
Sections have thier own branches. A version of a section is its own branch inside the section branch.

- A version is stored inside `core/` as "section1/v1"
- A version is stored inside `core/` as "section1-v1/"

### Optimal result

The reader reads the main README. <br>
He reads about a section which explains the latest version implemented in the repo. <br>
The section could also display older version. <br>
The section also tells about sections that they built on with thier exact version as dependecy. <br>

## My problems

The main problem ins't that this model won't work. But that I don't have that much experience to follow the rules for this model.
> without the other sections.

A section can have another section as dependency. <br>
For exmaple: `section/http_support-v2` depends on `section/tcp-v3`
