#ifndef TOWN_PLAYER_SCENE_OBJECT_UPDATES_G00578_H
#define TOWN_PLAYER_SCENE_OBJECT_UPDATES_G00578_H
/* Initialize and update enabled player scene objects (G00578). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A8BC8, CL:town/func_800A9234, CL:town/func_800A9334, CL:town/func_800A9410, PD:town/engine:800D0C78, PD:town/engine:800D0D54, PD:town/engine:80100E24, PD:town/engine:80100E28. */

#include "common.h"
#include "script_symbols.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/entity_objects.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/dungeon_delay_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 padC;
    s32 pad10;
} StackRecord;

typedef void (*EntityCallback)(void *, void *, void *, void *);

typedef struct S_800A6684_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_800A6684_0;

typedef struct {
    s8 pad00[0x50];
    void (*callback)(void *, s32, void *, s32);
} Obj;

typedef struct { u8 pad00[0x15]; u8 flag15; } State;

typedef struct { s32 x, y, z, dx, dy, dz; } VecState;

typedef struct S_800A6994_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x24];
    u16 unk_38;
} S_800A6994_0;

extern s32 test_resident_bitmap_bit();
extern void *create_town_effect_object();
extern s16 query_lowered_transform_position();
extern void handle_insert_initialize_two_values_status_flags();
extern void initialize_optional_object_state();
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
extern void select_record_entry_and_value(void *, void *, s8);
extern void advance_sprite_animation_and_textures(void *);
extern s32 update_object_and_clear_status_fields(void *);
extern void set_state_bytes_from_flags(s32 flags, u8 *state);
extern void create_colored_scaled_effect(StackRecord *);
extern void update_sine_pulse_color(StackRecord *);
extern s32 quantize_heading_to_sector(s16, s16);
extern s32 check_heading_past_half_sector(s16, s16);
extern void update_target_from_previous_state(void);
extern void apply_pending_indexed_value(s32, s32);
extern char D_800A630C[];
extern char D_800A62E8[];
void select_object_value_by_height_band();
extern u8 D_800A5638[];

extern void set_flagged_entry_values(u32 *record_lists, s32 value);
extern s32 bike_saved_position[];
extern u8 D_800D0D54[];
extern void *D_80100E24;
extern void *D_80100E28[1];

/* Functions defined in this translation unit. */
void initialize_enabled_scene_object(void);
void update_entity_sprite_and_effects(void *entity, EntityRec *position, S_800A6684_0 *sprite);
void save_and_clear_entity_flag_ten(Obj *obj, State *state, VecState *motion, s32 callback_arg);
void update_actor_position_and_heading(void *actor, s32 update_context, void *position, s32 setup_context);

#endif
