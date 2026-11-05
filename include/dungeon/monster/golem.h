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
    s32 callback;
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

typedef struct CopiedRenderObjectBody {
    union { s16 s; u16 u; } phase;
    u16 frames;
    void *source_state;
    void *render_data;
} CopiedRenderObjectBody;

typedef struct RandomizedOffsetVector {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} RandomizedOffsetVector;

typedef struct RandomizedOffsetObjectBody {
    union { s16 s; u16 u; } unk_00;
    union { s16 s; u16 u; } unk_02;
    union { s16 s; u16 u; } unk_04;
    union { s16 s; u16 u; } unk_06;
    union { s16 s; u16 u; } unk_08;
    u16 unk_0A;
    u16 unk_0C;
    union { u16 u; s16 s; } unk_0E;
    u8 pad_10[0x18];
    union { s32 word; struct { u8 pad_00[2]; s16 unk_2A; } half; } unk_28;
    union { s32 word; struct { u8 pad_00[2]; s16 unk_2E; } half; } unk_2C;
    union { s32 word; struct { u8 pad_00[2]; union { s16 s; u16 u; } unk_32; } half; } unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    ActorRecord *unk_40;
    RandomizedOffsetVector *unk_44;
    void *unk_48;
    void *unk_4C;
} RandomizedOffsetObjectBody;

s32 attempt_actor_action_and_display(ActorRecord *action_out, ObjectPosition *action_param, SpriteFrameState *actor_info, ActorRecord *acting_actor);
s32 create_copied_render_object(GolemActionWork *owner, ObjectPosition *source_state, Rec_func_800AA258_arg2 *render_data);
s32 initialize_directional_animation_action(void *state_ptr, ObjectPosition *action_arg, SpriteFrameState *sprite_ptr, ActorRecord *entity_ptr);
s32 scan_forward_tiles_for_target(GolemActionWork *action_state, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);




void advance_actor_height_arc(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *record, ActorRecord *actor);
void advance_timed_target_flags(CopiedRenderObjectBody *state, void *output, SpriteFrameState *target);
void update_staged_target_motion(RandomizedOffsetObjectBody *motion, RandomizedOffsetVector *trajectory, void *context);

void update_dungeon_actor_actions(struct GolemActionWork *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *stats);

/* Directional frame entries; the full allocation extent is not inferred. */
extern u8 golem_frame_set_1[];
s32 consume_pending_flag(ActorRecord *body, ActorRecord *flag_record);
void finish_successful_actor_action(ActorRecord *action_entity, ObjectPosition *action, SpriteFrameState *source_actor, ActorRecord *target_actor);
void * create_offset_actor_object(ActorRecord *unused, ObjectPosition *position, SpriteFrameState *sprite);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80172D08_arg1.h"
void *create_primitive_state_object(ActorRecord *unused, ObjectPosition *position, Rec_D_80082E80 *source);

void advance_timed_directional_reset(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void func_80170E94(struct GolemActionWork *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *stats);
void update_eligible_actor_action(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);

void advance_multi_stage_actor_effect(ActorRecord *body, void *incoming_entity, SpriteFrameState *sprite, ActorRecord *incoming_actor);

#endif
