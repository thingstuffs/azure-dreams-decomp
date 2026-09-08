#include "common.h"

extern s32 D_800E3D7C;
extern u8 D_80083460[12];
extern s32 D_800CBDB4;
extern u8 D_800E1B5D;

extern s32 func_8003FA44(s32 a0);
extern void *func_8003FC64(s32 a0);
extern s32 func_80042900(s32 a0, s32 a1);
extern s32 func_800A48F0(s32 a0, s32 a1, s32 a2);
extern void func_800419EC(s32 a0, s32 a1);
extern void func_800A56E0(s32 a0);
extern void func_800997FC(s32 a0);

s32 func_800CBF88(s32 arg0)
{
    void *v0;
    s32 result;
    u32 page;
    register s32 val;
    register s16 half;
    register u16 *counter;

    if (arg0 == D_800E3D7C) {
        if (func_8003FA44(1) == 0) {
            return 0;
        }
        result = func_80042900(arg0, 0x1C);
        page = 0x800E0000;
        if ((result << 0x10) == 0) {
            if ((func_800A48F0(arg0, 0x1C, 0x10) << 0x10) >= 0) {
                v0 = func_8003FC64(2);
                val = 0x10;
                ASM_KEEP(val);   /* MATCH pin: keeps a statement from moving across a call/branch */
                *(void **)((u8 *)v0 + 0x10) = &D_800CBDB4;
                ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
                half = val;
                ASM_KEEP(half);   /* MATCH pin: retail delay-slot fill depends on it */
                *(s16 *)((u8 *)v0 + 0x24) = half;
                ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
                counter = (u16 *)D_80083460;
                ASM_KEEP(counter);   /* MATCH pin: retail immediate-load split depends on it */
                counter[5] = (u16)(counter[5] + 1);
                func_800419EC(val, 8);
                func_800A56E0(0x818);
                return 1;
            }
        } else {
            ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
            func_800997FC(page + 0x1B5D);
        }
    }
    return 1;
}
