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

void func_818DAE84(void *arg0) {
    s32 count;
    s16 next_count;
    s32 progress;
    S_818DAE84_1 *inner;

    inner = ((S_818DAE84_0 *)arg0)->unk_00;
    inner->unk_52 = (u16)(inner->unk_52 | 0x8000);

    progress = ((S_818DAE84_0 *)arg0)->unk_0C;
    if (progress < 0x50) {
        progress += 8;
    }

    count = ((S_818DAE84_0 *)arg0)->unk_10;
    ((S_818DAE84_0 *)arg0)->unk_0C = progress;
    if (count < 9) {
        ((S_818DAE84_0 *)arg0)->unk_0C = count * 8;
    }

    next_count = (u16)((S_818DAE84_0 *)arg0)->unk_10 - 1;
    ((S_818DAE84_0 *)arg0)->unk_10 = next_count;
    if ((next_count << 16) <= 0) {
        ((S_818DAE84_0_pre *)arg0)[-1].unk_00 = (u16)(((S_818DAE84_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
