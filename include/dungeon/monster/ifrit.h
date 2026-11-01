#ifndef DUNGEON_MONSTER_IFRIT_H
#define DUNGEON_MONSTER_IFRIT_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Timer and color delta stored in an Ifrit impact particle body. */
typedef struct UpdateActorActionsAndImpactEffectsBody {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0xC];
    union { s32 s; u32 u; } unk_A4;
} UpdateActorActionsAndImpactEffectsBody;

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 ifrit_direction_frames[];



void advance_actor_animation_and_restore(ActorRecord *action, ObjectPosition *actor_id, SpriteFrameState *sprite, ActorRecord *actor);

/* Callback entry points. */
s32 render_linked_items_as_textured_strips(u8 *item_data);
void tick_object_motion_and_expire(void *object_data, void *motion_data, void *work_data);

void advance_actor_action_and_status(ActorRecord *in_action, ObjectPosition *in_context, SpriteFrameState *in_sprite, ActorRecord *in_actor);
#endif
