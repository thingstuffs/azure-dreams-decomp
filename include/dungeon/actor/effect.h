#ifndef DUNGEON_ACTOR_EFFECT_H
#define DUNGEON_ACTOR_EFFECT_H

/* Function contracts owned by src/dungeon/actor/effect/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
void *create_owner_linked_pulsing_effect(ObjectPosition *spawn_pos, ActorRecord *source_state, void *owner);




struct S_800CABA8_0;
void advance_damage_effect_and_particles(struct S_800CABA8_0 *effect, ObjectPosition *context, SpriteFrameState *record, void *actor);



/* Body created by create_indexed_floor_object (flags 0x110) and consumed by
 * update_dropped_object_motion. Borrowed position and sprite words retain
 * their integer views because the creator copies them from the source node. */
typedef struct DroppedObjectMotionBody {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[8];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { s16 s; u16 u; } unk_2A;
    u8 pad_2C[0x34];
    void *unk_60;
    u8 pad_64[6];
    s16 unk_6A;
    u8 pad_6C[0x1C];
    union { s16 s; u16 u; } unk_88;
    union { s16 s; u16 u; } unk_8A;
    union { void *address; s32 word; } unk_8C;
    union { void *address; s32 word; } unk_90;
    u8 pad_94[4];
    s32 unk_98;
    s32 *unk_9C;
    s16 unk_A0;
    s16 unk_A2;
    s16 unk_A4;
    u8 pad_A6[0x16];
} DroppedObjectMotionBody;

struct S_800A871C_4;
void update_dropped_object_motion(DroppedObjectMotionBody *object, register ObjectPosition *motion, struct S_800A871C_4 *tile);

struct StructArg0;
struct StructArg2;
s32 update_actor_fade_in(struct StructArg0 *object, s32 unused, struct StructArg2 *effect);
void run_actor_fade_in(void *owner, s32 context, void *effect);

/* Callback entry points. */
void advance_effect_positions_and_fade(void *effect, void *positions, SpriteFrameState *color);

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
void pack_item_flag_400_bitmap(u16 unused_saved_setting);
s32 roll_chance_and_apply_effect_four(struct State *state, s16 value, s16 flag);
s32 roll_threshold_effect_variant_a(struct State *state_ptr, s16 limit_input, s16 byte_input);
s32 roll_threshold_effect_variant_b(struct State *state_ptr, s16 limit_input, s16 byte_input);
s32 try_apply_threshold_effect_variant_b(void *entity, s16 chance, s16 effect_value);

void compact_item_entry_table(s32 entry_index);


s32 render_floor_items(s32 unused_value, ObjectPosition *unused_position, SpriteFrameState *render_params);

void remove_floor_items_at_tile(s16 target_x, s16 target_y);

struct Entry;
struct SourceLinkedFadeEffectBody;
void fade_effect_primitive(struct SourceLinkedFadeEffectBody *effect, void *unused, SpriteFrameState *primitive);
s32 render_actor_sprite_chain(void *initial_state, ObjectPosition *context, struct Entry *entry);
void update_owner_linked_pulsing_effect(void *effect_arg, ObjectPosition *position, SpriteFrameState *appearance);

#endif
