# Lane `<LANE>` - goto readability, <N> pin-free rows

Repository root: `<REPO>`. Your lane directory is `<REPO>/work/native_lane/<LANE>`:
WORK FROM IT (cd there first; every file you write, every compiler dump, stays inside it). Never edit `src/`, never
run git, gates, sweeps or landings. `TOOLS.md` in this directory lists every tool with its absolute path.

## The task

These rows are already byte-exact and carry **no pins**. They still read like decompiler output: plain
`goto label;` statements where the original author almost certainly wrote `if`/`else`, `while`, `for`, `do`,
`break`, `continue` or `return`. The project goal is source we can be proud to share, still byte-exact. Your job:
**remove as many plain gotos (and the labels they leave unused) as you can while the row stays byte-exact.**

<ROW_TABLE>

**Bonus, same rules:** some of these rows also carry uncounted scaffolding - a `do { ... } while (0)` barrier, a
`*(volatile T *)&x` read, a fake dependency. Removing any of it while staying exact is worth as much as a goto (the
kit stages equal-pin candidates whose volatile / one-trip count fell too); report what each one held.

Partial progress counts: a byte-exact candidate with FEWER gotos (and nothing else made worse) is a landing.
Stage it and keep working from it. A row where every goto provably has to stay is a result too - say which
compiler decision each remaining goto holds, measured, not guessed.

## What already worked (r79_sonnet_g1, Sonnet 5.5: 35 -> 5 gotos on 6 rows, every shape measured)

| shape | rewrite | tried / exact |
|---|---|---:|
| `goto L` where `L:` only returns | `return;` / `return x;` at each site | 2 / 2 |
| forward-goto ladder into a shared tail (`if (k == 1) {..; goto end;} if (k == 2) ...`) | if / else-if chain falling out to the tail | 5 / 5 |
| leading `if (p == 0) goto done;` | wrap the rest in `if (p != 0) { ... }` | 3 / 4 |
| chain of `if (!c) goto done;` guards | one `&&` chain, or nested ifs | (same row) |
| zero / calculate / finish trio | `if (A \|\| (b = e) == 0) { zero } else { calc }` | 2 / 6 |
| a label shared by several arms | keep ONE label inside an else arm (pure C) | 1 / 1 |

r79_sonnet_g5 (8 rows, 38 -> 1 gotos, 7 volatile sites removed as well):

| shape | rewrite | note |
|---|---|---|
| a state/phase ladder (`if (p == 0) goto a; if (p == 1) goto b; ...`) | `switch (p)` with fallthrough where one arm runs into the next | an if/else chain measured dist 20 on the same row |
| a goto pair into a shared tail | `if (a \|\| !b) { default } else { alt }`, DEFAULT ARM FIRST | alt-first `&&` form: dist 111 |
| a jump into an else arm | early `return;` in the arm, shared tail after the if/else | |
| a one-line shared case tail (`next++; goto out;`) | copy the line into each case (owner: a duplicated statement in both arms is fine) | hoisting it after the switch: dist 9 |
| backward goto loop with the exit test mid-body | `while (1) { ...; if (!next) break; ... }` | do/while and for(;;) also matched |
| `*(volatile T *)&x` read / volatile field stores | plain read/store - try it on every row, it often stays exact | 7 of 9 removed |

Never merge different bit tests of one word into a single `&&` (`(f & 0x410) && (f & 0x20000)`): combine merges
them (dist 12) - nest the ifs.

Never merge redundant range tests into one `&&` chain (`kind != 0 && kind < 0xB && kind == 1`): combine folds
them and drops a branch group (dist 3-4) - nest the ifs instead. Merged flag tests (`flags & (A|B|C)`) and
duplicated shared calls per arm measured 46-51: keep the original test order and one call site. A removed
`do {} while (0)` or `*(volatile T *)&x` read that breaks the match stays - say what it held.

## How to measure (the kit)

    cd <REPO>/work/native_lane/<LANE> && source <REPO>/tools/lanes/lanekit/env.sh
    python3 <REPO>/tools/lanes/lanekit/lab.py baseline <row> --score     # MUST print exact=true first
    python3 <REPO>/tools/lanes/lanekit/lab.py <row> cand1.c cand2.c --score
    python3 <REPO>/tools/lanes/lanekit/diff.py <row> cand.c --vs pinned --ctx 4
    python3 <REPO>/tools/lanes/lanekit/why.py <row> --pass loop --variant cand.c
    python3 <REPO>/tools/lanes/lanekit/lab.py report

Control-flow rewrites move labels around, so a byte-identical listing can still differ in label ORDER: `--score`
byte-scores every candidate within `LANEKIT_SCORE_NEAR` listing lines (default 24); export `LANEKIT_SCORE_NEAR=200`
before calling a structural rewrite a failure (r79_sonnet_g27: exact at listing distance 21).
`lab.py ... --score` stages an exact candidate to `out/<container>/<name>.c` automatically when it has the same
pins (none) and **strictly fewer plain gotos** and adds nothing banned; otherwise it prints `NOT staged (reason)`.
Stage only your best candidate per row: each later exact one with fewer gotos overwrites it. `lab.py` refuses more
than 60 variants on one row without `--more`. At most 4 compiles in parallel.

## What gcc 2.7/2.8 does with each shape (why a rewrite can change bytes)

* **Loops.** `while`/`for`/`do` get NOTE_INSN_LOOP_BEG/END notes from the front end; a backward-goto loop does
  not. loop.c (invariant hoisting, strength reduction/givs, `-fno-rerun...` aside) runs only on noted loops, so a
  goto loop the decompiler left because loop.c changed the code when it was a `while` may be real. Measure: when a
  structured loop changes bytes, `why.py --pass loop` shows what loop.c moved. Try the equivalents before giving
  up: `while (c)`, `for (;;) { if (!c) break; ... }`, `do { } while (c)` inside `if (c)`, the test placement
  (top/bottom), `continue` vs a trailing test. gcc 2.x rotates `while (c) body` into
  `if (c) { loop: body; if (c) goto loop; }` itself - the m2c shape `if (c) { L: ...; if (c) goto L; }` is
  very often a plain `while` (or `for`) loop.
* **Forward gotos** (`if (c) goto L; A; L: B;`) are usually `if (!c) { A; } B;` or an `if/else` chain; the
  code is often identical, but block order and jump threading (jump.c) can differ - measure.
* **`goto` to a shared `return`/epilogue** is usually `return x;` at each site (gcc makes one return label
  anyway), or an if/else that falls to the single return.
* **Loop exits** via goto are `break`; jumps to the loop's next iteration are `continue`.
* A goto into the middle of a loop / a label between two loops is the hardest shape: often a `for` whose test
  the author wrote at the top, or a `do/while` with an early `break`. Leave it if every structured spelling
  measures worse - and say what differed.

## Rules (a candidate that breaks any of these is not a result)

* Byte-exact by `lab.py --score` / `verify.py`, nothing else counts.
* No new `ASM_*`, `__asm__`, `volatile`, fences, one-trip blocks (`do {} while (0)`, `while (0)`, `for (;0;)`),
  fake dependencies or dead stores; no new gotos elsewhere to pay for removed ones (net goto count must fall).
* Never move a label INSIDE a block so a remaining goto jumps into it (`if (c) { L: ... }` with `goto L;` from
  outside): a goto into a block reads worse than the flat labels it replaced - the coordinator rejects it (g41).
* Duplication (owner ruling): copying a SHORT shared statement or tail (1-3 lines, e.g. `x++; break;`) into each arm
  is fine - it is likely how the original was written. Copy a longer block (at most ~6 lines) only when the
  alternative is a goto that jumps INTO another block; never copy more than that (g46: a 15-line copy was replaced
  by the 1-goto-fewer variant). Otherwise keep the goto and say what the copy would have cost.
* Keep the function's behaviour identical (same semantics on every path) - this is a refactor, not a new
  decompilation. Keep every `#include`, the signature, and existing names/comments unless a comment describes
  a label you removed (update it then). Do not rename variables in this lane.
* Delete labels your rewrite leaves unused (gcc warns but compiles; an unused label is still clutter).
* Never change a row's cfg/recipe. An uglier-but-structured spelling that stays exact is acceptable - but prefer
  the spelling a human would write.

IO discipline (the disk is shared): never `grep`/`rg`/`find` recursively over `work/`, the repo root or the home
directory; search only narrow directories with `rg --max-filesize 4M` (`grep` here is ugrep). Run shell commands
in the foreground; never poll with `pgrep` on a pattern your own command line contains.

## REPORT.md - the required shape

One block per row:

    ### <row id>
    **Result:** gotos N -> M (staged | nothing exact)
    **The change:** the structured forms used (e.g. "rotated goto loop -> while; goto-to-return -> return x").
    **Kept gotos:** each remaining goto, the structured spellings tried, and what changed in the listing
      (which pass: loop hoist, jump threading, block order...), from `diff.py` / `why.py`.
    **Generator rule:** APPEARS (the textual shape) / RESOLVES (the rewrite) for every shape that WORKED, and
      the shapes that never worked - precise enough that a script can sweep 900 more rows tomorrow.

End REPORT.md with a table: shape, times tried, times exact.
