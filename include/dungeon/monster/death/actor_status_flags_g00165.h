#ifndef DUNGEON_MONSTER_DEATH_ACTOR_STATUS_FLAGS_G00165_H
#define DUNGEON_MONSTER_DEATH_ACTOR_STATUS_FLAGS_G00165_H
/* Advances Death's action state and directional animation while processing status flags. */

#include "common.h"
#include "engine/graphics/select_sprite_entry_api.h"
#include "dungeon/monster/death.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"



/* arg0 in wait_death_mp_and_animate */
typedef struct S_8017409C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017409C_2;

/* base in wait_death_mp_and_animate */
typedef struct S_8017409C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_8017409C_4;

/* global in wait_death_status_and_animate */
extern s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
extern s16 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
extern s32 generate_random_value(void);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void func_801743F0(void *, void *, void *, void *);
extern s32 death_action_resume_address;
#include "dungeon/monster/death_frames.h"
extern u8 death_frame_set_3[];

/* Functions defined in this translation unit. */
void wait_death_status_and_animate(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);

#endif
