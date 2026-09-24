# F240 three-arm compiler diagnostic

This private probe compiles the unchanged `cohort/f240_owned.c` (SHA-256
`fd2520894739effd99a2ae2ca6299bb9681902bab774d8713c6852f779e17cdf`)
at `-O2 -G32` with `-da`. Each arm has its own copied source, assembly, log,
and all RTL dumps. `probe.py` and `compile_receipt.json` pin the inputs and
record output hashes. There are no production edits or assembly patches.

| Arm | Compiler and additional flag | First `.sched` order | Raw assembly start | Scheduler time |
| --- | --- | --- | --- | ---: |
| A | CDK 2.7.2, `-fno-expensive-optimizations` | head load, index arithmetic, queue HI/LO | `lbu v0`, `#nop`, `addu` | 12 |
| B | GCC 2.8.1, `-fno-expensive-optimizations` | head load, index arithmetic, queue HI/LO | `lbu v0`, `#nop`, `addu` | 12 |
| C | CDK 2.7.2, expensive enabled | queue HI, head load, queue LO, index arithmetic | `lui a0`, `lbu v1`, `addiu a0` | 11 |

The first *instruction-order* divergence is the first scheduler pass. All
three expansion dumps start with queue HI (insn 7), queue LO (8), then head
load (9). A/B schedule head load first, issue queue HI/LO late, and record
one stall. C schedules HI/head/LO and records no stall. The second scheduler
preserves these orders. The 2.8.1 arm does not isolate a version effect; it
shows the same order as no-expensive CDK for this function.

The compiler inputs to that scheduler already differ. In the initial `.rtl`
dump, insn 17 for synthesized stride multiplication reuses reg 87 in A/B
(`reg87 = reg87 + reg85`), while C creates reg 88
(`reg88 = reg87 + reg85`). This changes the live-range graph. Local upstream
GCC 2.7.2 source traces it to `stmt.c:2435`:
`preserve_subexpressions_p()` returns true when
`flag_expensive_optimizations` is set. `expmed.c:2234` calls it from
`expand_mult`; the true branch makes `accum_target = 0` rather than reusing
the accumulator for a constant multiply. The scheduler itself has no direct
`flag_expensive_optimizations` branch in `sched.c`; its `priority()` and
`rank_for_schedule()` use dependencies, latency, and original order. CDK's
local compiler directory contains binaries only, so the precise source
attribution is to the available GCC 2.7.2 source plus observed CDK RTL,
not to a verified CDK source patch.

An explicit source expression `(index << 1) + index` is a targeted way to
avoid the synthesized `* 3` step and test whether the no-expensive arm can
produce the required pseudo/dependency graph. Merely moving a local queue
base declaration or using a byte pointer was already insufficient in the
earlier natural-source checks. No new source rewrite or recipe sweep was
performed here.

Arm C's raw compiler assembly has the same apparent 12-instruction order and
register roles as the retail F240 listing, including the delay-slot `nop`
expected after `jr`. This is **provisional**: no ASPSX assembly, relocation,
or retail-byte comparison was performed in this diagnostic. Root is checking
genuine assembly separately.
