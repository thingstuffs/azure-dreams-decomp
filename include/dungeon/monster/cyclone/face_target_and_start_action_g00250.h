#ifndef DUNGEON_MONSTER_CYCLONE_FACE_TARGET_AND_START_ACTION_G00250_H
#define DUNGEON_MONSTER_CYCLONE_FACE_TARGET_AND_START_ACTION_G00250_H
#include "dungeon/level/tile_flags.h"
#include "dungeon/actor/status.h"
#include "dungeon/level.h"

struct ObjectPosition;
/* Face target and start action. Shared declarations. */
/* Faces the target or searches ahead before starting the actor's action. */

#include "common.h"
#include "dungeon/monster/cyclone.h"
#include "shared/dungeon_image_buffer.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/sprite_frame_state.h"

#define D_801764A0_OFF 0x2C4A0

typedef struct S_801722E4_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801722E4_5_pre;

/* arg2 in face_target_and_start_action */
typedef struct S_801722E4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801722E4_2;

/* extern */

extern u8 cyclone_frame_set_2[];
/* arg0 in search_ahead_and_start_action */
extern s32 find_eligible_entry_at_coordinates(void *, u16, u16);
extern s32 check_entity_interaction_compatibility(void *, void *);

/* Shared import declarations; data casts preserve each measured view. */
extern void select_sprite_entry(void *, u8, s32);

/* Functions defined in this translation unit. */
void face_target_and_start_action(ActorRecord *action_state, ObjectPosition *event_context, SpriteFrameState *sprite, ActorRecord *actor);
s32 search_ahead_and_start_action(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
void update_action_state_direction_specific(ActorRecord *action_state, ObjectPosition *action_param, SpriteFrameState *sprite, ActorRecord *actor);
void clear_actor_action_flag_and_animate(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *animation, ActorRecord *actor);

#include "shared/object_node.h"

#endif
