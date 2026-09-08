#include "common.h"

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

/* Updates object flags and display offset from its linked sub-object. */
void func_7FDD1BE8(S_7FDD1BE8 *object)
{
    S_7FDD1BE8_sub *sub_object = object->unk04;
    u16 *prior_flags = (u16 *)((u8 *)object - 2);

    if (sub_object->unk20 == 4) {
        object->unk16 &= 0xFFFD;
    }
    if (object->unk00 == 0) {
        object->unkE = (sub_object->unk24 * 0x10) + 0xA0;
        if (sub_object->unk26 & 1) {
            *prior_flags |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}
