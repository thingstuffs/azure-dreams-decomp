# azure-dreams-decomp status

Generated 2026-09-09T01:46:42Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

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
| M2C_FIELD raw offsets | 2950 | 1,457,076 | 57.0% | 120 | 122,816 | 4.8% |
| m2c local names | 5182 | 2,172,128 | 84.9% | 3176 | 1,482,600 | 58.0% |
| ASM_ pins | 2137 | 1,466,884 | 57.3% | 2029 | 1,425,016 | 55.7% |
| goto | 1545 | 1,318,412 | 51.5% | 1540 | 1,315,880 | 51.4% |
| computed-goto jump table | 317 | 437,288 | 17.1% | 317 | 437,288 | 17.1% |
| inline asm outside macros | 362 | 256,260 | 10.0% | 349 | 253,988 | 9.9% |
| fidelity blocking site (LABEL_AS_CALL/PASSTHRU_NO_ARGS) | 1489 | 680,132 | 26.6% | 1070 | 559,652 | 21.9% |
| any fidelity site | 2655 | 1,286,668 | 50.3% | 2327 | 1,197,616 | 46.8% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 751 | 560,500 | 21.9% | 607 | 515,044 | 20.1% |
| maspsx marker pins (scaffolding) | 394 | 351,668 | 13.7% | 367 | 344,720 | 13.5% |
| local address-named struct | 633 | 346,988 | 13.6% | 3175 | 1,611,560 | 63.0% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 632 | 155,088 | 6.1% | 2510 | 408,196 | 16.0% |

Pin sites: 25,878 total; REG 12,818, KEEP 6,889, KEEP_NV 2,501, SCHED_BARRIER 1,355, TAILSLOT_PIN 501, USE 299, USE_NV 261, KEEP_DEP_NV 184.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,558,124 | 100.0% |
| L1 | 2,037,216 | 79.6% |
| L2 | 1,935,748 | 75.7% |
| L3 | 1,902,360 | 74.4% |
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
