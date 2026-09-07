#include "common.h"

typedef struct DungeonState {
    u8 pad0[10];
    s16 field_A;
    u8 pad_C[4];
    s32 field_10;
} DungeonState;

extern DungeonState D_80083460;
extern u8 D_8016B778[];
extern void func_8016AD00(void);
extern void func_8016D65C() __attribute__((noreturn));

void func_8016D5B4(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u8 old;
    u8 value;

    old = *(u8 *)((u8 *)arg0 + 0x9B);
    value = old + 1;
    *(u8 *)((u8 *)arg0 + 0x9B) = value;

    if (value == 1) {
        s32 state = D_80083460.field_10;

        if (state == arg3 - 0x20) {
            D_80083460.field_10 = state & 0x7FFFFFFF;
            func_8016D65C(&D_80083460);
        }
    } else if (value >= 5) {
        DungeonState *state = &D_80083460;

        *(u8 *)((u8 *)arg0 + 0x9B) = old;
        if (state->field_A == 0) {
            func_8016AD00();
            *(s8 *)((u8 *)arg0 + 0xB4) = 1;
            state->field_A = (u16)state->field_A + 1;
            *(u8 *)((u8 *)arg0 + 0x9B) = 0;
            *(u8 **)((u8 *)arg0 + 0x8C) = D_8016B778;
        }
    }
}
