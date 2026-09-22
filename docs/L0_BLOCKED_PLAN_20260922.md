# The 138 L0-blocked rows: classification, yield-ranked work list, packs (2026-09-22b)

138 rows / **74,456 B** sit at L0 (`ledger/levels.jsonl`, level == 0), superseding the morning's
295 -> 288 count once §5's ruling (a `PASSTHRU_NO_ARGS` site on a `(void)`, byte-exact callee is not
a fidelity site) is applied and `tools/levels.py` re-run — 150 rows / 88,764 B left L0. Row table:
`docs/evidence/l0_blocked_20260922b.json` (138 records, recomputed against the CURRENT text with
`census.live_sites`/`live_audit`, `levels.intra_tail_calls`, `audit.json` for `need`/`kind`; adds
`callee_defined` per PASSTHRU site — `void-exact`/`void-not-exact`/`params:<list>`/`undefined`). The original `l0_blocked_20260922.json` (295 rows) stays for history; it is stale.

Two rows (`dungeon/func_800909A0`, `dungeon/func_80097AB8`) carry zero live PASSTHRU/LAC/ITC site
any more but are still L0: `levels.py`'s `boiler` gate (leftover m2c `typedef float f32;` header)
blocks L0->L1 regardless — a `t1_boiler.py` job, outside this taxonomy, carried as `BOILER-ONLY`.

dungeon 42/43,376 B, town 73/26,316 B, main 23/4,764 B. **90 of 138 carry no pin at all**; 70 have already been in some lane's pack.

## 1. Sub-classes

`need`/`kind`: `ledger/cache/audit.json`. Liveness: `census.live_sites` against the current text.
`callee_defined` (new): every `func_*` def in `src/{main,town,dungeon,slus}/*.c` x `ledger/baseline.jsonl`.

| sub | rows | bytes | pins | what it is |
|---|---:|---:|---:|---|
| BOILER-ONLY | 2 | 1,004 | 0 | zero live PASSTHRU/LAC/ITC site; held only by leftover m2c boilerplate |
| PASSTHRU-genuine | 9 | 3,212 | 19 | callee declares real parameters — pass-through is right, reader work |
| PASSTHRU-mixed | 1 | 152 | 0 | one genuine site + one undefined-callee site, same row |
| PASSTHRU-undefined | 37 | 15,968 | 10 | callee has no C definition anywhere in the tree; top targets `func_80071494` (32 sites), `func_800191E8` (8), `func_8001E82C`/`func_8001A7AC` (3 each) |
| LAC-mid | 21 | 12,168 | 43 | mid-row if/else rejoin only; 7 have a rowbase record, 14 don't |
| LAC-epi | 24 | 7,856 | 12 | epilogue only; 7 have a rowbase record, 17 don't |
| LAC-mixed-kind | 5 | 3,308 | 2 | one row mixes mid-row + epilogue; 2 have a rowbase record, 3 don't |
| LAC-other | 9 | 1,912 | 4 | target lies in **another row**: a real inter-row tail jump, no mechanism |
| ITC | 21 | 26,260 | 135 | intra-row noreturn tail pseudo-call, no baseline class; all 21 rowbase-proven |
| mixed | 9 | 2,616 | 7 | PASSTHRU + LAC/ITC both live; 8 of 9 are PASSTHRU-undefined + LAC-other — no mechanism either side |
| **total** | **138** | **74,456** | **242** | reconciles with `ledger/levels.jsonl` |

## 2. Yield-ranked work list

The morning's PT-A1..E menu is gone or reclassified; plainly, which sub-classes have a mechanism:

1. **LAC mid-row — has one.** `build_lac_lanes.py` links each pseudo-call at the true base once a
   rowbase record exists; the model rewrites goto/return (transform `t11_midrow`, 103 rows applied
   2026-09-08, `ledger/sweeps/t11_midrow.jsonl` — no `t11_midrow.py` generator, it's lane/model
   work). LAC family lane rate 0.45. 7/21 rows have a rowbase record now; 14 don't.
2. **LAC epilogue — has one, same gate.** `t10_epilogue.py` re-opens once a rowbase record exists:
   7/24 qualify, 17 don't.
3. **Rowbase data gap.** 49 LAC/ITC rows lack a `config/overlays/<family>.rowbase.jsonl` record
   (`rowbase.py` only READS one; a first record is manual j-solve evidence, then
   `tools/lanes/promote_honest.py` promotes it to `proven`). Only 34/49 would unlock work if it
   existed (LAC-mid 14 + LAC-epi 17 + LAC-mixed-kind 3, 7,956 B); LAC-other (7)/mixed (8) have none.
4. **PASSTHRU genuine — has one, tiny.** 10 rows / 3,364 B; `t8b_passthru_params.py`/`t8c_passthru_joint.py` handle it.
5. **PASSTHRU undefined-callee — no mechanism.** 47 rows / 18,736 B; top targets `func_80071494`
   (32 sites), `func_800191E8` (8) aren't even registered rows in `ledger/rows.jsonl`. Needs the
   callee decompiled or declared first (see §3's rebuild note).
6. **LAC-other — no mechanism**, unchanged: 9 rows / 1,912 B, a real inter-row tail jump.

## 3. Packs built (NOT launched)

Four packs in `work/native_lane/`, 48 rows / 33,132 B, each with `base/` (all 48 copies verified
current), `out/`, `rows.md` (duck + injected per-row fidelity note), `BRIEF.md`, `PROMPT.txt` and
`TOOLS.md` (v2 brief + lane kit). Notes and class questions in `work/lane_notes/`.

| lane | rows | bytes | sub-class | fresh | tier | still L0 (2026-09-22b) |
|---|---:|---:|---|---:|---|---:|
| `l0_pt_hold1` | 12 | 1,396 | PT-A3 | 12 | Claude Opus | 7 (5 now L1+) |
| `l0_pt_hold2` | 12 | 2,812 | PT-A3 | 12 | Gemini (agy) | 2 (10 now L1+) |
| `l0_pt_ord1` | 12 | 7,732 | PT-C2 | 11 | astra | 3 (9 now L1+) |
| `l0_lacjump1` | 12 | 21,192 | LAC-M 3, ITC 9 | 4 | astra | 12 (0 now L1+) |

(last column: `base/` listing vs. current `ledger/levels.jsonl`, post void-callee ruling)
**Tiers.** `ledger.py --by family`: LAC 0.45 over 32 lanes, best on the opus-labelled lanes
(`lackeep5` 0.875, `lacf1` 0.57) and astra (`lac_hard` 0.71), worst on sol (0.11–0.33); sol and luna
are out of capacity today. PASSTHRU has **no lane rate at all** — do not borrow ARG's 0.06, which is
`t33_argconst`, a different question. PT-A3 is therefore split across the two tiers that can be
compared in one wave (Opus vs Gemini, same sub-class, same brief): that A/B is the point. **It is
confounded by size** — `hold1` holds the 12 smallest PT-A3 rows (1,396 B) and `hold2` the next 12
(2,812 B) — so read it as a rate on rows of a similar kind, not a clean head-to-head. The ordinal
pack goes to astra because it is whole-function reading (match each `jal` in address order to its C
call). `l0_lacjump1` goes to astra: big rows, and the LAC family's astra rate is 0.71.

**Charter check on retries** (the rule is *never on rows a lane already served **at the same
text***). Each pack row's current sha was compared against the serving lane's own
`base/<container>/<name>.c`: in `l0_lacjump1`, **4 rows are fresh and 8 have text that changed since
every lane that served them** — so no row in any pack violates the rule. Five rows that *did* fail
it (`dungeon/func_81958F28` same text as all 8 of its serving lanes, `dungeon/func_818761D8` vs
`r72_kit_astra8`, `town/func_80810454` vs `r59_sol_large3`, `dungeon/func_8197C800` vs
`r70_kit_sol3`, `dungeon/func_819C0C18` vs `fx2`/`lacf1`/`r59_sol_mid4`) were **dropped**, which is
why the two originally-built lanes `l0_lacmid1`/`l0_lactail1` were replaced by the single 12-row
`l0_lacjump1`. `--repack` is still passed because `served.py` cannot distinguish same-text from
changed-text; the sha comparison above is the actual justification.

**Clones.** `l0_pt_ord1` is 12 *distinct* problems: of the seven 468 B rows only four
(`func_80F33094`, `80F39094`, `80F4B094`, `80F57094`) are rename-blind identical, so three siblings
were dropped and `dungeon/func_800AEA34`, `town/func_808146C8`, `town/func_805D3370` added; if the
representative lands, `tools/lanes/clone_transfer.py` carries it to the siblings free.

**Rebuild (2026-09-22b).** Hold packs not rebuilt — PT-A3 retired (§5). `l0_lacjump1` lost 0/12: no
rebuild, per instructions. `l0_pt_ord1` lost 9/12: dry run (`build_class_pack.py l0_pt_ord2 PASSTHRU
--rows town/func_805D3370,town/func_80813E14,town/func_808146C8 --duck --dry-run`, `pool 3 screened
out 0`) finds the 3 survivors, but all 3 are `PASSTHRU-undefined` on the same two hub callees
(§1/§2) at a **constant** `need` — not an ordinal question any more. `l0_pt_ord2` would send astra
at a question the callee cannot answer; **not built**. Launch commands unchanged, no new directory.

**Launch commands (do not run).**

```bash
# astra pool - two lanes, both in flight, one landing when the pool drains
nohup python3 tools/lanes/pool.py l0blocked --model astra -c 2 \
      --lanes l0_pt_ord1,l0_lacjump1 > work/native_lane/pool_l0blocked.log 2>&1 &

# Gemini, through the agy branch of launch_lane.sh
AGY_MODEL=gemini-3.8-flash-high bash tools/lanes/launch_lane.sh l0_pt_hold2 agy

# Claude Opus: there is NO Opus id in launch_lane.sh - its agy branch defaults to Gemini and
# ledger.py's tier_of_model only recognises gpt-*-{luna,sol,astra}.  The "opus" tier in
# ledger/lanes.jsonl comes from parse_title reading "(opus)" in BRIEF.md, and lacf1/lackeep5 carry
# no codex.log, lane.pid or last_message.txt - they were NOT launched by launch_lane.sh.  Per the
# charter, Opus runs through Workflow or `claude -p`; BRIEF.md line 1 already carries "(opus)" so
# the ledger files it correctly:
claude -p "$(cat work/native_lane/l0_pt_hold1/PROMPT.txt)"

# land when all four have exited (wait on work/native_lane/<lane>/lane.pid with kill -0)
LAND_ISOLATED=1 bash tools/lanes/land_gap.sh l0blocked \
      l0_pt_hold1 l0_pt_hold2 l0_pt_ord1 l0_lacjump1
```

**CPU work, no lane, runs alongside.** `gen_drive.py --fresh` truncates the journal and re-sweeps
the row list it is given, so it reaches PT-A1 (absent from the journal) and PT-A2 (stale) together;
a plain `sweep.py` run over the same list does the same without discarding the journal.

```bash
python3 tools/lanes/gen_drive.py --fresh t8b_passthru_params      # PT-A1 + PT-A2, 35 rows
# after the live_sites filter in t8_passthru.sites():  the same command                 # PT-B, 12 rows
# after tools/xform/t8c_passthru_joint.py exists:
python3 tools/lanes/gen_drive.py --fresh t8c_passthru_joint       # PT-C1, 89 rows
```

## 4. Honest estimate

Bytes that would reach L1, restricted to sub-classes with a real mechanism (PT-A1..E retired, §5):

| line | rows | bytes to L1 | basis |
|---|---:|---:|---|
| PASSTHRU-genuine reader sweep | 10 | ~3,000 | tiny, mechanical |
| LAC mid-row, rowbase present | 7 | ~3,700 | LAC lane rate 0.45 on 8,212 B |
| LAC epilogue, rowbase present | 7 | ~4,000 | t10 near-total once linked |
| LAC-mixed-kind, rowbase present | 2 | ~1,050 | LAC lane rate 0.45 on 2,372 B |
| ITC (all rowbase-proven) | 21 | ~11,800 | LAC lane rate 0.45 on 26,260 B |
| **total** | **~47** | **~23,500 B of 74,456 (32%)** | |

Not counted: the rowbase gap (34 rows / 7,956 B) needs a first record before either tool can try;
LAC-other (9/1,912 B) and PASSTHRU-undefined (37+/18,736 B) have no mechanism at all; BOILER-ONLY
(2/1,004 B) is `t1_boiler.py`'s job, outside this taxonomy.

## 5. Ruling requested: is PASSTHRU_NO_ARGS on a (void) callee a fidelity site?

Three results (2026-09-22) agree: `t8c_passthru_joint.py` built 89/89 joint candidates on multi-site rows, 0 exact,
every diff the same forced-register mechanism (FIDELITY.md's t8c paragraph); a Gemini lane (`work/native_lane/l0_pt_hold2/REPORT.md`,
12 rows) independently concluded "retain 0-arg call" row after row; and hub `func_800A6D30` (190 sites) is
`s32 func_800A6D30(void)` in `src/dungeon/func_800A15D0.c` — the LCG, reads no argument, exact.

**`need` is not callee-derived.** No audit generator lives here (`decomp_audit_ratchet.py`'s docstring: "the audit itself
lives in `tools/census/gaps/decomp_audit.py`"; that path and the `work/s3_splat` tree it needs are absent), so this is
read off the data. `func_800A6D30` reads zero registers (only its own seed) and `func_800990FC` (buffer selector) the
same, yet neither's `need` is ever empty over 228 / 29 sites — a callee-derived `need` on a function reading nothing
must be empty. `need` also varies **between sites of one callee inside one caller** (`town/func_800C0840` on
`func_800352FC`: `a3,a2,a1 / a3,a2 / a3,a2 / a3`, `ledger/cache/audit.json`) — no callee-invariant value can do that.
`need` is a caller-side label (which of a0-a3 still hold entry values at that call), mislabelled in `tools/agent_task.py:167`
("reads registers {need} at the call") and in FIDELITY.md's own class definition ("retail's callee reads argument
registers … the audit's need"). `func_800A6508` (dungeon/func_800A0DA8.c) and `func_800352FC` (`src/slus/konami_runtime_w_800352FC.c`)
confirm the shape: each passes a global's address on to one further call, reading none of its own. All four `(void)`,
all four exact. (Checked: 712/1,302 void-exact targets forward into another `func_`, 79 with fewer args than that
callee declares — ordinary byte-derived PASSTHRU debt, never blocking, about what the wrapper forwards onward, not
whether it reads its own caller's registers.)

**Patch:** `docs/evidence/passthru_void_callee.patch` (NOT applied) adds `census.void_exact_targets()` plus one line in
`live_sites`: a PASSTHRU_NO_ARGS site is not live when its target is `(void)` in the tree and that row verifies exact
(mirrors `levels.py`'s own slus rule: `status == "ok"`, since slus carries no `exact`). Measured by re-running
`levels.py`'s logic in memory (`ledger/levels.jsonl` untouched, clean before and after): **150 rows / 88,764 B leave
L0** — dungeon 129/78,592 B, town 21/10,172 B, main 0 — L0 falls from 288/163,220 B to 138/74,456 B.

**What stays blocked.** Of 209 L0 rows with a live PASSTHRU_NO_ARGS site: **10 rows / 3,364 B** target a callee that
genuinely declares parameters and verifies exact under that signature (real class — e.g. `dungeon/func_80098378` →
`func_8009EF04(s32 setup_a0, …, setup_a3)`, four sites of `func_80019988(void *record, s32 entry_index)`); **47 rows /
18,736 B** target a callee with no definition anywhere in the tree (top: `func_80071494` 32 sites, `func_800191E8` 8).
Neither group is adjudicated by this patch; the rest stay at L0 behind a live LAC/ITC site or a pin.

**For the owner:** (a) accept the patch as an audit correction, the same footing as the `live_sites` comment fix
already here — 150 rows / 88,764 B move to L1 at once, no lane spend; or (b) keep the class and price the 10 + 47
rows above as the only genuine PASSTHRU_NO_ARGS work left, retiring the model-lane menu (PT-A3/C1/C2/C3/D/E) built
to answer a question these callees cannot pose.

**Ruling 2026-09-22 (owner, verbatim):** "if it legitimately is shown the call site is void, no args is valid and no
longer a fidelity site. It may have been flagged because it showed no args but no one knew that was legitimate or
missing." — option (a) taken: a PASSTHRU_NO_ARGS site on a `(void)`, byte-exact callee is not a fidelity site.
`docs/evidence/passthru_void_callee.patch` applied to `tools/census.py` (`void_exact_targets()` + the `live_sites`
line); `python3 tools/levels.py && python3 tools/status.py` re-run clean, no tree drift.
Measured exactly as predicted: **150 rows / 88,764 B leave L0** (dungeon 129/78,592 B, town 21/10,172 B), L0
288/163,220 B -> 138/74,456 B; of the 150, 2 rows / 916 B stop at L1 (M2C_FIELD left), 98 rows / 56,308 B stop at L2
(no landed promotion), 50 rows reach L3 directly. Wording corrected in FIDELITY.md's PASSTHRU_NO_ARGS bullet and
`tools/agent_task.py`'s prompt (`need` is a caller-side label, not a claim about what the callee reads).

## 6. Opus wave results (2026-09-22 evening)

Five Opus agents, one L0 remainder class each (§5 ruling, §2 yield-ranked list). Before/after read
from `ledger/levels.jsonl` + `ledger/rows.jsonl` at 2026-09-22 07:20Z against `docs/evidence/l0_blocked_20260922b.json`
subclass tags (all 35 current L0 rows resolve to a b.json subclass, no drift). Report's own landed/
refused count in parens; several don't match the ledger "cleared" count exactly (off by 1-4 rows) —
not reconciled here, kept as reported.

| class assigned | before | after | cleared | report says |
|---|---:|---:|---:|---:|
| ITC | 21 / 26,260 | 9 / 13,940 | 12 / 12,320 | 12 to L3, 1 pin-free exception never closed |
| LAC-mid + LAC-mixed-kind | 26 / 15,476 | 9 / 11,224 | 17 / 4,252 | 18 landed |
| LAC-epi | 24 / 7,856 | 4 / 4,556 | 20 / 3,300 | 19 landed + 5 refused |
| PASSTHRU-undefined (+1 PASSTHRU-mixed) | 38 / 16,120 | 1 / 488 | 37 / 15,632 | 27 callees disassembled |
| PT-genuine + LAC-other + mixed | 27 / 7,740 | 12 / 5,056 | 15 / 2,684 | 11 landed |
| BOILER-ONLY (not one of the five) | 2 / 1,004 | 0 / 0 | 2 / 1,004 | cleared by t1_boiler/L2 sibling |
| **L0 total** | **138 / 74,456** | **35 / 35,264** | **103 / 39,192** | |

**Templates that paid.** ITC: delete the pseudo-call when a `return;`/if-else merge already follows;
`goto` an already-labelled block (flip the test on scorer polarity=1); THREAD-FILL HOIST (retail +4:
hoist the delay-slot load above the shared label); PAGE-BASE VAR -> plain extern symbol. LAC mid/epi:
"init join" (forward `j` -> if/else + shared tail, merge m2c's `result`/`base` locals); backward `j`
= LOOP (induction step on the back edge only, slots spelled `base + i*stride + disp`); shared-increment
join (carry the loaded byte in a local of the field's width, hoist the taken arm's stored constant
above its test); mid-row `else` (taken arm's call skips the next block). PASSTHRU-genuine:
`t8b_passthru_params.py`/`t8c_passthru_joint.py` reader work, small and mechanical. LAC-other/mixed:
13/18 "other-row" sites were misclassification (`kind` vs a null `true_name`) — 10 rowbase records
fixed it. PASSTHRU-undefined: no C template — the fix is the declaration route below, not a rewrite.

**Tooling added.** `tools/lanes/mint_rowbase.py` mints the first `solved` rowbase record: registered-
identity grade (`foff + 0x80197000 == int(true_name)`, main family, bookkeeping only) or target-
containment grade (no `true_name`; every LAC/ITC target inside the candidate base, not all inside the
synthetic one). `config/void_callees.txt` (28 symbols: 27 tier A from disassembled retail bytes, 1
tier B call-site-only) feeds `census.py::declared_void_callees()`, unioned into `void_exact_targets()`
(evidence: `docs/evidence/void_callees_20260922.md`). `census.py`'s `DEF_HEADER_RE` blanks a row's own
definition header before scanning for `LABEL_AS_CALL` self-calls (back-edge loop rows whose target is
the row's own base). `census.live_sites`/`levels.intra_tail_calls` now blank `port`/`dead` arm lines
before matching a call — text the build never compiles isn't a live call (freed `town/func_8051EDA4`).

**Landing recipe, rows with no rowbase record.** Region `[foff, foff+size)` -> delta from
`ledger/splits/<fam>.jsonl` -> write a `solved` record (j-solve proof) -> regression-verify -> build
the t10/hand candidate -> land -> `build_ovl/tools/rowbase.py promote` with an **absolute** candidate
path. Trap: a relative path CFAILs silently — `promote`'s cwd is `build_ovl/`, not the repo root.

**Tier-B caveat for the owner.** `void_callees.txt`'s one tier-B entry, `func_80071494`, has no image
on disc to disassemble; its "reads no argument" verdict rests on 37 retail call sites (v0 always
masked/consumed as `s32 rand(void)`), not the callee's own bytes like the other 27. It alone gates 10
rows / 10,536 B out of L0. Comment says "delete this line to keep tier A only" — that re-blocks them.

**CLOSED (2026-09-22, rowbase mop-up).** `dungeon_deep_t8_187c` is **no longer an open item**: the
window gates MATCH. It was red because rows had been landed against rowbase regions that were still
`solved` — `promote.py::needs_gate` skipped the window gate as soon as a row had a `true_name`, while
the gate only links at the true base when the region is ALSO `proven`, so the gate kept linking those
rows synthetic and their own `j` words came out wrong. Promoting the regions fixed `t8_1830`,
`t8_187c`, `t8_18d0`, `t8_197a`, `t8b_18fad38` and `t8b_1972800`; `needs_gate` now tests
`true_name AND a proven rowbase delta that matches it` (unit test `tools/tests/test_promote_needs_gate.py`).

**NEW open item — `main/func_7FDD3D54`, linking scope at the true base.** Its rowbase record
(`row_23d54_8008acb4`, delta `0x80066F60`) is **not byte-neutral** and was **backed out**: with the
record the row goes from exact to **11 subs / const-remat**, every reference to its `D_8009xxxx` data
symbols coming back as `lui $v0, 0` — the relocations stop resolving once the row is linked at
`0x8008ACB4`, while the instruction stream is otherwise unchanged. Nothing else in the mop-up showed
this (16 other records were minted and 16/17 rows regression-verified exact), so it looks specific to
that bank rather than to the tool. Worth understanding before anything else is minted at
`0x80066F60`. Its tail-jump target is a decode artefact, not a real symbol: a J-type word takes its
top nibble from the PC, so at the synthetic base `0x7FDD3D54` the word decodes as `func_7008ACFC`,
while at the true base it is `0x8008ACFC` = **base + 0x48**, an ordinary intra jump.

**Open items.** `t10_epilogue.py`: no `goto done; ...; done: return <var>;` action for value-returning
functions, `polarity` missing from `COLLAPSE_CLASSES`. `dungeon/func_81875C70`: maspsx `jal`->`j`
false member of `config/noreturn_syms.dungeon.txt` — needs a `config/noreturn_false_members.jsonl`
entry + dungeon gate, not added (the row's honest loop is otherwise byte-perfect: residue is that one
word). `main/func_7FDD3F8C`: `live_sites` counts a plain call of a
`config/sibcall_syms.txt` target as `LABEL_AS_CALL` (stale label); no `noreturn` attribute either —
neither fixed. Two devkit rowbase deltas by fingerprint (`0x7FF01000`/town foff `0x7FFEF0`,
`0x7FEC7000`/foff `0x8394E0`) are candidates only, not minted. `main/func_80019EF8`: still L0 —
`func_8007CA38` is off-disc and the tree contradicts itself on its signature.

**Current L0 residue (35 rows / 35,264 B), grouped by the refusal class a report names; "not
reached" where none of the five reports names this row specifically:**

| refusal class | rows | bytes | example row(s) |
|---|---:|---:|---|
| ITC label-liverange (only non-closing pin-free site) | 1 | 2,524 | dungeon/func_81904990 (true base func_80024190, target func_80024AA0) |
| ITC pin-in-front (refused, no per-row mechanism named) | 8 | 11,416 | dungeon/func_818EC800, func_81850800, func_818E6800, func_8197C800, func_818BC9CC, func_8186EDA8, func_8195AB84, func_8191CA88 |
| LAC reg-rename ($a1/$v1 free-register choice) | 2 | 628 | dungeon/func_80088964, town/func_80813294 |
| LAC-mid noreturn false member (maspsx jal->j) | 1 | 932 | dungeon/func_81875C70 |
| LAC-epi broad (LEAD-18: preceding call is `j`, retail `jal`) | 2 | 4,288 | dungeon/func_80A71654, func_80FB176C |
| LAC-epi dead-code-retention | 1 | 112 | dungeon/func_800A3C30 |
| LAC-epi length-drift (empty leaf frame kept) | 2 | 312 | town/func_80810F98, func_808151F8* |
| PASSTHRU-undefined off-disc signature contradiction | 1 | 488 | main/func_80019EF8 |
| LAC-other hold-set (no C spelling, genuine inter-row j) | 1 | 88 | town/func_8047E0D8 |
| LAC-other stale sibcall label / no noreturn attr | 1 | 324 | main/func_7FDD3F8C |
| not reached (LAC-mid 4, LAC-mixed-kind 2, mixed 1, PT-genuine 5, LAC-other 3) | 15 | 14,152 | — |

*`func_808151F8` is tagged `LAC-other` in `l0_blocked_20260922b.json`; the LAC-epi report groups it
with `func_80810F98`'s length-drift class by name. Not reconciled.

Post-wave check (2026-09-22 evening): `gate_all.py` re-gated the 191 stale windows: 191 MATCH; SLUS SHA-1 gate MATCH. Two corrections to the reports above: town/func_8070E604 is at L3 (its second target func_8001A7AC is tier A in void_callees.txt); the ITC "pin-free site always closes" rule has two exceptions (func_81904990/func_80024AA0 and dungeon/func_8191CA88), so it is a screen, not a guarantee.

## 7. Afternoon wave 2026-09-22

10 shape-work rows (all dungeon, per-row jump/tail-call sites needing a C shape), 6 landed, 4 refused with
measured residue. 5 of the 6 landed rows promoted a rowbase region solved->proven; `func_819611CC` also
registered `true_name` `func_800269CC`. Trades in `ledger/recipe_trades.jsonl` round `l2_shape_20260922`.

| row | result | shape |
|---|---|---|
| `func_81960530` | landed | pseudo-call -> `continue;` |
| `func_81880F28` | landed | 3 pseudo-calls -> `goto update_motion;` |
| `func_80E3C98C` | landed | deleted the pseudo-call; an existing goto already spelled it |
| `func_8191CA88` | landed | epilogue pseudo-call -> `goto done;` + site_for_pin trade `ASM_REG("$8")` on `motion` |
| `func_8183EE88` | landed | 3 pseudo-calls -> `return;` + arm swap (the polarity/12 screen) |
| `func_819611CC` | landed | backward `j` -> label+goto loop + site_for_pin trade `ASM_REG("$2")` on `initial_state` |
| `func_8197CEC0` | refused | const-remat/15: honest `break` gives the post-switch tail a third predecessor; reorg copies `li $s0,4` into two empty delay slots; site B alone was clean = a possible 2->1 partial (owner call) |
| `func_818390F8` | refused | broad/1 word: `addiu $s0,$sp,24` vs retail `move $s0,$s7` (inner-loop biv re-init); a real `for(;;)` is worse at 33; not `-fno-rerun-cse-after-loop`; needs `true_name` + proven region before any exact candidate can gate |
| `town/func_80813294` | refused | reg-rename/2: `li $a1,10` vs `$v1`; hoisting fills the delay slot but forces the register; `ASM_REG("$3")` makes it worse at 18 |
| `dungeon/func_80088964` | refused | reg-rename/3: `$v0`/`$v1` local-alloc tie in an untouched block |

Refused candidates kept in the session scratchpad only (not durable).

**Corrected L0/L2 residue counts (post-wave, this session).** L0 32 rows / 34,196 B (dungeon 20, town 11,
main 1); L2 8 rows / 4,076 B (`dungeon/func_81071000`, `func_818390F8`, `func_8197CEC0`, `func_8199AAD4` +
4 parked ovmovie rows). Section 6's 35-row / 35,264 B table is superseded: 7 named rows left L0 today
(`func_8191CA88` via the shape landing above; `func_81875C70`, `func_80A71654`, `func_80FB176C`,
`town/func_80810F98`, `town/func_808151F8`, `main/func_80019EF8` resolved incidentally, likely by the
census/false-member fix in `docs/HANDOVER.md` section 0). `func_8197CEC0` and `func_818390F8` are now L2,
not L0 — they were never in section 6's table (it only covers the L0 population); see `docs/HANDOVER.md`
section 3 for the full reclassification against `l0_blocked_20260922b.json` subclasses.

## 8. Goal round 2026-09-22 (13:55-15:15Z): every row reaches L3

Supersedes section 7's "Corrected L0/L2 residue counts" — those were the state at the start of this round
(L0 32 rows / 34,196 B, L2 8 rows / 4,076 B). By 15:15Z: **L0 0, L2 0** (`ledger/levels.jsonl`, all 6,767
rows at L3). Pins 4,355 -> 4,322 in 1,053 rows; 27 site-for-pin trades recorded in
`ledger/recipe_trades.jsonl` round `l0_goal_20260922` (matches `STATUS.md`'s own site-for-pin counter).

### Per-row outcome table

Built from the 23 `l0_goal_20260922` ledger lines (13 distinct rows; the other 10 lines are follow-up
trades on the same 13, or `recipe-reduction` records with no pin field). "Sites" is the tail-jump/NON_MATCHING
site count given directly in the ledger's `site_closed`/`site_open`/`tail_targets_after` fields or the row's
own trade text — left "—" where the ledger did not log a site count for that row. "Pins" is this round's
net change only (first known pins_before -> last known pins_after for the row this round), read from the
ledger's `traded`/`why` prose where the structured `pins_before`/`pins_after` fields were null.

| row | sites (before→after) | pins (before→after) | template(s) (§ below) | trade |
|---|---|---:|---|---|
| `dungeon/func_81844F2C` | 2 intra (`func_80024808`, `func_80024860`) → 0 | 2 → 3 (peaked at 4 mid-round) | 6 | site A: ASM_REG("$5") + ASM_KEEP(`effect`) added (ruling b, +2); site B: pin-free via cell switch 2.7.2-G0 → 2.7.2-cdk-G0 (NOT byte-neutral at the old cfg, section 4b); then ASM_KEEP(`tick_or_index`) removed (-1) |
| `dungeon/func_818B6AFC` | 1 (NON_MATCHING arm) → 0 | 16 → 17 (`pins_after_live` 14) | ruling (d) | ASM_USE_NV(`render_owner`) added |
| `dungeon/func_8199AAD4` | — | 8 → 9 | — | ASM_KEEP(`table_end`) added |
| `dungeon/func_8195AB84` | — | 5 → 6 (net; 3 added / 2 removed) | — | ASM_REG("$21") `saved_x` + ASM_REG("$23") `saved_z` + ASM_REG("$4") `transform` added; ASM_KEEP + ASM_KEEP_NV(`call_context`) removed — section 4a open question |
| `dungeon/func_81850800` | — | 13 → 12 | 3 | ASM_SCHED_BARRIER at the `span_magnitude:` join head |
| `dungeon/func_8197CEC0` | site B (L2 partial, ruling c) → 0 | 3 → 4 | 3 | ASM_SCHED_BARRIER at the post-switch join head |
| `town/func_8080C650` | — | 15 → 7 (net, 2 trades) | 10 | trade 1: ASM_REG("$18") `var_s2` added, ASM_TAILSLOT_PIN_TIED(`temp_v0_6`) removed (net 0); trade 2: ASM_TAILSLOT_PIN_TIED + 7x ASM_KEEP(`var_s2`) + ASM_SCHED_BARRIER removed (-8) |
| `dungeon/func_818BC9CC` | — | 2 → 2 | 2 | ASM_SCHED_BARRIER (z_extent load → add, tail of L_case0) added; ASM_TAILSLOT_PIN_TIED(`far_z`) removed |
| `dungeon/func_8197C800` | — | 14 → 15 | 4 | ASM_KEEP(`result`) on the page-base spelling of `D_80083780` in `case_three` added |
| `dungeon/func_818E6800` | sites A-D → 0 | 16 → 12 | 1 (sites B-D), 3 (site A) | ASM_SCHED_BARRIER as first statement of `state_2:` added; ASM_TAILSLOT_PIN(`count`) + 2x ASM_TAILSLOT_PIN(`next_state`) + ASM_REG("$3") `hold_frames` + ASM_KEEP_DEP_NV(`hold_frames`,`current_state`) removed |
| `dungeon/func_818EC800` | 1 forward (`func_80024990`) → 0 | 17 → 10 (net, 3 trades) | 8, 4 | trade 1: ASM_TAILSLOT_PIN_TIED(`frame`) removed (17→16); trade 2: ASM_USE2(`sprite`,`frame_data`) + ASM_USE_G_NV(`callback_arg`) + ASM_USE_G_NV(`saved_draw_mode`) + ASM_USE(`frame`) removed (16→12); trade 3: 2x ASM_KEEP(`frame_data`) removed (12→10) |
| `dungeon/func_81904990` | 2 (`func_800244B0`, `func_80024AA0`) → 0 | 15 → 13 (net, 4 trades, peaked 16) | 2, 3, 4, 8 | trade 1: ASM_REG("$16") `frame_data` added, ASM_TAILSLOT_PIN(`frame_header`) + back-edge ASM_KEEP(`frame_data`) removed (15→14, partial); trade 2: ASM_SCHED_BARRIER at arm tail + ASM_REG("$21") `frame_header` added (14→16, partial — `func_800244B0` site regressed, addressing/7 residue on record); trade 3: ASM_TAILSLOT_PIN(`tail_value`) removed (16→15); trade 4: ASM_KEEP_NV(`frame_data`) + ASM_REG("$16") `frame_data` removed (15→13) |
| `dungeon/func_818390F8` | 1 backward (`func_80024934`) → 0 | 5 → 0 | 7 | ASM_KEEP(`screen_base`), ASM_KEEP(`render_record`), 2x ASM_KEEP(`position`), ASM_REG("$20") `projection_out` all removed; recipe-reduction: byte-exact at both recipes, moved onto the bare dungeon census recipe |

**Reconciliation note.** The 13 rows above net -21 pins (2→3 +1, 16→17 +1, 8→9 +1, 5→6 +1, 13→12 -1, 3→4 +1,
15→7 -8, 2→2 0, 14→15 +1, 16→12 -4, 17→10 -7, 15→13 -2, 5→0 -5). `STATUS.md`'s round-level delta is
4,355 → 4,322 (-33). The remaining -12 pins came from landings elsewhere in the round with no
`ledger/recipe_trades.jsonl` record (untraded — no site-for-pin trade to log because no pin was added; not
itemised here). Confirmed against `ledger/levels.jsonl` directly: `func_81904990` and `func_818EC800` both
show `tail_jumps: 0`, `split_audit: []` in their current record, so the sites left open mid-round
(`func_800244B0`, `func_80024AA0`, `func_80024990`) are closed in the final state even though no later ledger
line logs the closing move explicitly.

### Ten templates (mechanism, reusable across rows — see also `docs/HANDOVER.md` section 6)

1. Many retail intra `j` words are gcc's own cross-jump output: write the shared tail verbatim inside the arm
   and let post-reload cross-jumping merge it (`ovmovie/func_800403EC`, `dungeon/func_80BD3BA8` site 1,
   `func_818E6800` sites B-D, `func_81904990` &2 block). When it over-merges (the unconditional-jump minimum
   is 1 insn), swap arm polarity so the negative arm falls through and never ends in a simplejump to the
   shared label (`func_80BD3BA8` site 2: polarity/3 -> 0).
2. To KEEP two identical tails unmerged where retail duplicates them: a zero-byte volatile asm
   (ASM_SCHED_BARRIER) within the last two insns of the tail but not in the delay-slot position breaks
   `find_cross_jump` (minimum 2 for the jump-chain case, 1 when a CODE_LABEL sits in one stream); an
   order-only statement difference does not survive sched1 (`func_818BC9CC`, `func_818E6800` site A). Better
   still: give both arms the same destination pseudo (`x = x +- load`) so the final op overwrites its dead
   operand and cannot float above the stores (`func_81904990` third site, zero pins).
3. ASM_SCHED_BARRIER right after a multi-predecessor label (or as the last statement of an arm) restores
   delay slots lost to reorg's redirect past the join head (`func_81850800` 21 -> 0, `func_8197CEC0` 10 -> 0
   word-residue; `func_81904990` forward site).
4. A CALL_INSN marks every call-saved register as referenced (resource.c), so a fake noreturn call changes
   reorg's slot choice and live ranges: with the call gone, reorg takes the first fall-through insn; a
   page-base split (`result = 0x80080000; ASM_KEEP(result); ptr = (T*)((u8*)result + off)`) gives it a
   takeable head insn (`func_8197C800`). Rematerialised `lui/addiu` pairs at each use come from a pseudo with
   a REG_EQUIV symbol whose live range runs prologue-to-epilogue; ONE shared C pointer variable used at every
   site including the epilogue reproduces it at zero pins (`func_818EC800`, `func_81904990`).
5. A `volatile` load is never delay-slot eligible: dropping `volatile` closed reg-rename/2
   (`town/func_80813294`) and a union-volatile in `func_80088964`.
6. Polarity residues from jump.c's condjump-around-uncondjump inversion fire only when the conditional jump
   is IMMEDIATELY followed by the unconditional one: spell the arm as a bare `goto label;` with the target
   block's first statement placed at the label head; the compiler cell mattered (2.7.2-cdk keeps an in-block
   page base in a register where FSF 2.7.2 folds it) (`func_81844F2C` site B, cell switch 2.7.2-G0
   -fno-schedule-insns2 -> 2.7.2-cdk-G0, NOT byte-neutral at the old cfg).
7. loop.c strength reduction takes the pointer induction variable's initial value from the address
   expression's rtx: `&buf[i*2]` gives `addiu $s0,$sp,0x18`, `&screen_base[i*2]` through a real variable gives
   the register copy `move $s0,$s7` (`func_818390F8`, five pins fell, flag dropped).
8. Delete the pseudo-call AND its ASM_USE/ASM_KEEP cluster in ONE candidate; measuring with the cluster in
   place over-constrains the join and hides free landings (`func_818EC800` 16 -> 10 pins, `func_81904990`
   16 -> 13).
9. Three of five "PASSTHRU-genuine" tags were wrong: the b.json `callee_defined` read the C tree's
   declaration, not retail bytes; the honest fix corrected the callee TU to `(void)` (byte-neutral) rather
   than passing arguments.
10. ASM_TAILSLOT_PIN_TIED sites: spell the taken arm so its last statement is the slot producer; reorg fills
    the slot itself and the tied pin falls (`func_818F2800`, five sites, five pins).
