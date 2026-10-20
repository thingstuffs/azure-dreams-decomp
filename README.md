# azure-dreams-decomp

Readable C source for *Azure Dreams* (PlayStation, NTSC-U, `SLUS-006.14`) that compiles,
function by function, to the same bytes as the retail game.

*Azure Dreams* is (c) Konami. This is an independent fan research and preservation project, not
affiliated with or endorsed by Konami. **No game data is included**: you need your own copy of the
disc to build or verify anything. See [NOTICE](NOTICE) and [Legal](#legal).

## Status

Numbers are from [STATUS.md](STATUS.md) (see its "At a glance" section), which is generated from the
ledger (snapshot of 2026-10-17; rerun `python3 tools/status.py` for today's).

- **Byte-exact coverage.** 17,474 functions and data rows, 6,271,564 bytes, in five containers
  (`slus` main executable, `main`, `town`, `dungeon`, `ovmovie` overlays), all verified
  byte-identical to retail.
  Rows are built by the stock compiler cells (gcc 2.7.2-era builds); the few rows that need a
  non-default compiler flag are tracked in STATUS.md.
- **Share of the code in C.** 76.1% of the overlay code is C; 95.0% counting byte-identical copies
  of C that are proven elsewhere on the disc (they become C by reference as the tree is
  de-duplicated). The main executable is accounted separately in STATUS.md.
- **Pins: 0.** A "pin" is an `ASM_*` marker, fence or other scaffolding that was needed to coax
  the compiler into the retail bytes. All 25,918 original sites have been removed, and no raw inline-asm
  statements or hand-written asm in function bodies remain.

The aim is not just matching bytes but making the C human: typed structs instead of raw offsets,
named locals and functions, no compiler-driven contortions.

## Quick start

You need Linux, `python3` (3.x with PyYAML), `git`, `curl`, `cmake`, `ninja` and
`mipsel-linux-gnu-as` (binutils). `tools/setup.sh` checks for them and says which are missing.

```sh
git clone <this repository> azure-dreams-decomp && cd azure-dreams-decomp
mkdir -p bin && cp "/path/to/Azure Dreams.bin" "/path/to/Azure Dreams.cue" bin/   # your own disc
tools/setup.sh            # venv, stock compilers (hash-checked downloads), assembler front end, mkpsxiso, disc extract
tools/setup.sh --check    # verify the set-up only
```

The disc image's SHA-1 and every downloaded piece are pinned in `tools/toolchain.lock.json`;
set-up refuses anything that does not match.

Optional: the overlay-module windows (677 of 3,207 window configs) also check against Sony's genuine
ASPSX 2.79 assembler from the Psy-Q 4.4 SDK, which cannot be redistributed. If you own the SDK,
`tools/setup.sh --psyq /path/to/psyq` copies and hash-checks it. Without it, the SLUS executable and every
other window still build and verify. See [docs/TOOLCHAIN_PSYQ.md](docs/TOOLCHAIN_PSYQ.md).

Then prove a function matches:

```sh
python3 tools/verify.py town/func_8008D54C src/town/func_8008D54C.c   # one function (per-row scorer)
tools/build/build_slus.sh                                              # whole SLUS executable, SHA-1 checked
bash tools/build/mk_ovl_root.sh && python3 tools/build/gate_all.py     # every overlay window
python3 tools/build/container_check.py --rebuild-disc                  # containers, then the disc itself
```

A full run takes a long time (hours of CPU); the per-function scorer takes seconds. The window gate's
compile command is the only compile command of record; the scorer is a development shortcut.

## Layout

| path | what |
|---|---|
| `src/<container>/` | the current C source, one function (or data object) per file, named by its retail address (`func_8008D54C.c`) or its recovered name. The only tree the gates compile |
| `include/` | headers: shared types (`include/shared/`, `include/records/`), module headers, compat macros |
| `raw/` | the frozen starting point: the byte-matching sources as imported at `PIN`. Never edited; kept as byte provenance |
| `config/` | the SLUS split and symbols, 2,000+ overlay window definitions, compiler/assembler flags per region, `names.tsv` (renames), noreturn lists |
| `ledger/` | machine-readable project state: the row database (`splits/`), `rows.jsonl`, `baseline.jsonl`, gate verdicts, promotions, levels, names |
| `tools/` | provisioning (`setup.sh`, `toolchain.lock.json`), the gates and build scripts (`build/`, `gate/`), the vendored assembler front end (`maspsx/`), analysis and transform tools, tests (`tools/tests/`) |
| `docs/` | reference documentation; start at [docs/README.md](docs/README.md). `docs/evidence/` holds the research notes behind individual names and decisions; `docs/history/` is the project's working journal |
| `STATUS.md` | generated progress report |
| `LICENSE`, `NOTICE` | licence scope and legal notice |

Not committed: the disc image (`bin/`), its extract (`work/disc/`), the toolchain (`toolchain/`), the
virtualenv, and the build roots (`build_slus/`, `build_ovl/`). They are created by `tools/setup.sh`.

## Cleanliness levels

| level | meaning |
|---|---|
| L0 | verified byte-exact against retail through the stock compilers |
| L1 | no m2c boilerplate, no scaffolding left to erase |
| L2 | no raw offset access: typed structs with explicit `unk_XX` members and padding |
| L3 | locals named, one-line summary written, accepted refined body landed |
| L4 | in a module with a shared header; zero pins; no tail-jump dependency |
| L5 | strict: no fidelity site of any audit class, no computed-goto table, no inline asm, no `NON_MATCHING` guard |

Definitions are in [docs/PLAN.md](docs/PLAN.md) and `tools/levels.py`.

## How it is proven

Every function is compiled with the original compiler generation (gcc 2.7.2-era Psy-Q/Cygnus
builds) and Sony-compatible assembler behaviour (`tools/maspsx`), then compared with the bytes read
from your disc. Mismatches are refused; nothing is accepted on a guess. Transforms and edits go
through `tools/promote.py` / the window gate, which re-verify before anything lands, and
`tools/reverify.py` re-proves every row. [CONTRIBUTING.md](CONTRIBUTING.md) describes the workflow.

## Row database

`ledger/splits/<container>.jsonl` is the split table of each container: every row the gate lays out
with its extent, verdict, compiler config and source. `tools/registry.py` derives `ledger/rows.jsonl`
and assigns each row its gate window. `tools/row_db.py check` verifies the tables.

## Contributing

Read [CONTRIBUTING.md](CONTRIBUTING.md). In short: a change is good if the byte-exact check still
passes and the C is closer to what a person would write. Names and types are tracked in
`config/names.tsv` and `ledger/names.jsonl`.

## Legal

- *Azure Dreams* and its code, data and trademarks are (c) Konami. This project is not affiliated
  with or endorsed by Konami, and grants no rights in Konami's material.
- No game data is included. You must supply your own copy of the game. The reconstructed C
  describes the behaviour of Konami's program, and a few files express small tables as C; those
  tables remain Konami's.
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
