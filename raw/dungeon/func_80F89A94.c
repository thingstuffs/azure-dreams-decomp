#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_8009A028();
extern void func_8009A3D0();
extern void func_800A2FE0();
extern void func_800A32A4();
extern void func_800A56E0();
extern void func_800ACF88();
extern void func_8017341C() __attribute__((noreturn));
extern void func_801734E8() __attribute__((noreturn));
extern u8 D_8006CCD8;
extern u8 D_8006CCE8;
extern s32 D_800814A0;
extern s32 D_80083460;
extern s16 D_8008346A;

void func_80173294(void *arg0, void *arg1, void *arg2, void *arg3) {
    register u8 *p0 ASM_REG("$16");
    register u8 *p1 ASM_REG("$8");
    register u8 *p2 ASM_REG("$18");
    register u8 *p3 ASM_REG("$17");
    register s32 index ASM_REG("$3");
    register s32 table_x ASM_REG("$4");
    register u8 *table_y_base ASM_REG("$2");
    register s32 table_y ASM_REG("$6");
    register s32 table_bias ASM_REG("$5");
    s32 state;
    s32 field14;
    s32 state_lt_2;

    p0 = arg0;
    p1 = arg1;
    p2 = arg2;
    p3 = arg3;
    table_x = (s32)(unsigned long)&D_8006CCD8;
    table_y_base = &D_8006CCE8;
    index = (FIELD(p3, u16, 0x6A) >> 8) & 0xE;
    table_bias = 0xC000;
    table_x = *(s16 *)(unsigned long)(u32)(index + table_x);
    index += (s32)(unsigned long)table_y_base;
    ASM_KEEP(index);
    ASM_KEEP(table_y_base);
    ASM_KEEP(table_x);
    ASM_KEEP(table_bias);
    field14 = FIELD(p1, s32, 0x14);
    table_y = *(s16 *)(unsigned long)(u32)index;
    field14 += table_bias;
    FIELD(p1, s32, 0x14) = field14;
    ASM_KEEP(p1);
    ASM_KEEP(table_y);
    state = FIELD(p0, u8, 0x9B);

    if (state == 1) goto state_1;
    state_lt_2 = state < 2;
    if (!state_lt_2) goto high_states;
    ASM_KEEP(state_lt_2);
    if (state == 0) {
        state = 0xFFFE0000;
        goto state_0;
    }
    func_801734E8(table_x, table_bias, table_y);

high_states:
    if (state == 2) goto state_2;
    if (state == 3) goto state_3;
    func_801734E8(table_x, table_bias, table_y);

state_0:
    state |= 0x8000;
    field14 = table_x << 16;
    FIELD(p1, s32, 0xC) = field14;
    field14 = table_y << 16;
    FIELD(p1, s32, 0x10) = field14;
    FIELD(p1, s32, 0x14) = state;
    if (D_8008346A != 0) goto done;
    FIELD(p0, u8, 0x9B)++;

state_1:
    {
        s32 flags;
        s32 object_flags;
        u16 x;
        u16 y;
        u16 status;
        volatile u8 *state_byte;
        register s32 mask_a0 ASM_REG("$4");
        register s32 mask_v1 ASM_REG("$3");
        register s32 state_next ASM_REG("$2");

        flags = FIELD(p3, s32, 0x14);
        if (flags & 0x4000) {
            if (!(flags & 0x20000000)) func_800ACF88(p3);
        }
        func_800A56E0(0x805);
        mask_a0 = 0xF7FFFFFF;
        status = FIELD(p0, u16, 0x98);
        mask_v1 = 0xFFFBFFFF;
        status |= 8;
        FIELD(p0, u16, 0x98) = status;
        object_flags = FIELD(p3, s32, 0x1C);
        object_flags &= mask_a0;
        object_flags &= mask_v1;
        FIELD(p3, s32, 0x1C) = object_flags;
        ASM_KEEP(mask_a0);
        ASM_KEEP(mask_v1);
        FIELD(p2, s16, 0x10) = 0x60;
        x = FIELD(p2, u16, 0x12);
        y = FIELD(p2, u16, 0x14);
        x -= 0x80;
        y |= 0xC;
        FIELD(p2, u16, 0x12) = x;
        FIELD(p2, u16, 0x14) = y;
        state_byte = (volatile u8 *)((u8 *)p0 + 0x9B);
        state_next = *state_byte + 1;
        ASM_TAILSLOT_PIN(state_next);
        func_8017341C(mask_a0);
    }

state_2:
    if (!(FIELD(p2, u16, 0x14) & 0x6000)) goto done;
    FIELD(p0, s16, 0x96) = 0x80;
    FIELD(p0, u8, 0x9B) = FIELD(p0, u8, 0x9B) + 1;
    func_801734E8(table_x, table_bias, table_y);

state_3:
    {
        u8 value;
        u16 timer;
        s32 *global_base;
        s32 linked;
        s32 flags;
        s32 mode;
        u8 coord_x;
        u8 coord_y;

        FIELD(p3, s32, 0x1C) |= 0x10000000;
        value = FIELD(p0, u8, 0x96);
        FIELD(p2, u8, 0xE) = value;
        FIELD(p2, u8, 0xD) = value;
        FIELD(p2, u8, 0xC) = value;
        timer = FIELD(p0, u16, 0x96) - 0x10;
        FIELD(p0, u16, 0x96) = timer;
        if ((s16)timer >= 0x10) goto done;
        global_base = &D_80083460;
        linked = global_base[4];
        if (linked == (s32)(p3 - 0x20)) global_base[4] = linked & 0x7FFFFFFF;
        func_800A2FE0(p3);
        func_800A32A4(p3);
        flags = FIELD(p3, s32, 0x1C);
        coord_x = FIELD(p2, u8, 0x24);
        coord_y = FIELD(p2, u8, 0x25);
        mode = 0x3000;
        if (flags & 0x2000) mode = 0x300;
        func_8009A3D0(coord_x, coord_y, mode);
        func_8009A028(p3);
        FIELD(p3, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    ASM_KEEP(p0);
    ASM_KEEP(p2);
    ASM_KEEP(p3);
    return;
}
