## One-trip `do { } while (0)` blocks are not neutral (round 85; r85_opus_g1 800A8714 7->4, r85_opus_g2 81904990)
A `do {...} while (0)` (inline or as a macro body) emits loop notes: global.c weights every ref inside it as loop depth
2 (a parameter used in a STEPVEC-style macro got refs 132 / priority 3534 instead of 116 / 2662 - the wrong callee-saved
order the pins then faked), calls.c treats it as a loop for argument pre-copies, and sched1 treats its edges as region
barriers. 38 pinned rows (142 pins) still carry one: unwrap it to `{ }` (or delete it) TOGETHER with erasing the pins
around it and using parameters directly - alone, either move usually fails (both are needed on 800A8714). Some are
load-bearing fences (8095563C: unwrapping one block alone is 2 off): then find what retail's order really came from.
