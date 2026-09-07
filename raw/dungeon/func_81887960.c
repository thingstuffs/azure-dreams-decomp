#include "common.h"

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))
#define COUNTER D_80026326.counter

typedef struct Global26326 {
    u16 counter;
    s16 flag;
    u16 unused[3];
} Global26326;

typedef struct Global26328 {
    s16 flag;
    u16 unused[4];
} Global26328;

typedef struct Global814A0 {
    s32 flags;
    s32 unused[2];
} Global814A0;

extern void func_8002530C(void) __attribute__((noreturn));
extern void func_80025314(void) __attribute__((noreturn));
extern void func_8002569C(s32, s32, s32, s32, void *);
extern u8 D_80020000[0x10000];
extern Global26326 D_80026326;
extern Global26328 D_80026328;
extern Global814A0 D_800814A0;

void func_80025160(void *arg0, s32 arg1, void *arg2) {
    s16 state;
    s32 one;
    u16 value;
    u16 angle;
    u16 next;
    s32 call_a1;
    s32 signed_angle;
    void *call_arg5;
    u8 *flag_page;
    u8 *flags_page;

    one = 1;
    COUNTER = COUNTER + 1;
    state = FIELD(arg0, s16, 0xA);

    if (state == one) {
        goto state_1;
    }
    value = state < 2;
    if (value == 0) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    FIELD(arg2, u8, 0xC) = 0x20;
    func_80025314();

state_ge_2:
    value = 2;
    if (state == value) {
        goto state_2;
    }
    value = 3;
    if (state == value) {
        goto state_3;
    }
    FIELD(arg2, u8, 0xC) = 0x20;
    func_80025314();

state_0:
    value = FIELD(arg2, u16, 6) + 0x80;
    FIELD(arg2, u16, 6) = value;
    if ((s16)value <= 0x100) {
        goto set_colors;
    }
    FIELD(arg2, u16, 6) = 0x100;
    if (FIELD(arg0, s16, 0x22) < 0x61) {
        next = FIELD(arg0, volatile u16, 0x18);
        angle = FIELD(arg0, volatile u16, 0x1C);
        call_a1 = FIELD(arg0, s16, 0x16);
        next = next - ((s32)(next << 16) >> 19);
        ASM_SCHED_BARRIER();
        angle = angle + 0x80;
        call_arg5 = (u8 *)arg0 - 0x20;
        FIELD(arg0, u16, 0x1C) = angle;
        signed_angle = angle << 16;
        FIELD(arg0, u16, 0x18) = next;
        ASM_MEM_BARRIER();
        func_8002569C(arg1, call_a1, FIELD(arg0, s16, 0x18),
                     signed_angle >> 16, call_arg5);
    }
    FIELD(arg0, u16, 0xA)++;
    if (FIELD(arg0, s16, 0x22) == 0x6F) {
        D_80026328.flag = one;
        func_8002530C();
    }
    goto set_colors;

state_1:
    flag_page = (u8 *)0x80020000;
    ASM_KEEP_NV(flag_page);
    if (FIELD(flag_page, s16, 0x6328) == 0) {
        goto state_1_zero;
    }
    FIELD(arg2, s16, 6) = -0x100;
    FIELD(arg0, u16, 0x1A) = 0x10;
    FIELD(arg0, u16, 0xA)++;
    func_8002530C();

state_2:
    value = FIELD(arg0, u16, 0x1A) - 1;
    FIELD(arg0, u16, 0x1A) = value;
    if ((value << 16) > 0) {
        goto set_colors;
    }
    FIELD(arg0, u16, 0xA)++;

state_3:
    value = FIELD(arg2, u16, 6) + 0x80;
    FIELD(arg2, u16, 6) = value;
    if ((value << 16) >= 0) {
        flags_page = (u8 *)0x80080000;
        ASM_KEEP_NV(flags_page);
        FIELD(arg0, u16, -2) |= 0x8000;
        FIELD(flags_page, s32, 0x14A0) |= 0x8000;
    }

state_1_zero:
    ASM_SCHED_BARRIER();
set_colors:
    FIELD(arg2, u8, 0xC) = 0x20;
    FIELD(arg2, u8, 0xD) = 0x40;
    FIELD(arg2, u8, 0xE) = 0xE0;
}
