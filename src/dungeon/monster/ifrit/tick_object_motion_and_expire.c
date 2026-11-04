#include "common.h"
#include "dungeon/monster/ifrit.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"

extern void advance_sprite_animation_and_textures(void *work);

/* Advances object motion, decrements its timer, and flags expiration. */
void tick_object_motion_and_expire(ActorImpactEffectBody *object_data, void *motion_data, SpriteFrameState *work_data)
{
    s32 *motion = motion_data;
    ActorImpactEffectBody *object = object_data;
    SpriteFrameState *work= work_data;
    s16 timer;

    work->color.word -= object->unk_A4.s;
    motion[0] += motion[3];
    motion[1] += motion[4];
    motion[2] += motion[5];

    timer = object->unk_96 - 1;
    object->unk_96 = timer;
    if (timer <= 0) {
        ((ObjectNodeHeader *)object - 1)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

    advance_sprite_animation_and_textures(work);
}
