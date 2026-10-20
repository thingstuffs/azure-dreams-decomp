# Proof and source quality

The goal is readable C that rebuilds the retail game's exact bytes. Byte equality,
coverage, historical provenance and source quality are separate claims. The
[generated status page](../STATUS.md) reports their measured state; this page
defines the terms without duplicating changing totals.

## What is checked

| Check | Scope and limit |
|---|---|
| Per-row verification (`tools/verify.py`) | Ordinary SLUS rows compare pinned objects; overlay rows compare retail slices. Grouped SLUS candidates use their module/partition image context. This is the candidate feedback step. |
| Overlay window gate | Compiles and links a complete selected region against the extracted container. It checks placement and resolved targets that a row-only score can miss. |
| SLUS image gate | Rebuilds the executable and checks its retail SHA-1 and pinned build recipe. |
| Module/placement certificate | Binds the reviewed source, headers, recipe, tools, ownership and affected gate results. Required native-module checks include genuine-ASPSX comparison. A stale certificate grants no current placement proof. |
| Byte-map census | Accounts for physical container extents, including code outside registered C, library code, data and unresolved spans. It does not turn a data label into compiled C. |

Use [source locations](SOURCE_LAYOUT.md) to resolve row IDs to the editable TU.
Use [link lists](LINK_LISTS.md) to understand multiple placements of that TU.
Code sharing and compilation boundaries need evidence; adjacency alone does not
prove a historical source file.

## Quality levels

These levels accumulate requirements. `tools/levels.py` implements the exact
predicates and writes `ledger/levels.jsonl`; `tools/status.py` presents them.
The labels describe recorded, verified work, rather than a subjective reading
of a source file.

| Level | Additional requirement |
|---|---|
| L0 | Recorded byte-exact baseline at the registered recipe. This alone says little about readability. |
| L1 | No decompiler boilerplate or blocking fidelity spelling; pin erasure has been attempted where pins remain. Whole functions emitted as assembly remain blocking. |
| L2 | Typed access replaces raw `M2C_FIELD`/`FIELD` access. Partial types may retain unknown fields. |
| L3 | A recorded source refinement is present, and every tail-jump dependency has an acceptable split audit. Unresolved or intra-function pseudo-call boundaries block it. |
| L4 | Reviewed current module placement, no pins or tail-jump dependencies, and no source-driven assembler imitation or contradictory compiler-cell fingerprint. Shared declarations and evidence-backed membership are part of the module review. |
| L5 | No remaining blocking fidelity site, computed goto, inline assembly, `NON_MATCHING` guard or recorded compiler-model dependency. |

A byte-verified real `jal` call with no assembler rewrite can be excluded from
the tail-jump count when its split audit establishes that fact. A real call to
a non-returning function is not automatically a pseudo-call. The evaluator also
distinguishes a source-dependent assembler workaround from an accepted model of
an unavailable historical compiler. See [FIDELITY.md](FIDELITY.md).

The machine-readable `l4_residue` and `l5_residue` fields explain why a row stops
at its current level. A module certificate alone grants neither L4 nor L5, and
an exact C row does not prove that all other code in its container is decompiled.

## Making a change

Explain the evidence for the name, type, source shape or module boundary.
Compare the candidate at the registered recipe, run the affected window or image
gate, and refresh certificates whose bound inputs changed. A header change can
affect multiple containers; a shared TU can affect multiple placements.
See the [documentation index](README.md) for a concrete lookup/verification
example and [type consolidation](TYPE_CONSOLIDATION.md) for shared types.

Preserve measured failures as explicit limits. An address, successful link or
passing byte comparison cannot by itself establish a type's meaning, a source
filename, a runtime load path or unreachable code.

The [decision record](evidence/r97_decisions.md) preserves the historical rulings.
Earlier entries can describe superseded tooling and totals; use the current
guides and generated status when checking a contribution.
