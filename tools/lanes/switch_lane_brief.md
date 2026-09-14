# Lane: computed-goto dispatches as honest `switch` (@MODEL@), @NROWS@ rows

Repo root: `@ROOT@`; run every command from there. Your directory is
`work/native_lane/@LANE@/`. Write ONLY inside it: that includes temporary `.c` files, compiler dumps, any
`cc1 -da` output and any redirected stderr (run such commands with this directory as the working directory;
never write files at the repo root). Never edit `src/`, never run git, never run gates, sweeps,
`pin_search.py` or `apply_candidates.py`.

IO discipline (the disk is shared): never grep/rg recursively over `work/`, the repo root or `@HOME@`.
Search only narrow directories (`tools/`, `include/`, `docs/`, `config/overlays/`, this directory, the two
report directories named below), and pass `--max-filesize 4M` to `rg`. When waiting on a process, wait on
its PID, never on `pgrep -f` of a pattern your own command line contains. CPU: at most 4 compiles in parallel.

## The family

317 src files spell a `switch` as a computed goto. `work/maspsx_jtbl/REPORT.md` proved why, and proved it
is no longer needed: our assembler front end (maspsx) rewrote a compiler-LOCAL (`$L...`) jump-table indexed
load into a 5-word base-materialised sequence, where retail -- and genuine ASPSX 2.56, 2.67 and 2.79 --
have GNU as's ordinary 4-word `$at` macro:

```
retail / ASPSX / fixed maspsx   sll v0,v1,2 (delay slot) | lui at,%hi | addu at,at,v0 | lw v0,%lo(at)
the old maspsx rewrite          lui v0,%hi (delay slot) | addiu v0,v0,%lo | sll v1,v1,2 | addu v1,v1,v0 | lw v0,0(v1)
```

One word longer, so every later word of the row shifts by one. A GLOBAL table dodged the pass, which is why
the tree spells the dispatch as

```c
    static void *const state_labels[] __attribute__((used)) = { &&case_0, &&case_1, ... };
    register s32 dispatch_a1 ASM_REG("$5");
    ...
    value = st->state;
    if ((u32)value >= 7) { goto done; }
    goto *D_80526454[value];
```

The pass is being fixed to a no-op, and then the honest spelling reproduces retail: at 2.6.3/2.7.2/2.7.2-cdk
gcc emits the macro form directly; at 2.8.0/2.8.1 gcc splits the table address itself unless the cell carries
`-mno-split-addresses` (see "The 2.8.x cell rule"). Four rows already landed as real switches with **zero**
pins and their own `.rdata` jump table -- read them before you start, they are the whole recipe:

* `src/town/func_8080F4A4.c` (2.6.3-G0, 3 switches), `src/town/func_808109A4.c` (2.6.3-G0),
  `src/town/func_80811C54.c` (2.6.3-G0, 2 switches), `src/town/func_80813E14.c` (**2.8.1-G0
  `-mno-split-addresses`**, 3 switches).

`rows.md` names, per row: the cell, every `goto *` statement and its table symbol(s), the label array with its
entries **in table order** (index = case number), the case count, the live pin sites per macro, the `$5`/`$6`
dispatch pins, the bounds guard, and for a 2.8.x row the exact cfg string to use. Start from
`base/<container>/<name>.c`. `python3 tools/verify.py <row_id> <file> --diff` prints generated | retail.

## Recipe

1. Read the C and `rows.md`. Find the dispatch value, the table symbol, the label array and the labelled
   blocks it points at.
2. Write the real switch:
   - `goto *D_XXXXXXXX[value];` becomes `switch (value) {` ... `}` around the labelled blocks;
   - entry *i* of the label array becomes `case i:` on that label's block; the label itself goes away
     (unless something else still jumps to it);
   - an entry that names the same block twice is **two `case` labels stacked on that block**
     (`case 3:` / `case 4:` on one block, no duplicated code);
   - keep the blocks where they are: they already sit in retail order. **Case ORDER decides whether
     gcc's `jump.c` inverts a branch pair**, so write the cases in the table's order and reorder only if
     the residue tells you to;
   - delete the table's `extern` declaration, the label array, any `(void)name;` keep-alive use, the
     `__attribute__((used))` and an `#ifndef NON_MATCHING` / `#endif` pair that wrapped only the array;
   - delete the bounds guard (`if ((u32)value >= 7) { goto done; }`): the switch emits its own `sltiu`, and
     leaving the guard doubles the check. Its target becomes the switch's `default:` (write
     `default: goto done;` when other paths still need that label, or let the cases fall out of the switch
     to the same code when that is what the guard did);
   - index arithmetic (`idx = (x & 0x3FFF) - 1;`) has two spellings: `switch (idx) { case 0: ...` and
     `switch (x & 0x3FFF) { case 1: ...` -- gcc folds a minimum case into the dispatch `addiu`, so try both.
3. Verify: `python3 tools/verify.py <row_id> <absolute path to your .c>`.
4. When it is exact, erase pins one at a time and keep every erasure that stays exact: first the `$5`/`$6`
   dispatch-argument `ASM_REG`s (back to plain `T v;`), then any `ASM_KEEP`/`(void)` keep and any
   `ASM_SCHED_BARRIER`/`ASM_MEM_BARRIER` fence that was only holding the dispatch shape (the ones next to the
   dispatch value, the table load or the label array). Pins elsewhere in the row are fair game too -- fewer
   pins is the goal -- but never trade a pin for any form in "Not allowed".
5. Residue reading: if the only difference is at the dispatch and your candidate is exactly ONE word longer,
   with every later word shifted by one and the dispatch spelled `lui/addiu/sll/addu/lw 0()`, then the maspsx
   pass is still live in this tree (`work/maspsx_jtbl/REPORT.md` section 5). That is not your row's fault:
   write it in `REPORT.md`, stop that row, and say so in your final message. **Do not** add
   `--preserve-casesi-at`, any other maspsx flag, or a pin to work around it.
6. If the dispatch matches but the body does not, diff the arms: a case that falls through to the next in
   retail must fall through in your C (no `break`), and a case that ends in the function's tail is a
   `break`/`return`, not a `goto` to the epilogue.

## The 2.8.x cell rule

At 2.8.0/2.8.1 `mips_split_addresses` is on by default and gcc never emits the macro form. Those rows need
`-mno-split-addresses` added to the cfg -- a cell change under `tools/pin_cells_land.py` rules 1-2:

1. your candidate is exact at the NEW cfg and NOT exact at the recorded one, and
2. the row's current PINNED text (`base/<container>/<name>.c`) is also exact at the new cfg, so no byte
   evidence depends on the change.

`verify.py` has no cfg flag; score at another cfg with (read-only, scores nothing into the ledger):

```sh
python3 -c "
import sys; sys.path.insert(0,'tools')
from pathlib import Path
from common import rows; from verify import verify
r = {x['id']: x for x in rows()}['town/func_80813E14']
print(verify(dict(r, cfg='2.8.1-G0 -mno-split-addresses'), Path('/abs/path/to/candidate.c')))"
```

(pass a `Path`, as every caller in the tree does). `rows.md` prints the exact cfg string per 2.8.x row;
copy it verbatim. Both parts must be measured and reported, and the candidate then goes to `out_cell/`
(see below), never to `out/`. Flags are capped at two per row (owner's rule): if `rows.md` says a row is
already at the cap, measure and report it, but write no `.cfg`.

## Not allowed (census counts these like pins, so they remove nothing)

No new `ASM_*`, `__asm__`, `volatile`, fences, fake dependencies (`x = e + a; x -= a;`, `f(a + v - v)`, a dead
store), and no one-trip block: `do { } while (0)`, `while (0) { }`, `for (;0;)` or any block that runs once only
to change what the compiler sees. No NEW branch whose two arms hold the same code unless it is the
cross-jump form (both arms real, each executed once on its path). Never edit a `NON_MATCHING` arm.
No "impossible in C" verdict is accepted; report what you measured. No new maspsx flags (`row_asflags` is not
yours to change) and no new computed goto or label array.

## Tools, budget, output

- Score: `python3 tools/verify.py <row_id> <absolute path to your .c>`; `--diff` for generated | retail.
- The compiler recipe is fixed per row (`cell` in `rows.md`) except for the 2.8.x rule above.
- About 30 scorer runs per row.
- An exact candidate goes to `out/<container>/<name>.c` (with `base/.../<name>.c.base_sha` copied next to it)
  ONLY if `verify.py` said `"exact": true` for that file AND it has fewer `ASM_*` sites than the base AND it
  adds none of the forms above. A cell-dependent candidate goes to `out_cell/<container>/<name>.c` with the
  `.base_sha` and a `<name>.c.cfg` file holding the new cfg string (e.g. `2.8.1-G0 -mno-split-addresses`).
- A `slus/w_*` row is scored by object identity against the pinned TU, and a real switch adds a TU-local
  `.rdata` jump table, so the object hash will differ: such a row can only come back exact through the
  text-identical disassembly fallback. Print the whole verdict and quote its `proof` field in `REPORT.md`
  (the SLUS SHA-1 gate is the proof of record there, and it is not yours to run).
- `REPORT.md`: per row, the result, the table symbol(s) and case count, how the cases mapped (index -> label),
  the cell change if any with both rule-1/rule-2 measurements, pins before -> after, and every direction
  measured that failed; then the general rules you found (which case spellings paid, which did not).
