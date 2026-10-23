# Contributing

Improve the reconstructed C while preserving its compiled bytes. Support names,
types and ownership with evidence: a byte match establishes output identity,
not the meaning of a proposed name. Keep changes small enough to review as one
function, feature or coherent rename/type change.

## Inputs and rights

Bring your own NTSC-U disc and follow [BUILD.md](docs/BUILD.md) to provision
tools. Genuine native-TU assembler comparison additionally needs the pinned
assembler from your own [Psy-Q SDK](docs/TOOLCHAIN_PSYQ.md).

Do not submit disc images, extracted game files, retail disassembly or hex
dumps, compiled objects, SDK payloads, secrets or private machine paths.
Initialized reconstructed C tables remain game material; [NOTICE](NOTICE)
explains the rights boundary. Original contributions use the project
[licence](LICENSE); third-party material retains its own terms.

## Find the source and record the evidence

Run from the repository root; these lookups need no disc:

```sh
python3 tools/source_layout.py path town/func_8008D54C
python3 tools/source_layout.py ids src/town/scene/copy_words_backward_from_offset.c
python3 tools/source_layout.py --root . check
python3 tools/row_db.py check
```

Use the resolver's current result for the row you are editing. A physical
translation unit (TU) can contain several functions or serve multiple image
placements. Edit its home source and account for every affected consumer.
Do not recreate a historical per-row file or move source without updating its
layout and manifests. [LAYOUT.md](docs/LAYOUT.md) maps the tree;
[the reader guides](docs/guide/README.md) explain features and callbacks.

For a name, cite a string/assertion, dispatch table, callers, data layout or
field use supporting the meaning. For a type, establish offsets, access
widths, signedness, alignment and relationships across its users. For a
control-flow change, explain the behavior and lifetime that the new C expresses.
Put uncertain interpretations in evidence as hypotheses; retain unknown fields
instead of assigning unsupported meanings. See [EVIDENCE.md](docs/EVIDENCE.md)
and [type consolidation](docs/TYPE_CONSOLIDATION.md).

## Prove the changed bytes

Keep the registered compiler and assembler recipe. With your extracted disc
and tools available, a candidate check for the example row is:

```sh
nice -n 10 python3 tools/verify.py town/func_8008D54C \
    src/town/scene/copy_words_backward_from_offset.c --gate
```

Replace the ID and path for your change. `--gate` requests the additional
window check when required; the verifier can report registered scorer/gate
equivalence instead. This diagnostic is useful for iteration, but it does not
replace integration proof or renew a module certificate.

A declaration, shared header or TU edit needs checks of every consuming TU and
placement. For a rename/type/header rewrite, the complete-TU identity helper
can record the before state and compare the after state. This optional helper
also needs `clang` on PATH (`sudo apt-get install clang` on Ubuntu). Set `CHANGED_C` to
the source path being changed, and include each changed header after `--edit`:

```sh
mkdir -p build/review
nice -n 10 python3 tools/typing/tu_identity.py snapshot \
    --edit "$CHANGED_C" --workers 4 --receipt build/review/before.jsonl
# Make the source/header change, then compare against that snapshot.
nice -n 10 python3 tools/typing/tu_identity.py compare \
    --receipt build/review/before.jsonl --workers 4 --results build/review/after.jsonl
```

The helper discovers the affected physical TUs and checks raw object,
canonical assembly and canonical object identity. Inspect failures and the
reported closure; do not present a snapshot made after an edit as a before
proof. [Rename proof](docs/RENAME_PROOF.md) covers aliases and relocations.

For complete integration proof in a provisioned checkout:

```sh
make configure
make -j4
make check
```

The current image proof must bind the changed sources, headers, recipes and
tools. Old passing receipts do not prove new inputs. Complete images,
diagnostic recipe/placement layouts and switch-table contents are compared
with your disc; imported gaps are accounted separately. Native TUs record
whether genuine ASPSX comparison ran. Historical module-certificate renewal
and the all-window loop are retired from this workflow. See
[what the build check proves](docs/BUILD.md#what-the-check-proves).

Run tests for tools or behavior you changed and include the commands, exit
statuses and compact results with the pull request. Explain any retained
limitation or missing required proof. Byte identity and the separate
[quality levels](docs/PLAN.md) both matter; a readability score alone is not
proof that a rewrite is safe.

## Naming and house style

| Thing | Style | Example |
| --- | --- | --- |
| New functions and globals | Short English `snake_case`, without a binary prefix | `spend_actor_mp` |
| Types | `PascalCase` | `ActorRecord` |
| Locals and parameters | `snake_case` | `slot_index` |
| Constants and macros | `UPPER_SNAKE_CASE` | `ITEM_KIND_HERB` |
| Unknown fields | Offset-based `unk_XX` with explicit padding | `unk_1C` |
| Unrecovered functions/data | Keep the address identifier | `func_8008D54C`, `D_80283000` |

Use a verb for a function where it describes the operation; preserve an
original developer spelling proven by the disc. Names need to be unique within
a linked image. Follow nearby C formatting and prefer ordinary expressions,
loops, named locals and typed field access. Retype a declaration rather than
replacing `value->field` with a cast at each access. Do not introduce extra
casts, goto, volatile, inline asm, register pins or `M2C_` workarounds to make a
readability change match. Existing byte-sensitive debt needs an explicit,
evidenced follow-up rather than an unsupported rewrite.

Reuse `ActorRecord`, `PlayerRecord` and `ObjectPosition` from
[include/shared/entity.h](include/shared/entity.h). Actor +0x24/+0x25 is
fractional/integer familiar or monster MP, with `max_mp` at +0x66; the player
has none. `EntityRec` is a legacy view to avoid in new code. Reuse the existing
shared types, flags and IDs described in [LAYOUT.md](docs/LAYOUT.md).

### Declarations and ownership

Decision 74 groups prototypes in **one owning header per source folder**,
`include/<subsystem>/<feature>.h`. Rename declarations with definitions and
callers. A C file includes its own folder header and the owning headers for
its callees; do not add local extern lists or a header per function/C file.
Owning headers include shared type headers. Shared records belong under
`include/shared/` or `include/records/`; library stand-ins belong under
`include/sdk/` and must not copy SDK header text. Data externs belong with
their definition's folder, or in per-image data headers for retail imports.
Keep a byte-sensitive exception documented when moving it changes output.

Matching copies share one home implementation through placements (decision 75).
Do not duplicate C to make a second image work. See
[decisions 61, 73, 74 and 75](docs/evidence/r97_decisions.md) and
[symbol conventions](docs/SYMBOLS.md).

### Names, constants and generated records

Function/data aliases and evidence live in `config/names.tsv`.
`python3 tools/apply_names.py --help` describes proposal and dry-run options;
read them before applying names, then check all affected consumers. Use
shared concept headers for reused constants and types, and local definitions
for private implementation details. Keep the reasoning separate from proof
hashes so a reviewer can assess both.

`STATUS.md`, container `INDEX.md` files and most of `ledger/` are generated or
machine-maintained. Use their tools rather than hand-editing measurements.
Do not hand-edit hash-guarded `config/link_graph/` shards. Keep proof attachments
small; summarize larger results with hashes and reproduction commands rather
than adding binary output or large dumps.

## Report a problem

Use the repository's issue tracker. Distinguish a build/tool failure, an error
in the reconstruction or documentation, and a bug already present in the game.
Include:

- the commit/revision, supported disc region and host/tool versions;
- exact commands or gameplay steps, expected result and observed result;
- the affected row ID, symbol, source path or image/offset if known;
- the first useful error and a compact text log or evidence for the suspected
  name/type/behavior error.

Do not attach game/SDK files, save data, retail dumps or private paths. You can
report a source/documentation issue without a disc; state which checks you
could run. Consult [BUGS.md](docs/BUGS.md) first for preserved gameplay bugs.
That page maps community reports to code and credits the **adrando randomizer
guide**; retain that attribution when extending it. A byte-exact reconstruction
preserves retail behavior, including bugs. Report a proposed behavior fix
separately and explain that it changes the game's bytes.

## Before submitting

Check source/layout consistency and the links in the public documentation:

```sh
python3 tools/row_db.py check
python3 tools/source_layout.py --root . check
python3 tools/docs/check_links.py README.md CONTRIBUTING.md docs/BUILD.md docs/LAYOUT.md docs/README.md docs/guide
python3 tools/prepublish_scan.py
```

Review the diff for unrelated generated changes and include the evidence,
commands and results needed to reproduce your proof. Do not submit ignored
build products. For documentation-only changes, link and example checks are
appropriate; explain any command you could not verify.
