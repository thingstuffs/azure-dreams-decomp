#ifndef DUNGEON_MONSTER_GOLEM_H
#define DUNGEON_MONSTER_GOLEM_H

/* Function contracts owned by src/dungeon/monster/golem/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
/* Golem callback work rooted at the actor body. The action dispatcher, forward
 * scan and motion transition share these slots; +0xAE selects the alternate mode. */
typedef struct GolemActionWork {
    u8 pad_00[0x8C];
    union { s32 word; void *address; } callback;
    u8 pad_90[6];
    s16 duration;
    u16 flags;
    u8 state;
    u8 phase;
    u8 pad_9C[0xC];
    s16 target_x;
    s16 target_y;
    s16 steps;
    u8 mode;
} GolemActionWork;

s32 attempt_actor_action_and_display(ActorRecord *action_out, ObjectPosition *action_param, SpriteFrameState *actor_info, ActorRecord *acting_actor);
s32 create_copied_render_object(GolemActionWork *owner, ObjectPosition *source_state, Rec_func_800AA258_arg2 *render_data);
s32 initialize_directional_animation_action(void *state_ptr, ObjectPosition *action_arg, SpriteFrameState *sprite_ptr, void *entity_ptr);
s32 scan_forward_tiles_for_target(GolemActionWork *action_state, ObjectPosition *transfer_data, SpriteFrameState *origin, void *actor);




void advance_actor_height_arc(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *record, ActorRecord *actor);
void advance_timed_target_flags(void *state, void *output, SpriteFrameState *target);

void update_dungeon_actor_actions(GolemActionWork *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *stats);

/* Directional frame entries; the full allocation extent is not inferred. */
extern u8 golem_frame_set_1[];
s32 consume_pending_flag(struct GolemActionWork *object, ActorRecord *flag_record);
void finish_successful_actor_action(ActorRecord *action_entity, ObjectPosition *action, SpriteFrameState *source_actor, void *target_actor);





#endif
