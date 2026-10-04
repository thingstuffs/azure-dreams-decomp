
## Your task: the `#ifdef NON_MATCHING` / `#ifndef NON_MATCHING` blocks

Several rows keep two versions of code: a compiled arm and a `NON_MATCHING` arm (a portable/plain-C version for
other builds). Both arms must stay valid C. Your job, per block:
1. If the NON_MATCHING arm is DEAD - it duplicates the compiled arm exactly, is empty, or does nothing the compiled
   arm does not - delete the whole `#if...NON_MATCHING ... #else ... #endif` wrapper and keep the compiled arm's code.
2. If the NON_MATCHING arm is STALE - it names variables, fields or helpers the compiled arm no longer uses (the
   compiled arm was rewritten since) - bring it in line with the compiled arm's current C (same names, same
   structure, only the pin/ASM_ parts differing) - that keeps the leftover count equal, so it will NOT stage: list
   these in the report with the edit as a diff block instead.
3. Otherwise leave it.
Never edit the COMPILED arm (the one the real build sees: for `#ifdef NON_MATCHING ... #else X #endif` it is X; for
`#ifndef NON_MATCHING X #else ... #endif` it is X). After a deletion, also compile the row with `-DNON_MATCHING` is
not needed (the arm is gone); for a stale-arm edit, check it still compiles: `lab.py` has no flag for that, so just
make sure the C is valid by reading it.
