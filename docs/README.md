# Documentation

This project reconstructs Azure Dreams for PlayStation as readable C and checks
the result against a user-supplied NTSC-U disc (`SLUS-006.14`). Start with the
[repository README](../README.md) for setup and [generated status](../STATUS.md)
for measured coverage and remaining limitations. The
[contribution guide](../CONTRIBUTING.md) describes submitting a change.

## What to read first

| Your goal | Read |
|---|---|
| Find a function after the source reorganization | [Source locations](SOURCE_LAYOUT.md) |
| Understand what a successful match proves | [Proof and quality levels](PLAN.md), then [fidelity limitations](FIDELITY.md) |
| Improve a function or field name | [Naming evidence](EVIDENCE.md) and [symbol conventions](SYMBOLS.md) |
| Improve a shared type | [Type consolidation](TYPE_CONSOLIDATION.md) and [struct census](STRUCT_CENSUS.md) |
| Understand repeated code and disc coverage | [Link lists and byte maps](LINK_LISTS.md) |
| Build all overlay module windows | [Psy-Q requirement](TOOLCHAIN_PSYQ.md) |
| Review compilation boundaries | [Executable modules](SLUS_MODULES.md), [function partitions](SLUS_PARTITIONS.md), [overlay module placements](LL5_MODULE_PLACEMENTS.md) |
| Choose further work | [Open work](OPEN_ITEMS.md) |

## How the proof works

A **row** is a stable record of a function or data extent. Its ID can retain an
old container name or address even when its source file has moved. A **translation
unit** (TU) is one C compiler input; several rows can share it. A **placement**
reuses a TU in another load image. These are different counts.

The per-row verifier helps assess a candidate. The overlay **window gate** links
the surrounding region and compares its bytes to the extracted retail container;
the executable gate compares the complete linked SLUS image. Module certificates
add reviewed membership, storage ownership, genuine-assembler comparison and
input freshness where required. An unchanged object or a zero scorer distance
alone does not establish all of these claims. See [PLAN.md](PLAN.md).

The byte maps also describe library code, data, padding and unresolved spans.
Matching every registered C row does not mean that every byte on the disc is C.
Use the separate coverage and quality tables in generated status.

## Contribute a better name, type or shape

Run these lookup commands from the repository root; they do not need a disc:

```sh
python3 tools/source_layout.py check
python3 tools/source_layout.py path town/func_8008D54C
python3 tools/evidence.py show town/func_8032F844
```

The path command finds the current file rather than assuming a filename from
the row ID. Edit the physical TU when several rows share it.

* **Name:** cite the assertion, developer string, dispatch table or call-site
  evidence supporting it. Use snake_case for new function and global names;
  keep proven original developer spellings. Function/global aliases belong in
  `config/names.tsv`. Review the meaning separately from the byte proof.
* **Type:** establish field offsets, access widths, signedness, alignment and
  ownership across users. Put shared definitions under `include/`; retain
  unknown fields when the evidence is incomplete. Check every affected user.
* **Shape:** explain the control flow or data lifetime that replaces a cast,
  pin or other workaround. Keep the evidenced compiler recipe and compare
  against retail after the change. Record a precise limitation when it remains.

For example, after setup, verify the current source and request the additional
overlay gate when the verifier requires it.
**Requires your disc and provisioned tools; native module windows also require
the genuine assembler described in [TOOLCHAIN_PSYQ.md](TOOLCHAIN_PSYQ.md).**

```sh
python3 tools/verify.py town/func_8008D54C src/town/scene/copy_words_backward_from_offset.c --gate
```

The verifier reports whether it ran a window or used proven scorer/gate
equivalence for a registered true-name row. Use the path resolver again if that
file moves. A shared-header or TU change
needs all affected rows/windows and any stale module certificates refreshed.
[Rename proof](RENAME_PROOF.md) explains why spelling-only changes still need
object, relocation and retail checks. Keep generated `STATUS.md` and source
indexes generated, and submit source, explanation and compact proof receipts
together. Do not submit disc images, extracted assets or compiled objects.

## Evidence and project history

[Evidence records](evidence/) contain the detailed reasoning and measurements.
The [decision record](evidence/r97_decisions.md) includes the source-layout,
naming and publication rules (decisions 60–68). Earlier entries are historical;
later rulings may supersede them.

The public export omits the working journals. Dated evidence and any archived
workflow notes may describe old totals, source paths and removed tools. Use
the current reference pages above for contribution instructions and generated
status for current measurements.
