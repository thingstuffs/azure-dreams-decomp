
## Round-80 harvest: try these FIRST where the signature fits

Opus lanes that led with these paid 5-109 pins each on 09-29. Every one is written up with its mechanism in
`tools/learnings/pin_removal_possibilities.md` (round-80 sections):

- **Clone family:** diff the row against pin-free and pinned siblings first (`diff.py`); if a sibling is the same
  function, transplant the canonical body (the xxx084 / TILE_1 family went 109 pins -> 0 that way).
- **Dead `lbu` reads pinned to scattered registers:** the source wrote the values back (`r = p->r; ... p->r = r;`);
  post-reload CSE deletes those stores after allocation (check: store in `.lreg`, gone in `.greg`).
- **abs():** same-register `bgez; nop; negu` or different-register `bgez; move; subu` is `v = abs(x)`.
- **movstrsi:** lw/sw triples off one base with $3/$4/$5 scratch = a struct assignment `dst = SYMBOL;`.
- **Parameters:** use them directly instead of pinned copies; declare at the element width (s16 params get a
  register conversion pseudo; s32 stack params stay tied to their slot).
- **Natural divisions:** hand-expanded shift/round sequences with pins -> write `/2 /4 /8` per stored field.
- **Integer pages with KEEP/KEEP_DEP:** use the typed symbol; a symbol argument on a local REASSIGNED between calls
  keeps retail's shared `lui` + per-call `%lo`.
- **Loops:** reorg inverse add after a back edge -> decrement first in the do/while; one-trip `do{}while(0)` blocks
  count as loops for calls.c's constant-argument pre-copy.
- **Allocation ties:** quote `prio.py` numbers (refs, live length - at cdk live comes from sched1's recount) and say
  what change would flip the tie; the kit's `checks.py` names order residues that no statement order can move.

**Tidiness (round 80, sol 6.1 texts):** do not add new `#ifdef NON_MATCHING` / `#ifndef NON_MATCHING` splits (edit an existing split in lockstep, or collapse it when both arms end up the same); delete a pin's comment together with the pin (no orphaned "still load-bearing" comments); no whitespace-only lines or empty `{ }` wrappers left behind.
