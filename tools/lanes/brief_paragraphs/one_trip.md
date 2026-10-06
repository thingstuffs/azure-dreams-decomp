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

## Round 96 (r96_sonnet_ot1-ot4: 23 of 64 pin-free rows cleared) - shapes that were exact
- `do { cur += N; } while (0);` last in a pointer-walk do-while body -> plain `cur += N;` placed BEFORE the counter increment (800B8B44).
- one-trip before the first store of a small local pointer table -> brace initializer on the declaration `void *t[2] = { &A, &B };` (80470D24).
- one-trip + manual `if (x < 0) x = 0 - x;` -> `abs(...)` (`extern int abs(int);` as sibling rows declare it) (800A816C).
- one-trip around a pointer-walk step with a separate counter -> counted `for` with an indexed read of the table pointer (8001F720).
- early `return x` inside a one-trip followed by a tail -> if/else with the tail in the else and ONE return at the end (805D2FC4).
- `local = A; ...; local = B;` (a local reused for an unrelated second value) around a one-trip -> write B straight into its store as a compound op (8080BF18).
- `p[k] |= m` (ARRAY_REF = MEM_IN_STRUCT) then a global read/RMW, held by a one-trip -> `*(p + k) |= m` (plain deref is not in_struct, sched1 keeps the order) (80814E64).
- Never worked (measured, do not repeat): plain unwrap / statement permutations on pure loop-weight register-priority blocks; no-op masks (invented arithmetic - refused); structured spellings of goto loops that pass a constant argument to a call (loop.c hoists it: retail has no loop notes there).
- Tool note: run lab.py from the LANE ROOT (it stages relative to the current directory).
- (r96_sonnet_ot3/ot4) set of a local the sibling arms also use -> reuse the shared local; a callee-saved register swap on unwrap is a loop-weight REG_N_REFS effect: add the missing weighted ref NATURALLY (split nested call, real param type with a multiply, delete an early alias local); store in both arms; same-constant arms -> constant at the use; init at the loop head instead of before the loop + at the tail; junk argument to a (void) callee dropped (check the callee's definition and other callers). Plain unwrap: 0/18 on rows holding a sched1 region order or a reorg delay-slot fill.
