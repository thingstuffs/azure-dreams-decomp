#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
extern int abs(int);

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
} StackLocals;


extern s32 func_8003DE58(void *, Lookup *, s16 *, s32);
extern void func_80024F0C(State *, Motion *);
extern s32 func_800A44E0(s32, s32, s16, s32);
extern s32 func_800BCB04(s32, s32, s16);
extern void func_8002523C(State *, Motion *);
extern void func_800A56E0(s32);
extern void func_80024640(State *, Motion *);
extern void func_80024024(void *, u8, Owner *);


/* Updates an owner-directed movement sequence and its timed action states. */
void func_818C3B90(State *action, Motion *motion, Motion *aux_arg)
{
    Motion *aux_motion = aux_arg;
    OwnerPrefix *prefix;
    Owner *owner;
    s32 dispatch_state;
    s32 index;
    s32 next_state;
    StackLocals stack;
    Motion *position;
    u16 position_z;
    dispatch_state = action->state;
    owner = action->owner;
    action->timer++;
    switch (dispatch_state) {
    case 0:
        action->timer = 0;
        action->state++;
        action->angle = (owner->flags >> 9) & 7;
        aux_motion->dx.val = 0x00808080;

    case 1:
        prefix = (OwnerPrefix *)((u8 *)owner - 0x20);
        if (func_8003DE58(prefix->lookup->field8, prefix->lookup, stack.diffs, 0) == 0 &&
            !(prefix->lookup->flags & 0x8000)) {
            break;
        }

        position = prefix->position;
        motion->x.h.hi = position->x.h.hi;
        motion->y.h.hi = position->y.h.hi;
        position_z = position->z.h.hi;
        motion->z.h.hi = position_z;

        if (!(prefix->lookup->flags & 0x8000)) {
            s16 adjusted_z;
            motion->x.h.hi += stack.diffs[0];
            motion->y.h.hi += stack.diffs[1];
            adjusted_z = (u16)motion->z.h.hi;
            adjusted_z += (u16)stack.diffs[2];
            motion->z.h.hi = adjusted_z;
        } else {
            motion->z.h.hi = position_z - 64;
        }

        if (*(u16 *)action->field4 & 0x80) {
            Motion *target;
            if (owner->target != 0) {
                s32 x_delta;
                u8 *delta_iter;

                index = 1;

                target = *(Motion **)((u8 *)owner->target - 24);
                stack.diffs[0] = x_delta = abs(target->x.h.hi - motion->x.h.hi);
                stack.diffs[1] = abs(target->y.h.hi - motion->y.h.hi);
                stack.diffs[2] = abs(*(s16 *)((u8 *)owner->target + 0x88) - motion->z.h.hi);

                action->duration = x_delta;
                do {
                    s32 signed_delta;
                    u32 delta_bits;

                    delta_iter = (u8 *)&stack.local + index * 2;
                    signed_delta = *(s16 *)(delta_iter + 24);
                    delta_bits = *(u16 *)(delta_iter + 24);
                    if (signed_delta > action->duration) {
                        action->duration = delta_bits;
                    }
                    index++;
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
                next_state = (u16)action->state + 1;
            } else {
                u16 path_x;
                u16 path_y;
                s16 grid_x;
                s16 grid_y;
                u16 last_x;
                u16 saved_y;
                s32 probe_z;
                s16 *step_y;
                s32 floor_height;
                s32 dest_x;
                s32 dest_y;

                index = 0;
                path_x = prefix->lookup->x;
                path_y = prefix->lookup->y;
                last_x = path_x;
                saved_y = path_y;
                while (index < 8) {
                    grid_x = (s16)path_x;
                    grid_y = (s16)path_y;
                    if ((s16)func_800A44E0((grid_x << 6) & 0xFFC0, (grid_y << 6) & 0xFFC0, owner->z,
                            (s16)(action->angle << 9)) != 0) {
                        break;
                    }
                    position = (Motion *)&dirStepX[action->angle];
                    probe_z = (u16)owner->z;
                    probe_z -= 32;
                    probe_z = (u32)probe_z << 16;
                    probe_z >>= 16;
                    step_y = &dirStepY[action->angle];
                    floor_height = func_800BCB04(((grid_x + *(s16 *)position) << 6) + 32 & 0xFFE0,
                        ((grid_y + *step_y) << 6) + 32 & 0xFFE0, probe_z);
                    if ((s16)floor_height >= 513 || (s16)(floor_height - owner->z) < -63) {
                        break;
                    }
                    index++;
                    path_x += dirStepX[action->angle];
                    path_y += dirStepY[action->angle];
                    saved_y = path_y;
                    last_x = path_x;
                }

                target = &stack.local;
                index = 1;
                dest_x = ((last_x << 16) >> 10) + ((dirStepX[action->angle] + 1) << 5);
                target->x.h.hi = dest_x;
                dest_y = ((saved_y << 16) >> 10) + ((dirStepY[action->angle] + 1) << 5);
                target->y.h.hi = dest_y;
                target->z.h.hi = motion->z.h.hi + 32;
                stack.diffs[0] = abs(target->x.h.hi - motion->x.h.hi);
                stack.diffs[1] = abs(target->y.h.hi - motion->y.h.hi);
                stack.diffs[2] = abs(target->z.h.hi - motion->z.h.hi);

                action->duration = stack.diffs[0];
                do {
                    s32 signed_delta;
                    u32 delta_bits;
                    u8 *delta_iter;

                    delta_iter = (u8 *)&stack.local + index * 2;
                    signed_delta = *(s16 *)(delta_iter + 24);
                    delta_bits = *(u16 *)(delta_iter + 24);
                    if (signed_delta > action->duration) {
                        action->duration = delta_bits;
                    }
                    index++;
                } while (index < 3);
                action->duration = action->duration >> 4;
                if (action->duration == 0) {
                    action->duration = 1;
                }

                motion->dx.val = (target->x.val - motion->x.val) / action->duration;
                motion->dy.val = (target->y.val - motion->y.val) / action->duration;
                motion->dz.val = (target->z.val - motion->z.val) / action->duration;
                func_8002523C(action, motion);
                next_state = 6;
            }
            action->state = next_state;
            action->timer = 0;
        }
        break;

    case 2:
        motion->x.val += motion->dx.val;
        motion->y.val += motion->dy.val;
        motion->z.val += motion->dz.val;
        if (action->timer >= action->duration) {
            func_800A56E0(0x300);
            action->timer = 0;
            action->state++;
        }
        break;

    case 3:
        if (action->timer >= 12) {
            func_80024640(action, motion);
            action->timer = 0;
            action->state++;
        }
        break;

    case 4:
        if (action->timer >= 49) {
            func_80024024(owner->target, action->byte9, owner);
            action->timer = 0;
            action->state++;
        }
        break;

    case 5:
        if (action->fieldC == 0) {
            dungeonStatus.unk_0C = 0;
            *(u16 *)((u8 *)action - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        break;

    case 6:
        motion->x.val += motion->dx.val;
        motion->y.val += motion->dy.val;
        motion->z.val += motion->dz.val;
        if (action->timer >= action->duration) {
            action->state = 5;
            action->timer = 0;
        }
    }
    action->fieldC = 0;
}

