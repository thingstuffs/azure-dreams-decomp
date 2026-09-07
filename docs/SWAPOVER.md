# Swap-over: making this repository the only tree

Owner's intent (2026-09-07): once the last compiler-bridge rows upstream are closed (10 left,
6,860 B, per the upstream census at the time of writing), this repository becomes the single
source of truth and the work is "moving through the levels". No more upstream/downstream.

Today this tree *borrows* from the upstream checkout for everything that proves bytes. After the
swap it has to own those pieces. This document is the inventory, the gaps, and the order of work.

## 1. What proving bytes needs, and where it lives today

| piece | upstream location | size | action at swap |
|---|---|---:|---|
| toolchain provisioning | `tools/setup.sh`: decompals old-gcc releases 2.6.3 / 2.7.2 / 2.7.2-cdk / 2.8.0 / 2.8.1 / 2.91.66 / 2.95.2, mipsel binutils (apt), maspsx + one required patch, mkpsxiso + one patch, splat64, m2c | script + 2 patches | import as `tools/setup.sh` + `tools/patches/`; pin release URLs and hashes in a lock file |
| disc extraction | `work/overlay_recon/extract_bins.py` (**untracked** upstream), `tools/psx_disc.py`; disc supplied by the user, never committed | 2 scripts | import; document the Redump SHA-1 and the extract layout (`SLUS_006.14`, `MAIN_MAIN.BIN`, `TOWN_TOWN.BIN`, `DUNGEON_DUNGEON.BIN`, `OVMOVIE.BIN`) |
| SLUS build + gate | `tools/configure.py` → `build.ninja` (per-TU compiler cell and flags) → `tools/cc.sh` / `as.sh` / `ccproc.py` → link → objcopy → `sha1sum -c config/slus_006.14.sha1`; needs `config/slus_006.14.yaml`, `.symbols.txt`, splat-generated `config/generated/*` (untracked) | ~10 files + splat run | import; point the source glob at `src/slus/*.c`; keep the whole-binary SHA-1 as the gate |
| overlay gates | `tools/overlay_local_gate.py` + 2,181 window YAMLs in `config/overlays/` (dungeon 1,465, town 711, main 4, ovmovie 1) + `*.symbols.txt`, `*.rowbase.jsonl`, `*.as_flags.jsonl`, `*.selfspan_labels.json`; windows compile matched C, incbin everything else from the extracted container, link, byte-compare | 2,190 config files + gate tool and its imports | import; rewrite window `c_path`s to `src/<container>/<func>.c`; run every window as the container gate |
| row database | `overlays/<ovl>/overlay_first_pass_results.json` (row identity, foff, size, config, true name, gate window) | 5 files | already mirrored into `ledger/rows.jsonl`; make the ledger primary and drop the mirror step |
| per-function scorer (dev tool) | `tools/aligned_score.py` and its closure: `match.py`, `az_target.py`, `residue_class.py`, `overlay_as_flags.py`, `rowbase.py`, `live_truth.py`, `overlay_evidence.py`, `oracle_scoring.py`, `work/g3/overlay_func_compare.py` | ~10 modules | import as `tools/score/`; keep for transform verification (the residue classes are what the pin census uses) |
| assembler name tables | upstream maspsx still carries 627 `func_`-keyed entries; the name-blind rescore showed only 7 rows depend on them | patch | adopt the neutralised maspsx (or upstream's Phase-2 removal); fix or document the 7 rows |
| headers | `include/` (8 files) | tiny | already here |
| native port | `port/` (131 files) | optional | later; not needed to prove bytes |

Not needed: agent-campaign payloads (`config/knowledge*`, `config/function_dossiers`,
`work/wave_*`, `work/dungeon_p1`, dossiers, learnings), the 132 tool tests that cover them,
and the campaign docs. The build closure is roughly 30 tools, 2,200 config files and 2 patches.

### Lesson from the first gate runs (2026-09-07)

The per-row verifier passed a header via `C_INCLUDE_PATH`; GCC then treats it as a *system*
header and tolerates typedef redefinitions that the window gate (which uses `-I`, a user
directory) rejects. Seven files carried a stray `typedef s8 M2C_UNK8;` next to the hoisted
compat header and were "exact" per the verifier but broke the gate. The verifier now passes
the include root as `-I`, the seven files are fixed, and every transformed row was re-verified
under the strict rule: 4,628 of 4,643 exact. The 15 others fail identically from the raw pinned
text (six name-table SLUS units, six dungeon page bodies and one page file whose bytes moved
when upstream's assembler changed on 2026-09-07) and resolve at the pin bump. Rule for the swap: **the gate's compile command is the only compile
command**; verification tools must call it, not imitate it.

### Second lesson: the per-row scorer is blind to relocation targets (2026-09-07)

The container-wide gate run (2,181 windows, 10 minutes, 2,136 byte-identical) caught one window
the per-row scorer had passed: a row where T3a had replaced jumps to `func_800257F0`, a
*resident-executable* shared tail, with `return`. The scorer compares relocation-normalised
words, so a `j` to a different target looks identical; the linked window does not. Every one of
the 400 rows T3a touched jumps to a tail outside its own extent, so T3a is retired (it now
refuses any target outside the row) and those rows were re-derived without it. Rule: **any
transform that can move a jump or call target is proven by the window gate, never by the
per-row scorer alone.** The remaining mismatching windows and the 38 error windows are upstream
drift (page bodies whose bytes changed with the assembler; retired bridge compiler cells) and
fail identically from `raw/`.

### Container-wide gate result (2026-09-07, `ledger/gate.jsonl`)

All 2181 windows gated from this tree with every transform applied: **2139 byte-identical**
(TOWN 711/711, MAIN 3/4, OVMOVIE 1/1, DUNGEON all but the drift set). Not green: 35 windows
whose rows were landed through bridge compiler cells upstream retired today (cannot be rebuilt
from the pin any more), 4 dungeon page windows and 1 MAIN dial row that fail identically from
`raw/` (assembler change upstream today), and the engine mirror (gated from the pinned engine
copies until its roster is folded into the dungeon rows). Every one of those resolves at the
pin bump; none is attributable to a transform.

## 2. Gaps found in the inventory

1. **Overlay containers are proven per window, not linked whole.** SLUS has a whole-binary
   SHA-1 gate; MAIN/TOWN/DUNGEON/OVMOVIE have window byte-compares with incbin fill. That is a
   real proof for every matched row but not a whole-container rebuild. A whole-container link
   (every fragment either C or checked-in asm/incbin, then SHA-1) is the honest end state and
   is future work, not a swap blocker.
2. **17 rows have no gate window** (9 ovmovie, 8 main). At the swap every row must sit in a
   window or in the whole-container link; carve or fold them first.
3. **Disc rebuild is not a tracked script.** `work/roundtrip/` holds a mkpsxiso project and a
   rebuilt image, but no tracked tool produces them. Import or rewrite (`mkpsxiso` project
   from the extract layout) so "byte-identical disc" is a command.
4. **`asm/psyq` and `asm/nonmatchings` are untracked upstream** yet windows can stage
   checked-in assembly twins from there. Confirm which windows need any, and track those files.
5. **The 4 stale-name dungeon rows** are already fixed upstream; the verifier here tolerates
   them either way.

## 3. Order of work

**Now (does not wait for the bridge):**

- import the build closure into `tools/build/` and `config/` here, unchanged in behaviour,
  with `src/slus/` and `src/<container>/` as the source roots; keep `.upstream` only for the
  extracted containers until extraction runs here;
- run the full gate from this tree at the current pin: SLUS SHA-1 plus every overlay window;
  record the result in `ledger/gate.jsonl` (window → sha of inputs → pass/fail);
- carve the 17 windowless rows; import the disc round-trip.

**Done 2026-09-07 08:30 UTC — SLUS build imported.** `tools/build/` holds the unmodified
upstream build scripts (configure, cc, as, ccproc, asproc, the splat extension);
`tools/build/mk_slus_root.sh` creates `build_slus/`, a view root where `src/` is `src/slus`,
`tools/` is `tools/build`, and the toolchain, venv and baserom are the upstream checkout's until
provisioned here. `splat split → configure.py → ninja` runs from this tree (1,131 objects).
The SHA-1 gate currently fails on 13 translation units: all are name-table-dependent main-EXE
rows that upstream is re-landing at stock today (its assembler changed at 08:05), i.e. pin-era
sources meeting today's assembler. Every other object is identical to the pinned baseline.
Expected green at the pin bump.

**Done 2026-09-07 09:00 UTC — overlay gate imported.** `tools/gate/` holds the unmodified
upstream window gate and its 15-module closure; `config/overlays/` the 2,190 window and
symbol files; `tools/build/mk_ovl_root.sh` creates `build_ovl/`, a view root where
`overlays/<ovl>/first_pass_matched` is `src/<ovl>`. Proven from this tree with every
transform applied: the 4-row dungeon micro window (8,860 B), the 391-row MAIN boot window
(86,016 B) and the 1,414-segment TOWN scene window (335,872 B, the largest window in the game)
rebuild byte-identical. The platform-library assembly twins the windows stage are
generated by the SLUS split (`build_slus/asm/psyq`), not hand-written, so nothing is lost there.

**At the swap (bridge at zero upstream):**

1. pin the final upstream commit; replay (refresh, registry, baseline, census, sweeps, levels);
2. full gate from this tree; every row green;
3. `raw/` frozen as the last upstream snapshot; `upstream/` mirror step retired;
   `ledger/rows.jsonl` becomes the row database;
4. README: this is the tree; upstream archived.

**After:** levels only. L3 through the agent campaign, L4 modules and names, L5 pin
documentation, with the whole-container link as the standing gate.


## Pin bump to `82f20568` (2026-09-07) — upstream's bridge lane at zero

Upstream closed its last bridge row on 2026-09-07 (`da6217da`: main-EXE `func_8000F774` at stock
2.7.2-cdk-G0), recorded the exit (`1d8ced01`: 192/192 keyed landings closed, census 0/0) and
deleted the last maspsx dial and its guard patches (`787552bc`, `82f20568`). This tree took
`82f20568` with `tools/pin_bump.py` after a rehearsal in a throwaway worktree at `1d8ced01`.
The README recipe had **five gaps**; the rehearsal found them, the script closes them:

1. **Changed rows were never re-derived.** The sweeps take the current `src/` text as input and
   key their journals on its hash, and `verify.py --baseline` skips any row id already
   journalled, so a row whose upstream text changed would have kept its old derived file and
   its stale baseline record (for SLUS rows the cached pinned *object* — the reference every
   later verify compares against — would have been wrong from then on). The bump diffs the
   registry (text, config, dial, stock status) and resets those rows: `raw/` refreshed, `src/`
   reset to the new raw text, `refine/` body set aside, baseline cleared for a full rebuild.
2. **Imported copies were outside the recipe.** `config/overlays/*.as_flags.jsonl`,
   `*.rowbase.jsonl`, the noreturn/sibcall symbol lists and `tools/configure.py` are copies of
   upstream files (schema tag renamed); nothing re-copied them. The bump re-imports every one
   and lists the changes (at `82f20568`: 9 config files and the gate's `configure.py`).
3. **The pinned SLUS recipe came from the live tree.** `refresh.py` copied whatever
   `build.ninja` the live checkout had. The bump runs `splat split` and the *pinned*
   `configure.py` in `build_slus/` and records that as the pinned recipe (884 TUs; 0 cells
   differed from the live file this time, but the derivation is now honest).
4. **The stock predicate disagreed with upstream.** 36 rows (22.9 kB) that upstream counts as
   stock were excluded here: plus-dialect labels (`2.7.2+-G0`), ordinary `-m` flags, and
   general-purpose maspsx options (`--expand-div`, `--aspsx-version=`, `--preserve-*`).
   `common.py` now mirrors upstream's rule (stock cell, ordinary gcc flags, no `--retail-*`
   dial). At `82f20568` every registered row is stock: **6,766 / 6,766** (was 6,662).
5. **The campaign would not re-serve a row whose refine body was set aside.** `agent_task.py
   --all` treated an accepted journal entry as done; it now also requires the `refine/` file.

Two verifier lessons on top:

- **The six "assembler drift" rows were the verifier's own doing.** `dungeon/func_80A1D000`,
  `func_80A35000`, `func_80A41000`, `func_80AC5000`, `func_80FC3000`, `func_818F8800` (page
  rows whose `.text` starts with a data prefix under the true-name symbol) and the two town
  data rows written as C (`func_8094ECC4`, `func_80950CC0`) failed the per-row scorer
  (`extent-prefix 33`, "redeclared as different kind of symbol") while the window gate matched
  them. The cause was `normalise_definition`'s stale-name rename: when the row symbol was not a
  *function* definition it renamed the file's helper function onto the row symbol. It now
  leaves any text that already carries the row symbol alone; all eight score exact.
- **The window gate is the fallback of record.** For a text in `raw/` or `src/`, a row the
  scorer still cannot prove is gated through a view root over that tree
  (`verify.py::gate_fallback`, used by `--baseline` and `reverify.py`); a MATCH is recorded
  with `proof: window-gate` and the scorer's opinion kept beside it. Nothing is ever kept on
  the scorer's word against the gate's.

The baseline, `ledger/reverify.jsonl` and `ledger/gate.jsonl` are rebuilt in full at every
bump: the rows compile through the live toolchain, so an unchanged row can still change bytes.

**Registry diff at `82f20568`:** 83 rows with changed text, 78 with a changed config or dial,
104 flipping to stock, 122 stale rows in all (83 raw files refreshed, 86 derived files reset,
2 refine bodies set aside), 0 rows added or removed.

**Outcome:** every registered row stock and byte-exact at the pin (6,766 / 6,766; L0 100.0 %),
4,619 transformed rows re-verified with 0 drift, both refine bodies restored, SLUS SHA-1 gate OK
from the transformed tree, overlay gate **2,172 / 2,172 windows byte-identical** (2,181 YAMLs
minus 9 superseded seed windows). Levels: L1 73.1 %, L2 69.4 %, L3 12.9 % (bytes). The
4 windows that failed at the old pin (`dungeon_deep_t8b_adf000/b93000/b9f000/ba5000`) were
seed windows for rows since classified as data; each has a `_truebase_` twin that matches, so
`gate_all.py` now skips a seed whose twin exists **unless a registered row still names the seed
as its window** (`dungeon_deep_t8b_9c2650` keeps two rows past its twin's range and stays).
Wall time 77 min for the script plus a 12 min follow-up (the 8 verifier-only rows re-scored and
re-swept); the report is `ledger/pin_bumps/82f20568.json`. **The swap-over (§3) starts here.**
