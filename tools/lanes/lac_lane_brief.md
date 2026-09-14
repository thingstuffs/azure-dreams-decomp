# Lane: label-as-call rows as honest C (@MODEL@), @NROWS@ rows

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

m2c spelled every intra-function jump it could not structure as a CALL to a pseudo-function that it declared
`__attribute__((noreturn))` and named after the jump target's TRUE address (`func_80025390` for a block at
0x80025390). Our assembler front end converts that `jal` to `j` by a name list (`config/sibcall_syms.*.txt`,
`config/noreturn_syms.*.txt`), which is why the rows are byte-exact today. Two Fable/opus waves in round 25
proved what the calls are (`work/tailslot_skeptic/REPORT.md` section 3; `work/tailslot_honest/pack4/REPORT.md`):
**every pseudo-callee is inside its own row** - a shared block that two arms cross-jump to, the epilogue, a
loop head, or a thread-filled label one word before the "function". The honest C is the `goto` or `return`
the jump stands for, and once it is written the keeps, register pins and fences that were only holding the
pseudo-call shape fall too (on 87 rows: 76 `ASM_REG`, 45 keeps, 41 fences besides the marker pins). 104 rows
landed that way this round at 86-97% per pack.

Each row in `rows.md` names its cell, its true base and delta, and every pseudo-call site: the callee, its
offset inside the row (callee minus true base), and whether the word before the callee equals the jump's
delay-slot word (a THREAD FILL: the source label is then at offset-4). Start from
`base/<container>/<name>.c`. `python3 tools/verify.py <row_id> src/<row_id>.c --diff` prints generated | retail
so you can read the block at the offset.

## Recipe

1. Read the C and the retail listing. For each pseudo-call find the block at its offset (normalise the
   thread fill first).
2. Replace `func_X(args);` / `return func_X(...);` with the honest form:
   - the epilogue -> `return <value>;` (the value is what retail leaves in `v0`: a variable, a constant, a
     call result; a `void` function returns nothing);
   - a shared block that computes into a register the arms disagree about -> write the block's statements
     in BOTH arms (an implicit `else` becomes a real one) and let gcc cross-jump them;
   - a shared block whose arms differ only in values already held in variables -> a label on the block and
     `goto` to it from each arm;
   - a loop head -> a label at the head and `goto` (never `do { } while (1)`: the loop note turns on LICM
     and costs two words);
   - a shared `move v0,<callee-saved>` join -> `goto <the existing return label>`, never a duplicated
     `return expr;` (that lets gcc compute straight into `v0` and jump to the epilogue: wrong `j`).
   Convert EVERY pseudo-call that terminates either merging arm: cross-jumping needs a jump on both sides.
   Delete the pseudo-function's extern declaration when unused.
3. Verify: `python3 tools/verify.py <row_id> <absolute path to your .c>`. When it is exact, erase the row's
   remaining pins one at a time (`ASM_REG` declarations back to plain `T v;`, `ASM_KEEP(v);` deleted,
   fences deleted) and keep every erasure that stays exact: fewer pins is the goal.
4. Residue diagnostics that paid: one `addu` with swapped operands under a narrower-than-int store -> keep
   the sum in a `u32` temp and store the temp; a mis-coloured register on a variable that is NOT the join
   value -> use the duplicated-arms form, not a shared join variable (the join pseudo goes to global
   allocation and takes the wrong register); two different join offsets in one row can be one duplicated
   tail (the common suffix is just longer at one site); a `page = 0x8002xxxx; x = page - N` value that a
   pseudo-call returns -> spell it as the symbol it is (`&D_...`).
5. A frameless row at a 2.8.x cell may be unable to express a jump to its epilogue (gcc >= 2.8 inlines
   `jr ra`); then try a 2.7.2-family cell under `tools/pin_cells_land.py` rules 1-2 (the candidate exact at
   the new cell and not at the recorded one, the PINNED text exact at the new cell too, the row's flags
   kept) and report the cell in REPORT.md.

## Not allowed (census counts these like pins, so they remove nothing)

No new `ASM_*`, `__asm__`, `volatile`, fences, fake dependencies (`x = e + a; x -= a;`, `f(a + v - v)`, a dead
store), and no one-trip block: `do { } while (0)`, `while (0) { }`, `for (;0;)` or any block that runs once only
to change what the compiler sees. No NEW branch whose two arms hold the same code unless it is the
cross-jump form above (both arms real, each executed once on its path). Never edit a `NON_MATCHING` arm.
No "impossible in C" verdict is accepted; report what you measured.

## Tools, budget, output

- Score: `python3 tools/verify.py <row_id> <absolute path to your .c>`; `--diff` for generated | retail.
- The compiler recipe is fixed per row (`cell` in `rows.md`) unless step 5 applies.
- About 30 scorer runs per row.
- An exact candidate goes to `out/<container>/<name>.c` (with `base/.../<name>.c.base_sha` copied next to it)
  ONLY if `verify.py` said `"exact": true` for that file AND it has fewer `ASM_*` sites than the base AND it
  adds none of the forms above. A cell-dependent candidate goes to `out_cell/<container>/<name>.c` with the
  `.base_sha` and a `<name>.c.cfg` file holding the new cfg string.
- `REPORT.md`: per row, the result, what each pseudo-call turned out to be (offset, kind), the change, pins
  before -> after, every direction measured; then the general rules you found.
