#include "common.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef void (*Callback)(void *, void *, void *, void *);

extern void func_800353F4();
extern void func_80042B68();
extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern void func_800A48F0();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s32 func_800BCB04();
extern void func_80169FC0() __attribute__((noreturn));
extern void func_8016A158() __attribute__((noreturn));
extern void func_8016A17C() __attribute__((noreturn));
extern void func_8016A1E8() __attribute__((noreturn));
extern void func_8016A280() __attribute__((noreturn));
extern void func_8016A298() __attribute__((noreturn));
extern void func_8016A318() __attribute__((noreturn));
extern void func_8016A348() __attribute__((noreturn));
extern void D_8016A36C();

extern u16 D_80013714;
extern s16 D_80083228;
extern u16 D_80083462;
extern s16 D_8008346A;
extern u8 *D_800E3D7C;
extern Callback D_80173B94[];
extern u8 D_80173DDC[];

void func_80169EC0(void *arg0, void *arg1, void *arg2)
{
    register void *owner ASM_REG("$17") = arg0;
    register void *motion ASM_REG("$20") = arg1;
    register void *data ASM_REG("$19") = arg2;
    register void *actor ASM_REG("$16") = owner;
    register s16 initialWork ASM_REG("$18");
    register s16 work ASM_REG("$18");
    register u32 initialRaw ASM_REG("$2");
    Callback callback;
    Callback callback2;
    s32 result;
    s32 flags;
    s32 i;
    u8 *scan;
    void *entry;
    void *record;
    u16 status;
    u16 height;
    s16 signedHeight;

    if (FIELD(owner, u8, 0xB1) == 0 &&
        !(D_80013714 & 1) && D_8008346A == 0) {
        FIELD(owner, u8, 0xB1) = 1;
        func_800353F4(D_80173DDC);
        FIELD(owner, u8, 0x6D) = 0;
        FIELD(owner, u8, 0x9B) = 0;
    }

    ASM_MEM_BARRIER();

    if (D_80013714 & 8) {
        i = 1;
        scan = D_800E3D7C + 4;
        do {
            entry = FIELD(scan, void *, 0xAC);
            if (entry != NULL) {
                record = FIELD(entry, void *, -0x14);
                FIELD(record, u16, 0x14) &= 0xFFBF;
            }
            i--;
            scan -= 4;
        } while (i >= 0);
    }

    if (FIELD(owner, u8, 0xB0) == 1) {
        register u32 page ASM_REG("$2");
        func_800A48F0(actor, 7, 1);
        page = 0x80080000;
        ASM_PAGEBASE_PIN(page);
        func_80169FC0();
        return;
    }

    func_80042B68(actor, 7);
    if (D_80083462 & 0x2000) {
        callback = FIELD(owner, Callback, 0x8C);
        if (callback == (Callback)D_8016A36C) {
            callback(owner, motion, data, actor);
            func_8016A348();
            return;
        } else {
            FIELD(actor, u8, 0x71) &= 0x7F;
            func_8016A348();
            return;
        }
    }

    {
        register void *callOwner ASM_REG("$4") = owner;
        register void *callMotion ASM_REG("$5") = motion;
        register void *callData ASM_REG("$6") = data;

        ASM_USE2_NV(callOwner, callMotion);
        ASM_USE_NV(callData);
        initialRaw = FIELD(actor, u8, 0x6D);
        initialRaw <<= 24;
        ASM_KEEP_NV(initialRaw);
        initialWork = (s32)initialRaw >> 24;
        if (func_800A9E70(callOwner, callMotion, callData, actor) != 0) {
            return;
        }
    }

    callback2 = FIELD(owner, Callback, 0x8C);
    if (callback2 != NULL) {
        callback2(owner, motion, data, actor);
    }
    D_80173B94[FIELD(owner, u8, 0x9A)](owner, motion, data, actor);
    if (initialWork != FIELD(actor, s8, 0x6D)) {
        func_800AA36C(owner, motion, data, actor);
    }

    status = FIELD(data, u16, 0x14);
    if (!(status & 0x8000)) {
        register s32 angleCalc ASM_REG("$2");
        u16 lowStatus;
        u16 lowCleared;
        angleCalc = D_80083228 + FIELD(actor, s16, 0x2A) + 0x100;
        work = (angleCalc >> 9) & 7;
        if (FIELD(owner, s16, 0x94) != work) {
            u8 *steps = FIELD(data, u8 *, 0x2C);
            if (steps != NULL) {
                func_80047738(data, steps[work], FIELD(data, s8, 4));
            }
            FIELD(owner, s16, 0x94) = work;
        }

        lowStatus = FIELD(data, u16, 0x14);
        lowCleared = lowStatus & 0xFFFE;
        FIELD(data, u16, 0x14) = lowCleared;
        if (!(FIELD(actor, s32, 0x1C) & 0x20)) {
            if (!(lowStatus & 0x40)) {
                func_800478B8(data);
                func_8016A158();
                return;
            }
        } else {
            FIELD(data, u16, 0x14) = lowCleared | 0x7000;
        }
        func_800A020C(FIELD(actor, s32, 0x1C), (u8 *)data + 0xC);
        func_8016A17C();
        return;
    }

    FIELD(data, u16, 0x14) = (status & 0x800) ?
                            (status & 0x8FFF) : (status | 0x7000);

    FIELD(motion, s32, 0) += FIELD(motion, s32, 0xC);
    FIELD(motion, s32, 4) += FIELD(motion, s32, 0x10);
    if (FIELD(owner, u16, 0x98) & 8) {
        FIELD(owner, u8, 0x9D) = 0;
        func_8016A1E8();
        return;
    }

    FIELD(motion, s32, 0x14) += FIELD(owner, s8, 0x9D) * 0x14000;
    FIELD(owner, u8, 0x9D)++;
    ASM_MEM_BARRIER();
    FIELD(owner, s32, 0x90) += FIELD(motion, s32, 0x14);

    if (FIELD(owner, u16, 0x98) & 4) {
        goto clear_movement_flag;
    }
    result = func_800BCB04(FIELD(motion, u16, 2), FIELD(motion, u16, 6),
                           (s16)(FIELD(actor, u16, 0x88) - 0x20));
    if ((s16)result >= 0x200) {
        goto clear_movement_flag;
    }
    signedHeight = FIELD(actor, s16, 0x88);
    height = FIELD(actor, u16, 0x88);
    if (FIELD(owner, s16, 0x92) + signedHeight < (s16)result) {
        FIELD(actor, s32, 0x1C) &= 0xF7FFFFFF;
        func_8016A298(height, result, signedHeight);
        return;
    }
    if ((s16)result >= signedHeight) {
        FIELD(owner, s32, 0x90) = 0;
        func_8016A280(height, result, signedHeight);
        return;
    }
    FIELD(owner, s16, 0x92) = result - height;
    FIELD(motion, s32, 0x14) = 0;
    FIELD(actor, s32, 0x1C) |= 0x08000000;
    FIELD(owner, u8, 0x9D) = 0;
    flags = FIELD(actor, s32, 0x1C);
    if (flags & 0x40000000) {
        FIELD(actor, s32, 0x1C) = flags & 0xBFFFFFFF;
        result = func_800BCB04((FIELD(data, u8, 0x24) << 6) | 0x20,
                               (FIELD(data, u8, 0x25) << 6) | 0x20,
                               (s16)(FIELD(actor, u16, 0x88) - 0x20));
        FIELD(owner, s16, 0x92) += FIELD(actor, u16, 0x88) - result;
        FIELD(actor, u16, 0x88) = result;
        func_8016A318();
        return;
    }
    goto finish;

clear_movement_flag:
    FIELD(actor, s32, 0x1C) &= 0xF7FFFFFF;

finish:
    FIELD(motion, s16, 0xA) = FIELD(owner, s8, 0xAA) +
                              (FIELD(actor, u16, 0x88) +
                               FIELD(owner, u16, 0x92));
    FIELD(data, u16, 0x14) |= 0x40;
    ASM_KEEP(owner);
    ASM_KEEP(motion);
    ASM_KEEP(data);
    ASM_KEEP(actor);
    ASM_KEEP(work);
}
