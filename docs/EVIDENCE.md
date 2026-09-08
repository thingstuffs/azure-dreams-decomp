# Naming and module evidence (what the disc and earlier analysis tell us, per row)

*Index written 2026-09-08. Machine-readable form: `ledger/evidence/` (built by `tools/evidence.py build`,
per-row merge in `ledger/evidence/rows.jsonl`); coverage table in `STATUS.md`.*

The lanes that name things (L2 locals and summaries today, L4 names and modules next) must not
guess where a fact exists. This page lists every source of real names the tree holds, what each
one proves, and how each level consumes it. All of it is in-tree; nothing reads another checkout.

## 1. Sources

| source | in-tree file | what it is | strength |
|---|---|---|---|
| **Konami / Sony assertion sites** | `docs/evidence/konami_assertion_sites.md` + `.csv`; joined to rows in `ledger/evidence/assertions.jsonl` | PSY-Q `assert()` compiles to `printf("Assertion failed: file \"%s\", line %d\n", __FILE__, __LINE__)`; Konami shipped debug builds of several modules, so 458 site copies (89 distinct) name **15 real source files** with exact line numbers: `main.c`, `lshop.c`, `player.c` (TOWN game code), `tobjs.c`, `sn_main.c`, `flgtst.c` (TOWN devkit blob), `c_server.c` (Sony libcard), `card_mes.c`, `card_opt.c`, `card_win.c`, `cardbk.c`, `cardinfo.c`, `cardslot.c`, `cardsme.c`, `memory.c` (MAIN.BIN card UI). | **hard fact**: a function containing `main.c:40` is in `main.c`, full stop; functions inside one object are in source-line order |
| **Developer identifiers** | `ledger/evidence/dev_identifiers.json` | The `%s = %d` debug prints keep the **expression text**: `((u_long)p - (u_long)ost_w)/ sizeof(OSETDT)`, `osel_w`, `cdhd_cnt`, `ov_work.kind`, `p->kind`, `gsw->check_sum`, `card_first_flg`, `head`, `ptr[n].vx`, `ptr[n].vy`, `kind`/`mode`/`sno`, `s0[0]`/`s1[0]`/`s[0]`, `cnt`. These are the developers' own variable, type and member names. The `main.c` triple (`OSETDT`, `ost_w`, `osel_w`, `cdhd_cnt`) is linked into **every one of the 54 TOWN event-script modules** (54 copies), which is why it looked script-related: it is the town-scene `main.o` that each script module carries. Also the developer path strings (`\vx035\data\sn\SENGEI00.BIN`, `\vx035\data\town\st.bin`), save names (`BASLUS-00614`, leftover `BISLPS-00001`) and libcard device names. | **hard fact** for the text; the owning file is proven for `main.c`/`c_server.c`, inferred for `kind`/`mode`/`sno` (`flgtst.c`?), unknown for `head`/`ptr[n]` and `s0[0]` |
| **Randomizer address map** | `docs/evidence/adrando-findings.md`; facts in `ledger/evidence/adrando_map.json` | The Azure Dreams De-Randomizer's `romAddresses` / `rowLength` / `monsterStats` map, verified against this disc: 90 named addresses (data tables such as `initialStatsTable` @ `0x8006D168` = 24-byte records with `attack@0 … flyingLiftable@22`, `trapTable` @ `0x80072CD0` = 12-byte records, `statGrowthTable` = 8-byte, `itemCategoryTable`, `floorMonsterTable`, `usedBallItemTable`, text strings, and code sites such as `checkKohDeathTopFloor`, `placeMonsterRollGamma`, `initMonsterSpawnRate`, `eggBombLevelUp`). Item category enum (`TYPE`), trap enum, spell ids, LCG constants. Facts only (addresses, sizes, names); no code from that project. | **strong** for data-symbol names and record layouts; the code-site names describe what the randomizer patches there, i.e. what the surrounding function does |
| **Resident pointer tables** | `ledger/evidence/vm_tables.json` | The event-script VM handler table at `0x8006AA90` (89 entries: entry *i* handles opcode *i*; four slots share the 8-byte "unimplemented" stub; the 89th word is the default state-transition dispatcher) and five more resident function-pointer tables (`0x8006AC9C` 19, `0x8006AD74` 12, `0x8006B01C` 33, `0x8007AED8` 40, `0x8008077C` 16). Each entry is resolved to the SLUS row that defines the target. | **hard fact** for opcode numbering and "called through table X"; the opcode *meaning* still has to be read from the handler |
| **Prior per-function notes** | `ledger/evidence/knowledge/<func>.json` | 281 notes carried over from the matching campaign (`doc`, typed `globals` with the reasoning behind the declaration, `calls` with callee summaries). | **medium**: written while matching, verify against the code before using a name |
| **Applied names** | `config/names.tsv` | The 20 function renames already applied through the alias mechanism (`tools/build/ccproc.py`), each with its evidence line. | applied |
| **Record headers** | `include/records/Rec_*.h`, `ledger/records.json`, `docs/STRUCT_CENSUS.md` | The T7 shared record layouts (member offsets proven by every user). Member *names* are the L4 deliverable; the layouts are the frame the names go into. | layout proven, names pending |

Sizes: 39 rows carry an assertion site (18 MAIN, 21 TOWN; 430 copies), 13 rows print a developer
identifier, 52 randomizer code sites resolve to a function (24 DUNGEON rows) and 22 rows reference a
randomizer-named data table, 72 SLUS rows are pointer-table targets, 408 SLUS rows have a prior note:
562 rows in all (`STATUS.md` keeps the live table). 34 assertion copies sit in functions the tree does
not own (the devkit blob `tobjs.c`/`sn_main.c` functions and the unnamed `head`/`ptr[n]` object):
`ledger/evidence/assertions_unowned.json` keeps them for the module map.

## 2. The implied source map (TOWN scene overlay, front to back)

From `konami_assertion_sites.md` §4.1, one TOWN chunk in link order; the same shape repeats in the
other 53 script modules (most carry only the `main.o` subset):

| true vram | object | proof |
|---|---|---|
| `0x80018544` | unnamed object (vertex walker) | `head`, `ptr[n].vx`, `ptr[n].vy` |
| `0x80018AC4` – `0x80018E70` | `lshop.o` | `lshop.c:65`, `:113`, `:118`, `:128` in three consecutive functions |
| `0x800191A4`, `0x80019278` | `main.o` (top of file) | `main.c:40`, `main.c:55` (revision B: `:39`, `:54` in 7 modules) |
| `0x80019D04` | `main.o` (object-set code, ~0xA90 B later) | `OSETDT` / `ost_w` / `osel_w` / `cdhd_cnt` |
| `0x8001A2A4` | `player.o` | `player.c:64` |

MAIN.BIN: `c_server.c` (Sony libcard) in two revisions (shipped at `0x80020000`, devkit at
`0x80400000`), then Konami's card UI files. The TU boundaries this fixes are the ones the L4 module
step must respect: `lshop.o` / `main.o` split between the end of the `lshop.c:128` function and the
start of the `main.c:40` function; `main.o` / `player.o` split after the object-set function.

## 3. How each level uses it

- **L2 / L3 lanes (`tools/agent_task.py`)**: the prompt carries the row's block (`tools/evidence.py
  show <row>` prints it). Rules in the block: assertion file:line must stay exactly as it is (it is
  the proof of placement); expression identifiers are the real names for the matching locals and
  globals; randomizer table names and layouts read the `D_` symbols; a pointer-table entry says the
  function is opcode *i*'s handler; prior notes are candidates to verify, not facts. Function
  symbols stay `func_XXXXXXXX` in the lane (renames go through `config/names.tsv`), member names
  stay `unk_XX` (they are named once in `include/records/`). The journal records `evidence: true`
  on every row that had a block, so the effect can be measured.
- **L4 names (`config/names.tsv`, `include/records/`)**: start from the evidence rows. Order of
  trust: assertion text and developer identifiers (verbatim), randomizer table names (verbatim for
  data symbols: `D_8006D168` → `initialStatsTable`), pointer-table roles (opcode numbering), prior
  notes (verify), call-site roles. A name with no evidence line is not applied.
- **L4 modules (`src/<container>/<module>.c`)**: a row with an assertion source file goes in the
  module of that name (`main.c`, `lshop.c`, `player.c`, `c_server.c`, `card_*.c`, `memory.c`);
  rows between two proven objects go with the object the link order implies; everything else by
  call-graph cluster and address range. `ledger/levels.jsonl` carries `evidence: [...]` per row so
  the gate can check that a row with `assert_sites` is in a module consistent with its file.
- **The card-UI devkit modules** (`card_*.c`, `memory.c`) and the TOWN devkit blob (`tobjs.c`,
  `sn_main.c`, `flgtst.c`) are debug builds that shipped by accident; they are named from the
  evidence like everything else but are not game code.

## 4. Re-deriving

```sh
python3 tools/evidence.py build          # from docs/evidence/*.csv, ledger/evidence/adrando_map.json, knowledge/, baserom, config/names.tsv
python3 tools/evidence.py census         # the STATUS.md table
python3 tools/evidence.py show town/func_8032F844
python3 tools/levels.py && python3 tools/status.py
```

`tools/evidence.py import --adrando-constants <constants.js> --knowledge-dir <dir>` was the one-time
import (2026-09-08) from files given on the command line; the results are committed, so nothing
standing depends on it.
