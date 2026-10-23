#include "common.h"
#include "town/minigame/gym.h"
#include "shared/town_handler_entries.h"
#include "shared/object_flags.h"
#include "shared/entity.h"








extern ObjectPosition view_reference_entity;

extern void sound_set_cd_cue_parameters(s32, s32, s32, s32);
extern void SD_Call(s32);
extern void apply_global_scene_value(void *);

/* Update object motion, scoring, and timed state transitions. */
void update_gym_score_object(GymScoreObject *obj, ObjectPosition *motion)
{
    GymState *child;
    s16 ticks_left;
    u16 state;

    child = obj->child;
    motion->x.v += motion->velocity_x;
    motion->z.v += motion->velocity_z;
    motion->velocity_z += motion->velocity_y;

    ticks_left = obj->timer - 1;
    obj->timer = ticks_left;

    switch (obj->state) {
    case 0:
    case 0x40:
    {
        s32 y;
        u16 score;
        s16 signed_score;

        if (motion->velocity_z < 0) {
            break;
        }

        y = motion->z.v;
        if (y > (s32)0xFFF00000) {
            if (!(child->flags & 1)) {
                SD_Call(0x506);
            }
            child->flags |= 1;
            obj->state = 0xFF;
            return;
        }
        if (y <= (s32)0xFFA00000) {
            break;
        }

        if (obj->state == 0 && (child->flags & 1)) {
            break;
        }
        if (gym_lane_delay != 0) {
            break;
        }
        if (obj->target != gym_lane) {
            break;
        }

        SD_Call(0x512);
        signed_score = child->score.s;
        score = child->score.s;
        if (signed_score < 9999) {
            if (obj->state == 0) {
                score++;
                child->score.s = score;
                if ((gym_high_score[0] << 16) < (score << 16)) {
                    gym_high_score[0] = score;
                }
            }
        }
        if (obj->state != 0) {
            obj->timer = 8;
        } else {
            obj->timer = 4;
        }
        apply_global_scene_value(countdown_action_handler_table);
        motion->velocity_y = 0;
        motion->velocity_z = 0;
        motion->velocity_x = 0;
        obj->state = obj->state + 1;
        return;
    }

    case 1:
        if ((ticks_left << 16) > 0) {
            break;
        }
        obj->timer = 8;
        motion->velocity_x = ((s32)0x02A00000 - motion->x.v) / obj->timer;
        motion->velocity_z = ((s32)0xFFC00000 - motion->z.v) / obj->timer;
        obj->state = obj->state + 1;
        return;

    case 2:
        if ((ticks_left << 16) >= 0) {
            break;
        }
        SD_Call(0x525);
        obj->timer = 6;
        motion->velocity_x = motion->velocity_z = motion->velocity_y;
        obj->state = 0xFF;
        return;

    case 0x20:
        if ((ticks_left << 16) > 0) {
            break;
        }
        obj->timer = 10;
        obj->state = (u16)obj->state + 1;
        return;

    case 0x21:
    {
        ObjectPosition *target = &view_reference_entity;
        s32 target_z = target->y.v;
        s32 z = motion->y.v;
        s32 y = motion->z.v;
        s32 offset_y = y + 0x600000;
        motion->y.v = z + ((target_z - z) >> 1);
        motion->z.v = y + ((target->z.v - offset_y) >> 1);
        if ((s16)obj->timer <= 0) {
            obj->state = 1;
        }
        break;
    }

    case 0x41:
    {

        if ((ticks_left << 16) > 0) {
            break;
        }

        if (*(s16 *)0x800135C2 == child->score.s) {
            sound_set_cd_cue_parameters(0, 0x2C3D, 0x01000001, 0x01000271);
            SD_Call(0x300);
            state = obj->state + 1;
            obj->timer = 7;
            obj->state = state;
            return;
        }
        sound_set_cd_cue_parameters(0, 0x2C3D, 0, 0x01000290);
        SD_Call(0x300);
        state = obj->state + 1;
        obj->timer = 7;
        obj->state = state;
        return;
    }

    case 0x42:
    {
        child->flags |= 2;
        {
            s32 x = motion->x.v;
            s32 z = motion->y.v;
            s32 y = motion->z.v;

            motion->x.v = x + (((s32)0x03800000 - x) >> 1);
            motion->y.v = z + (((s32)0x03C00000 - z) >> 1);
            motion->z.v = y + ((-y) >> 1);
            if ((s16)obj->timer > 0) {
                break;
            }
            obj->timer = 4;
            obj->state = 0xFF;
            return;
        }
    }

    case 0xFF:
    {
        u16 *object_flags = (u16 *)obj - 1;
        s32 *global_flags_ptr = ((s32 *)(&object_flag_block));
        s32 updated_flags;

        *object_flags |= 0x8000;
        updated_flags = global_flags_ptr[0] | 0x8000;
        global_flags_ptr[0] = updated_flags;
        if ((s16)obj->timer <= 0) {
            *object_flags |= 0x8000;
            global_flags_ptr[0] = updated_flags;
        }
        break;
    }

    default:
        break;
    }

    return;
}
