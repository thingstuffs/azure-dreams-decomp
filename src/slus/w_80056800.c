#include "common.h"

/* manual g1 strike 2: order the negative-direction compare like retail */
#include "common.h"

typedef struct S_80056800_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x28];
    s32 unk_34;
    s16 unk_38;
    s16 unk_3A;
    u8 pad_3C[0x4];
    s16 unk_40;
} S_80056800_0;   /* arg0 in func_80056800 */



void func_80056800(S_80056800_0 *arg0) {
    s32 diff;
    s32 neg_limit;

    if (arg0->unk_08 != 0) {
        if (arg0->unk_34 != 0) {
            if ((arg0->unk_3A + arg0->unk_38) < arg0->unk_40) {
                arg0->unk_3A = (u16)arg0->unk_3A + (u16)arg0->unk_38;
                return;
            }
            arg0->unk_34 = 0;
            arg0->unk_3A = (u16)arg0->unk_40;
            return;
        }

        diff = arg0->unk_3A - arg0->unk_38;
        neg_limit = -arg0->unk_40;
        if (neg_limit < diff) {
            arg0->unk_3A = (u16)arg0->unk_3A - (u16)arg0->unk_38;
            return;
        }
        arg0->unk_34 = 1;
        arg0->unk_3A = -((s16)(u16)arg0->unk_40);
        return;
    }
    arg0->unk_3A = 0;
}
