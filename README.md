# azure-dreams-decomp

Readable C source for *Azure Dreams* (PlayStation, NTSC-U, `SLUS-006.14`) that compiles,
function by function, to the same bytes as the retail game.

*Azure Dreams* is (c) Konami. This is an independent fan research and preservation project, not
affiliated with or endorsed by Konami. **No disc images or extracted binaries are included**:
you need your own copy of the disc to build or compare against retail. See
[NOTICE](NOTICE) and [Legal](#legal).

## Status

Numbers are from [STATUS.md](STATUS.md) (see its "At a glance" section), which is generated from the
ledger (snapshot of 2026-10-20; rerun `python3 tools/status.py` for today's).

- **Byte-exact coverage.** 21,432 functions and data rows, 8,028,304 bytes, in five containers
  (`slus` main executable, `main`, `town`, `dungeon`, `ovmovie` overlays). Every overlay window and
  the whole executable rebuild byte-identical to retail; 21,392 rows (8,018,768 bytes) also carry a
  per-row byte-identical record, and the remaining 40 are proven by the window rebuild.
  Rows are built by the stock compiler cells (gcc 2.7.2-era builds); the few rows that need a
  non-default compiler flag are tracked in STATUS.md.
- **Share of the code in C.** 99.0% of the overlay code is C; 99.5% counting byte-identical copies
  of C that are proven elsewhere on the disc (they become C by reference as the tree is
  de-duplicated). The main executable is accounted separately in STATUS.md.
- **Readability.** L3 90.4%, L4 9.2%, L5 8.9% of bytes (levels below); 227 of 300 module
  certificates current.
- **Pins: 0.** A "pin" is an `ASM_*` marker, fence or other scaffolding that was needed to coax
  the compiler into the retail bytes. All 25,918 original sites have been removed.

The aim is not just matching bytes but making the C human: typed structs instead of raw offsets,
named locals and functions, no compiler-driven contortions.

## Quick start

Clone this repository using its GitHub **Code** button and run the following
commands from the clone's root. You need Linux, Python 3.10 or later with PyYAML
and venv support, `git`, `curl`, `cmake`, `ninja`, a host C/C++ build toolchain and
`mipsel-linux-gnu-as` (binutils). The host packages are listed in
`tools/toolchain.lock.json`; `tools/setup.sh` reports missing prerequisites.

**Requires your own NTSC-U disc image and cue sheet.** Replace the example paths
with your files; the destination filenames below are the setup defaults.

```sh
mkdir -p bin
cp "/path/to/Azure Dreams.bin" "/path/to/Azure Dreams.cue" bin/
bash tools/setup.sh            # venv, stock compilers, assembler front end, mkpsxiso, disc extraction
bash tools/setup.sh --check    # report setup gaps
```

The lock records the disc SHA-1, compiler hashes, mkpsxiso commit and Python
dependency versions. Setup checks those identities; host packages are supplied
by your system.

Complete overlay proof also requires Sony's genuine ASPSX 2.79 assembler from
your own Psy-Q SDK. Setup copies and hash-checks the pinned file; the repository
does not supply it. SLUS and windows without native module placements can be
checked without that SDK. See [docs/TOOLCHAIN_PSYQ.md](docs/TOOLCHAIN_PSYQ.md)
for installation and scope.

Find the current source for a stable row ID. This lookup needs no disc:

```sh
python3 tools/source_layout.py path town/func_8008D54C
```

After setup, check that source. **Requires the extracted disc and provisioned
toolchain; requested module-window checks may also require Psy-Q.**

```sh
python3 tools/verify.py town/func_8008D54C src/town/scene/copy_words_backward_from_offset.c --gate
```

The verifier reports whether a window ran or whether registered address
evidence makes its scorer equivalent to the window check for that row. A
passing row score does not refresh every affected module certificate.

For the full build, run these in order. **Requires your disc, provisioned tools
and the pinned Psy-Q assembler/loader for module windows.**

```sh
bash tools/build/build_slus.sh -j 4
bash tools/build/mk_ovl_root.sh
python3 tools/build/gate_all.py --workers 4
python3 tools/build/container_check.py --rebuild-disc
```

A full run can take hours. The final container/disc check reports compiled C,
gated window bytes and retail fill separately; byte-identical output does not
mean every byte was compiled from C. See [the proof guide](docs/PLAN.md).

## Layout

| path | what |
|---|---|
| `src/` | editable C organized under `engine/`, `frontend/`, `town/`, `dungeon/` and `movie/`; a translation unit may contain several rows. Use [the source resolver](docs/SOURCE_LAYOUT.md) to find it |
| `include/` | headers: shared types (`include/shared/`, `include/records/`), module headers, compat macros |
| `config/` | split/symbol tables, overlay windows, compiler/assembler recipes, `names.tsv` aliases and frozen source hashes |
| `ledger/` | current row database, layout, baseline, proof and quality records; the public export omits the internal event history |
| `tools/` | setup, gates, build scripts, the vendored assembler front end (`maspsx/`) and analysis tools |
| `docs/` | reference documentation; start at [docs/README.md](docs/README.md). `docs/evidence/` records the reasoning behind names, types and decisions |
| `STATUS.md` | generated progress report |
| `LICENSE`, `NOTICE` | licence scope and legal notice |

Not committed: the disc image (`bin/`), its extract (`work/disc/`), the toolchain (`toolchain/`), the
virtualenv, and the build roots (`build_slus/`, `build_ovl/`). Setup provisions the
disc and tools; the build scripts create the build roots.

## Cleanliness levels

| level | meaning |
|---|---|
| L0 | recorded byte-exact baseline at the registered recipe |
| L1 | no decompiler boilerplate or blocking fidelity spelling |
| L2 | typed accesses replace raw field macros; unknown fields may remain |
| L3 | recorded refinement and an acceptable audit for each tail-jump dependency |
| L4 | current reviewed module placement, no pins or tail-jump dependencies, and no source-driven assembler imitation or contradictory compiler fingerprint |
| L5 | no blocking fidelity site, computed goto, inline assembly, `NON_MATCHING` guard or recorded compiler-model dependency |

Requirements accumulate. Full definitions and exceptions are in
[docs/PLAN.md](docs/PLAN.md) and `tools/levels.py`.

## How it is proven

Registered C is compiled with the recorded stock compiler recipe and
Sony-compatible assembler behaviour (`tools/maspsx`). The linked window or SLUS
image is compared against your disc. Native overlay modules additionally need
the genuine assembler comparison. Certificates bind source, headers, recipe,
ownership, tools and affected placements; changed inputs make old proof stale.
[CONTRIBUTING.md](CONTRIBUTING.md) describes how to check a change, and
[docs/PLAN.md](docs/PLAN.md) explains each proof's scope.

## Row database

`ledger/splits/<container>.jsonl` is the split table of each container: every row the gate lays out
with its extent, verdict, compiler config and source. `tools/registry.py` derives `ledger/rows.jsonl`
and assigns each row its gate window. `tools/row_db.py check` verifies the tables.

## Contributing

Read [CONTRIBUTING.md](CONTRIBUTING.md). In short: a change is good if the byte-exact check still
passes and the C is closer to what a person would write. `config/names.tsv`
tracks function/global aliases and evidence; shared types live under `include/`.

## Legal

- *Azure Dreams* and its code, data and trademarks are (c) Konami. This project is not affiliated
  with or endorsed by Konami, and grants no rights in Konami's material.
- No disc images or extracted binaries are included. You must supply your own
  copy of the game. The reconstructed C describes the behaviour of Konami's
  program, and a few files express small tables as C; those tables remain Konami's.
- The project's own original work (tools, build scripts, docs, recovered names and annotations, and
  the contributors' own expression in the C to the extent they hold rights) is released under
  [The Unlicense](LICENSE). Third-party parts keep their own licences: `tools/maspsx/` is MIT.
- Full statement and credits: [NOTICE](NOTICE). This is not legal advice.

## Credits

- **Azure Dreams De-Randomizer** by ProGrammar-R (MPL-2.0): address and table map of the retail
  binary that anchored many names and struct layouts. Only facts were used; none of its code.
- **sotn-decomp**: naming vocabulary for common PlayStation game structures.
- Toolchain: **splat**, **m2c**, **maspsx**, **decompals old-gcc** builds of the Psy-Q-era GCC,
  **mkpsxiso**, **spimdisasm**, GNU binutils.
