# Lane `<LANE>` - byte-neutral source cleanup (<TASK>)

Repository root: `<REPO>`. Your lane directory is `<REPO>/work/native_lane/<LANE>`: WORK FROM IT (cd there first;
every file you write stays inside it). The rows' current texts are in `base/<container>/<name>.c`.

## Hard rules
- Never edit anything under `<REPO>/src/`, `include/`, `config/`, `tools/`, `ledger/`; never run git, gates, sweeps or
  landings; never change a row's compiler recipe.
- A result counts ONLY when `lab.py ... --score` says exact=true (byte-identical object). Nothing else counts.
- Do not change control flow, statement order, expressions, types of locals, widths, casts or declarations other than
  what your task below allows. This lane is a SPELLING lane: the compiled bytes must not move.
- Never add pins (ASM_* macros), volatile, `__asm__`, one-trip `do {} while (0)` blocks, gotos, or new
  decompiler-style names (temp_/var_/phi_/argN/spXX/M2C_*). Keep every #include the row needs.
- IO rule (shared disk): no recursive grep/rg over the repo root, `work/` or `$HOME`. `rg --max-filesize 4M` on a
  narrow directory (`src/<container>`, `include/`) is fine. Run commands in the foreground; never poll with pgrep.
- At most 4 compiles in parallel. Keep scratch files in `tmp/`.

## How to measure and stage (the kit; TOOLS.md lists every tool with its absolute path)

    cd <REPO>/work/native_lane/<LANE> && source <REPO>/tools/lanes/lanekit/env.sh
    python3 <REPO>/tools/lanes/lanekit/lab.py baseline <row> --score     # MUST print exact=true first
    python3 <REPO>/tools/lanes/lanekit/lab.py <row> cand.c --score        # exact + fewer leftovers => staged to out/
    python3 <REPO>/tools/lanes/lanekit/diff.py <row> cand.c --vs pinned --ctx 4   # when not exact: what moved
    python3 <REPO>/tools/lanes/lanekit/lab.py report

`--score` stages an exact candidate to `out/<container>/<name>.c` automatically when pins are unchanged and the count of
decompiler leftovers fell (M2C_* tokens, temp_/var_/phi_ locals, argN parameters, spXX names, NON_MATCHING; comments
excluded) or gotos fell, and nothing banned grew; otherwise it prints `NOT staged (reason)`. Stage your best
candidate per row (a later exact one with fewer leftovers overwrites it). Work row by row: baseline, edit, score,
stage, next row. If one edit breaks exactness, back it out and keep the rest - partial cleanup of a row counts.

## Report
Write REPORT.md: one block per row - `**Result:** leftovers N -> M (staged | nothing exact)`, what you changed, and
any edit that changed bytes (what moved: that is useful evidence). End your final message with one line per row.
