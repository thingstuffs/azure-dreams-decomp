# azure-dreams-decomp status

Generated 2026-09-08T00:28:36Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

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
| ASM_ pins | 2137 | 1,466,884 | 57.3% | 2077 | 1,440,156 | 56.3% |
| goto | 1545 | 1,318,412 | 51.5% | 1545 | 1,318,412 | 51.5% |
| computed-goto jump table | 317 | 437,288 | 17.1% | 317 | 437,288 | 17.1% |
| inline asm outside macros | 362 | 256,260 | 10.0% | 362 | 256,260 | 10.0% |
| fidelity blocking site (LABEL_AS_CALL/PASSTHRU_NO_ARGS) | 1489 | 680,132 | 26.6% | 1363 | 643,104 | 25.1% |
| any fidelity site | 2655 | 1,286,668 | 50.3% | 2541 | 1,256,708 | 49.1% |
| local address-named struct | 633 | 346,988 | 13.6% | 3182 | 1,613,264 | 63.1% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 632 | 155,088 | 6.1% | 1243 | 193,136 | 7.5% |

Pin sites: 25,878 total; REG 12,818, KEEP 6,889, KEEP_NV 2,501, SCHED_BARRIER 1,355, TAILSLOT_PIN 501, USE 299, USE_NV 261, KEEP_DEP_NV 184.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,558,124 | 100.0% |
| L1 | 1,907,800 | 74.6% |
| L2 | 1,808,376 | 70.7% |
| L3 | 1,084,380 | 42.4% |
| L4 | 0 | 0.0% |
| L5 | 0 | 0.0% |

On shared record headers (T7, `include/records/`): 1168 rows, 659,544 bytes (25.8%); records used: 88.
