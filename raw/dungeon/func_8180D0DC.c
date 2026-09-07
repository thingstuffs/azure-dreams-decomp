#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))

typedef struct {
    u8 pad[8];
    s32 height;
} HeightData;

extern s32 func_800644B8(s32, s32);

extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_800814A0;
extern u8 D_80082E80[];
extern u8 D_80083228[];
extern HeightData D_80083780;

void func_800260DC(u8 *obj, u8 *dst, u8 *rgb)
{
    register u8 *other ASM_REG("$5");
    register u8 *other_data ASM_REG("$3");
    u8 *room;
    u8 *iter_src;
    u8 *iter_dst;
    s16 *x_adjust;
    s16 *y_adjust;
    s32 i;
    s32 offset;
    register s32 phase ASM_REG("$5");
    s32 duration;
    s32 shade;
    register u8 *shade_ptr ASM_REG("$2");
    register s32 shade_raw ASM_REG("$2");
    register s32 pointer_shade ASM_REG("$3");
    register s32 final_coord ASM_REG("$2");
    register s32 final_adjust ASM_REG("$3");
    register u16 final_state ASM_REG("$2");
    register u16 final_z ASM_REG("$3");
    s32 compare_lhs;
    s32 compare_rhs;
    register u16 y ASM_REG("$3");
    u16 z;

    U16_AT(obj, 0x1A) = U16_AT(obj, 0x2C);
    U16_AT(obj, 0x1E) = U16_AT(obj, 0x2E);
    U16_AT(obj, 0x22) = U16_AT(obj, 0x30);

    i = 1;
copy_history:
    offset = i * 8;
    i--;
    iter_src = obj + i * 8;
    iter_dst = obj + offset;
    U16_AT(iter_dst, 0x24) = U16_AT(iter_src, 0x24);
    U16_AT(iter_dst, 0x26) = U16_AT(iter_src, 0x26);
    U16_AT(iter_dst, 0x28) = U16_AT(iter_src, 0x28);
    if (i > 0) {
        goto copy_history;
    }

    y = U16_AT(obj, 0x12);
    z = U16_AT(obj, 0x16);
    U16_AT(obj, 0x24) = U16_AT(obj, 0x0E);
    other = PTR_AT(obj, 8);
    ASM_KEEP(y);
    ASM_KEEP(other);
    U16_AT(obj, 0x26) = y;
    U16_AT(obj, 0x28) = z;

    if (other != 0) {
        goto have_other;
    }

    if (S16_AT(obj, 0x64) == 0) {
        goto interpolate;
    }
    if (S16_AT(obj, 0x64) == 1) {
        goto state_one;
    }
    goto copy_out;

interpolate:
    phase = ((-S16_AT(D_80083228, 0) + 0x500) >> 8) & 0xE;
    room = D_80082E80;
    x_adjust = (s16 *)(D_8006CCD8 + phase);
    {
        s32 x_target;
        s32 x_current;

        x_target = room[0x24] + *x_adjust;
        duration = S16_AT(obj, 0x66);
        ASM_KEEP(x_target);
        x_current = S16_AT(obj, 0x0E);
        U16_AT(obj, 0x0E) += ((x_target << 6) -
                              ((x_current -= 0x20), x_current)) / duration;
    }
    y_adjust = (s16 *)(D_8006CCE8 + phase);
    ASM_KEEP(phase);
    {
        register s32 y_target ASM_REG("$3");
        s32 y_current;

        y_target = room[0x25];
        ASM_KEEP(y_target);
        y_target += *y_adjust;
        ASM_KEEP(y_target);
        y_current = S16_AT(obj, 0x12);
        U16_AT(obj, 0x12) += ((y_target << 6) -
                              ((y_current -= 0x20), y_current)) / duration;
    }

    S32_AT(obj, 0x14) +=
        (D_80083780.height -
         (func_800644B8(duration * 42, duration) << 12) -
         S32_AT(obj, 0x14)) / S16_AT(obj, 0x66);

    if (S16_AT(obj, 0x6A) < 0x80) {
        U16_AT(obj, 0x6A) += 0x10;
    }
    shade = U8_AT(obj, 0x6A);
    U8_AT(rgb, 0x0D) = shade;
    U8_AT(rgb, 0x0E) = shade;
    U8_AT(rgb, 0x0C) = shade;

    U16_AT(obj, 0x66)--;
    if (S16_AT(obj, 0x66) > 0) {
        goto copy_out;
    }

    final_coord = room[0x24];
    final_adjust = *x_adjust;
    ASM_KEEP(final_coord);
    ASM_KEEP(final_adjust);
    final_coord += final_adjust;
    final_coord <<= 6;
    ASM_KEEP(final_coord);
    final_coord += 0x20;
    U16_AT(obj, 0x0E) = final_coord;
    final_coord = room[0x25];
    final_adjust = *y_adjust;
    ASM_KEEP(final_coord);
    ASM_KEEP(final_adjust);
    final_coord += final_adjust;
    final_coord <<= 6;
    ASM_KEEP(final_coord);
    final_coord += 0x20;
    U16_AT(obj, 0x12) = final_coord;
    ASM_KEEP(final_coord);
    final_state = U16_AT(obj, 0x64);
    final_z = U16_AT(&D_80083780, 0x0A);
    ASM_KEEP(final_state);
    ASM_KEEP(final_z);
    U16_AT(obj, 0x64) = final_state + 1;
    U16_AT(obj, 0x16) = final_z;
    goto copy_out;

state_one:
    if (S16_AT(obj, 0x1A) != S16_AT(obj, 0x0E)) {
        goto copy_out;
    }
    if (S16_AT(obj, 0x1E) != S16_AT(obj, 0x12)) {
        goto copy_out;
    }
    compare_lhs = S16_AT(obj, 0x22);
    compare_rhs = S16_AT(obj, 0x16);
    ASM_KEEP(compare_rhs);
    goto compare_z;

have_other:
    other_data = other + 0x20;
    ASM_KEEP(other_data);
    U16_AT(obj, 0x0E) = U16_AT(other_data, 0x2C);
    U16_AT(obj, 0x12) = U16_AT(other_data, 0x2E);
    z = U16_AT(other_data, 0x30);
    U16_AT(obj, 0x16) = z;

    if (S16_AT(obj, 0x64) != 0) {
        goto compare_position;
    }

    shade_ptr = PTR_AT(PTR_AT(obj, 8), 0x0C);
    ASM_KEEP(shade_ptr);
    shade_raw = U8_AT(shade_ptr, 0x0C) - S16_AT(obj, 0x6E) * 8;
    pointer_shade = shade_raw;
    ASM_KEEP(shade_raw);
    ASM_KEEP(pointer_shade);
    if ((s16)shade_raw < 0) {
        pointer_shade = 0;
    }
    U8_AT(rgb, 0x0E) = pointer_shade;
    U8_AT(rgb, 0x0D) = pointer_shade;
    U8_AT(rgb, 0x0C) = pointer_shade;

    U16_AT(obj, 0x66)--;
    if (S16_AT(obj, 0x66) > 0) {
        goto copy_out;
    }
    U16_AT(obj, 0x64)++;
    goto copy_out;

compare_position:
    if (S16_AT(obj, 0x1A) != S16_AT(obj, 0x0E)) {
        goto copy_out;
    }
    if (S16_AT(obj, 0x1E) != S16_AT(obj, 0x12)) {
        goto copy_out;
    }
    compare_lhs = S16_AT(obj, 0x22);
    compare_rhs = (s16)z;

compare_z:
    if (compare_lhs != compare_rhs) {
        goto copy_out;
    }
    U16_AT(obj, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
    goto done;

copy_out:
    U16_AT(dst, 2) = U16_AT(obj, 0x1A);
    U16_AT(dst, 6) = U16_AT(obj, 0x1E);
    U16_AT(dst, 0x0A) = U16_AT(obj, 0x22);
    U16_AT(dst, 0x0E) = U16_AT(obj, 0x0E);
    U16_AT(dst, 0x12) = U16_AT(obj, 0x12);
    U16_AT(dst, 0x16) = U16_AT(obj, 0x16);
    U16_AT(obj, 0x68)++;

done:
    return;
}
