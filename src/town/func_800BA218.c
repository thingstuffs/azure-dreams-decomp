/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

extern u16 *D_800D1868[4];

void func_800B7978(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    register s16 var_a0;
    register s16 var_t1;
    u16 *var_a2;
    u16 temp_t3;
    u16 temp_t4;
    u16 temp_v1;
    u16 temp_v0_3;
    u8 *base;
    u8 *address;
    s32 index;

    index = arg2 << 0x10;
    base = (u8 *)D_800D1868;
    ASM_KEEP(base);   /* MATCH pin: retail schedule: same instructions, different order without it */
    index >>= 0xE;
    address = (u8 *)index;
    address = (u8 *)((s32)address + (s32)base);
    var_a2 = *(u16 **)address;
    var_t1 = 0;
    temp_t4 = *var_a2++;
    temp_t3 = *var_a2++;
    temp_v1 = *var_a2++;
    temp_v0_3 = *var_a2++;
    arg0 -= temp_v1;
    arg1 -= temp_v0_3;
    while ((var_t1 << 0x10) < (temp_t3 << 0x10)) {
        var_a0 = 0;
        while (var_a0 < (s16)temp_t4) {
            temp_v1 = *var_a2;
            if (temp_v1 != 0) {
                ((u16 *)arg3)[((var_t1 + (s16)arg1) << 7) + var_a0 + (s16)arg0] = temp_v1;
            }
            var_a2++;
            var_a0++;
        }
        var_t1++;
    }
}
