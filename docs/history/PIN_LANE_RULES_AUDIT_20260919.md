# Lane rules versus generators: the audit (2026-09-19)

Source: the "general rule" sections of 128 lane reports (236 `REPORT.md` under `work/native_lane/`, 819 per-row verdict lines) read against the opening docstrings of the 68 generators in `tools/xform/`, by an Opus agent (about 150k tokens; the digest lives in `work/native_lane/r58_opus2/`). Rank = independent lanes proposing the rule x how mechanical it is (regex 3, small parser 2, model 1).

## Rules the lanes proposed that no generator implements, or implements narrowly

| # | gap | lanes | shape -> change | nearest generator, what it lacks | mechanical |
|---|---|---|---|---|---|
| 1 | multi-set destination / in-place accumulator | 6 | `T v = a+b+c;` -> `T v = a+b; v += c;` (also `v <<= 5` before use): the destination pseudo becomes multi-set, `birthing_insn_p` stops boosting it, the scheduler leaves it put | `t69_prologue` knows the mechanism (`reg_n_sets == 1`) but only deletes parameter copies; `t35_shiftspell` flips one operator, never splits a chain | regex |
| 2 | arm-specific store sinking paired with fence erasure | 8 | a staged temp assigned per arm and stored once after the join -> each arm stores itself (or a field RMW), fence erased | `t67_tailform` duplicates an identical run; `t52_fencestage` rebuilds stores only straight-line around a fence | parser |
| 3 | callee signature/arity repair (narrowing) | 5 | `func(fake_arg)` with `ASM_REG("$4")`/`ASM_SET` -> `func()` and a `(void)` prototype; or a wrapper's pass-through argument restored | `t8/t8b_passthru` only add arguments; nothing removes one or edits a prototype down. Caveat (t70): a scorer-exact prototype change was once withdrawn because another caller could not adopt it; the per-row gate does not see other callers | regex |
| 4 | reference-count nudge across the priority window | 5 | two allocnos tie on `floor_log2(refs)*refs/live`; add a real reference (`v = (u8)v;` before a byte store, route a call result through `v`) or lower the competitor's | `t65_regroute` knows `allocno_compare` but only moves copy suggestions and allocno order; the windows are computable from the `-da .lreg` dump | parser |
| 5 | label-as-call, non-epilogue sites | 6-7 | thread-filled target -> label on the statement at target-4 + plain `goto`; loop-head pseudo-call -> label + backward goto after one-time setup; shared join -> goto the existing return label | `t10_epilogue` handles `kind == "epilogue"` only; `t3` leaves mid-row sites "for a later transform" | parser |
| 6 | return the kept local | 4 | non-void function, success path ends `return;`, a `$v0`-pinned dead local holds the result -> `return result;` | `t48_gotoreturn` converts gotos to returns, never introduces a return value (r36: the bare-return population may be exhausted) | regex |
| 7 | dead formal as host | 5 | a parameter dead early carries a later same-type value; the entry copy leaves a hard-register preference | `natural` HOST / `t60` reuse disjoint locals, never a formal | parser |
| 8 | aggregate assignment | 5 | a run of scalar field copies covering a struct -> one typed `*d = *s;` | `t4_fields` builds the struct types but never merges the copies | parser |
| 9 | sink a definition past the last call on every path | 5 | a value initialised before an unrelated call -> path-local definition after each path's last call | `t42_sinkcopy` is the narrow corner: parameter copies, one block, no per-path duplication | parser |
| 10 | symbol <-> constant provenance | 4 | retail's second word decides: `addiu` -> a symbol, `ori` -> a constant; `page+off` -> `symbol[index]` | `t29/t54/t59` go integer -> symbol only; nothing spells a symbol back as a constant or reads the retail word to choose | regex+ |

Below the cut: duplicate switch targets and cases that `goto` retained labels (`t73_ifswitch` builds from an if-tree only); producer fusion at all sites jointly for an anchor pin whose preference is broadcast (alloc30: "this should be a generator"); cross-type host reuse with casts at consumers; argument-embedded assignment `f(a, cur = g(...))` (a model's job).

## Implemented, proposed by several lanes, paid little: the rule was wrong or too narrow

- `t43_rewrite_greedy` 1 of 1,467 rows against polarity/arm swaps proposed by six lanes: polarity alone is wrong; every lane win paired it with a block-membership change (a direct early return, an arm-local store).
- `t51b_pairs` 0 of 787 against "two coupled changes" in ten alloc lanes: the lanes paired rewrites, t51b paired erasures.
- `t62_regfamily` 0 of 186 against `t66_sameregmerge` 7 of 9: the same unit (the same-register family), the wrong operation (erasing asks the allocator for a new decision; merging asks for one fewer).
- `t51` fuse 5 of 61 against eight lanes proposing producer fusion: implemented as "the next statement's sole use"; the lanes fuse non-adjacently and through the real consumer.
- `t37_localwidth` 1.4%: width alone is unsafe wherever the load/store mode is observable; it pays paired (`t70`, both ends, 15 of 164).
- `t42_sinkcopy` 9 of 125: the narrow corner of a sink rule four lanes state generally.

## Application or expression?

Both, unevenly. The mechanisms are known to the point of prediction (alloc48: every solved row was called from `.lreg`/`.greg`/`.sched` before a scorer run). What the lanes keep reporting is that the winning move is a composition whose first step looks worse (alloc19's `func_8009A61C`: fusion + host reuse + an abs idiom, none alone enough; t53's win: a width change that worsens assembly distance but improves the pass-stream distance, then a fusion). Single-shape textual rewrites cannot express that, and `t27`'s beam already composes to depth: its limit is the screen, which ranks the correct first step below a cosmetic one by assembly distance. The tool indicated is a compositional search over declaration-level atoms (`varset.py`'s inventory: RETYPE, SPLIT, INLINE, MERGE, plus host/formal reuse and prototype edits) ranked by pass-stream state (allocno priority windows, conflict sets, ready-list ranks from `-da`) rather than assembly distance, with the whole-function joint move as the unit. The inexpressible residue the lanes name (reorg delay-slot theft, LUID tie inversion, leaf-function scan order, keeps that hide a value from CSE with no allocation or order lever) is real but small.

## Actions

1. Gap 1 as a generator (`t74_multiset`), listing-screened; 2. gap 6 (`return` of the kept local) as a small generator; 3. gap 10's reverse direction (symbol spelled as a constant when retail's second word is `ori`); 4. the pass-stream screen (ready-list ranks and allocno windows from `-da`) as the ranking for a compositional search, replacing assembly distance for the first step. Gaps 3 and 4 need care (other callers; pin-for-pin trades are not charter-legitimate).
