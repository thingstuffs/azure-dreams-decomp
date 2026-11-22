#include "modules/town_map_props.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_trail_views.h"

#include "shared/sprite_source.h"

typedef struct YorozuPoseSources {
    SpriteSourceEntry *entries[9];
} YorozuPoseSources;

extern const YorozuPoseSources D_80089684;
#include "town/map/animation.h"
#include "engine/script.h"

extern SpriteSourceEntry D_800F9D80[];

/* Advances the actor animation state and applies a timed pose offset. */
void advance_actor_animation_pose(YorozuPoseProp *actor, ObjectPosition *pose, SpriteFrameState *animation) {
    YorozuPoseSources animations;
    s16 animation_index;
    s32 state;
    s16 elapsed_frames;

    animations = D_80089684;
    advance_sprite_animation_and_textures(animation);
    state = actor->state;
    switch (state) {
    case 0:
        if ((service_script_controller() != 0) && (check_town_target_and_callback(actor) != 0)) {
            animation_index = rand() & 7;
            actor->state = animation_index;
            actor->animation_index = animation_index;
            select_record_entry_and_value(animation, animations.entries[actor->state], 0);
            actor->state += 0x20;
        }
        break;
    case 0x20:
        if (!(animation->flags & 0x6000))
            return;
        select_record_entry_and_value(animation, animations.entries[0], 0);
        actor->pose_ticks = 0;
        actor->animation_index = 0;
        pose->z.w.i = actor->base_height;
        actor->state = 0x60;
        break;
    case 0x23:
        if (!(animation->flags & 0x6000))
            return;
        actor->pose_ticks = 6;
        actor->animation_index = 8;
        select_record_entry_and_value(animation, animations.entries[8], 0);
        actor->state = 0x40;
        break;
    case 0x24:
        if (!(animation->flags & 0x6000))
            return;
        select_record_entry_and_value(animation, D_800F9D80, 0);
        {
            s16 next_state = 0x20;
            actor->state = next_state;
        }
        break;
    case 0x25:
        if (!(animation->flags & 0x6000))
            return;
        select_record_entry_and_value(animation, D_800F9D80, 0);
        actor->state = 0x20;
        break;
    case 0x21:
    case 0x22:
    case 0x26:
    case 0x27:
        if (!(animation->flags & 0x6000))
            return;
        actor->state = 0x60;
        break;
    case 0x40:
        pose->z.w.i = actor->base_height + (rcos((actor->pose_ticks << 0xC) / 22) >> 8);
        elapsed_frames = actor->pose_ticks;
        actor->pose_ticks = elapsed_frames + 1;
        if (elapsed_frames >= 0xDC) {
            actor->state = 0x20;
        }
        break;
    case 0x60:
        if ((service_script_controller() == 0) || (check_town_target_and_callback(actor) == 0)) {
            actor->state = 0;
        }
        break;
    }

    if (animation->flags & 0x6000) {
        select_record_entry_and_value(animation, animations.entries[actor->animation_index], 0);
    }
}
