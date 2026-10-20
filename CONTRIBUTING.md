# Contributing

Contributions should make the reconstructed C easier to understand while
preserving its compiled bytes. Names, types and module boundaries also need
evidence for their meaning; a successful byte check alone cannot establish it.

## Before anything: legal ground rules

- Do not add game data to the repository: no disc images, executables, extracted files, hex dumps
  of retail code or data, or disassembly of retail code. `tools/prepublish_scan.py` checks for
  these; run it before you open a pull request.
- You need your own copy of the game to build and compare against retail (see
  the README).
- By contributing you agree your original contribution is released under the project licence
  ([LICENSE](LICENSE)); see [NOTICE](NOTICE) for what the licence does not cover.

## Set-up

Follow the [README quick start](README.md#quick-start) from the repository root.
It creates `bin/` before copying your disc and provisions the required tools.
Builds and retail-byte verification need your own disc; complete native overlay
proof also needs the [pinned Psy-Q assembler](docs/TOOLCHAIN_PSYQ.md).
Source lookup and row-database checks do not need either input.

## What a good change is

1. **It is still byte-exact.** Nothing is accepted on appearance.
2. **The C is closer to what a person would write**: typed structs instead of raw offsets, named
   locals, loops and conditionals that read as loops and conditionals, no leftover compiler
   workarounds. A readable change that matches beats a clever change that matches.
3. **It records its evidence.** If you rename or retype something, say what in the game justifies it
   (a string, a table layout, a call pattern). Guesses about gameplay meaning belong in a comment
   marked as a guess, not in a name.

## How a change is proven

Start by finding the physical source for the row you want to improve. Run from
the repository root; these checks need no disc:

```sh
python3 tools/source_layout.py check
python3 tools/source_layout.py path town/func_8008D54C
python3 tools/row_db.py check
```

Edit the resolved source in your working tree, keeping the registered compiler
recipe. Then compare it with retail. **This example requires your extracted
disc and provisioned tools; module-window proof may also require Psy-Q.**

```sh
python3 tools/verify.py town/func_8008D54C src/town/scene/copy_words_backward_from_offset.c --gate
```

Use your row ID and the resolver's path for another function. The verifier is
the candidate check; `--gate` requests the additional overlay window proof
when needed. Its output says when registered address evidence makes the row
scorer equivalent instead. That does not renew a module certificate.

The linked window and SLUS image gates are the proof of record. To build all
of them from a provisioned clone, run the executable first, then the overlay
view and windows. **Requires your disc and the pinned Psy-Q assembler/loader
for native module windows.**

```sh
bash tools/build/build_slus.sh -j 4
bash tools/build/mk_ovl_root.sh
python3 tools/build/gate_all.py --workers 4
```

For a focused change, check every affected row/window or executable image.
A shared header reaches all its users, and a TU may be placed in several
containers. Refresh certificates whose bound inputs changed; an old passing
receipt does not prove the new source. See [proof scope](docs/PLAN.md),
[executable modules](docs/SLUS_MODULES.md) and
[overlay placements](docs/LL5_MODULE_PLACEMENTS.md).

Keep each change small (one function, one module, or one rename batch) and say in the pull
request which gate you ran and its result.

## Layout of `src/`

Editable source lives under `src/engine/`, `src/frontend/`, `src/town/`,
`src/dungeon/` and `src/movie/`. Stable row IDs retain container/address names;
several rows can share a TU, and some placements reuse another row's source.
Use [the source resolver](docs/SOURCE_LAYOUT.md) and edit the complete physical
TU. Do not recreate an old per-row file or move sources by hand: the layout,
module manifests and proof records must agree.

A function with no recovered name keeps an address symbol such as
`func_800A8714`; data uses names such as `D_80283000`. A symbol alias and a source
move are different operations.

## Naming conventions

| thing | style | example |
|---|---|---|
| new function and global names | `snake_case`, no binary prefix; functions start with a verb where appropriate | `init_monster_from_stats`, `bcd_to_int` |
| types (struct, union, enum, typedef) | `PascalCase` | `MonsterStats` |
| local variables, parameters | `snake_case` | `slot_index` |
| macros and constants | `UPPER_SNAKE_CASE` | |
| unknown fields | `unk_XX` (hex offset) with explicit padding | `u8 unk_1C;` |
| unrecovered functions / data | address name | `func_8008D54C`, `D_80283000` |

Preserve an original developer identifier when the disc proves its spelling;
see [the naming rules](docs/SYMBOLS.md) and
[decisions 61 and 63](docs/evidence/r97_decisions.md). Names describe the
supported operation. Record uncertain interpretations as hypotheses in the
evidence rather than assigning an unsupported gameplay name.

### Where names and types are tracked

- `config/names.tsv` - function and data renames. Columns: address, old name, new name,
  evidence. Alias lowering preserves canonical linked identities; a spelling
  change still needs verification. `tools/apply_names.py` accepts proposals, refuses conflicting
  names, rewrites references and checks touched rows. Inspect its options and
  dry-run mode before applying your proposal:

  ```sh
  python3 tools/apply_names.py --help
  ```

  Applying a proposal requires the disc and provisioned tools. Complete the
  affected window/image gates afterwards; the rename tool's row checks do not
  replace them. [Rename proof](docs/RENAME_PROOF.md) explains the object,
  relocation and shared-header requirements.
- `ledger/names.jsonl` - machine-maintained rename results, when retained; the
  public export omits internal event history. Include evidence and compact
  verification results with your change.
- `include/shared/`, `include/records/`, `include/modules/` - shared game types. Merge duplicates
  into the shared type rather than adding a new per-function view (see
  [docs/TYPE_CONSOLIDATION.md](docs/TYPE_CONSOLIDATION.md)).
- [Symbol conventions](docs/SYMBOLS.md) and [naming evidence](docs/EVIDENCE.md)
  explain how to support a proposed name.

## Cleanliness levels

Rows are ranked L0 to L5 (see [docs/PLAN.md](docs/PLAN.md)); `tools/levels.py`
computes them and `STATUS.md` reports them. Preserve the proof and quality of
every affected row when improving a function or shared type.

## Generated files

`STATUS.md`, `src/*/INDEX.md` and most of `ledger/` are generated or machine-maintained. Do not edit
them by hand; use their generators. Keep proof receipts to measurements and
hashes. For detail above 2 MB, include a compact summary and SHA-256, following
[decision 62](docs/evidence/r97_decisions.md).

## Before you push

```sh
python3 tools/prepublish_scan.py     # no game bytes, no private paths, no tokens, nothing oversized
```
