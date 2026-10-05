## One-trip `do { } while (0)` blocks are not neutral (round 85; r85_opus_g1 800A8714 7->4, r85_opus_g2 81904990)
A `do {...} while (0)` (inline or as a macro body) emits loop notes: global.c weights every ref inside it as loop depth
2 (a parameter used in a STEPVEC-style macro got refs 132 / priority 3534 instead of 116 / 2662 - the wrong callee-saved
order the pins then faked), calls.c treats it as a loop for argument pre-copies, and sched1 treats its edges as region
barriers. 38 pinned rows (142 pins) still carry one: unwrap it to `{ }` (or delete it) TOGETHER with erasing the pins
around it and using parameters directly - alone, either move usually fails (both are needed on 800A8714). Some are
load-bearing fences (8095563C: unwrapping one block alone is 2 off): then find what retail's order really came from.
Calibration (r85_opus_ot2, 7 rows): most remaining one-trip blocks are LOAD-BEARING barriers (unwrapping alone is not
exact on 5 of 7): they stand for a cse block end (cse.c 8102 ends at the loop note - the copy-head rule), a MEM_IN_STRUCT
dependence (spell the store as a struct field), or a sched1 order (birthing boost / single-set locals). Replace the
block with the C shape it stands for, not with nothing.

Loop form decides delay slots (r85_opus_p3): if a fence sits near the last test of a `do { ... i++; if (i >= N) break; } while (1)` body, try a `for (; i < N; i++)` loop with the entry zero written once at the loop head. Only the for form puts NOTE_INSN_LOOP_VTOP right after the beq's target label. cdk reorg.c mostly_true_jump (1403-1411) then predicts the jump taken, and the delay slot takes the increment from the target. Check sibling rows for a for-loop shape. Exact on 810ADDF4.

## Round 93: what pin-free one-trips held, and the natural shape that replaced them (r93_sonnet_ot3-ot10, ~37 blocks)
Erase the block alone first; ~1 in 3 held nothing (plain unwrap) or only a mis-structure (rewrite the wrapped
conditional / else-return as the natural while/if). Otherwise, by what the block held:
- a parameter/prologue copy -> the parameter with its REAL type/width (s16 5th stack arg, `u8 *dst`, typed struct
  pointer) used directly, copy deleted (80094218, 8028AC34, 80A9E9D0, 800BF754, 8181B1A0)
- a store order -> store each field right after its computation / compound-assign then read fresh / RMW then read back /
  reorder the store GROUPS (80A9E980, 813301AC, 80D90ABC, 800D25D0, 8180DE3C, 8186898C)
- a store after an if/else join -> the store in both arms (80FDC628)
- a cse block end -> fresh s32 for the re-read variable (808CB5C8)
- a global/page-pointer copy -> the global or the declared array element directly (`dungeonStatus.unk_0A--`,
  `D_80175D58[1]`) (809A2650, 80D3EBDC, 8133896C)
- a derived pointer -> compute it inside the null test that guards its use (80013868, 8181B1A0)
- an init before a pointer walk / rotated loop -> counted `for` with ONE walker or an index (8008D588, 800D2160,
  8000F160, 818F34E4)
- an init order / const-remat -> swap the inits (zero-init first) (w_8004A170, 8180DA84)
- a cursor-step order -> step right after the read (`x = *cur++`) (8096DC50)
Did NOT yield (note and move on): pure loop-weight register-priority blocks (the block's +loop-depth refs decide a
callee-saved order) and bare sched1/sched2 region barriers with no memory dependence (store vs disjoint load, prologue
region, call-result sext).
