#include "common.h"

extern s32 func_8009A3D0();
extern s8 func_8009FB34();
extern s32 func_800A4E2C();
extern s32 func_800AA53C();
typedef struct {
    u8 pad[10];
    u16 counter;
} DungeonState;

extern DungeonState D_80083460;

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

void func_800AA5E4(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 var_a2;
    s32 temp_v0;
    s32 x;
    s32 y;
    void *var_a0;
    register DungeonState *state ASM_REG("$3");

    FIELD(arg0, s8, 0x9A) = 4;
    FIELD(arg0, s8, 0x9B) = 0;
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(arg0, s16, 0x96) = 0x10;
    FIELD(arg0, u16, 0x98) = FIELD(arg0, u16, 0x98) | 8;
    temp_v0 = FIELD(arg3, s32, 0x1C) | 0x10000;
    FIELD(arg3, s32, 0x1C) = temp_v0;
    x = FIELD(arg2, u8, 0x24);
    y = FIELD(arg2, u8, 0x25);
    var_a2 = 0x3000;
    if (temp_v0 & 0x2000) {
        var_a2 = 0x300;
    }
    func_8009A3D0(x, y, var_a2);
    var_a0 = (u8 *)arg2 + 0x24;
loop:
    if ((s16)func_800A4E2C(var_a0, (u8 *)arg2 + 0x25) < 0) {
        var_a0 = (u8 *)arg2 + 0x24;
        goto loop;
    }
    FIELD(arg2, s8, 0x26) = func_8009FB34(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800AA53C(arg3);
    state = &D_80083460;
    ASM_KEEP(state);
    state->counter = state->counter + 1;
}
