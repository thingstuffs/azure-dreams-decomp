#ifndef DUNGEON_ACTOR_EFFECT_H
#define DUNGEON_ACTOR_EFFECT_H

/* Function contracts owned by src/dungeon/actor/effect/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
void *create_owner_linked_pulsing_effect(ObjectPosition *spawn_pos, ActorRecord *source_state, void *owner);




struct S_800CABA8_0;
void advance_damage_effect_and_particles(struct S_800CABA8_0 *effect, ObjectPosition *context, SpriteFrameState *record, void *actor);



/* Body created by create_dropped_item_object (flags 0x110) and consumed by
 * update_dropped_object_motion. The creator borrows its source actor's
 * position and sprite from the actor's node header. */
typedef struct DroppedObjectMotionBody {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 facing;
    u8 pad_2C[0x34];
    ActorRecord *source_actor;
    u8 pad_64[6];
    s16 unk_6A;
    u8 pad_6C[0x1C];
    s16 ground_height;
    s16 travel_steps;
    ObjectPosition *source_position;
    SpriteFrameState *source_sprite;
    u8 pad_94[4];
    s32 unk_98;
    s32 *unk_9C;
    s16 unk_A0;
    s16 unk_A2;
    s16 unk_A4;
    u8 pad_A6[0x16];
} DroppedObjectMotionBody;

typedef struct DroppedItemNode {
    ObjectNodeHeader header;
    DroppedObjectMotionBody body;
} DroppedItemNode;

DroppedItemNode *create_dropped_item_object(void *owner, ObjectPosition *source_coords, SpriteFrameState *unused,
                                 ActorRecord *source_data, DungeonItemEntry *init_data, s16 tile_id);
void update_dropped_object_motion(DroppedObjectMotionBody *object, register ObjectPosition *motion, SpriteFrameState *tile);

s32 update_actor_fade_in(ActorRecord *object, ObjectPosition *unused, SpriteFrameState *effect);
void run_actor_fade_in(void *owner, s32 context, void *effect);

/* Callback entry points. */
void advance_effect_positions_and_fade(void *effect, ObjectPosition *positions, SpriteFrameState *color);

void unmark_selected_item(void *selection);
/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 place_item_at_valid_floor_position(s32 x, s32 y, s32 z, s32 unused, s32 *object_data);

s32 try_apply_paralysis_effect(void *actor, s32 chance, s32 action);
void *create_item_render_object(void *parent, void *sprite_source, s16 x, s32 y, s16 z);
s32 find_floor_item_at_world_position(s32 input_x, s32 input_y, s32 input_z);

s32 find_valid_floor_item_position(s16 x, s16 y, s16 z, s16 *out_x, s16 *out_y, s16 *out_distance);

void mark_category_items(s32 group_bit);

struct ObjectNodeHeader;
struct State;
void *create_source_linked_fading_effect(struct ObjectNodeHeader *source, s16 copy_position);
s32 get_item_sprite_source(void *item_data);
void snapshot_item_flag_bitmap(u16 unused_saved_setting);
s32 roll_paralysis_effect(struct State *state, s16 value, s16 flag);
s32 roll_poison_effect(struct State *state_ptr, s16 limit_input, s16 byte_input);
s32 roll_blind_effect(struct State *state_ptr, s16 limit_input, s16 byte_input);
s32 try_apply_blind_effect(void *entity, s16 chance, s16 effect_value);

void compact_item_entry_table(s32 entry_index);


s32 render_floor_items(s32 unused_value, ObjectPosition *unused_position, SpriteFrameState *render_params);

void remove_floor_items_at_tile(s16 target_x, s16 target_y);

struct SourceLinkedFadeEffectBody;
void fade_effect_primitive(struct SourceLinkedFadeEffectBody *effect, void *unused, SpriteFrameState *primitive);
void *create_status_linked_render_effect(ObjectPosition *source_pos, s32 render_param, s16 initial_state, s8 *status);
s32 render_actor_sprite_chain(void *initial_state, ObjectPosition *context, SpriteFrameState *entry);
void update_owner_linked_pulsing_effect(void *effect_arg, ObjectPosition *position, SpriteFrameState *appearance);

#endif
