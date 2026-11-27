#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "town/scene/animation.h"
#include "town/data.h"
#define AZ_FOREIGN_LOCAL_FUNC_80071494
#include "town/devkit/old_minigame_imports.h"
#undef AZ_FOREIGN_LOCAL_FUNC_80071494

extern s32 func_80071494(); /* Unprototyped: JP identity rand(void); the surplus source arguments preserve the retail instruction stream. */

extern u8 D_8028E568[];
/* The selected entry starts at D_8028E568. Its next word supplies the sprite source. */
extern struct {
    void *source;
    u8 trailing_data[8];
} D_8028E56C;
extern u8 D_8028E590[];
extern u8 D_8028E600[];
extern u8 D_805266C0[];
extern u8 D_805266CC[];
extern u8 D_805266D8[];
extern u8 D_8053013C[];

typedef struct FallingTimedSceneObject {
    u8 pad_00[0x48];
    void * unk_48;
    u8 pad_4C[0x1C];
    s16 state;
    u8 pad_6A[0x2E];
    s8 * active_flag;
    u8 pad_9C[0x4];
    s16 phase;
    u16 timer;
    u16 flags;
    u16 step_duration;
    u8 pad_A8[0x4];
    FallingSceneController *owner;
} FallingTimedSceneObject;   /* obj in animate_falling_timed_object */


/* Per-frame step for the town cutscene actor: integrate its motion, then run its ten-state dispatch. */
void animate_falling_timed_object(FallingTimedSceneObject *obj, ObjectPosition *motion, SpriteFrameState *incoming_out) {
    FallingSceneController *aux;
    SpriteFrameState *out;
    void **entry_slot;
    u16 table[14];
    s32 a0;
    s32 a1;
    s32 value;
    s32 flag;
    s32 state;
    s16 phase_u16;
    u16 mode;
    s8 *ptr;

    aux = obj->owner;
    __builtin_memcpy(table, D_805266C0, 12);
    __builtin_memcpy(&table[8], D_805266CC, 12);

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    motion->z.v += motion->velocity_z;
    obj->timer = obj->timer - 1;
    aux->flags |= 1;

    state = obj->state;
    out = incoming_out;
    switch (state) {
    case 0:
    {
        s32 state0_flag;
        a1 = func_80071494() & 0xF;
        if (aux->count >= 25) {
            a1 = func_80071494() & 7;
            a0 = a1 + 14;
        } else {
            if (aux->count >= 19) {
                state0_flag = a1 < 3;
                if (state0_flag)
                    goto state0_small;
                state0_flag = a1 < 5;
            } else if (aux->count >= 7) {
                state0_flag = a1 < 4;
                if (state0_flag)
                    goto state0_small;
                state0_flag = a1 < 8;
            } else {
                state0_flag = a1 < 6;
                if (state0_flag) {
state0_small:
                    a1 = (0 - func_80071494()) & 3;
                    goto state0_finish;
                }
                state0_flag = a1 < 7;
            }
            a0 = a1 + 14;
            if (state0_flag) {
                a1 = (func_80071494(a0, a1) % 23) + 44;
state0_finish:
                a0 = a1 + 14;
            }
        }
        obj->timer = a0;
        obj->step_duration = a0;
        motion->velocity_y = (s32)0xFFC00000 / ((s16)(obj->timer));
        if (obj->phase < 2)
            out->flags |= 1;
        if (((u16)(obj->phase)) & 1) {
            out->depth_bias = -256;
            motion->velocity_y = 0 - motion->velocity_y;
        } else {
            out->depth_bias = -64;
            func_80034A1C(out, D_8028E600, 0);
        }
        obj->state = 1;
        break;
    }

    case 1:
    {
        s32 case1_value;
        if (((s16)(obj->timer)) <= 0) {
            motion->velocity_y = 0;
            phase_u16 = obj->step_duration;
            case1_value = (s32)0x800000 / (s16)(phase_u16 * 2);
            obj->timer = phase_u16 * 2;
            motion->velocity_x = case1_value;
            if (obj->phase < 2)
                motion->velocity_x = 0 - case1_value;
            func_80034A1C(out, D_8028E590, 0);
            obj->state = 2;
            break;
        }
        break;
    }

    case 2:
    {
        u16 phase;
        if (((s16)(obj->timer)) <= 0) {
            phase = obj->step_duration;
            obj->timer = phase;
            mode = ((u16)(obj->phase));
            value = (s32)0xFFC00000 / (s16)phase;
            if (mode & 1) {
                if ((s16)mode == 1)
                    a0 = value;
                else
                    a0 = 0 - value;
                motion->velocity_x = a0;
                motion->velocity_y = 0;
            } else {
                motion->velocity_x = 0;
                motion->velocity_y = value;
            }
            obj->state = 3;
            break;
        }
        break;
    }

    case 3:
        if (((s16)(obj->timer)) <= 0) {
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            motion->y.v += (s32)0xFFFC0000;
            entry_slot = &out->frame_entry;
            *entry_slot = D_8028E568;
            out->source = D_8028E56C.source;
            out->unk_04 = 0;
            out->frame_ticks = 0;
            if (func_80071494() & 7) {
                u16 phase3;
                /* BYTES: Redundant store retail really emits; the A6 load between the two A2 stores keeps cse from deleting the first store. */
                obj->timer = 16;
                phase3 = obj->step_duration;
                obj->timer = phase3;
                motion->velocity_z = ((s32)0xFF900000 - motion->z.v) / ((s16)phase3);
                obj->state = 4;
            } else {
                s32 pos;
                s32 acceleration;
                obj->timer = 12;
                acceleration = (func_80071494() & 0xFF) << 12;
                pos = motion->z.v;
                a0 = 0x580000;
                pos += a0;
                a0 = ((s16)(obj->timer));
                acceleration -= pos;
                acceleration /= a0;
                motion->velocity_z = acceleration;
                obj->state = 5;
            }
            break;
        }
        break;

    case 4:
        if (motion->z.v <= (s32)0xFFA80000 &&
            !(obj->flags & 2)) {
            out->depth_bias = 0;
            obj->unk_48 = D_805266D8;
            obj->flags |= 2;
            func_8023FA58(obj, motion, D_8053013C);
            aux->level.u += 1;
        }
        if (((s16)(obj->timer)) == 3) {
            entry_slot = &out->frame_entry;
            *entry_slot = D_8028E568;
            out->source = D_8028E56C.source;
            out->unk_04 = 0;
            out->frame_ticks = 0;
        }
        if (((s16)(obj->timer)) <= 0) {
            motion->velocity_z = 0;
            obj->state = 7;
            obj->timer = ((s16)(obj->step_duration)) * 2 + 20;
        }
        break;

    case 5:
        if (((s16)(obj->timer)) <= 0) {
            obj->timer = 6;
            motion->velocity_z = ((s32)0xFFD80000 - motion->z.v) /
                obj->timer;
            obj->state = 6;
        }
        break;

    case 6:
        if (((s16)(obj->timer)) <= 0) {
            obj->timer = 8;
            motion->velocity_z = ((s32)0xFF900000 - motion->z.v) / (obj->timer);
            obj->state = 4;
            break;
        }
        break;

    case 7:
    {
        SpriteFrameState *call_out;
        if (((s16)(obj->timer)) <= 0) {
            call_out = out;
            if (obj->phase & 1) {
                value = (s32)D_8028E590;
            } else {
                out->depth_bias = 64;
                value = (s32)D_8028E600;
            }
            func_80034A1C(call_out, (void *)value, 0);
            obj->flags &= 0xFFFD;
            aux->flags &= 0xFFFB;
            flag = ((u16)(obj->phase));
            obj->timer = 8;
            a1 = -0x80000;
            if (flag & 1) {
                a0 = a1;
                if ((s16)flag != 1)
                    a0 = 0x80000;
                motion->velocity_x = a0;
                motion->velocity_y = 0;
            } else {
                motion->velocity_x = 0;
                motion->velocity_y = a1;
            }
            obj->state = 8;
        }
        break;
    }

    case 8:
        if (((s16)(obj->timer)) <= 0) {
            func_8023FB18(obj);
            ptr = obj->active_flag;
            if (ptr != 0)
                *ptr = 0;
            func_80050D68(obj);
            {
                u16 *flags = &NODE_HEADER(obj)->flags;
                *flags |= 0x8000;
            }
            scene_object_flags |= 0x8000;
        }
        break;

    case 9:
    {
        s32 phase;
        phase = ((s16)(obj->timer));
        if (phase == 1) {
            func_80058F88(0x512);
            phase = ((s16)(obj->timer));
        }
        if (phase < 6) {
            out->scale_x = table[phase];
            out->scale_y = table[((s16)(obj->timer)) + 8];
        }
        if (((s16)(obj->timer)) <= 0)
            obj->state = 8;
        break;
    }
    default:
        break;
    }

    func_8003EA54(out);
    if ((obj->flags & 2) && func_80252550(D_8053013C, motion) != 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        {
            FallingSceneController *tail_aux = obj->owner;
            tail_aux->value.u += 1;
        }
        obj->flags &= 0xFFFD;
        entry_slot = &out->frame_entry;
        *entry_slot = D_8028E568;
        out->source = D_8028E56C.source;
        out->unk_04 = 0;
        out->frame_ticks = 0;
        obj->timer = 14;
        obj->state = 9;
    }
    return;
#undef obj
#undef motion
#undef out
}
