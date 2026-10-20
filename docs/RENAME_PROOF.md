# Checking a spelling-only change

A rename needs two reviews: whether the new name is supported by evidence,
and whether the edit preserves the compiled result. Object equality can check
the second; it cannot establish the first. Follow the naming rules in
[SYMBOLS.md](SYMBOLS.md).

## What neutrality requires

`tools/rename_proof.py` contains the token and ELF comparison primitives.
`check_renames` permits a consistent, injective identifier replacement while
keeping literal spellings, numbers, keywords, punctuation, directives and token
counts fixed. Comments and ordinary whitespace may change. It conservatively
refuses ambiguous captures, swaps, partial mappings and unsupported tokens.
This is a token check, not a C binding resolver.

`compare_objects` checks allocated section contents and order, section metadata,
ELF ABI/flags, non-FILE symbols and relocations targeting allocated storage.
NOBITS sizes count. No instruction or relocation bits are masked; equal call
instruction words cannot conceal a changed relocation target. Non-allocated
debug/comment metadata is outside this comparison.

Compile both sides at the registered recipe in the complete physical context.
Then verify both against retail. A comment can change `__LINE__`, and a local
name can affect an old compiler's register allocation, so a token-only check is
insufficient. The public primitive module's historical command wrapper depends
on internal workflow files; it is not the recommended public-clone entry point.
Use the public verifier described in the [documentation index](README.md).

## Shared headers and complete TUs

A header rename affects every dependent row, including users with unchanged
source text. Verify the complete population. An inlined member must be checked
in its physical TU, and executable partitions may emit more than one compiler
stream. A single member's unchanged slice cannot prove its siblings or owned
data. Use [source locations](SOURCE_LAYOUT.md),
[executable modules](SLUS_MODULES.md) and [partitions](SLUS_PARTITIONS.md).

Function/global renames also update the alias/evidence workflow in
`config/names.tsv` and `ledger/names.jsonl`. Local/member spelling changes do
not replace that workflow. Preserve canonical linked identities.

## Acceptance

Retain the before/after source hashes, recipe and dependency hashes, object
comparison and retail verdict. A changed or missing input makes an old receipt
stale. Run the affected window/image gates and renew any certificates that bind
changed inputs. Neither a retained receipt nor a spelling-only description
waives those checks.

Receipts should contain measurements and hashes, with large detail archived as
specified in [decision 62](evidence/r97_decisions.md). Do not commit compiled
objects or retail dumps as rename evidence.
