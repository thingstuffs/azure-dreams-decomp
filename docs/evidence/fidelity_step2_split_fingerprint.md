# Toolchain fidelity step 2: split-address fingerprint census over retail words (2026-09-24)

Measurement only (brief `work/fidelity/STEP2_BRIEF.md`; plan `docs/TOOLCHAIN_FIDELITY_PLAN.md` step 2). Nothing under
`src/`, `include/`, `ledger/`, `config/`, recipes, `tools/maspsx` or `tools/build` was touched; no gates, landings,
sweeps or git. Tool `tools/fidelity/split_fingerprint.py` (test `tools/tests/test_split_fingerprint.py`, 19 cases);
per-row data `work/fidelity/split_fingerprint.jsonl` (6,767 rows); step-4 list `work/fidelity/step4_candidates.tsv`;
page-constant rows `work/fidelity/page_pin_fingerprint.tsv`; per-module evidence `work/fidelity/module_fingerprint.jsonl`.

## Headline

- **The sceptic's slus calibration reproduces exactly**: 185/317 pin-free `2.7.2-cdk`, 66/107 pin-free `2.8.1`,
  6/364 pin-free `2.7.2`, 36/42 pinned cdk (his detector ported verbatim as `--mode reloc`; pin status unchanged
  since his run).
- **Every container shows the same split, and it is sharp.** Over rows that address RAM at all (a HIGH/LO pair of any
  form): pin-free rows at splitting cells show the fingerprint in **3,342 / 4,114 (81%)**; pin-free rows at
  non-splitting cells (2.6.3, 2.7.2, cdk `-mmips-as`, 2.8.x `-mno-split-addresses`) in **14 / 317 (4.4%)**, and all 14
  either carry scaffolding in the current text (6) or have no source-level cause and await step 1's maspsx-pass attribution (8; below). Pinned rows at non-splitting cells:
  **56 / 102 (55%)** - the pins imitate a splitting compiler.
- **Module census agrees**: of 365 modules with a census `best_recipe`, 345 agree with the fingerprint, 19 have too
  little pin-free addressing to say, 0 splitting-recipe modules contradict it, and the 1 contradiction is `dungeon/ovl_10a30bc.c` (census `2.7.2`, its one
  addressing row `func_810830BC` is registered `2.8.1-G0` and splits). Apart from that one-row module, no module whose
  census recipe is 2.6.3/2.7.2 has a pin-free fingerprint row.
- **Step-4 candidates: 70 rows** registered at a non-splitting cell whose retail shows a strict fingerprint
  (56 pinned / 323 pins, of which 122 page-constant pin sites; 53 at 2.7.2, 16 at 2.6.3, 1 cdk `-mmips-as`), plus 2
  weak-only rows. **48 of the 70 sit in a module whose census recipe already splits** (all of dungeon/town/main
  except 5 dungeon rows without a census module) - for those, clause 4b's "toward the module census recipe" and "toward
  the retail-proven recipe" coincide. The other 22 (17 slus, 5 dungeon) have no module census.
- Page-constant pin class (`page_pin_rows.txt`, 150 rows / 332 sites): 146 show the fingerprint (strict), 2 weak-only,
  2 none. At non-splitting cells: 46 strict + 2 weak of 48 rows (124 sites) - the sceptic's "~50 rows / ~125 sites"
  confirmed by retail bytes.

## Method

### Material
- **Overlay rows** (dungeon, town, main, ovmovie; 5,883): the scorer's retail slice,
  `build_ovl/work/s3_splat/extract/<BIN>[foff : foff+size]` (`DUNGEON_DUNGEON.BIN`, `TOWN_TOWN.BIN`,
  `MAIN_MAIN.BIN`, `OVMOVIE.BIN`; checked against the sceptic's `func_80AEF73C` split pair). The 23 `main` rows gated
  by `main_7fdd.overlay.yaml` name `work/roundtrip/extract/MAIN/MAIN.BIN`; in the view root that file is the same
  inode as `MAIN_MAIN.BIN` (`cmp` identical).
- **slus rows** (884 TUs, 1,099 functions): the global functions each TU defines (`T` symbols of
  `build_slus/build/src/<tu>.o`), address/size from the linked `build_slus/build/slus_006.14.elf`, words from
  `baserom/slus_006.14` (the ELF's `._800` section is byte-identical to the baserom from 0x800; the build's `.ok`
  stamp is current). The row table's `defs` field lists REFERENCED functions too, so it cannot be used for this.
- **The sceptic's cache** (`ledger/cache/slus_dis/*.txt`, objdump `-d -r` of each pinned TU object, 884 files; his
  "556" is not a row count that reproduces - the scan covers all 884) is used for the calibration and as relocation
  ground truth: 1,091 of 1,099 functions align with retail under a relocation mask (8 do not: the cached raw object
  differs from the linked build - a stale cache; e.g. `w_80043674` has two nops before a `mult` that the cached object
  lacks; those 8 are scanned from retail but carry no ground truth).
- Pins: `tools/pin_census.sites_of(current_text(row))` (src/). Page-constant pin rows: the sceptic's
  `page_pin_rows.txt`. Modules: `ledger/modules.jsonl` -> `ledger/module_recipe_census.jsonl` (dungeon/town/main only;
  **slus has no module census**). Two text columns per row: `page_lit` (literal `0x8XXX0000` in the C, comments
  stripped) and `asm_hi` (an `asm` statement containing `lui`/`%hi`).

### Which cells split
`grep split_addresses toolchain/gcc-src/*/config/mips/mips.c`: 0 in 2.6.3 and 2.7.2; 5 in 2.8.0, 2.8.1, 2.91.66,
2.95.2 (`mips_split_addresses = 1` under `TARGET_GAS && TARGET_SPLIT_ADDRESSES && optimize && !flag_pic`);
`2.7.2-cdk` is the Cygnus 2.7.2 with the same path under `-mgas`. Probe (compiled here, `-O2 -G0`, the tree's
compilers): `extern int sym[]; return sym[2];` is `lw $2,sym+8` (macro) at 2.6.3/2.7.2 and
`lui $2,%hi(sym+8) # high / lw $2,%lo(sym+8)($2)` at cdk and 2.8.1; `sym2 = sym2 + v` shares one HIGH between the
load and the store at cdk/2.8.1; `return sym;` at cdk/2.8.1 puts the `addiu %lo` in the `j $31` delay slot.
**Integer constant addresses are macros at every cell**: `*(int*)0x80083498` is `lw $2,-2146945896` (and the store
`sw $4,-2146945896`, an `$at` macro) at 2.6.3, 2.7.2, cdk and 2.8.1; an address VALUE `(int*)0x80083498` is
`li/ori` (`lui/ori`) everywhere. So no split shape can come from an integer constant through cc1 + an assembler at
any cell - it takes a constant hidden from cse (an `ASM_KEEP`/`ASM_REG` pin, or a local assigned a page the way the
pinned texts do), inline asm, or a maspsx pass. Splitting = cell in {2.7.2-cdk, 2.8.0, 2.8.1, 2.91.66, 2.95.2} and
neither `-mmips-as` nor `-mno-split-addresses` in the flags.

### The detector (raw retail words; `scan()` in the tool)
For every `lui rX,P` (rX != $0) the walker follows rX forward on the fall-through path - through delay slots, into
the target of an unconditional in-function `b`/`j`, stopping after `jr`, dropping caller-saved carriers after a
call's slot, at most 48 steps; a `lui` in a delay slot is followed on the branch-taken path first (reorg fills slots
from the target), then the fall-through - and records every LO user: `addiu rY,rC,lo`, a load or a store with base
rC (rC = rX or a register derived from it by `addu`, the indexed form). Target = `(P<<16) + sext(lo)`.

Classes that are NOT the fingerprint:

| class | shape | why excluded |
|---|---|---|
| `macro_la` | `lui rX ; addiu rX,rX,lo`, adjacent, only user | ASPSX `la` expansion (and the adjacent cdk pair, byte-identical) |
| `macro_load` | `lui rX ; l* rX,lo(rX)`, adjacent, only user | ASPSX load macro (uses the destination as temporary) |
| `macro_idx` | `lui rX ; addu rX,rX,rI ; l* rX,lo(rX)` | indexed load macro |
| `at_macro` | `lui $at` + access through `$at` | store / indexed macro; also every integer constant address store |
| `int_ori` | any `ori` user | integer constant (`large_int` split is `ior`, never `plus`) |
| `page_only` | no LO user on the walked path | a round integer used as a value, or a HIGH whose LO lies off the path |
| `nonram` | a target outside 0x80000000-0x801FFFFF | scratchpad/IO/other integers |
| `page_shared` | one HIGH whose LO targets straddle a known symbol start | a page base shared by several symbols: the page-constant shape, not a single-symbol HIGH/LO_SUM (symbol starts: SLUS ELF symbols; overlays: `D_XXXXXXXX` names in the container's src plus resident SLUS data) |

Fingerprint kinds (strict unless noted; a HIGH can carry several):

| kind | shape | why a macro/integer cannot make it |
|---|---|---|
| `high_in_slot` | the `lui` sits in a branch/jump delay slot | a 2-word macro never fits a slot (ASPSX's own diagnostic); cc1 at 2.6.3/2.7.2 never puts `la` in a slot |
| `interleaved` | an unrelated instruction between the `lui` and its first LO user | macros are atomic; genuine ASPSX never splits `la` (sceptic's probes) |
| `lo_other_reg` | `addiu rY,rX,lo`, rY != rX | `la rY` expands into rY only |
| `load_other_reg` | `l* rY,lo(rX)`, rY != rX | the load macro's temporary is its destination |
| `store_high_base` | a store through a non-`$at` HIGH | the store macro always uses `$at` |
| `shared_high` | one `lui` feeds >= 2 LO users | a macro re-materialises per access |
| `slot_lo` (weak) | the only insn between them is a branch/jump whose slot holds the LO | natural at cdk (`lui ; j $31 ; addiu`), but the exact shape of several maspsx passes (tail rotations, `_split_funcaddr_la`, `_rotate_marked_store_into_jal_delay`); reported, not counted in `fp` |

A row is `fp` when it has >= 1 HIGH with a strict kind that is not `page_shared`. Flags recorded per HIGH:
`funcaddr` (an `addiu` target is a function address), `after_call` (a call between HIGH and LO).

**Telling integer page constants from symbol splits in raw words.** Decidable: `ori` users (integer), no LO user
(integer value), non-RAM target, one HIGH across two symbols (`page_shared`). NOT decidable: a page constant hidden
from cse and used as `lui rX,0x8008 / lw rY,0x2E60(rX)` is byte-identical to the cdk split of `D_80082E60` - that is
exactly why the pins work. The words cannot say which spelling the ORIGINAL source had, but they do not need to: both
spellings need a compiler that emits the HIGH as its own instruction (or scaffolding that imitates one); the original
was a symbol (integer addresses are macros at every cell, probe above). For slus the pinned objects carry the answer
for the PINNED text: of 816 strict fingerprint HIGHs, 782 are `R_MIPS_HI16` symbol relocations and 34 are literal
page immediates (the page-constant scaffolding, 29 rows; `--validate`). For overlays the row columns `page_pins` /
`page_lit` / `asm_hi` say which rows' current text carries a page constant or inline asm.

## Validation

1. **Sceptic reproduced** (`--mode reloc`, his scan verbatim: `$at` excluded, 8-insn window, first `R_MIPS_LO16` of
   the same symbol): 2.7.2-cdk pin-free 185/317 (lo_sum_other_reg 73, pair_interleaved 118, load_base_ne_dest 51),
   pinned 36/42; 2.8.1 pin-free 66/107, pinned 10/12; 2.7.2 pin-free 6/364; 2.6.3 0/3; 2.91.66 1/1; 2.95.2 2/3 + 1/1.
2. **Raw detector vs relocations** (slus, 1,091 aligned functions, each raw HIGH labelled by the pinned object's word):
   strict fingerprint 782 sym / 34 literal; weak 47 sym; `macro_la` 543/4; `macro_load` 424/26; `at_macro` 210/32;
   `int_ori` 0/181; `page_only` 1/122; `nonram` 0/9. Every `int_ori`, `nonram` and all but one `page_only` HIGH is a
   literal in the object (integers, as classified); before the delay-slot walker learned the taken path, 85 symbol
   HIGHs fell into `page_only` - they were all slot-filled HIGHs.
3. **Row level, sceptic vs raw** (Table 2): the raw detector finds every sceptic row except 13 whose only evidence is
   `slot_lo` (`lui a0 ; jal ; addiu a0` - counted by him as interleaved, weak here); it adds rows through kinds he did
   not count (`high_in_slot`, `store_high_base`, `shared_high`) and through literal-page HIGHs a relocation scan cannot
   see (the pinned 2.6.3/2.7.2 rows `w_8003D92C`, `w_80046E38`, ...).
4. Unit test: one synthetic sequence per kind and one negative per exclusion (`python3 tools/tests/test_split_fingerprint.py`).
5. Spot checks: `dungeon/func_80AEF73C` interleaved at 0x80170FBC (`lui v0,0x8017 / lw s4,8(s1) / addiu v0,v0,22920`),
   `dungeon/func_818CEB58` high_in_slot at 0x818CEBB0, `slus/w_8003E39C` lo_other_reg - the sceptic's rows, as he read them.

## Results

### Table 1 - fingerprint rate by container x registered cell x pin status

`rows` all rows; `addr` rows with >= 1 RAM-address HIGH (any class); `fp` rows with >= 1 strict fingerprint HIGH; `fp/addr` the rate; `weak` rows whose only split evidence is slot_lo; `at` rows with an `$at` macro access.

| container | registered cell | splits? | pins | rows | addr | fp | fp/addr | weak-only | at |
|---|---|---|---|---:|---:|---:|---:|---:|---:|
| dungeon | 2.6.3 | NO | pin-free | 21 | 17 | 1 | 6% | 0 | 1 |
| dungeon | 2.6.3 | NO | pinned | 12 | 12 | 10 | 83% | 0 | 0 |
| dungeon | 2.7.2 | NO | pin-free | 25 | 19 | 2 | 11% | 0 | 8 |
| dungeon | 2.7.2 | NO | pinned | 30 | 28 | 20 | 71% | 0 | 2 |
| dungeon | 2.7.2-cdk | yes | pin-free | 1897 | 1675 | 1471 | 88% | 32 | 3 |
| dungeon | 2.7.2-cdk | yes | pinned | 366 | 357 | 348 | 97% | 1 | 1 |
| dungeon | 2.8.0 | yes | pin-free | 138 | 133 | 120 | 90% | 5 | 0 |
| dungeon | 2.8.0 | yes | pinned | 34 | 33 | 31 | 94% | 0 | 0 |
| dungeon | 2.8.0 -mno-split-addresses | NO | pin-free | 3 | 3 | 0 | 0% | 0 | 0 |
| dungeon | 2.8.1 | yes | pin-free | 115 | 113 | 105 | 93% | 1 | 0 |
| dungeon | 2.8.1 | yes | pinned | 90 | 88 | 87 | 99% | 0 | 1 |
| dungeon | 2.8.1 -mno-split-addresses | NO | pin-free | 1 | 1 | 0 | 0% | 0 | 0 |
| dungeon | 2.8.1 -mno-split-addresses | NO | pinned | 1 | 1 | 0 | 0% | 0 | 0 |
| dungeon | 2.91.66 | yes | pinned | 2 | 1 | 0 | 0% | 1 | 0 |
| dungeon | 2.95.2 | yes | pin-free | 2 | 2 | 2 | 100% | 0 | 0 |
| dungeon | 2.95.2 | yes | pinned | 6 | 6 | 4 | 67% | 0 | 0 |
| main | 2.6.3 | NO | pin-free | 92 | 19 | 0 | 0% | 0 | 9 |
| main | 2.6.3 | NO | pinned | 3 | 1 | 0 | 0% | 0 | 0 |
| main | 2.7.2 | NO | pin-free | 74 | 26 | 1 | 4% | 0 | 18 |
| main | 2.7.2 | NO | pinned | 4 | 4 | 3 | 75% | 1 | 0 |
| main | 2.7.2-cdk | yes | pin-free | 232 | 137 | 94 | 69% | 7 | 1 |
| main | 2.7.2-cdk | yes | pinned | 5 | 3 | 3 | 100% | 0 | 0 |
| main | 2.8.0 | yes | pin-free | 2 | 1 | 1 | 100% | 0 | 0 |
| main | 2.8.0 | yes | pinned | 1 | 0 | 0 | 0% | 0 | 0 |
| main | 2.8.1 | yes | pin-free | 7 | 6 | 6 | 100% | 0 | 0 |
| main | 2.8.1 | yes | pinned | 2 | 2 | 2 | 100% | 0 | 0 |
| main | 2.95.2 | yes | pin-free | 1 | 0 | 0 | 0% | 0 | 0 |
| ovmovie | 2.7.2 | NO | pin-free | 14 | 5 | 0 | 0% | 0 | 0 |
| ovmovie | 2.7.2 | NO | pinned | 1 | 0 | 0 | 0% | 0 | 0 |
| ovmovie | 2.7.2-cdk | yes | pin-free | 2 | 1 | 1 | 100% | 0 | 0 |
| ovmovie | 2.8.1 | yes | pin-free | 5 | 5 | 3 | 60% | 0 | 0 |
| slus | 2.6.3 | NO | pin-free | 3 | 3 | 0 | 0% | 0 | 1 |
| slus | 2.6.3 | NO | pinned | 4 | 4 | 2 | 50% | 0 | 1 |
| slus | 2.7.2 | NO | pin-free | 364 | 146 | 9 | 6% | 0 | 44 |
| slus | 2.7.2 | NO | pinned | 29 | 17 | 5 | 29% | 0 | 12 |
| slus | 2.7.2-cdk | yes | pin-free | 317 | 284 | 225 | 79% | 10 | 24 |
| slus | 2.7.2-cdk | yes | pinned | 42 | 40 | 37 | 92% | 0 | 5 |
| slus | 2.7.2-cdk -mmips-as | NO | pinned | 1 | 1 | 1 | 100% | 0 | 1 |
| slus | 2.8.1 | yes | pin-free | 107 | 100 | 72 | 72% | 3 | 4 |
| slus | 2.8.1 | yes | pinned | 12 | 11 | 11 | 100% | 0 | 4 |
| slus | 2.91.66 | yes | pin-free | 1 | 1 | 1 | 100% | 0 | 0 |
| slus | 2.95.2 | yes | pin-free | 3 | 3 | 2 | 67% | 0 | 0 |
| slus | 2.95.2 | yes | pinned | 1 | 1 | 1 | 100% | 0 | 0 |
| town | 2.6.3 | NO | pin-free | 128 | 44 | 0 | 0% | 0 | 31 |
| town | 2.6.3 | NO | pinned | 18 | 13 | 3 | 23% | 0 | 5 |
| town | 2.7.2 | NO | pin-free | 66 | 33 | 1 | 3% | 0 | 8 |
| town | 2.7.2 | NO | pinned | 28 | 21 | 12 | 57% | 1 | 2 |
| town | 2.7.2-cdk | yes | pin-free | 2301 | 1615 | 1209 | 75% | 100 | 1 |
| town | 2.7.2-cdk | yes | pinned | 87 | 81 | 74 | 91% | 1 | 1 |
| town | 2.8.0 | yes | pin-free | 12 | 8 | 7 | 88% | 1 | 0 |
| town | 2.8.0 | yes | pinned | 1 | 1 | 1 | 100% | 0 | 0 |
| town | 2.8.1 | yes | pin-free | 31 | 26 | 19 | 73% | 0 | 0 |
| town | 2.8.1 | yes | pinned | 7 | 5 | 5 | 100% | 0 | 0 |
| town | 2.8.1 -mno-split-addresses | NO | pin-free | 1 | 1 | 0 | 0% | 0 | 1 |
| town | 2.91.66 | yes | pin-free | 2 | 0 | 0 | 0% | 0 | 0 |
| town | 2.91.66 | yes | pinned | 4 | 3 | 2 | 67% | 0 | 0 |
| town | 2.95.2 | yes | pin-free | 4 | 4 | 4 | 100% | 0 | 0 |
| town | 2.95.2 | yes | pinned | 5 | 5 | 5 | 100% | 0 | 0 |

### Totals by cell class (all containers)

| cell class | pins | rows | addr | fp | fp/addr |
|---|---|---:|---:|---:|---:|
| non-splitting | pin-free | 792 | 317 | 14 | 4.4% |
| non-splitting | pinned | 131 | 102 | 56 | 54.9% |
| splitting | pin-free | 5179 | 4114 | 3342 | 81.2% |
| splitting | pinned | 665 | 637 | 611 | 95.9% |

### Table 2 - slus: the sceptic's relocation detector vs the raw-word detector (per row)

| registered cell | pins | rows | sceptic any | raw fp | both | sceptic only | raw only |
|---|---|---:|---:|---:|---:|---:|---:|
| 2.6.3 | pin-free | 3 | 0 | 0 | 0 | 0 | 0 |
| 2.6.3 | pinned | 4 | 0 | 2 | 0 | 0 | 2 |
| 2.7.2 | pin-free | 364 | 6 | 9 | 6 | 0 | 3 |
| 2.7.2 | pinned | 29 | 0 | 5 | 0 | 0 | 5 |
| 2.7.2-cdk | pin-free | 317 | 185 | 225 | 175 | 10 | 50 |
| 2.7.2-cdk | pinned | 42 | 36 | 37 | 36 | 0 | 1 |
| 2.7.2-cdk -mmips-as | pinned | 1 | 0 | 1 | 0 | 0 | 1 |
| 2.8.1 | pin-free | 107 | 66 | 72 | 63 | 3 | 9 |
| 2.8.1 | pinned | 12 | 10 | 11 | 10 | 0 | 1 |
| 2.91.66 | pin-free | 1 | 1 | 1 | 1 | 0 | 0 |
| 2.95.2 | pin-free | 3 | 2 | 2 | 2 | 0 | 0 |
| 2.95.2 | pinned | 1 | 1 | 1 | 1 | 0 | 0 |

sceptic-only rows (first 12 per stratum): 2.7.2-cdk/pin-free: konami_runtime_w_8003528C, konami_runtime_w_800352B4, konami_runtime_w_800352D8, konami_runtime_w_800352FC, konami_runtime_w_80035320, w_8004437C, w_8004B08C, w_80050BA4, w_80050EF8, w_800540A8; 2.8.1/pin-free: w_80043E04, w_8004D7A8, w_8004D7E8

raw-only rows (first 12 per stratum): 2.6.3/pinned: w_80046E38, w_8004E6F4; 2.7.2/pin-free: konami_runtime_w_8003B7C8, w_800423C0, w_8005A1D0; 2.7.2/pinned: w_8003D92C, w_8003FAD4, w_80041588, w_80051228, w_80052144; 2.7.2-cdk/pin-free: konami_runtime_w_80033AA8, konami_runtime_w_80033AE8, konami_runtime_w_80033B2C, konami_runtime_w_80035378, konami_runtime_w_8003571C, konami_runtime_w_800357B0, konami_runtime_w_80035D40, konami_runtime_w_8003605C, konami_runtime_w_80036110, konami_runtime_w_80036574, konami_runtime_w_80038000, konami_runtime_w_800381A4; 2.7.2-cdk/pinned: w_800589B8; 2.7.2-cdk -mmips-as/pinned: w_8003E39C; 2.8.1/pin-free: konami_runtime_w_8003B92C, w_8003F80C, w_80045340, w_80048190, w_800504B4, w_80053428, w_800549FC, w_80054CD4, w_8005B378; 2.8.1/pinned: w_80043458

### Table 3 - fingerprint kinds, pin-free rows (HIGH counts)

| cell class | high_in_slot | interleaved | lo_other_reg | load_other_reg | store_high_base | shared_high | slot_lo | shared_multioff | funcaddr | after_call | page_shared |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| non-splitting | 5 | 5 | 3 | 4 | 11 | 4 | 10 | 3 | 5 | 6 | 5 |
| splitting | 3502 | 4494 | 1912 | 1942 | 1919 | 1423 | 1256 | 20 | 856 | 899 | 38 |

Pin-free non-splitting rows with a strict fingerprint (the 14 of Table 1), by what the current text contains:
4 carry a page literal without an ASM pin (`town/func_8032F794`, `dungeon/func_80B97094`, `dungeon/func_81917234`,
`slus/w_800423C0`) - HOW each gets the split shape at its non-splitting cell without a pin is not verified here
(a guess: the literal is assigned in several arms and cse cannot fold it); 1 builds the pair in inline asm
(`main/func_800112D8`, `lui $2,%hi / addiu %0,$2,%lo` string); 1 is the whole function as `.word` asm
(`slus/w_8005A1D0` - not C at all); and 8 have none of these - the sceptic's six slus rows plus
`slus/konami_runtime_w_8003B7C8` and `dungeon/func_800938EC` (a loop-hoisted `lui a1,0x8001 / lw v0,668(a1)` over
`D_8001029C[i]`, the shape of maspsx `_fold_lo_into_accesses`). Step 1 (genuine-ASPSX differential) is the
instrument that attributes those 8 to passes; the sceptic traced `w_8004AB7C` to `_sink_call_separated_la` directly.
**The slus 2.7.2 pin-free count is 9 here vs the sceptic's 6 - not a calibration miss**: the 3 extra rows are
`w_800423C0` (page literal), `w_8005A1D0` (`.word` asm) and `konami_runtime_w_8003B7C8` (`shared_high` +
`store_high_base`, kinds his scan did not count; mechanism unattributed); the first two are literal-page HIGHs a
relocation scan cannot see.

`at_macro` is NOT a clean counter-fingerprint: integer-address stores are `$at` macros at every cell (probe), and at
`-G8` (most slus rows) cdk leaves small externs as macros too. At `-G0` it is rare at splitting cells (8 overlay rows
of 5,000+).

### Table 4 - module census best_recipe vs the fingerprint (dungeon/town/main; slus has no module census)

| census recipe | splits? | modules | agree | contradict | weak/no evidence | rows fp/addr (pin-free) |
|---|---|---:|---:|---:|---:|---:|
| 2.7.2-cdk-G0 | yes | 282 | 278 | 0 | 4 | 2681/3378 |
| 2.7.2-cdk | yes | 31 | 28 | 0 | 3 | 53/63 |
| 2.8.0-G0 | yes | 19 | 19 | 0 | 0 | 121/130 |
| 2.6.3-G0 | NO | 13 | 8 | 0 | 5 | 0/55 |
| 2.6.3 | NO | 11 | 6 | 0 | 5 | 0/24 |
| 2.7.2 | NO | 3 | 2 | 1 | 0 | 1/4 |
| 2.7.2-G0 | NO | 3 | 2 | 0 | 1 | 0/19 |
| 2.8.1-G0 | yes | 2 | 2 | 0 | 0 | 22/24 |
| 2.8.0 | yes | 1 | 0 | 0 | 1 | 0/0 |

Contradictions:

| module | census recipe | pin-free fp/addr | all fp/addr | rows registered non-splitting with fp |
|---|---|---:|---:|---|
| dungeon/ovl_10a30bc.c | 2.7.2 | 1/1 | 1/1 |  |

Splitting-recipe modules with no or thin evidence (no contradiction): `dungeon/beldo_ai.c`, `beldo_idle.c`,
`ovl_182c3c0.c`, `ovl_1876800.c`, `ovl_1912800.c`, `ovl_cb3000.c`, `main/card_opt.c`, `main/ovl_80021848.c` - no or
< 3 pin-free addressing rows. Non-splitting-recipe modules marked "no evidence" have no pin-free RAM addressing at all.
Per-module records (rates, verdict, fingerprint rows registered non-splitting): `work/fidelity/module_fingerprint.jsonl`
(the plan asked for this as a column of `ledger/module_recipe_census.jsonl`; the brief forbids ledger edits, so it is a
separate file - merging it is an orchestrator call).

### Table 5 - page-constant pin rows (work/native_lane/r77_fable_splitaddr/cands/page_pin_rows.txt)

| registered cell | splits? | rows | page-pin sites | retail fp | weak only | no evidence |
|---|---|---:|---:|---:|---:|---:|
| 2.6.3 | NO | 13 | 15 | 13 | 0 | 0 |
| 2.7.2 | NO | 35 | 109 | 33 | 2 | 0 |
| 2.7.2-cdk | yes | 66 | 136 | 65 | 0 | 1 |
| 2.8.0 | yes | 6 | 8 | 5 | 0 | 1 |
| 2.8.1 | yes | 26 | 51 | 26 | 0 | 0 |
| 2.91.66 | yes | 1 | 1 | 1 | 0 | 0 |
| 2.95.2 | yes | 3 | 12 | 3 | 0 | 0 |

The 2 weak-only non-splitting page-pin rows (`main/func_80013B18`, `town/func_8032C8B8`) have only a `slot_lo` HIGH;
the 2 splitting rows with no evidence (`dungeon/func_800BFE94` 2.8.0, `town/func_800C5428` cdk) are the residue kind the
sceptic sampled (the page pin changes allocation, not the split).

## Step-4 candidate list

`work/fidelity/step4_candidates.tsv` - every row registered at a non-splitting cell whose retail shows a strict
fingerprint (70, `step4 = CANDIDATE`), then the 2 weak-only rows (`step4 = weak`). Columns: id, cfg, splitting, pins,
page_pins, page_lit, asm_hi, asm_words, fp, fp_highs, kinds (HIGH counts), examples (retail addresses of fingerprint HIGHs),
module, census_recipe, census_splits, mechanism (what in the CURRENT text makes the non-splitting cell emit the shape:
`page_pin` / `page_literal` / `inline_asm_hi` / `asm_words` / `pins_other` (pinned, no page) / `maspsx_or_other`),
step4.
`work/fidelity/page_pin_fingerprint.tsv` - the same columns for all 150 page-constant pin rows.

### Table 6 - step-4 candidates (registered at a non-splitting cell, retail shows a strict fingerprint)

| mechanism in current source | pinned rows | pin-free rows | page-pin sites | census recipe splits (yes/NO/none) |
|---|---:|---:|---:|---|
| page_pin | 46 | 0 | 122 | 38/0/8 |
| page_literal | 9 | 4 | 0 | 7/0/6 |
| maspsx_or_other | 0 | 8 | 0 | 1/0/7 |
| pins_other | 1 | 0 | 0 | 1/0/0 |
| inline_asm_hi | 0 | 1 | 0 | 1/0/0 |
| asm_words | 0 | 1 | 0 | 0/0/1 |

candidates: 70 rows (56 pinned, 323 pins, 122 page-pin sites); by registered cell: 2.7.2 53, 2.6.3 16, 2.7.2-cdk -mmips-as 1

By container: dungeon 33, town 17, slus 17, main 5 (incl. weak). Census coherence: dungeon 28 + town 16 + main 4 = 48
candidates are in modules whose census `best_recipe` is a splitting cell (all `2.7.2-cdk-G0`/`2.7.2-cdk`/`2.8.0-G0`),
0 are in a module whose census recipe is non-splitting, 22 have no module census (17 slus, 5 dungeon deep rows).

### Table 7 - rows registered with -mmips-as / -mno-split-addresses

| row | cfg | pins | fp | kinds | at_macro HIGHs |
|---|---|---:|---|---|---:|
| town/func_80813E14 | 2.8.1-G0 -mno-split-addresses | 0 | - |  | 1 |
| dungeon/func_800A4DDC | 2.8.0 -mno-split-addresses | 0 | - |  | 0 |
| dungeon/func_80F90E88 | 2.8.1-G0 -mno-split-addresses | 17 | - |  | 0 |
| dungeon/func_81811E30 | 2.8.0-G0 -mno-split-addresses | 0 | - |  | 0 |
| dungeon/func_81811E70 | 2.8.0 -mno-split-addresses | 0 | - |  | 0 |
| dungeon/func_81811EC0 | 2.8.1-G0 -mno-split-addresses | 0 | - |  | 0 |
| slus/w_8003E39C | 2.7.2-cdk -mmips-as -G0 | 4 | FP | lo_other_reg | 1 |

The six `-mno-split-addresses` rows show no fingerprint (their flag and their retail agree). `slus/w_8003E39C` (cdk
`-mmips-as`) shows `lo_other_reg` - the sceptic's row; it is in the candidate list.

## Caveats
- Conservative walker: fall-through only (a HIGH whose LO is reached only by a taken conditional branch is missed),
  48-step window. Absence of the fingerprint is not evidence against splitting: a splitting cell's adjacent
  same-register pair is byte-identical to a macro, and 12-31% of pin-free addressing rows at splitting cells show only
  such pairs (on those rows: 510 `macro_la` and 199 `macro_load` HIGHs, 15 `at_macro`, 6 `page_shared`).
- `main` rates are lower (69% of addressing cdk rows) because its rows address less; the non-splitting side is 1/45.
- The retail words cannot tell which spelling (symbol or page) the original used when the bytes are identical; they
  prove the HIGH was emitted as its own instruction. Which recipe reproduces it naturally is step 4's question.
- 8 slus functions (`w_80043674`, `w_80044D24`, `konami_runtime_w_8003BE1C`, ...) are scanned from retail but have no
  relocation ground truth: the cached raw object differs from the linked build (missing hazard nops).
- Temporary files: `work/fidelity/tmp2` (removed at the end). `work/fidelity/` carries a `.ignore` (`*`), so the
  3.3 MB `split_fingerprint.jsonl` is outside agent searches.

## Decisions for the orchestrator
1. **Step-4 scope.** 70 strict candidates (+2 weak). 48 are coherence moves toward a splitting module census recipe
   (clause 4b as written); 22 (17 slus, 5 dungeon without a census module) need the charter amendment (decision 4:
   "toward the recipe the retail bytes prove"). Which cell for the slus ones (cdk vs 2.8.1) is not decidable from the
   fingerprint alone - both split.
2. **Pin-free candidates** (14: 4 page literals without pins, 1 inline-asm pair, 1 `.word` function, 8 maspsx-
   made): these are byte-exact scaffolding the pin census does not count (a page literal assigned to a local, an asm
   `lui/%hi` string, raw words, a maspsx pass). Should the pin census / fidelity debt count them? They are invisible to
   `sites_of`.
3. **Weak tier.** `slot_lo`-only rows (2 non-splitting page-pin rows; ~160 splitting rows) are kept out of `fp`
   because maspsx passes produce that exact shape. Step 1's pass attribution can promote or retire it.
4. **Module census column.** `work/fidelity/module_fingerprint.jsonl` is ready to merge into
   `ledger/module_recipe_census.jsonl` as an evidence column if the orchestrator wants it there (ledger edit, not made).
5. **`dungeon/ovl_10a30bc.c`** census recipe `2.7.2` vs its only addressing row splitting at `2.8.1-G0`: a one-row
   module; the census recipe is probably the thing to revisit.
