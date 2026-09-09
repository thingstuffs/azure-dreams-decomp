# azure-dreams-decomp status

Generated 2026-09-09T19:51:59Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

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
| m2c local names | 5182 | 2,172,128 | 84.9% | 2874 | 1,360,504 | 53.2% |
| ASM_ pins | 2137 | 1,466,884 | 57.3% | 1829 | 1,348,172 | 52.7% |
| goto | 1545 | 1,318,412 | 51.5% | 1565 | 1,332,436 | 52.1% |
| computed-goto jump table | 317 | 437,288 | 17.1% | 317 | 437,288 | 17.1% |
| inline asm outside macros | 362 | 256,260 | 10.0% | 335 | 246,252 | 9.6% |
| fidelity blocking site (LABEL_AS_CALL/PASSTHRU_NO_ARGS) | 1489 | 680,132 | 26.6% | 309 | 157,164 | 6.1% |
| any fidelity site | 2655 | 1,286,668 | 50.3% | 1779 | 960,608 | 37.6% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 751 | 560,500 | 21.9% | 341 | 266,540 | 10.4% |
| maspsx marker pins (scaffolding) | 394 | 351,668 | 13.7% | 138 | 130,644 | 5.1% |
| do{}while(0) scheduling barrier (scaffolding, pure C) | 226 | 162,516 | 6.4% | 260 | 151,712 | 5.9% |
| local address-named struct | 633 | 346,988 | 13.6% | 3179 | 1,620,468 | 63.3% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 632 | 155,088 | 6.1% | 2727 | 449,852 | 17.6% |

Pin sites: 25,878 total; REG 12,818, KEEP 6,889, KEEP_NV 2,501, SCHED_BARRIER 1,355, TAILSLOT_PIN 501, USE 299, USE_NV 261, KEEP_DEP_NV 184.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,558,124 | 100.0% |
| L1 | 2,396,020 | 93.7% |
| L2 | 2,395,864 | 93.7% |
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
