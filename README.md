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

The tree is derived from one upstream commit (`PIN`). To take a newer upstream (for example
after the compiler-bridge rows are closed there):

```sh
echo <commit> > PIN
python3 tools/refresh.py            # re-extract upstream/ at the pin
python3 tools/registry.py           # rows.jsonl: new/changed rows (bridge rows become stock)
python3 tools/verify.py --baseline  # byte-exact verdict per row (resumable; only new rows compile)
python3 tools/census.py
for t in t1_boiler t4_fields t3_epilogue t2_pins t6_pin_notes; do python3 tools/sweep.py $t --workers 6; done
python3 tools/complete_tree.py && python3 tools/levels.py && python3 tools/status.py
```

Rows whose upstream text changed are re-derived (the sweep journals key on the input hash);
unchanged rows are skipped. `refine/` bodies are re-verified against the new pin and any that
no longer match are reported, never silently kept.
