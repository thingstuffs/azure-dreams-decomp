# Lane: register pins with a measured sufficient allocator knob (sol), @NROWS@ rows

Repo root: `@ROOT@`; run every command from there. Your directory is
`work/native_lane/@LANE@/`. Write ONLY inside it: that includes temporary `.c` files, compiler dumps, any
`cc1 -da` output and any redirected stderr (run such commands with this directory as the working directory;
never write files at the repo root). Never edit `src/`, never run git, never run gates, sweeps,
`pin_search.py` or `apply_candidates.py`.

IO discipline (the disk is shared): never grep/rg recursively over `work/`, the repo root or `@HOME@`.
Search only narrow directories (`tools/`, `include/`, `docs/`, one `toolchain/gcc-src/<version>/`, this
directory), and pass `--max-filesize 4M` to `rg`. When waiting on a process, wait on its PID, never on
`pgrep -f` of a pattern your own command line contains. CPU: at most 4 compiles in parallel.

## What is different about this pack

Every row here was already given to an earlier register pack and came back without an exact candidate. What
is new is a MEASUREMENT, not a guess: `tools/alloc_probe.py` erased the pin, ran the stock compiler under a
debugger, changed ONE allocator input in memory at the moment the allocator decides, and compared the final
assembly with retail. For each site in `rows.md` the knob(s) that were SUFFICIENT are listed: with that one
input changed and nothing else, the unpinned compile reproduces retail byte for byte. So the site is provably
a single-input allocation decision, and the question for you is narrower than last time: **which C spelling
gives the allocator that input?** Do not spend verifies on levers that move other inputs first.

Read the knob as follows (stock GCC 2.x local-alloc.c + global.c; `tools/lanes/alloc_lane_brief.md` has the
allocator model in full):

- `pref` / `copypref` (global): the value needs a PREFERENCE for retail's register, which the allocator
  records from a copy between the value and that hard register: the value is staged into a call argument
  register, read out of a return register, or tied to a hard register by an operation. Look at retail's
  register: `$a0-$a3` means the value is passed to a call in that position (an argument the current text
  computes into a temp, or passes as a different expression); `$v0/$v1` means the value is a call's return
  value or the function's return (a `return x` where the text returns a copy or a re-read); `$s*` with a
  preference means a copy at a call boundary. Make the copy real: the value itself must be the argument /
  the returned expression / the read of the return, without an intervening temp or re-computation.
- `sugg` (local): the same for a value that lives in one block: it needs a suggestion, i.e. a copy to or
  from retail's hard register inside the block (argument staging, return, a tied operand).
- `unconflict` (local or global): retail's register is held by another value while this one is live; the
  overlap has to end. Shorten or split the OTHER value's lifetime (a later definition, an earlier last use,
  a copy sunk to its consumer), or move this value's definition later / last use earlier. `rows.md` names
  the competitor when the probe could bind it.
- `order-swap`: this value must be allocated BEFORE the value that took the register (higher priority in
  the sort): more real references, a shorter live interval, a wider mode, or, for a genuine GLOBAL tie,
  the declaration order. For a local quantity, births decide, not declarations.
- `used-so-far-set` / `used-so-far-clear` (global): the allocator prefers registers already used in the
  function; which registers EARLIER real values occupy is the lever.
- `competitor-refs-1` / `competitor-unsugg` / `competitor-unpref`: the competitor, not this value, has to
  lose one reference / its suggestion / its preference.
- `force` alone (no input knob): the assignment is single-site but no one-input change was found; treat
  as an ordinary diagnosed row.

Also given per site: the allocator's own reason for the pinned register (the observer, as in earlier packs),
the erased distance in assembly lines, and whether the knob changed the allocator's decision. A knob that is
sufficient AND changed the decision is the strongest signal.

## Levers that have landed (same as every register pack)

Lifetime split, statement move, producer fusion, hostwide reuse, declaration order for a global tie
(`tools/xform/natural.py`, `t51_sched_order.py`, `t53_reg_state.py`), a type width change on the value or a
neighbour (the landed fixes for `order-swap` sites were mostly `register s32 x ASM_REG(..)` -> `u8 x` /
`s16 x`: a narrower mode changes the rank), an argument or return staged directly. Generators tried each
alone on every row here and missed; the earlier pack's REPORT is in its lane directory (named in `rows.md`)
and says what did not work: do not repeat it.

## Reading a candidate before you spend a verify

`python3 tools/alloc_trace.py <row_id> --source <your candidate .c>` prints the allocator's real inputs for
your candidate; `python3 tools/alloc_probe.py <row_id> --source <your candidate .c> --site N` re-runs the
probe on it (analysis only, ~2 s). If the knob is still sufficient on your candidate, your edit did not move
the input yet; if the probe says the site is exact with the pin erased, you are done and verify will agree.
`tools/verify.py` remains the only authority.

## Not allowed (census counts these like pins, so they remove nothing)

No new `ASM_*`, `__asm__`, `volatile`, fences, fake dependencies (`x = e + a; x -= a;`, `f(a + v - v)`, a
dead store), and no one-trip block: `do { } while (0)`, `while (0) { }`, `for (;0;)` or any block that runs
once only to change what the compiler sees. No NEW branch whose two arms hold the same code. Moving an
existing keep to another place does not remove it. No "impossible in C" verdict is accepted; report what
you measured.

## Tools, budget, output

- Score: `python3 tools/verify.py <row_id> <absolute path to your .c>`; `--diff` for generated | retail.
- The compiler recipe is fixed per row (`cell` in `rows.md`); do not change it.
- About 25 scorer runs per row.
- An exact candidate goes to `out/<container>/<name>.c` (with `base/.../<name>.c.base_sha` copied next to it)
  ONLY if `verify.py` said `"exact": true` for that file AND it has fewer `ASM_*` sites than the base AND it
  adds none of the forms above. No comments about the erased pin in the output file.
- End your final message with ONE LINE PER ROW: the row, the result, the change in one sentence, the knob
  and whether your change supplied it, the generator rule in one sentence, and what did not work.
- `REPORT.md`: per row, the result, the change, which allocator input you moved and whether the observed
  decision changed, every direction measured; then, for the pack, whether the knob was the right instruction
  (APPEARS / RESOLVES / RESULT) so the next builder can keep or drop it.
