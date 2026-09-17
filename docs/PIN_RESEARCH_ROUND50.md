# Round 50: real symbols, helper contracts and bounded reconstruction

**Four pins removed: 6,028 remain in 1,271 functions; 75 removed from 6,103.**
Both complete rows and covering windows match; host syntax, SLUS and row database
checks pass. Five fingerprint tests pass. The [durable receipt](evidence/pin_research_round50_20260917.json)
includes source pairs, controls, allocation evidence and independent reviews.

The points routine `819A764C` has an independently reviewed reconstruction that
removes three of five pins. It replaces three fake external epilogue calls with
ordinary returns, uses the actual message symbol, and addresses the global flag
word directly. Its interface and real helper calls are unchanged.

The old source is exact at `2.7.2 -fno-strength-reduce`; the new source is exact
at `2.7.2-cdk -fno-strength-reduce`. The cross-combinations fail: old/CDK has
distance five; natural globals/plain has distance thirteen and two extra words.
This follows the reviewed whole-function reconstruction route. The stricter
automatic cell-correction rule is unchanged.

CDK's natural symbol lowering supplies the concrete mechanism: the message low
half fits the call delay slot, and the global flag high half fits a branch delay
slot. Exact bytes establish the reproducible recipe. They do not prove the
historical compiler release. No compiler or assembler behavior was modified.

## Why the two input pins remain open

The individual and combined erasures all fail. A local-allocation explanation
correctly reports that this is a global allocation and directs us to the global
trace. That trace is valid and reproduces the uninstrumented assembly.

The input pointer has 31 references and live length 96, giving priority 12,916.
It takes `s0` before the loop index (priority 9,750) and cursor (9,705), which then
take `s1` and `s2`. Retail instead holds the input in `s2`, index in `s0`, and
cursor in `s1`. There are no register preferences directing the allocation.
This explains the role cycle without declaring either pin necessary.

The next source question is the actual record layout: five points with an
eight-byte stride, initial point at +4, intermediate points at +12/+20/+28, and
target point at +36. Investigate its real index/cursor lifetimes. Do not insert
fake uses or retain dead work to manipulate allocator priority.

## A false lineage conflict corrected

The inherited fingerprint treated every non-stack store in a call or jump delay
slot as CDK/2.8 evidence. All four such stores in this target address object-local
fields. A two-line ordinary pointer-store probe compiled by unmodified plain
GCC 2.7.2 emits a store in a call delay slot too. That disproves the unqualified
rule; an exact pinned baseline alone would not have done so.

The repository-local `tools/lineage_fingerprint.py` now retains these stores as
scheduling observations without letting them alone determine the compiler
family. It requires an explicit overlay, reads current clean-ledger targets, and
accepts an explicit body slice for rows containing bank data. Existing split-store
and guarded zero-copy evidence is retained. Five focused regression tests pass.
Use this local tool for future work; the reference checkout is unchanged.

A follow-up on Gemini's archived `8195AB84` removes the automatic local-store
conflict, but its two-register address split remains a useful clue. At stock CDK
with its existing flags, the old source is exact while the saved candidate still
misses nineteen substitutions. No new source menu or removal is claimed.

## Luna's near match closes with the real helper contract

The second epilogue-only target, `818B78E8`, had one scheduling keep. Luna's six
bounded probes recovered ordinary local control flow, direct argument accesses,
and the actual counter updates. Its best zero-pin source matched 186 words
apart from one instruction-order pair: zero substitutions and two reorder
indels. The frame and all register roles already matched.

The remaining constraint came from an inherited call with three arguments.
The resident helper `func_800478B8` takes only the entity pointer and forwards
that pointer to two update steps. Declaring that actual signature and passing
one argument makes the counter increment schedule naturally: **186/186 words
exact at unchanged `2.8.1-G0`, zero pins**. The public three-pointer entry
contract is unchanged. No helper implementation or backend change is required.
The final source uses the already-proven runtime name `func_800250E8`.

This result supports function-level delegation with accurate callee facts and
root residual review. It does not establish a universal prototype rewrite:
earlier isolated helper-arity probes were negative, and this function needed
the complete return/counter/dispatch reconstruction together.

## Transfer and next work

This wave's direct erasure cascade adds zero beyond the complete repairs.
The remaining count measures constraint sites, not distinct C patterns. We have
proven transfers in earlier aggregate-copy and paired-return bodies, but no
validated census of how many distinct patterns the remaining pins represent.
Do not extrapolate the current small cohorts into 6,000 independent hard tasks.

The next bounded actions are to reconstruct the points routine's genuine
five-record traversal using its measured allocation priorities, and to package
the next epilogue-only function with verified helper contracts for Luna or
Gemini. Internal loop targets need their own control-flow/allocation facts.
Use the corrected local fingerprint and measured body boundaries throughout;
no target in this wave is declared impossible.
