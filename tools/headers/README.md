# Header ownership tool

`python3 tools/headers/headers.py table --data --out <output>` records current
function sites, SDK classification and the complete data plan. `dryrun --data
--scope src` prints the static whole-tree plan. `apply --decide-only --data
--scope src --out <output> --workers 4` decides it with compiler assembly and
restores temporary headers. Omit `--decide-only` to write accepted edits.

## Extern wave (one folder per run)

`tools/headers/extern_wave.py` is the lane driver for the local_externs debt
(tools/lint/debt_check.py). One run plans one folder, byte-decides every
(TU, header) include, applies the accepted edits and proves complete-TU
identity for every registered physical TU whose include closure contains an
edited file (the folder TUs and every consumer of a changed header):

```sh
python3 tools/headers/extern_wave.py --folder src/engine/audio --recursive \
    --skip-list <files owned by other lanes> --out <dir> --workers 4 \
    --deps-cache <dir>/../deps.json.gz [--data] [--dry-run]
```

A changed TU is rolled back (its own edit first; several edited members of
one physical TU are retried file by file; then every changed header in its
closure with the folder TUs that needed it), repeated until the final state is
the proven state. Files whose per-function lexical debt rises are restored.
Outputs: receipt.json (local externs before/after, proof set, holds by reason),
holds.tsv, files.tsv, folder.patch and wave.log. SLUS partitions and members of
a physical TU, which the assembly filter cannot compile alone, are decided by
the complete-TU proof of the physical TUs that see them.

Existing owning headers are append-only. Hand-written headers and the headers
this tool once generated (since edited by hand: types, comments, data) are
never regenerated: a needed name the header lacks is appended after an
`APPEND_MARK` comment before the include guard's `#endif`, with its type
includes and tag forward declarations. A name the header (or its closure)
declares with a different type is a TU hold (`hand_written_header_differs`);
an appended name that another consumer of the header declares incompatibly is
a TU hold (`consumer_conflict`). Only headers that do not exist are generated
whole. New includes go after the last include that precedes the first removed
declaration, function definition, initialised object or included code fragment.

`python3 tools/headers/census.py --out <dir> [--data] [--verdicts verdicts.jsonl]`
maps every debt-checker local_externs site to its outcome (planned/proven
removal, byte hold, static keep reason, or unmodelled) by reason and folder.

Data rewriting is opt-in (`--data`). Keep tree-wide application off until the
data-name changes have landed. Pilot scope:
`--scope src/engine src/slus src/frontend src/main`.
Handwritten headers are not rewritten: compatible legacy data declarations may
remain alongside the generated owner. Global one-declaration completion needs a
legacy-header fold with every consumer snapshotted and proved. `table` lists
these in `data_legacy_headers.tsv`; the data plan reports C-local eligibility
separately from `global_status` / `global_reason` for the uniqueness goal.
Functions-only reruns preserve data declarations and includes already installed
by a prior `--data` pass; they do not move additional local data externs.

The SDK classifier uses the pinned SLUS segment intervals and symbol addresses,
including numeric `func_` aliases. Its stand-ins are independently written
contracts, with common scalar aliases and opaque pointers for SDK records.
There is no proprietary SDK header input. A library match without a reviewed
signature stays local as `sdk_signature_unresolved`. Unknown names stay local;
a numeric-looking name alone is not evidence that a function remains in asm.
`config/names.tsv` provides explicit ownership evidence for renamed C aliases.
An asm owner requires an actual `INCLUDE_ASM` invocation and unanimous typed
caller declarations. Each SDK header carries decision 74's replacement notice.

Data ownership follows a unique C definition, otherwise the importing image.
All views of a symbol must agree, including qualifiers and array extents. This
is deliberately stricter than C compatibility: extent changes can alter `-G8`
addressing. Anonymous/private types, multiple definitions, complex declarators
and named extents remain holds. Existing generated declarations seed ownership
on reruns, even after all local externs have been removed. No owning header
includes another owning header.

A TU/header is atomic: if one declaration cannot move, that TU keeps the local
declarations for the entire header. Compile errors and changed assembly are
recorded, never accepted. `explain --data --tu <source> --header <header>` shows
the compiler diagnostic or assembly difference for one attempt.

Before any source write, take a `tools/typing/tu_identity.py snapshot` of every
physical consumer. After applying, compare raw objects, canonical assembly and
canonical objects. Verify the dependency closure, refresh layout-inline records,
check the row database, rebuild SLUS fresh and gate only windows covering the
changed overlay TUs (`windows.py --tus <edited.txt> --args`). The assembly filter
is not a substitute for these proofs. Worker limit: six; gates use four.

`triage.py --out <output>` audits wrong-signature candidates without changing C.
It requires unanimous direct-call arity, no address-taking, unanimous explicit
caller arity/types for added parameters, and unused removed formals. Proposals
still require manual body review and complete physical-TU proof, including any
partition consumers. A void body without proven return evidence stays held. A simple tail call can
justify an explicit return only when the callee, every caller and complete-TU
bytes agree.

Tests: `python3 -m unittest discover -s tools/headers -p 'test*.py' -v`.

Function addresses are excluded from the data import plan (`data_is_function_address`).
`handler_addresses.py` resolves exact C entries using the defining row's address
space, resident/engine ownership, and image-scoped link placements. Coincident
numbers in another overlay do not establish ownership. Retype these imports to
the definition's folder header and prove every affected consumer before applying.
Export the live address-declaration census with:
`python3 tools/headers/handler_addresses.py --root . --out <output>`.

Before changing a resolved address alias to a readable function identifier, check
its canonical spelling through every linked placement:

```sh
python3 tools/headers/check_handler_bindings.py --root . --map retypes.tsv --out binding_checks.tsv
```

This uses ccproc's last-row name mapping and the object rebinder's address rules.
A copied callback can have a different address from its canonical home function.
Keep such imports held until the producer can represent the typed placement alias.
A known C entry and a compatible prototype alone do not prove this substitution.
