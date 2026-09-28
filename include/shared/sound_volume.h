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
 * Declared unsized on purpose: retail never addresses it $gp-relative, and the 2.7.2-cdk -G8 rows
 * (func_80053E20, func_8005560C, ...) put a declaration of <= 8 bytes in .sbss/$gp (measured: 37 / 74 words off),
 * so the original declaration those TUs saw was > 8 bytes or unsized; `short [8]` (m2c's guess) would claim the
 * separate table D_80084810 that follows (reached only from its own base, by func_800550E8). */
extern short volumeScale[];

#endif
