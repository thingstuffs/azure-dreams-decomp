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
the include root as `-I`, the seven files are fixed, and every transformed row is re-verified
under the strict rule. Rule for the swap: **the gate's compile command is the only compile
command**; verification tools must call it, not imitate it.

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
