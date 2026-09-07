#include "common.h"

typedef s32 M2C_UNK;
#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80048A44();
extern s32 func_8008C730();
extern void func_8008C798(void) __attribute__((noreturn));
extern void func_8008c798(void) __attribute__((noreturn));
extern M2C_UNK func_80099844();
extern s32 func_8009B5AC();
extern M2C_UNK func_8009F644();
extern M2C_UNK func_800A56E0();
extern s32 D_80012090[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_80081484[];
extern s32 D_80083170[];
extern s16 D_80083228[];
extern u8 D_8008ACDC[];
extern u8 D_800DCFC8[];
extern u8 D_800E0495[];

s32 func_8008C5C4(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0;
    register u32 tail_page ASM_REG("$3");
    register s32 tail_result ASM_REG("$2");
    register s32 state_value ASM_REG("$3");
    register s32 temp_v1_2 ASM_REG("$3");

    temp_v1 = ((u16)FIELD(arg3, u16, 0x2A) >> 8) & 0xE;
    temp_v0 = func_8009B5AC(
        arg3,
        (s16)(FIELD(arg2, u8, 0x24) + *(u16 *)(D_8006CCD8 + temp_v1)),
        (s16)(FIELD(arg2, u8, 0x25) + *(u16 *)(D_8006CCE8 + temp_v1)));
    FIELD(arg0, s32, 0x124) = temp_v0;
    if (temp_v0 != 0) {
        var_v0 = -1;
        if (temp_v0 <= 0) {
            if (!(FIELD(temp_v0, s32, 0x14) & 0x80000)) {
                FIELD(arg0, s32, 0x11C) = temp_v0;
                FIELD(arg0, s32, 0x124) = 0;
                return func_8008C730(temp_v0);
            }
            ASM_SCHED_BARRIER();
            state_value = *(s32 *)0x80012090;
            if (state_value == 1) {
                ASM_SCHED_BARRIER();
                temp_v1_2 = FIELD(temp_v0, u8, 0x13);
                if ((temp_v1_2 == 0x39) || (temp_v1_2 == 2)) {
                    if (D_80083170[0] & 0x40) {
                        func_800A56E0(0x506);
                        func_80099844(FIELD(arg0, s32, 0x124), &D_800E0495);
                        tail_result = 0;
                    } else {
                        tail_result = 0;
                    }
                    ASM_KEEP(tail_result);
                    tail_page = 0x80080000;
                    ASM_KEEP(tail_page);
                    FIELD((void *)tail_page, s32, 0x1484) = 0;
                    tail_page = 0x80090000;
                    ASM_KEEP(tail_page);
                    tail_page -= 0x5324;
                    FIELD(arg0, s32, 0x124) = 0;
                    FIELD(arg0, void *, 0x8C) = (void *)tail_page;
                    func_8008C798();
                }
            }
            temp_a3 = FIELD(arg0, s32, 0x124);
            FIELD(temp_a3, s32, 0x1C) |= 0x80000;
            FIELD(arg3, s32, 0x1C) |= 0x100000;
            FIELD(FIELD(arg0, s32, 0x124), void *, 0x60) = arg3;
            func_8009F644(arg3, 0x20, 0, 0);
            func_800A56E0(0x511);
            FIELD(arg0, s8, 0x9A) = 0x1B;
            FIELD(arg0, s8, 0x9B) = 0;
            FIELD(arg0, void *, 0x8C) = 0;
            FIELD(arg2, u8 *, 0x2C) = D_800DCFC8;
            func_80048A44(
                arg2,
                D_800DCFC8[((s32)(D_80083228[0] +
                                         (s16)FIELD(arg3, u16, 0x2A) + 0x100) >>
                                  9) &
                                 7],
                0, 1);
            tail_result = 1;
            ASM_TAILSLOT_PIN(tail_result);
            func_8008c798();
        }
        return var_v0;
    }
    FIELD(arg0, u8 *, 0x8C) = D_8008ACDC;
    var_v0 = 0;
    return var_v0;
}

/* MECHANISM: The natural 0x20 frame holds arg0/arg2/arg3 in s0/s2/s1; v1 locals
   split the D_80012090 load and tail page bases, with fences at scheduling seams.
   Branch-local v0 merges and per-site noreturn/tail-slot contracts recover both tails. */
