#ifndef DUNGEON_MONSTER_IFRIT_H
#define DUNGEON_MONSTER_IFRIT_H
struct ActorImpactEffectBody;

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Timer and color delta stored in an Ifrit impact particle body. */
typedef struct ActorImpactEffectBody {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0xC];
    union { s32 s; u32 u; } unk_A4;
} ActorImpactEffectBody;

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 ifrit_direction_frames[];



void advance_ifrit_attack_animation(ActorRecord *action, ObjectPosition *actor_id, SpriteFrameState *sprite, ActorRecord *actor);

/* Callback entry points. */
s32 render_linked_textured_strips(u8 *item_data);
void tick_object_motion_and_expire(struct ActorImpactEffectBody *object_data, void *motion_data, SpriteFrameState *work_data);

void update_sleeping_ifrit(ActorRecord *in_action, ObjectPosition *in_context, SpriteFrameState *in_sprite, ActorRecord *in_actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void advance_item_use_with_impact_effect(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

#endif
