# Lane: diagnosed register pins (luna), @NROWS@ rows

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

`ASM_REG("$N")` on a local declaration (`register s32 v ASM_REG("$4")`, `include/common.h`) is a hard
register binding: it takes the variable out of the allocator's competition and nails it to `$N`. It emits no
instruction. Every row here is a row whose retail bytes are reproduced only with that binding in place, so
retail's original C made the *allocator itself* put that value in that register. The rewrite you are looking
for changes an allocator input, not the arithmetic.

These rows are not guesses. Each pin site in `rows.md` was observed inside the stock compiler with a debugger
(`work/native_lane/alloc_astra/REPORT.md`, round 25): the quantity or allocno the pinned value becomes, its
references, live interval, calls crossed, preferences, the registers already taken when it asks, and the
decision the allocator actually made. `rows.md` gives you that per site, with the reason translated into the
lever it names. Start from `base/<container>/<name>.c`.

## The allocator model (stock GCC local + global allocation)

**Membership.** A pseudo that lives in one basic block and dies once can become a *local quantity*, allocated
first, block by block. Everything else that survives becomes a *global allocno*, allocated afterwards over the
whole function. Reusing one C variable for two real values merges their reference and death histories into one
quantity; splitting a variable into two separates them. A pin makes the value a hard register instead, so it
never enters the competition at all: erasing the pin puts a new competitor into it.

**Priority.** Within a pass, quantities are ranked by roughly `floor_log2(refs) * refs * size / live`, where
`refs` is the loop-weighted reference count, `size` the register size of the mode and `live` the length of the
live interval. So one more (or one fewer) *real* reference, a shorter lifetime, or a split that halves an
interval changes the rank. Adding a reference that does no work is not available to you (see "Not allowed") —
the reference has to be a real use.

**Suggestions outrank priority.** A copy to or from a hard register (an argument staged for a call, a return
value read, an arithmetic operand tied to a hard register) leaves a *suggestion* on the quantity, and
suggestions are tried before ordinary numeric rank. Round 25 measured this directly: in `town/800A10FC` the
callback pseudo had priority 3,333 and an arithmetic suggestion for `$2`; the address pseudo had priority
10,000 and no suggestion; the callback took `$2` first and the address had to take `$3`. A higher priority does
not win against a suggestion. Aliases that are coalesced away before allocation leave no suggestion at all.

**Conflicts and call masks.** A register is excluded, not merely disfavoured, when another live value already
holds it, when an earlier allocation took it, when it is fixed or the frame pointer, or — for a value whose
lifetime crosses a call — when it is caller-saved. Priority can never defeat an exclusion. The lever against an
exclusion is the *lifetime*: shorten it, split it, move a definition or a last use, move the value to the other
side of the call.

**Already-used registers.** Global allocation prefers a register already used somewhere in the function over an
untouched one, to avoid paying for another saved register. In the measured `818EC800` case the desired `$21`
was free and unblocked, but `$22` was already in the used set and won. So which registers *earlier* real values
occupy is itself an input.

**Numbering.** Equal ranks are settled by quantity or allocno number. Global allocno numbers follow pseudo
order, which follows declaration order — so reversing two declarations settles a genuine **global** tie, and
round 25's multi-cell fixture proved that (seven changed assembly lines in all five cells). Local quantity
numbers follow *births*, not declarations: reversing declarations changes pseudo numbers and nothing else for a
local tie. Where `rows.md` flags a **tie**, the competitor quantity and its priority are printed; the four
flagged sites are the only confirmed unsuggested equal-priority local conflicts in the population, and no
source rewrite for them has been found yet.

## Levers that have landed

- **Lifetime split** — one C variable carrying two real values becomes two variables, each with its own birth
  and death (`tools/xform/t51_sched_order.py`; the round-25 win on `dungeon/80285464` splits the data pointer).
- **Statement move** — an independent load or store moved across another, changing overlap and order without
  changing work (also t51; the same win moves a table load after an existing load/store pair).
- **Producer fusion** — a pointer load folded into its single consumer, deleting a user-variable lifetime
  (`80330560`).
- **Hostwide reuse** — a local promoted to function scope and reused for another real lifetime, changing
  membership and preferences (`natural.ALLOC_LEVERS`: `host_candidates`, `hostwide_candidates`,
  `unhost_candidates`, `declorder_candidates` in `tools/xform/natural.py`; the round-25 win on
  `dungeon/8187A9A8` removes a pin that way — same refs, same live length, same conflicts, a different *global
  preference*).
- **Declaration order** — only for a global tie, as above.
- `tools/xform/t53_reg_state.py` screens register-pin rewrites against the compiler's pass streams.

Generators already try each of those ONE at a time on every row in this pack, and failed. Expect to need **two
changes together** (a split *and* a move; a fusion *and* a reorder), which is exactly how both round-25 wins
were found. Other pins on the row may stay; only the sites named in `rows.md` are the target.

## Reading a candidate before you spend a verify

If `tools/alloc_trace.py` is present (it is being written in parallel with this pack; check first), you may run

```sh
python3 tools/alloc_trace.py <row_id> --source <your candidate .c>
```

to see what the allocator actually does with your candidate — the quantities it forms, their priorities,
suggestions, the registers occupied at each attempt and the register it hands out. Use it to tell "my edit did
not change any allocator input" from "it changed the input and the answer is still wrong": the first means try
a different lever, the second means you are close. It is analysis only. `tools/verify.py` remains the only
authority on whether a candidate is exact; an allocation that looks right is not a result.

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
- End your final message with ONE LINE PER ROW: the row, the result, the change in one sentence, the mechanism
  in one sentence, the generator rule in one sentence, and what did not work.
- `REPORT.md`: per row, the result, the change, the mechanism, every direction measured — and for each row say
  which allocator input you moved and whether the observed decision changed; then the general rule (APPEARS /
  RESOLVES / how to recognise the population).
