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

/* Creates an effect for the active entity or displays its status message. */
s32 func_800CBF88(s32 entity)
{
    void *effect;
    s32 status;
    register s32 effect_id;
    register s16 effect_id_half;
    register u16 *effect_counts;

    if (entity == D_800E3D7C) {
        if (func_8003FA44(1) == 0) {
            return 0;
        }
        status = func_80042900(entity, 0x1C);
        if ((status << 0x10) == 0) {
            if ((func_800A48F0(entity, 0x1C, 0x10) << 0x10) >= 0) {
                effect = func_8003FC64(2);
                effect_id = 0x10;
                ASM_KEEP(effect_id);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                *(void **)((u8 *)effect + 0x10) = &D_800CBDB4;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                effect_id_half = effect_id;
                ASM_KEEP(effect_id_half);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                *(s16 *)((u8 *)effect + 0x24) = effect_id_half;
                effect_counts = (u16 *)D_80083460;
                effect_counts[5] = (u16)(effect_counts[5] + 1);
                func_800419EC(effect_id, 8);
                func_800A56E0(0x818);
                return 1;
            }
        } else {
            func_800997FC(&D_800E1B5D);
        }
    }
    return 1;
}
