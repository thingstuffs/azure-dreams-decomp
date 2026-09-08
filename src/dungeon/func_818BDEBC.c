#include "common.h"

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
#define LOAD_TABLE_X_BASE(v) ((v) = (s32)D_8006CCD8)
#define LOAD_TABLE_Y_BASE(v) ((v) = (s32)D_8006CCE8)
#else
#define LOAD_TABLE_X_BASE(v) \
    do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3328; } while (0)
#define LOAD_TABLE_Y_BASE(v) \
    do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3318; } while (0)
#endif

void func_800256BC(EffectState *arg0, Motion *arg1, register ColorPart *part) {
    EffectState *state = arg0;
    register Motion *motion ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *owner;
    u8 *color_part = (u8 *)part;
    register void *meta ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *node;
    void *source;
    void *target;
    Position16 *source_pos;
    Position16 *target_pos;
    MotionWork work;
    s32 i;
    s32 state_index;
    u16 timer_value;
    s32 value;
    u32 color;
    register s32 first_delta ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 z;
    u16 ground;
    register s32 tile_x ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 tile_y;
    u32 dead_page;
    register s32 temp_t0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s16 *table_x_entry;
    s16 *table_y_entry;
    u16 *update_x_entry;
    u16 *update_y_entry;
    s32 table_offset;
    register s32 update_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 loop_owner_z ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 next_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s32 next_y;
    register s16 *table ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 out_idx;
    s32 offset_x;
    s32 offset_y;
    register s32 signed_x ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 work_x;
    s32 work_y;
    u16 saved_y;
    static void *const keepalive[] = {
        &&case_0, &&case_1, &&case_2, &&case_3,
        &&case_4, &&case_5, &&case_6
    };

    timer_value = state->timer;
    state_index = state->state;
    timer_value++;
    owner = state->owner;
    state->timer = timer_value;
    motion = arg1;

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

    meta = (u8 *)owner - 0x20;
    node = PTR_AT(meta, 0xC);
    if (!func_8003DE58(PTR_AT(node, 8), node, work.probe_delta, 0)) {
        if (!(U16_AT(PTR_AT(meta, 0xC), 0x14) & 0x8000)) {
            goto case_6;
        }
    }

    source = PTR_AT(meta, 8);
    source_pos = (Position16 *)source;
    S16_AT(motion, 2) = source_pos->x;
    S16_AT(motion, 6) = source_pos->y;
    z = source_pos->z;
    S16_AT(motion, 0xA) = z;

    if (!(U16_AT(PTR_AT(meta, 0xC), 0x14) & 0x8000)) {
        S16_AT(motion, 2) += work.probe_delta[0];
        S16_AT(motion, 6) += work.probe_delta[1];
        S16_AT(motion, 0xA) = S16_AT(motion, 0xA) + work.probe_delta[2];
    } else {
        S16_AT(motion, 0xA) = z - 0x40;
    }
    if (!(U16_AT(state->image, 0) & 0x80)) {
        goto case_6;
    }

    i = 1;
    if (PTR_AT(owner, 0x60) != 0) {
        state->target = PTR_AT(owner, 0x60);
        target = PTR_AT(PTR_AT(owner, 0x60), -0x18);

        value = S16_AT(motion, 2);
        first_delta = S16_AT(target, 2) - value;
        if (first_delta < 0) {
            first_delta = -first_delta;
        }
        work.probe_delta[0] = first_delta;

        {
        s32 y_delta = S16_AT(target, 6);
        register s32 y_rhs ASM_REG("$3") = S16_AT(motion, 6);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        color_part = (u8 *)&work.destination + 2;
        ASM_KEEP(color_part);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        y_delta -= y_rhs;
        if (y_delta < 0) {
            y_delta = -y_delta;
        }
        work.probe_delta[1] = y_delta;
        }

        value = S16_AT(target, 0xA) -
                D_800DDC40[U8_AT(state->target, 0x13)] - S16_AT(motion, 0xA);
        if (value < 0) {
            value = -value;
        }
        work.probe_delta[2] = value;

        state->duration = first_delta;
        for (; i < 3; i++, color_part += 2) {
            if (S16_AT(color_part, 0x18) > state->duration) {
                state->duration = (u16)S16_AT(color_part, 0x18);
            }
        }
        state->duration = (s16)state->duration >> 4;
        if (state->duration == 0) {
            state->duration = 1;
        }

        motion->dx = (S32_AT(target, 0) - motion->x) / state->duration;
        motion->dy = (S32_AT(target, 4) - motion->y) / state->duration;
        motion->dz = (S32_AT(target, 8) -
                      (((D_800DDC40[U8_AT(state->target, 0x13)] >> 1) * 3) << 16) -
                      motion->z) / state->duration;
        func_80025344(state, motion);
        value = (u16)state->state + 1;
        goto set_state;
    }

    i = 0;
    {
    void *tile_node;
    tile_node = PTR_AT(meta, 0xC);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    dead_page = 0x80070000;
    ASM_KEEP(dead_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    tile_x = U8_AT(tile_node, 0x24);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    tile_y = U8_AT(tile_node, 0x25);
    }
    work_x = tile_x;
    saved_y = tile_y;

    do {
        if ((s16)func_800A44E0(((s16)tile_x << 6) & 0xFFC0,
                               ((s16)tile_y << 6) & 0xFFC0,
                               S16_AT(owner, 0x88),
                               (s16)(state->direction << 9)) != 0) {
            break;
        }

        LOAD_TABLE_X_BASE(temp_t0);
        ASM_KEEP(temp_t0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        table_offset = (s16)state->direction;
        loop_owner_z = U16_AT(owner, 0x88);
        table_offset *= 2;
        table_x_entry = (s16 *)(table_offset + temp_t0);
        ASM_KEEP(table_x_entry);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        loop_owner_z -= 0x20;
        loop_owner_z = (s16)loop_owner_z;
        LOAD_TABLE_Y_BASE(temp_t0);
        table_y_entry = (s16 *)(table_offset + temp_t0);
        ASM_KEEP(table_y_entry);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ground = func_800BCB04(
            (((s16)tile_x + *table_x_entry) << 6) + 0x20 & 0xFFE0,
            (((s16)tile_y + *table_y_entry) << 6) + 0x20 & 0xFFE0,
            loop_owner_z);

        if ((s16)ground > 0x200) {
            break;
        }
        if ((s16)(ground - U16_AT(owner, 0x88)) < -0x3F) {
            break;
        }

        LOAD_TABLE_X_BASE(temp_t0);
        update_offset = (s16)state->direction;
        i++;
        update_offset *= 2;
        update_x_entry = (u16 *)(update_offset + temp_t0);
        LOAD_TABLE_Y_BASE(temp_t0);
        update_y_entry = (u16 *)(update_offset + temp_t0);
        ASM_KEEP(update_y_entry);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        next_x = tile_x + *update_x_entry;
        tile_x = next_x;
        next_y = tile_y + *update_y_entry;
        tile_y = next_y;
        saved_y = next_y;
        ASM_KEEP4_NV(next_x, next_y, tile_x, tile_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        work_x = next_x;
    } while (i < 8);

    target_pos = (Position16 *)&work.destination;
    ASM_KEEP_NV(target_pos);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    i = 1;
    ASM_KEEP_NV(i);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    first_delta = (u32)work_x << 16;
    table = D_8006CCD8;
    first_delta = (s32)first_delta >> 10;
    out_idx = (s16)state->direction;
    color_part = (u8 *)&work.destination + 2;
    offset_x = table[out_idx];
    table = D_8006CCE8;
    signed_x = first_delta + ((offset_x + 1) << 5);
    target_pos->x = signed_x;
    signed_x = (s16)signed_x;
    ASM_KEEP(signed_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_t0 = saved_y;
    out_idx = (s16)state->direction;
    ASM_KEEP_DEP_NV(temp_t0, out_idx);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    next_x = (u32)(u16)temp_t0 << 16;
    offset_y = table[out_idx];
    next_x = (s32)next_x >> 10;
    next_x += (offset_y + 1) << 5;
    target_pos->y = next_x;
    next_x = (u32)next_x << 16;
    next_y = U16_AT(motion, 0xA) + 0x20;
    target_pos->z = next_y;

    {
        s32 rhs;

        rhs = S16_AT(motion, 2);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        next_x = (s32)next_x >> 16;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        signed_x -= rhs;
        if (signed_x < 0) signed_x = -signed_x;
        work.probe_delta[0] = signed_x;

        rhs = S16_AT(motion, 6);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        next_y = (u32)next_y << 16;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        next_x -= rhs;
        if (next_x < 0) next_x = -next_x;
        work.probe_delta[1] = next_x;

        rhs = S16_AT(motion, 0xA);
        next_y = (s32)next_y >> 16;
        next_y -= rhs;
        if (next_y < 0) next_y = -next_y;
        work.probe_delta[2] = next_y;
    }

    first_delta = signed_x;
    state->duration = first_delta;
    do {
        if (S16_AT(color_part, 0x18) > state->duration) {
            state->duration = (u16)S16_AT(color_part, 0x18);
        }
        i++;
        color_part += 2;
    } while (i < 3);
    state->duration = (s16)state->duration >> 4;
    if (state->duration == 0) {
        state->duration = 1;
    }

    motion->dx = (S32_AT(target_pos, 0) - motion->x) / state->duration;
    motion->dy = (S32_AT(target_pos, 4) - motion->y) / state->duration;
    motion->dz = (S32_AT(target_pos, 8) - motion->z) / state->duration;
    func_8002558C(state, motion);
    value = 6;
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
        value = 5;
        goto set_state;
    }
    goto case_6;

set_state:
    state->state = value;
    state->timer = 0;
case_6:
    state->done = 0;
}
