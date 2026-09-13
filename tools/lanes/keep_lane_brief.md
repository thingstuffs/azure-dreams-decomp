# Lane: keeps whose lone erasure is nearly exact (luna), @NROWS@ rows

Repo root: `@ROOT@`; run every command from there. Your directory is
`work/native_lane/@LANE@/`. Write ONLY inside it: that includes temporary `.c` files, compiler dumps, any
`cc1 -da` output and any redirected stderr (run such commands with this directory as the working directory;
never write files at the repo root). Never edit `src/`, never run git, never run gates, sweeps,
`pin_search.py` or `apply_candidates.py`.

IO discipline (the disk is shared): never grep/rg recursively over `work/`, the repo root or `@HOME@`.
Search only narrow directories (`tools/`, `include/`, `docs/`, one `toolchain/gcc-src/<version>/`, this
directory), and pass `--max-filesize 4M` to `rg`. When waiting on a process, wait on its PID, never on
`pgrep -f` of a pattern your own command line contains. CPU: at most 4 compiles in parallel.

## The family

`ASM_KEEP(v)` is `__asm__ __volatile__("" : "=r"(v) : "0"(v))` (`include/common.h`; `ASM_KEEP_NV` is the same
without `volatile`). It emits no instruction. It ends `v`'s known value: after it, `v` is the output of an asm,
a new value the compiler knows nothing about. Each row in `rows.md` names ONE keep whose lone erasure is
within a few instructions of retail, the scorer residue of that erasure, its class at combine, the pass where
the data flow first differs, and what the kept variable holds. Start from `base/<container>/<name>.c`.

What is known (round 19's keep lane, `work/native_lane/keep_astra/REPORT.md`, and `docs/PIN_MECHANISMS_20260912.md`
"Round 19"): erasing a keep restores an equivalence the compiler then uses, each at a named pass:
- a closed constant is substituted into its uses at the first CSE (`li; addu` becomes `addiu`);
- a copy is replaced by its source (CSE keeps the oldest equivalent register), so the copy's register vanishes;
- two equal loads fold into one; a dead load or arithmetic loses its consumer and disappears;
- known bits make an OR result and a truncated copy interchangeable; combine merges a call result's copy.
So retail's original C gave the compiler a DIFFERENT value there, or a different producer. Look for:
- a real join: the variable assigned different values on two paths (a phi the decompiler flattened);
- a different C type or width at the definition or the use (sub-word producers: `u8`/`s16` fields, masks);
- the value really read again (a second read of the field, through another pointer or type);
- a different expression or producer that yields the same bits (a symbol in place of a literal address, as
  `tools/xform/t54_pagebase.py` does for page constants and `t59_offsetsym` for a page plus an offset;
  `abs()` for a conditional negate, as `t16_absidiom`);
- where the variable is assigned (sinking a copy into the block that uses it, `t42_sinkcopy`; storing directly
  instead of through the local, `t38_unstage`; a local's width, `t37_localwidth`/`t37b_localwidth_keep`);
- a loop update moved after the statements that read the old value (`dungeon/func_800C72B4`, round 23).
Generators already try each of those ONE at a time on every row; these rows are where that failed, so expect
to need two changes together. Other pins may stay; only the named keep matters.

Round 23's keep lanes went 2 of 48: on most rows the few instructions left were an equivalence CSE is
entitled to use (a shared constant, a coalesced copy, a folded offset). Say so when you measure it, and name
the producer that would have to differ.

## Not allowed (census counts these like pins, so they remove nothing)

No new `ASM_*`, `__asm__`, `volatile`, fences, fake dependencies (`x = e + a; x -= a;`, `f(a + v - v)`, a dead
store), and no one-trip block: `do { } while (0)`, `while (0) { }`, `for (;0;)` or any block that runs once only
to change what the compiler sees. No NEW branch whose two arms hold the same code. Moving an existing keep to
another place does not remove it. No "impossible in C" verdict is accepted; report what you measured.

## Tools, budget, output

- Score: `python3 tools/verify.py <row_id> <absolute path to your .c>`; `--diff` for generated | retail.
- The compiler recipe is fixed per row (`cell` in `rows.md`); do not change it.
- About 25 scorer runs per row.
- An exact candidate goes to `out/<container>/<name>.c` (with `base/.../<name>.c.base_sha` copied next to it)
  ONLY if `verify.py` said `"exact": true` for that file AND it has fewer `ASM_*` sites than the base AND it
  adds none of the forms above. No comments about the erased pin in the output file.
- `REPORT.md`: per row, the result, the change, the mechanism, every direction measured; then the general rule
  (APPEARS / RESOLVES / how to recognise the population).
