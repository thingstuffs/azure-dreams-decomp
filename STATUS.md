# azure-dreams-decomp status

Generated 2026-09-23T07:01:22Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

## Denominator (rows matched at the pin)

| container | rows | bytes | stock rows | stock bytes | baseline exact | exact bytes | unverified |
|---|---:|---:|---:|---:|---:|---:|---:|
| slus | 884 | 473,788 | 884 | 473,788 | 884 | 473,788 | 0 |
| main | 423 | 62,760 | 423 | 62,760 | 423 | 62,760 | 0 |
| town | 2695 | 457,832 | 2695 | 457,832 | 2695 | 457,832 | 0 |
| dungeon | 2743 | 1,560,892 | 2743 | 1,560,892 | 2743 | 1,560,892 | 0 |
| ovmovie | 22 | 2,852 | 22 | 2,852 | 22 | 2,852 | 0 |
| ALL | 6745 | 2,555,272 | 6745 | 2,555,272 | 6745 | 2,555,272 | 0 |

ovmovie is parked by the owner (listed, excluded from ALL). SLUS rows are verified by object identity with the pinned TU (SLUS is byte-exact by its SHA-1 gate, tools/build/build_slus.sh); overlay rows by retail-slice comparison through the per-row scorer, with the window gate as the fallback of record. Non-stock rows (bridge cells, per-row assembler dials, platform asm) would be excluded; there are none at the pin.

Baseline NOT exact: 0 rows

## Shape census: pinned raw text vs current clean tree (files / bytes carrying each defect)

| defect | files (pin) | bytes (pin) | % bytes | files (clean) | bytes (clean) | % bytes |
|---|---:|---:|---:|---:|---:|---:|
| m2c boilerplate block | 2332 | 515,092 | 20.1% | 0 | 0 | 0.0% |
| M2C_FIELD raw offsets | 2950 | 1,457,076 | 57.0% | 0 | 0 | 0.0% |
| m2c local names | 5182 | 2,172,128 | 84.9% | 2697 | 1,275,120 | 49.8% |
| ASM_ pins | 2135 | 1,465,048 | 57.3% | 914 | 883,708 | 34.5% |
| goto | 1545 | 1,318,412 | 51.5% | 1603 | 1,367,948 | 53.5% |
| computed-goto jump table | 317 | 437,288 | 17.1% | 315 | 435,848 | 17.0% |
| inline asm outside macros | 362 | 256,260 | 10.0% | 277 | 231,848 | 9.1% |
| fidelity blocking site (LABEL_AS_CALL/PASSTHRU_NO_ARGS) | 1489 | 680,132 | 26.6% | 308 | 157,064 | 6.1% |
| any fidelity site | 2655 | 1,286,668 | 50.3% | 1778 | 960,508 | 37.5% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 751 | 560,500 | 21.9% | 123 | 106,692 | 4.2% |
| maspsx marker pins (scaffolding) | 393 | 351,556 | 13.7% | 5 | 5,468 | 0.2% |
| do{}while(0) scheduling barrier (scaffolding, pure C) | 227 | 156,176 | 6.1% | 371 | 271,440 | 10.6% |
| fake dependency x=(e)+a;x-=a / arg+v-v (scaffolding, pure C) | 1 | 408 | 0.0% | 2 | 820 | 0.0% |
| local address-named struct | 633 | 346,988 | 13.6% | 3152 | 1,621,112 | 63.4% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 632 | 156,440 | 6.1% | 3067 | 541,976 | 21.2% |

Pin sites now: 3,790 in 913 rows; REG 1,806, KEEP 885, KEEP_NV 500, SCHED_BARRIER 195, KEEP_DEP_NV 77, USE_NV 53, USE 50, CLOBBER 36.  At the pin: 25,759; REG 12,778, KEEP 6,854, KEEP_NV 2,500, SCHED_BARRIER 1,349, TAILSLOT_PIN 499, USE 294, USE_NV 260, KEEP_DEP_NV 184.

Hidden scaffolding, not in the pin count (`pin_census.hidden_asm`): raw asm statements 3, calls of local asm wrappers 9, hand-written asm in function bodies 5 (C that is missing); symbol aliases 111 (a second typed name for one symbol: a missing type); file-scope asm directives 434.

Per-row optimization flags (weak evidence about the real build; each switch is undone from the `t30_cellpins` journal's `cell_from`): 289 rows carry one flag, 40 carry two or more.

Site-for-pin trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"site_for_pin","id":row,"site":"LABEL_AS_CALL|ITC|PASSTHRU","pin":macro,"residue_without_pin":str,"at":iso,"note":str}` -- one pin, or two when one is not enough (owner ruling 2026-09-22 afternoon, "accept 2 pins") -- charter rule 3, "a pin moved elsewhere is not a removal"; the trade is tracked, and L4 is where pins stop counting toward removal regardless): 27.

Void callees (`config/void_callees.txt`, tiers read from its section-header comments -- no per-line marker exists): tier A 30, tier B 1 symbols (matches `census.declared_void_callees()`). Rows whose PASSTHRU_NO_ARGS exemption rests on a tier-B symbol alone (blocked again if tier B were dropped, tier-A/in-tree exemptions do not cover them): 11 rows, 11,864 B.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,558,124 | 100.0% |
| L1 | 2,558,124 | 100.0% |
| L2 | 2,558,124 | 100.0% |
| L3 | 2,558,124 | 100.0% |
| L4 | 0 | 0.0% |
| L5 | 0 | 0.0% |

On shared record headers (T7, `include/records/`): 1163 rows, 658,372 bytes (25.7%); records used: 102.

L4 residue (rows below L4, by blocker; a row can carry more than one): pins 927 rows (888,656 B), tail_jump 9 rows (2,544 B), not_in_module 6,767 rows (2,558,124 B).

## Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)

| container | assert file:line / expression | developer identifiers | randomizer map (code) | randomizer map (data tables) | resident pointer tables | script function names | prior notes | applied names | any (rows / bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| slus | 0 | 0 | 1 | 0 | 72 | 7 | 408 | 14 | 479 / 328,024 |
| main | 18 | 5 | 1 | 0 | 0 | 0 | 0 | 0 | 19 / 6,420 |
| town | 21 | 8 | 1 | 1 | 0 | 114 | 0 | 0 | 137 / 18,196 |
| dungeon | 0 | 0 | 24 | 21 | 0 | 0 | 0 | 0 | 44 / 35,592 |

Every lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.
