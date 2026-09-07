# Pin census (ledger/pins.jsonl)

Single-site erasure from the original pinned text, one experiment per site, verified against retail bytes.

- sites: **22505** in **2066** rows; dead on their own: **10474 (47%)**; rows whose every pin is dead on its own: **92** (4%)
- build failures: 22

A pin is *dead* if erasing it alone leaves the bytes exact. Pins interact: the greedy transform (T2) erases more than the single-site rate in some rows and less in others.


### by macro

| key | sites | dead (erasable) | build-fail | breakage classes when kept | length when kept |
|---|---:|---:|---:|---|---|
| ASM_REG | 11656 | 5881 (50%) | 1 | broad 1299, reg-rename 1226, reorder-only 710, addressing 467 | {'same-len': 4412, 'shorter': 400, 'longer': 962} |
| ASM_KEEP | 6098 | 3003 (49%) | 20 | reorder-only 710, broad 517, length-drift 349, block-order 332 | {'same-len': 1785, 'shorter': 794, 'longer': 496} |
| ASM_KEEP_NV | 1750 | 820 (47%) | 0 | reorder-only 273, broad 193, length-drift 108, code-motion 70 | {'longer': 148, 'shorter': 162, 'same-len': 620} |
| ASM_SCHED_BARRIER | 1078 | 325 (30%) | 0 | reorder-only 230, block-order 140, code-motion 105, length-drift 88 | {'shorter': 218, 'same-len': 446, 'longer': 89} |
| ASM_TAILSLOT_PIN | 460 | 0 (0%) | 0 | delay-slot 238, length-drift 127, slot-rotation 48, broad 25 | {'same-len': 267, 'shorter': 179, 'longer': 14} |
| ASM_USE | 259 | 110 (42%) | 0 | reorder-only 29, broad 23, block-order 22, code-motion 16 | {'shorter': 49, 'same-len': 84, 'longer': 16} |
| ASM_USE_NV | 211 | 83 (39%) | 0 | reorder-only 23, broad 22, length-drift 21, block-order 16 | {'same-len': 79, 'shorter': 35, 'longer': 14} |
| ASM_MEM_BARRIER | 164 | 44 (27%) | 0 | length-drift 36, block-order 19, reorder-only 17, code-motion 13 | {'shorter': 58, 'same-len': 44, 'longer': 18} |
| ASM_KEEP_DEP_NV | 144 | 41 (28%) | 0 | reorder-only 41, slus-diff 19, length-drift 13, broad 11 | {'same-len': 78, 'shorter': 16, 'longer': 9} |
| ASM_CLOBBER | 136 | 35 (26%) | 1 | reg-rename 24, block-order 19, reorder-only 12, length-drift 11 | {'shorter': 32, 'same-len': 56, 'longer': 12} |
| ASM_TAILSLOT_PIN_TIED | 128 | 2 (2%) | 0 | delay-slot 63, length-drift 38, slot-rotation 12, hold-set 4 | {'shorter': 58, 'same-len': 65, 'longer': 3} |
| ASM_SET | 81 | 33 (41%) | 0 | reorder-only 10, reg-rename 10, code-motion 9, slot-rotation 4 | {'same-len': 36, 'shorter': 5, 'longer': 7} |
| ASM_USE2 | 78 | 34 (44%) | 0 | reorder-only 13, broad 7, length-drift 4, block-order 4 | {'shorter': 13, 'same-len': 29, 'longer': 2} |
| ASM_USE2_NV | 63 | 20 (32%) | 0 | broad 13, reorder-only 7, hold-set 6, reg-rename 4 | {'same-len': 37, 'longer': 2, 'shorter': 4} |
| ASM_PAGEBASE_PIN | 51 | 1 (2%) | 0 | delay-slot 50 | {'same-len': 50} |
| ASM_KEEP4 | 36 | 17 (47%) | 0 | length-drift 6, reorder-only 5, broad 2, code-motion 1 | {'shorter': 9, 'same-len': 8, 'longer': 2} |
| ASM_UNDEF | 33 | 13 (39%) | 0 | block-order 4, hold-set 3, length-drift 3, reg-rename 3 | {'longer': 8, 'same-len': 8, 'shorter': 4} |
| ASM_KEEP4_NV | 28 | 6 (21%) | 0 | reorder-only 13, code-motion 4, hold-set 2, broad 1 | {'same-len': 19, 'longer': 2, 'shorter': 1} |
| ASM_USE_G_NV | 9 | 0 (0%) | 0 | li-expansion 2, hold-set 2, reg-rename 2, reorder-only 1 | {'same-len': 5, 'shorter': 3, 'longer': 1} |
| ASM_KEEP_MEMDEP_NV | 9 | 0 (0%) | 0 | reorder-only 5, code-motion 1, dead-code-retention 1, broad 1 | {'same-len': 9} |
| ASM_KEEP_MEMDEP | 7 | 0 (0%) | 0 | broad 3, li-expansion 1, reorder-only 1, code-motion 1 | {'longer': 1, 'same-len': 5, 'shorter': 1} |
| ASM_JALDELAY_PIN | 7 | 4 (57%) | 0 | reorder-only 2, slus-diff 1 | {'same-len': 3} |
| ASM_KEEP_MEM_NV | 6 | 0 (0%) | 0 | reorder-only 4, code-motion 1, slot-rotation 1 | {'same-len': 5, 'shorter': 1} |
| ASM_KEEP_OLD | 5 | 1 (20%) | 0 | length-drift 3, slus-diff 1 | {'shorter': 2, 'longer': 1, 'same-len': 1} |
| ASM_CLOBBER_A0 | 3 | 0 (0%) | 0 | length-drift 3 | {'shorter': 3} |
| ASM_DEP | 1 | 0 (0%) | 0 | reorder-only 1 | {'same-len': 1} |
| ASM_KEEP_MEM | 1 | 0 (0%) | 0 | reorder-only 1 | {'longer': 1} |
| ASM_LIVE_SIBCALL_PIN | 1 | 0 (0%) | 0 | dead-code-retention 1 | {'shorter': 1} |
| ASM_SHAPE_D_SIBCALL_PIN | 1 | 1 (100%) | 0 |  | {} |
| ASM_KEEP_INPUT | 1 | 0 (0%) | 0 | slus-diff 1 | {'same-len': 1} |


### ASM_REG by register

| key | sites | dead (erasable) | build-fail | breakage classes when kept | length when kept |
|---|---:|---:|---:|---|---|
| $2 (v) | 2644 | 1357 (51%) | 0 | broad 532, reg-rename 179, const-remat 126, length-drift 97 | {'longer': 195, 'same-len': 971, 'shorter': 121} |
| $3 (v) | 1726 | 904 (52%) | 0 | broad 280, reg-rename 247, code-motion 58, length-drift 48 | {'same-len': 665, 'longer': 105, 'shorter': 52} |
| $4 (a) | 1421 | 669 (47%) | 1 | reorder-only 143, reg-rename 130, broad 119, code-motion 105 | {'shorter': 48, 'longer': 171, 'same-len': 532} |
| $5 (a) | 987 | 429 (43%) | 0 | reg-rename 182, reorder-only 81, broad 75, code-motion 48 | {'same-len': 405, 'shorter': 24, 'longer': 129} |
| $16 (s) | 619 | 342 (55%) | 0 | reg-rename 58, reorder-only 46, broad 43, addressing 36 | {'longer': 48, 'same-len': 203, 'shorter': 26} |
| $17 (s) | 605 | 367 (61%) | 0 | addressing 53, reorder-only 46, reg-rename 40, broad 34 | {'same-len': 188, 'longer': 33, 'shorter': 17} |
| $18 (s) | 573 | 355 (62%) | 0 | addressing 56, reorder-only 48, reg-rename 35, hold-set 22 | {'same-len': 176, 'longer': 30, 'shorter': 12} |
| $6 (a) | 499 | 235 (47%) | 0 | reg-rename 72, broad 43, reorder-only 33, code-motion 21 | {'same-len': 168, 'longer': 83, 'shorter': 13} |
| $19 (s) | 460 | 242 (53%) | 0 | addressing 74, reorder-only 38, broad 30, hold-set 21 | {'same-len': 176, 'longer': 23, 'shorter': 19} |
| $20 (s) | 401 | 227 (57%) | 0 | addressing 76, reorder-only 27, reg-rename 20, hold-set 15 | {'same-len': 151, 'longer': 10, 'shorter': 13} |
| $21 (s) | 372 | 153 (41%) | 0 | reorder-only 92, addressing 55, reg-rename 20, const-remat 15 | {'same-len': 198, 'shorter': 10, 'longer': 11} |
| $7 (a) | 340 | 152 (45%) | 0 | reg-rename 58, broad 27, length-drift 17, code-motion 16 | {'longer': 57, 'same-len': 125, 'shorter': 6} |
| $22 (s) | 273 | 123 (45%) | 0 | reorder-only 71, addressing 23, reg-rename 23, hold-set 9 | {'same-len': 134, 'shorter': 6, 'longer': 10} |
| $8 (t) | 247 | 98 (40%) | 0 | reg-rename 53, broad 39, const-remat 20, hold-set 11 | {'same-len': 115, 'shorter': 14, 'longer': 20} |
| $23 (s) | 170 | 77 (45%) | 0 | addressing 27, reg-rename 24, hold-set 13, broad 8 | {'same-len': 75, 'longer': 11, 'shorter': 7} |
| $9 (t) | 85 | 42 (49%) | 0 | reg-rename 25, broad 8, length-drift 4, const-remat 2 | {'same-len': 36, 'shorter': 3, 'longer': 4} |
| $10 (t) | 53 | 40 (75%) | 0 | reg-rename 7, broad 2, length-drift 2, code-motion 1 | {'same-len': 11, 'shorter': 1, 'longer': 1} |
| $0 (None) | 50 | 0 (0%) | 0 | li-expansion 27, length-drift 7, broad 6, hold-set 5 | {'longer': 15, 'same-len': 30, 'shorter': 5} |
| $11 (t) | 38 | 21 (55%) | 0 | reg-rename 7, broad 3, reorder-only 2, slus-diff 2 | {'same-len': 16, 'shorter': 1} |
| $12 (t) | 28 | 22 (79%) | 0 | reg-rename 3, broad 3 | {'same-len': 6} |
| $13 (t) | 14 | 10 (71%) | 0 | reg-rename 3, code-motion 1 | {'same-len': 4} |
| $14 (t) | 11 | 6 (55%) | 0 | reg-rename 5 | {'same-len': 5} |
| $1 (at) | 8 | 2 (25%) | 0 | reg-rename 3, slus-diff 3 | {'same-len': 6} |
| $15 (t) | 7 | 2 (29%) | 0 | reg-rename 4, length-drift 1 | {'longer': 1, 'same-len': 4} |
| $29 (sp) | 7 | 0 (0%) | 0 | hold-set 3, broad 2, length-drift 1, reg-rename 1 | {'longer': 3, 'same-len': 4} |
| $24 (t) | 4 | 2 (50%) | 0 | reg-rename 1, slus-diff 1 | {'same-len': 2} |
| $25 (t) | 3 | 1 (33%) | 0 | reg-rename 2 | {'same-len': 2} |


### by container

| key | sites | dead (erasable) | build-fail | breakage classes when kept | length when kept |
|---|---:|---:|---:|---|---|
| dungeon | 17774 | 8304 (47%) | 6 | broad 1794, reorder-only 1763, reg-rename 1222, code-motion 806 | {'same-len': 6481, 'shorter': 1598, 'longer': 1385} |
| town | 3799 | 1803 (47%) | 6 | broad 371, reorder-only 334, reg-rename 285, length-drift 189 | {'longer': 325, 'same-len': 1309, 'shorter': 356} |
| slus | 785 | 320 (41%) | 7 | slus-diff 302, length-drift 156 | {'same-len': 302, 'longer': 79, 'shorter': 77} |
| main | 130 | 38 (29%) | 3 | broad 14, reg-rename 13, const-remat 11, reorder-only 10 | {'same-len': 56, 'shorter': 17, 'longer': 16} |
| ovmovie | 17 | 9 (53%) | 0 | code-motion 2, reorder-only 2, reg-rename 1, addressing 1 | {'same-len': 5, 'longer': 3} |


### by compiler cell

| key | sites | dead (erasable) | build-fail | breakage classes when kept | length when kept |
|---|---:|---:|---:|---|---|
| 2.7.2-cdk-G0 | 9262 | 4456 (48%) | 2 | broad 941, reorder-only 857, reg-rename 695, code-motion 408 | {'shorter': 759, 'same-len': 3341, 'longer': 704} |
| 2.8.1-G0 | 7504 | 3398 (45%) | 1 | reorder-only 811, broad 734, reg-rename 466, length-drift 364 | {'longer': 555, 'same-len': 2771, 'shorter': 779} |
| 2.7.2 | 1545 | 642 (42%) | 15 | length-drift 153, broad 148, reg-rename 96, reorder-only 91 | {'same-len': 530, 'longer': 191, 'shorter': 167} |
| 2.7.2-cdk | 1308 | 588 (45%) | 3 | slus-diff 193, length-drift 123, reorder-only 81, broad 77 | {'shorter': 114, 'same-len': 494, 'longer': 109} |
| 2.7.2-G0 | 1127 | 530 (47%) | 1 | broad 138, reorder-only 94, reg-rename 70, length-drift 52 | {'same-len': 384, 'shorter': 84, 'longer': 128} |
| 2.8.1 | 682 | 305 (45%) | 0 | broad 55, length-drift 53, reg-rename 49, reorder-only 44 | {'same-len': 246, 'longer': 60, 'shorter': 71} |
| 2.95.2-G0 | 358 | 181 (51%) | 0 | reorder-only 44, broad 37, reg-rename 31, code-motion 12 | {'same-len': 132, 'shorter': 25, 'longer': 20} |
| 2.6.3-G0 | 321 | 170 (53%) | 0 | reorder-only 50, broad 18, addressing 14, reg-rename 13 | {'longer': 17, 'same-len': 117, 'shorter': 17} |
| 2.8.0-G0 | 258 | 130 (50%) | 0 | reorder-only 32, broad 22, reg-rename 22, addressing 11 | {'same-len': 96, 'shorter': 20, 'longer': 12} |
| 2.91.66-G0 | 127 | 69 (54%) | 0 | reg-rename 18, broad 10, code-motion 7, reorder-only 5 | {'same-len': 40, 'shorter': 7, 'longer': 11} |
| 2.6.3 | 10 | 4 (40%) | 0 | length-drift 4, code-motion 1, slus-diff 1 | {'longer': 1, 'same-len': 1, 'shorter': 4} |
| 2.91.66 | 3 | 1 (33%) | 0 | code-motion 1, length-drift 1 | {'same-len': 1, 'shorter': 1} |


### by context

| key | sites | dead (erasable) | build-fail | breakage classes when kept | length when kept |
|---|---:|---:|---:|---|---|
| plain | 19924 | 9573 (48%) | 16 | broad 1987, reorder-only 1935, reg-rename 1425, code-motion 916 | {'shorter': 1568, 'same-len': 7128, 'longer': 1639} |
| before-call | 1065 | 217 (20%) | 0 | delay-slot 308, length-drift 182, slot-rotation 68, broad 65 | {'shorter': 315, 'longer': 58, 'same-len': 475} |
| after-call | 629 | 309 (49%) | 0 | reg-rename 55, reorder-only 50, broad 49, addressing 37 | {'same-len': 230, 'longer': 47, 'shorter': 43} |
| before-return | 347 | 177 (51%) | 1 | reorder-only 40, broad 37, block-order 18, length-drift 17 | {'shorter': 34, 'same-len': 123, 'longer': 12} |
| after-label | 158 | 77 (49%) | 1 | block-order 19, broad 15, slot-rotation 12, reorder-only 9 | {'shorter': 23, 'longer': 18, 'same-len': 39} |
| before-call before-return | 78 | 2 (3%) | 0 | delay-slot 41, length-drift 13, broad 9, slot-rotation 6 | {'shorter': 24, 'same-len': 51, 'longer': 1} |
| after-call before-call | 69 | 27 (39%) | 0 | delay-slot 7, reorder-only 7, length-drift 6, hold-set 5 | {'shorter': 12, 'longer': 9, 'same-len': 21} |
| after-call before-return | 58 | 25 (43%) | 3 | delay-slot 7, length-drift 6, code-motion 3, dead-code-retention 3 | {'longer': 1, 'same-len': 15, 'shorter': 14} |
| in-#define | 50 | 11 (22%) | 1 | const-remat 14, li-expansion 7, broad 4, hold-set 3 | {'same-len': 24, 'longer': 9, 'shorter': 5} |
| after-loop-head | 47 | 23 (49%) | 0 | reg-rename 5, broad 4, length-drift 3, reorder-only 3 | {'same-len': 13, 'longer': 9, 'shorter': 2} |
| before-return after-label | 41 | 17 (41%) | 0 | block-order 7, broad 5, polarity 5, hold-set 3 | {'same-len': 17, 'longer': 5, 'shorter': 2} |
| after-call after-loop-head | 11 | 2 (18%) | 0 | const-remat 2, block-order 2, reorder-only 1, hold-set 1 | {'same-len': 5, 'shorter': 4} |


### macro x context (top)

| key | sites | dead (erasable) | build-fail | breakage classes when kept | length when kept |
|---|---:|---:|---:|---|---|
| ASM_REG plain | 11223 | 5686 (51%) | 1 | broad 1258, reg-rename 1175, reorder-only 693, addressing 437 | {'shorter': 376, 'same-len': 4232, 'longer': 928} |
| ASM_KEEP plain | 5276 | 2574 (49%) | 16 | reorder-only 631, broad 455, length-drift 304, code-motion 287 | {'same-len': 1561, 'shorter': 676, 'longer': 449} |
| ASM_KEEP_NV plain | 1620 | 755 (47%) | 0 | reorder-only 257, broad 175, length-drift 103, code-motion 67 | {'longer': 135, 'shorter': 151, 'same-len': 579} |
| ASM_SCHED_BARRIER plain | 924 | 270 (29%) | 0 | reorder-only 207, block-order 120, code-motion 87, length-drift 77 | {'shorter': 194, 'same-len': 380, 'longer': 80} |
| ASM_TAILSLOT_PIN  before-call | 384 | 0 (0%) | 0 | delay-slot 194, length-drift 116, slot-rotation 40, broad 13 | {'same-len': 210, 'shorter': 162, 'longer': 12} |
| ASM_REG after-call | 377 | 170 (45%) | 0 | reg-rename 41, broad 38, addressing 30, hold-set 17 | {'same-len': 153, 'longer': 30, 'shorter': 24} |
| ASM_KEEP  before-call | 305 | 135 (44%) | 0 | block-order 34, delay-slot 30, broad 24, length-drift 20 | {'shorter': 67, 'longer': 24, 'same-len': 79} |
| ASM_KEEP  before-return | 284 | 165 (58%) | 1 | reorder-only 34, broad 31, code-motion 12, length-drift 11 | {'shorter': 19, 'longer': 10, 'same-len': 89} |
| ASM_USE plain | 214 | 95 (44%) | 0 | reorder-only 27, broad 20, block-order 15, code-motion 13 | {'shorter': 35, 'same-len': 70, 'longer': 14} |
| ASM_USE_NV plain | 191 | 78 (41%) | 0 | reorder-only 22, length-drift 20, broad 19, block-order 15 | {'same-len': 67, 'shorter': 32, 'longer': 14} |
| ASM_KEEP after-call | 164 | 99 (60%) | 0 | reorder-only 26, reg-rename 8, addressing 6, code-motion 5 | {'same-len': 46, 'shorter': 12, 'longer': 7} |
| ASM_MEM_BARRIER plain | 145 | 36 (25%) | 0 | length-drift 33, reorder-only 16, block-order 16, code-motion 13 | {'shorter': 54, 'same-len': 43, 'longer': 12} |
| ASM_KEEP_DEP_NV plain | 131 | 39 (30%) | 0 | reorder-only 35, slus-diff 19, length-drift 13, broad 7 | {'same-len': 68, 'longer': 9, 'shorter': 15} |
| ASM_CLOBBER plain | 119 | 32 (27%) | 1 | reg-rename 21, block-order 16, reorder-only 11, length-drift 10 | {'shorter': 27, 'same-len': 47, 'longer': 12} |
| ASM_TAILSLOT_PIN_TIED  before-call | 102 | 0 (0%) | 0 | delay-slot 46, length-drift 33, slot-rotation 11, hold-set 4 | {'shorter': 51, 'same-len': 48, 'longer': 3} |
| ASM_SET plain | 74 | 32 (43%) | 0 | reorder-only 9, code-motion 9, reg-rename 9, broad 4 | {'same-len': 33, 'shorter': 5, 'longer': 4} |
| ASM_KEEP_NV  before-call | 69 | 33 (48%) | 0 | reorder-only 14, broad 11, reg-rename 4, li-expansion 2 | {'shorter': 3, 'same-len': 26, 'longer': 7} |
| ASM_USE2 plain | 64 | 34 (53%) | 0 | reorder-only 9, broad 5, code-motion 4, const-remat 3 | {'same-len': 23, 'shorter': 5, 'longer': 2} |
| ASM_USE2_NV plain | 55 | 17 (31%) | 0 | broad 11, hold-set 6, reorder-only 4, reg-rename 4 | {'same-len': 32, 'longer': 2, 'shorter': 4} |
| ASM_SCHED_BARRIER  before-call | 49 | 16 (33%) | 0 | code-motion 10, block-order 6, reorder-only 6, length-drift 6 | {'same-len': 23, 'longer': 1, 'shorter': 9} |
| ASM_REG  before-call | 43 | 20 (47%) | 0 | reg-rename 10, broad 3, hold-set 2, reorder-only 2 | {'same-len': 20, 'longer': 3} |
| ASM_SCHED_BARRIER  before-return | 41 | 8 (20%) | 0 | block-order 13, reorder-only 5, polarity 5, length-drift 3 | {'same-len': 20, 'shorter': 8, 'longer': 5} |
| ASM_TAILSLOT_PIN  before-call before-return | 41 | 0 (0%) | 0 | delay-slot 19, length-drift 9, broad 8, slot-rotation 5 | {'same-len': 28, 'shorter': 13} |
| ASM_SCHED_BARRIER after-call | 39 | 19 (49%) | 0 | reorder-only 10, code-motion 4, delay-slot 2, length-drift 2 | {'shorter': 3, 'same-len': 14, 'longer': 3} |
| ASM_PAGEBASE_PIN  before-call | 39 | 0 (0%) | 0 | delay-slot 39 | {'same-len': 39} |
| ASM_KEEP_NV after-call | 35 | 13 (37%) | 0 | broad 5, length-drift 4, code-motion 3, const-remat 2 | {'longer': 6, 'shorter': 5, 'same-len': 11} |
| ASM_KEEP4 plain | 31 | 17 (55%) | 0 | length-drift 6, broad 2, code-motion 1, reorder-only 1 | {'shorter': 8, 'same-len': 4, 'longer': 2} |
| ASM_KEEP after-call before-return | 30 | 15 (50%) | 3 | length-drift 5, block-order 2, code-motion 1, delay-slot 1 | {'longer': 1, 'same-len': 3, 'shorter': 8} |
| ASM_KEEP after-call before-call | 28 | 13 (46%) | 0 | length-drift 5, hold-set 3, reorder-only 2, block-order 1 | {'shorter': 7, 'longer': 4, 'same-len': 4} |
| ASM_UNDEF plain | 26 | 9 (35%) | 0 | block-order 4, length-drift 3, reg-rename 3, extent-prefix 1 | {'longer': 6, 'same-len': 7, 'shorter': 4} |
| ASM_KEEP4_NV plain | 24 | 5 (21%) | 0 | reorder-only 12, code-motion 3, hold-set 2, reg-rename 1 | {'same-len': 17, 'shorter': 1, 'longer': 1} |
| ASM_TAILSLOT_PIN plain | 19 | 0 (0%) | 0 | delay-slot 14, slot-rotation 2, broad 1, length-drift 1 | {'same-len': 15, 'shorter': 2, 'longer': 2} |
| ASM_KEEP_NV  before-return | 18 | 15 (83%) | 0 | broad 1, reorder-only 1, length-drift 1 | {'same-len': 2, 'shorter': 1} |
| ASM_TAILSLOT_PIN_TIED  before-call before-return | 17 | 0 (0%) | 0 | delay-slot 12, length-drift 3, const-remat 1, slot-rotation 1 | {'shorter': 5, 'same-len': 12} |
| ASM_USE  before-call | 17 | 6 (35%) | 0 | block-order 5, slot-rotation 3, hold-set 1, reorder-only 1 | {'shorter': 10, 'same-len': 1} |
| ASM_USE  before-return | 16 | 4 (25%) | 0 | block-order 2, hold-set 2, broad 2, delay-slot 1 | {'same-len': 8, 'shorter': 2, 'longer': 2} |
| ASM_SCHED_BARRIER after-call before-return | 16 | 6 (38%) | 0 | delay-slot 6, dead-code-retention 2, code-motion 1, polarity 1 | {'same-len': 7, 'shorter': 3} |


### by function size

| key | sites | dead (erasable) | build-fail | breakage classes when kept | length when kept |
|---|---:|---:|---:|---|---|
| <=2 KB | 12744 | 5904 (46%) | 2 | broad 1330, reorder-only 1171, reg-rename 854, length-drift 587 | {'same-len': 4714, 'shorter': 1174, 'longer': 950} |
| <=512 B | 6701 | 3291 (49%) | 12 | reorder-only 720, broad 569, reg-rename 396, length-drift 334 | {'shorter': 532, 'same-len': 2307, 'longer': 559} |
| >2 KB | 2298 | 969 (42%) | 0 | broad 225, reg-rename 199, reorder-only 173, length-drift 141 | {'longer': 190, 'same-len': 890, 'shorter': 249} |
| <=128 B | 762 | 310 (41%) | 8 | length-drift 73, reg-rename 72, broad 56, code-motion 45 | {'same-len': 242, 'shorter': 93, 'longer': 109} |


### by pins in the function

| key | sites | dead (erasable) | build-fail | breakage classes when kept | length when kept |
|---|---:|---:|---:|---|---|
| >25 | 9231 | 4499 (49%) | 1 | broad 999, reorder-only 881, reg-rename 625, code-motion 411 | {'same-len': 3279, 'longer': 734, 'shorter': 718} |
| 11-25 | 7732 | 3749 (48%) | 1 | reorder-only 712, broad 680, reg-rename 481, length-drift 375 | {'same-len': 2716, 'shorter': 656, 'longer': 610} |
| 6-10 | 3270 | 1492 (46%) | 7 | reorder-only 335, broad 296, reg-rename 181, length-drift 171 | {'same-len': 1201, 'longer': 228, 'shorter': 342} |
| 3-5 | 1479 | 549 (37%) | 9 | reg-rename 139, broad 133, reorder-only 127, length-drift 118 | {'same-len': 577, 'shorter': 194, 'longer': 150} |
| 1-2 | 793 | 185 (23%) | 4 | reg-rename 95, length-drift 94, broad 72, reorder-only 54 | {'same-len': 380, 'shorter': 138, 'longer': 86} |


### Breakage classes over all kept pins

| class | kept sites | share | what it means | mechanical alternative to try |
|---|---:|---:|---|---|
| broad | 2180 | 18% | many differences at once | not mechanical: the pin is load-bearing for the whole shape |
| reorder-only | 2109 | 18% | same instructions, different order (scheduler) | statement reorder in source; split/join expressions; barrier only if needed |
| reg-rename | 1521 | 13% | same instructions, different register colouring | declaration-order / first-use permutation (bounded search); merge two temps into one |
| length-drift | 1135 | 9% | different instruction count (extra/missing move, nop) | usually a copy that must be coalesced: reuse the variable; agent tier |
| code-motion | 988 | 8% | a statement moved across a call/branch | re-place the statement in source order; a dependency through a local |
| block-order | 736 | 6% | basic blocks laid out in a different order | goto/if polarity flip; agent tier |
| addressing | 677 | 6% | address computed differently (%hi/%lo vs gp, base+offset) | extern declaration shape (array vs scalar) — a declaration transform |
| slot-rotation | 562 | 5% | branch/jump delay-slot fill differs | reorder the statement before the branch; a plain temp instead of a pin |
| delay-slot | 494 | 4% | the instruction in a branch/jump delay slot differs | a temp that is dead after the branch; usually the TAILSLOT pin family — assembler-shaped, keep documented |
| const-remat | 449 | 4% | constant re-materialised vs kept in a register | hoist the constant into a named local used twice; volatile-free |
| hold-set | 400 | 3% | different callee-saved set / frame layout | reduce live ranges (scope a temp), or accept a documented pin |
| slus-diff | 302 | 3% |  |  |
| li-expansion | 266 | 2% | immediate load expanded differently (lui/addiu vs li) | write the constant in the retail split form; a named local |
| dead-code-retention | 154 | 1% | retail keeps a computation the compiler now drops | a volatile-free use of the value (assign to a local that is passed on) |
| polarity | 35 | 0% | branch condition inverted | swap if/else arms or invert the comparison |
| extent-prefix | 1 | 0% |  |  |
