#include "common.h"
#include "shared/entity.h"
#include "shared/entity_objects.h"
#include "shared/sprite_frame_state.h"

/* Context reached through the callback work's first word. Only the fields
 * read or written by this spin controller are described here. */
typedef struct SpinContext {
    u8 pad_00[0x14];
    s32 unk_14;
    s16 state;
    union { s16 s; u16 u; } angle;
    u8 pad_1C[6];
    s16 kind;
    s16 sector;
} SpinContext;

typedef struct SpinPhaseWork {
    SpinContext *context;
    s32 previous_x;
    s32 previous_y;
    u8 pad_0C[0x4C];
    s32 target_x;
    s32 target_y;
    union {
        Fixed1616 fixed;
        struct { u16 frac, i; } bits;
    } target_height;
    u8 pad_64[8];
    s32 unk_6C;
    s16 phase;
    union { s16 s; u16 u; } phase_value;
    u16 stop_ticks;
} SpinPhaseWork;
extern int abs(int);

typedef struct {
    s16 x;
    s16 unk2;
    s16 y;
    s16 unk6;
} LocalPoint;

extern u8 D_8002004C[];
extern u8 D_800245DC[];

extern s32 SquareRoot0(s32);
extern void LoadImage(LocalPoint *, void *);
extern void SD_Call(s32);


/* Update the effect position, spin phases, animated icons, and rotation sound. */
void update_effect_position_spin_phases(SpinPhaseWork *state_arg, ObjectPosition *target_arg, SpriteFrameState *effect_arg)
{
    ObjectPosition *world_pos = &view_reference_entity;
    ObjectPosition *close_pos;
    s32 dx = (world_pos->x.v + (s32)0xFCA00000) >> 16;
    s32 dy = (world_pos->y.v + (s32)0xFCA00000) >> 16;
    SpinContext *spin_data;
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
    s32 icon_frame;
    s32 value_close;
    s32 value_idle;
    s32 value_accel;
    s32 value_sector;
    s32 value_decel;
    s32 value_stop;
    s32 value_draw;
    s32 value_wrap;
    u32 phase;

    spin_data = state_arg->context;
    prev_angle = effect_arg->angle_z;
    point = *(LocalPoint *)D_8002004C;
    dx_squared = dx * dx;
    dy_squared = dy * dy;
    distance = SquareRoot0(dx_squared + dy_squared);
    state_arg->target_height.fixed.v = target_arg->z.v;

    if (world_pos->y.v > 0x035FFFFF ? distance < 185 : distance < 193) {
        close_pos = &view_reference_entity;
        if (close_pos->z.w.i >= target_arg->z.w.i) {
            close_pos->x.v = state_arg->previous_x;
            close_pos->y.v = state_arg->previous_y;
        }
        state_arg->target_x = close_pos->x.v;
        state_arg->target_y = close_pos->y.v;
        if (distance < 128) {
            value_close = (128 - distance) >> 1;
            state_arg->target_height.bits.i = state_arg->target_height.bits.i - value_close;
        }
    } else if (distance < 209) {
        ObjectPosition *mid_pos;
        mid_pos = &view_reference_entity;
        if (mid_pos->z.w.i >= target_arg->z.w.i) {
            mid_pos->x.v = state_arg->previous_x;
            mid_pos->y.v = state_arg->previous_y;
        }

        abs_dx = dx;
        abs_dx = abs(abs_dx);
        abs_dy = dy;
        abs_dy = abs(abs_dy);
        if (abs_dx > abs_dy || mid_pos->y.v <= 0x033FFFFF) {
            state_arg->target_y = mid_pos->y.v;
            if (dx > 0) {
                state_arg->target_x = mid_pos->x.v - 0x00280000;
            } else {
                state_arg->target_x = mid_pos->x.v + 0x00280000;
            }
        } else {
            state_arg->target_x = mid_pos->x.v;
            if (dy > 0) {
                state_arg->target_y = mid_pos->y.v - 0x00280000;
            } else {
                state_arg->target_y = mid_pos->y.v + 0x00280000;
            }
        }
    } else {
        state_arg->target_x = 0x03600000;
        state_arg->target_y = 0x03600000;
    }

    state_arg->previous_x = view_reference_entity.x.v;
    state_arg->previous_y = view_reference_entity.y.v;

    {
        s32 scaled_speed = spin_data->unk_14 / ((spin_data->kind << 8) + 0x300);
        s32 base_speed = scaled_speed + 0x40;
        speed_limit = ((3 - spin_data->kind) << 5) + base_speed;
    }

    phase = state_arg->phase;
    switch (phase) {

    case 0:
        value_idle = effect_arg->color.c.b;
        value_idle += (128 - value_idle) >> 1;
        effect_arg->color.c.b = value_idle;
        effect_arg->color.c.g = value_idle;
        effect_arg->color.c.r = value_idle;
        state_arg->unk_6C = 0x00080000;
        break;

    case 1:
        reduced_speed = (state_arg->phase_value.s + 16) >> 4;
        value_accel = state_arg->phase_value.u + reduced_speed;
        state_arg->phase_value.u = value_accel;
        if ((s16)value_accel > speed_limit) {
            state_arg->phase_value.u = speed_limit;
            state_arg->phase = 2;
        }
        effect_arg->angle_z += state_arg->phase_value.u;
        break;

    case 2:
        effect_arg->angle_z += speed_limit;
        if (distance >= 161 && view_reference_entity.y.v > 0x03600000 && spin_data->state == 5) {
            state_arg->phase_value.s = speed_limit;
            state_arg->phase = 3;
        }
        break;

    case 3:
        dx = effect_arg->angle_z & 0x7FF;
        if (dx >= 0x6AB) {
            spin_data->sector = 0;
        } else {
            dy = 0x155;
            distance = 4;
            sector_start = 0x554;
            for (; distance >= 0; distance--, sector_start -= dy) {
                if (dx >= sector_start) {
                    break;
                }
            }
            value_sector = distance & 1;
            if (value_sector) {
                spin_data->sector = 1;
            } else {
                spin_data->sector = 2;
            }
        }
        spin_data->angle.s = 0;

    case 4:
        if (spin_data->kind == 2) {
            dx = 6;
        } else {
            dx = 5;
        }
        value_decel = state_arg->phase_value.s >> dx;
        reduced_speed = state_arg->phase_value.u - value_decel;
        state_arg->phase_value.u = reduced_speed;
        effect_arg->angle_z += state_arg->phase_value.u;
        spin_data->angle.u += state_arg->phase_value.u;
        if (state_arg->phase_value.s < (1 << dx)) {
            state_arg->stop_ticks = 0;
            state_arg->phase = 5;
        }
        break;

    case 5:
        effect_arg->angle_z += state_arg->phase_value.u;
        spin_data->angle.u += state_arg->phase_value.u;
        value_stop = state_arg->stop_ticks + 1;
        state_arg->stop_ticks = value_stop;
        if ((value_stop & 3) == 0) {
            state_arg->phase_value.u -= 2;
        }
        if (state_arg->phase_value.s < 4) {
            state_arg->phase = 0;
        }
        break;

    case 6:
        state_arg->phase = 7;
        state_arg->phase_value.s = 0;

    case 7:
        for (dx = 0; dx < 3; dx++) {
            point.x = 122 + dx * 16;
            point.y = 6;
            icon_frame = (state_arg->phase_value.s >> 1) + dx;
            LoadImage(&point, (void *)((icon_frame % 3) * 32 + (u8 *)D_800245DC));
        }
        value_draw = state_arg->phase_value.u;
        state_arg->phase_value.u = value_draw + 1;
        if ((s16)value_draw >= 198) {
            state_arg->phase = 0;
        }

    }

    value_wrap = effect_arg->angle_z & 0xFFF;
    effect_arg->angle_z = value_wrap;
    if ((prev_angle >> 8) != ((u32)value_wrap >> 8)) {
        SD_Call(0x701);
    }
}
