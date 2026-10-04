#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
extern int abs(int);

typedef struct Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct MotionWork {
    Motion destination;
    s16 probe_delta[3];
} MotionWork;

typedef struct Vec3 {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct Position16 {
    u16 pad0;
    s16 x;
    u16 pad4;
    s16 y;
    u16 pad8;
    s16 z;
} Position16;

typedef struct EffectState {
    void *owner;
    void *image;
    u8 unk8;
    u8 id;
    s16 state;
    s16 unkC;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 done;
    s16 unk16;
    void *target;
} EffectState;

typedef struct ColorPart {
    u8 pad[0xC];
    u32 color;
} ColorPart;

#define U8_AT(p, n) (*(u8 *)((u8 *)(p) + (n)))
#define S16_AT(p, n) (*(s16 *)((u8 *)(p) + (n)))
#define U16_AT(p, n) (*(u16 *)((u8 *)(p) + (n)))
#define S32_AT(p, n) (*(s32 *)((u8 *)(p) + (n)))
#define PTR_AT(p, n) (*(void **)((u8 *)(p) + (n)))

extern u8 D_800DDC40[256];

extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_800A44E0(s32, s32, s32, s32);
extern u16 func_800BCB04(s32, s32, s32);
extern void func_80025344(EffectState *, Motion *);
extern void func_8002558C(EffectState *, Motion *);
extern void func_800A56E0(s32);
extern void func_80024024(void *, u8, void *);


/* Advance an effect toward its target or along its facing direction, then handle its timed states. */
s32 func_800256BC(EffectState *state, Motion *motion, register ColorPart *part) {
    void *owner;
    u8 *color_part = (u8 *)part;
    void *owner_meta;
    void *owner_node;
    void *source_motion;
    void *target_pos;
    Position16 *table_x_entry;
    MotionWork work;
    s32 index;
    s32 state_index;
    u16 timer_value;
    s32 motion_x;
    s32 z_distance;
    s32 next_state;
    u32 color;
    s32 x_distance;
    s16 source_z;
    u16 ground_z;
    u16 tile_x;
    u16 tile_y;
    s16 grid_x;
    s16 grid_y;
    s16 *table_y_entry;
    s32 probe_z;
    s32 dest_x;
    s32 dest_y;
    u16 end_tile_x;
    u16 end_tile_y;
    timer_value = state->timer;
    state_index = state->state;
    timer_value++;
    owner = state->owner;
    state->timer = timer_value;

    switch (state_index) {
    case 0:
    color = 0x00808080;
    state->timer = 0;
    state->state++;
    state->direction = (U16_AT(owner, 0x2A) >> 9) & 7;
    S32_AT(color_part, 0xC) = color;

    case 1:
    owner_meta = (u8 *)owner - 0x20;
    owner_node = PTR_AT(owner_meta, 0xC);
    if (!func_8003DE58(PTR_AT(owner_node, 8), owner_node, work.probe_delta, 0)) {
        if (!(U16_AT(PTR_AT(owner_meta, 0xC), 0x14) & 0x8000)) {
            break;
        }
    }

    source_motion = PTR_AT(owner_meta, 8);
    table_x_entry = (Position16 *)source_motion;
    S16_AT(motion, 2) = table_x_entry->x;
    S16_AT(motion, 6) = table_x_entry->y;
    source_z = table_x_entry->z;
    S16_AT(motion, 0xA) = source_z;

    if (!(U16_AT(PTR_AT(owner_meta, 0xC), 0x14) & 0x8000)) {
        S16_AT(motion, 2) += work.probe_delta[0];
        S16_AT(motion, 6) += work.probe_delta[1];
        S16_AT(motion, 0xA) = S16_AT(motion, 0xA) + work.probe_delta[2];
    } else {
        S16_AT(motion, 0xA) = source_z - 0x40;
    }
    if (!(U16_AT(state->image, 0) & 0x80)) {
        break;
    }

    index = 1;
    if (PTR_AT(owner, 0x60) != 0) {
        state->target = PTR_AT(owner, 0x60);
        target_pos = PTR_AT(PTR_AT(owner, 0x60), -0x18);

        motion_x = S16_AT(motion, 2);
        x_distance = S16_AT(target_pos, 2) - motion_x;
        x_distance = abs(x_distance);
        work.probe_delta[0] = x_distance;

        {
            s32 y_delta = S16_AT(target_pos, 6);
            s32 motion_y = S16_AT(motion, 6);
            color_part = (u8 *)&work.destination + 2;
            y_delta -= motion_y;
            y_delta = abs(y_delta);
            work.probe_delta[1] = y_delta;
        }

        z_distance = S16_AT(target_pos, 0xA) -
                D_800DDC40[U8_AT(state->target, 0x13)] - S16_AT(motion, 0xA);
        z_distance = abs(z_distance);
        work.probe_delta[2] = z_distance;

        state->duration = x_distance;
        for (; index < 3; index++, color_part += 2) {
            if (S16_AT(color_part, 0x18) > state->duration) {
                state->duration = (u16)S16_AT(color_part, 0x18);
            }
        }
        state->duration = (s16)state->duration >> 4;
        if (state->duration == 0) {
            state->duration = 1;
        }

        motion->dx = (S32_AT(target_pos, 0) - motion->x) / state->duration;
        motion->dy = (S32_AT(target_pos, 4) - motion->y) / state->duration;
        motion->dz = (S32_AT(target_pos, 8) -
                      (((D_800DDC40[U8_AT(state->target, 0x13)] >> 1) * 3) << 16) -
                      motion->z) / state->duration;
        func_80025344(state, motion);
        next_state = (u16)state->state + 1;
    } else {
        index = 0;
        {
            void *tile_node;
            tile_node = PTR_AT(owner_meta, 0xC);
            tile_x = U8_AT(tile_node, 0x24);
            tile_y = U8_AT(tile_node, 0x25);
        }
        end_tile_x = tile_x;
        end_tile_y = tile_y;

        while (index < 8) {
            grid_x = (s16)tile_x;
            grid_y = (s16)tile_y;
            if ((s16)func_800A44E0((grid_x << 6) & 0xFFC0,
                                   (grid_y << 6) & 0xFFC0,
                                   S16_AT(owner, 0x88),
                                   (s16)(state->direction << 9)) != 0) {
                break;
            }
            table_x_entry = (Position16 *)&dirStepX[state->direction];
            probe_z = U16_AT(owner, 0x88);
            probe_z -= 0x20;
            probe_z = (u32)probe_z << 16;
            probe_z >>= 16;
            table_y_entry = &dirStepY[state->direction];
            ground_z = func_800BCB04(
                ((grid_x + *((s16 *)table_x_entry)) << 6) + 0x20 & 0xFFE0,
                ((grid_y + *table_y_entry) << 6) + 0x20 & 0xFFE0,
                probe_z);
            if ((s16)ground_z >= 0x201 || (s16)(ground_z - U16_AT(owner, 0x88)) < -0x3F) {
                break;
            }
            index++;
            tile_x += dirStepX[state->direction];
            tile_y += dirStepY[state->direction];
            end_tile_y = tile_y;
            end_tile_x = tile_x;
        }

        target_pos = (void *)((Position16 *)&work.destination);
        index = 1;
        color_part = (u8 *)&work.destination + 2;
        dest_x = ((end_tile_x << 16) >> 10) + ((dirStepX[state->direction] + 1) << 5);
        ((Position16 *)target_pos)->x = dest_x;
        dest_y = ((end_tile_y << 16) >> 10) + ((dirStepY[state->direction] + 1) << 5);
        ((Position16 *)target_pos)->y = dest_y;
        ((Position16 *)target_pos)->z = S16_AT(motion, 0xA) + 0x20;
        work.probe_delta[0] = abs(((Position16 *)target_pos)->x - S16_AT(motion, 2));
        work.probe_delta[1] = abs(((Position16 *)target_pos)->y - S16_AT(motion, 6));
        work.probe_delta[2] = abs(((Position16 *)target_pos)->z - S16_AT(motion, 0xA));

        state->duration = work.probe_delta[0];
        for (; index < 3; index++, color_part += 2) {
            if (S16_AT(color_part, 0x18) > state->duration) {
                state->duration = (u16)S16_AT(color_part, 0x18);
            }
        }
        state->duration = (s16)state->duration >> 4;
        if (state->duration == 0) {
            state->duration = 1;
        }

        motion->dx = (S32_AT((Position16 *)target_pos, 0) - motion->x) / state->duration;
        motion->dy = (S32_AT((Position16 *)target_pos, 4) - motion->y) / state->duration;
        motion->dz = (S32_AT((Position16 *)target_pos, 8) - motion->z) / state->duration;
        func_8002558C(state, motion);
        next_state = 6;
    }
    state->state = next_state;
    state->timer = 0;
    break;

    case 2:
    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    if (state->timer < state->duration) {
        break;
    }
    func_800A56E0(0x300);
    state->state++;
    state->timer = 0;
    break;

    case 3:
    if (state->timer < 0x10) {
        break;
    }
    state->state++;
    state->timer = 0;
    break;

    case 4:
    if (state->timer < 0x30) {
        break;
    }
    func_80024024(PTR_AT(owner, 0x60), state->id, owner);
    state->state++;
    state->timer = 0;
    break;

    case 5:
    if (state->done != 0) {
        break;
    }
    dungeonStatus.unk_0C = 0;
    U16_AT(state, -2) |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
    break;

    case 6:
    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    if (state->timer >= state->duration) {
        state->state = 5;
        state->timer = 0;
    }
    break;

    default:
        break;
    }
    state->done = 0;
}
