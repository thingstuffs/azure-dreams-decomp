#include "common.h"
extern int abs(int);

typedef struct {
    s16 x;
    s16 unk2;
    s16 y;
    s16 unk6;
} LocalPoint;

extern u8 D_8002004C[];
extern void *D_80020058[];
extern u8 D_800245DC[];
extern u8 D_80083780[];

extern s32 func_80064710(s32);
extern void func_800672D8(LocalPoint *, void *);
extern void SD_Call(s32);

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))

/* Update the effect position, spin phases, animated icons, and rotation sound. */
void func_80020C10(void *state_arg, void *target_arg, void *effect_arg)
{
    s32 *world_pos = (s32 *)D_80083780;
    s32 *close_pos;
    s32 dx = (world_pos[0] + (s32)0xFCA00000) >> 16;
    s32 dy = (world_pos[1] + (s32)0xFCA00000) >> 16;
    void *effect;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *spin_data ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 prev_angle;
    LocalPoint point;
    s32 distance;
    s32 dx_squared;
    s32 dy_squared;
    s32 abs_dx;
    s32 abs_dy;
    s32 speed_limit;
    s32 sector_start;
    s32 reduced_speed;
    s32 icon_x;
    s32 icon_frame;
    register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u32 phase;
    static void *const phase_labels[] = {
        &&idle, &&accelerate, &&spin, &&select_sector,
        &&decelerate, &&stop_spin, &&start_icons, &&draw_icons,
    };

    effect = effect_arg;
    spin_data = *(void **)state_arg;
    prev_angle = U16(effect, 0x1A);
    point = *(LocalPoint *)D_8002004C;
    dx_squared = dx * dx;
    dy_squared = dy * dy;
    distance = func_80064710(dx_squared + dy_squared);
    S32(state_arg, 0x60) = S32(target_arg, 8);

    if (world_pos[1] > 0x035FFFFF) {
        if (distance < 185) {
            goto close_range;
        }
    } else if (distance < 193) {
        goto close_range;
    }
    goto middle_range;

close_range:
    close_pos = (s32 *)D_80083780;
    if (S16(close_pos, 0xA) >= S16(target_arg, 0xA)) {
        close_pos[0] = S32(state_arg, 4);
        close_pos[1] = S32(state_arg, 8);
    }
    S32(state_arg, 0x58) = close_pos[0];
    S32(state_arg, 0x5C) = close_pos[1];
    if (distance < 128) {
        value = (128 - distance) >> 1;
        U16(state_arg, 0x62) = U16(state_arg, 0x62) - value;
    }
    goto position_done;

middle_range:
    if (distance < 209) {
        s32 *mid_pos;
        mid_pos = (s32 *)D_80083780;
        if (S16(mid_pos, 0xA) >= S16(target_arg, 0xA)) {
            mid_pos[0] = S32(state_arg, 4);
            mid_pos[1] = S32(state_arg, 8);
        }

        abs_dx = dx;
        abs_dx = abs(abs_dx);
        abs_dy = dy;
        if (abs_dy < 0) {
            ASM_KEEP(abs_dy);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            abs_dy = -abs_dy;
        }
        if (abs_dx > abs_dy) {
            goto x_axis;
        }
        if (mid_pos[1] > 0x033FFFFF) {
            goto y_axis;
        }
x_axis:
        S32(state_arg, 0x5C) = mid_pos[1];
        if (dx > 0) {
            S32(state_arg, 0x58) = mid_pos[0] - 0x00280000;
        } else {
            S32(state_arg, 0x58) = mid_pos[0] + 0x00280000;
        }
        goto position_done;

y_axis:
        S32(state_arg, 0x58) = mid_pos[0];
        if (dy > 0) {
            S32(state_arg, 0x5C) = mid_pos[1] - 0x00280000;
        } else {
            S32(state_arg, 0x5C) = mid_pos[1] + 0x00280000;
        }
    } else {
        S32(state_arg, 0x58) = 0x03600000;
        S32(state_arg, 0x5C) = 0x03600000;
        goto position_done;
    }

position_done:
    S32(state_arg, 4) = S32(D_80083780, 0);
    S32(state_arg, 8) = S32(D_80083780, 4);

    {
        s32 scaled_speed = S32(spin_data, 0x14) / ((S16(spin_data, 0x22) << 8) + 0x300);
        s32 base_speed = scaled_speed + 0x40;
        speed_limit = ((3 - S16(spin_data, 0x22)) << 5) + base_speed;
    }

    phase = S16(state_arg, 0x70);
    if (phase >= 8) {
        goto wrap_angle;
    }
    (void)phase_labels;
    goto *D_80020058[phase];

idle:
    value = U8(effect, 0xE);
    value += (128 - value) >> 1;
    U8(effect, 0xE) = value;
    U8(effect, 0xD) = value;
    U8(effect, 0xC) = value;
    S32(state_arg, 0x6C) = 0x00080000;
    goto wrap_angle;

accelerate:
    reduced_speed = (S16(state_arg, 0x72) + 16) >> 4;
    value = U16(state_arg, 0x72) + reduced_speed;
    U16(state_arg, 0x72) = value;
    if ((s16)value > speed_limit) {
        U16(state_arg, 0x72) = speed_limit;
        S16(state_arg, 0x70) = 2;
    }
    U16(effect, 0x1A) += U16(state_arg, 0x72);
    goto wrap_angle;

spin:
    U16(effect, 0x1A) += speed_limit;
    if (distance >= 161 && S32(D_80083780, 4) > 0x03600000 && S16(spin_data, 0x18) == 5) {
        S16(state_arg, 0x72) = speed_limit;
        S16(state_arg, 0x70) = 3;
    }
    goto wrap_angle;

select_sector:
    dx = U16(effect, 0x1A) & 0x7FF;
    if (dx >= 0x6AB) {
        S16(spin_data, 0x24) = 0;
        goto reset_spin_angle;
    }
    dy = 0x155;
    distance = 4;
    sector_start = 0x554;
    for (; distance >= 0; distance--, sector_start -= dy) {
        if (dx >= sector_start) {
            break;
        }
    }
    value = distance & 1;
    if (value) {
        S16(spin_data, 0x24) = 1;
    } else {
        S16(spin_data, 0x24) = 2;
    }
reset_spin_angle:
    S16(spin_data, 0x1A) = 0;

decelerate:
    if (S16(spin_data, 0x22) == 2) {
        dx = 6;
    } else {
        dx = 5;
    }
    value = S16(state_arg, 0x72) >> dx;
    reduced_speed = U16(state_arg, 0x72) - value;
    U16(state_arg, 0x72) = reduced_speed;
    U16(effect, 0x1A) += U16(state_arg, 0x72);
    U16(spin_data, 0x1A) += U16(state_arg, 0x72);
    if (S16(state_arg, 0x72) < (1 << dx)) {
        S16(state_arg, 0x74) = 0;
        S16(state_arg, 0x70) = 5;
    }
    goto wrap_angle;

stop_spin:
    U16(effect, 0x1A) += U16(state_arg, 0x72);
    U16(spin_data, 0x1A) += U16(state_arg, 0x72);
    value = U16(state_arg, 0x74) + 1;
    U16(state_arg, 0x74) = value;
    if ((value & 3) == 0) {
        U16(state_arg, 0x72) -= 2;
    }
    if (S16(state_arg, 0x72) < 4) {
        S16(state_arg, 0x70) = 0;
    }
    goto wrap_angle;

start_icons:
    S16(state_arg, 0x70) = 7;
    S16(state_arg, 0x72) = 0;

draw_icons:
    dx = 0;
    spin_data = (void *)6;
    dy = (s32)D_800245DC;
    icon_x = 122;
icon_loop:
    {
        point.x = icon_x;
        point.y = (s32)spin_data;
        icon_frame = (S16(state_arg, 0x72) >> 1) + dx;
        func_800672D8(&point, (void *)((icon_frame % 3) * 32 + dy));
        icon_x += 16;
        dx++;
    }
    if (dx < 3) {
        goto icon_loop;
    }
    value = U16(state_arg, 0x72);
    U16(state_arg, 0x72) = value + 1;
    if ((s16)value >= 198) {
        S16(state_arg, 0x70) = 0;
    }

wrap_angle:
    value = U16(effect, 0x1A) & 0xFFF;
    U16(effect, 0x1A) = value;
    if ((prev_angle >> 8) != ((u32)value >> 8)) {
        SD_Call(0x701);
    }
}
