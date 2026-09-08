# azure-dreams-decomp

Readable, byte-exact C for Azure Dreams (PlayStation, SLUS-006.14). Every function here still
compiles to the retail bytes; the work is to make the C human. (The working checkout is called
`azure-clean` locally; tool docstrings and the dashboard use that name.)

The tree started as a replay of a byte-matching decompilation at one commit (`PIN`): its sources
are frozen in `raw/`, and everything else — machine transforms, hand refinements, the row
database, the gates, the toolchain — lives here. There is no upstream any more (the swap-over is
recorded in `docs/SWAPOVER.md`).

## Layout

| path | what |
|---|---|
| `raw/<container>/` | the pinned sources, frozen: every matched function as it was at `PIN` (`slus`, `main`, `town`, `dungeon`, `ovmovie`); `raw/include/` the pinned headers. Never edited |
| `src/<container>/` | the current best version of **every** function: transformed where the machine layers have reached it, otherwise identical to `raw/` |
| `refine/<container>/` | hand/agent-refined bodies (level 3+) that supersede `src/` for that function |
| `include/` | headers the clean tree compiles against (`common.h`, `m2c_compat.h` for the hoisted m2c macros, `records/` shared record layouts, `script_symbols.h` the developers' script constants, generated) |
| `ledger/` | machine-readable truth: `splits/` (the row database: every container's split table, the SLUS recipe), `rows.jsonl` (registry of matched rows), `baseline.jsonl` (byte-exact verdict per row at the pin), `reverify.jsonl`, `gate.jsonl` / `gate_slus.jsonl` / `containers.jsonl` (gate verdicts), `census.jsonl`, `levels.jsonl`, `sweeps/*.jsonl` (every transform verdict), `pins.jsonl`, `agents/` (campaign journals and bodies), `pin_bumps/`, `evidence/` (naming and module evidence per row: assertion sites, developer identifiers, randomizer map, pointer tables, prior notes) |
| `config/` | the SLUS split (`slus_006.14.yaml`, symbols, SHA-1), the 2,181 overlay window YAMLs and symbol/as-flags/rowbase files (`overlays/`), noreturn/sibcall lists, `func_sizes.json` |
| `tools/` | `setup.sh` + `toolchain.lock.json` (provisioning), `disc.py`, `row_db.py`, `registry.py`, `verify.py`, `sweep.py` + `xform/`, `census.py`, `levels.py`, `status.py`, `agent_task.py`, `struct_census.py`, `evidence.py`; `build/` (SLUS build, window gate runner, container check), `gate/` (the window gate and the per-row scorer), `maspsx/` (vendored assembler front end), `patches/` |
| `docs/` | `PLAN.md` (strategy and levels), `SWAPOVER.md` (how the tree came to own everything), `REPORT_20260907.md`, `PIN_CENSUS.md`, `STRUCT_CENSUS.md`, `BAKEOFF.md`, `HANDOVER.md`, `EVIDENCE.md` (index of the naming evidence and how each level uses it), `SYMBOLS.md` (the recovered names in plain language), `evidence/` (the assertion catalogue and randomizer findings verbatim) |
| `STATUS.md` | generated: bytes per cleanliness level, shape census before/after |

Not committed: the disc image (`bin/`), its extract (`work/disc/`), the toolchain (`toolchain/`),
the venv, `baserom/`, and the build roots (`build_slus/`, `build_ovl/`).

## Cleanliness levels

| level | meaning |
|---|---|
| L0 | verified byte-exact at the pin through stock compilers |
| L1 | no m2c boilerplate, dead pins erased, no blocking fidelity site |
| L2 | no raw offset access (`M2C_FIELD` / `FIELD`): typed structs with explicit `unk_XX` members and padding |
| L3 | locals named, one-line summary; a `refine/` body exists |
| L4 | in a module with a shared header |
| L5 | strict: no `ASM_*` pin or marker, no noreturn tail-call spelling, no fidelity site of any audit class, no computed-goto table, no inline asm. A pin that survives is annotated `/* UNRESOLVED C shape (pin): removing it <measured effect>; … */` — a debt record, never a justification |

## Provisioning

```sh
cp "/path/to/Azure Dreams.bin" "/path/to/Azure Dreams.cue" bin/   # your own disc; SHA-1 in tools/toolchain.lock.json
tools/setup.sh                                                    # venv, the seven stock cc1 drops, maspsx link, mkpsxiso, extract
tools/setup.sh --check                                            # verify only
```

`tools/toolchain.lock.json` pins every external piece with a hash: the disc and its five
containers, the decompals old-gcc drops (`toolchain/compilers/` holds those seven and nothing
else — the guard that no compiler bridge can be reintroduced), the mkpsxiso commit and patch, the
splat version. The assembler front end is vendored (`tools/maspsx`, MIT): function-blind, no name
tables, no per-function options. `tools/disc.py extract|rebuild|check` is the disc round trip.

## Verifying

Three proofs, from cheapest to the one of record:

```sh
python3 tools/verify.py <container>/<func> <file.c>     # one row: the per-row scorer (overlays) or object identity (SLUS)
tools/build/build_slus.sh [--fresh]                     # the SLUS gate: split, configure, build, SHA-1 (ledger/gate_slus.jsonl)
bash tools/build/mk_ovl_root.sh && python3 tools/build/gate_all.py [--retry]   # every overlay window (ledger/gate.jsonl)
python3 tools/build/container_check.py --rebuild-disc   # whole containers from the gated windows + SLUS, then the disc (ledger/containers.jsonl)
```

The window gate's compile command is the only compile command; the per-row scorer is a dev
tool, and a row it cannot prove is gated through its window (`verify.py::gate_fallback`).
Transforms are applied with `tools/sweep.py <transform>`; every row is verified and journalled,
mismatches are refused, nothing is guessed. `tools/reverify.py` re-proves every transformed row.

## Dashboard

`tools/dashboard_serve.sh` regenerates `dashboard/index.html` every minute from the ledger and
journals and serves it on port 8002: levels by bytes and by container, what is running, the
agent campaign, the gate verdicts, remaining work and recent commits. `ovmovie` is parked (movie
playback exists elsewhere) and listed without being counted.

## Row database

`ledger/splits/<container>.jsonl` is the split table of each container: every row the gate lays
out (matched or not) with its extent, verdict, compiler config and source; `ledger/splits/slus.jsonl`
the per-TU recipe of the executable. `tools/registry.py` derives `ledger/rows.jsonl` (the
registry of matched rows) from them and assigns every row its gate window: the gate compiles
every matched row whose extent lies inside a window's file range, so a row is never "windowless"
(`gate_config_derived` marks rows whose split record did not name one). `tools/row_db.py check`
verifies the tables; `tools/row_db.py export <root>` writes them in the gate's input format
(the build-root scripts do this).

A row is **stock** when its cc1 is a stock cell, its gcc flags are ordinary (no
`-fretail-`/`-fsn-`/`-fdriver-`), and its maspsx options carry no per-function `--retail-*` dial.
Both config label dialects (`2.8.1 -G0 …` and `2.8.1+-G0 …`) parse identically
(`tools/common.py::parse_cfg`). Every registered row is stock at the pin.

## History: the pin

`PIN` names the commit of the byte-matching tree this one was derived from; `tools/pin_bump.py`
was the sync recipe (refresh a mirror, re-import, re-derive, re-verify, re-gate) and stays as a
record. It needs a checkout of that tree named in `.upstream`; nothing else does.

## Licence

Everything original in this repository (the tools, the ledger, the documentation, the transformed
and refined C) is released into the public domain under [The Unlicense](LICENSE): use it, copy it,
sell it, claim it, no attribution required. Two things are not ours to dedicate:

- `tools/maspsx/` is vendored from [maspsx](https://github.com/mkst/maspsx) under its MIT licence
  (`tools/maspsx/LICENSE`).
- The reconstructed sources describe *Azure Dreams*, which is © Konami. They are the product of
  decompiling the retail binaries for research and preservation; no rights in the game are claimed,
  and the repository contains no game data.

## Credits

- **Azure Dreams De-Randomizer** by ProGrammar-R (https://github.com/ProGrammar-R/ProGrammar-R.github.io, MPL-2.0).
  Its address and table map of the retail binary (`initialStatsTable`, `trapTable`,
  `itemCategoryTable`, record layouts, the RNG constants) anchored many of the symbol names and
  struct layouts here. Only those facts were used; none of its code is included.
- **sotn-decomp** (https://github.com/Xeeynamo/sotn-decomp): naming vocabulary for common
  PlayStation game structures, borrowed only where the Azure Dreams evidence supports the same concept.
- Toolchain: **splat** (https://github.com/ethteck/splat), **m2c** (https://github.com/matt-kempster/m2c),
  **maspsx** (https://github.com/mkst/maspsx), **decompals old-gcc** builds of the Psy-Q-era GCC
  (https://github.com/decompals/old-gcc), **mkpsxiso** (https://github.com/Lameguy64/mkpsxiso),
  **spimdisasm**, GNU binutils.
- *Azure Dreams* is © Konami. This repository contains no game data; you must supply your own disc.
