#include "common.h"

extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern s32 func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern s32 func_80099844(void *, void *);
extern s32 func_800A48F0(void *, s32, s32);
extern void func_800A5720(s32);
extern s32 func_800A6D30(void);
extern s32 func_800C8500(void *);
extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern s32 D_8008942C[];
extern s32 D_800E196F[];
extern s32 D_800E1987[];
extern s32 D_800E1996[];
extern s32 D_800E19AA[];

/* Toggle the 0xB/0xC status pair between attacker and target: roll the attacker's 0x3 chance plus its 0x11 bonus against 0x30, apply or clear the status on the target, and report whether the attempt did not fail. */
u32 func_800C857C(void *attacker, void *target) {
    s32 roll;
    s32 status;
    s32 shifted;
    s32 chance;
    s32 base_chance;

    status = -1;
    if (func_800C8500(target) != 0) {
        if (*(s32 *)((s8 *)target + 0x14) & 0x4000) {
            func_80099844(target, &D_800E196F);
        }
        return 0;
    }
    roll = func_800A6D30() & 0xFFFF;
    base_chance = *(u8 *)((s8 *)attacker + 0x11) >> 2;
    if (*(u8 *)((s8 *)attacker + 3) != 0) {
        chance = roll % *(u8 *)((s8 *)attacker + 3) + base_chance;
    } else {
        chance = base_chance;
    }
    if (chance >= 0x30) {
        if (*(s32 *)((s8 *)attacker + 0x1C) & 0x2000) {
            if (!(*(s32 *)((s8 *)target + 0x1C) & 0x2000)) {
                if ((func_80042900(target, 0xC) << 0x10) != 0) {
                    func_80042B68(target, 0xC);
                    status = 0;
                    goto block_success;
                }
                status = func_800A48F0(target, 0xB, 0x10);
                if ((status << 0x10) < 0) {
                    goto block_error;
                }
                {
                    s32 session = func_800990FC();
                    void *effect;
                    register s32 handle ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    effect = &D_800E1987;
                    ASM_KEEP_NV(effect);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    handle = session;
                    attacker = handle;
                    func_80099290(func_80099194(&D_8008942C, func_80099734(target, func_80099194(effect, handle))));
                    func_800A5720(attacker);
                }
                goto block_success;
            }
        } else if (*(s32 *)((s8 *)target + 0x1C) & 0x2000) {
            if ((func_80042900(target, 0xB) << 0x10) != 0) {
                func_80042B68(target, 0xB);
                status = 0;
                goto block_success;
            }
            status = func_800A48F0(target, 0xC, 0x10);
            if ((status << 0x10) < 0) {
                goto block_error;
            }
            func_80099844(target, &D_800E1996);
        }
    }
block_success:
    shifted = status << 0x10;
    if (shifted < 0) {
block_error:
        if (*(s32 *)((s8 *)target + 0x14) & 0x4000) {
            func_80099844(target, &D_800E19AA);
        }
        shifted = status << 0x10;
    }
    shifted = status << 0x10;
    return (u32) ~(shifted >> 0x10) >> 0x1F;
}
