# azure-clean status

Generated 2026-09-07T10:19:29Z. Upstream pin `7b62e858` (7b62e858ff29, extracted 2026-09-07T03:01:54Z).

## Denominator (rows matched upstream at the pin)

| container | rows | bytes | stock rows | stock bytes | baseline exact | exact bytes | unverified |
|---|---:|---:|---:|---:|---:|---:|---:|
| slus | 884 | 473,788 | 864 | 464,388 | 864 | 464,388 | 0 |
| main | 423 | 62,760 | 402 | 56,908 | 402 | 56,908 | 0 |
| town | 2695 | 457,832 | 2662 | 428,088 | 2662 | 428,088 | 0 |
| dungeon | 2742 | 1,560,880 | 2713 | 1,540,628 | 2713 | 1,540,628 | 0 |
| ovmovie | 22 | 2,852 | 21 | 2,712 | 21 | 2,712 | 0 |
| ALL | 6744 | 2,555,260 | 6641 | 2,490,012 | 6641 | 2,490,012 | 0 |

ovmovie is parked by the owner (listed, excluded from ALL). SLUS rows are verified by object identity with the pinned TU (upstream SLUS is byte-exact by its SHA-1 gate); overlay rows by retail-slice comparison through upstream's scorer. Non-stock rows (bridge cells, per-row assembler dials, platform asm) are excluded until they close upstream.

Baseline NOT exact: 0 rows

## Shape census: pinned upstream vs current clean tree (files / bytes carrying each defect)

| defect | files (pin) | bytes (pin) | % bytes | files (clean) | bytes (clean) | % bytes |
|---|---:|---:|---:|---:|---:|---:|
| m2c boilerplate block | 2334 | 516,520 | 20.2% | 43 | 15,852 | 0.6% |
| M2C_FIELD raw offsets | 2950 | 1,457,076 | 57.0% | 160 | 156,700 | 6.1% |
| m2c local names | 5181 | 2,172,116 | 84.9% | 5181 | 2,172,116 | 84.9% |
| ASM_ pins | 2096 | 1,441,328 | 56.3% | 2038 | 1,415,992 | 55.4% |
| goto | 1545 | 1,318,004 | 51.5% | 1545 | 1,318,004 | 51.5% |
| computed-goto jump table | 317 | 437,288 | 17.1% | 317 | 437,288 | 17.1% |
| inline asm outside macros | 361 | 255,964 | 10.0% | 361 | 255,964 | 10.0% |
| fidelity blocking site (LABEL_AS_CALL/PASSTHRU_NO_ARGS) | 1501 | 684,808 | 26.8% | 1501 | 684,808 | 26.8% |
| any fidelity site | 2662 | 1,288,900 | 50.4% | 2662 | 1,288,900 | 50.4% |
| local address-named struct | 633 | 346,988 | 13.6% | 3391 | 1,616,448 | 63.2% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 641 | 159,188 | 6.2% | 1252 | 197,236 | 7.7% |

Pin sites: 25,629 total; REG 12,667, KEEP 6,869, KEEP_NV 2,462, SCHED_BARRIER 1,337, TAILSLOT_PIN 511, USE 288, USE_NV 253, KEEP_DEP_NV 180.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,492,724 | 97.4% |
| L1 | 1,822,620 | 71.2% |
| L2 | 1,729,864 | 67.6% |
| L3 | 116,832 | 4.6% |
| L4 | 0 | 0.0% |
| L5 | 0 | 0.0% |
