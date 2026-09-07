#include "common.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80173678_0 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
} S_80173678_0;   /* arg0 in func_80173678 */

typedef struct S_80173678_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
} S_80173678_1;   /* arg3 in func_80173678 */




extern void func_80047784();
extern s16 D_80083228[5];
extern u8 D_80175E9C[];
extern u8 D_80175EA4[];
extern u8 D_80175EAC[];

void func_80173678(S_80173678_0 *arg0, s32 arg1, Rec_D_80082E80 *arg2, S_80173678_1 *arg3) {
    s32 kind;
    u8 *data;
    u8 *old;

    arg0->unk_9A = 0x10;
    arg0->unk_9B = 0;
    kind = arg3->unk_48;
    if (kind == 0xE) {
        goto case_14;
    }
    if ((s32) kind < 0xF) {
        if (kind == 0xD) {
            goto case_13;
        }
        return;
    }
    if (kind == 0xF) {
        goto case_15;
    }
    return;

case_13:
    data = D_80175E9C;
    old = arg2->unk_2C.as_pu8;
    if (old == data) {
        return;
    }
    arg2->unk_2C.as_pu8 = data;
    func_80047784(arg2,
                  data[((D_80083228[0] + arg3->unk_2A + 0x100) >> 9) & 7],
                  0);
    return;
case_14:
    data = D_80175EA4;
    old = arg2->unk_2C.as_pu8;
    if (old == data) {
        return;
    }
    arg2->unk_2C.as_pu8 = data;
    func_80047784(arg2,
                  data[((D_80083228[0] + arg3->unk_2A + 0x100) >> 9) & 7],
                  0);
    return;
case_15:
    data = D_80175EAC;
    old = arg2->unk_2C.as_pu8;
    if (old == data) {
        return;
    }
    arg2->unk_2C.as_pu8 = data;
    func_80047784(arg2,
                  data[((D_80083228[0] + arg3->unk_2A + 0x100) >> 9) & 7],
                  0);
}
