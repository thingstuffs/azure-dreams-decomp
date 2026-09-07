#include "common.h"

extern s32 func_80049004(s32 *a0, s32 a1, s32 a2);
extern s32 func_800491CC(s32 a0, void *a1, s32 a2);
extern s32 D_8002E5E8[];

s32 func_800AEF5C(void *arg0, s32 arg1) {
    s32 var_s1 = 0;
    s32 temp_v0 = func_80049004((s32 *)((s8 *)arg0 + 0xDC), arg1, 8);

    *(s32 *)((s8 *)arg0 + 0xD8) = temp_v0;
    if (temp_v0 != 0) {
        *(s32 *)((s8 *)arg0 + 0xBC) = D_8002E5E8[0];
        *(s32 *)((s8 *)arg0 + 0xC0) = D_8002E5E8[1];
        *(s32 *)((s8 *)arg0 + 0xC4) = D_8002E5E8[2];
        func_800491CC(temp_v0, (s8 *)arg0 + 0xBC, 0x1A);
        var_s1 = 1;
    }
    return var_s1;
}
