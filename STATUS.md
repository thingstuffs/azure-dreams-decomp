# azure-dreams-decomp status

Generated 2026-09-08T03:40:06Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

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
| m2c local names | 5182 | 2,172,128 | 84.9% | 5182 | 2,172,128 | 84.9% |
| ASM_ pins | 2137 | 1,466,884 | 57.3% | 2054 | 1,432,384 | 56.0% |
| goto | 1545 | 1,318,412 | 51.5% | 1545 | 1,318,412 | 51.5% |
| computed-goto jump table | 317 | 437,288 | 17.1% | 317 | 437,288 | 17.1% |
| inline asm outside macros | 362 | 256,260 | 10.0% | 362 | 256,260 | 10.0% |
| fidelity blocking site (LABEL_AS_CALL/PASSTHRU_NO_ARGS) | 1489 | 680,132 | 26.6% | 1070 | 559,652 | 21.9% |
| any fidelity site | 2655 | 1,286,668 | 50.3% | 2327 | 1,197,616 | 46.8% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 751 | 560,500 | 21.9% | 637 | 518,168 | 20.3% |
| maspsx marker pins (scaffolding) | 394 | 351,668 | 13.7% | 381 | 346,700 | 13.6% |
| local address-named struct | 633 | 346,988 | 13.6% | 3182 | 1,613,264 | 63.1% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 632 | 155,088 | 6.1% | 1242 | 192,948 | 7.5% |

Pin sites: 25,878 total; REG 12,818, KEEP 6,889, KEEP_NV 2,501, SCHED_BARRIER 1,355, TAILSLOT_PIN 501, USE 299, USE_NV 261, KEEP_DEP_NV 184.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,558,124 | 100.0% |
| L1 | 1,991,104 | 77.8% |
| L2 | 1,891,456 | 73.9% |
| L3 | 1,593,004 | 62.3% |
| L4 | 0 | 0.0% |
| L5 | 0 | 0.0% |

On shared record headers (T7, `include/records/`): 1168 rows, 659,544 bytes (25.8%); records used: 88.

## Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)

| container | assert file:line / expression | developer identifiers | randomizer map (code) | randomizer map (data tables) | resident pointer tables | script function names | prior notes | applied names | any (rows / bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| slus | 0 | 0 | 1 | 0 | 72 | 2 | 408 | 14 | 475 / 327,604 |
| main | 18 | 5 | 1 | 0 | 0 | 0 | 0 | 0 | 19 / 6,420 |
| town | 21 | 8 | 1 | 1 | 0 | 51 | 0 | 0 | 74 / 10,228 |
| dungeon | 0 | 0 | 24 | 21 | 0 | 0 | 0 | 0 | 44 / 35,592 |

Every lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.
