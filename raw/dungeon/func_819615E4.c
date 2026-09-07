#include "common.h"

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Vec3s;

typedef struct {
    u8 pad0[0x30];
    s16 x;
    s16 y;
    s16 z;
    u8 pad36[2];
    s16 cur_x;
    s16 cur_y;
    s16 cur_z;
    u8 pad3e[0xA];
    s16 state;
    u8 pad4a[2];
    s16 timer;
    u8 pad4e[2];
    s16 phase;
    u8 pad52[2];
    s16 step;
} State;

typedef struct {
    u8 pad0[2];
    s16 cur_x;
    u8 pad4[2];
    s16 cur_y;
    u8 pad8[2];
    s16 cur_z;
    u8 intensity;
    u8 padD;
    s16 x;
    u8 pad10[2];
    s16 y;
    u8 pad14[2];
    s16 z;
} Target;

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern u16 D_80027330[];
extern s32 D_800814A0;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_80083780[];
extern void **D_800E3D18;
extern u8 *D_800E3D7C;

extern void func_80025334(s16, s16, s16);
extern void func_8002711C(void) __attribute__((noreturn));
extern void func_800271EC(void) __attribute__((noreturn));
extern void func_8003DE58(void *, void *, Vec3s *, s16);
extern void func_800B8D64(s16, s16, s16);

void func_819615E4(State *state, Target *target, u8 *color)
{
    Vec3s delta;
    Vec3s base;
    s32 d;
    s32 a;
    s16 value;
    u16 next;
    register u32 table_page ASM_REG("$2");

    D_80027330[0]++;

    if (state->state == 1) {
        goto update;
    }
    if (state->state < 2) {
        if (state->state == 0) {
            goto init;
        }
        func_800271EC();
        return;
    }

    ASM_KEEP(color);
    if (state->state == 2) {
        goto fade;
    }
    if (state->state == 3) {
        table_page = 0x80080000;
        goto phase;
    }
    func_800271EC();
    return;

init:
    {
        s32 index;
        u8 *spawn = D_80083780;

        base.x = *(u16 *)(spawn + 2);
        base.y = *(u16 *)(spawn + 6);
        base.z = *(u16 *)(D_800E3D7C + 0x88) - 0x50;
        index = ((D_80083228 + *(s16 *)(D_800E3D7C + 0x2A) + 0x100) >> 7) & 0x1C;
        func_8003DE58(*(void **)((s32)index + (s32)D_800E3D18), D_80082E80,
                      &delta, 0);
        base.x += delta.x;
        state->x = base.x;
        base.y += delta.y;
        state->y = base.y;
        base.z += delta.z;
        state->z = base.z;
        state->state++;
    }
update:
    {
        s32 product;

        a = state->cur_x;
        d = state->x - a;
        if (d < 0) {
            d += 7;
        }
        product = (d >> 3) * (state->step + 1);
        target->x = (u16)target->x +
            (a + product - target->x) / state->timer;
    }
    {
        s32 product;

        a = state->cur_y;
        d = state->y - a;
        if (d < 0) {
            d += 7;
        }
        product = (d >> 3) * (state->step + 1);
        target->y = (u16)target->y +
            (a + product - target->y) / state->timer;
    }
    {
        s32 product;

        a = state->cur_z;
        d = state->z - a;
        if (d < 0) {
            d += 7;
        }
        product = (d >> 3) * (state->step + 1);
        target->z = (u16)target->z +
            (a + product - target->z) / state->timer;
    }

    value = (u16)state->cur_x + ((target->x - state->cur_x) >> 2);
    state->cur_x = value;
    target->cur_x = value;
    value = (u16)state->cur_y + ((target->y - state->cur_y) >> 2);
    state->cur_y = value;
    target->cur_y = value;
    value = (u16)state->cur_z + ((target->z - state->cur_z) >> 2);
    state->cur_z = value;
    target->cur_z = value;

    next = state->timer - 1;
    state->timer = next;
    if ((s16)next > 0) {
        return;
    }
    func_800B8D64(state->x, state->y, state->z);
    next = state->state;
    ASM_KEEP(next);
    {
        register u16 reset_timer ASM_REG("$3") = 5;

        ASM_KEEP(reset_timer);
        state->timer = reset_timer;
    }
    func_8002711C();
    return;

fade:
    color[0xC] -= color[0xC] / state->timer;
    next = state->timer - 1;
    state->timer = next;
    if ((s16)next > 0) {
        return;
    }
    if (state->step == 0) {
        color[0xC] = 0;
        state->phase = 4;
        state->state++;
        func_800271EC();
        return;
    }
    goto finish;

phase:
    {
        s32 index;
        register u8 *table ASM_REG("$17");

        table = (u8 *)(table_page + 0x2E80);
        ASM_KEEP_NV(table);
        func_8003DE58(*(void **)(table + 8), table, &base, 0);
        next = state->phase - 1;
        state->phase = next;
        if ((s16)next > 0) {
            return;
        }
        index = ((*(u16 *)(D_800E3D7C + 0x2A) >> 8) & 0xE);
        func_80025334(
            (s16)(((table[0x24] +
                    (*(s16 *)((u8 *)&D_8006CCD8 + index) * 4)) << 6) + 0x20),
            (s16)(((table[0x25] +
                    (*(s16 *)((u8 *)&D_8006CCE8 + index) * 4)) << 6) + 0x20),
            *(s16 *)(D_800E3D7C + 0x88));
finish:
        FIELD(state, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
}
