# Lane: live fences (luna), @NROWS@ rows

Repo root: `@ROOT@`; run every command from there. Your directory is
`work/native_lane/@LANE@/`. Write ONLY inside it: that includes temporary `.c` files, compiler
dumps, any `cc1 -da` output and any redirected stderr (run such commands with this directory as the
working directory; never write files at the repo root). Never edit `src/`, never run git, never run
gates, sweeps, `pin_search.py` or `apply_candidates.py`.

IO discipline (the disk is shared): never grep/rg recursively over `work/`, the repo root or
`@HOME@`. Search only narrow directories (`tools/`, `include/`, `docs/`, one
`toolchain/gcc-src/<version>/`, this directory, `work/native_lane/codemotion/`), and pass
`--max-filesize 4M` to `rg`. When waiting on a process, wait on its PID, never on `pgrep -f` of a
pattern your own command line contains. CPU: at most 4 compiles in parallel.

## The family

@LIVE@ `ASM_SCHED_BARRIER` fences (zero-byte volatile asm, see `include/common.h`) remain live: erasing
one alone changes the bytes. The first scheduler (and the second) will not move an insn across a
volatile asm, so each fence holds some instruction order that retail has and the unfenced text does
not. Each row in `rows.md` names the fence to erase (a scheduling fence or a memory barrier, see
below) and the scorer's residue after that erasure (all are live; fences that die alone were
excluded). Start from `base/<container>/<name>.c`.

What is already known (read before starting):
- `docs/PIN_PATTERNS.md` section 9 and `tools/xform/t20_fencefree.py` / `tools/xform/natural.py`: a
  third of sampled fences stood for a natural shape m2c lowered into something else (a loop test
  increment, an if/else before a fenced call, a copy a fenced statement reads); `t20` searches those
  shapes. About 55% of the studied fences were pure barriers with no shape found. 123 of 151 fences
  removed in round 1 were dead leftovers of earlier agent lanes.
- Around the live fences (2026-09-13 census): store before / register work after 81, load before /
  register after 70, register / register 65, control / control 63, store / load 49, store / store 25.
  Only 13 fences have a `volatile` access next to them.
- The first scheduler's order is decided per basic block by insn priority (the longest dependency
  chain to the block end), then by original order. An empty volatile asm is a FULL dependency cut
  (every register and all of memory; `work/native_lane/sched_astra/REPORT.md`): no permutation of
  side-effect-free statements can stand in for a fence, only a changed dependency graph or CFG.
- Which pass a fence decides (a census of 150 fences, round 19): the first scheduler 71, delay-slot
  filling 31, combine 26, cross-jumping (jump2) 12, the second scheduler 9. Each row below names
  its own, with the reordered pairs when a scheduler decides.

## What the fence lanes found (fences2 to fences33: 50 of 293 rows exact; REPORT.md in each)

- Gotos into a shared return tail written as direct returns, the call before the return copied
  into each arm when needed (`town/func_800B3834`, `dungeon/func_800BB728`, `dungeon/func_80097AB8`).
- Condition polarity: `if (s != 0) { FENCE; return; } goto L;` became `if (s == 0) goto L;
  return;`. Which arm falls through is what the fence was holding (`dungeon/func_800ABD9C`,
  `dungeon/func_818F9B98`, `dungeon/func_818EDB60`, `dungeon/func_8008BCD0`).
- Direct stores in both arms of an if/else in place of a temporary stored after the join
  (`dungeon/func_80F87270`, `main/func_8001FAA8`, `slus/w_80040CBC`).
- A staged temporary (`t = p->f | K; ... p->f = t;`) written as direct field read-modify-writes
  (`dungeon/func_818BDB44`, `dungeon/func_8186F0C4`, `dungeon/func_800BB400`, `dungeon/func_80E07054`); a
  pointer temporary into a global array written as `D_X[i]` stores (`town/func_800AE09C`,
  `dungeon/func_800B7CFC`); a slot pointer built as `D_X + 0xFA` indexed by the slot (`dungeon/func_80CC2828`).
- `abs()` for a manual conditional negate (`town/func_800C2BFC`, `dungeon/func_8192365C`), and
  `F = abs(F);` for a field staged through a negated temporary (`dungeon/func_80E0F7C0`, now `t16b_fieldabs`).
- A decrement moved into the loop test (`dungeon/func_818B1484`, `dungeon/func_818B11B4`); a statement
  moved past the loop-back test (`dungeon/func_807B0B3C`); a counted `for` for a do-while
  (`dungeon/func_8028A5D8`).
- Staged flags or shift/add chains written directly (`dungeon/func_818BDD8C`, `dungeon/func_80C16F00`; now
  `t52_fencestage`); the branch after a call inverted (`dungeon/func_813284E4`); an inner test inverted into
  an early return (`dungeon/func_80095160`); a fenced dispatch test's polarity flipped so the other target
  falls through (`dungeon/func_8180A214`, `town/func_800C217C`, `dungeon/func_80090C24`).
- A keep moved after the store it guards or after the statement that follows it, the fence above
  dropped (`dungeon/func_80E91000`, `dungeon/func_818BDEBC`, `func_818C3B90`, `func_8197C800`; now
  `t57_keepafterstore` and `t57b_keepafternext`).
- One temporary reused for two copies (`dungeon/func_8196096C`); a reused local split into two
  (`dungeon/func_8008C504`); a pointer setup moved after its scalar producer (`dungeon/func_818B7F38`); a
  pure computation hoisted above the branch that used it (`town/func_800B6514`, `dungeon/func_818E6F98`); an
  initialisation moved into a shared block (`dungeon/func_80D3CBF8`); a positive-height arm duplicated with
  explicit stores (`dungeon/func_80BC1BA8`); an update duplicated into both arms of the next EXISTING test
  (`dungeon/func_80084084`); direct stores in an arm in place of a constant staged into a shared store tail
  (`dungeon/func_8102F83C`); a staged tile store written as one indexed store (`town/func_800B9CC8`).
- A page literal and its keep replaced by the symbol the file already names (`dungeon/func_8132B8AC`; now
  `t59_offsetsym` for a page plus an offset).
- Generators already try each of these ONE at a time with one pin erased, on every row. These
  rows are the ones where that failed, so expect to need two changes together, usually the
  branch structure around the fence as well. A `do`-to-`for` rewrite, tried on 120 rows, never
  helped: gcc compiles both the same. Only the fence matters here; other pins may stay.

## What has worked on neighbouring families (read the generator docstrings in `tools/xform/`)

- **Changing a compiler decision, not a spelling.** Loop notes (`t41_gotoloop.py`,
  `t44_doloop_greedy.py`), declared widths (`t36_paramwidth.py`, `t37_localwidth.py`), where a copy
  is assigned (`t42_sinkcopy.py`), storing directly instead of through a pinned local
  (`t38_unstage.py`). A dependency that changes an insn's priority changes the schedule.
- **Spellings do not help** (`t43_rewrite_greedy.py`: 1 of 1,467).

## Memory barriers

A row may name `ASM_MEM_BARRIER()`, `__asm__ __volatile__("" : : : "memory")` (include/common.h),
not a scheduling fence. A memory clobber orders memory accesses across it and makes CSE forget what it
knew about memory: a load after it is reloaded, a store before it is not merged with one after it. It
does not cut register dependencies. In the round-19 census 12 of 27 memory-barrier erasures first
differ at combine (CSE reused a loaded value or merged stores once the barrier was gone) and the rest in
the schedulers or delay-slot filling. So look first for what the original did to make the value be
read or written again: a second read of the field through another pointer or type, a store the original
made twice, a call between them, or a loop edge.

## What is wanted

For each row, find the natural 1997 C that gives retail's order without the fence. Compare the
fenced and unfenced `.sched` / `.sched2` dumps: which insns swap, their priorities, and what each
depends on. Then look for the source shape:
- a statement order that puts the moved insn in another block (a branch, a label, a loop edge);
- a real data dependency the original had (the value re-read after a store, an expression that
  reuses a result), which lengthens a chain and so raises a priority;
- a different variable structure (one variable reused for two values, or two for one);
- a pointer/array spelling that changes whether gcc's alias analysis lets a load pass a store.

If a mechanism resolves one row, try it on the others and state the rule as a generator could apply
it.

## Not allowed (census counts these like pins, so they remove nothing)

No new `ASM_*`, `__asm__`, `volatile`, fences, fake dependencies (`x = e + a; x -= a;`, `f(a + v - v)`, a
dead store), and no one-trip block: `do { } while (0)`, `while (0) { }`, `for (;0;)` or any block that runs
once only to change what the compiler sees. No NEW branch whose two arms hold the same code (a statement
copied into both arms of an EXISTING branch is fine). Moving an existing keep to another place does not
remove it. No casts that reuse a variable across unrelated types. No "impossible in C" or
"scheduler-owned" verdict is accepted; report what you measured.

## Tools, budget, output

- Score: `python3 tools/verify.py <row_id> <absolute path to your .c>`; `--diff` for generated | retail.
- The compiler recipe is fixed per row (`cell` column of `rows.md`); do not change it.
- About 25 scorer runs per row.
- An exact candidate goes to `out/<container>/<name>.c` (with `base/.../<name>.c.base_sha` copied next
  to it) ONLY if `verify.py` said `"exact": true` for that file AND it has fewer `ASM_*` sites than the
  base AND it adds none of the forms above. No comments about the erased fence in the output file.
- `REPORT.md`: per row, the result, the change, the mechanism, every direction measured; then the
  general rule (APPEARS / RESOLVES / how to recognise the population).
