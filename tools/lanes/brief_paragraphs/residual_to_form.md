# Residual-to-form (A/B addendum against tonight's brief)

Read after `duck_pack_brief_v2.md`, before your first row. Four hard rules plus a stop rule, mined
from tonight's failures (`docs/evidence/lane_log_mining_gpt6_20260923.md`).

## 1. Name the residual, then aim one candidate at it

After erasing a coupled group (`erase.py`'s FALL TOGETHER), you get a nonzero listing distance. Do
not spend your next ten variants on that group's width/order/declaration spellings. Name the
residual first — the allocno rank, dependency edge, scheduler tie, or relocation artifact `why.py`
shows for that exact erasure — then write ONE source form engineered to remove that named thing.
**Why:** every mined row that measured a joint erasure and swept spellings around it stayed open;
the one full solve (`func_8032CE94`) named the residual ("a global register hiding two independent
source problems") and wrote one candidate per problem.

## 2. A plateau with a nonzero score means the listing screen is lying

If your best family sits at listing distance <= 4, is scored, and will not move, stop trusting the
listing screen. First write and score one absolute-load or symbol-relocation candidate (the numeric
address as `*(TYPE*)0xADDR`, or the already-declared symbol) even if it looks listing-worse; only
then return to the plateaued family. **Why:** `func_80819B14` was distance 0 at byte total 26 and
distance 3 at byte total 0 — "do not accept listing identity as proof." Two mined rows sat on an
identical `+addiu $2,$2,0` relocation residue all night without trying this.

## 3. An unchanged flow vector means ask the allocator, not the source

When `why.py --pass greg`/`lreg` reports the same refs/live/calls on both texts but a different hard
register, the allocator's own preference decided it, not a spelling. Run (path confirmed in this
lane's `TOOLS.md`), then test only the source change that flips its stated preference:

    python3 tools/alloc_trace.py <row> [--source cand.c]

**Why:** `record_alloc_trace.txt` ("preferences $a0 ... target-register-already-selected") named a
fix directly; this output was cited in only 1 of 10 mined sol6 lanes.

## 4. Thirty variants, no distance gain: stop permuting, add a local

After 30 variants of one width/order/declaration family with no distance gain, the next candidate
must not be variant 31 of the same family — it must introduce a fresh declared local at the value's
real lifetime boundary, where it is actually computed or first needed, not where the pin sat.
**Why:** the winning move on `func_800995D0` (a fresh `field_z`) and `func_8032FD1C` (a fresh
byte-offset temporary); no mined row added a new local after a plateaued sweep — all narrowed,
reordered, or widened the existing one instead.

## Stop rule

A row is not finished while its own report names an executable next measurement never run. If your
"What I would need to know" paragraph describes a specific trial, run it.
