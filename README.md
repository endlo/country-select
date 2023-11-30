# country-select

A simple project to select countries from a dropdown using [Melange](https://github.com/melange-re/melange)
with [opam](https://opam.ocaml.org/).

## Quick Start

```shell
make init

# In separate terminals:
make watch
make serve
```

When running `make init`, you may encounter an error like this:

```
[ERROR] Could not determine which packages to install for this switch:
  * Missing dependency:
    - melange >= 1.0.0
    no matching version
```

It means `opam` doesn't have the latest packages definitions from the opam-repository. To address this, first run `opam update`, then rerun `make init`.

### React

React support is provided by
[`reason-react`](https://github.com/reasonml/reason-react/). The entry
point of the sample React app is [`src/ReactApp.re`](src/ReactApp.re).

## Commands

In opam / dune projects, our personal preference is to group commonly used commands in a Makefile. This is completely optional.

You can see all available commands by running `make help` or just `make`. Here
are a few of the most useful ones:

- `make init`: set up opam local switch and download OCaml, Melange and
JavaScript dependencies
- `make install`: install OCaml, Melange and JavaScript dependencies
- `make watch`: watch for the filesystem and have Melange rebuild on every
change
- `make serve`: serve the application with a local HTTP server

## JavaScript output

Melange compiles source files into JavaScript files. This means it can be used
for projects on any JavaScript platform - not just the browser.

The project includes a `melange.emit` stanza for a React app. This stanza tells
Dune to generate JavaScript files using Melange, and specifies in which folder
the JavaScript files should be placed, by leveraging the `target` field.

We can find the JavaScript files for the React app in `_build/default/src/output/*`.

To host this React app, `_build/default/src/output/src/ReactApp.js` can be passed as
entry to a bundler like Webpack:

```bash
webpack --mode production --entry ./_build/default/src/output/src/ReactApp.js
```
