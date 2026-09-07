#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();
extern void func_8014D53C() __attribute__((noreturn));
extern void func_8014D5E4() __attribute__((noreturn));
extern void func_8014D74C() __attribute__((noreturn));
extern void func_8014D7E4() __attribute__((noreturn));
extern void func_8014D8D4() __attribute__((noreturn));
extern void func_8014D8D8() __attribute__((noreturn));
extern void func_8014D910() __attribute__((noreturn));

extern u8 D_8006CCF8[8];
extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_8014D9DC;
extern u8 D_80150634[8];
extern u8 D_80150644[8];
extern u8 D_80150654[8];
extern u8 D_8015065C[8];
extern u8 D_80150664[8];
extern u8 D_8015066C[8];
extern Callback D_801506A0[];

void func_8014D3A8(void *arg0, void *arg1, void *arg2)
{
    register void *base ASM_REG("$19") = arg0;
    register s16 old_state ASM_REG("$16");
    register u8 old_raw ASM_REG("$2");
    register void *call_arg0 ASM_REG("$4");
    register void *call_arg1 ASM_REG("$5");
    register void *call_arg2 ASM_REG("$6");
    register s32 motion_value ASM_REG("$4");
    register u32 motion_raw ASM_REG("$3");
    s16 index;
    s16 value;
    s32 flags;
    register s32 amount ASM_REG("$2");
    u16 initial_mode;
    u16 mode;

    if (D_80083462 & 0x2000) {
        register void *entry_self ASM_REG("$4") = arg0;
        Callback entry_callback;

        entry_callback = FIELD(arg0, Callback, 0x8C);
        if (entry_callback == (Callback)&D_8014D9DC) {
            ASM_KEEP(entry_self);
            entry_callback(entry_self, arg1, arg2, entry_self);
            return;
        }
        FIELD(arg0, u8, 0x71) &= 0x7F;
        return;
    }

    ASM_USE_NV(base);
    ASM_SET(base);
    call_arg0 = arg0;
    call_arg1 = arg1;
    call_arg2 = arg2;
    ASM_KEEP4(call_arg0, call_arg1, call_arg2, base);
    old_raw = FIELD(arg0, u8, 0x6D);
    ASM_KEEP(old_raw);
    old_state = (s8)old_raw;
    if (func_800A9E70(call_arg0, call_arg1, call_arg2, arg0) != 0) {
        return;
    }

    {
        Callback ordinary_callback = FIELD(arg0, Callback, 0x8C);

        if (ordinary_callback != 0) {
            ordinary_callback(arg0, arg1, arg2, arg0);
        }
    }
    D_801506A0[FIELD(arg0, u8, 0x9A)](arg0, arg1, arg2, arg0);
    {
        register s32 old_compare ASM_REG("$2");

        old_compare = (u32)(u16)old_state << 16;
        ASM_KEEP_NV(old_compare);
        old_compare >>= 16;
        if (old_compare != FIELD(arg0, s8, 0x6D)) {
            func_800AA36C(arg0, arg1, arg2, arg0);
        }
    }

    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);

    if (!(FIELD(arg0, s32, 0x1C) & 0x40000) &&
        !(FIELD(arg0, u16, 0x98) & 8)) {
        FIELD(arg1, s32, 0x14) += FIELD(arg0, s8, 0x9D) * 0x14000;
        FIELD(arg0, u8, 0x9D)++;
        func_8014D53C();
        return;
    }

    do { FIELD(arg0, u8, 0x9D) = 0; } while (0);
    FIELD(arg0, s32, 0x90) += FIELD(arg1, s32, 0x14);
    initial_mode = FIELD(arg2, u16, 0x14);

    if (!(initial_mode & 0x8000)) {
        ASM_KEEP(base);
        index = ((D_80083228 + FIELD(base, s16, 0x2A) + 0x100) >> 9) & 7;
        if (FIELD(arg0, s16, 0x94) != index) {
            func_80047738(arg2,
                *(u8 *)(FIELD(arg2, u8 *, 0x2C) + index),
                FIELD(arg2, s8, 4));
            FIELD(arg0, s16, 0x94) = index;
        }
        if (D_8006CCF8[index] != 0) {
            register u32 tail_value ASM_REG("$2");

            tail_value = FIELD(arg2, u16, 0x14) | 1;
            ASM_TAILSLOT_PIN(tail_value);
            func_8014D5E4();
            return;
        }

        FIELD(arg2, u16, 0x14) &= 0xFFFE;
        func_800A020C(FIELD(base, s32, 0x1C), (u8 *)arg2 + 0xC);
        if (!(FIELD(base, s32, 0x1C) & 0x20)) {
            if (!(FIELD(arg2, u16, 0x14) & 0x40)) {
                func_800478B8(arg2);
                goto clear_8000000;
            }
        } else {
            FIELD(arg2, u16, 0x14) |= 0x7000;
            FIELD(base, s32, 0x1C) &= 0xFFFBFFFF;
        }

clear_8000000:
        FIELD(base, s32, 0x1C) &= 0xF7FFFFFF;
        flags = FIELD(base, s32, 0x1C);
        if (flags & 0x40000) {
            mode = FIELD(arg2, u16, 0x14);
            if (!(mode & 0x40)) {
                u8 *kind = FIELD(arg2, u8 *, 0x2C);

                if (kind == D_80150634) {
                    if (FIELD(arg2, s8, 4) == 3 && (mode & 0x1000)) {
                        FIELD(arg0, s32, 0xAC) = 0x60000;
                        FIELD(arg0, s32, 0xB0) = (s32)0xFFFF3000;
                    }
                    FIELD(arg0, s32, 0xA4) += FIELD(arg0, s32, 0xAC);
                    FIELD(arg0, s32, 0xAC) += FIELD(arg0, s32, 0xB0);
                    if (FIELD(arg0, s32, 0xA4) <= 0) {
                        FIELD(arg0, s32, 0xA4) = 0;
                        func_8014D74C();
                        return;
                    }
                } else if (kind == D_80150644 || kind == D_8015066C) {
                    FIELD(arg0, s32, 0xA4) -= 0x40000;
                    if (FIELD(arg0, s32, 0xA4) <= 0) {
                        FIELD(arg0, s32, 0xA4) = 0;
                        func_8014D74C();
                        return;
                    }
                } else if (kind != D_80150654 && kind != D_8015065C &&
                           kind != D_80150664) {
                    FIELD(arg0, s32, 0xA4) = 0;
                }
            }

            amount = FIELD(arg0, u16, 0x98) & 8;
            if (amount == 0) {
                motion_value = FIELD(arg0, s16, 0x92);
                motion_raw = FIELD(arg0, u16, 0x92);
                if (amount < motion_value) {
                    amount = motion_raw - 8;
                    FIELD(arg0, s16, 0x92) = amount;
                    func_8014D910();
                    return;
                }
                goto adjust_positive;
            }
            goto finish_motion;
        }

        {
            register s32 tail_sum ASM_REG("$3");
            register u16 tail_mode ASM_REG("$4");

            amount = FIELD(arg0, s32, 0xA4);
            tail_sum = FIELD(arg0, s32, 0x90);
            tail_mode = FIELD(arg0, u16, 0x98);
            FIELD(arg0, s16, 0xB8) = 0;
            FIELD(arg0, s32, 0xA4) = 0;
            tail_sum += amount;
            ASM_USE_NV(tail_mode);
            ASM_TAILSLOT_PIN(tail_sum);
            func_8014D7E4();
            return;
        }
    }

    if (initial_mode & 0x800) {
        FIELD(arg2, u16, 0x14) = initial_mode & 0x8FFF;
    } else {
        FIELD(arg2, u16, 0x14) = initial_mode | 0x7000;
    }
    FIELD(base, s32, 0x1C) &= 0xF7FFFFFF;
    flags = FIELD(base, s32, 0x1C);

    if (!(flags & 0x40000)) {
        amount = FIELD(arg0, s32, 0xA4);
        FIELD(arg0, s16, 0xB8) = 0;
        FIELD(arg0, s32, 0xA4) = 0;
        FIELD(arg0, s32, 0x90) -= amount;
        if (!(FIELD(arg0, u16, 0x98) & 8)) {
            value = func_800BCB04(FIELD(arg1, u16, 2),
                                  FIELD(arg1, u16, 6),
                                  (s16)(FIELD(base, u16, 0x88) - 0x20)) -
                    FIELD(base, u16, 0x88);
            if (value < FIELD(arg0, s16, 0x92)) {
                FIELD(arg0, s16, 0x92) = value;
                FIELD(arg0, u8, 0x9D) = 0;
                FIELD(arg1, s32, 0x14) = 0;
                FIELD(base, s32, 0x1C) |= 0x08000000;
                func_8014D910();
                return;
            }
        }
        goto finish_motion;
    }

    if (!(FIELD(arg2, u16, 0x14) & 0x40)) {
        u8 *kind = FIELD(arg2, u8 *, 0x2C);

        if (kind == D_80150634) {
            FIELD(arg0, s32, 0xAC) = 0;
            func_8014D8D4();
            return;
        }
        if (kind == D_80150644 || kind == D_8015066C) {
            FIELD(arg0, s32, 0xA4) -= 0x40000;
            if (FIELD(arg0, s32, 0xA4) <= 0) {
                FIELD(arg0, s32, 0xA4) = 0;
                func_8014D8D8();
                return;
            }
        } else if (kind != D_80150654 && kind != D_8015065C &&
                   kind != D_80150664) {
            FIELD(arg0, s32, 0xA4) = 0;
        }
    }

    amount = FIELD(arg0, u16, 0x98) & 8;
    if (amount == 0) {
        motion_value = FIELD(arg0, s16, 0x92);
        motion_raw = FIELD(arg0, u16, 0x92);
        if (amount < motion_value) {
            amount = motion_raw - 8;
            goto store_adjustment;
        }
adjust_positive:
        amount = motion_value < -8;
        if (amount != 0) {
            amount = motion_raw + 8;
        } else {
            goto finish_motion;
        }
store_adjustment:
        FIELD(arg0, s16, 0x92) = amount;
    }
finish_motion:
    flags = FIELD(base, s32, 0x1C);
    if (flags & 0x40000000) {
        FIELD(base, s32, 0x1C) = flags & 0xBFFFFFFF;
        value = func_800BCB04((FIELD(arg2, u8, 0x24) << 6) | 0x20,
                              (FIELD(arg2, u8, 0x25) << 6) | 0x20,
                              (s16)(FIELD(base, u16, 0x88) - 0x20));
        if (value < 0x200) {
            FIELD(arg0, s16, 0x92) =
                (u16)FIELD(arg0, s16, 0x92) +
                (FIELD(base, u16, 0x88) - value);
            FIELD(base, u16, 0x88) = value;
        }
    }
    FIELD(arg1, s16, 0xA) = FIELD(base, u16, 0x88) +
                             (u16)FIELD(arg0, s16, 0x92) -
                             FIELD(arg0, u16, 0xA6);
    FIELD(arg2, u16, 0x14) |= 0x40;
}
