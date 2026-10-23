# azure-dreams-decomp status

**Azure Dreams (PlayStation, NTSC-U `SLUS-006.14`) rebuilt as readable C that compiles to the retail game's exact bytes.** This page is generated from the ledger by `tools/status.py`; every figure is computed, none is typed in.

Generated 2026-10-23T09:55:32Z. Baseline: first-pass text frozen 2026-09-07.


## At a glance

| | |
|---|---|
| **Matched** | 21,432 functions and data rows, 8,028,304 bytes, in 5 containers (`slus` = SLUS_006.14 executable, `main` = MAIN.BIN, `town` = TOWN overlays, `dungeon` = DUNGEON overlays, `ovmovie` = OVMOVIE overlay) |
| **Byte-identical to retail** | 21,432 of 21,432 rows (100.0%), 8,028,304 bytes; 0 unverified |
| **Code that is C** | 99.0% as C; 99.5% counting byte-identical copies of C functions proven elsewhere (of 7,619,712 bytes of classified or estimated code in `dungeon`, `main`, `ovmovie`, `town`; `slus` is accounted by its own rows; breakdown under Not yet C) |
| **Assembler scaffolding left** | 0 pin sites in 0 rows (from 25,918 at the first pass) |
| **Readability** | L3 90.6%, L4 12.6%, L5 12.2% of bytes (levels below) |


## Not yet C

Code bytes per binary: `slus` = SLUS_006.14 executable, `main` = MAIN.BIN, `town` = TOWN overlays, `dungeon` = DUNGEON overlays, `ovmovie` = OVMOVIE overlay. Columns **in C** and **SDK library asm** are done: C is compiled and matched, and PsyQ SDK library code is reported as library, not a decompile target (decision 55). The columns **byte-identical copies of C**, **undecompiled split segments**, **other hand asm / unported** and **heuristic only** are not yet C; **not yet C** is their sum.

| container | code bytes | in C | C % | byte-identical copies of C | undecompiled split segments | SDK library asm | other hand asm / unported | heuristic only | not yet C (excl. library) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| `slus` (SLUS_006.14) | 225,000 | 180,900 | 80.4% | 0 | 0 | 43,872 | 228 | 0 | 228 |
| `main` (MAIN.BIN) | 70,676 | 66,260 | 93.8% | 0 | 0 | 492 | 0 | 3,924 | 3,924 |
| `town` (TOWN overlays) | 825,476 | 810,120 | 98.1% | 5,280 | 0 | 132 | 0 | 9,944 | 15,224 |
| `dungeon` (DUNGEON overlays) | 6,715,820 | 6,659,488 | 99.2% | 38,132 | 0 | 0 | 0 | 18,200 | 56,332 |
| `ovmovie` (OVMOVIE overlay) | 6,396 | 5,516 | 86.2% | 0 | 0 | 880 | 0 | 0 | 0 |
| **total** | 7,843,368 | 7,722,284 | 98.5% | 43,412 | 0 | 45,376 | 228 | 32,068 | 75,708 |

- **in C**: code whose C is compiled and compared byte for byte with retail.
- **byte-identical copies of C**: a span proven identical to a C function elsewhere in the images; it becomes a link-list placement of that function's source, not new C.
- **undecompiled split segments**: code the split tables carve out inside an overlay window that has no C row yet.
- **SDK library asm**: PsyQ / Sony library code kept as assembler of the retail bytes (library code, decision 55); in `slus` the PsyQ objects linked into the text, in the overlays the regions recorded as `sdk_asm` (30 whole Sony SDK objects are also listed in `ledger/sdk_objects.jsonl`).
- **other hand asm / unported**: hand-written assembler of the original program (`slus`: `main.s` and retail data blobs inside the text range) or regions recorded as deliberately unported.
- **heuristic only**: spans that look like functions (`jr ra` shape) with no row, split or proven copy; an estimate.
- **`slus`** is measured from the linked image: text range, SDK objects and hand asm by linker-script ownership, the rest is C (row sizes are stale pre-partition sizes and are not used).


## Progress by container

| container | rows | bytes | verified byte-identical | verified bytes | unverified |
|---|---:|---:|---:|---:|---:|
| slus | 884 | 473,788 | 884 | 473,788 | 0 |
| main | 469 | 66,260 | 469 | 66,260 | 0 |
| town | 5,935 | 813,136 | 5,935 | 813,136 | 0 |
| dungeon | 14,116 | 6,669,604 | 14,116 | 6,669,604 | 0 |
| ovmovie | 28 | 5,516 | 28 | 5,516 | 0 |
| ALL | 21,432 | 8,028,304 | 21,432 | 8,028,304 | 0 |

Data rows: 363 (13,132 B); stale-image residue DATA: 1 (488 B).

Placement unproven (excluded from L4 module placement): 6 rows (1,688 B): town/D_802F100C, town/D_802F1074, town/D_802F11AC, dungeon/D_808CB000, dungeon/D_80921000, dungeon/func_80921000


Baseline NOT exact: 0 rows


## Readability levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 8,028,304 | 100.0% |
| L1 | 8,028,304 | 100.0% |
| L2 | 8,028,304 | 100.0% |
| L3 | 7,275,104 | 90.6% |
| L4 | 1,011,168 | 12.6% |
| L5 | 981,836 | 12.2% |

L0 byte-exact, L1 no fidelity blockers, L2 typed field access, L3 readable body landed in `src/`, L4 zero pins and placed in a module with a shared header and current make image proof, L5 nothing left (no fidelity site, goto table, inline asm or `NON_MATCHING`). Full definitions: docs/PLAN.md.

On shared record headers (T7, `include/records/`): 4030 rows, 2,425,488 bytes (30.2%); records used: 98.

L4 residue (rows below L4, by blocker; a row can carry more than one; parked containers excluded): pins 0 rows (0 B), tail_jump 0 rows (0 B), not_in_module 19,018 rows (7,011,372 B).

## Code shape: what is left to clean in the C

Defects still present in the current tree (files = source files, bytes = image bytes of the functions in them; the last row is the positive one). The comparison with the frozen first-pass text is collapsed below.

| defect still in the clean tree | files | bytes | % of bytes |
|---|---:|---:|---:|
| goto | 140 | 366,956 | 4.6% |
| computed-goto jump table | 1 | 16 | 0.0% |
| inline asm outside macros | 6 | 7,608 | 0.1% |
| any fidelity site | 2 | 23,708 | 0.3% |
| any live audit site, unnarrowed | 1,643 | 2,611,008 | 32.5% |
| do{}while(0) scheduling barrier | 17 | 135,536 | 1.7% |
| fake dependency x=(e)+a;x-=a / arg+v-v | 1 | 408 | 0.0% |
| local address-named struct | 2,631 | 3,859,620 | 48.1% |
| clean shape | 8,160 | 7,661,348 | 95.4% |

<details><summary>pinned first-pass text vs current tree, every defect</summary>

| defect | files (pin) | bytes (pin) | % bytes | files (clean) | bytes (clean) | % bytes |
|---|---:|---:|---:|---:|---:|---:|
| m2c boilerplate block | 2331 | 510,576 | 6.4% | 0 | 0 | 0.0% |
| M2C_FIELD raw offsets | 2950 | 1,449,308 | 18.1% | 0 | 0 | 0.0% |
| m2c local names | 5181 | 2,162,116 | 26.9% | 0 | 0 | 0.0% |
| ASM_ pins | 2135 | 1,456,292 | 18.1% | 0 | 0 | 0.0% |
| goto | 1545 | 1,312,068 | 16.3% | 140 | 366,956 | 4.6% |
| computed-goto jump table | 317 | 436,504 | 5.4% | 1 | 16 | 0.0% |
| inline asm outside macros (clean: minus the composite-row carve debt, counted on its own line below) | 360 | 242,072 | 3.0% | 6 | 7,608 | 0.1% |
| fidelity blocking site, LABEL_AS_CALL/PASSTHRU_NO_ARGS (pin: baseline audit of the frozen text; clean: live, L5 predicate) | 1489 | 676,096 | 8.4% | 0 | 0 | 0.0% |
| any fidelity site (pin: any baseline audit class; clean: live L5 `fidelity_site` predicate, = levels.py) | 2654 | 1,280,740 | 16.0% | 2 | 23,708 | 0.3% |
| any live audit site, unnarrowed (clean column only; pin column repeats the row above) | 2654 | 1,280,740 | 16.0% | 1643 | 2,611,008 | 32.5% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 668 | 489,140 | 6.1% | 0 | 0 | 0.0% |
| maspsx marker pins (scaffolding) | 394 | 347,664 | 4.3% | 0 | 0 | 0.0% |
| do{}while(0) scheduling barrier (scaffolding, pure C) | 227 | 156,008 | 1.9% | 17 | 135,536 | 1.7% |
| fake dependency x=(e)+a;x-=a / arg+v-v (scaffolding, pure C) | 1 | 408 | 0.0% | 1 | 408 | 0.0% |
| local address-named struct | 633 | 346,824 | 4.3% | 2631 | 3,859,620 | 48.1% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 631 | 154,308 | 1.9% | 8160 | 7,661,348 | 95.4% |

</details>

Pin sites now: 0 in 0 rows; none left.  At the pin: 25,918; REG 12,816, KEEP 6,936, KEEP_NV 2,505, SCHED_BARRIER 1,355, TAILSLOT_PIN 506, USE 294, USE_NV 260, KEEP_DEP_NV 190.


## Image proof

`make check`: 1490/1490 images exact; 8553 overlay recipes checked. L4/L5 use current image proof and registered module shared headers. Module certificates are retired from this rule.



## Likely incorrect compiler (registered recipe vs the real build)

The game is one `2.7.2-cdk -G0 -O2` build plus a town -O1 debug family and stock Sony/devkit/minigame objects (r84_fable_build). A row is listed when its recipe differs from the one its module's pin-free rows use. Module recipe = ledger/module_recipe_census.jsonl `best_recipe`; per row see src/<container>/INDEX.md.

**Compilers are aligned: 0 rows differ from their module's recipe.** 30 rows sit at a registered recipe backed by per-row compiler evidence; 614 attributions are unconfirmed; 30 are Sony SDK library objects (not the game build); 4 rows sit at a recipe the module census cannot separate from the best one.


<details><summary>class table</summary>

| class | rows | slus / ovmovie / dungeon / town / main | pinned rows | pins |
|---|---:|---|---:|---:|
| late cell (2.8.x / egcs / 2.95.2: fitted) | 0 | 0 / 0 / 0 / 0 / 0 | 0 | 0 |
| cdk cell + crutch flags, module is plain | 0 | 0 / 0 / 0 / 0 / 0 | 0 | 0 |
| stock cell inside a cdk module | 0 | 0 / 0 / 0 / 0 / 0 | 0 | 0 |
| other mismatch with the module recipe (-G, stock flavour, -O1) | 0 | 0 / 0 / 0 / 0 / 0 | 0 | 0 |
| **total** | **0** | | **0** | **0** |

</details>

<details><summary>rows whose recipe the module census cannot separate from best_recipe (tie_with): 4</summary>

main/func_80019E34 2.7.2-G0 (best 2.7.2), main/func_8001C7F4 2.7.2 (best 2.7.2-G0), main/func_800207D4 2.7.2-G0 (best 2.6.3), main/func_80020F68 2.7.2 (best 2.6.3-G0).

</details>

<details><summary>rows at a registered recipe backed by per-row compiler evidence (ledger/recipe_evidence.jsonl): 30</summary>

ovmovie/func_800400AC 2.7.2-cdk-G0 (supported), ovmovie/func_800402D8 2.7.2-cdk-G0 (supported), ovmovie/func_8004033C 2.7.2-cdk-G0 (supported), ovmovie/func_80040360 2.7.2-cdk-G0 (supported), ovmovie/func_800403EC 2.7.2-cdk-G0 (supported), ovmovie/func_800404A8 2.7.2-cdk-G0 (supported), ovmovie/func_80040690 2.7.2-cdk-G0 (supported), ovmovie/func_8004072C 2.7.2-cdk-G0 (supported), ovmovie/func_800408BC 2.7.2-cdk-G0 (supported), ovmovie/func_80040954 2.7.2-cdk-G0 (supported), ovmovie/func_8004099C 2.7.2-cdk-G0 (supported), ovmovie/func_80040ED8 2.7.2-G0 (supported), ovmovie/func_80040F10 2.7.2-G0 (supported), ovmovie/func_80040F9C 2.7.2-G0 (supported), ovmovie/func_80041038 2.7.2-G0 (supported), ovmovie/func_80041044 2.7.2-G0 (supported), ovmovie/func_800410C0 2.7.2-G0 (supported), ovmovie/func_800410E0 2.7.2-G0 (supported), ovmovie/func_8004111C 2.7.2-G0 (supported), ovmovie/func_80041158 2.7.2-G0 (supported), ovmovie/func_8004117C 2.7.2-G0 (supported), ovmovie/func_800411A0 2.7.2-G0 (supported), ovmovie/func_8004129C 2.7.2-G0 (supported), ovmovie/func_80041330 2.7.2-G0 (supported), ovmovie/func_800413C0 2.7.2-G0 (supported), ovmovie/func_80041458 2.7.2-G0 (supported), ovmovie/func_800414F0 2.7.2-G0 (supported), ovmovie/func_80041508 2.7.2-G0 (supported), town/func_806D30B4 2.6.3-G0 (confirmed), town/func_808B2B04 2.6.3-G0 (confirmed).

</details>

<details><summary>unconfirmed compiler attributions (ledger/recipe_evidence.jsonl `to_confirm` names the measurement): 614</summary>

dungeon/func_7FFEDB5C 2.7.2-cdk-G0, dungeon/func_7FFEDB64 2.7.2-cdk-G0, dungeon/func_7FFEDB6C 2.7.2-cdk-G0, dungeon/func_7FFEDB74 2.7.2-cdk-G0, dungeon/func_7FFEDB7C 2.7.2-cdk-G0, dungeon/func_7FFEDDF0 2.7.2-cdk-G0, dungeon/func_80083D40 2.7.2-cdk-G0, dungeon/func_80085574 2.7.2-cdk-G0, dungeon/func_800BFE40 2.7.2-cdk-G0, dungeon/func_800C38D4 2.7.2-cdk-G0, dungeon/func_800C9794 2.7.2-cdk-G0, dungeon/func_800D1194 2.7.2-cdk-G0, dungeon/func_800D22A4 2.7.2-cdk-G0, dungeon/func_800D22AC 2.7.2-cdk-G0, dungeon/func_800D4F00 2.7.2-cdk-G0, dungeon/func_800D4F64 2.7.2-cdk-G0, dungeon/func_800D4FC8 2.7.2-cdk-G0, dungeon/func_800D5000 2.7.2-cdk-G0, dungeon/func_800D5038 2.7.2-cdk-G0, dungeon/func_800D5070 2.7.2-cdk-G0, dungeon/func_800D50A8 2.7.2-cdk-G0, dungeon/func_80506908 2.7.2-cdk-G0, dungeon/func_809217CC 2.7.2-cdk-G0, dungeon/func_8097DD68 2.7.2-cdk-G0, dungeon/func_80983D68 2.7.2-cdk-G0, dungeon/func_80989D68 2.7.2-cdk-G0, dungeon/func_8098FD68 2.7.2-cdk-G0, dungeon/func_80995D68 2.7.2-cdk-G0, dungeon/func_8099BD68 2.7.2-cdk-G0, dungeon/func_809A25AC 2.7.2-cdk-G0, dungeon/func_809A85AC 2.7.2-cdk-G0, dungeon/func_809AE5AC 2.7.2-cdk-G0, dungeon/func_809B45AC 2.7.2-cdk-G0, dungeon/func_809BA5AC 2.7.2-cdk-G0, dungeon/func_809C05AC 2.7.2-cdk-G0, dungeon/func_809C65AC 2.7.2-cdk-G0, dungeon/func_809D1AC0 2.7.2-cdk-G0, dungeon/func_809D7AC0 2.7.2-cdk-G0, dungeon/func_809DDAC0 2.7.2-cdk-G0, dungeon/func_809E3AC0 2.7.2-cdk-G0, dungeon/func_809E9AC0 2.7.2-cdk-G0, dungeon/func_809EFAC0 2.7.2-cdk-G0, dungeon/func_80A79E5C 2.7.2-cdk-G0, dungeon/func_80A7FE5C 2.7.2-cdk-G0, dungeon/func_80A85E5C 2.7.2-cdk-G0, dungeon/func_80A8BE5C 2.7.2-cdk-G0, dungeon/func_80A91E5C 2.7.2-cdk-G0, dungeon/func_80A97E5C 2.7.2-cdk-G0, dungeon/func_80AA3E88 2.7.2-cdk-G0, dungeon/func_80AA9E88 2.7.2-cdk-G0, dungeon/func_80AAFE88 2.7.2-cdk-G0, dungeon/func_80AB5E88 2.7.2-cdk-G0, dungeon/func_80ABBE88 2.7.2-cdk-G0, dungeon/func_80AC1E88 2.7.2-cdk-G0, dungeon/func_80AC84B4 2.7.2-cdk-G0, dungeon/func_80ACE4B4 2.7.2-cdk-G0, dungeon/func_80AD44B4 2.7.2-cdk-G0, dungeon/func_80ADA4B4 2.7.2-cdk-G0, dungeon/func_80AE04B4 2.7.2-cdk-G0, dungeon/func_80AE64B4 2.7.2-cdk-G0, dungeon/func_80AEC4B4 2.7.2-cdk-G0, dungeon/func_80AF8324 2.7.2-cdk-G0, dungeon/func_80AFE324 2.7.2-cdk-G0, dungeon/func_80B04324 2.7.2-cdk-G0, dungeon/func_80B0A324 2.7.2-cdk-G0, dungeon/func_80B10324 2.7.2-cdk-G0, dungeon/func_80B16324 2.7.2-cdk-G0, dungeon/func_80B1B804 2.7.2-cdk-G0, dungeon/func_80B21804 2.7.2-cdk-G0, dungeon/func_80B27804 2.7.2-cdk-G0, dungeon/func_80B2D804 2.7.2-cdk-G0, dungeon/func_80B33804 2.7.2-cdk-G0, dungeon/func_80B39804 2.7.2-cdk-G0, dungeon/func_80B3F804 2.7.2-cdk-G0, dungeon/func_80B998A4 2.7.2-cdk-G0, dungeon/func_80B9F8A4 2.7.2-cdk-G0, dungeon/func_80BA58A4 2.7.2-cdk-G0, dungeon/func_80BAB8A4 2.7.2-cdk-G0, dungeon/func_80BB18A4 2.7.2-cdk-G0, dungeon/func_80BB78A4 2.7.2-cdk-G0, dungeon/func_80BBD8A4 2.7.2-cdk-G0, dungeon/func_80BCA420 2.7.2-cdk-G0, dungeon/func_80BD0420 2.7.2-cdk-G0, dungeon/func_80BD6420 2.7.2-cdk-G0, dungeon/func_80BDC420 2.7.2-cdk-G0, dungeon/func_80BE2420 2.7.2-cdk-G0, dungeon/func_80BE8420 2.7.2-cdk-G0, dungeon/func_80BF34AC 2.7.2-cdk-G0, dungeon/func_80BF94AC 2.7.2-cdk-G0, dungeon/func_80BFF4AC 2.7.2-cdk-G0, dungeon/func_80C054AC 2.7.2-cdk-G0, dungeon/func_80C0B4AC 2.7.2-cdk-G0, dungeon/func_80C114AC 2.7.2-cdk-G0, dungeon/func_80C6C148 2.7.2-cdk-G0, dungeon/func_80C72148 2.7.2-cdk-G0, dungeon/func_80C78148 2.7.2-cdk-G0, dungeon/func_80C7E148 2.7.2-cdk-G0, dungeon/func_80C84148 2.7.2-cdk-G0, dungeon/func_80C8A148 2.7.2-cdk-G0, dungeon/func_80C90148 2.7.2-cdk-G0, dungeon/func_80CA1B04 2.7.2-cdk-G0, dungeon/func_80CB3B04 2.7.2-cdk-G0, dungeon/func_80CC57A0 2.7.2-cdk-G0, dungeon/func_80CCB7A0 2.7.2-cdk-G0, dungeon/func_80CD17A0 2.7.2-cdk-G0, dungeon/func_80CD77A0 2.7.2-cdk-G0, dungeon/func_80CDD7A0 2.7.2-cdk-G0, dungeon/func_80CE37A0 2.7.2-cdk-G0, dungeon/func_80CEB7B8 2.7.2-cdk-G0, dungeon/func_80CF17B8 2.7.2-cdk-G0, dungeon/func_80CF77B8 2.7.2-cdk-G0, dungeon/func_80CFD7B8 2.7.2-cdk-G0, dungeon/func_80D037B8 2.7.2-cdk-G0, dungeon/func_80D097B8 2.7.2-cdk-G0, dungeon/func_80D0F7B8 2.7.2-cdk-G0, dungeon/func_80D14664 2.7.2-cdk-G0, dungeon/func_80D1A664 2.7.2-cdk-G0, dungeon/func_80D20664 2.7.2-cdk-G0, dungeon/func_80D26664 2.7.2-cdk-G0, dungeon/func_80D2C664 2.7.2-cdk-G0, dungeon/func_80D32664 2.7.2-cdk-G0, dungeon/func_80D38664 2.7.2-cdk-G0, dungeon/func_80D3EB38 2.7.2-cdk-G0, dungeon/func_80D44B38 2.7.2-cdk-G0, dungeon/func_80D4AB38 2.7.2-cdk-G0, dungeon/func_80D50B38 2.7.2-cdk-G0, dungeon/func_80D56B38 2.7.2-cdk-G0, dungeon/func_80D5CB38 2.7.2-cdk-G0, dungeon/func_80D62B38 2.7.2-cdk-G0, dungeon/func_80D918A4 2.7.2-cdk-G0, dungeon/func_80D978A4 2.7.2-cdk-G0, dungeon/func_80D9D8A4 2.7.2-cdk-G0, dungeon/func_80DA38A4 2.7.2-cdk-G0, dungeon/func_80DA98A4 2.7.2-cdk-G0, dungeon/func_80DAF8A4 2.7.2-cdk-G0, dungeon/func_80DB58A4 2.7.2-cdk-G0, dungeon/func_80DBC940 2.7.2-cdk-G0, dungeon/func_80DC2940 2.7.2-cdk-G0, dungeon/func_80DC8940 2.7.2-cdk-G0, dungeon/func_80DCE940 2.7.2-cdk-G0, dungeon/func_80DD4940 2.7.2-cdk-G0, dungeon/func_80DDA940 2.7.2-cdk-G0, dungeon/func_80DE0940 2.7.2-cdk-G0, dungeon/func_80DEB9BC 2.7.2-cdk-G0, dungeon/func_80DF19BC 2.7.2-cdk-G0, dungeon/func_80DF79BC 2.7.2-cdk-G0, dungeon/func_80DFD9BC 2.7.2-cdk-G0, dungeon/func_80E039BC 2.7.2-cdk-G0, dungeon/func_80E099BC 2.7.2-cdk-G0, dungeon/func_80E39884 2.7.2-cdk-G0, dungeon/func_80E3F884 2.7.2-cdk-G0, dungeon/func_80E45884 2.7.2-cdk-G0, dungeon/func_80E4B884 2.7.2-cdk-G0, dungeon/func_80E51884 2.7.2-cdk-G0, dungeon/func_80E57884 2.7.2-cdk-G0, dungeon/func_80E5D884 2.7.2-cdk-G0, dungeon/func_80E643D8 2.7.2-cdk-G0, dungeon/func_80E6A3D8 2.7.2-cdk-G0, dungeon/func_80E703D8 2.7.2-cdk-G0, dungeon/func_80E763D8 2.7.2-cdk-G0, dungeon/func_80E7C3D8 2.7.2-cdk-G0, dungeon/func_80E823D8 2.7.2-cdk-G0, dungeon/func_80E883D8 2.7.2-cdk-G0, dungeon/func_80EE271C 2.7.2-cdk-G0, dungeon/func_80EE871C 2.7.2-cdk-G0, dungeon/func_80EEE71C 2.7.2-cdk-G0, dungeon/func_80EF471C 2.7.2-cdk-G0, dungeon/func_80EFA71C 2.7.2-cdk-G0, dungeon/func_80F0071C 2.7.2-cdk-G0, dungeon/func_80F0671C 2.7.2-cdk-G0, dungeon/func_80F0BAAC 2.7.2-cdk-G0, dungeon/func_80F11AAC 2.7.2-cdk-G0, dungeon/func_80F17AAC 2.7.2-cdk-G0, dungeon/func_80F1DAAC 2.7.2-cdk-G0, dungeon/func_80F23AAC 2.7.2-cdk-G0, dungeon/func_80F29AAC 2.7.2-cdk-G0, dungeon/func_80F2FAAC 2.7.2-cdk-G0, dungeon/func_80F5FA0C 2.7.2-cdk-G0, dungeon/func_80F65A0C 2.7.2-cdk-G0, dungeon/func_80F6BA0C 2.7.2-cdk-G0, dungeon/func_80F71A0C 2.7.2-cdk-G0, dungeon/func_80F77A0C 2.7.2-cdk-G0, dungeon/func_80F7DA0C 2.7.2-cdk-G0, dungeon/func_80F83A0C 2.7.2-cdk-G0, dungeon/func_80FDDB14 2.7.2-cdk-G0, dungeon/func_80FE3B14 2.7.2-cdk-G0, dungeon/func_80FE9B14 2.7.2-cdk-G0, dungeon/func_80FEFB14 2.7.2-cdk-G0, dungeon/func_80FF5B14 2.7.2-cdk-G0, dungeon/func_80FFBB14 2.7.2-cdk-G0, dungeon/func_81001B14 2.7.2-cdk-G0, dungeon/func_81007810 2.7.2-cdk-G0, dungeon/func_8100D810 2.7.2-cdk-G0, dungeon/func_81013810 2.7.2-cdk-G0, dungeon/func_81019810 2.7.2-cdk-G0, dungeon/func_8101F810 2.7.2-cdk-G0, dungeon/func_81025810 2.7.2-cdk-G0, dungeon/func_8102B810 2.7.2-cdk-G0, dungeon/func_810321F8 2.7.2-cdk-G0, dungeon/func_810381F8 2.7.2-cdk-G0, dungeon/func_8103E1F8 2.7.2-cdk-G0, dungeon/func_810441F8 2.7.2-cdk-G0, dungeon/func_8104A1F8 2.7.2-cdk-G0, dungeon/func_810501F8 2.7.2-cdk-G0, dungeon/func_810561F8 2.7.2-cdk-G0, dungeon/func_8105B990 2.7.2-cdk-G0, dungeon/func_81061990 2.7.2-cdk-G0, dungeon/func_81067990 2.7.2-cdk-G0, dungeon/func_8106D990 2.7.2-cdk-G0, dungeon/func_81073990 2.7.2-cdk-G0, dungeon/func_81079990 2.7.2-cdk-G0, dungeon/func_8107F990 2.7.2-cdk-G0, dungeon/func_81085DB4 2.7.2-cdk-G0, dungeon/func_81086878 2.7.2-cdk-G0, dungeon/func_8108BDB4 2.7.2-cdk-G0, dungeon/func_8108C878 2.7.2-cdk-G0, dungeon/func_81091DB4 2.7.2-cdk-G0, dungeon/func_81092878 2.7.2-cdk-G0, dungeon/func_81097DB4 2.7.2-cdk-G0, dungeon/func_81098878 2.7.2-cdk-G0, dungeon/func_8109DDB4 2.7.2-cdk-G0, dungeon/func_8109E878 2.7.2-cdk-G0, dungeon/func_810A3DB4 2.7.2-cdk-G0, dungeon/func_810A4878 2.7.2-cdk-G0, dungeon/func_810A9DB4 2.7.2-cdk-G0, dungeon/func_810AA878 2.7.2-cdk-G0, dungeon/func_810AF96C 2.7.2-cdk-G0, dungeon/func_810B596C 2.7.2-cdk-G0, dungeon/func_810BB96C 2.7.2-cdk-G0, dungeon/func_810C196C 2.7.2-cdk-G0, dungeon/func_810C796C 2.7.2-cdk-G0, dungeon/func_810CD96C 2.7.2-cdk-G0, dungeon/func_810D396C 2.7.2-cdk-G0, dungeon/func_81252B28 2.7.2-cdk-G0, dungeon/func_81253620 2.7.2-cdk-G0, dungeon/func_812540F0 2.7.2-cdk-G0, dungeon/func_812543E8 2.7.2-cdk-G0, dungeon/func_81258B28 2.7.2-cdk-G0, dungeon/func_81259620 2.7.2-cdk-G0, dungeon/func_8125A0F0 2.7.2-cdk-G0, dungeon/func_8125A3E8 2.7.2-cdk-G0, dungeon/func_8125EB28 2.7.2-cdk-G0, dungeon/func_8125F620 2.7.2-cdk-G0, dungeon/func_812600F0 2.7.2-cdk-G0, dungeon/func_812603E8 2.7.2-cdk-G0, dungeon/func_81264B28 2.7.2-cdk-G0, dungeon/func_81265620 2.7.2-cdk-G0, dungeon/func_812660F0 2.7.2-cdk-G0, dungeon/func_812663E8 2.7.2-cdk-G0, dungeon/func_8126AB28 2.7.2-cdk-G0, dungeon/func_8126B620 2.7.2-cdk-G0, dungeon/func_8126C0F0 2.7.2-cdk-G0, dungeon/func_8126C3E8 2.7.2-cdk-G0, dungeon/func_81270B28 2.7.2-cdk-G0, dungeon/func_81271620 2.7.2-cdk-G0, dungeon/func_812720F0 2.7.2-cdk-G0, dungeon/func_812723E8 2.7.2-cdk-G0, dungeon/func_81276B28 2.7.2-cdk-G0, dungeon/func_81277620 2.7.2-cdk-G0, dungeon/func_812780F0 2.7.2-cdk-G0, dungeon/func_812783E8 2.7.2-cdk-G0, dungeon/func_812A90B0 2.7.2-cdk-G0, dungeon/func_812AF0B0 2.7.2-cdk-G0, dungeon/func_812B50B0 2.7.2-cdk-G0, dungeon/func_812BB0B0 2.7.2-cdk-G0, dungeon/func_812C10B0 2.7.2-cdk-G0, dungeon/func_812C70B0 2.7.2-cdk-G0, dungeon/func_812CD0B0 2.7.2-cdk-G0, dungeon/func_8132629C 2.7.2-cdk-G0, dungeon/func_81326484 2.7.2-cdk-G0, dungeon/func_81326708 2.7.2-cdk-G0, dungeon/func_81328A14 2.7.2-cdk-G0, dungeon/func_81328A1C 2.7.2-cdk-G0, dungeon/func_81329544 2.7.2-cdk-G0, dungeon/func_81329928 2.7.2-cdk-G0, dungeon/func_81337BA8 2.7.2-cdk-G0, dungeon/func_81337E44 2.7.2-cdk-G0, dungeon/func_813383A8 2.7.2-cdk-G0, dungeon/func_813383C4 2.7.2-cdk-G0, dungeon/func_813383E8 2.7.2-cdk-G0, dungeon/func_81338408 2.7.2-cdk-G0, dungeon/func_81810530 2.7.2-cdk-G0, dungeon/func_8181053C 2.7.2-cdk-G0, dungeon/func_81811CCC 2.7.2-cdk-G0, dungeon/func_81935128 2.7.2-cdk-G0, dungeon/func_81947288 2.7.2-cdk-G0, dungeon/func_8199AF84 2.7.2-cdk-G0, dungeon/func_8199B124 2.7.2-cdk-G0, main/func_80012358 2.7.2-cdk-G0, main/func_80019E34 2.7.2-G0, main/func_8001C7F4 2.7.2, main/func_8001E3A0 2.6.3-G0, main/func_8001E4E8 2.6.3-G0, main/func_800207D4 2.7.2-G0, main/func_80020F68 2.7.2, main/func_800213A0 2.6.3-G0, main/func_800213FC 2.6.3-G0, main/func_800214DC 2.6.3-G0, main/func_8002155C 2.6.3-G0, main/func_8002159C 2.6.3-G0, main/func_800215DC 2.6.3-G0, main/func_8002161C 2.6.3-G0, main/func_80021684 2.6.3-G0, main/func_800216DC 2.6.3-G0, main/func_80021730 2.6.3-G0, main/func_80021768 2.6.3-G0, slus/code 2.7.2-cdk, town/func_800B29F8 2.7.2-cdk-G0, town/func_800B6108 2.7.2-cdk-G0, town/func_800B6D50 2.7.2-cdk-G0, town/func_800B7738 2.7.2-cdk-G0, town/func_802EE53C 2.6.3-G0, town/func_802EE624 2.6.3-G0, town/func_802EE6CC 2.6.3-G0, town/func_802EE6F4 2.6.3-G0, town/func_802EE7A8 2.6.3-G0, town/func_802EE7B0 2.6.3-G0, town/func_802F1394 2.6.3-G0, town/func_80333574 2.7.2-cdk-G0, town/func_803335A0 2.7.2-cdk-G0, town/func_8046A9C8 2.7.2-cdk-G0, town/func_8046AB24 2.7.2-cdk-G0, town/func_8046AC54 2.7.2-cdk-G0, town/func_804804E4 2.7.2-cdk-G0, town/func_80480530 2.7.2-cdk-G0, town/func_80481244 2.7.2-cdk-G0, town/func_8048189C 2.7.2-cdk-G0, town/func_80481D68 2.7.2-cdk-G0, town/func_8048225C 2.7.2-cdk-G0, town/func_804822EC 2.7.2-cdk-G0, town/func_804B7930 2.7.2-cdk-G0, town/func_804B7950 2.7.2-cdk-G0, town/func_804B7970 2.7.2-cdk-G0, town/func_804B7990 2.7.2-cdk-G0, town/func_804B79B0 2.7.2-cdk-G0, town/func_804B79D0 2.7.2-cdk-G0, town/func_804B7A28 2.7.2-cdk-G0, town/func_804B7A48 2.7.2-cdk-G0, town/func_804B7A68 2.7.2-cdk-G0, town/func_804B9500 2.7.2-cdk-G0, town/func_804B99CC 2.7.2-cdk-G0, town/func_804B9EC0 2.7.2-cdk-G0, town/func_804B9F50 2.7.2-cdk-G0, town/func_804D0FA8 2.7.2-cdk-G0, town/func_804D1474 2.7.2-cdk-G0, town/func_804D1968 2.7.2-cdk-G0, town/func_804D19F8 2.7.2-cdk-G0, town/func_804D887C 2.7.2-cdk-G0, town/func_804D8D48 2.7.2-cdk-G0, town/func_804D923C 2.7.2-cdk-G0, town/func_804D92CC 2.7.2-cdk-G0, town/func_804F08A0 2.7.2-cdk-G0, town/func_804F0D6C 2.7.2-cdk-G0, town/func_804F1260 2.7.2-cdk-G0, town/func_804F12F0 2.7.2-cdk-G0, town/func_80500784 2.7.2-cdk-G0, town/func_80500C50 2.7.2-cdk-G0, town/func_80501144 2.7.2-cdk-G0, town/func_805011D4 2.7.2-cdk-G0, town/func_8050E168 2.7.2-cdk-G0, town/func_8050E82C 2.7.2-cdk-G0, town/func_8050ECF8 2.7.2-cdk-G0, town/func_8050F1EC 2.7.2-cdk-G0, town/func_8050F27C 2.7.2-cdk-G0, town/func_805204E4 2.7.2-cdk-G0, town/func_805209B0 2.7.2-cdk-G0, town/func_80520EA4 2.7.2-cdk-G0, town/func_80520F34 2.7.2-cdk-G0, town/func_805501CC 2.7.2-cdk-G0, town/func_80550698 2.7.2-cdk-G0, town/func_80550B8C 2.7.2-cdk-G0, town/func_80550C1C 2.7.2-cdk-G0, town/func_80559718 2.7.2-cdk-G0, town/func_80559BE4 2.7.2-cdk-G0, town/func_8055A0D8 2.7.2-cdk-G0, town/func_8055A168 2.7.2-cdk-G0, town/func_80579168 2.7.2-cdk-G0, town/func_805797CC 2.7.2-cdk-G0, town/func_80579C98 2.7.2-cdk-G0, town/func_8057A18C 2.7.2-cdk-G0, town/func_8057A21C 2.7.2-cdk-G0, town/func_8059E130 2.7.2-cdk-G0, town/func_8059E188 2.7.2-cdk-G0, town/func_8059E4A0 2.7.2-cdk-G0, town/func_8059E6D0 2.7.2-cdk-G0, town/func_8059E808 2.7.2-cdk-G0, town/func_8059F450 2.7.2-cdk-G0, town/func_8059FB98 2.7.2-cdk-G0, town/func_805A0064 2.7.2-cdk-G0, town/func_805A0558 2.7.2-cdk-G0, town/func_805A05E8 2.7.2-cdk-G0, town/func_805D210C 2.7.2-cdk-G0, town/func_805D211C 2.7.2-cdk-G0, town/func_805D212C 2.7.2-cdk-G0, town/func_805D2174 2.7.2-cdk-G0, town/func_805D2194 2.7.2-cdk-G0, town/func_805D2200 2.7.2-cdk-G0, town/func_805D2228 2.7.2-cdk-G0, town/func_805D2E0C 2.7.2-cdk-G0, town/func_805D2E2C 2.7.2-cdk-G0, town/func_805D4468 2.7.2-cdk-G0, town/func_805D4934 2.7.2-cdk-G0, town/func_805D4E28 2.7.2-cdk-G0, town/func_805D4EB8 2.7.2-cdk-G0, town/func_806011DC 2.7.2-cdk-G0, town/func_80601310 2.7.2-cdk-G0, town/func_80601338 2.7.2-cdk-G0, town/func_80601B6C 2.7.2-cdk-G0, town/func_806022B4 2.7.2-cdk-G0, town/func_80602780 2.7.2-cdk-G0, town/func_80602C74 2.7.2-cdk-G0, town/func_80602D04 2.7.2-cdk-G0, town/func_806156E0 2.7.2-cdk-G0, town/func_80615708 2.7.2-cdk-G0, town/func_80615F3C 2.7.2-cdk-G0, town/func_80616684 2.7.2-cdk-G0, town/func_80616B50 2.7.2-cdk-G0, town/func_80617044 2.7.2-cdk-G0, town/func_806170D4 2.7.2-cdk-G0, town/func_80632100 2.7.2-cdk-G0, town/func_806321D0 2.7.2-cdk-G0, town/func_80632230 2.7.2-cdk-G0, town/func_80632258 2.7.2-cdk-G0, town/func_8063288C 2.7.2-cdk-G0, town/func_80632D58 2.7.2-cdk-G0, town/func_8063324C 2.7.2-cdk-G0, town/func_806332DC 2.7.2-cdk-G0, town/func_8064711C 2.7.2-cdk-G0, town/func_80647190 2.7.2-cdk-G0, town/func_806471E8 2.7.2-cdk-G0, town/func_80647920 2.7.2-cdk-G0, town/func_80647DEC 2.7.2-cdk-G0, town/func_806482E0 2.7.2-cdk-G0, town/func_80648370 2.7.2-cdk-G0, town/func_8065BF68 2.7.2-cdk-G0, town/func_8065BF88 2.7.2-cdk-G0, town/func_8065BFA8 2.7.2-cdk-G0, town/func_8065BFF4 2.7.2-cdk-G0, town/func_8067F74C 2.7.2-cdk-G0, town/func_80680170 2.7.2-cdk-G0, town/func_806807C8 2.7.2-cdk-G0, town/func_80680C94 2.7.2-cdk-G0, town/func_80681188 2.7.2-cdk-G0, town/func_80681218 2.7.2-cdk-G0, town/func_80698240 2.7.2-cdk-G0, town/func_80698898 2.7.2-cdk-G0, town/func_80698D64 2.7.2-cdk-G0, town/func_80699258 2.7.2-cdk-G0, town/func_806992E8 2.7.2-cdk-G0, town/func_806A973C 2.7.2-cdk-G0, town/func_806A9C08 2.7.2-cdk-G0, town/func_806AA0FC 2.7.2-cdk-G0, town/func_806AA18C 2.7.2-cdk-G0, town/func_806C5EDC 2.7.2-cdk-G0, town/func_806C6858 2.7.2-cdk-G0, town/func_806C6FA0 2.7.2-cdk-G0, town/func_806C746C 2.7.2-cdk-G0, town/func_806C7960 2.7.2-cdk-G0, town/func_806C79F0 2.7.2-cdk-G0, town/func_806C9180 2.7.2-cdk-G0, town/func_806C937C 2.7.2-cdk-G0, town/func_806C9388 2.7.2-cdk-G0, town/func_806C9970 2.7.2-cdk-G0, town/func_806C9E3C 2.7.2-cdk-G0, town/func_806CA330 2.7.2-cdk-G0, town/func_806CA3C0 2.7.2-cdk-G0, town/func_806CB180 2.7.2-cdk-G0, town/func_806CB384 2.7.2-cdk-G0, town/func_806CB96C 2.7.2-cdk-G0, town/func_806CBE38 2.7.2-cdk-G0, town/func_806CC32C 2.7.2-cdk-G0, town/func_806CC3BC 2.7.2-cdk-G0, town/func_806CD32C 2.7.2-cdk-G0, town/func_806CD914 2.7.2-cdk-G0, town/func_806CDDE0 2.7.2-cdk-G0, town/func_806CE2D4 2.7.2-cdk-G0, town/func_806CE364 2.7.2-cdk-G0, town/func_806CF0F8 2.7.2-cdk-G0, town/func_806CF190 2.7.2-cdk-G0, town/func_806CF778 2.7.2-cdk-G0, town/func_806CFC44 2.7.2-cdk-G0, town/func_806D0138 2.7.2-cdk-G0, town/func_806D01C8 2.7.2-cdk-G0, town/func_806D1100 2.7.2-cdk-G0, town/func_806D16E8 2.7.2-cdk-G0, town/func_806D1BB4 2.7.2-cdk-G0, town/func_806D20A8 2.7.2-cdk-G0, town/func_806D2138 2.7.2-cdk-G0, town/func_806D561C 2.7.2-cdk-G0, town/func_806D5AE8 2.7.2-cdk-G0, town/func_806D5FDC 2.7.2-cdk-G0, town/func_806D606C 2.7.2-cdk-G0, town/func_806D8580 2.7.2-cdk-G0, town/func_806D8FC8 2.7.2-cdk-G0, town/func_806D9494 2.7.2-cdk-G0, town/func_806D9988 2.7.2-cdk-G0, town/func_806D9A18 2.7.2-cdk-G0, town/func_806DB100 2.7.2-cdk-G0, town/func_806DB114 2.7.2-cdk-G0, town/func_806DB790 2.7.2-cdk-G0, town/func_806DBC5C 2.7.2-cdk-G0, town/func_806DC150 2.7.2-cdk-G0, town/func_806DC1E0 2.7.2-cdk-G0, town/func_806F21C4 2.7.2-cdk-G0, town/func_806F2690 2.7.2-cdk-G0, town/func_806F2B84 2.7.2-cdk-G0, town/func_806F2C14 2.7.2-cdk-G0, town/func_8070E9D4 2.7.2-cdk-G0, town/func_8070E9F4 2.7.2-cdk-G0, town/func_8070F6BC 2.7.2-cdk-G0, town/func_8070F6D0 2.7.2-cdk-G0, town/func_8070F6E4 2.7.2-cdk-G0, town/func_8070F6F8 2.7.2-cdk-G0, town/func_8070F708 2.7.2-cdk-G0, town/func_8070F718 2.7.2-cdk-G0, town/func_8070F740 2.7.2-cdk-G0, town/func_8070F768 2.7.2-cdk-G0, town/func_8070F790 2.7.2-cdk-G0, town/func_8070F854 2.7.2-cdk-G0, town/func_8070F874 2.7.2-cdk-G0, town/func_8070F894 2.7.2-cdk-G0, town/func_8070F8EC 2.7.2-cdk-G0, town/func_8070F90C 2.7.2-cdk-G0, town/func_80710138 2.7.2-cdk-G0, town/func_80710880 2.7.2-cdk-G0, town/func_80710D4C 2.7.2-cdk-G0, town/func_80711240 2.7.2-cdk-G0, town/func_807112D0 2.7.2-cdk-G0, town/func_8072A288 2.7.2-cdk-G0, town/func_8072A2A8 2.7.2-cdk-G0, town/func_8072A308 2.7.2-cdk-G0, town/func_8072AB30 2.7.2-cdk-G0, town/func_8072AFFC 2.7.2-cdk-G0, town/func_8072B4F0 2.7.2-cdk-G0, town/func_8072B580 2.7.2-cdk-G0, town/func_8074C98C 2.7.2-cdk-G0, town/func_8074CF74 2.7.2-cdk-G0, town/func_8074D440 2.7.2-cdk-G0, town/func_8074D934 2.7.2-cdk-G0, town/func_8074D9C4 2.7.2-cdk-G0, town/func_80761AF8 2.7.2-cdk-G0, town/func_80761B50 2.7.2-cdk-G0, town/func_80761C08 2.7.2-cdk-G0, town/func_80761D30 2.7.2-cdk-G0, town/func_807623D0 2.7.2-cdk-G0, town/func_8076289C 2.7.2-cdk-G0, town/func_80762D90 2.7.2-cdk-G0, town/func_80762E20 2.7.2-cdk-G0, town/func_807707C0 2.7.2-cdk-G0, town/func_80770C8C 2.7.2-cdk-G0, town/func_80771180 2.7.2-cdk-G0, town/func_80771210 2.7.2-cdk-G0, town/func_80774928 2.7.2-cdk-G0, town/func_80774F28 2.7.2-cdk-G0, town/func_807753F4 2.7.2-cdk-G0, town/func_807758E8 2.7.2-cdk-G0, town/func_80775978 2.7.2-cdk-G0, town/func_80777128 2.7.2-cdk-G0, town/func_80777728 2.7.2-cdk-G0, town/func_80777BF4 2.7.2-cdk-G0, town/func_807780E8 2.7.2-cdk-G0, town/func_80778178 2.7.2-cdk-G0, town/func_8077E2A4 2.7.2-cdk-G0, town/func_8077E770 2.7.2-cdk-G0, town/func_8077EC64 2.7.2-cdk-G0, town/func_8077ECF4 2.7.2-cdk-G0, town/func_807851EC 2.7.2-cdk-G0, town/func_80785824 2.7.2-cdk-G0, town/func_80785CF0 2.7.2-cdk-G0, town/func_807861E4 2.7.2-cdk-G0, town/func_80786274 2.7.2-cdk-G0, town/func_8079A84C 2.7.2-cdk-G0, town/func_8079AD18 2.7.2-cdk-G0, town/func_8079B20C 2.7.2-cdk-G0, town/func_8079B29C 2.7.2-cdk-G0, town/func_8081AAC0 2.7.2-cdk-G0, town/func_8081AB04 2.7.2-cdk-G0, town/func_808753FC 2.6.3-G0, town/func_80875684 2.6.3-G0, town/func_80875808 2.6.3-G0, town/func_80875858 2.6.3-G0, town/func_808758AC 2.6.3-G0, town/func_8087590C 2.6.3-G0, town/func_80878110 2.6.3-G0, town/func_8087FFD0 2.6.3-G0, town/func_8087FFF0 2.6.3-G0, town/func_80880010 2.6.3-G0, town/func_80880030 2.6.3-G0, town/func_80880050 2.6.3-G0, town/func_80880070 2.6.3-G0, town/func_80880274 2.6.3-G0, town/func_80883524 2.6.3-G0, town/func_808B3104 2.6.3-G0, town/func_808B3374 2.6.3-G0, town/func_808B95EC 2.6.3-G0, town/func_808B960C 2.6.3-G0, town/func_808B962C 2.6.3-G0, town/func_808B964C 2.6.3-G0, town/func_808B966C 2.6.3-G0, town/func_808B968C 2.6.3-G0, town/func_808B98AC 2.6.3-G0, town/func_8094DB74 2.7.2-G0, town/func_8094EB74 2.7.2-G0, town/func_8094FB70 2.7.2-G0, town/func_80950B70 2.7.2-G0, town/func_80951B70 2.7.2-G0, town/func_8095212C 2.7.2-G0, town/func_80952C34 2.7.2-G0, town/func_80956FA8 2.7.2-cdk-G0, town/func_8096AC8C 2.7.2-cdk-G0, town/func_8096AD44 2.7.2-cdk-G0, town/func_8096DB00 2.7.2-cdk-G0, town/func_8096DFCC 2.7.2-cdk-G0, town/func_8096DFEC 2.7.2-cdk-G0.

</details>

<details><summary>Sony SDK library objects (ledger/sdk_objects.jsonl, whole-object byte match): 30</summary>

main/func_80021644, main/func_80021654, main/func_80021664, main/func_80021674, main/func_800216BC, main/func_800216CC, main/func_80021798, main/func_800217A8, main/func_800217B8, main/func_800217C8, main/func_800218A0, main/func_80021958, main/func_800219C4, main/psyq_A78_2716BC, main/psyq_A80_2716CC, main/psyq_A92_271644, main/psyq_A93_271654, main/psyq_C171_271664, main/psyq_C172_271674, ovmovie/func_80041638, ovmovie/func_8004166C, town/func_802F1644, town/func_802F1654, town/func_802F1664, town/func_802F1674, town/func_802F16BC, town/func_802F16CC, town/psyq_A74_271798, town/psyq_A75_2717A8, town/psyq_A76_2717B8.

</details>


## Tracked spellings and trades

Choices the tree keeps on purpose and tracks; none is an assembler pin. The compact table and the full descriptions are collapsed.


<details><summary>Tracked spellings and trades: 12 kinds (none is an assembler pin)</summary>

| kind | count | where recorded |
|---|---|---|
| oddities (zero-byte fences retail needs) | 0 | `ledger/oddities.jsonl` |
| one-trip barrier rows | 2 | `ledger/onetrip_barrier_rows.jsonl` |
| load-bearing one-trip rows | 85 | `ledger/onetrip_loadbearing.jsonl` |
| carve debt: composite rows | 0 statements in 0 rows | `tools/pin_census.py composite_asm_spans` |
| hidden scaffolding (not pins) | 8 sites (6 symbol aliases) | `pin_census.hidden_asm` |
| per-row optimization flags | 2,016 rows with one, 0 with two or more | `ledger/rows.jsonl` |
| site-for-pin trades | 27 | `ledger/recipe_trades.jsonl` |
| dead-initializer trades | 24 | `ledger/recipe_trades.jsonl` |
| union trades (tracked, plausibility unproven) | 41 open of 52 sites | `ledger/union_trades.jsonl` |
| dead-branch trades (decision 45) | 4 rows | `ledger/recipe_trades.jsonl` |
| dead-arm trades (decision 46) | 1 rows | `ledger/recipe_trades.jsonl` |
| void callees (tier A in-tree / tier B explicit) | 30 + 1 symbols; 11 rows rest on tier B | `config/void_callees.txt` |

</details>

<details><summary>full descriptions</summary>

Tracked, not pins (owner 2026-10-06): oddities 0 (ledger/oddities.jsonl - zero-byte fences retail needs, curiosities, not removal targets: -); one-trip barrier rows 2 (ledger/onetrip_barrier_rows.jsonl); load-bearing one-trip rows 85 (ledger/onetrip_loadbearing.jsonl, statement-macro bodies, not counted in the do{}while(0) row above).
Carve debt - composite rows (r95 decisions item 8 kept the spelling for bytes; r99: it is an artifact of one-row-per-function carving, owned by module placement): the `asm("func_X")` data prefix (another function's jump table / overlay data that retail places before this row's code) and its `.globl/.type/.size func_X` stamp (`pin_census.composite_asm_spans`), 0 statements in 0 rows - counted here, not in the inline-asm row above; still L5 `inline_asm` residue in levels.py until the module TU owns the data.
Hidden scaffolding, not in the pin count (`pin_census.hidden_asm`): raw asm statements 0, calls of local asm wrappers 0, hand-written asm in function bodies 0 (C that is missing); symbol aliases 6 (a second typed name for one symbol: a missing type); file-scope asm directives 2; file-scope global register variables 0 (`register T g asm("$R")`).

Per-row optimization flags (weak evidence about the real build; each switch is undone from the `t30_cellpins` journal's `cell_from`): 2,016 rows carry one flag, 0 carry two or more.

Site-for-pin trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"site_for_pin","id":row,"site":"LABEL_AS_CALL|ITC|PASSTHRU","pin":macro,"residue_without_pin":str,"at":iso,"note":str}` -- one pin, or two when one is not enough (owner ruling 2026-09-22 afternoon, "accept 2 pins") -- charter rule 3, "a pin moved elsewhere is not a removal"; the trade is tracked, and L4 is where pins stop counting toward removal regardless): 27.

Dead-initializer trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"dead_init","id":row,"site":pins,"init":decl,"lane":lane,"at":iso,"note":str}` -- a never-read `= 0` at a declaration makes the variable multi-set; ordinary C by the owner ruling 2026-09-23, tracked as a spelling trade, informational, the pin count is unchanged; appended by tools/apply_candidates.py at landing): 24.

Union trades (`ledger/union_trades.jsonl`, owner 2026-10-13: kept as nicer-than-a-pin but TRACKED - their plausibility as original 1997 code is unproven; census work/native_lane/_r118/union_census): zero-init one-member idiom (accepted trade): 30 sites in 6 rows (6 rows still carry a union; most: func_8180B064 16, func_80098378 9, func_808119EC 2, func_809A38E4 1); host-merge levers (int/pointer share one union variable; owner ruling pending): 11 sites in 10 rows (7 rows still carry a union; most: func_81983138 2, func_800C7F80 1, func_80EF3FB0 1, func_80EF9FB0 1). Resolved by re-spells (original-C shapes, byte-exact): 11 of 52 recorded sites. Refused union levers (float launders, dead-value keepers) are recorded in the hard basket.

Dead-branch trades (decision 45, owner 2026-10-13; `ledger/recipe_trades.jsonl` kind dead_branch - a one-arm `if (value) { local = 0; }` over a retail-evidenced value whose arm sets a never-read local, reconstructing a set-but-unused leftover that jump2 deletes while delete_computation keeps the load): 4 rows (func_800A3D40, func_80B467DC, func_8105A724, func_81339F68).

Dead-arm trades (decision 46, owner 2026-10-13; `ledger/recipe_trades.jsonl` kind dead_arm - a never-taken arm over a never-reassigned local that combine folds after flow counted it, so sched/global/reload still see it and jump2 deletes it; the arm body is a RECONSTRUCTION, only its shape is byte-evidenced): 1 rows (func_80DE48EC).

Void callees (`config/void_callees.txt`, tiers read from its section-header comments -- no per-line marker exists): tier A 30, tier B 1 symbols (matches `census.declared_void_callees()`). Rows whose PASSTHRU_NO_ARGS exemption rests on a tier-B symbol alone (blocked again if tier B were dropped, tier-A/in-tree exemptions do not cover them): 11 rows, 11,864 B.


</details>


<details><summary>Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)</summary>

| container | assert file:line / expression | developer identifiers | randomizer map (code) | randomizer map (data tables) | resident pointer tables | script function names | prior notes | applied names | any (rows / bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| slus | 0 | 0 | 1 | 0 | 72 | 7 | 408 | 14 | 479 / 328,024 |
| main | 18 | 5 | 1 | 0 | 0 | 0 | 0 | 0 | 19 / 6,420 |
| town | 26 | 8 | 1 | 1 | 0 | 114 | 0 | 0 | 142 / 19,536 |
| dungeon | 0 | 0 | 24 | 21 | 0 | 0 | 0 | 0 | 44 / 35,592 |

</details>

Every lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.

## How a match is proven

Landing proof: `make check` compares all generated images with the disc, including the SLUS EXE and extra recipe layouts. Native TUs use the canonical genuine ASPSX comparison when the SDK is present. L4/L5 also require the independent source-quality predicates.


<details><summary>How rows are verified</summary>

No container is parked (ovmovie unparked by the owner 2026-10-14). Ordinary SLUS rows use pinned-TU object verification; grouped module candidates use the full SLUS image gate, including sibling functions and owned data. Historical raw baselines stay per row. Overlay rows use retail-slice comparison through the per-row scorer, with complete make image proof as the landing check. Non-stock rows (bridge cells, per-row assembler dials, platform asm) would be excluded; there are 0 at the pin.

Current landing proof: `make -j8 && make check`; extra layouts cover recipes outside load images.


</details>

**Read next.** [README](README.md) (project overview) - [docs/README.md](docs/README.md) (documentation index) - [docs/PLAN.md](docs/PLAN.md) (levels L0-L5) - [docs/FIDELITY.md](docs/FIDELITY.md) (what scaffolding means) - [docs/SLUS_MODULES.md](docs/SLUS_MODULES.md) (executable modules) - [CONTRIBUTING.md](CONTRIBUTING.md).


