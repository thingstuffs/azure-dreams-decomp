# azure-dreams-decomp status

Generated 2026-09-13T12:51:58Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

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
| m2c boilerplate block | 2332 | 515,092 | 20.1% | 32 | 6,088 | 0.2% |
| M2C_FIELD raw offsets | 2950 | 1,457,076 | 57.0% | 10 | 7,368 | 0.3% |
| m2c local names | 5182 | 2,172,128 | 84.9% | 2873 | 1,360,324 | 53.2% |
| ASM_ pins | 2135 | 1,465,048 | 57.3% | 1510 | 1,208,092 | 47.2% |
| goto | 1545 | 1,318,412 | 51.5% | 1589 | 1,350,100 | 52.8% |
| computed-goto jump table | 317 | 437,288 | 17.1% | 317 | 437,288 | 17.1% |
| inline asm outside macros | 362 | 256,260 | 10.0% | 284 | 234,168 | 9.2% |
| fidelity blocking site (LABEL_AS_CALL/PASSTHRU_NO_ARGS) | 1489 | 680,132 | 26.6% | 308 | 157,064 | 6.1% |
| any fidelity site | 2655 | 1,286,668 | 50.3% | 1778 | 960,508 | 37.5% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 751 | 560,500 | 21.9% | 341 | 266,540 | 10.4% |
| maspsx marker pins (scaffolding) | 393 | 351,556 | 13.7% | 134 | 130,124 | 5.1% |
| do{}while(0) scheduling barrier (scaffolding, pure C) | 227 | 156,176 | 6.1% | 415 | 295,964 | 11.6% |
| fake dependency x=(e)+a;x-=a / arg+v-v (scaffolding, pure C) | 1 | 408 | 0.0% | 2 | 820 | 0.0% |
| local address-named struct | 633 | 346,988 | 13.6% | 3178 | 1,620,288 | 63.3% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 632 | 156,440 | 6.1% | 2829 | 474,144 | 18.5% |

Pin sites now: 8,628 in 1,507 rows; REG 4,207, KEEP 2,070, KEEP_NV 854, SCHED_BARRIER 488, TAILSLOT_PIN 163, USE_NV 135, KEEP_DEP_NV 119, USE 101.  At the pin: 25,759; REG 12,778, KEEP 6,854, KEEP_NV 2,500, SCHED_BARRIER 1,349, TAILSLOT_PIN 499, USE 294, USE_NV 260, KEEP_DEP_NV 184.

Hidden scaffolding, not in the pin count (`pin_census.hidden_asm`): raw asm statements 3, calls of local asm wrappers 10, hand-written asm in function bodies 5 (C that is missing); symbol aliases 113 (a second typed name for one symbol: a missing type); file-scope asm directives 444.

Per-row optimization flags (weak evidence about the real build; each switch is undone from the `t30_cellpins` journal's `cell_from`): 351 rows carry one flag, 40 carry two or more.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,558,124 | 100.0% |
| L1 | 2,396,204 | 93.7% |
| L2 | 2,396,048 | 93.7% |
| L3 | 2,394,688 | 93.6% |
| L4 | 0 | 0.0% |
| L5 | 0 | 0.0% |

On shared record headers (T7, `include/records/`): 1164 rows, 658,600 bytes (25.7%); records used: 102.

## Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)

| container | assert file:line / expression | developer identifiers | randomizer map (code) | randomizer map (data tables) | resident pointer tables | script function names | prior notes | applied names | any (rows / bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| slus | 0 | 0 | 1 | 0 | 72 | 7 | 408 | 14 | 479 / 328,024 |
| main | 18 | 5 | 1 | 0 | 0 | 0 | 0 | 0 | 19 / 6,420 |
| town | 21 | 8 | 1 | 1 | 0 | 114 | 0 | 0 | 137 / 18,196 |
| dungeon | 0 | 0 | 24 | 21 | 0 | 0 | 0 | 0 | 44 / 35,592 |

Every lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.
