# CD stride expansion and allocator lifetimes

Measured on SLUS `func_8003F240` and `func_8003E758` with CDK 2.7.2,
`-O2 -G32`, and explicit small-data ownership. See
[the full evidence](../../docs/evidence/gp_cd_cohort.md).

F240's queue index uses a 24-byte stride. With expensive optimization disabled,
constant-multiply expansion reuses its accumulator pseudo for shift/add; with it
enabled, expansion creates a fresh pseudo. The first scheduler consequently
changes from head-load-first with one load-delay stall to queue-HI/head-load/
queue-LO, matching retail's twelve instructions. This is not a direct scheduler
flag switch: the initial RTL already has different pseudo-register lifetimes.
Available GCC 2.7.2 `stmt.c` / `expmed.c` explain the mechanism; CDK-specific
source is not locally available. Merely moving a pointer local earlier in C had
no effect. Writing an explicit shift/add eliminated the extra word but still
left register mismatches, so that version was not adopted.

Under the enabled setting, E758 differed in seven words at its completion lookup
because address-base and stride registers exchanged roles. Expressing the
24-byte offset as `completion_offset = head_index << 1; completion_offset +=
head_index; completion_offset <<= 3;` gives one distinct accumulator for that
lookup. Reusing the earlier dispatch's `head_stride` variable disturbed the
other block; a separately scoped local preserved both regions. The final owner
is exact across all eight CD functions, 1,041 words, using one CDK `-G32` recipe.

Scope: these observations are measurements of these C shapes and compiler
settings, not a general rule that locals force physical registers. A flag-only
mismatch did not establish a compiler-version wall. Resolve expansion/live-range
ownership before config grinding, and verify the full joined function set after
changing a shared recipe.
