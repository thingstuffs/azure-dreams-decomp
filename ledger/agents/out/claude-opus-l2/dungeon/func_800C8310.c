#include "common.h"

extern u8 D_800E3D40[];
extern s32 D_80083460[3];
extern s32 func_80042900(void *, s32);
extern s32 func_8003FA44(s32);
extern void *func_8003FC64(s32);
extern void func_800C5E5C(s32, s32, s16, void *, s32);
extern s32 func_800A56E0(s32);
extern s32 func_800A6508(void);
extern s32 func_800A6D30(void);
extern s32 func_800CD994(void *, s32);
extern u8 D_800CD910[];
extern u8 D_800DF820[];

/* Step trigger: stop when all four 0x2C slots are taken, then roll the object's 0x3 chance and either spawn the 0x613 effect object over the owning tile (returning -1) or give the fallback cue. */
s32 func_800CDA70(void *object) {
    s16 index;
    s32 seed;
    s32 result;
    void *entry;
    void *effect;

    result = 1;
    if ((func_80042900(object, 0xA) << 0x10) == 0) {
        index = 0;
loop_2:
        if (*(s8 *)((u8 *)object + ((index << 0x10) >> 0xF) + 0x2C) != 0) {
            index += 1;
            if (index < 4) {
                goto loop_2;
            }
        }
        if (index >= 4) goto done;
            if (*D_800E3D40 == 0) {
                seed = func_800A6D30() & 0xFFFF;
                if (*(u8 *)((u8 *)object + 3) != 0) {
                    index = seed % *(u8 *)((u8 *)object + 3);
                } else {
                    index = 0;
                }
            } else {
                index = 0;
            }
            if (index < 0x40) {
                entry = *(void **)((u8 *)object - 0x14);
                if (*(u16 *)((u8 *)entry + 0x14) & 0x8000) {
                    func_800CD994(object, 0x10);
                    return -1;
                }
                result = 0;
                if (func_8003FA44(2) != 0) {
                    effect = func_8003FC64(2);
                    *(u8 **)((u8 *)effect + 0x10) = D_800CD910;
                    *(void **)((u8 *)effect + 0x20) = object;
                    *(s16 *)((u8 *)effect + 0x26) = 0xC;
                    func_800C5E5C(
                        ((*(u8 *)((u8 *)entry + 0x24)) << 6) | 0x20,
                        ((*(u8 *)((u8 *)entry + 0x25)) << 6) | 0x20,
                        *(s16 *)((u8 *)object + 0x88), D_800DF820, 0);
                    func_800A56E0(0x613);
                    {
                        u8 *counter_base = (u8 *)D_80083460;
                        (*(u16 *)(counter_base + 0xA))++;
                    }
                    return -1;
                }
                return result;
            }
        if (*(u8 *)((u8 *)object + 0x13) == 0) {
            func_800A6508();
        }
done:
        return result;
    }
    return result;
}
