#ifndef DUNGEON_MONSTER_BELDO_H
#define DUNGEON_MONSTER_BELDO_H

/* Function contracts owned by src/dungeon/monster/beldo/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
#include "shared/entity.h"

struct S_81275000_0;

typedef struct AttachedSpriteWithOffsetBody {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    u8 pad_96[0x16];
    union {
        void * pointer;
        s32 integer;
    } unk_AC;
    union { s16 s; u16 u; } unk_B0;
    union { s16 s; u16 u; } unk_B2;
    union { s16 s; u16 u; } unk_B4;
    s16 unk_B6;
    u8 pad_B8[0x1C];
    u32 pad_D4[4];
    u16 pad_E4[8];
    u32 pad_F4[4];
    u8 pad_104[0xE];
} AttachedSpriteWithOffsetBody;

void create_attached_sprite_with_offset(ActorRecord *owner_data, MovingPosition *base_position, SpriteFrameState *sprite_template, s16 offset_id);
void copy_part_state(AttachedSpriteWithOffsetBody *root, void *out_pos_arg, void *dst_part_arg);
void create_flagged_actor_object_2(AttachedSpriteWithOffsetBody *root, void *output_pos, void *target_data);

void run_actor_callbacks_and_adjust_global_flag(void *entity_ptr, void *motion, void *check_arg, void *actor_arg);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void update_actor_movement_and_height(ActorRecord *entity_arg, ObjectPosition *motion_arg, SpriteFrameState *monster_arg);

void advance_actor_action_and_target(ActorRecord *action, void *motion, SpriteFrameState *sprite, void *actor);
void advance_queued_movement_step(ActorRecord *motion, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *path);
void *create_entity_and_initialize_placement(s16 entity_id, s32 tile_x, s16 tile_y, u16 initial_height);
void update_actor_part_brightness(void *root_data, void *position_out, void *part_out);
void update_beldo_attached_part(struct S_81275000_0 *root_data, void *position_data, void *render_data);
void update_object_animation(ActorRecord *obj, ObjectPosition *motion, SpriteFrameState *part, ActorRecord *state);

s32 replay_actor_direction_commands(ActorRecord *actor, ObjectPosition *action_context, SpriteFrameState *sprite);
#endif
