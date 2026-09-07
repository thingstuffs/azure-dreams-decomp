# azure-clean

Readable, byte-exact C for Azure Dreams (PlayStation, SLUS-006.14), derived from a
byte-matching decompilation of the game (the "upstream" tree, not published yet).
Every function here still compiles to the retail bytes; the work is to make the C human.

Upstream pin: see `PIN` (the upstream commit the tree is derived from). This tree is a
**replay**: `upstream@PIN → machine transforms → hand refinements`, so it is refreshed by
bumping the pin and re-running, never by hand-merging.

## Layout

| path | what |
|---|---|
| `raw/<container>/` | the pinned upstream sources, untouched: every matched function as it is upstream (`slus`, `main`, `town`, `dungeon`, `ovmovie`); `raw/include/` its headers |
| `src/<container>/` | the current best version of **every** function: transformed where the machine layers have reached it, otherwise identical to `raw/`. `INDEX.md` per container lists file, function, bytes, compiler cell and cleanliness level |
| `refine/<container>/` | hand/agent-refined bodies (level 3+) that supersede `src/` for that function |
| `include/` | headers the clean tree compiles against (`common.h` from upstream, `m2c_compat.h` for the hoisted m2c macros) |
| `ledger/` | machine-readable truth: `rows.jsonl` (registry), `baseline.jsonl` (byte-exact verdict per row at the pin), `census.jsonl`, `levels.jsonl`, `sweeps/*.jsonl` (every transform verdict), `pins.jsonl` (pin census), `agents/` (bake-off and campaign journals), `struct_census.json` |
| `tools/` | refresh, registry, verify, census, pin_census, xform plugins, sweep, levels, status, agent_task, struct_census |
| `docs/` | `PLAN.md` (strategy and decisions), `REPORT_20260907.md` (day-one results), `PIN_CENSUS.md`, `STRUCT_CENSUS.md`, `BAKEOFF.md` |
| `STATUS.md` | generated: bytes per cleanliness level, shape census before/after |

## Cleanliness levels

| level | meaning |
|---|---|
| L0 | verified byte-exact at the pin through stock compilers |
| L1 | no m2c boilerplate, dead pins erased, no blocking fidelity site |
| L2 | no raw offset access (`M2C_FIELD` / `FIELD`): typed structs with explicit `unk_XX` members and padding |
| L3 | locals named, one-line summary; a `refine/` body exists |
| L4 | in a module with a shared header |
| L5 | pin-free, or every remaining pin documented (`/* MATCH pin: ... */` states the measured reason) |

## Verifying

`tools/verify.py <container>/<func> <file.c>` compiles a candidate through the pinned stock
toolchain of the upstream checkout and compares it with the retail bytes (overlays) or the
pinned object (SLUS). Transforms are applied with `tools/sweep.py <transform>`; every row is
verified and journalled, mismatches are refused, nothing is guessed.

Requires the upstream checkout (toolchain, scorer, retail extracts): put its path in a
`.upstream` file at the repo root (gitignored) or in `AZURE_CLEAN_UPSTREAM`; see `tools/common.py`.

## Dashboard

`tools/dashboard_serve.sh` regenerates `dashboard/index.html` every minute from the ledger and
journals and serves it on port 8002: levels by bytes and by container, what is running, the
agent campaign, the container gate verdicts, remaining work and recent commits. `ovmovie` is
parked (movie playback exists elsewhere) and listed without being counted.

## Syncing with upstream

The tree is derived from one upstream commit (`PIN`). To take a newer upstream:

```sh
python3 tools/pin_bump.py <commit> [--workers 6]        # ~35 min end to end
```

Pause the Layer-2 agent campaign first (it writes `refine/`; the script warns if one is running in
the tree) and relaunch it afterwards. The script runs, in order: `refresh` (mirror at the new pin),
`import` (the upstream files this repo carries copies of — `config/overlays/*`, the symbol lists,
`tools/configure.py`, the pinned headers — re-copied with the schema rename; every changed file is
listed), `slus` (`build_slus/` view root, `splat split`, `configure.py` at the pin: the pinned
`build.ninja` is **derived from the pinned `configure.py`**, never copied from the live tree),
`registry` (diff against the previous registry: text changed, config/dial changed, stock flips),
`stale` (those rows: `raw/` refreshed, `src/` reset to the new raw text so the sweeps re-derive
them, `refine/` bodies set aside, the baseline cleared for a full rebuild — the toolchain is the
live one, so an unchanged row can still change bytes), `baseline`, `sweeps` (census, T1/T4/T2/T6,
complete_tree, levels), `refine` (set-aside bodies re-verified at the new pin: exact ones restored,
the rest journalled in `ledger/agents/pin_bump_refine.jsonl` and left under `work/pin_bump/<pin>/`
— never kept silently; the campaign serves those rows again), `status`, `gate_slus` (ninja SHA-1
gate) and `gate_ovl` (fresh `ledger/gate.jsonl`, every window). `--from STEP` resumes,
`--stop-after STEP` stops early. The report is `ledger/pin_bumps/<pin>.json`.

Two gate rules the tools apply: a row the per-row scorer cannot measure (a `.text` data prefix
under the true-name symbol, a data row written as C) is proven through its window instead
(`tools/verify.py::gate_fallback`, recorded with `proof: window-gate`); and a synthetic-base
seed window whose bytes are re-gated by a `_truebase_` twin at the proven base is skipped by
`gate_all.py` unless a registered row still names it as its window (9 such seeds at `82f20568`).

A row is **stock** when its cc1 is a stock cell, its gcc flags are ordinary (no
`-fretail-`/`-fsn-`/`-fdriver-`), and its maspsx options carry no per-function `--retail-*` dial —
the rule upstream's `live_truth` census applies. Both config label dialects (`2.8.1 -G0 …` and
`2.8.1+-G0 …`) parse identically (`tools/common.py::parse_cfg`).

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
