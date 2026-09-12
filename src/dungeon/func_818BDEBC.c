#include "common.h"
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

extern void *D_80024008[];
extern u8 D_800DDC40[256];
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern s32 D_8008346C;
extern u32 D_800814A0;

extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_800A44E0(s32, s32, s32, s32);
extern u16 func_800BCB04(s32, s32, s32);
extern void func_80025344(EffectState *, Motion *);
extern void func_8002558C(EffectState *, Motion *);
extern void func_800A56E0(s32);
extern void func_80024024(void *, u8, void *);

#ifdef NON_MATCHING
#define do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3328; } while (0) ((v) = (s32)D_8006CCD8)
#define do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3318; } while (0) ((v) = (s32)D_8006CCE8)
#else
#define LOAD_TABLE_X_BASE(v) \
    do { (v) = 0x80070000;  (v) -= 0x3328; } while (0)
#define LOAD_TABLE_Y_BASE(v) \
    do { (v) = 0x80070000;  (v) -= 0x3318; } while (0)
#endif

/* Advance an effect toward its target or along its facing direction, then handle its timed states. */
void func_800256BC(EffectState *effect, Motion *effect_motion, register ColorPart *part) {
    EffectState *state = effect;
    register Motion *motion ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *owner;
    u8 *color_part = (u8 *)part;
    register void *owner_meta ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *owner_node;
    void *source_motion;
    void *target_motion;
    Position16 *source_pos;
    Position16 *target_pos;
    MotionWork work;
    s32 index;
    s32 state_index;
    u16 timer_value;
    s32 motion_x;
    s32 z_distance;
    s32 next_state;
    u32 color;
    register s32 x_distance ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 source_z;
    u16 ground_z;
    register s32 tile_x ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 tile_y;
    u32 table_page;
    register s32 table_base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s16 *table_x_entry;
    s16 *table_y_entry;
    u16 *update_x_entry;
    u16 *update_y_entry;
    s32 table_offset;
    register s32 update_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 probe_z ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 next_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s32 next_y;
    register s16 *direction_steps ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 direction_index;
    s32 offset_x;
    s32 offset_y;
    register s32 dest_x ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 end_tile_x;
    u16 end_tile_y;
    static void *const state_labels[] = {
        &&case_0, &&case_1, &&case_2, &&case_3,
        &&case_4, &&case_5, &&case_6
    };

    timer_value = state->timer;
    state_index = state->state;
    timer_value++;
    owner = state->owner;
    state->timer = timer_value;
    motion = effect_motion;

    if ((u32)state_index >= 7) {
        goto case_6;
    }
    goto *D_80024008[state_index];

case_0:
    color = 0x00808080;
    state->timer = 0;
    state->state++;
    state->direction = (U16_AT(owner, 0x2A) >> 9) & 7;
    S32_AT(color_part, 0xC) = color;
    ASM_KEEP(color_part);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

    owner_meta = (u8 *)owner - 0x20;
    owner_node = PTR_AT(owner_meta, 0xC);
    if (!func_8003DE58(PTR_AT(owner_node, 8), owner_node, work.probe_delta, 0)) {
        if (!(U16_AT(PTR_AT(owner_meta, 0xC), 0x14) & 0x8000)) {
            goto case_6;
        }
    }

    source_motion = PTR_AT(owner_meta, 8);
    source_pos = (Position16 *)source_motion;
    S16_AT(motion, 2) = source_pos->x;
    S16_AT(motion, 6) = source_pos->y;
    source_z = source_pos->z;
    S16_AT(motion, 0xA) = source_z;

    if (!(U16_AT(PTR_AT(owner_meta, 0xC), 0x14) & 0x8000)) {
        S16_AT(motion, 2) += work.probe_delta[0];
        S16_AT(motion, 6) += work.probe_delta[1];
        S16_AT(motion, 0xA) = S16_AT(motion, 0xA) + work.probe_delta[2];
    } else {
        S16_AT(motion, 0xA) = source_z - 0x40;
    }
    if (!(U16_AT(state->image, 0) & 0x80)) {
        goto case_6;
    }

    index = 1;
    if (PTR_AT(owner, 0x60) != 0) {
        state->target = PTR_AT(owner, 0x60);
        target_motion = PTR_AT(PTR_AT(owner, 0x60), -0x18);

        motion_x = S16_AT(motion, 2);
        x_distance = S16_AT(target_motion, 2) - motion_x;
        x_distance = abs(x_distance);
        work.probe_delta[0] = x_distance;

        {
            s32 y_delta = S16_AT(target_motion, 6);
            s32 motion_y = S16_AT(motion, 6);
               /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            color_part = (u8 *)&work.destination + 2;
            y_delta -= motion_y;
            y_delta = abs(y_delta);
            work.probe_delta[1] = y_delta;
        }

        z_distance = S16_AT(target_motion, 0xA) -
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

        motion->dx = (S32_AT(target_motion, 0) - motion->x) / state->duration;
        motion->dy = (S32_AT(target_motion, 4) - motion->y) / state->duration;
        motion->dz = (S32_AT(target_motion, 8) -
                      (((D_800DDC40[U8_AT(state->target, 0x13)] >> 1) * 3) << 16) -
                      motion->z) / state->duration;
        func_80025344(state, motion);
        next_state = (u16)state->state + 1;
        goto set_state;
    }

    index = 0;
    {
        void *tile_node;
        tile_node = PTR_AT(owner_meta, 0xC);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        table_page = 0x80070000;
        ASM_KEEP(table_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        tile_x = U8_AT(tile_node, 0x24);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        tile_y = U8_AT(tile_node, 0x25);
    }
    end_tile_x = tile_x;
    end_tile_y = tile_y;

    do {
        if ((s16)func_800A44E0(((s16)tile_x << 6) & 0xFFC0,
                               ((s16)tile_y << 6) & 0xFFC0,
                               S16_AT(owner, 0x88),
                               (s16)(state->direction << 9)) != 0) {
            break;
        }

        (table_base) = 0x80070000; ASM_KEEP(table_base); (table_base) -= 0x3328;
           /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        table_offset = (s16)state->direction;
        probe_z = U16_AT(owner, 0x88);
        table_offset *= 2;
        table_x_entry = (s16 *)(table_offset + table_base);
        ASM_KEEP(table_x_entry);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        probe_z -= 0x20;
        probe_z = (s16)probe_z;
        (table_base) = 0x80070000; ASM_KEEP(table_base); (table_base) -= 0x3318;
        table_y_entry = (s16 *)(table_offset + table_base);
        ASM_KEEP(table_y_entry);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ground_z = func_800BCB04(
            (((s16)tile_x + *table_x_entry) << 6) + 0x20 & 0xFFE0,
            (((s16)tile_y + *table_y_entry) << 6) + 0x20 & 0xFFE0,
            probe_z);

        if ((s16)ground_z > 0x200) {
            break;
        }
        if ((s16)(ground_z - U16_AT(owner, 0x88)) < -0x3F) {
            break;
        }

        (table_base) = 0x80070000; ASM_KEEP(table_base); (table_base) -= 0x3328;
        update_offset = (s16)state->direction;
        index++;
        update_offset *= 2;
        update_x_entry = (u16 *)(update_offset + table_base);
        (table_base) = 0x80070000; ASM_KEEP(table_base); (table_base) -= 0x3318;
        update_y_entry = (u16 *)(update_offset + table_base);
        ASM_KEEP(update_y_entry);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        next_x = tile_x + *update_x_entry;
        tile_x = next_x;
        next_y = tile_y + *update_y_entry;
        tile_y = next_y;
        end_tile_y = next_y;
        ASM_KEEP4_NV(next_x, next_y, tile_x, tile_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        end_tile_x = next_x;
    } while (index < 8);

    target_pos = (Position16 *)&work.destination;
    ASM_KEEP_NV(target_pos);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    index = 1;
    x_distance = (u32)end_tile_x << 16;
    direction_steps = D_8006CCD8;
    x_distance = (s32)x_distance >> 10;
    direction_index = (s16)state->direction;
    color_part = (u8 *)&work.destination + 2;
    offset_x = direction_steps[direction_index];
    direction_steps = D_8006CCE8;
    dest_x = x_distance + ((offset_x + 1) << 5);
    target_pos->x = dest_x;
    dest_x = (s16)dest_x;
    ASM_KEEP(dest_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    table_base = end_tile_y;
    direction_index = (s16)state->direction;
    ASM_KEEP_DEP_NV(table_base, direction_index);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    next_x = (u32)(u16)table_base << 16;
    offset_y = direction_steps[direction_index];
    next_x = (s32)next_x >> 10;
    next_x += (offset_y + 1) << 5;
    target_pos->y = next_x;
    next_x = (u32)next_x << 16;
    next_y = U16_AT(motion, 0xA) + 0x20;
    target_pos->z = next_y;

    {
        s32 motion_coord;

        motion_coord = S16_AT(motion, 2);
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        next_x = (s32)next_x >> 16;
        dest_x -= motion_coord;
        dest_x = abs(dest_x);
        work.probe_delta[0] = dest_x;

        motion_coord = S16_AT(motion, 6);
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        next_y = (u32)next_y << 16;
        next_x -= motion_coord;
        next_x = abs(next_x);
        work.probe_delta[1] = next_x;

        motion_coord = S16_AT(motion, 0xA);
        next_y = (s32)next_y >> 16;
        next_y -= motion_coord;
        next_y = abs(next_y);
        work.probe_delta[2] = next_y;
    }

    x_distance = dest_x;
    state->duration = x_distance;
    do {
        if (S16_AT(color_part, 0x18) > state->duration) {
            state->duration = (u16)S16_AT(color_part, 0x18);
        }
        index++;
        color_part += 2;
    } while (index < 3);
    state->duration = (s16)state->duration >> 4;
    if (state->duration == 0) {
        state->duration = 1;
    }

    motion->dx = (S32_AT(target_pos, 0) - motion->x) / state->duration;
    motion->dy = (S32_AT(target_pos, 4) - motion->y) / state->duration;
    motion->dz = (S32_AT(target_pos, 8) - motion->z) / state->duration;
    func_8002558C(state, motion);
    next_state = 6;
    goto set_state;

case_1:
    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    if (state->timer < state->duration) {
        goto case_6;
    }
    func_800A56E0(0x300);
    state->state++;
    state->timer = 0;
    goto case_6;

case_2:
    if (state->timer < 0x10) {
        goto case_6;
    }
    state->state++;
    state->timer = 0;
    goto case_6;

case_3:
    if (state->timer < 0x30) {
        goto case_6;
    }
    func_80024024(PTR_AT(owner, 0x60), state->id, owner);
    state->state++;
    state->timer = 0;
    goto case_6;

case_4:
    if (state->done != 0) {
        goto case_6;
    }
    D_8008346C = 0;
    U16_AT(state, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
    goto case_6;

case_5:
    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    if (state->timer >= state->duration) {
        next_state = 5;
        goto set_state;
    }
    goto case_6;

set_state:
    state->state = next_state;
    state->timer = 0;
case_6:
    state->done = 0;
}
