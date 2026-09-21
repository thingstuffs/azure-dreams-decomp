# Rounds 62-63 (2026-09-21): rubber-duck briefs, astra on whole families, generators from its answers

Start: 5,580 pins / 1,154 rows (round 61's close, [round 60-61 note](PIN_RESEARCH_ROUND60.md)).  At this checkpoint
(03:55Z): **5,463 / 1,139**, every landing gated (covering windows + SLUS MATCH).  Owner's direction (2026-09-21): the
session architects and decides from the data, Opus does the bounded work, every model pack carries a rubber-duck brief per
function, astra or sol on whole functions or on mechanisms - either is good.

## What the data said, and the pipeline it produced

A fresh lone-erasure census (5,582 sites) ranks the residue classes: `MOVED|1-2 -move` 173 sites, the prologue
`-move,sw` pair 95, the address-constant class (`lui/addiu` vs `lui/ori`) 209 sites in 119 rows, unaligned `lwl/lwr`
copies 88 sites in 21 rows, the item-target shape 25 rows, one row with 36 `ASM_USE_NV(angle)` (a reference-count pump =
the allocation-order rule).  Retries do not pay (sol on Gemini's mid-class misses 0 of 15; the wider scorer fallback 0);
mechanism-to-generator does.  The pipeline now: **census class -> five clean rows, duck-briefed, with the class question ->
astra -> Opus turns the answer into a generator -> tree sweep -> land in the gaps between codex lanes.**

## Duck briefs (`tools/lanes/duck_brief.py`, `build_class_pack.py --duck --rows`)

Per row: STATE (each pin, its note, its lone-erasure class and changed lines; the joint picture - all pins, and pairs up to
five pins: which fall together), KNOWN (mechanism hypothesis per pin, each generator's verdict on this row from the sweep
journals, the allocation simulator's verdict, earlier lanes' measured distances), NEEDED (what must change, whether the
pins must fall together, what is unknown).  The pack prompt makes the model restate the duck first and answer it in its report.

## Astra on the two bounded clone families: 5 of 5 in fifteen minutes

`r62_astra_families` (item-target 3 rows, raw-height 2; sol and hand probes had bounded both).  One idea, **lifetime
merge**: the call result and the next value live in ONE variable, so the second inherits the first's pseudo - its register,
and the ordering dependence of overwriting it.  Item-target: `value = (s32)call(); store = (void *)value; value = load;`
(astra wrote a union; the cast form is exact too and is what the generator prefers) - the keep goes, the two `lb` loads stay
after the store in `$2/$3`.  Raw-height: the pinned `u32 raw_height` hosted on the dead `u16 part_flags`: width and
allocation priority change together.

**t87_lifetimemerge** (Opus, from astra's report): 5 of 5 exemplars, the item-target class 15 of 15 rows whose store is
volatile, 0 of 10 whose store is a plain member (there the first lifetime is forwarded into the store and the merge is a
listing no-op: a separate astra question, pack `r63_astra_itemnv`); tree sweep 384 eligible, 24 rows, 25 pins; forms: cast
16, rename 4, hoist 2, narrow 2, union 0.  One merge per row per pass; passes 2-3 re-sweep after landing.

## Two class generators (Opus)

**t86_symaddr**, the address-constant class: symbol spelling x position x stock cell, an `la`-count prescreen, recipe
switches only where `pin_cells_land` rules 1-3 hold.  528 eligible, **22 rows, 44 pins**, six switches to the splitting
2.7.2-cdk cell (recorded in `ledger/recipe_trades.jsonl`).  Findings: the cell is the binding constraint for non-splitting
rows; naming a PAGE symbol at a splitting cell can never match (a spurious `addiu r,r,0`), the symbol must be named at the
offset address; the 27 rows where the listing looked exact at cdk are not landable (0 of 27 byte-exact: where the pinned text
is not retail at a cell, its listing is no target) - three of them are 1, 4 and 6 words off and want a scorer-guided search.

**t78_aggcopy, page copies**: the `lwl/lwr` rows are not scalarized copies; they hold a page constant and a derived pointer
feeding an existing block copy.  Naming the object (`*(Copy32 *)&dst = *(Copy32 *)&D_80024028;`) is byte-exact at the cdk
cell.  gcc's `expand_block_move` only distinguishes alignment >= 4 from < 4.  3 rows, 8 pins; lead `dungeon/func_8187C45C`
(41 pins) at distance 1: four page runs share one `lui`, so they must be rewritten jointly on one page-struct symbol.

Landed together: 5,575 -> 5,500 (75 pins with the cascade), then t87 and the astra rows -> 5,463.

## Chain H (sol): retries and the never-served far band

Gemini-only mid rows 0 of 15 (stopped); Gemini-only MOVED/CHANGED-small 1, 1, then a third slice; never-served far band
at 1-3 pins 2, 1, 1 rows per slice.  Thin, as the round-60 data predicted; it runs to its stop rule.

## Queued

Chain I (astra): the five biggest never-served rows (51-40 pins), then the allocation family (the 36-pin row and three
study near-misses with `r61_alloc_study/NOTE.md`).  Chain J (astra): five class-family packs with the class question
(`-move` placement, constant loads, memory loads/shifts, the prologue pair, recolourings).  Chain K: the plain-store item rows.

Spelling trades to revisit (owner: acceptable when documented): the labelled dispatch row (round 60), two empty `if` arms
from t82, the `(s32)`/`(void *)` casts of the lifetime merge (a 1997 author may simply have reused one `int`).
