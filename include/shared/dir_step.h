#ifndef SHARED_DIR_STEP_H
#define SHARED_DIR_STEP_H
/* Per-direction map-grid step tables, SLUS .data 0x8006CCD8 / 0x8006CCE8 (8 x s16 each, retail bytes):
 *     dirStepX = { 1, 1, 0, -1, -1, -1,  0,  1 }
 *     dirStepY = { 0, 1, 1,  1,  0, -1, -1, -1 }
 * Indexed by a direction 0..7 (an angle >> 9 with 0x1000 = one turn); direction 0 steps +x, 2 steps +y.
 * X pairs with the map-grid x byte of an entity (+0x24), Y with the grid y byte (+0x25) and with the
 * second ground axis of a world position (func_807B0110).  Every access in the 231 rows is a 16-bit
 * element (lh/lhu, or lbu of the low byte) at 2*d from its own table base.
 * The readable names are config/names.tsv aliases of D_8006CCD8 / D_8006CCE8: tools/build/ccproc.py
 * (gate, SLUS) and tools/gate/match.py (scorer) spell them back before the assembler, so every binary
 * links the same address (docs/TYPE_CONSOLIDATION.md). */
extern short dirStepX[8];   /* s16; plain C types so the header needs no include order */
extern short dirStepY[8];

#endif
