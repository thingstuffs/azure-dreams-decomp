#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171058[];
extern u8 D_801748A0[];
extern u8 D_801748A8[];
extern u8 D_801748B0[];

void func_80173A08(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 scratch[2];
    s32 state;
    s32 remaining;
    s32 tile_x;
    s32 x;
    s32 temp_v0;
    s32 velocity;
    s32 y;
    s32 sum;
    s32 counter;
    register s32 entity_mask ASM_REG("$3");
    s32 timer;
    s32 flags;
    s32 index;
    register u8 *table ASM_REG("$5");
    u8 *global_base;
    u8 *map_base;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto tick;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto tick;

state_zero:
    if (!(FIELD(arg2, u16, 0x14) & 0x6000)) {
        goto tick;
    }
    table = D_801748A0;
    FIELD(arg2, u8 *, 0x2C) = table;
    index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, table[index & 7], 0);
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg3, s32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg0, s16, 0xB0) = 5;
    FIELD(arg0, s32, 0xA0) = 0;
    FIELD(arg0, u8, 0x9B)++;
    goto tick;

state_one:
    FIELD(arg0, s32, 0x90) += 0xC0000;
    if (!(FIELD(arg2, u16, 0x14) & 0x6000)) {
        goto tick;
    }
    table = D_801748A8;
    FIELD(arg2, u8 *, 0x2C) = table;
    index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, table[index & 7], 0);
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg3, s32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg0, s16, 0xB0) = 5;
    FIELD(arg0, s32, 0xA0) = 0;
    FIELD(arg0, s32, 0x90) -= 0x400000;
    FIELD(arg0, u8, 0x9B)++;

state_two:
    remaining = FIELD(arg0, s16, 0xB0);
    FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA0);
    if (remaining != 0) {
        tile_x = FIELD(arg2, u8, 0x24);
        x = FIELD(arg1, s16, 2);
        tile_x <<= 6;
        x -= 0x20;
        FIELD(arg1, s32, 0xC) = ((tile_x - x) << 16) / remaining;

        y = FIELD(arg1, s16, 6);
        y -= 0x20;
        FIELD(arg1, s32, 0x10) =
            (((FIELD(arg2, u8, 0x25) << 6) - y) << 16) /
            FIELD(arg0, s16, 0xB0);

        temp_v0 = (0 - func_800644B8(FIELD(arg0, s16, 0xB0) * 0x199)) << 10;
        FIELD(arg0, s32, 0xA0) = temp_v0 + (temp_v0 >> 1);
    }

    sum = FIELD(arg0, s32, 0x90);
    velocity = FIELD(arg0, s32, 0xA0);
    counter = FIELD(arg0, u16, 0xB0);
    sum += velocity;
    counter -= 1;
    FIELD(arg0, u16, 0xB0) = counter;
    FIELD(arg0, s32, 0x90) = sum;
    if ((counter << 16) >= 0) {
        goto state_three;
    }

    entity_mask = 0x08000000;
    ASM_KEEP(entity_mask);
    FIELD(arg0, s32, 0x90) = 0;
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg3, s32, 0x1C) |= entity_mask;
    table = D_801748B0;
    FIELD(arg2, u8 *, 0x2C) = table;
    index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, table[index & 7], 0);
    FIELD(arg0, u8, 0x9B)++;

state_three:
    if (!(FIELD(arg3, s32, 0x1C) & 0x08000000)) {
        goto tick;
    }
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    table = D_801748B0;
    FIELD(arg2, u8 *, 0x2C) = table;
    index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, table[index & 7], 0);
    FIELD(arg0, u8, 0x9B)++;

tick:
    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((timer << 16) > 0) {
        return;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800AD594(arg3, 4);
    func_800A4ACC(arg3);

    global_base = (u8 *)&D_80083460;
    if (FIELD(global_base, s16, 8) != 0) {
        FIELD(global_base, u16, 8)--;
    }

    flags = FIELD(arg3, s32, 0x1C);
    if (flags & 0x2000) {
        if (FIELD(arg3, u16, 0x46) & 0x8000) {
            FIELD(arg3, u16, 0x46) &= 0x7FFF;
        }
        goto finish;
    }
    if (flags & 0x410) {
        goto finish;
    }
    if (flags & 0x20000) {
        map_base = D_80082E80;
        FIELD(arg3, s16, 0x2A) = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            FIELD(map_base, u8, 0x24), FIELD(map_base, u8, 0x25), scratch);
    }

finish:
    FIELD(arg0, void *, 0x8C) = D_80171058;
    func_800A9A04(arg3);
}
