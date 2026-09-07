#include "common.h"

typedef struct S_80173294_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_80173294_0;   /* p3 in func_80173294 */

typedef struct S_80173294_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_80173294_1;   /* p1 in func_80173294 */

typedef struct S_80173294_2 {
    u8 pad_00[0x96];
    union { s16 s16; u8 u8; u16 u16; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80173294_2;   /* p0 in func_80173294 */

typedef struct S_80173294_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173294_3;   /* p2 in func_80173294 */



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
    u8 *p0;
    u8 *p1;
    u8 *p2;
    register u8 *p3 ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 index;
    register s32 table_x ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    register u8 *table_y_base ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 table_y;
    register s32 table_bias ASM_REG("$5");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 state;
    s32 field14;
    s32 state_lt_2;

    p0 = arg0;
    p1 = arg1;
    p2 = arg2;
    p3 = arg3;
    table_x = (s32)(unsigned long)&D_8006CCD8;
    table_y_base = &D_8006CCE8;
    index = (((S_80173294_0 *)p3)->unk_6A >> 8) & 0xE;
    table_bias = 0xC000;
    table_x = *(s16 *)(unsigned long)(u32)(index + table_x);
    index += (s32)(unsigned long)table_y_base;
    ASM_KEEP(table_bias);   /* MATCH pin: load-bearing for the whole function shape */
    field14 = ((S_80173294_1 *)p1)->unk_14;
    table_y = *(s16 *)(unsigned long)(u32)index;
    field14 += table_bias;
    ((S_80173294_1 *)p1)->unk_14 = field14;
    ASM_KEEP(p1);   /* MATCH pin: load-bearing for the whole function shape */
    state = ((S_80173294_2 *)p0)->unk_9B;

    if (state == 1) goto state_1;
    state_lt_2 = state < 2;
    if (!state_lt_2) goto high_states;
    ASM_KEEP(state_lt_2);   /* MATCH pin: retail delay-slot fill depends on it */
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
    ((S_80173294_1 *)p1)->unk_0C = field14;
    field14 = table_y << 16;
    (*(s32 *)((u8 *)p1 + 0x10)) = field14;
    (*(s32 *)((u8 *)p1 + 0x14)) = state;
    if (D_8008346A != 0) goto done;
    ((S_80173294_2 *)p0)->unk_9B++;

state_1:
    {
        s32 flags;
        s32 object_flags;
        u16 x;
        u16 y;
        u16 status;
        volatile u8 *state_byte;
        s32 mask_a0;
        s32 mask_v1;
        register s32 state_next ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */

        flags = ((S_80173294_0 *)p3)->unk_14;
        if (flags & 0x4000) {
            if (!(flags & 0x20000000)) func_800ACF88(p3);
        }
        func_800A56E0(0x805);
        mask_a0 = 0xF7FFFFFF;
        status = ((S_80173294_2 *)p0)->unk_98;
        mask_v1 = 0xFFFBFFFF;
        status |= 8;
        ((S_80173294_2 *)p0)->unk_98 = status;
        object_flags = ((S_80173294_0 *)p3)->unk_1C;
        object_flags &= mask_a0;
        object_flags &= mask_v1;
        ((S_80173294_0 *)p3)->unk_1C = object_flags;
        ASM_KEEP(mask_a0);   /* MATCH pin: retail immediate-load split depends on it */
        ((S_80173294_3 *)p2)->unk_10 = 0x60;
        x = ((S_80173294_3 *)p2)->unk_12;
        y = ((S_80173294_3 *)p2)->unk_14;
        x -= 0x80;
        y |= 0xC;
        ((S_80173294_3 *)p2)->unk_12 = x;
        ((S_80173294_3 *)p2)->unk_14 = y;
        state_byte = (volatile u8 *)((u8 *)p0 + 0x9B);
        state_next = *state_byte + 1;
        ASM_TAILSLOT_PIN(state_next);   /* MATCH pin: keeps a statement from moving across a call/branch */
        func_8017341C(mask_a0);
    }

state_2:
    if (!(((S_80173294_3 *)p2)->unk_14 & 0x6000)) goto done;
    ((S_80173294_2 *)p0)->unk_96.s16 = 0x80;
    ((S_80173294_2 *)p0)->unk_9B = ((S_80173294_2 *)p0)->unk_9B + 1;
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

        ((S_80173294_0 *)p3)->unk_1C |= 0x10000000;
        value = ((S_80173294_2 *)p0)->unk_96.u8;
        ((S_80173294_3 *)p2)->unk_0E = value;
        ((S_80173294_3 *)p2)->unk_0D = value;
        ((S_80173294_3 *)p2)->unk_0C = value;
        timer = ((S_80173294_2 *)p0)->unk_96.u16 - 0x10;
        ((S_80173294_2 *)p0)->unk_96.u16 = timer;
        if ((s16)timer >= 0x10) goto done;
        global_base = &D_80083460;
        linked = global_base[4];
        if (linked == (s32)(p3 - 0x20)) global_base[4] = linked & 0x7FFFFFFF;
        func_800A2FE0(p3);
        func_800A32A4(p3);
        flags = ((S_80173294_0 *)p3)->unk_1C;
        coord_x = ((S_80173294_3 *)p2)->unk_24;
        coord_y = ((S_80173294_3 *)p2)->unk_25;
        mode = 0x3000;
        if (flags & 0x2000) mode = 0x300;
        func_8009A3D0(coord_x, coord_y, mode);
        func_8009A028(p3);
        (*(u16 *)((u8 *)p3 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    ASM_KEEP(p0);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP(p2);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    ASM_KEEP(p3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    return;
}
