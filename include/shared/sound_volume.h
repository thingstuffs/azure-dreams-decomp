#ifndef SHARED_SOUND_VOLUME_H
#define SHARED_SOUND_VOLUME_H

/* volumeScale (0x80084808, SLUS .bss; config/names.tsv spells it D_80084808 for the assembler): three Q15 volume
 * scale factors of the sound code (r78 phase 9, OPEN_ITEMS #17).  func_800559B4 (sound init) sets all three to
 * 0x7FFF; the setters func_80053E14 / func_80053DF0 / func_80053DCC (and func_80053E20 by selector 2 / 1 / 4) store
 * the option words at 0x80080A9C / 0x80080A98 / 0x80080A94 into [0] / [1] / [2] at boot and when the options change;
 * func_80053E90 reads them back by the same selector.  Each is used as `level * volumeScale[i] / 32767`:
 *   [0] func_8005560C: the gain it passes to func_8005B4D0 (starts voices for a program's tones)
 *   [1] func_800552C8: D_800848F8's level -> func_8005B27C (two 7-bit values for sequence entry D_800847D0.field22)
 *   [2] func_80054D64: D_80084858's level -> func_8005A56C (mode 0, value * 256)
 * Declared size: retail proves only that every TU saw MORE than 8 bytes here (r78 phase 9, measured):
 *   - <= 8 bytes (short[3] / short[4]) puts it in $gp small data at -G8: w_80053E20 37 words off, w_8005560C 74,
 *     and the whole SLUS image 88,120 words off with slus/code's stock 2.7.2 store macros;
 *   - UNSIZED also breaks slus/code (func_80053DCC / func_80053E14): with no `.extern` size the stock-2.7.2 store
 *     macro is expanded through $at with a nop where retail (and any size > 8) schedules the store into the jal
 *     delay slot - SLUS image 88,082 words off;
 *   - short[5] and short[8] both reproduce retail (image MATCH).
 * [8] is the size every declaration used before phase 9 (globals.h, the rows): the true extent is NOT known - it
 * may be a larger block that also holds the table D_80084810 (w_800550E8 reaches that from %hi(D_80084810), which a
 * field of one aggregate would also give), so do not read [8] as a claim that 0x80084810.. belongs to this array. */
extern short volumeScale[8];

#endif
