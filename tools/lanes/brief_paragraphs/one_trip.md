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
