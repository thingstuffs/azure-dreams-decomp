# Pin pattern tables

Generated 2026-09-11T10:55Z by `tools/pin_patterns.py` - do not edit; the narrative is `docs/PIN_PATTERNS.md`.  Site records at the current text: 8,889 in 1,339 rows (of 1,717 pinned rows); marker pins (TAILSLOT/PAGEBASE/JALDELAY) left out below: 151.  Singly exact: 0.

## Damage when a site is erased alone

| words | sites |
|---|---:|
| 1-2 | 1,670 |
| 3-5 | 2,020 |
| 6-12 | 2,273 |
| 13+ | 2,775 |

## Coverage - within 5 words (3,690 sites)

| granularity | clusters | cover 50 % | cover 80 % | cover 90 % | singletons |
|---|---:|---:|---:|---:|---:|
| residue class | 15 | 2 | 4 | 6 | 0 |
| macro family x class | 87 | 5 | 14 | 24 | 13 |
| residue signature | 599 | 5 | 72 | 230 | 393 |
| macro family x signature | 838 | 15 | 186 | 469 | 567 |

## Coverage - within 12 words (5,963 sites)

| granularity | clusters | cover 50 % | cover 80 % | cover 90 % | singletons |
|---|---:|---:|---:|---:|---:|
| residue class | 15 | 3 | 5 | 9 | 0 |
| macro family x class | 98 | 6 | 19 | 32 | 13 |
| residue signature | 1513 | 12 | 365 | 917 | 1105 |
| macro family x signature | 1872 | 34 | 680 | 1276 | 1392 |

## Coverage - every non-marker site (8,738 sites)

| granularity | clusters | cover 50 % | cover 80 % | cover 90 % | singletons |
|---|---:|---:|---:|---:|---:|
| residue class | 15 | 3 | 7 | 10 | 0 |
| macro family x class | 103 | 8 | 24 | 37 | 8 |
| residue signature | 2835 | 36 | 1088 | 1962 | 2223 |
| macro family x signature | 3311 | 93 | 1564 | 2438 | 2628 |

## Top residue signatures (within 12 words)

| sites | signature |
|---|---:|
| 1,271 | `rename*` |
| 609 | `rename` |
| 313 | `move:move move:sw` |
| 182 | `move:move` |
| 181 | `move:addiu` |
| 118 | `+addiu -ori move:lui` |
| 66 | `+addiu -ori` |
| 65 | `operand*` |
| 57 | `move:addiu move:lui` |
| 52 | `+addiu -ori rename` |
| 45 | `move:lui` |
| 45 | `move:lw` |
| 43 | `+nop -move` |
| 38 | `move:move move:sw rename*` |
| 33 | `operand` |
| 32 | `move:addiu move:move` |
| 28 | `+move rename*` |
| 27 | `move:sw` |
| 26 | `move:sh` |
| 24 | `+nop -move rename*` |
| 24 | `move:move move:sw rename` |
| 23 | `move:lhu` |
| 21 | `move:move* move:sw rename*` |
| 19 | `+move move:beqz rename*` |
| 18 | `+move move:addiu rename*` |
| 16 | `move:sll` |
| 16 | `move:lw move:nop rename*` |
| 15 | `move:sra` |
| 15 | `+move -nop` |
| 15 | `move:addiu move:move rename` |

## Inside the rename cluster (within 12 words)

| which operand differs | instructions | sites |
|---|---:|---:|
| destination only | 3,003 | 1,622 |
| a source only | 1,806 | 909 |
| a store/branch reads another register | 1,757 | 924 |
| destination and a source | 1,217 | 668 |
| FOLD: retail in place, gcc reads the copy's source | 317 | 225 |
| SPLIT: gcc in place, retail reads another register | 187 | 177 |

| directional kind | mnemonic | instructions |
|---|---:|---:|
| FOLD | addiu | 206 |
| SPLIT | addiu | 75 |
| FOLD | sll | 42 |
| SPLIT | addu | 32 |
| FOLD | addu | 24 |
| SPLIT | andi | 20 |
| SPLIT | sra | 20 |
| FOLD | sra | 18 |
| SPLIT | sll | 15 |
| SPLIT | subu | 11 |
| FOLD | negu | 10 |
| SPLIT | ori | 7 |
| FOLD | andi | 6 |
| FOLD | slt | 3 |
| SPLIT | or | 2 |
| FOLD | and | 2 |

## Linkage - 2,405 pin pairs in 565 rows

| relation | pairs | share |
|---|---:|---:|
| additive (joint = sum) | 1,284 | 53 % |
| overlap (joint < sum) | 961 | 40 % |
| synergy (joint > sum) | 131 | 5 % |
| cancel (joint < either single) | 29 | 1 % |

| line gap | pairs | overlap | synergy | cancel |
|---|---:|---:|---:|---:|
| <= 3 lines | 600 | 52 % | 10 % | 1 % |
| 4-15 | 741 | 43 % | 4 % | 1 % |
| 16+ | 1064 | 32 % | 3 % | 1 % |

Exact proper subsets still open at the current text (size of n): none

## What has ever freed a pin - 515 removed sites (pre-fix text not in git: 13)

| fix | removed sites |
|---|---:|
| t15 fence | 175 |
| t16_absidiom | 56 |
| t15 narrow | 42 |
| t15 fence-return | 25 |
| t13_cellfix | 23 |
| pin_subsets | 22 |
| t13_depin rewrite | 21 |
| t13_depin delete,rewrite | 17 |
| t13_depin pure erasure | 12 |
| t15 fence+fence-return | 10 |
| t15 depinject | 9 |
| t15 partial-strip | 9 |
| t13_depin retype | 9 |
| t15 fence2 | 8 |
| t15 efence | 8 |
| t15 efence+fence | 7 |
| t15 dup_after_if | 6 |
| t13_depin fence,insert | 6 |
| t13_depin retype,rewrite | 6 |
| t9_regpins delete | 6 |
| t15 deadstore | 5 |
| t13_depin delete,insert | 5 |
| t13_depin insert,rewrite | 4 |
| t15 deadstore+narrow | 3 |
| t15 depinject+fence | 3 |
| t9_regpins insert,rewrite | 3 |
| t15 collapse | 2 |
| t13_depin delete,retype,rewrite | 2 |
| t9_regpins retype | 1 |
| t15 dup_after_if+fence | 1 |

Replaced by a fence or fence variant: 244 of 515 (47 %).  Macro family of the removed sites: REG 236, KEEP 168, BARRIER 61, USE 24, KEEP_NV 23, UNDEF 1, MARKER 1, SET 1.

