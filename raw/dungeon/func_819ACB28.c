#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8003DE58(void *, void *, void *, s32);
extern void func_800244A8(void) __attribute__((noreturn));
extern s32 func_800249DC(void *);
extern void func_8004491C(void *, void *);

typedef struct CounterView {
    u16 value;
    u16 pad[5];
} CounterView;

typedef struct FlagsView {
    s32 value;
    s32 pad[2];
} FlagsView;

extern CounterView D_80027452;
extern u8 D_80045340[];
extern FlagsView D_800814A0;

void func_819ACB28(void *arg0, void *arg1, void *arg2)
{
    s16 temp_v1;
    u16 temp_a0;
    void *temp_a0_2;
    void *temp_s0;

    D_80027452.value = D_80027452.value + 1;
    temp_v1 = FIELD(arg0, s16, 0x2C);
    temp_a0 = FIELD(arg0, u16, 0x2C);

    if (temp_v1 == 0) {
        temp_s0 = FIELD(FIELD(arg0, void *, 8), void *, 0xC);
        if (FIELD(arg0, s16, 0x2E) == 0) {
            if (func_8003DE58(FIELD(temp_s0, void *, 8), temp_s0,
                              (u8 *)arg0 + 0x24, 0) == 0) {
                if (FIELD(temp_s0, u16, 0x14) & 0x8000) {
                    FIELD(arg0, s16, 0x28) = -0x40;
                }
            }
            FIELD(arg0, s16, 0x2E) = 1;
        }

        temp_a0_2 = FIELD(FIELD(arg0, void *, 8), void *, 8);
        FIELD(arg1, s16, 2) =
            FIELD(temp_a0_2, u16, 2) + FIELD(arg0, u16, 0x24);
        FIELD(arg1, s16, 6) =
            FIELD(temp_a0_2, u16, 6) + FIELD(arg0, u16, 0x26);
        FIELD(arg1, s16, 0xA) =
            FIELD(temp_a0_2, u16, 0xA) + FIELD(arg0, u16, 0x28);
        if (func_800249DC(arg1) != 0) {
            func_8004491C((u8 *)arg0 - 0x20, D_80045340);
            FIELD(arg0, u16, 0x2C) = FIELD(arg0, u16, 0x2C) + 1;
            func_800244A8();
        }
    } else if (temp_v1 == 1) {
        if (FIELD(arg2, u8, 0xC) < 0xC0) {
            FIELD(arg2, u32, 0xC) += 0x202020;
            func_800244A8();
        }
        FIELD(arg0, u16, 0x2C) = temp_a0 + 1;
        func_800244A8();
    } else if (temp_v1 == 2) {
        FIELD(arg2, u32, 0xC) += 0xFFEFEFF0;
        if (FIELD(arg2, u8, 0xC) == 0) {
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0.value |= 0x8000;
        }
    }
}
