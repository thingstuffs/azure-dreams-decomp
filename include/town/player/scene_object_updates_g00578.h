#ifndef TOWN_PLAYER_SCENE_OBJECT_UPDATES_G00578_H
#define TOWN_PLAYER_SCENE_OBJECT_UPDATES_G00578_H
/* Initialize and update enabled player scene objects (G00578). */
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
#include "records/Rec_func_80094268_arg0.h"
#include "shared/dungeon_delay_views.h"
#include "town/person/position.h"
#include "slus.h"

#ifndef NULL
#define NULL 0
#endif

/* Stack position supplied to the bicycle crossing-effect spawners by update_entity_sprite_and_effects. */
typedef struct {
    s32 unk0; /* effect X in 16.16 world units, copied from the bicycle position */
    s32 unk4; /* effect Y in 16.16 world units, placed on one side of the crossing */
    s32 unk8; /* effect height in 16.16 world units, bicycle height minus 40 world units */
    s32 padC;
    s32 pad10;
} StackRecord;

/* Bicycle work callback invoked with (entity, entity, position, sprite) by update_entity_sprite_and_effects. */
typedef void (*EntityCallback)(void *, void *, void *, void *);

/* Sprite-part slice of the town bicycle object created by initialize_enabled_scene_object.
 * update_entity_sprite_and_effects selects its directional source and fades its crossing flash. */
typedef struct S_800A6684_0 {
    u8 pad_00[0x4];
    s8 unk_04; /* current sprite-source entry index retained when the directional source changes */
    u8 pad_05[0x7];
    u8 unk_0C; /* red modulation byte; crossing flashes set 255, then fade toward 128 */
    u8 unk_0D; /* green modulation byte; crossing flashes set 255, then fade toward 128 */
    u8 unk_0E; /* blue modulation byte, kept equal to green during the flash fade */
    u8 pad_0F[0x5];
    u16 unk_14; /* sprite status/render flags; heading selection sets or clears bit 0 */
} S_800A6684_0;

/* Bicycle work callback slice initialized by save_and_clear_entity_flag_ten.
 * initialize_enabled_scene_object owns the node through create_town_effect_object. */
typedef struct {
    s8 pad00[0x50];
    void (*callback)(void *, s32, void *, void *); /* movement/heading callback installed as update_actor_position_and_heading */
} Obj;

typedef struct { u8 pad00[0x15]; u8 flag15; } State;

/* Bicycle position/motion part initialized by save_and_clear_entity_flag_ten.
 * The initializer copies view_reference_entity and clears the three motion increments. */
typedef struct { s32 x /* world X in 16.16 units */, y /* world Y in 16.16 units */, z /* world height in 16.16 units */, dx /* X motion increment in 16.16 units per position update; initially zero */, dy /* Y motion increment in 16.16 units per position update; initially zero */, dz; /* height increment in 16.16 units per position update; initially zero */ } VecState;

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
extern s8 D_800D0CAC[];
extern s8 D_800D0CC4[];
extern s8 D_800D0CE8[];
extern s8 D_800D0D0C[];
extern s8 D_800D0D30[];
extern s32 town_movement_speed;
extern void *D_80100E24_R;
extern void advance_sprite_animation_and_textures(void *);
extern s32 update_object_and_clear_status_fields(void *);
extern void set_state_bytes_from_flags(s32 flags, u8 *state);
extern void create_colored_scaled_effect(StackRecord *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void update_sine_pulse_color(StackRecord *);
extern void update_target_from_previous_state(void);
extern void apply_pending_indexed_value(s32, s32);
extern char D_800A630C[];
extern char D_800A62E8[];
extern u8 D_800A5638[];

extern void set_flagged_entry_values(u32 *record_lists, s32 value);
extern s32 bike_saved_position[];
extern u8 D_800D0D54[];
extern void *D_80100E24;
extern void *D_80100E28[1];

/* Functions defined in this translation unit. */
void initialize_enabled_scene_object(void);
void update_entity_sprite_and_effects(void *entity, EntityRec *position, SpriteFrameState *sprite);
void save_and_clear_entity_flag_ten(Obj *obj, State *state, VecState *motion, void *callback_arg);
void update_actor_position_and_heading(void *actor, s32 update_context, void *position, void *setup_context);

#endif
