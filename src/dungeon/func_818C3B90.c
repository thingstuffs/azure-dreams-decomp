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
#define do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3328; } while (0) ((v) = (s32)D_8006CCD8)
#define do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3318; } while (0) ((v) = (s32)D_8006CCE8)
#else
#define LOAD_TABLE_X_BASE(v) \
    do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3328; } while (0)
#define LOAD_TABLE_Y_BASE(v) \
    do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3318; } while (0)
#endif


/* Updates an owner-directed movement sequence and its timed action states. */
void func_818C3B90(State *action, Motion *motion_arg, Motion *aux_arg)
{
    static void *const state_labels[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6
    };
    register Motion *motion ASM_REG("$20") = motion_arg;
    Motion *aux_motion = aux_arg;
    register OwnerPrefix *prefix ASM_REG("$18");
    Owner *owner;
    s32 dispatch_state;
    s32 index;
    StackLocals stack;
    dispatch_state = action->state;
    owner = action->owner;
    action->timer++;
    if ((u32)dispatch_state >= 7) {
        goto done;
    }
    (void)state_labels;
    goto *D_80024008[(u32)dispatch_state];

jt_c0:
    {
        Motion *position;
        u16 position_z;

        action->timer = 0;
        action->state++;
        action->angle = (owner->flags >> 9) & 7;
        aux_motion->dx.val = 0x00808080;

jt_c1:
        prefix = (OwnerPrefix *)((u8 *)owner - 0x20);
        if (func_8003DE58(prefix->lookup->field8, prefix->lookup, stack.diffs, 0) == 0 &&
            !(prefix->lookup->flags & 0x8000)) {
            goto done;
        }

        position = prefix->position;
        motion->x.h.hi = position->x.h.hi;
        motion->y.h.hi = position->y.h.hi;
        position_z = position->z.h.hi;
        motion->z.h.hi = position_z;

        if (!(prefix->lookup->flags & 0x8000)) {
            s32 adjusted_z;
            motion->x.h.hi += stack.diffs[0];
            motion->y.h.hi += stack.diffs[1];
            ASM_SCHED_BARRIER();
            adjusted_z = (u16)motion->z.h.hi;
            adjusted_z += (u16)stack.diffs[2];
            ASM_TAILSLOT_PIN_TIED(adjusted_z);
            func_800254EC();
        }
        ASM_KEEP(position_z);
        motion->z.h.hi = position_z - 64;
    }

    if (*(u16 *)action->field4 & 0x80) {
        index = 1;
        if (owner->target != 0) {
            register Motion *target ASM_REG("$7");
            register s32 x_delta ASM_REG("$4");
            s32 axis_delta;
            s32 coord;
            register u8 *delta_iter ASM_REG("$5");

            target = *(Motion **)((u8 *)owner->target - 24);
            axis_delta = motion->x.h.hi;
            x_delta = target->x.h.hi - axis_delta;
            if (x_delta < 0) {
                x_delta = -x_delta;
            }
            stack.diffs[0] = x_delta;
            axis_delta = target->y.h.hi;
            coord = motion->y.h.hi;
            axis_delta -= coord;
            if (axis_delta < 0) {
                axis_delta = -axis_delta;
            }
            stack.diffs[1] = axis_delta;
            delta_iter = (u8 *)&stack.local + 2;
            coord = motion->z.h.hi;
            axis_delta = *(s16 *)((u8 *)owner->target + 0x88) - coord;
            ASM_SCHED_BARRIER();
            if (axis_delta < 0) {
                axis_delta = -axis_delta;
            }
            stack.diffs[2] = axis_delta;

            action->duration = x_delta;
            do {
                s32 signed_delta = *(s16 *)(delta_iter + 24);
                u32 delta_bits = *(u16 *)(delta_iter + 24);
                if (signed_delta > action->duration) {
                    action->duration = delta_bits;
                }
                index++;
                delta_iter += 2;
            } while (index < 3);
            action->duration = action->duration >> 4;
            if (action->duration == 0) {
                action->duration = 1;
            }

            motion->dx.val = (target->x.val - motion->x.val) / action->duration;
            motion->dy.val = (target->y.val - motion->y.val) / action->duration;
            motion->dz.val =
                ((*(s16 *)((u8 *)owner->target + 0x88) << 16) - motion->z.val) /
                action->duration;
            func_80024F0C(action, motion);
            {
                s32 next_state;
                next_state = (u16)action->state + 1;
                ASM_TAILSLOT_PIN_TIED(next_state);
                func_80025A50();
            }
        } else {
            register s32 grid_x ASM_REG("$21");
            s32 grid_y;
            s32 saved_x;
            Motion *destination;
            register s32 coord_work ASM_REG("$4");
            s32 coord_aux;
            register s32 x_work ASM_REG("$5");
            register s16 *table ASM_REG("$3");
            register u8 *delta_iter ASM_REG("$6");
            register s32 table_work ASM_REG("$8");
            s16 *table_x_entry;
            s16 *table_y_entry;
            u16 *update_x_entry;
            u16 *update_y_entry;
            register s32 probe_z ASM_REG("$6");
            s32 table_offset;
            register s32 update_offset ASM_REG("$3");
            s16 probe_result;

            index = 0;
            table = (s16 *)prefix->lookup;
            ASM_SCHED_BARRIER();
            coord_aux = 0x80070000;
            ASM_KEEP(coord_aux);
            grid_x = ((Lookup *)table)->x;
            grid_y = ((Lookup *)table)->y;
            saved_x = grid_x;
            ASM_SCHED_BARRIER();
            stack.accum_y = grid_y;

            for (; index < 8;) {
                s16 tile_x;
                s16 tile_y;
                s32 probe;

                tile_x = grid_x;
                tile_y = grid_y;
                probe = func_800A44E0(
                    (tile_x << 6) & 0xFFC0,
                    (tile_y << 6) & 0xFFC0,
                    owner->z,
                    (s32)((u32)(u16)action->angle << 25) >> 16);
                if ((s16)probe != 0) {
                    break;
                }

                do { (table_work) = 0x80070000; ASM_KEEP(table_work); (table_work) -= 0x3328; } while (0);
                ASM_KEEP(table_work);
                table_offset = (s16)action->angle;
                probe_z = (u16)owner->z;
                table_offset *= 2;
                table_x_entry = (s16 *)(table_offset + table_work);
                ASM_KEEP(table_x_entry);
                probe_z -= 32;
                probe_z = (s16)probe_z;
                do { (table_work) = 0x80070000; ASM_KEEP(table_work); (table_work) -= 0x3318; } while (0);
                table_y_entry = (s16 *)(table_offset + table_work);
                ASM_KEEP(table_y_entry);
                probe_result = func_800BCB04(
                    ((tile_x + *table_x_entry) * 64 + 32) & 0xFFE0,
                    ((tile_y + *table_y_entry) * 64 + 32) & 0xFFE0,
                    probe_z);
                if (probe_result >= 513 ||
                    (s16)(probe_result - (u16)owner->z) < -63) {
                    break;
                }

                do { (table_work) = 0x80070000; ASM_KEEP(table_work); (table_work) -= 0x3328; } while (0);
                update_offset = (s16)action->angle;
                index++;
                update_offset *= 2;
                update_x_entry = (u16 *)(update_offset + table_work);
                do { (table_work) = 0x80070000; ASM_KEEP(table_work); (table_work) -= 0x3318; } while (0);
                update_y_entry = (u16 *)(update_offset + table_work);
                ASM_KEEP(update_y_entry);
                coord_work = grid_x + *update_x_entry;
                grid_x = coord_work;
                coord_aux = grid_y + *update_y_entry;
                grid_y = coord_aux;
                stack.accum_y = coord_aux;
                ASM_KEEP4_NV(coord_work, coord_aux, grid_x, grid_y);
                saved_x = coord_work;
            }

            destination = &stack.local;
            ASM_KEEP_NV(destination);
            index = 1;
            ASM_KEEP_NV(index);
            x_work = (u32)saved_x << 16;
            table = D_8006CCD8;
            x_work = (s32)x_work >> 10;
            delta_iter = (u8 *)&stack.local + 2;
            x_work += (table[action->angle] + 1) << 5;
            destination->x.h.hi = x_work;
            x_work = (s16)x_work;
            coord_work = (s32)((u32)(u16)(table_work = stack.accum_y) << 16) >> 10;
            table = D_8006CCE8;
            coord_work += (table[action->angle] + 1) << 5;
            destination->y.h.hi = coord_work;
            coord_work = (u32)coord_work << 16;
            coord_aux = (u16)motion->z.h.hi + 32;
            destination->z.h.hi = coord_aux;

            {
                s32 coord;

                coord = motion->x.h.hi;
                ASM_SCHED_BARRIER();
                coord_work = (s32)coord_work >> 16;
                ASM_SCHED_BARRIER();
                x_work -= coord;
                if (x_work < 0) {
                    x_work = -x_work;
                }
                stack.diffs[0] = x_work;

                coord = motion->y.h.hi;
                ASM_SCHED_BARRIER();
                coord_aux = (u32)coord_aux << 16;
                ASM_SCHED_BARRIER();
                coord_work -= coord;
                if (coord_work < 0) {
                    coord_work = -coord_work;
                }
                stack.diffs[1] = coord_work;

                coord = motion->z.h.hi;
                coord_aux = (s32)coord_aux >> 16;
                coord_aux -= coord;
                if (coord_aux < 0) {
                    coord_aux = -coord_aux;
                }
                stack.diffs[2] = coord_aux;
            }

            action->duration = x_work;
            do {
                s32 signed_delta = *(s16 *)(delta_iter + 24);
                u32 delta_bits = *(u16 *)(delta_iter + 24);
                if (signed_delta > action->duration) {
                    action->duration = delta_bits;
                }
                index++;
                delta_iter += 2;
            } while (index < 3);
            action->duration = action->duration >> 4;
            if (action->duration == 0) {
                action->duration = 1;
            }

            motion->dx.val = (destination->x.val - motion->x.val) / action->duration;
            motion->dy.val = (destination->y.val - motion->y.val) / action->duration;
            motion->dz.val = (destination->z.val - motion->z.val) / action->duration;
            func_8002523C(action, motion);
            {
                s32 next_state;
                next_state = 6;
                ASM_TAILSLOT_PIN_TIED(next_state);
                func_80025A50();
            }
        }
    }
    goto done;

jt_c2:
    motion->x.val += motion->dx.val;
    motion->y.val += motion->dy.val;
    motion->z.val += motion->dz.val;
    if (action->timer >= action->duration) {
        func_800A56E0(0x300);
        func_800259BC();
    }
    goto done;

jt_c3:
    if (action->timer >= 12) {
        func_80024640(action, motion);
        func_800259BC();
    }
    goto done;

jt_c4:
    if (action->timer >= 49) {
        func_80024024(owner->target, action->byte9, owner);
        action->timer = 0;
        action->state++;
        func_80025A58();
    }
    goto done;

jt_c5:
    if (action->fieldC == 0) {
        D_8008346C[0] = 0;
        *(u16 *)((u8 *)action - 2) |= 0x8000;
        D_800814A0.value |= 0x8000;
        func_80025A58();
    }
    goto done;

jt_c6:
    motion->x.val += motion->dx.val;
    motion->y.val += motion->dy.val;
    motion->z.val += motion->dz.val;
    if (action->timer >= action->duration) {
        action->state = 5;
        action->timer = 0;
    }
done:
    action->fieldC = 0;
}

#undef LOAD_TABLE_X_BASE
#undef LOAD_TABLE_Y_BASE
