# 81811E30: scope the repeated-base folding question

Status: **unresolved pass consumer**. No production source, recipe or assembler
changed. This az-wall-deconstruct investigation scopes the old `_fold_selfinc_la`
claim; it does not establish a missing compiler or a compiler-wide impossibility.
The tracked [route](selfinc_81811E30/route.json) is compiler RTL/I2 analysis before
another source reconstruction.

The complete [retail body](selfinc_81811E30/retail.s) is 16 words. There is no
stack frame or call. `a0` holds the target value, `a2` counts matches, and `a1`
counts visited entries (initialized from the known-zero `a2`). `v1` starts at
`0x80010000`; every iteration loads an unsigned byte at `0x57D2(v1)`. Zero exits,
equality increments the match count, then the entry count advances and is tested
against 64. The back-edge delay slot advances `v1` by 19. The return delay slot
copies the count into `v0`. All accesses use the same folded low displacement;
retail never constructs the full `0x800157D2` pointer.

The [lineage fingerprint](selfinc_81811E30/lineage.txt), rerun after the source
trials, finds no family-discriminating store, split-address, call or GP evidence.
The known-zero copy is family-neutral. The registered 2.8.0 recipe is retained
as an experiment scope, not asserted as an independently identified lineage.
The checkout lacks the skill's `RUNBOOK.md` and `tools/aligned_score.py`; the
local scorer resolves every instruction of the full retail extent and records
aligned regions with zero masks in the [receipt](selfinc_81811E30/aligned_receipt.json).
It uses `difflib.SequenceMatcher`; the reported distances are not asserted to
be optimal LCS edit distances.
No positional mismatch count is used as a repair distance.

| Feature | Current attribution | Evidence and route |
|---|---|---|
| Counts, zero exit, 64-entry bound, stride 19, return | C semantics/control flow | Existing pointer source reproduces these with the pass; array-index forms were reconstructed from the full site map. |
| Repeated high-only base and folded load displacement | Compiler address representation, currently imitated by maspsx | Removing only the pass adds one word. Natural source probes and raw genuine compilers below do not produce this repeated form in the measured scope. Continue with address-GIV RTL. |
| Additional loop test/load in the structured candidate | Front-end/control-flow and loop optimization | The real C loop permits strength reduction but changes the loop layout. Preserve retail's layout when a source lever is identified. |
| Family selection | Unattributed | Fingerprint is insufficient; no ranking of failed C shapes establishes a lineage. |

The [index/goto source](selfinc_81811E30/index_goto.c) expresses accesses as byte
array offsets with stride 19. It emits 21 words at plain 2.7.2 and 22 at CDK,
2.8.0, 2.8.1 and 2.95.2, all at `-O2 -G0`. The changed source leaves index
multiplication inside the loop. A [structured do-loop](selfinc_81811E30/index_loop.c)
at 2.8.0 reduces the index arithmetic but emits 21 words: an initial folded load,
then a full pointer for repeated loads. A two-exit infinite-loop spelling has the
same result. None is a candidate for landing, and further source variations
were stopped.

The [RTL excerpts](selfinc_81811E30/rtl_receipt.json) retain the mechanism:
`input.c.loop` identifies induction variable 82, combines address GIVs at
instructions 30/32, and reduces them to pseudo 107. Its initializer is a full
symbol address formed from `high`/`lo_sum`; later loads use that full pointer.
This supplies a concrete next compiler-pass question, rather than a flag sweep:
can the low displacement remain in the load while the induction variable carries
only the high base? The subsequent pass inspection below narrows that question.

The [nine raw genuine compiler runs](selfinc_81811E30/psyq_receipt.json) cover
exactly three source forms (canonical pointer, index/goto, index/do-loop) at
PsyQ 4.0, 4.1 and 4.4, `-S -O2 -w -G0`, default address-splitting flags. Source,
compiler, preprocessor and driver hashes are recorded. The adjacent `*.raw.s`
files preserve the full outputs; any repository prefix in a file directive is
rendered as `<repo>` in these copies.

PsyQ 4.0 uses a full-base `la` for the pointer and do-loop forms. PsyQ 4.1/4.4
split the full address into `lui`/`addiu`; their do-loop versions use a folded
initial load but then construct a full pointer for the repeated accesses. None
of the nine emits retail's repeated high-only-base form. This conclusion is
limited to these sources, binaries and flags. It does not justify retiring the
pass, accepting a compiler wall, or inventing a pointer to an address page in C.

Reproduce via `work/wall_81811E30/probe.py`, `score.py` and
`psyq_probe/run.py`. See the broader [12-consumer check](selfinc_consumers.md)
for unchanged-source and pass-ablation controls.

The [post-loop receipt](selfinc_81811E30/post_loop_receipt.json) follows the
initializer (instruction 96), stride update (99), and repeated load (32) through
CSE2, combine and global allocation. All retain the full-address induction
variable. Combine leaves the initializer in basic block 1 and the repeated load
in basic block 5; the induction variable is also updated in block 4. Global
allocation assigns both the earlier high-base pseudo 96 and full-pointer pseudo
107 to v1, but keeps the low addition. Register coalescing does not remove it.

The available GCC 2.8.0 `combine.c`, lines 23–49, describes same-block logical
links and expression substitution. Together with these dumps, this explains why
simply waiting for combine to fold the initializer is not a repair for this
source: matching retail requires changing the loop induction variable's origin
and its repeated load addresses together. This is a scoped mechanism finding,
not proof that another evidenced source representation or compiler mode cannot
produce retail. Next inspect address-GIV formation/cost decisions in `loop.c`
and establish the actual record layout before proposing a typed-record source.
