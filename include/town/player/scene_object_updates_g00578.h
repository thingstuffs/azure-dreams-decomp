#ifndef TOWN_PLAYER_SCENE_OBJECT_UPDATES_G00578_H
#define TOWN_PLAYER_SCENE_OBJECT_UPDATES_G00578_H
/* Initialize and update enabled player scene objects. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A8BC8, CL:town/func_800A9234, CL:town/func_800A9334, CL:town/func_800A9410, PD:town/engine:800D0C78, PD:town/engine:800D0D54, PD:town/engine:80100E24, PD:town/engine:80100E28. */

#include "common.h"
#include "town/scene/list_setup.h"
#include "town/event/object_setup.h"
#include "shared/sprite_frame_state.h"
#include "script_symbols.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/entity_objects.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/dungeon_delay_views.h"
#include "town/person/position.h"
#include "slus.h"

#ifndef NULL
#define NULL 0
#endif

/* Stack position supplied to the bicycle crossing-effect spawners by update_entity_sprite_and_effects. */
typedef struct {
    s32 x; /* effect X in 16.16 world units, copied from the bicycle position */
    s32 y; /* effect Y in 16.16 world units, placed on one side of the crossing */
    s32 z; /* effect height in 16.16 world units, bicycle height minus 40 world units */
    s32 padC;
    s32 pad10;
} StackRecord;

/* The bicycle dispatcher passes the same Town body in its first two slots, followed by the node position and sprite. */
typedef void (*EntityCallback)(TownObjectRecord *, TownObjectRecord *, ObjectPosition *, SpriteFrameState *);

/* start_bicycle_at_view_reference initializes the node's ObjectPosition slot
 * from view_reference_entity and clears its three motion increments. */

typedef struct S_800A6994_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x24];
    u16 unk_38;
} S_800A6994_0;

extern s32 test_resident_bitmap_bit(s32 bit_id);
extern s8 D_800A6684[];
extern s32 bike_default_position[];
extern s8 D_800D0C90[];
extern struct Box D_800D0CAC;
extern s8 bicycle_slow_update_entries[];
extern s8 bicycle_slow_start_entries[];
extern s8 bicycle_fast_update_entries[];
extern s8 bicycle_fast_start_entries[];
extern s32 town_movement_speed;
extern void *D_80100E24_R;
extern void advance_sprite_animation_and_textures(void *);
extern s32 update_object_and_clear_status_fields(void *);
extern void set_state_bytes_from_flags(s32 flags, u8 *state);
extern void create_colored_scaled_effect(StackRecord *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void create_shrinking_white_fade_effect(StackRecord *);
extern void update_target_from_previous_state(void);
extern void apply_pending_indexed_value(s32, s32);


extern u8 D_800A5638[];

extern void set_flagged_entry_values(u32 *record_lists, s32 value);
extern s32 bike_saved_position[];
extern u8 bicycle_flagged_entry_lists[];
extern void *bicycle_update_entries;
extern void *bicycle_start_entries[1];

/* Functions defined in this translation unit. */
void initialize_enabled_scene_object(void);
void update_entity_sprite_and_effects(void *entity, ObjectPosition *position, SpriteFrameState *sprite);
void start_bicycle_at_view_reference(TownObjectRecord *object, TownObjectRecord *state, ObjectPosition *motion, SpriteFrameState *sprite);
void update_bicycle_position_and_heading(TownObjectRecord *object, TownObjectRecord *update_context, ObjectPosition *position, SpriteFrameState *sprite);

#endif
