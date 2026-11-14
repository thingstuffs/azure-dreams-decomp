#include "shared/object_node.h"
#ifndef DUNGEON_OVL_FA7000_H
#define DUNGEON_OVL_FA7000_H
#include "engine/node/registration.h"
struct ActorRecord;
#include "common.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/system.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/actor/status.h"
struct ObjectNodeHeader;
struct SpriteFrameState;
extern u8 zu_default_frames[];
void select_sprite_entry(void *object_data, s16 table_index, s16 entry_index);
void func_80047784(void *object_data, s16 table_index, s16 entry_index);
s16 test_neighbor_position_relation(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);
/* This retail bank used the signed-halfword declaration. */
s16 sample_terrain_surface_height();
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
s16 get_actor_height_difference(ActorRecord *left_record, ActorRecord *right_record);
void *probe_directional_neighbor(void *entity, s32 x, s32 y, u32 direction);
void spend_actor_mp(ActorRecord *entity, s32 base_reduction);
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
void *spawn_zu_actor(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
void update_zu_movement(ActorRecord *entity, ObjectPosition *motion_arg, SpriteFrameState *sprite_arg);
void update_zu_behavior(ActorRecord *actor, ObjectPosition *context, struct SpriteFrameState *sprite, ActorRecord *stats_in);
void advance_zu_path(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void select_zu_movement(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data);
s32 try_begin_zu_directional_action(ActorRecord *action_state, ObjectPosition *motion_param, struct SpriteFrameState *sprite, ActorRecord *actor);
void begin_zu_action(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite, ActorRecord *entity);
s32 check_zu_action_ready(struct ActorRecord *actor, ObjectPosition *primary_context, SpriteFrameState *secondary_context, s32 force_move);
void select_zu_tile_movement_callback(ActorRecord *state, ObjectPosition *motion, struct SpriteFrameState *source, ActorRecord *target);
void select_zu_linked_motion_callback(ActorRecord *state, ObjectPosition *action, struct SpriteFrameState *source, ActorRecord *target);
void update_zu_windup_strike(ActorRecord *body, ObjectPosition *motion,struct SpriteFrameState *sprite, ActorRecord *actor);
void update_zu_spell_action(ActorRecord *owner_input, ObjectPosition *motion_input, SpriteFrameState *actor_input, ActorRecord *object);
void restore_zu_to_tile(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity);
void update_zu_defeat_removal(ActorRecord *effect_data, void *motion_data, SpriteFrameState *sprite_data, void *object_data);
void update_zu_hop_and_shrink(ActorRecord *state, ObjectPosition *action, SpriteFrameState *source, ActorRecord *target);
void forward_actor_removal_callback(void *state, ObjectPosition *action, SpriteFrameState *source, ActorRecord *target);
void finish_zu_hop_and_grow(ActorRecord *state, ObjectPosition *action, struct SpriteFrameState *source, ActorRecord *target);
void update_sleeping_zu(ActorRecord *controller, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void advance_zu_animation(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
void update_zu_sprite_state(ActorRecord *actor, ObjectPosition *action, struct SpriteFrameState *sprite, ActorRecord *target);
void update_directional_sprite_state_and_signals(ActorRecord *state, ObjectPosition *action, struct SpriteFrameState *source, ActorRecord *target);
void restore_after_terrain_interpolation(ActorRecord *state, ObjectPosition *action, struct SpriteFrameState *source, ActorRecord *target);
void restore_after_spinning_fall(ActorRecord *state, ObjectPosition *action, struct SpriteFrameState *source, ActorRecord *target);
void restore_after_fade_in(ActorRecord *state, ObjectPosition *action, struct SpriteFrameState *source, ActorRecord *target);
void update_zu_effect_fade(void *effect, ObjectPosition *position, struct SpriteFrameState *visual);
struct CylindricalEffectWork;

/* Spin, height drift, and fade phase for a bank effect particle. */
typedef struct BankEffectFadeBody {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
    u8 pad_0A[0xA];
    u16 unk_14;
    u8 pad_16[0x32];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;
} BankEffectFadeBody;

void start_bank_actor_hit_reaction(ActorRecord *work, ObjectPosition *part_a, SpriteFrameState *part_b, ActorRecord *actor);
void update_zu_timed_effect(ActorRecord *state_input, ObjectPosition *motion_input, SpriteFrameState *animation_input, ActorRecord *actor_input);
void create_cylindrical_effect(struct CylindricalEffectWork *state);
#endif

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void *create_actor_kind_object(s16 flags, s16 field24_input, s16 field25_input, s16 field0A_input);
void *create_configured_overlay_actor_third(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
void *spawn_zu_slot_f(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);
