#include "common.h"

#include "common.h"

extern s32 func_80018174(s32, s32, s32, s32, s32);
extern void func_8004F884(void *);
extern u8 D_80071784[];

s32 func_8004FC98(void *arg0) {
    s32 temp_v0;
    s32 var_s0;
    u8 temp_v1;
    u8 *var_s1;
    u8 *table;
    u8 *entry;

    var_s0 = 0;
    if (*(s32 *)((u8 *)arg0 + 0x24) > 0) {
        table = D_80071784;
        var_s1 = arg0;
loop:
#ifdef NON_MATCHING
        entry = table + *(s32 *)((u8 *)arg0 + 0x30) * 3;
#else
        entry = (u8 *)((u32)(*(s32 *)((u8 *)arg0 + 0x30) * 3) + (u32)table);
#endif
        temp_v1 = entry[var_s0];
        temp_v0 = func_80018174(*(s32 *)(var_s1 + 0x10), var_s0, 0x18,
                               temp_v1 * 0xC - 0x40,
                               temp_v1 * 0x1E + 0x200);
        *(s32 *)(var_s1 + 4) = temp_v0;
        if (temp_v0 == 0) {
            return 0;
        }
        temp_v0 = *(s32 *)((u8 *)arg0 + 0x24);
        var_s0++;
        var_s1 += 4;
        if (var_s0 < temp_v0) {
            goto loop;
        }
    }

    *(s32 *)((u8 *)arg0 + 0x2C) = 1;
    *(s32 *)((u8 *)arg0 + 0x28) = 1;
    func_8004F884(arg0);
    return 1;
}
