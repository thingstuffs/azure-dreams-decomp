#include "common.h"

typedef union Fixed32 {
    s32 val;
    struct {
        u16 lo;
        s16 hi;
    } h;
} Fixed32;

typedef struct Motion {
    Fixed32 x;
    Fixed32 y;
    Fixed32 z;
    Fixed32 dx;
    Fixed32 dy;
    Fixed32 dz;
} Motion;

typedef struct Owner {
    u8 pad0[0x2A];
    u16 flags;
    u8 pad2C[0x34];
    void *target;
    u8 pad64[0x24];
    s16 z;
} Owner;

typedef struct State {
    Owner *owner;
    void *field4;
    u8 pad8;
    u8 byte9;
    s16 state;
    s16 fieldC;
    s16 fieldE;
    s16 angle;
    s16 timer;
    s16 duration;
} State;

typedef struct Lookup {
    u8 pad0[8];
    void *field8;
    u8 padC[8];
    u16 flags;
    u8 pad16[14];
    u8 x;
    u8 y;
} Lookup;

typedef struct OwnerPrefix {
    u8 pad0[8];
    Motion *position;
    Lookup *lookup;
} OwnerPrefix;

typedef struct LargeInt {
    s32 value;
    s32 pad[2];
} LargeInt;

typedef struct StackLocals {
    Motion local;
    s16 diffs[3];
    u16 pad;
    u16 accum_y;
} StackLocals;

extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern s32 D_8008346C[3];
extern LargeInt D_800814A0;
extern void *D_80024008[];

extern s32 func_8003DE58(void *, Lookup *, s16 *, s32);
extern void func_80024F0C(State *, Motion *);
extern s32 func_800A44E0(s32, s32, s16, s32);
extern s32 func_800BCB04(s32, s32, s16);
extern void func_8002523C(State *, Motion *);
extern void func_800A56E0(s32);
extern void func_80024640(State *, Motion *);
extern void func_80024024(void *, u8, Owner *);

extern void func_800254EC(void) __attribute__((noreturn));
extern void func_80025A50(void) __attribute__((noreturn));
extern void func_800259BC(void) __attribute__((noreturn));
extern void func_80025A58(void) __attribute__((noreturn));

#ifdef NON_MATCHING
#define LOAD_TABLE_X_BASE(v) ((v) = (s32)D_8006CCD8)
#define LOAD_TABLE_Y_BASE(v) ((v) = (s32)D_8006CCE8)
#else
#define LOAD_TABLE_X_BASE(v) \
    do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3328; } while (0)
#define LOAD_TABLE_Y_BASE(v) \
    do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3318; } while (0)
#endif

#define local stack.local
#define diffs stack.diffs
#define accum_y stack.accum_y

/* Updates the effect state, moving toward its target or a reachable tile ahead. */
void func_818C3B90(State *effect, Motion *motion_arg, Motion *display_arg)
{
    static void *const state_labels[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6
    };
    register Motion *motion ASM_REG("$20") = motion_arg;
    Motion *display = display_arg;
    register OwnerPrefix *owner_prefix ;
    Owner *owner;
    s32 phase;
    s32 next_state;
    s32 index;
    StackLocals stack;
    phase = effect->state;
    owner = effect->owner;
    effect->timer++;
    if ((u32)phase >= 7) {
        goto done;
    }
    (void)state_labels;
    goto *D_80024008[(u32)phase];

jt_c0:
    {
        Motion *position;
        u16 position_z;

        effect->timer = 0;
        effect->state++;
        effect->angle = (owner->flags >> 9) & 7;
        display->dx.val = 0x00808080;

jt_c1:
        owner_prefix = (OwnerPrefix *)((u8 *)owner - 0x20);
        if (func_8003DE58(owner_prefix->lookup->field8, owner_prefix->lookup, diffs, 0) == 0 &&
            !(owner_prefix->lookup->flags & 0x8000)) {
            goto done;
        }

        position = owner_prefix->position;
        motion->x.h.hi = position->x.h.hi;
        motion->y.h.hi = position->y.h.hi;
        position_z = position->z.h.hi;
        motion->z.h.hi = position_z;

        if (!(owner_prefix->lookup->flags & 0x8000)) {
            s32 adjusted_z;
            motion->x.h.hi += diffs[0];
            motion->y.h.hi += diffs[1];
            ASM_SCHED_BARRIER();
            adjusted_z = (u16)motion->z.h.hi;
            adjusted_z += (u16)diffs[2];
            motion->z.h.hi = adjusted_z;
        } else {

            motion->z.h.hi = position_z - 64;
        }
    }

    if (*(u16 *)effect->field4 & 0x80) {
        index = 1;
        if (owner->target != 0) {
            register Motion *target ASM_REG("$7");
            register s32 x_diff ASM_REG("$4");
            s32 axis_diff;
            s32 current_coord;
            register u8 *diff_cursor ASM_REG("$5");

            target = *(Motion **)((u8 *)owner->target - 24);
            axis_diff = motion->x.h.hi;
            x_diff = target->x.h.hi - axis_diff;
            if (x_diff < 0) {
                x_diff = -x_diff;
            }
            diffs[0] = x_diff;
            axis_diff = target->y.h.hi;
            current_coord = motion->y.h.hi;
            axis_diff -= current_coord;
            if (axis_diff < 0) {
                axis_diff = -axis_diff;
            }
            diffs[1] = axis_diff;
            diff_cursor = (u8 *)&local + 2;
            current_coord = motion->z.h.hi;
            axis_diff = *(s16 *)((u8 *)owner->target + 0x88) - current_coord;
            ASM_SCHED_BARRIER();
            if (axis_diff < 0) {
                axis_diff = -axis_diff;
            }
            diffs[2] = axis_diff;

            effect->duration = x_diff;
            do {
                s32 axis_distance = *(s16 *)(diff_cursor + 24);
                u32 distance_bits = *(u16 *)(diff_cursor + 24);
                if (axis_distance > effect->duration) {
                    effect->duration = distance_bits;
                }
                index++;
                diff_cursor += 2;
            } while (index < 3);
            effect->duration = effect->duration >> 4;
            if (effect->duration == 0) {
                effect->duration = 1;
            }

            motion->dx.val = (target->x.val - motion->x.val) / effect->duration;
            motion->dy.val = (target->y.val - motion->y.val) / effect->duration;
            motion->dz.val =
                ((*(s16 *)((u8 *)owner->target + 0x88) << 16) - motion->z.val) /
                effect->duration;
            func_80024F0C(effect, motion);
            next_state = (u16)effect->state + 1;
            goto set_state;
        } else {
            register s32 x ASM_REG("$21");
            s32 y;
            s32 saved_x;
            Motion *destination;
            register s32 next_x ASM_REG("$4");
            s32 next_y;
            register s32 work_x ASM_REG("$5");
            register s16 *table ASM_REG("$3");
            register u8 *diff_cursor ASM_REG("$6");
            register s32 table_base ASM_REG("$8");
            s16 *table_x_entry;
            s16 *table_y_entry;
            u16 *update_x_entry;
            u16 *update_y_entry;
            register s32 probe_z ASM_REG("$6");
            s32 table_offset;
            register s32 update_offset ASM_REG("$3");
            s16 floor_z;

            index = 0;
            table = (s16 *)owner_prefix->lookup;
            ASM_SCHED_BARRIER();
            next_y = 0x80070000;
            ASM_KEEP(next_y);
            x = ((Lookup *)table)->x;
            y = ((Lookup *)table)->y;
            saved_x = x;
            ASM_SCHED_BARRIER();
            accum_y = y;

            for (; index < 8;) {
                s16 tile_x;
                s16 tile_y;
                s32 blocked;

                tile_x = x;
                tile_y = y;
                blocked = func_800A44E0(
                    (tile_x << 6) & 0xFFC0,
                    (tile_y << 6) & 0xFFC0,
                    owner->z,
                    (s32)((u32)(u16)effect->angle << 25) >> 16);
                if ((s16)blocked != 0) {
                    break;
                }

                LOAD_TABLE_X_BASE(table_base);
                ASM_KEEP(table_base);
                table_offset = (s16)effect->angle;
                probe_z = (u16)owner->z;
                table_offset *= 2;
                table_x_entry = (s16 *)(table_offset + table_base);
                ASM_KEEP(table_x_entry);
                probe_z -= 32;
                probe_z = (s16)probe_z;
                LOAD_TABLE_Y_BASE(table_base);
                table_y_entry = (s16 *)(table_offset + table_base);
                ASM_KEEP(table_y_entry);
                floor_z = func_800BCB04(
                    ((tile_x + *table_x_entry) * 64 + 32) & 0xFFE0,
                    ((tile_y + *table_y_entry) * 64 + 32) & 0xFFE0,
                    probe_z);
                if (floor_z >= 513 ||
                    (s16)(floor_z - (u16)owner->z) < -63) {
                    break;
                }

                LOAD_TABLE_X_BASE(table_base);
                update_offset = (s16)effect->angle;
                index++;
                update_offset *= 2;
                update_x_entry = (u16 *)(update_offset + table_base);
                LOAD_TABLE_Y_BASE(table_base);
                update_y_entry = (u16 *)(update_offset + table_base);
                ASM_KEEP(update_y_entry);
                next_x = x + *update_x_entry;
                x = next_x;
                next_y = y + *update_y_entry;
                y = next_y;
                accum_y = next_y;
                ASM_KEEP4_NV(next_x, next_y, x, y);
                saved_x = next_x;
            }

            destination = &local;
            ASM_KEEP_NV(destination);
            index = 1;
            ASM_KEEP_NV(index);
            work_x = (u32)saved_x << 16;
            table = D_8006CCD8;
            work_x = (s32)work_x >> 10;
            diff_cursor = (u8 *)&local + 2;
            work_x += (table[effect->angle] + 1) << 5;
            destination->x.h.hi = work_x;
            work_x = (s16)work_x;
            next_x = (s32)((u32)(u16)(table_base = accum_y) << 16) >> 10;
            table = D_8006CCE8;
            next_x += (table[effect->angle] + 1) << 5;
            destination->y.h.hi = next_x;
            next_x = (u32)next_x << 16;
            next_y = (u16)motion->z.h.hi + 32;
            destination->z.h.hi = next_y;

            {
                s32 current_coord;

                current_coord = motion->x.h.hi;
                ASM_SCHED_BARRIER();
                next_x = (s32)next_x >> 16;
                ASM_SCHED_BARRIER();
                work_x -= current_coord;
                if (work_x < 0) {
                    work_x = -work_x;
                }
                diffs[0] = work_x;

                current_coord = motion->y.h.hi;
                ASM_SCHED_BARRIER();
                next_y = (u32)next_y << 16;
                ASM_SCHED_BARRIER();
                next_x -= current_coord;
                if (next_x < 0) {
                    next_x = -next_x;
                }
                diffs[1] = next_x;

                current_coord = motion->z.h.hi;
                next_y = (s32)next_y >> 16;
                next_y -= current_coord;
                if (next_y < 0) {
                    next_y = -next_y;
                }
                diffs[2] = next_y;
            }

            effect->duration = work_x;
            do {
                s32 axis_distance = *(s16 *)(diff_cursor + 24);
                u32 distance_bits = *(u16 *)(diff_cursor + 24);
                if (axis_distance > effect->duration) {
                    effect->duration = distance_bits;
                }
                index++;
                diff_cursor += 2;
            } while (index < 3);
            effect->duration = effect->duration >> 4;
            if (effect->duration == 0) {
                effect->duration = 1;
            }

            motion->dx.val = (destination->x.val - motion->x.val) / effect->duration;
            motion->dy.val = (destination->y.val - motion->y.val) / effect->duration;
            motion->dz.val = (destination->z.val - motion->z.val) / effect->duration;
            func_8002523C(effect, motion);
            next_state = 6;
            goto set_state;
        }
    }
    goto done;

jt_c2:
    motion->x.val += motion->dx.val;
    motion->y.val += motion->dy.val;
    motion->z.val += motion->dz.val;
    if (effect->timer >= effect->duration) {
        func_800A56E0(0x300);
        goto advance_state;
    }
    goto done;

jt_c3:
    if (effect->timer >= 12) {
        func_80024640(effect, motion);
        goto advance_state;
    }
    goto done;

jt_c4:
    if (effect->timer >= 49) {
        func_80024024(owner->target, effect->byte9, owner);
advance_state:
        effect->timer = 0;
        effect->state++;
        goto done;
    }
    goto done;

jt_c5:
    if (effect->fieldC == 0) {
        D_8008346C[0] = 0;
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0.value |= 0x8000;
        goto done;
    }
    goto done;

jt_c6:
    motion->x.val += motion->dx.val;
    motion->y.val += motion->dy.val;
    motion->z.val += motion->dz.val;
    if (effect->timer >= effect->duration) {
        next_state = 5;
set_state:
        effect->state = next_state;
        effect->timer = 0;
    }
done:
    effect->fieldC = 0;
}

#undef local
#undef diffs
#undef accum_y
#undef LOAD_TABLE_X_BASE
#undef LOAD_TABLE_Y_BASE
