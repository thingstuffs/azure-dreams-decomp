#ifndef DUNGEON_ACTOR_EFFECT_H
#define DUNGEON_ACTOR_EFFECT_H

/* Function contracts owned by src/dungeon/actor/effect/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
void *create_owner_linked_pulsing_effect(void *spawn_pos, EntityRec *source_state, void *owner);




void advance_damage_effect_and_particles(void *effect, ObjectPosition *context, SpriteFrameState *record, void *actor);



void update_dropped_object_motion(void *object, register ObjectPosition *motion, void *tile);

struct StructArg0;
struct StructArg2;
s32 update_actor_fade_in(struct StructArg0 *object, s32 unused, struct StructArg2 *effect);
void run_actor_fade_in(void *owner, s32 context, void *effect);

/* Callback entry points. */
void advance_effect_positions_and_fade(void *effect, void *positions, void *color);

void clear_selected_item_flag_400(void *selection);
/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 place_item_at_valid_floor_position(s32 x, s32 y, s32 z, s32 unused, s32 *object_data);

s32 try_apply_effect_four_by_chance(void *actor, s32 chance, s32 action);
void *create_item_render_object(void *parent, void *sprite_source, s16 x, s32 y, s16 z);
s32 find_floor_item_at_world_position(s32 input_x, s32 input_y, s32 input_z);

s32 find_valid_floor_item_position(s16 x, s16 y, s16 z, s16 *out_x, s16 *out_y, s16 *out_distance);

void mark_category_items_flag_400(s32 group_bit);

struct ObjectNodeHeader;
struct State;
void *create_source_linked_fading_effect(struct ObjectNodeHeader *source, s16 copy_position);
s32 get_item_category_value(void *item_data);
void pack_item_flag_400_bitmap(void);
s32 roll_chance_and_apply_effect_four(struct State *state, s16 value, s16 flag);
s32 roll_threshold_effect_variant_a(struct State *state_ptr, s16 limit_input, s16 byte_input);
s32 roll_threshold_effect_variant_b(struct State *state_ptr, s16 limit_input, s16 byte_input);
s32 try_apply_threshold_effect_variant_b(void *entity, s16 chance, s16 effect_value);

#endif
