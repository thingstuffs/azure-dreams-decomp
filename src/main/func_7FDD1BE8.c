#include "common.h"

/* Sets a "used"/flag bit on an object based on flags in a linked sub-object
 * (a1 = *(a0+4)), then (when a0's type field is 0) recomputes a display
 * offset field from a1's data and, if a1's flag bit 0 is set, sets the
 * 0x8000 "used" bit both on a 16-bit field 2 bytes before a0 and on the
 * global 32-bit flags word D_800814A0 (same global touched by func_8004F52C
 * / func_8004F558 / func_8004B530). */
extern int D_800814A0;

typedef struct {
    u8 pad20[0x20];
    s16 unk20;      /* offset 0x20: type/kind */
    u8 pad24[0x24 - 0x22];
    s16 unk24;      /* offset 0x24 */
    u16 unk26;      /* offset 0x26: flag bits */
} S_7FDD1BE8_sub;

typedef struct {
    s16 unk00;          /* offset 0x0 */
    u8 pad04[0x4 - 0x2];
    S_7FDD1BE8_sub *unk04; /* offset 0x4 */
    u8 padE[0xE - 0x8];
    s16 unkE;           /* offset 0xE */
    u8 pad16[0x16 - 0x10];
    u16 unk16;          /* offset 0x16 */
} S_7FDD1BE8;

void func_7FDD1BE8(S_7FDD1BE8 *arg0)
{
    S_7FDD1BE8_sub *a1 = arg0->unk04;
    u16 *flagsBefore = (u16 *)((u8 *)arg0 - 2);

    if (a1->unk20 == 4) {
        arg0->unk16 &= 0xFFFD;
    }
    if (arg0->unk00 == 0) {
        arg0->unkE = (a1->unk24 * 0x10) + 0xA0;
        if (a1->unk26 & 1) {
            *flagsBefore |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}
