# Lane: @BUCKET@ (sol), @NROWS@ rows

Repo root: `@ROOT@`; run every command from there. Your directory is
`work/native_lane/@LANE@/`. Write ONLY inside it: that includes temporary `.c` files, compiler dumps, any
`cc1 -da` output and any redirected stderr (run such commands with this directory as the working directory;
never write files at the repo root). Never edit `src/`, never run git, never run gates, sweeps,
`pin_search.py` or `apply_candidates.py`.

IO discipline (the disk is shared): never grep/rg recursively over `work/`, the repo root or `@HOME@`.
Search only narrow directories (`tools/`, `include/`, `docs/`, one `toolchain/gcc-src/<version>/`, this
directory), and pass `--max-filesize 4M` to `rg`. When waiting on a process, wait on its PID, never on
`pgrep -f` of a pattern your own command line contains. CPU: at most 4 compiles in parallel, never more
than 8 processes at once.
@RETRY@
## The family: rows no instrument explains (@NEAR@ near, @FAR@ far)

Every other pack in this project is cut by FAMILY - keeps, register pins, fences. This one is cut by what is
NOT known about the row. That needs three sentences of background, because `rows.md` speaks in them.

**A pin and its residue.** Each `ASM_*` site in `base/<container>/<name>.c` (`include/common.h`) emits no
instruction; it constrains the compiler so that this function's bytes reproduce retail. Erase one site alone,
compile, and diff the listing against retail: that diff is the site's RESIDUE, and `d0` is its size in
listing lines. A small `d0` means the pin is nearly unnecessary - one C-level fact away.

**The fingerprint.** `tools/lanes/residue.py` reduces a residue to a key: a class (INVISIBLE / MOVED /
RECOLOURED / BOTH / CHANGED, by an order-aware test), a `d` band, the opcode multiset of each side (the
SHAPE, `-` retail and `+` the pin-free candidate) and the register pairs. `rows.md` prints all of it per site.

**A cause, and what a cause is NOT.** Round 33 took the ~5,400 byte-exact rows that need no pin at all,
applied ONE m2c-style source move to each (an entry copy of a parameter, an address literal for a symbol, a
declaration reorder, a width change, a hoist into a temporary, a lifetime split or merge, two adjacent
statements swapped, a `while` written as m2c's goto loop ... 16 kinds, each a generator's move REVERSED),
compiled it and fingerprinted the residue. A pinned site's CAUSES are the kinds whose residues carry the same
fingerprint, ranked by share. That is a statistical match on a residue, not a diagnosis: on the rows a
generator actually landed, some catalogue kind reproduced the pre-landing text only 45% of the time. So every
cause in `rows.md` is labelled **a compatible mechanism, not the move**. Treat one as a hypothesis to TEST
first and cheaply - never as an instruction, and never as a reason to stop looking elsewhere.

**Why these rows are here.** The catalogue explains 56.5% of the near band (sites within 4 listing lines).
These rows are its failures:
- an **UNEXPLAINED-NEAR** row has a site within 4 lines of retail, and not one of its near sites is covered
  by the catalogue at all. Something small and nameable is missing from the source and no measured move
  produces it.
- a **FAR** row has no site within 4 lines. Round 33's negative control measured that beyond d = 4 the key
  covers the catalogue's own other half at 41 / 13 / 2 / 3% (bands 5-8 / 9-16 / 17-32 / 33+), so nothing can
  be said about the shape - `rows.md` prints the class and shape for a far site and NO cause, deliberately.
  A far pin usually means the pin holds a whole region together: the function's structure, not one statement.

Generators have already tried their moves one at a time on every row here and failed; the CPU search is
menu-limited (one lane-won text in nine is reachable at depth 2). What has never been tried on these rows is
**the rewrite only a model makes**: read the whole function, decide what C a human would have written, and
write that - a different control shape, a different set of variables and lifetimes, a different join, a
different type at the definition, statements grouped into the order the work really has. Two changes together
are the norm among the wins that landed; one change at a time is what already failed.

## What is already measured, so you do not re-derive it

`rows.md` prints the MEASURED NEGATIVE under each site whose class or cause has one. They are real
measurements over whole populations, each from `docs/PIN_MECHANISMS_20260912.md`:
- **the parameter-copy class (t69_prologue)** - the residue is decided at `greg`, before any scheduler runs:
  the candidate emits the merged parameters' entry copies in parameter order where retail has body copies in
  declaration order. Which copies retail's C had as PARAMETERS is the question. Every register and ordering
  lever is at 0 (round 34).
- **the address / page-base class (t29 / t54 / t59)** - respelling the address is spent: `T29_SYMDEF` 164
  candidate rows -> 1 pin, `T29_NONRAM` 0 of 37, the copy-drop composition 0 at 0 on 97 rows, t54 at four
  times its verify budget 0 of 40. The residue after a correct respelling is allocation and schedule (round 34).
- **the scheduling / statement-order class (t51)** - on 60 sites where t51's own independence test allows the
  move the residue names, 0 reach distance 0, and 312 of 402 sched-moved sites move three or more
  instructions: it is a REGION reschedule (round 31). A single statement moved is measured and negative.
- **RECOLOURED / BOTH residues** - 516 of the 898 uncovered near-band pins are allocation choices no single
  text move produces (round 33). Read the allocator model below before proposing a spelling.
- **INVISIBLE** - 21 of 6,480 sites only; the residue is assembler-side, not a C question (round 30).

The allocator model, in four lines (round 25, measured under a debugger): a pseudo living in one block and
dying once becomes a local QUANTITY, everything else a global ALLOCNO; priority is roughly
`floor_log2(refs) * refs * size / live`; a copy to or from a hard register leaves a SUGGESTION that outranks
priority; a register held by another live value, taken by an earlier allocation, fixed, or caller-saved for a
value whose lifetime crosses a call, is EXCLUDED and no priority defeats it. The lever against an exclusion is
the lifetime: split it, shorten it, move a definition or a last use. `python3 tools/alloc_trace.py <row_id>
--source <your candidate .c>` prints what the allocator actually did with your candidate (analysis only).

## How to spend the row

1. **Read the whole function first** and say what it is doing. These rows are not one-liner fixes.
2. **Test the named hypotheses first** - the causes in `rows.md`, cheapest first. They are cheap precisely
   because they are named; a hypothesis you TEST and refute is a result worth writing down.
3. **Then the whole-function rewrite.** Change the shape, not the spelling: a join the decompiler flattened, a
   loop written the way the source had it, a variable carrying two lifetimes split in two, a value read from
   where it really lived, an early return instead of a flag, a helper's arguments in a different staging.
4. Hypotheses are to be TESTED, not assumed. `tools/verify.py` is the only authority; an explanation that
   looks right and does not verify is not a result.
5. **An unreachable class is a finding.** If a row cannot be reached, say exactly what you measured, what the
   remaining difference is, and what would have to be different in the compiler's input to produce it. That
   verdict, with its evidence, is worth as much as a landing - but "impossible in C" with no measurement is
   not accepted.
6. You are free in approach: any C the rules below allow, any order of rows, any tool you write inside this
   directory.

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
- A candidate that removes SOME of the row's pins and verifies exact is a win: write it out.
- End your final message with ONE LINE PER ROW: the row, the result, the change in one sentence, the mechanism
  in one sentence, the generator rule in one sentence, and what did not work.
- `REPORT.md`: write it BEFORE you build anything (the plan and the first readings) and refresh it hourly. Per
  row: the result, the change, the mechanism, every direction measured and what it cost, and whether the
  catalogue's cause was compatible with what you found. Then the general rule (APPEARS / RESOLVES / how to
  recognise the population) and a closing summary: which rows are unreachable and why, what tooling you built
  worth keeping, and what you would do next.
