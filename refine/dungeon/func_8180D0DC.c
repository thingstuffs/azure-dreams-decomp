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

/* Updates position history, motion and shading, and flags objects whose positions have settled. */
void func_800260DC(u8 *obj, u8 *coords_out, u8 *rgb)
{
    register u8 *linked_obj ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u8 *linked_data ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *room;
    u8 *history_src;
    u8 *history_dst;
    s16 *x_adjust;
    s16 *y_adjust;
    s32 history_index;
    s32 history_offset;
    register s32 direction_offset ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 frames_left;
    s32 shade;
    register u8 *linked_rgb ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 raw_shade;
    register s32 linked_shade ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 final_coord;
    register s32 final_adjust ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u16 final_state;
    u16 final_z;
    s32 previous_z;
    s32 current_z;
    u16 y;
    u16 z;

    U16_AT(obj, 0x1A) = U16_AT(obj, 0x2C);
    U16_AT(obj, 0x1E) = U16_AT(obj, 0x2E);
    U16_AT(obj, 0x22) = U16_AT(obj, 0x30);

    history_index = 1;
copy_history:
    history_offset = history_index * 8;
    history_index--;
    history_src = obj + history_index * 8;
    history_dst = obj + history_offset;
    U16_AT(history_dst, 0x24) = U16_AT(history_src, 0x24);
    U16_AT(history_dst, 0x26) = U16_AT(history_src, 0x26);
    U16_AT(history_dst, 0x28) = U16_AT(history_src, 0x28);
    if (history_index > 0) {
        goto copy_history;
    }

    y = U16_AT(obj, 0x12);
    z = U16_AT(obj, 0x16);
    U16_AT(obj, 0x24) = U16_AT(obj, 0x0E);
    linked_obj = PTR_AT(obj, 8);
    ASM_KEEP(y);   /* MATCH pin: retail schedule: same instructions, different order without it */
    U16_AT(obj, 0x26) = y;
    U16_AT(obj, 0x28) = z;

    if (linked_obj != 0) {
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
    direction_offset = ((-S16_AT(D_80083228, 0) + 0x500) >> 8) & 0xE;
    room = D_80082E80;
    x_adjust = (s16 *)(D_8006CCD8 + direction_offset);
    {
        s32 x_target;
        s32 x_current;

        x_target = room[0x24] + *x_adjust;
        frames_left = S16_AT(obj, 0x66);
        ASM_KEEP(x_target);   /* MATCH pin: keeps a statement from moving across a call/branch */
        x_current = S16_AT(obj, 0x0E);
        U16_AT(obj, 0x0E) += ((x_target << 6) -
                              ((x_current -= 0x20), x_current)) / frames_left;
    }
    y_adjust = (s16 *)(D_8006CCE8 + direction_offset);
    {
        s32 y_target;
        s32 y_current;

        y_target = room[0x25];
        y_target += *y_adjust;
        ASM_KEEP(y_target);   /* MATCH pin: retail schedule: same instructions, different order without it */
        y_current = S16_AT(obj, 0x12);
        U16_AT(obj, 0x12) += ((y_target << 6) -
                              ((y_current -= 0x20), y_current)) / frames_left;
    }

    S32_AT(obj, 0x14) +=
        (D_80083780.height -
         (func_800644B8(frames_left * 42, frames_left) << 12) -
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
    final_coord += final_adjust;
    final_coord <<= 6;
    final_coord += 0x20;
    U16_AT(obj, 0x0E) = final_coord;
    final_coord = room[0x25];
    final_adjust = *y_adjust;
    final_coord += final_adjust;
    final_coord <<= 6;
    final_coord += 0x20;
    U16_AT(obj, 0x12) = final_coord;
       /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    final_state = U16_AT(obj, 0x64);
    final_z = U16_AT(&D_80083780, 0x0A);
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
    previous_z = S16_AT(obj, 0x22);
    current_z = S16_AT(obj, 0x16);
    goto compare_z;

have_other:
    linked_data = linked_obj + 0x20;
    U16_AT(obj, 0x0E) = U16_AT(linked_data, 0x2C);
    U16_AT(obj, 0x12) = U16_AT(linked_data, 0x2E);
    z = U16_AT(linked_data, 0x30);
    U16_AT(obj, 0x16) = z;

    if (S16_AT(obj, 0x64) != 0) {
        goto compare_position;
    }

    linked_rgb = PTR_AT(PTR_AT(obj, 8), 0x0C);
    raw_shade = U8_AT(linked_rgb, 0x0C) - S16_AT(obj, 0x6E) * 8;
    linked_shade = raw_shade;
    ASM_KEEP(linked_shade);   /* MATCH pin: retail delay-slot fill depends on it */
    if ((s16)raw_shade < 0) {
        linked_shade = 0;
    }
    U8_AT(rgb, 0x0E) = linked_shade;
    U8_AT(rgb, 0x0D) = linked_shade;
    U8_AT(rgb, 0x0C) = linked_shade;

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
    previous_z = S16_AT(obj, 0x22);
    current_z = (s16)z;

compare_z:
    if (previous_z != current_z) {
        goto copy_out;
    }
    U16_AT(obj, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
    goto done;

copy_out:
    U16_AT(coords_out, 2) = U16_AT(obj, 0x1A);
    U16_AT(coords_out, 6) = U16_AT(obj, 0x1E);
    U16_AT(coords_out, 0x0A) = U16_AT(obj, 0x22);
    U16_AT(coords_out, 0x0E) = U16_AT(obj, 0x0E);
    U16_AT(coords_out, 0x12) = U16_AT(obj, 0x12);
    U16_AT(coords_out, 0x16) = U16_AT(obj, 0x16);
    U16_AT(obj, 0x68)++;

done:
    return;
}
