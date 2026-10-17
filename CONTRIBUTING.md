# Contributing

Thank you for looking. This is a byte-exact decompilation: the C must compile to exactly the bytes
the retail game contains. That makes contributions easy to judge, and it is the whole contract.

## Before anything: legal ground rules

- Do not add game data to the repository: no disc images, executables, extracted files, hex dumps
  of retail code or data, or disassembly of retail code. `tools/prepublish_scan.py` checks for
  these; run it before you open a pull request.
- You need your own copy of the game to build and verify (see the README).
- By contributing you agree your original contribution is released under the project licence
  ([LICENSE](LICENSE)); see [NOTICE](NOTICE) for what the licence does not cover.

## Set-up

```sh
cp "/path/to/Azure Dreams.bin" "/path/to/Azure Dreams.cue" bin/
tools/setup.sh
```

## What a good change is

1. **It is still byte-exact.** Nothing is accepted on appearance.
2. **The C is closer to what a person would write**: typed structs instead of raw offsets, named
   locals, loops and conditionals that read as loops and conditionals, no leftover compiler
   workarounds. A readable change that matches beats a clever change that matches.
3. **It records its evidence.** If you rename or retype something, say what in the game justifies it
   (a string, a table layout, a call pattern). Guesses about gameplay meaning belong in a comment
   marked as a guess, not in a name.

## How a change is proven

```sh
# one function: compile it through the project's toolchain and compare with your disc's bytes
python3 tools/verify.py <container>/<func> path/to/candidate.c
# the proof of record, for what you touched:
tools/build/build_slus.sh                            # if you touched src/slus (SHA-1 of the whole executable)
bash tools/build/mk_ovl_root.sh && python3 tools/build/gate_all.py    # overlay windows
python3 -m unittest discover -s tools/tests         # tool tests (no disc needed for most)
```

`tools/verify.py` is the quick check; the window gate (`gate_all.py`) and the SLUS SHA-1 gate are the
proof of record. A function only counts as done when the gate for its window says it matches.
Refined function bodies go in through `tools/promote.py`, which re-verifies before it writes
`src/`; the result is journalled in `ledger/promotions.jsonl`.

Keep each change small (one function, one module, or one rename batch) and say in the pull
request which gate you ran and its result.

## Layout of `src/`

One function (or one data object) per file, `src/<container>/<name>.c`. A function with no
recovered name keeps its address name, `func_800A8714`; data is `D_80283000`. Do not move or
rename files by hand: the row database in `ledger/splits/` and the gate windows refer to them.
Renames go through `tools/apply_names.py` (below).

## Naming conventions

| thing | style | example |
|---|---|---|
| functions | `snake_case`, no binary prefix, starts with a verb where it does something (decision 61; older `camelCase` names are being converted) | `init_monster_from_stats`, `bcd_to_int` |
| types (struct, union, enum, typedef) | `PascalCase` | `MonsterStats` |
| local variables, parameters | `snake_case` | `slot_index` |
| macros and constants | `UPPER_SNAKE_CASE` | |
| unknown fields | `unk_XX` (hex offset) with explicit padding | `u8 unk_1C;` |
| unrecovered functions / data | address name | `func_8008D54C`, `D_80283000` |

Names describe the verified mechanical operation, not guessed gameplay. Say "medium" confidence in
the evidence column when you are not sure.

### Where names and types are tracked

- `config/names.tsv` - function and data renames. Columns: address, old name, new name,
  evidence. The build keeps the original section name and adds an alias, so a rename never changes
  the bytes. Add rows with `python3 tools/apply_names.py <proposal.tsv> [--dry-run]`, which refuses
  duplicates, rewrites the sources and verifies every touched function.
- `ledger/names.jsonl` - the journal of every rename attempt and its verification result.
- `include/shared/`, `include/records/`, `include/modules/` - shared game types. Merge duplicates
  into the shared type rather than adding a new per-function view (see
  [docs/TYPE_CONSOLIDATION.md](docs/TYPE_CONSOLIDATION.md)).
- `docs/SYMBOLS.md` and `docs/EVIDENCE.md` - where the evidence behind names is explained.

## Cleanliness levels

Rows are ranked L0 to L5 (see [docs/PLAN.md](docs/PLAN.md)); `python3 tools/levels.py` computes
them and `STATUS.md` reports them. Raising a function a level is a good contribution; lowering
the level of another function is not.

## Generated files

`STATUS.md`, `src/*/INDEX.md` and most of `ledger/` are generated or machine-maintained. Do not edit
them by hand; the tools regenerate them.

## Before you push

```sh
python3 tools/prepublish_scan.py     # no game bytes, no private paths, no tokens, nothing oversized
```
