# C7F80 plain-C review: measured blockers

No byte-exact pin-free C proposal was found. The requested fallback is a
scoped blocker report after source avenues were explored; this is not a
universal compiler-impossibility or permanent-pin verdict.

The strongest pin-free comparison source is
`work/native_lane/c7f80_review_package_20261014/candidates/review_pin_free.c`.
It scores 2 (zero substitutions, two indels) at `2.7.2-cdk-G0`, with the retail
48-byte frame. The complete function assembly differs only in the order of
`sll a1,s1,2` and `li a0,1293`. The current production control is byte exact.
The source is explicitly marked nonmatching and is not a landing proposal.

The blockers in the measured families are:

1. The closest source loses an early sound-ID carrier to constant propagation,
   leaving the wrong argument/scale order after scheduling.
2. A separate single-set scale changes that scheduling mechanism but gets
   v0 because its lifetime does not overlap the Y-address temporary. Those
   register choices create downstream scheduling differences.
3. Source role splits that produce the desired allocation remove the X-to-Y
   scratch-reuse dependencies or hoist an extra address, changing order or
   growing the frame. The tested ordinary scalar and inline-helper versions
   do not combine the needed properties.

A single diagnostic sched1 birth override yields all 560 retail bytes with
ordinary allocation. It changes a result that the current multi-set carrier
cannot obtain naturally, so it is evidence about a sufficient scheduler
outcome, not exact C. Other genuine C graphs remain possible.

The final structural checks included ordinary X/Y coordinate locals, shared
direction indexes, scalar-return inline helpers, and inline helpers writing
the three position fields. Their totals were respectively 35, 32–38, 32,
and 49. Arithmetic spelling changes normalized back to earlier failures.
Simplifying the inherited cursor idiom gives total 8 rather than an exact
source; the two-instruction reference should not be presented as recovered
original source merely because its score is smaller.

The genuine PsyQ 4.1 executable and the reconstructed CDK compiler produce
identical full-function assembly for both leading source shapes. The one-argument
sound ABI and genuine unused second argument in another branch were audited.
No current toolchain-path or ABI discrepancy explains the residual.

Full review package, exact measurements, source hashes, explored families,
and the explicit fallback-completion audit:
`work/native_lane/c7f80_review_package_20261014/REVIEW.md`.

No C7F80 production source, toolchain, recipe, or ledger was changed. Future
source work should seek a genuinely different dependency/lifetime graph;
repeating constant carriers, spelling variants, or forced compiler settings
would not resolve the measured source-reconstruction gap.


## Follow-up on the three new leads

The cursor-history lead is now causally resolved. The integer advance/read-back
idiom reaches flow analysis with 12 references to the Y carrier; a direct load
has 8. Combine removes the advance but local allocation retains those earlier
reference counts. The carrier priority therefore changes from 8571 to 12857,
across the position pointer's 9230, swapping their register allocation. Their
live intervals and first scheduling order otherwise agree. Thus the score-8
cleanup's extra register differences are downstream of this bookkeeping; they
do not identify another argument-order defect. Typed self-carrier forms can
retain the same history but still have the original score-2 mismatch. This is
an explanation of a near miss, not exact C.

Taking the cursor address through a real inline consuming helper failed: the
compiler retained a stack slot and expanded the frame to 56 bytes. Three
helper forms scored 28, 28, and 32. See
`work/native_lane/c7f80_cursor_helpers_20261014/REPORT.md` and the count trace at
`work/native_lane/c7f80_cursor_counts_20261014/receipts/CURSOR_COUNT_TRACE.md`.

The table-layout lead was tested without treating reconstructed declarations
as proof of the original object boundary. Retail has two contiguous eight-short
rows. A struct with X/Y members and a two-dimensional array both use the correct
Y relocation at base+16, but score 7 with the prior scheduler residue. A real
whole-object byte cursor changes loop optimization and scores 26. These checks
did not produce the required ordering; no shared declaration was changed. See
`work/native_lane/c7f80_table_owner_20261014/REPORT.md`.

The held historical compiler audit compiled the same single-scale source with
genuine PsyQ 4.0, 4.1, and 4.3 binaries. The relevant cdk/4.1/4.3 order agrees;
4.0 produces a different graph. Held 4.3 and 4.4 binaries are identical. The
available source versions retain the same single-set birth test and set-count
maintenance. This rules out the tested binary alternatives, not every historical
SN patch. See `work/native_lane/c7f80_patch_audit_20261014/REPORT.md`.

A fresh full-function verification after these trials still finds zero pins,
the retail frame/save mask, and only the same adjacent instruction swap in
`review_pin_free.c`. The production control remains byte exact and unchanged
(SHA256 `507aacd8e1c5d5ea8b486f7828e556753dd5aef7f7d2e8e9bbdb391ae193780b`).
The review source remains nonmatching and is not proposed for landing.


The targeted archival follow-up found no new compiler to test. The downloadable
PsyQ 4.2 artifact was inspected and contains libraries/headers only; the
DTL-H2000 System Software 4.02 image contains a driver but no cc1. Public SDK
collections, compiler mirrors, and the archived SN download references did not
yield a PSX build from the named 1997 window. The remaining concrete historical
input is a developer-kit or licensee backup containing that cc1. This is a
negative search result, not proof it never existed. Sources, archive hashes,
and inspection details are in
`work/native_lane/c7f80_patch_audit_20261014/ARCHIVE_SEARCH.md`.

### Follow-up completion audit

The explicitly permitted blocker-report outcome is satisfied for this round:
all three newly named leads were investigated, their resulting source or
archival branches were followed, and no untested actionable branch emerged.
The original exact-C outcome remains unachieved. The verified best source is
still the nonmatching score-2 reference. No proposal was staged or landed.

The remaining reconstruction blocker is a source graph that yields the needed
Y-address/scale lifetime overlap while preserving the required scheduling and
48-byte frame. The diagnostic scheduler override demonstrates a sufficient
compiler outcome but supplies no plausible C that achieves it. Count-history
experiments recover allocation only; table abstractions and ordinary helpers
change the earlier optimization graph or frame. This scoped conclusion does
not claim that no other original C expression can match.
