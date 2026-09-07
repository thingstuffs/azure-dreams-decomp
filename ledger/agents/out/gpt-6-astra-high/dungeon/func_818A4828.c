#include "common.h"

extern void func_800247D4(void);
extern void func_8002488C(void);
extern void func_800248D4(void);
extern void func_80024DF0(void);
extern void func_80024F30(void);
extern void func_80024FB0(void);
extern void func_80024FD8(void);
extern void func_800250E0(void);
extern void func_80025118(void);

extern s32 func_8009D218(void *, s32);
extern s32 func_800A6870(s32);
extern void func_800AD4D0(void *);
extern void func_800AD568(void *, s32);
extern void func_800B4C7C(s32, void *, s32, s32);

static void (*const callbacks[])(void) = {
    func_800247D4,
    0,
    func_8002488C,
    func_800248D4,
    func_80024DF0,
    func_80024F30,
    func_80024FB0,
    func_80024FD8,
    func_800250E0,
    func_80025118,
};

/* Applies a flag-adjusted stat increase to an eligible target and updates its state. */
void func_818A4828(void *target, s32 effect_param) {
    register s32 base_gain ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 stat_gain;

    if (func_8009D218(target, 1) == 0) {
        base_gain = func_800A6870(effect_param & 0xFF) + 4;
        stat_gain = base_gain;
        if (*(u8 *)((u8 *)target + 0x28) & 1) {
            stat_gain = base_gain + ((s32)(base_gain << 16) >> 17);
        }
        *(u16 *)((u8 *)target + 0x64) += stat_gain;
        func_800AD568(target, stat_gain);
        func_800B4C7C(0x8004, target, (s16)*(u16 *)((u8 *)target + 0x64), 1);
        func_800AD4D0(target);
    }
}

