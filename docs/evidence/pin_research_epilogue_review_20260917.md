# Independent review: `dungeon/func_818B78E8`

Verdict: no semantic, interface, helper-contract, or hidden-constraint blocker found. The candidate is a zero-pin exact reconstruction at the unchanged `2.8.1-G0` recipe. Full publication and covering-window gates remain pending outside this review.

## Bound evidence

- Baseline `base.c`: SHA-256 `471ab36b2a584827ddd44e61ef719c1b7226919943ce53e52d58ac132c943e07`; `baseline.summary.json` records 186/186 words exact with zero substitutions or indels.
- Candidate `candidate_final.c`: SHA-256 `8e33f4d2fc40fb4c7f631a20b7df54d167f86e38a8568e35c0237995c481c219`.
- `strict_final.json`: SHA-256 `43fedc3d0787d8705b020da1bb5ff62883a98cd23bbea83aa26975b81eed6598`; linked-strict 744-byte / 186-word exact match, zero positional words off, no relocation masking, and source hash equal to the candidate hash.
- Retail disassembly: SHA-256 `2ba4bb40f6d822dff43629a49d00178ba393859b3ed331268e4b2e2916fd92b6`; strict target SHA-256 `e8b45bf8fc034a37300d056f7cbd80b9d4a7c908d6971cba0afe39143734cbcd`.
- `identity.json`: SHA-256 `33525152a0890944f397ab160f1f7afd62317b47886501e8d3c1fd726607b4bd`; proven rowbase, true name `func_800250E8`, base `0x800250E8`, and unchanged `2.8.1-G0` recipe.
- Helper probe `root_helper_contract.summary.json`: SHA-256 `771aa7660e401ed195f6f6ca41b0edd549bda2f1d9807e762399e8c06fa72327`; 186/186 exact.

## Retail and source semantics

All 186 retail words were reviewed. The prologue fixes `s0=arg0`, `s3=arg1`, and `s1=arg2`. The candidate preserves every object, vector, state, counter, random-value, and state-dispatch update. Its direct argument accesses and 16-bit `field10` assignment express the same values as the baseline temporaries, including 16-bit wrap on storage.

The jumps at offsets `0xBC`, `0xD8`, and `0x28C` all enter `0x800253B0`, which only restores `ra/s3/s2/s1/s0`, restores `sp`, and returns with a `nop` delay slot. Replacing the fake `func_800253B0` noreturn calls with ordinary `goto done` control flow is therefore faithful. State 0 still updates the vector and advances state when its counter reaches the limit; states 1 and 2 retain their signed quotient/remainder-derived byte updates and thresholds; state 3 retains both flag writes.

The candidate changes the definition from the synthetic row spelling to proven runtime name `func_800250E8`. Its interface remains `void` with three pointer arguments in the same order. A current dungeon-source search finds definitions rather than direct calls for these spellings; a sibling overlay definition of `func_800250E8` also uses a three-pointer `void` ABI. Indirect use is not excluded, but the calling convention and consumed result are unchanged.

## Helper contract

The authoritative SLUS definition at `src/slus/code.c:281` is `void func_800478B8(void *entity)` (source SHA-256 `1c1afc31d56af7f3505ad1a9e54c4c21023aac81b2314ad3581dbeadf1e28b16`). It forwards that one pointer to `func_800477F4(entity)` and `func_80047694(entity)`. Their implementations likewise take one pointer and derive all downstream arguments from fields of that object; the reviewed source hashes are `9ec30d2b744b090fd3661fe6adb30f2dfaeb4b36edf4e1efaf4dc459f65070e9` and `1e8132583ff1138cfc5611a2a9579dab0f2f45dab76217316892b458269d79fd`.

Retail moves `s1` (`arg2`) into `$a0` before the helper call. `$a1` and `$a2` contain modulo intermediates computed for surrounding work, but the callee does not consume them. The baseline's old-style three-expression call therefore overstated the helper interface. The candidate's explicit `extern void func_800478B8(void *);` and `func_800478B8(arg2)` match the real contract while preserving the exact retail register stream, as independently shown by the helper probe and final strict result.

## Pin and compromise audit

The sole baseline pin was `ASM_KEEP_NV(inc_field10)`. The candidate removes it and contains no `ASM_*`, volatile access, inline assembly, fake noreturn edge, artificial external, literal-address dependency, ABI shortcut, or replacement constraint. The remaining old-style `func_80024FD4` declaration predates the candidate and its two-pointer call is unchanged. The Luna near-miss was a two-indel ordering residual; correcting the real helper prototype and call closed it without adding a pin.

## Inherited arithmetic limits

The source retains decompiler-style signed shifts used by the exact baseline, including left shifts of values that may be negative and implementation-defined arithmetic right shifts. Under a compiler or language model with different signed-shift rules, those expressions merit a separate semantic cleanup. The candidate does not introduce or broaden them, and the fixed 2.8.1 endpoint reproduces all retail words, so they are an inherited source limitation rather than a defect in this epilogue/helper repair.

No compiler, export, publication gate, production source, config, ledger, or git mutation was run for this independent review.

## Publication addendum (root, after independent review)

The accepted live source is `src/dungeon/func_818B78E8.c`, SHA-256 `8e33f4d2fc40fb4c7f631a20b7df54d167f86e38a8568e35c0237995c481c219`. It is byte-identical to the reviewed candidate; the recorded stock recipe is unchanged. Fresh full verification, linked-strict bytes, all covering windows, host syntax, SLUS and row database pass. The durable source pair, complete controls and gate records are in [the round-50 receipt](pin_research_round50_20260917.json). Earlier references to live/base source and pending gates describe the pre-publication review snapshot.
