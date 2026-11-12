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

## Bulk extern wave (many folders per run)

`tools/headers/extern_bulk.py` runs the same planner over many folders at once and proves the result on the
build graph only (no per-include assembly filter, no standalone TU capture):

```sh
python3 tools/headers/extern_bulk.py --scope src/dungeon/effect src/dungeon/item ... \
    --write include/dungeon/effect include/dungeon/item ... --append-shared \
    --port-adapt <native port>/tools/adapt.py --out <dir> --workers 4 [--plan-only] [--data | --data-named-only]
```

Settling rounds use screen proofs (`affected.prove(select=)`: one recipe per compiled source / family / copy
kind); one full proof accepts.  Failures are blamed without bisection (an appended prototype the compiler
names, the failing TU's own edit, the merged-TU members it compiles, names its source mentions, then the
includes it sees).  Never removed or published: recorded prototype floors, generated `S_<addr>` types in
prototypes, port adaptation anchors, decoded-image sources; new headers only with `--new-headers`.  Header
texts are always built from the committed header (append-only block).  `--plan-only` gives the static yield.

`tools/headers/extern_classes.py --out <dir> [--plan-sites <census.py sites.tsv>]` classifies every
local_externs site from build/codemap.db (function vs data, visible/elsewhere/no header, identical vs
disagreeing, no C definition, `D_` vs named) in seconds and fuses it with the planner census.

## Per-name extern trial

`tools/typing/extern_trial.py` drives the bulk machinery one name at a time: every local `.c` declaration of
each selected name is replaced by an include of its owner header (the definition's folder header, or the
`include/sdk` stand-in), each name planned alone per TU, so one name's hold never blocks another.  A TU
whose other local declarations disagree with what the owner header declares is held
(`existing_header_other*`), because only the trial's name moves.  The proof is `settle()` here (screen and
full build-graph proofs, blame restores the TU), then `tools/lint/lint_closure.py` against HEAD; a TU with a
new warning site is restored and the state proved again.  TUs restored together with another selected name
are retried per name.  Without `--append` an owner header that lacks the declaration is a `missing_owner`
hold.  `D_` names and prototype floors are never tried.

```sh
python3 tools/typing/extern_trial.py --top 50 --lint-port <native port> --port-adapt <native port>/tools/adapt.py \
    --out <dir> [--exclude-names-file F] [--recent-repo R --recent 40] [--plan-only | --dry-run]
```

`receipt.json`, `names.tsv` and `sites.tsv` give per name the files declaring it, kept and held, with a
reason class (type_disagreement, new_warning, byte_change, missing_owner, foreign_import, prototype_floor,
site_form, port_anchor, debt_rise, other) and the raw reason.

## Callback installs hidden by data aliases

`installer_names.py plan --edges <reviewed-hidden-edges.tsv> --scope src/town --out <dir>`
plans `data_alias_install` rewrites. It checks the callback's exact linked entry in every
installer image, including compiled placements. Unconfirmed banks and copy bindings hold;
a placed callback requires the same-image copy-link record. The reviewed table supplies
candidates, never authority to resolve an address in an unrelated image.

`apply --plan <dir>/plan.tsv --out <receipt>` includes the owner prototype, appending
unpublished prototypes through the existing header type rules when possible, and replaces
`&data_alias` or a decaying array alias with the function designator. It removes single-name
local extern declarations and preserves existing destination casts. No new cast is added;
native compiler failures must be held or resolved with a separately recorded cast.
`&array_alias[0]` also becomes the designator; data reads and nonzero indexing hold.
Native module inventories are synchronized: self addresses cease being imports, and
external data views become function imports at the same proven entry.

`retire --plan <dir>/plan.tsv --out <receipt>` removes dead extern-only alias declarations
and unused data-alias name rows. Live users, real storage and excluded dungeon source
declarations retain the alias. Regenerate the registry, module graph and link graph after
name/link changes. `measure --plan <dir>/plan.tsv --out <receipt>` counts visible install
and comparison edges from codemap's compressed type-flow facts. Refresh the codemap first.
Use `retire --dry-run` to audit remaining users before a name/link batch.
Every source batch still needs the complete build, native and debt proofs described above.
