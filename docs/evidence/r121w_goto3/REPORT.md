# r121w_goto3

Base: B13 private snapshot `ddc07bc5949684593cdc45a67e378a1f18324318` (`SCRATCH_HEAD`).
The snapshot has no Git metadata; `preimage_manifest.json` binds the actual B13
file preimages and final delta. No Git commits or ref moves were made.

**Seven goto statements removed in five existing homes, with no new rows or
coverage bytes.** The home-only census falls from **448 to 441 gotos**, and from
**219 to 217 files containing goto**. Twelve already covered placements now use
goto-free homes. Fourteen starting hold records close; three other homes have
exact partial reductions. No new goto edges, pins, asm, volatile, NON_MATCHING,
pragmas, artificial cases, compiler/assembler changes or comparison masks are
introduced. Existing semantic bit operations retain their meaning.

Production validation: **23 / 23 windows MATCH, including the final current-input audit**. The single final gate uses four workers
and exactly the 23 windows in `touched_windows.txt`. Row-database, source-layout
and exported-view checks passed before the launch. Every installed home and its
B13 preimage independently scores exact at the existing `2.7.2-cdk-G0` recipe.
The five home extents total 18,348 bytes; that is validation scope, not coverage.

**Per-item status**

| Home / queue item | Gotos before → after | Status |
|---|---:|---|
| `dungeon/func_812A524C` | 11 → 8 | exact partial: three indexed scan loops |
| `dungeon/func_8133AD74` | 2 → 1 | exact partial: genuine cases share the existing call tail |
| `dungeon/func_819A1654` | 2 → 1 | exact partial: timer condition falls through to case 4 |
| `dungeon/func_80A20A28` | 1 → 0 | exact indexed vertex loop; six existing placements cleaned |
| `dungeon/func_80FB5398` | 1 → 0 | exact indexed vertex loop; six existing placements cleaned |
| `dungeon/func_80E64FF0` | 2 → 2 | held: settling/falling loops change exit layout |
| `dungeon/func_80B467DC` | 2 → 2 | held: reconstructed goto-free candidate remains 3 substitutions / 0 indels |
| `dungeon/func_80CE9F34` | 1 → 1 | held: structured traversal 91 substitutions / 2 indels |
| `dungeon/func_80CEA348` | 1 → 1 | held: structured traversal 28 substitutions / 0 indels |
| `dungeon/func_80F90E88` | 3 → 3 | held: individual endpoint/extent loops and indexed endpoints fail |
| `dungeon/func_80FB402C` | 1 → 1 | held: split random-call arms remain one branch displacement off |
| `dungeon/func_80FB4C24` | 1 → 1 | held: indexed channels improve to 5 substitutions / 7 indels |
| `dungeon/func_8102FCB8` | 2 → 2 | held: structured cleanup variants fail jump-table validation |
| `town/func_8032EF6C`, `town/func_80476DBC` | unchanged | prior holds retained; no fresh rewrite claimed |
| Six uncovered SDK spans | unchanged | 32,784 bytes remain unregistered |
| 53 covered template holds | 53 → 41 | twelve placement records closed, with zero new coverage |
| 152 starting measured readability misses | two closed, one partially reduced | other outcomes retained, with fresh measurements where attempted |

The full 449-record input outcome table is `results.tsv`; the 293 remaining
hold records are in `holds.tsv`. Seventy-three fresh candidate measurements on
21 homes are recorded separately from inherited outcomes. These include genuine
compiler and jump-table failures; no failed measurement is represented as an
exact source result. Prior deliveries are marked `AT_BASE`. Every current-lane
`new_rows` and `new_coverage_bytes` field is zero. Old coverage deltas remain only
in explicitly named base fields.

**What closed**

A plain do/while scan in the largest donor rebases its byte cursor by `0x248`.
The added address instruction shifts many branch displacements. Index the stable
page base by `scan_index * 4` instead of advancing a separate C pointer, and the
compiler reconstructs the exact retail machine cursor. Each scan closes
independently, then all three close together at 5,464 bytes. The remaining eight
gotos preserve the earlier action stubs, their joins and initial dispatch. A
fully structured indexed version is 122 substitutions / 88 indels at 5,488
bytes and is not delivered. No compiler-version wall is claimed.

The two vertex donors use indexed writes in real descending do/while loops.
For `80A20A28`, use the existing `vertices` base: retaining its per-iteration
`vertex_base` alias adds a spill/reload and leaves 6 substitutions / 2 indels.
The stable-base spelling preserves all 1,408 bytes. `80FB5398` preserves all
1,500 bytes. Their twelve existing link-list placements account for 17,448
already covered bytes; they earn no new coverage.

In `8133AD74`, move real cases 5, 12, 14 and 18 to the existing shared call tail,
closing the preceding local block before those labels. All 5,068 bytes and the
jump table remain exact. Duplicating case 13's call still fails table validation.
In `819A1654`, a short-circuit condition performs the decrement only when the
original flags permit it, assigns state 4 only on the original transition, and
falls through to real case 4. All 4,908 bytes and the jump table match. Its
remaining interpolation loop has a 12-substitution / 0-indel goto-free miss;
localizing its index/product does not close the register roles.

**Validation and census authority**

The dependency closure contains 17 directly affected rows: five homes and twelve
link-list placements. Two native TUs add eleven sibling rows. Every active
production window covering those extents, including the native module projection
windows, is included in the 23-window scope. Both native-module certificates were renewed by consuming all seven native-window
receipts from that same gate; no certification window was rebuilt. The existing
membership/types/ownership review remains unchanged. No link list, registry row, rowbase,
recipe or raw first pass changes. `ledger/reverify.jsonl` gains five exact source
facts; the raw baseline and promotions ledger are unchanged. No L0 adoption or
coverage promotion is claimed.

The census resolves the registry through `source_layout`, counts each own-file
home once, and excludes placement facades and unregistered files. Two frozen
legacy relink copies (`80B79054`, `80B8B054`) also have one goto each and are
excluded. The initial diagnostic count including those copies was 450 → 443;
the requested home-only count is 448 → 441. Remaining relink or known non-home
copies were not edited. The largest-file follow-up inspected existing homes
`800A8714`, `80287C4C`, `819835AC`, `80084340`, `800CA184`, `8187C45C` and
`8133336C`; measured failures remain holds.

The grid's reconstructed cursor candidate remains exact in extent and has three
substitutions. A descriptor-based variant fixes the desired loop-base register
and later projection use but leaves four substitutions at the descriptor setup
and base reload. Flattened traversal and partial inner/outer loops also fail.
For the flight routine, either earlier loop changes the shared completion block
and state-test layout. The closest freshly measured single-loop rewrite is
8 substitutions / 50 indels; both original gotos stay.

**Holds by reason**

| Reason | Records |
|---|---:|
| Structured candidates still fail code, extent, compiler or jump-table comparison | 157 |
| Manual shared-tail/control shape; prior candidate absent, no new rewrite for this record | 86 |
| Already covered placement; remaining home still contains goto | 41 |
| Uncovered 5,464-byte SDK span; largest donor still contains eight gotos | 6 |
| Exact partial home cleanup; remaining edges held | 3 |
| **Total** | **293** |

Counts are outcome records, not disjoint coverage bytes. Covered placements,
readability homes and uncovered intervals can describe the same donor. The six
uncovered spans each contain 5,464 bytes, starting at file offsets `0x12CB24C`,
`0x12D124C`, `0x12D724C`, `0x12DD24C`, `0x12E324C` and `0x12E924C`. Their union
remains 32,784 bytes. Other non-goto SDK remainders remain out of this lane's
source-cleanup scope.

**Deliveries**

`delivery.patch`, `results.tsv`, `holds.tsv`, `touched_windows.txt`, `gate.log`,
`REPORT.md`, and `preimage_manifest.json`. The patch adds compact source/gate
receipts under `docs/evidence/` and measured idioms in
`tools/learnings/r121w_goto3_indexed_loops.md`. The final gate log replaces the
private root path with `<repo>`; its unredacted original is retained internally
and bound by SHA-256. Internal objects, retail slices, disassembly, compiler
dependencies and gate receipts remain inside the private root and are not
shipped. Large evidence is represented by summaries and SHA-256 values. The two renewed
certificate JSON files are included; their internal proof payloads remain in this
private root and are represented in the gate summary by hashes.

**HOW TO CONTINUE**

1. Apply only to the B13 preimages in `preimage_manifest.json`. Do not add the
   twelve existing placements again or count their bytes as new coverage. Keep
   the raw baseline unchanged. The patch application/reconstruction check must
   reproduce every final delivered hash. On a separate integration checkout,
   regenerate certificate proof payloads from the same canonical sources if the
   referenced internal proof directories are absent; no binary payload is shipped.
2. Continue `812A524C` from the installed three indexed loops (eight gotos).
   Keep the page base and index dataflow: reverting to a moving C pointer
   reintroduces the extra base instruction. The next unresolved feature is
   emission order of the three early action stubs and their joins, together
   with the initial two-way dispatch. The fully structured indexed candidate
   and its score are retained under this lane's `candidates/dungeon/` and
   `evidence/`. All six uncovered targets remain held until the entire home is
   goto-free and exact.
3. Continue the grid from `candidates/dungeon/func_80B467DC_cursor.c` (3 / 0).
   Compare `func_80B467DC_desc_base.c` and `evidence/grid_desc_regions.log`:
   the latter retains s4 and the final base use, but introduces the descriptor
   setup/reload residue. Resolve those live ranges together, without pins,
   invented cases or a masked comparison.
4. For `819A1654`, retain the delivered timer condition and investigate the
   fraction/Y-product allocation in `func_819A1654_timer_and_loop.c` (12 / 0).
   The residue also changes an earlier path-field base from a1 to a2; local
   index and interpolation-product variants were measured, not exact. For
   `8133AD74`, preserve the moved real cases; case 13 still needs its original
   call-site sharing and jump-table targets.
5. Reuse the indexed stable-base idiom only after checking each home's actual
   register roles. The successful vertex donors do not make the endpoint,
   attack, palette, flight or grid loop rewrites exact. Preserve the one-word
   skip-copy holds and all jump-table failures as genuine failures.
6. Use `results.tsv` / `holds.tsv` to distinguish inherited evidence from new
   measurements. Continue the remaining 41 covered-template holds and manual
   shared tails, then the largest remaining authoritative homes from
   `evidence/census_after.json`. Skip non-home copies scheduled for LL4.
7. After further source or row changes, refresh the export/projection, recompute
   source/module/placement closure, validate the view, and run one scoped gate
   with `--workers 4 --only-window ...`. Keep objects and retail payloads out of
   the next patch; summarize and hash large receipts.
