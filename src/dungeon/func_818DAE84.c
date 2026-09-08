#include "common.h"

typedef struct S_818DAE84_0_pre {
    u16 unk_00;
} S_818DAE84_0_pre;   /* the 0x2 bytes before arg0 in func_818DAE84, addressed as arg0[-1] */

typedef struct S_818DAE84_0 {
    void * unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
    s16 unk_10;
} S_818DAE84_0;   /* arg0 in func_818DAE84 */

typedef struct S_818DAE84_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_818DAE84_1;   /* inner in func_818DAE84 */



extern s32 D_800814A0[];

/* Updates progress from a countdown and sets completion flags when it expires. */
void func_818DAE84(void *state) {
    s32 remaining;
    s16 next_remaining;
    s32 progress;
    S_818DAE84_1 *linked_object;

    linked_object = ((S_818DAE84_0 *)state)->unk_00;
    linked_object->unk_52 = (u16)(linked_object->unk_52 | 0x8000);

    progress = ((S_818DAE84_0 *)state)->unk_0C;
    if (progress < 0x50) {
        progress += 8;
    }

    remaining = ((S_818DAE84_0 *)state)->unk_10;
    ((S_818DAE84_0 *)state)->unk_0C = progress;
    if (remaining < 9) {
        ((S_818DAE84_0 *)state)->unk_0C = remaining * 8;
    }

    next_remaining = (u16)((S_818DAE84_0 *)state)->unk_10 - 1;
    ((S_818DAE84_0 *)state)->unk_10 = next_remaining;
    if ((next_remaining << 16) <= 0) {
        ((S_818DAE84_0_pre *)state)[-1].unk_00 = (u16)(((S_818DAE84_0_pre *)state)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
