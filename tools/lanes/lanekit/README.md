# lanekit - the harness a lane gets, so no lane builds one again

Built 2026-09-21 from `docs/evidence/lane_log_mining_astra_20260921.md` and
`lane_log_mining_sol_20260921.md` (30 mined lanes). Every astra lane rebuilt the same
erase-compile-screen-verify-log loop; the cwd shim was invented twice and rewritten four more times;
five sol lanes hand-rolled subset erasure scans; and 13 of 16 astra lanes ended asking for a tool
that explains *why* a gcc pass decided what it did. That is what is here.

    cd work/native_lane/<lane>
    source <REPO>/tools/lanes/lanekit/env.sh     # optional; sets LANE/PYTHONPATH/TMPDIR
    python3 <REPO>/tools/lanes/lanekit/<tool>.py ...

Every tool writes **only inside the lane directory** (it refuses to run at the repository root), and
every compiler dump lands inside it by construction: `TMPDIR` and `tempfile.tempdir` point at
`<lane>/tmp`, so the `TemporaryDirectory` each shared tool compiles in is already there, and the
`sitecustomize.py` shim re-homes any compiler that would otherwise run at the repository root.

| tool | what it prints |
|---|---|
| `lab.py` | listing distance, pins left, byte score (a no-build candidate prints its cpp/cc1 stderr), and the REPORT table; `--base FILE`, `--cfg`, `cellscore`, `stage-cell [--equal-pins]` |
| `erase.py` | what each pin holds, and which pins fall together (`--cfg`: byte totals at another cell) |
| `why.py` | the pass DECISION that changed: priorities, allocnos, loop verdicts, RTL (`--cfg` for another cell); ONE text at TWO cfgs (`<text> --cfg A --vs-cfg B`); `--trace --block`: one block tick by tick; `--deps UID`: one insn's LOG_LINKS and dependents; `--block --deps-table`: the whole block's dependence table with birthing boost |
| `listing.py <row> <text.c>` | the normalised cc1 listing of a text (on the pinned exact text = retail's instruction order with register names) - round 93 (Fable) |
| `retail_listing.py <row> <cand.c> [--cfg]` | the scorer's generated listing of a non-exact candidate (prints nothing on MATCH: use listing.py) |
| `ccerr.py <row> <text.c>` | the preprocessor / cc1 stderr of a text - why lab.py said `no-build` |
| `diff.py` | the unified cc1-listing diff of one candidate vs pinned / erased / a file (+ `--score`, `--cfg`, `--scorer [--norm-regs]`: the byte scorer's retail-vs-generated diff and score; `--scorer --classify`: ORDER / COLOUR / OPCODE / COUNT per region); journalled to `lab_log.jsonl` |
| `checks.py` | the four proof checks (sole-ready, launched group, known-constant base, barrier): a verdict per residue insn |
| `dbr.py` | the delay-slot (reorg.c) explainer: for every branch/jump/call with a delay slot, which routine filled it (fill_simple backward/forward, fill_eager fall-through/target thread, steal, copy + redirect, relax) and every candidate it refused, in order, with the reason (register/memory conflict and the insn behind it, LIVE at the opposite thread and why - flow, first read, an update_block `(use (insn N))` marker -, may trap, not eligible: type/dslot/length, label/jump/asm stop, thread not owned); the mostly_true_jump prediction and the rule that gave it; `--retail`: retail's slot word beside ours and a `DECIDING:` line. The cell's own cc1 under gdb (`dbr_gdb.py`) |
| `combine.py` | the combine.c explainer (round 93): every try_combine attempt of the function (i3, i2, i1 uids of the `.flow` dump), COMBINED (the new i3 pattern, i2/i1 deleted) or REFUSED with the return site (combine.c line) and the check: can_combine_p's TRUE clause (use_crosses_set_p naming the store / CALL / register that crossed, crosses-call, call-arg, used-between ...), combinable_i3pat, subst-fail, or no-recog with every pattern handed to recog_for_combine and its code; `--insn UID` (as i3, i2 or i1), `--list`, `--all`, default = refusal census. The cell's own cc1 under gdb (`combine_gdb.py`) |
| `dump.py` | every `-da` pass dump of one text into a lane directory (`--cfg` for another cell) |
| `prio.py` | the global-allocation priority table of one text at a cfg (refs, live, floor_log2, priority, got) |
| `regcmp.py` | how many NAMED variables sit in a different register than in a reference text (`--subsets`: every pin-removal subset ranked) |
| `alloc_need.py` | the allocation INVERSE: retail's register per pseudo (from the aligned listing), a verdict per mis-coloured pseudo (ORDER / BLOCKED / CLASS / LOCAL / SPILLED) and, for ORDER, the `allocno_compare` inequality that flips it (`refs >= N at live L`, `live <= L`, ...) with the source lever per term |
| `lreg_explain.py` | local-alloc replayed from the `.lreg` dump: per block the qty list (birth/death indices, ties, copy/arith suggestions), the suggestion and priority orders block_alloc used (the 2/3-qty literal-number replay included), why each qty got its register, and for a mis-coloured LOCAL pseudo who held retail's register plus the PRIORITY (refs/length) or GEOMETRY (birth/death index) change that gives it; reproduces every local pseudo of every row against `;; Register N in R.` |
| `prefs.py` | global.c's hard-register PREFERENCES replayed exactly (set_preference, expand_preferences, prune_preferences / regs_someone_prefers, find_reg's copy-then-plain preference override): per allocno WHY it got its register (scan pass 0/1, or the preference and its provenance chain: which insn, which local qty / parameter / call argument / ASM_REG variable, which merge where a partner dies), why not retail's, and every single preference event whose removal gives retail's register (with collateral). `alloc_need.py` calls it on rows with a preference effect. Library: `tools/alloc_prefs.py` |
| `prefs_gdb.py` | the oracle `prefs.py` is validated against: the cell's cc1 under gdb, the preference sets after set_preference / expand / prune, regs_someone_prefers, regs_used_so_far and every find_reg result |
| `install.py` | `TOOLS.md` in a lane: the same table with that lane's rows |
| `sitecustomize.py`, `lane_shim.py`, `env.sh`, `kitlib.py`, `retailmap.py`, `dbr_gdb.py`, `combine_gdb.py` | plumbing; you never call these |

## Pin-removal source-shape possibilities

Read `../../learnings/pin_removal_possibilities.md` before inventing a new source family. It
catalogues aggregate-copy forms, lvalue signedness, prototype widths, struct fields versus raw
offsets, address-base sharing, variable split/merge and set-count effects, pointer-store CSE
effects, loop hoisting, and lexical control-flow order. Use these possibilities to rank hypotheses
for a target-local rebuild. The row's recorded recipe and full byte scorer remain the authority.

---

## lab.py - the harness

```
python3 .../lab.py baseline <row> --score          # STEP 1, always
python3 .../lab.py <row> v1.c v2.c --score         # variants as files
python3 .../lab.py <row> --subs shapes1.json --score [--score-top 3]
python3 .../lab.py <row> --grid grid1.json --score  # every combination of independent axes
python3 .../lab.py <row> v7.c --cfg "2.8.1-G0" --score          # measure at another cfg
python3 .../lab.py cellscore <row> v7.c --cfg "2.8.1-G0"        # trade check + hand-over lines
python3 .../lab.py stage-cell <row> v7.c --cfg "2.8.1-G0" --note "mechanism"   # exact there -> out/ + cells.jsonl
python3 .../lab.py stage-cell <row> v7.c --cfg "2.7.2-cdk-G0" --note "..." --equal-pins   # same pin count
python3 .../lab.py <row> --base cand/best.c --subs s.json --score   # substitute on YOUR file, not the erased text
python3 .../lab.py report                          # the REPORT.md table, from lab_log.jsonl
```

* **Before writing a helper of your own, check this README - 26 lanes rebuilt the listing diff
  (`diff.py`), 23 the dump fetch (`dump.py`), ~21 an `itertools.product` grid (`--grid`) in round 73.**
* **`--base FILE`** (with `--subs` / `--grid`) starts every substitution set from FILE instead of the
  pin-erased text - round 80: three lanes wrote `gen.py base.c subs.json outdir` for exactly this. `@name`
  and `"@base": "pinned"` still mean the pinned text; the guards, the misses log and the staging gate
  (admissible vs the lane's `base/` copy) are unchanged. Variant files given on the command line are
  measured as they are (`--base` does not touch them).
* **`--grid`** takes `{"axis": {"label": [["old","new"],...], ...}, ...}`: one label per axis, every
  combination, named `label+label+...`, applied in axis order like `--subs` (nearest-line message,
  `pattern-missing` logged). `[]` is a valid label ("leave it"); `"@base": "pinned"` starts from the
  pinned text. The product counts against the cap.
* **`--cfg CFG`** compiles and scores as if the row were registered at CFG (the row-dict override
  `land_coherence.sh` uses). Distance stays against the pinned listing at the registered cfg, so it
  is information only: every variant that builds is scored and nothing is staged. **`cellscore`**
  also scores the pinned text at CFG (rule 2: byte-neutral switch or genuine coherence trade) and,
  when exact, prints the `cells.jsonl` line and the `land_coherence.sh` command for the
  orchestrator. The registered cfg is never changed; nothing under `ledger/` is written. `--cfg` variants and
  `cellscore` count toward the 60-variant cap; the report marks their scores `exact @<cfg>` and
  does not count them as solves.

* **`stage-cell <row> cand.c --cfg CFG --note "..."`** is the hand-over `cellscore` describes, done: when
  `cand.c` scores exact at CFG (`kitlib.score_at`, no ledger write) AND passes `kitlib.admissible` vs the
  lane's `base/` copy, it is copied to `out/<container>/<file>.c` with the base's `.base_sha` and
  `cells.jsonl` gets `{"id","to","coherence","pins_before","pins_after","rule2","kind"}` (the format
  `tools/fidelity/land_recipe_move.py` reads; a re-stage of the same id + cfg replaces its line). Rule 2 is
  scored too (the pinned text at CFG): `kind` is `recipe-switch` when it holds (byte-neutral), else `coherence`.
  Not exact or not admissible: refused, exit 1, nothing staged (the attempt is still journalled in
  `lab_log.jsonl`). `--note` (the coherence argument) is required. The output ends with the `land` command.
* **`stage-cell --equal-pins`** (round 81: three lanes hand-staged such moves) also stages a candidate whose pin
  count is UNCHANGED - only the "fewer pins" rule of `kitlib.admissible` is waived; more pins, a pin the base did
  not have, new `volatile` / `__asm__` / `ASM_*` / one-trip blocks and added gotos are still refused. The kind still
  follows rule 2 (r81_opus_fc4's 819C04E8 was equal pins with rule 2 FALSE: a coherence move). A candidate that
  IS the pinned text is a pure recipe switch: `land_coherence.sh` would journal it `noop` in
  `apply_candidates.py` and then restore the recipe, so the hand-over names `tools/fidelity/land_recipe_move.py`
  instead (dry run, then `--apply`; its target must be a stock recipe that splits addresses).

* **`baseline` first.** It scores the row's own pinned text, which is byte-exact by definition: the
  scorer must say `exact=true, total=0`. One lane's custom adapter silently mis-scored every
  baseline (103/45/16/50/31 instead of 0) and it was caught only because that lane ran this check.
* **Two-tier screen.** The cc1 listing (~15 ms) is compared with the pinned text's listing, which is
  retail's instruction order on a byte-exact row. `--score` sends only the distance-0 variants to
  the byte scorer (5-20 s each); `--score-top N` also scores the N nearest of the run. Lanes that
  solved rows sent 1-6% of their variants to the scorer.
* **Guards, before anything is written:** a variant with more pin sites than the base, or more
  `volatile`, is refused and logged as `refused`.
* **Substitutions** are `variants.json` exactly as `tools/xform/variant_screen.py` reads it:
  `{"name": [["old","new"], ...]}` applied in order to the pin-erased base, first occurrence only;
  `"@name"` starts from the pinned text instead. A pattern that is not in the text prints the three
  nearest lines, not a bare `AssertionError`.
* **Staging.** A variant that is listing-exact AND scores exact AND passes the admission gate
  (strictly fewer pins, the rest a subset of the base's, no new `volatile`/`__asm__`/`ASM_*`, no new
  one-trip block) is copied to `out/<container>/<file>.c` with its `.base_sha`. `--no-stage` to
  measure without staging.
* **Everything** - refusals, failed builds, pattern misses, and every `diff.py` run - is appended to
  `lab_log.jsonl`, and `lab.py report` builds the table from that file (a `via` column names the tool:
  `lab.py`, `lab cellscore`, `diff.py`, `diff.py --scorer`, or your script's `source`; an identical
  measurement repeated prints once with `(xN)`). A row of the lane with **zero** measurements is
  printed as `ZERO MEASUREMENTS`: one sol lane left two of its five rows untried and the report read
  exactly like "measured and still open".
* **Cap:** more than 60 variants on one row needs `--more`. One lane wrote 209 probe files for two
  of its five rows.

Python API, if you are scripting a sweep of shapes:

```python
import sys; sys.path.insert(0, "<REPO>/tools/lanes/lanekit")
from lab import Lab
lab = Lab("dungeon/func_8009612C")
lab.baseline(score=True)
lab.test("narrow_param", text, note="s16 parameter", score=True)
```

Scoring from your own script instead (`kitlib.score_at`)? Journal it, or `lab.py report` prints the row as
ZERO MEASUREMENTS (r81_fable_late measured 18 rows that way and its REPORT_TABLE showed none of them):

```python
import kitlib; lane = kitlib.bootstrap(); row = kitlib.row_of("town/func_808B2D90")
v = kitlib.score_at(row, text, cfg="2.7.2-cdk-G0", diff=True)   # score fields AND v["text"], the scorer's listing
kitlib.record_score(lane, row, "sym4", v, source="cellprobe.py", cfg="2.7.2-cdk-G0", text=text)
```

`score_at(..., diff=True)` returns `exact`/`total`/`subs`/`indels`/`status` (the summary score, the number
rosters store) AND `text` (the `--diff` listing; `diff_status` is that run's own status): two scorer runs in
parallel, merged - before round 81 the fields were all None with `diff=True` (the TOTAL inside the `--diff`
text is the GLOBAL-LCS distance, not the regional total, so it is not parsed). `record_score` writes one
`{"kind": "score", "source": ...}` record; `cfg` marks a foreign-cfg score (the report counts its exact as a
trade, not a solve). Journal kinds `baseline`, `diff-listing`, `diff-scorer`, `diff-score` do not count toward
the 60-variant cap; `record_score`'s `score` records do.

## diff.py, dump.py

```
python3 .../diff.py <row> <cand.c|erased|pinned> [--vs pinned|erased|FILE] [--ctx N] [--score]
                    [--cfg CFG] [--scorer [--norm-regs]]
python3 .../diff.py <row> cand.c --scorer --classify [--cfg CFG]
python3 .../prio.py <row> <cand.c|pinned|erased> [--cfg CFG] [--top N] [--all]
python3 .../dump.py <row> <cand.c|pinned|erased> <outdir> [--cfg CFG] [--pass sched|greg|lreg|loop|combine|cse|jump|all]
```

`diff.py --cfg CFG` lists/scores both texts at that cell (no ledger write). **`--scorer`** prints the byte
scorer's retail-vs-generated disassembly diff (`-` retail, `+` generated; what `cdkdiff.py` / `sd.py` did)
at the row's cfg or `--cfg`; **`--norm-regs`** first renames each side's registers by first appearance and
masks branch targets, so a pure register renaming disappears and only real differences remain (`adiff.py`).

**`--scorer --classify`** labels every differing region of the scorer's listing, with counts: **ORDER** (the
same instruction, moved - identical text outside the LCS, paired nearest first), **COLOUR** (equal once the
allocatable registers v/a/t/s/fp are renamed), **OPCODE** (a different instruction or constant) and
**COUNT** (an insertion or deletion). It names the residue's pass before anything is swept: ORDER = a
scheduler (`why.py --trace`), COLOUR = allocation (`why.py --pass greg`, `prio.py`), OPCODE = cse / combine /
loop. An exact text prints "nothing to classify".

**`prio.py`** prints, for ONE text at a cfg, the `global.c` allocation table in allocno order: pseudo,
variable, refs, live length, calls crossed, `floor_log2(refs)`, the priority
(`floor_log2(refs) * refs / live * 10000`, `alloc_sim.priority`), the rank that priority alone gives
(`!` where the dump's own order differs) and the hard register got (`--all` adds the local-allocation
pseudos). It is `r80_cell_c1b/prio.py`; `why.py --pass greg` is the two-text comparison.

**`regcmp.py <row> cand.c [--ref ref.c] [--cfg CFG]`** is a progress measure for big register rows, where the
listing distance moves in dozens of lines per allocno: it compiles the candidate and the reference (default the
row's src text), takes `prio.py`'s table and prints every C variable that got a different hard register
(`name: was -> now (refs/live=priority)`) and the count; unnamed temporaries are ignored. **`--subsets`** erases
every subset of the candidate's live pins (`kitlib.sites` / `kitlib.erase`, as `erase.py`; refuses above
`--max-pins`, default 8) and ranks them by that count, writing the texts to `regcmp/`. It is
`r80_opus_r2`'s `pcmp.py` + `combo.py`.

**`alloc_need.py <row> cand.c [--ref pinned|FILE|none] [--cfg CFG] [--json OUT] [--all]`** is the inverse of
`prio.py`: instead of "who outranks whom", "what would the numbers have to be for retail's colouring".  One `-dap`
compile and one byte score; each pseudo's RETAIL register is voted from the scorer listing (`.lreg` uid -> pseudos,
`-dap` uid -> generated word, colour-key alignment -> retail word, operand position), cross-checked against the
pinned text's named registers (`ref` column).  Verdicts: **BLOCKED** (retail's register is a hard conflict here: a
local qty / hard-register set / remaining ASM_REG holds it - a global-vs-local question, not priority), **CLASS**
(retail keeps it call-clobbered but it crosses calls), **LOCAL** (block-local qty, approximate numbers), **SPILLED**,
**ORDER**.  For ORDER it simulates every single-mover reorder with `alloc_sim.allocate` (fidelity printed first) and
prints each solution as the `global.c:587` inequality with all four single-term ways, e.g. on 8180A990
`120 (entity) must outrank 84 (object_or_kind): 120 refs >= 22 at live 82 | 120 live <= 81 | 84 refs <= 25 | 84 live >= 102`,
plus the `update_equiv_regs` doubling note (single set + REG_EQUIV doubles live; a second set halves it) and the
lever for the cheapest term.  Validated on the four round-80 hand derivations (80D3BFD0, 80921B2C, 8180A990,
80DE9000: same pairs, same thresholds, the tie-break included).  An inequality is necessary, not sufficient.
LOCAL verdicts are explained by `lreg_explain.py` (below) instead of the old "approximate" line, and BLOCKED
verdicts list the local qtys / hard registers that hold retail's register INSIDE the global's life (index overlap
in local-alloc's index convention applied to the global's set..death spans, with the setting insn - "which call's
argument set").  `--retail-set P=REG` (pseudo or variable name,
repeatable) supplies retail registers by hand for rows whose candidates the scorer cannot map.

**PREFERENCES (round 85, `prefs.py` + `tools/alloc_prefs.py`).**  `alloc_sim.allocate` used the greg dump's
`;; N preferences:` line, which is hard_reg_preferences AFTER pruning; find_reg also reads hard_reg_copy_preferences,
hard_reg_full_preferences and regs_someone_prefers, which no dump prints.  `alloc_need.py` now re-derives all of them
from the same compile's `.lreg` RTL / `.greg` conflicts / `.flow` RTL (one `-dap` compile, `.flow` added) and, ONLY
when the row has a preference effect, says so: (a) a mis-coloured allocno whose register a copy or plain preference
chose over the scan, (b) one whose retail register pass 0 skipped through regs_someone_prefers, or (c) a GR_REGS
allocno the replay puts in a GPR where `alloc_sim.allocate` (run without the allocnos global.c keeps in hi/lo) says
otherwise, while an ORDER mis-colouring exists.  LO/HI-class and reload-retried allocnos alone never fire it, so on
such rows alloc_sim's GPR-for-LO placement can still distort the search (a separate, older gap).  Then: ORDER becomes
**PREF** for (a)/(b), a `# preference replay` block prints the decision and provenance per mis-coloured allocno
(`DECIDED BY PREFERENCE $s0 (the scan alone gave $v1) <- merged from 90 at insn 275 r101 = r90 (90 dies here) <- insn
135 r140@$s0 = zero_extend(subreg(r90))`), why retail's register was not taken (taken by which higher-priority
allocno, skipped as someone's preference, a callee-saved retail register on a value that crosses no call, or the
free registers below it that something would have to take), and the single preference changes that give retail's
registers (drop one set_preference insn, one expand merge, every merge of one allocno pair, every tie of one allocno
to one hard register; an ADDED preference is listed last and is a lever only where retail already moves that value
through the register).  The mover search then runs on the exact model.  On rows without a preference effect the
output is byte-identical to before (`--no-prefs` forces that).  Fidelity (r85_opus_preftool, gdb oracle
`prefs_gdb.py`): every stage exact - set_preference / expand / prune sets, regs_someone_prefers, regs_used_so_far,
every find_reg result - on 89 texts / 1,563 allocnos (the five round-85 preference rows pinned + erased + their
lane candidates, 12 pin-free rows, 25 sampled pinned rows pinned + erased, 12 rows at 2.8.0/2.8.1), which exercised
79 preference overrides, 27 pass-0 someone_prefers skips, 18 alternate-class (LO_REG -> GR_REGS) retries and 2
caller-saves allocations (summed over the three battery runs).  Against the greg dispositions (reload-retried allocnos excluded) `alloc_sim.allocate`
was wrong in 24 of them: on GPR mechanics in 15, on LO-class allocnos in 13.  Not exercised: DI-mode allocnos,
local-alloc eviction, shared allocnos.  (`lreg_explain` calls `analyse()` too, so a firing row runs the replay twice.)
Reload's retry_global_alloc is not modelled (an allocno global left in hi/lo or spilled can move; marked).
`python3 <KIT>/prefs.py <row> <text> [PSEUDO|NAME ...] [--retail P=REG ...] [--all] [--oracle]` is the standalone
form (`--oracle` adds the gdb comparison).

**`lreg_explain.py <row> cand.c [--retail listing|none] [--retail-set P=REG] [--block B] [--pseudo P] [--all]
[--no-search] [--json OUT]`** replays gcc 2.7.2 local-alloc.c `block_alloc` (2.8.1's differs only in spelling)
on the insn stream of the `.lreg` dump: `insn_number` counts every non-note object; per insn the md template of
the printed `{pattern}` gives the operands for `combine_regs` (a tie, or a copy/arith suggestion when one side
is a hard register), then REG_DEAD deaths (2N), note_stores births (SET 2N, CLOBBER 2N-1), REG_UNUSED deaths
(2N+1), SCRATCH qtys; then the suggestion pass (`qty_sugg_compare`) and the priority pass (`qty_compare`:
`int(floor_log2(refs) * refs * size / (death - birth) * 10000)`; for 2 or 3 qtys the literal
`qty_compare(0,1)/(1,2)/(0,1)` replay, which is not always sorted) and `find_free_reg` (lowest free register,
no REG_ALLOC_ORDER on MIPS; call-used excluded across calls; $fp never).  Fidelity: all 6,328 compilable texts of
the tree (pinned + all-erased, 2.6.3 .. 2.8.1) reproduce every one of 230,725 local pseudos
(r81_opus_lregexplain).  Per mis-coloured qty it prints who held retail's register (a qty placed earlier - in the
suggestion pass or by priority - or a hard register and the insn that set it), whether retail's register is ABOVE
free ones (then each must be busy in retail: a GLOBAL allocno cannot do that, so "NOT A LOCAL QTY IN RETAIL" -
lever: a second block use / second death / call), and two exact searches: PRIORITY (one qty's refs or length in
the key, e.g. `qty 1 (101) refs >= 4 (now 2)`) and GEOMETRY (one qty's birth or death index, with the insn:
`qty 0 (107) dies at index 10 instead of 12: last use at insn #5 (uid 67)`).  A qty placed in the suggestion
pass cannot be outranked; retail giving two overlapping qtys the same register is a geometry question.
For GLOBAL pseudos (with `--retail-set` or the listing) it prints the local qtys / hard registers inside their life.

`diff.py` prints the listing diff `lab.py` stores as `experiments/<func>/<name>.diff`, for one file,
then the distance line. Every run is journalled to `lab_log.jsonl` with a `source` tag (kind `diff-listing`
with the distance vs pinned, `diff-scorer` with the byte score - `--scorer` now prints `# score {...}` too -,
`diff-score` for `--score`); `--no-log` writes nothing. `dump.py` is `kitlib.dumps` (the compile
`why.py` uses) writing `<outdir>/<stem>.<pass>` and `<stem>.s`; `sched`/`cse`/`jump` include their
second pass; `outdir` must be inside the lane.

## erase.py - what each pin holds

```
python3 .../erase.py <row>                       # lone + all + every pair (<= 8 pins)
python3 .../erase.py <row> --mode subset --budget 60
python3 .../erase.py <row> --variant experiments/func_X/v7.c
python3 .../erase.py <row> --variant cand.c --cfg "2.7.2-cdk-G0"   # byte totals at another cell
python3 .../erase.py <row> --with-scaffold [--mode pair|subset] [--budget 60]   # + volatile / one-trip blocks as sites
```

**`--with-scaffold`** (round 93; owner insight in `brief_paragraphs/fidelity_first.md`: pins fall TOGETHER with
decompiler scaffolding): every `volatile` qualifier (`VOL#n`, erase = delete the word, `*(volatile T *)` -> `*(T *)`)
and every one-trip block (`ONETRIP#n`: `do { } while (0)`, `while (0) { }`, `for (;0;) { }`; erase = drop the wrapper,
BODY keeps a bare `{ }` so its locals keep their scope; nested blocks are separate sites; braceless bodies are not
matched) becomes an erasable site after the pins, listed as `VOL#3 line 120`, and goes through lone / all / pair /
subset like a pin. Comments and strings are ignored; a site inside a pin's own span is skipped. With the flag the
pair set is not capped by `--pair-pins` (that would hide every pin x scaffold pair): it is the groups first (all pins,
all VOL, all ONETRIP, all scaffold), the pin-only subsets, then every pin x scaffold pair (`--mode subset` adds each
pin with a whole kind, and scaffold x scaffold pairs); `--budget` cuts from the end. The report ends with a "Pin +
scaffold groups that fall together" line when a mixed group's residue is no larger than its best member. Without the
flag nothing changes. (kitlib's `ONE_TRIP`/`BANNED` stay the admission-gate regexes; erase.py uses brace-matched spans.)

Prints, and writes `erase_<func>.md`: every site with its line, its pin, its statement and the
listing distance of erasing it **alone**; the distance with **all** pins erased; and the subsets -
every pair on small rows, plus the same-macro and same-variable groups (`joint_scan.subsets_of`,
reused rather than re-derived). A pair **FALLS TOGETHER** when erasing both leaves a residue no
larger than either alone (`duck_brief.fall_together`): those pins are one mechanism and one
candidate has to move all of them. `--variant` runs the same scan on a candidate you have already
written - which of the remaining pins is still holding it.

Listing distances only; the byte scorer is never called here; the ledger is never touched. With `--cfg CFG`
the pinned listing is not retail's, so each erasure is byte-scored at CFG instead (`r80_cell_c2`'s
`erase_cfg.py`; 4 threads, 5-20 s each, mode defaults to `all`).

## why.py - the pass-decision explainer

```
python3 .../why.py <row> --pass sched|sched2|greg|lreg|loop|cse|cse2|combine|flow|jump|jump2|rtl|dbr
                        [--variant FILE|erased] [--vs pinned|erased|FILE] [--around TOKEN] [--top N]
```

`--cfg CFG` compiles both texts at that cell (the round-80 `why_cfg.py` wrapper).

**One text at two cfgs** (round 81, r81_fable_late: "is this 2.8.x row really a 2.8.x row?"):

```
python3 .../why.py <row> <text> --vs-cfg B [--cfg A] [--pass P] [--around TOKEN]    # <text>: pinned, erased or a file
```

compiles the SAME text as if the row were registered at A (default the registered cfg) and at B, and prints the
same explanations with the sides named A and B. `--pass greg`/`lreg` read each side's allocnos with ITS cell's
FIRST_PSEUDO_REGISTER (a cell missing from alloc_sim.FIRST gets the "no FIRST_PSEUDO_REGISTER" message, the other side still prints);
`--pass greg` also prints reload's `;; Need N regs of class C (for insn U)` -> `Spilling reg R` rounds of both
sides and says IDENTICAL/DIFFERENT (insn uids ignored) - on 81910A9C erased, 2.8.0 needs HI_REG/HILO_REG/2 MD_REGS/
3 ALL_REGS and spills 9, 64, 65, 66 where cdk needs 1 LO_REG/1 MD_REGS and spills 9, 65 (r81_fable_late class S,
read by hand from two `dump.py` runs). Without `--pass` it prints the cross-cell listing distance and a per-pass
table of how many insns differ with every pseudo masked, and names the first pass that differs (81910A9C: `rtl`,
the 2.8 `addressof` of the address-taken parameter). `--vs` and `--trace`/`--deps` are refused with `--vs-cfg`.

**One text, one block, tick by tick** (round 80, `r80_fable_n1` read these by hand from the raw dump):

```
python3 .../why.py <row> --pass sched2 --block <N|bN|uN|rN> --trace [--variant F] [--cfg X] [--retail]
python3 .../why.py <row> --pass sched2 --trace --insn 781 --variant cand.c [--block ...]
python3 .../why.py <row> --deps 781 [--pass sched2] [--variant cand.c] [--cfg X]
python3 .../why.py <row> --pass sched --block bN --deps-table [--variant cand.c] [--cfg X]
```

* **`--trace`** compiles ONE text (`--variant`, default the erased text; `pinned` or a file) with `-dap` and
  prints, for the block `--block` names, the table in emitted order - `pos` (forward position), uid, `src`
  (INSN_LUID rank, from the previous pass's chain; `?` = not in that dump, e.g. prologue insns or sched1's
  split insns), static `prio`/`refs`, the tick it became `ready`, the tick it was `picked` and `why` - then
  every tick: the pick, its reason and the full ready list with dynamic priorities (`[launch U]` = a queue
  release). Reasons: `sole` (the only ready insn: always issued), `priority` (tagged `[launched: birthing
  boost]` in sched1 for `adjust_priority`'s 0x7f000001, `[tail: ...]` for the jump/call kept at the end),
  `hazard` (`schedule_select`'s `greater potential hazard`, with what the sort had first), `LUID tie`
  (equal priority, the higher LUID goes first: the statement-order lever), `class/stale-sort` (equal
  priority but the LOWER LUID won: `rank_for_schedule`'s dependence class, whose cost is not in the dump, or
  a list SCHED_SORT did not re-sort - the one checkable fact, whether the loser is a LOG_LINK of the
  last-scheduled insn, is printed), `tie` (a LUID is unknown), `stall` (every ready insn blocked).
* **`--block`**: plain `N` = an insn uid when some block holds it, else the basic block number (the header
  says which reading it took); `bN` block number, `uN` uid, `rN` retail word index (scores the text).
* **`--retail`** byte-scores the text and adds `gen` / `retail` columns: uid -> generated word (the `-dap`
  `# <uid> <pattern>` annotations, aligned to the scorer's disassembly on mnemonic with li/la/symbolic
  loads expanded - a model of the assembler whose coverage is printed; `-` = not placed) -> retail word (LCS,
  moved instructions paired by identical text). On an exact text the scorer prints no listing and it says so.
* **`--insn N`** narrows to one insn: its dependents (it becomes ready when the last of them is issued),
  the tick it became ready, what it lost at each tick and why, and the tick it was picked.
* **`--deps UID`** prints the insn's LOG_LINKS with their kind (true / anti / output) and the insns whose
  LOG_LINKS name it (its `ref_count` owners), at `--pass` (default `sched2`; any pass dump works).
* **`--deps-table`** (with `--block`, sched or sched2; round 93) is the whole block's dependence graph in one
  table, the thing r93_fable_c9858 assembled by hand: per insn `pos`, uid, `src`, static `prio` and `refs`,
  `deps on` (its LOG_LINKS; a bare uid is a true dependence, else `(anti)` / `(output)`), `depended on by`
  (long lists are cut with `,+N`), `birth` and `boost`.  `birth` is cdk `sched.c birthing_insn_p` evaluated from
  the dumps: the destination is a single-set PSEUDO (`reg_n_sets == 1`, counted over the dump's insns) that is
  live when the insn is picked - sched.c fills the block backwards and `bb_live_regs` holds the block's live-out
  set plus every source of the insns already picked, so "live" = used later in the block or live out (the flow
  dump's `Registers live at start`).  `boost` is what the scheduler did: `BOOSTED` = the insn sat on a ready list
  at a LAUNCH priority (adjust_priority), `tail` = a jump/call/use kept at the block end.  A footer lists any
  insn where the two disagree (the static test approximates; on the r93_fable_c9858 block 1 they agree on all 27
  insns).  After reload birthing is off, so `--pass sched2` prints `-` in both columns.

Smoke (r80_fable_n1's 819B3414 `g_seed` at 2.7.2-cdk-G0): uid 781 -> gen [180] -> retail [172], ready from
T-19 after 528, loses T-19 on priority, T-20 on `potential hazard` to 521, T-21..T-23 on priority, and at
T-24 is `sole` - the report's whole mechanism, in one command.

Two `-da` compiles (one per text; every pass comes out of each), then the decisions that differ:

* **`sched` / `sched2`** - per basic block: each insn's `priority` and `ref_count`, the scheduler's
  ready lists, the **source** order (`INSN_LUID`) beside the **emitted** order, and each insn's
  dependence links. `src` is read from the dump of the pass BEFORE the scheduler (`.combine` for
  sched1, `.greg` for sched2), because `sched.c` numbers LUIDs by walking that chain and the chain
  is *not* UID order - combine creates high-UID insns and splices them where the combined insn was
  (two such splices on the smoke row alone). gcc 2.x `sched.c` fills a block from the end, priority is the
  longest dependence path, and ties are broken by `INSN_LUID`: equal priorities with a different
  order means a **tie broken by statement order** (move the statement in the C); different
  priorities means a **dependence edge appeared or vanished** (the `deps on` column says which).
* **`greg`** - the allocno table: pseudo, variable name, `n_refs`, `live_length`, calls crossed,
  `global.c allocno_compare` priority, the allocno **order**, and the hard register each one got.
  Allocnos present in one text and not the other are printed first as **MISSING ALLOCNO** - a
  `register x ASM_REG("$19")` pin is exactly that, and every lower-priority allocno slides one
  register down the callee-saved sequence. The dump's own `Register dispositions` is the truth; the
  `alloc_sim` model's agreement is printed as a flag, not as an answer.
* **`lreg`** - refs / live length / calls crossed per named pseudo, and the **flow vector**: when it
  is identical, the two texts pose the same allocation problem and any register difference is
  allocno ORDER, not lifetimes.
* **`loop`** - each loop's real insn count and every movable's verdict (`moved` / `not desirable` /
  `not safe`) plus the biv/giv/unrolling diagnostics, aligned by position. A changed insn count with
  no changed decision is not evidence.
* **everything else** - a filtered insn-pattern diff of that pass's dump, pseudos anonymised by
  first appearance (raw UIDs and regnos shift the moment a pin is erased, so neither ever aligns).

`--around` takes a C variable name (resolved to its pseudo through `alloc_sim.decl_pseudos`), a hard
register (`$19`, `a0`), a bare pseudo number, `L<n>` for a source line (its variables are used, its
comment is not), or an RTL substring. Mapping an assembly line back to RTL is **not** supported:
name the register or the variable.

## checks.py - the four proof checks, per residue insn

```
python3 .../checks.py <row> cand.c [--cfg CFG]
```

One `-dap` compile and one byte score of `cand.c` (at `--cfg`: nothing written), the residue classified as
`diff.py --classify` does, and for every residue insn one verdict with the evidence line of each check that
applies (`tools/learnings/pin_removal_possibilities.md`, "Proof checks"):

| verdict | check | meaning |
|---|---|---|
| `OPAQUE-BASE` | (iii) | `ori` where retail has `addiu`, made by combine's PLUS->IOR on a pseudo with ONE set from a CONST_INT: the base must be opaque (multi-set, parameter, HIGH/load); order is irrelevant |
| `BARRIER-GOVERNED` | (iv) | a volatile asm (`ASM_KEEP`, ...) shares the insn's sched2/sched1 block: order experiments are inert while it stands |
| `NOT-REORDERABLE` | (i) / (ii) | sched2: retail has it earlier but it was issued as the lone ready insn or on priority; sched1: retail's "non-launched N after launched H" with no non-launched consumer of H below N and H not a load |
| `REORDERABLE` | (i) / (ii) | the deciding pick was a LUID tie (or H has the consumer the rule needs) |
| `UNKNOWN` | - | the dumps cannot decide: no uid (an assembler `nop`), COUNT/COLOUR residue, an unknown LUID, a hazard or class pick |

The precedence is the table's order; every check's evidence is printed, so a `BARRIER-GOVERNED` insn also
shows what (i)/(ii) would say once the barrier is gone. Directions use the drift of the nearest unmoved
word, so an indel earlier in the function does not flip "earlier" and "later". Smoke: both r80_fable_n1 rows
reproduce the report (819B3414 g_seed: 780/781 BARRIER-GOVERNED by ASM_KEEP uid 483, 781's (i) line = sole at
T-24; 800AFA68 a_t2: (ii) NOT-REORDERABLE, consumers 30*/41* launched, 49 above 44; c_nokeep_noreg: 19
OPAQUE-BASE `ori`s on pseudo 95 = 0x1f800000).

## dbr.py - why a delay slot holds what it holds (reorg.c)

```
python3 .../dbr.py <row> [pinned|erased|cand.c] [--cfg CFG] [--retail] [--insn UID ...] [--all] [--json OUT]
python3 .../why.py <row> --pass dbr --variant cand.c [--cfg CFG]     # the same replay, then the old two-text .dbr diff
python3 .../dbr.py <row> cand.c --no-gdb                             # static: fills + a notes-only prediction
```

Round 85: five lanes stopped on a delay-slot residue (r85_opus_m10 800C379C / 8009CCC4, r85_opus_m5 80B471EC,
r85_opus_p3 810ADDF4, r85_opus_fit2 800C379C) and one traced reorg.c under gdb by hand (fit2's
`tmp/gdb1/t*.py`, hard-coded cdk addresses). The `.dbr` dump holds only reorg's statistics and the final
SEQUENCEs - not one reason - so this tool runs the cell's own cc1 under gdb (batch mode, no prompts, `--timeout`,
breakpoints placed by `nm` address and argument order read from the cell's own `reorg.c`, nothing hard-coded),
logs every reorg routine's arguments and return value and replays them against reorg.c's control flow.

* **Table**: one line per delay insn: the slot (`.dbr`), `filled by` (`simple (calls|jumps) pN (backward |
  forward | target thread)`, `eager pN (fall-through thread | target thread | steal)`), and with `--retail`
  `retail slot | ours` (the scorer listing aligned through the `-dap` uids, retailmap). `(insn deleted by reorg)`
  = relax_delay_slots removed the jump.
* **Per slot** (`--insn UID`, `--all`; default: every empty slot and every fill_eager fill): each routine and pass
  that looked at it, each candidate in scan order with ACCEPTED / REJECTED / STOP / PAST and the reason:
  * `reads $v1, which 158 `andi ...` sets` / `sets $a0, which the call itself sets` - insn_references /
    insn_sets_resource_p against the `set` / `needed` of the insns it would move past, with the insn behind it;
  * `sets $a0, LIVE at the opposite thread 188 ...` - mark_target_live_regs, and per register WHY:
    `live entering the target (flow's live-at-start of block B, head ...)`, `first read by U before any set`,
    `ADDED by find_dead_or_set_registers at (use (insn 223)) - update_block's marker for 223 `move $4,$2`, moved into
    the delay slot of 225 `jal ...``, and whether the forward scan reached an unconditional jump (whose target's
    liveness is ANDed in) - the r85_opus_fit2 800C379C mechanism in one line;
  * `may trap (it accesses memory)` - may_trap_p: a load/store is never hoisted into a non-annulled slot from a
    thread; `redundant with U`; `not eligible: type load has its own delay slot (dslot=yes)` / `too big: length 2
    words` (get_attr_type/dslot/length called on the candidate) / `the annulled alternative is unavailable` (MIPS I);
  * `stop:` a label (labels end fill_simple's backward scan and the fall-through thread), a jump, an asm
    (`asm_input` - an ASM_* barrier is exactly this stop), an already-filled sequence; `not examined: ... this
    thread is not owned` (only the head of an un-owned thread can be taken; the branch is then redirected past
    the copied insn - `branch redirected $L40 -> $L63`);
  * `own_target / own_fallthrough`: own_thread_p, and if not owned WHY (`$L11 (used 2 times) sits before its first
    active insn`, `85 bne ... precedes it with no barrier`);
  * `mostly_true_jump = 0 (likely NOT taken): EQ test` - the value AND the rule that produced it, in reorg.c order:
    __builtin_expect (cdk), LABEL_OUTSIDE_LOOP_P, NOTE_INSN_LOOP_BEG before the target label (2), NOTE_INSN_LOOP_VTOP
    right after it (1; 2.x looks at NEXT_INSN(label) only), rare_destination fall-through minus target, EQ/NE/sign
    tests against 0, backward/forward; the facts are printed (notes before/after the label, both rare values) and a
    rule that disagrees with the real value prints `MISMATCH` (never seen in validation).
* **`DECIDING:`** (with `--retail`): when retail's slot word is one of our candidates, the refusal that kept it out
  (`retail's slot insn `move a0,s0` = our 164: REJECTED in fill_eager_delay_slots (pass 1): sets $a0, LIVE at the
  opposite thread`); when it is the head of a thread fill_eager never tried, the prediction that ordered the
  threads (`... = the head of our target thread (1056 `li $2,1`), which fill_eager never tried: mostly_true_jump = 0:
  EQ test, so the fall-through thread was tried first and filled the slot with 788 `lui ...``).
* **Trust lines**, every run: `trace faithful` (the traced compile's assembly is byte-identical to a plain compile -
  the attribute queries cannot perturb it; same rule as tools/alloc_trace.py) and `trace vs .dbr` (the fills the
  trace recorded = the `.dbr` SEQUENCEs; a difference is labelled as a later relax_delay_slots / pass-2 change).
* `why.py --pass dbr` prints this replay for `--variant` (default erased; at most `--top` slot sections, or the one
  `--insn UID`), then the filtered two-text `.dbr` insn diff it always printed.
* Cost: one plain compile + one gdb run, 2-17 s (a 300-insn function ~2 s, 810ADDF4's 89 slots 17 s).

**Cells.** 2.7.2-cdk, 2.8.0, 2.8.1: full, validated (below). 2.7.2 / 2.6.3: the trace and fills are verified
(`trace vs .dbr` all equal on a pinned row), but those cc1s have no separate find_dead_or_set_registers
(2.6.3 also no redundant_insn), so a LIVE reason stops at "live at the target". 2.91.66 / 2.95.2 (egcs): the
same routine names (resource.c), arguments read from their own signatures; fills verified on pinned rows (`trace vs
.dbr` 22/22, 24/24, 98/98) but the replay wording is tagged UNVALIDATED (egcs reorg.c differs in detail).
Module / partitioned slus rows: the unit that defines the function is traced (`--func NAME` if the row's
`true_name` is not the C name).

**Validated** (lane `r85_opus_dbrtool`, `validation/`): fit2's text for 800C379C at cdk reproduces fit2's gdb
finding uid for uid (trial 164 `move $4,$16` refused: $a0 live at the else target, added at `(use (insn 223))`,
223 in the slot of 225 `jal func_80099290`); m10's g3c gives the same mechanism and the DECIDING line; 8009CCC4 nb:
EQ -> 0, fall-through owned, `lui` taken, retail's `li v0,1` is the untried target head; 80B471EC: pinned stops at
the barrier's `asm_input` and copies `addu $2,$19,1` from the target (= retail), 1ec_nb takes the fall-through
(DECIDING: EQ -> 0); 810ADDF4: for-loop text VTOP -> 1 (target thread first, exact), do-while text EQ -> 0
(DECIDING). Exact pinned rows at 2.6.3, 2.7.2, 2.7.2-cdk, 2.8.0, 2.8.1, 2.91.66, 2.95.2: `trace faithful` and
`trace vs .dbr` all equal (8008F814 at 2.8.1: a call slot filled in pass 2 is emptied again by
try_merge_delay_insns - the table says `emptied by relax p2` and the slot's lines say into which slot it merged).
The rule replay of mostly_true_jump agreed with the compiler's value on every branch of every run (no `MISMATCH`).

## New extern symbols: no `.set` line

`kitlib.admissible` refuses any candidate that adds an `__asm__`, so a lane that declares a new data symbol
and pins its address with `__asm__(".set D_A0700104, 0xA0700104")` cannot stage it. **Do not add the `.set`:
declare `extern <type> D_<ADDR>[];` (or `func_<ADDR>`) and nothing else.** Both byte authorities resolve a
name that spells its own address at LINK time: the per-row scorer (`tools/gate/overlay_func_compare.py`,
`inject_name_encoded_symbols`: catalog entries first, then the address parsed from `D_`/`func_<ADDR>`, then
readable names through `config/names.tsv`) and the overlay window gate (`tools/gate/overlay_local_gate.py`,
`symbol_addr`, the same order). SLUS rows link the whole image: a `D_<ADDR>` must already be in
`config/generated/slus_006.14.undefined_syms.txt` or `config/slus_006.14.c_syms.txt` (grep both first); if it
is in neither, name it in the report - the orchestrator adds the `c_syms` line, lanes do not touch `config/`.

It is not always byte-neutral either way. MEASURED (r81_opus_kit2, town/func_808B2D90 pinned text, its
`.set D_A0700000` line removed): identical at the splitting cells (2.8.1 registered, 2.7.2-cdk: totals 0/0 and
18/18), but at the NON-splitting cells (2.7.2, 2.6.3) the `.set` makes the symbol an assembler-time absolute and
`la D_A0700000+0x104` expands to `lui; ori` instead of the relocated `lui; addiu` retail has (totals 7 with
`.set` vs 6 without at 2.7.2 and 2.6.3). An existing `.set` in the base is not refused (admissible counts growth
only): keep it unless you are measuring exactly this.

## Honest limits

* `--score` runs `tools/verify.py`, which scores inside `build_ovl/`. That is the one sanctioned
  write outside the lane, and the kit cannot and does not prevent it.
* The shim re-homes a compiler only when it would run at the repository root. It deliberately leaves
  the scorer's own compiles (which run in `build_ovl/` and in the candidate's directory) alone: a
  shim that forced every compiler into the lane would break scoring, including in grandchildren that
  inherit `PYTHONPATH`.
* `why.py --pass sched` needs the two texts to have the same block count; when they do not, it says
  so and points at `--pass jump` / `--pass flow`, because the scheduler is then not the first
  difference.
* The uid -> generated-word map (`--retail`, `checks.py`) is a mnemonic alignment of gcc's `-dap` assembly
  against the scorer's disassembly with a small table of assembler macro expansions, not the assembler
  itself; a word it cannot place prints `-` and a check without a retail position says `UNKNOWN`.
* `dbr.py` needs gdb (`/usr/bin/gdb`; `--no-gdb` falls back to the dumps: fills classified by where the slot insn
  sat in `.jump2`, prediction from the loop notes and the condition only). The conflicting register is NAMED from
  the dump's RTL (a static mirror of mark_set/mark_referenced_resources); the decision itself is the compiler's
  return value. The insn "behind" a conflict is the nearest one in the chain as it was when reorg started.
* `combine.py` needs gdb and binutils (`nm`, `objdump`); one traced compile takes ~10 s on a 2 KB function. It traces the function the row names (`--func` for another one in the unit); egcs (2.91.66 / 2.95.2) have 14 can_combine_p sites and their own chain: read their reasons with the printed condition, not the label.
* `--trace` reads gcc 2.6-2.8 `sched.c` commentary; the haifa scheduler of 2.91.66 / 2.95.2 prints another
  format and the trace refuses rather than guesses.
* `alloc_sim`'s `find_reg` model does not reproduce every disposition (30 of 38 on one smoke row).
  Read the `got` column, which is the dump.
* `--pass greg` / `--pass lreg` need `alloc_sim.FIRST`'s FIRST_PSEUDO_REGISTER for the cell, which
  covers every cell of the tree: 2.6.3 (67), 2.7.2 (68), 2.7.2-cdk / 2.8.0 / 2.8.1 / 2.91.66 / 2.95.2 (76 -
  `len(call_used_regs)` in each cc1, the `#define` in each mips.h; egcs added round 85: on all 10 egcs rows,
  pinned and erased, every allocno is >= 76 and the named pseudos resolve). A future cell without an entry gets
  a message saying so rather than a wrong table. `--pass sched` works on all of them (2.95.2 still prints
  `;; insn[N]: priority`), and falls back to the filtered RTL diff if a future cell does not.

## combine.py - why combine merged, or did not merge, a LOG_LINK chain (combine.c)

```
python3 .../combine.py <row> [pinned|erased|cand.c] --insn UID [--i3-only] [--cfg CFG] [--func NAME]
python3 .../combine.py <row> cand.c            # the refusal census (attempts per reason)
python3 .../combine.py <row> cand.c --list     # one line per attempt;  --all: every attempt in full;  --json OUT
```

Round 93 (asked for by r93_fable_c9858's RETRO: ~25 fixture compiles to learn what one breakpoint in try_combine
prints). UIDs are the `.flow` dump's (`dump.py <row> <text> <dir>`; combine runs on flow's output, and the `.combine`
dump no longer holds the i2/i1 a merge deleted). Each attempt prints the i3/i2/i1 patterns as try_combine saw them,
the outcome and, when refused, WHICH check and its combine.c line (2.7.2-cdk numbering):

| reason | site | meaning / lever |
|---|---|---|
| `can_combine_p(i2 or i1): use_crosses_set_p` | 943 | the insn's source reads a register set again, or MEMORY with a store/CALL (`mem_last_set`), between it and i3 - the line names the insn (`insn 501 (set (mem:HI ...))`). Move the store/call, or keep it there to keep the insns apart |
| `can_combine_p(..): crosses-call` | 943 | a CALL lies between (INSN_CUID < last_call_cuid) and the source is not constant (names the call) |
| `call-arg` / `call-src` / `used-between` / `libcall-end` / `no-conflict` / `self-copy` / `volatile-asm` | 943 | the other clauses of the same chain (the first TRUE one, in source order) |
| `volatile-between` / `volatile-src` | 1005/1013 | a volatile asm / unspec_volatile between (a volatile MEM is NOT one: volatile_insn_p returns 0 for MEM) |
| `dest-not-reg` / `hard-reg` / `two-sets` / `i3-clobber` | 981-995 | the insn is a store, a hard-register copy, a 2-SET PARALLEL, or i3 clobbers its value |
| `combinable_i3pat: ...` | 1439/1640 | i3 writes its output partly (subreg / strict_low_part over i2dest/i1dest) or kills two registers |
| `subst-fail: ...` | 1667 | subst gave up - `(clobber (const_int 0))`, a new pseudo, a new MULT |
| `no-recog (volatile MEM)` | 2081 | the merged pattern holds a volatile MEM: combine_instructions runs `init_recog_no_volatile`, so general_operand refuses it whatever mips.md says (the pinned base's volatile `lbu; sll 24; sra 24` bytes: `--insn 504` on dungeon/func_800C9858 pinned) |
| `no-recog (added sets)` | 2081 | i2dest/i1dest is still live after i3, so the merged insn is a PARALLEL that keeps the old SET too - and it matches no insn |
| `no-recog` | 2081 | the merged pattern matches no mips.md insn (every `recog_for_combine` call is listed: pattern -> code, -1 = none; the split path included) |

2.x combine has NO cost test: what reads as "not profitable" in this compiler is `no-recog`.

How it knows (`combine_gdb.py`): breakpoints only at addresses INSIDE combine_instructions / try_combine /
can_combine_p / combinable_i3pat - entry, the single `ret`, every `return 0;` site (`mov $0x0,%eax; jmp epilogue`
in the -O0 cc1, paired by order with the `return 0;` statements of the cell's own `toolchain/gcc-src/<cell>/combine.c`
ONLY when the counts agree, else printed `unmapped`) and the return address of every call those routines make (the
arguments at the call, `%eax` after it). can_combine_p's long `||` chain has one return site: the tracer decides it
clause by clause from the locals `src`/`dest`/`all_adjacent` (their %ebp slots read from the disassembly) and the
results of the calls that invocation made (`clause check: ok` = the decided call clause was the last call made).
Never an inferior call, never a write: `trace faithful` compares the traced assembly with a plain compile, and
`trace vs .combine statistics` compares attempts/successes with the dump's `;; Combiner statistics`.

**Validated** (lane `r93_opus_kit2`, dungeon/func_800C9858, 2.7.2-cdk; faithful, statistics 649/649 30/30 and
663/663 33/33): `best_k1b.c` - attempt `i3 432 i2 431 i1 430` COMBINED into `(sign_extend:SI (mem/s:QI ...))` = `lb`
(the 2-insn `431+430` before it: no-recog, `(ashift (subreg:SI (mem:QI)))`); `diag_storebetween.c` (Fable's dummy
`sh` between the `lbu` and the `sll`) - `i3 507 i2 506 i1 498` REFUSED, can_combine_p(i1 498, succ 506) chain clause
use_crosses_set_p, `a store lies between: insn 501 (set (mem:HI (plus:SI (reg/v:SI 129) (const_int 128))) (const_int
0))` - not 504, the volatile `lhu` that also sits there. Other cells: the site tables map on every tree cell (counts
agree), 2.8.1 ran clean on the same fixture (all clause checks ok), but the chain clause list is cdk's: the header
says UNVALIDATED.

## Switch jump tables: `jtbl-mismatch` and `--no-jtbl` (round 82)

The scorer compares a switch's jump-table CONTENTS with retail (`match.py local_table_diffs`). A text whose table
differs is rejected (`jtbl: local .rodata at 0x... word N: got 0x..., retail 0x...`) and has NO listing.

* `kitlib.score_at`, `lab.py`, `diff.py --scorer` report that as the status **`jtbl-mismatch`** with `jtbl` =
  `[{addr, word, got, retail}]` - not `build-fail/no-hex`. `lab.py report` shows it in the score column.
* **`--no-jtbl`** (`diff.py`, implies `--scorer`; `lab.py` files/`--subs`/`--grid`/`baseline`/`cellscore`;
  `kitlib.score_at(no_jtbl=True)`) scores and prints the listing with the table-content check OFF, so a real `switch`
  whose code is not exact yet can be diffed. INFORMATIONAL: `exact` is always False, `text_exact` says whether the code
  matched (printed "text exact, jump table NOT checked"), records are journalled as `text-exact-nojtbl` /
  `scored-nojtbl`, nothing is staged, `stage-cell` refuses it. `diff.py --no-jtbl` also prints the real scorer's
  verdict on the same text. `tools/verify.py`, the gate and match.py keep the check ON (nothing on disk is edited: the
  check is disabled inside a child process by `nojtbl_run.py`; overlay rows only).
* A text-exact `--no-jtbl` result still needs the table fixed (word index and got/retail values are in the
  `jtbl-mismatch` status of the ordinary run) before it can land.
- `counts.py FILE.c --row <id> [--cfg CFG]`: reg_n_sets per register at flow and at combine (what sched1 reads), plus each sched1 block's boosted and not-boosted ready insns. Use it when why.py tags a moved insn `[launched: birthing boost]` (r85_fable_birth).
