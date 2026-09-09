#include "common.h"

typedef struct S_80017EF0_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80017EF0_0;

typedef struct S_80017EF0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80017EF0_1;

extern s32 func_80017EA0();
extern s32 D_80019BB0;
extern s32 D_80019BB4;

s32 func_80017EF0(S_80017EF0_0 *arg0, s32 arg1) {
    if (D_80019BB0 != 3) {
        ((S_80017EF0_1 *)((arg1 * 0x10) + arg0->unk_10))->unk_08 =
            func_80017EA0(D_80019BB4);
        return 1;
    }
    return 0;
}
