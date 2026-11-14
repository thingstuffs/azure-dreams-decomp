#ifndef MODULES_TOWN_PLAYER_INIT_H
#define MODULES_TOWN_PLAYER_INIT_H
struct SpriteFrameState;

#include "town/player/record.h"
#include "town/shop/item_lookup.h"
#include "town/scene/list_setup.h"
#include "town/person/position.h"
#include "town/player/coordinates.h"


struct ObjectPosition;
#include "common.h"
#include "town/scene/collision.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/object_node.h"
#include "shared/position_query.h"
#include "shared/tile_object.h"

typedef struct func_80092868_ScenePos {
    s16 pad0;
    u16 x;
    s16 pad4;
    u16 y;
    s16 pad8;
    s16 angle;
} func_80092868_ScenePos;

typedef struct func_80092868_RenderState {
    u8 pad0[0xC];
    s32 color;
    u8 pad10[0xC];
    s16 scale0;
    s16 scale1;
    u8 pad20[8];
    s32 source;
} func_80092868_RenderState;

typedef struct func_80092868_TownState {
    u8 pad0[0xC];
    u16 frame;
    s16 alternate;
    u16 *coords;
    u16 x_offset;
    u16 y_offset;
    s32 mode;
} func_80092868_TownState;

typedef struct func_80092868_TownObject {
    void *next;
    void *prev;
    func_80092868_ScenePos *scene;
    func_80092868_RenderState *render;
    void *callback;
} func_80092868_TownObject;

typedef struct func_80092868_TownWork {
    u8 pad0[0x10];
    u16 frame0;
    s16 field12;
    u8 pad14[2];
    s16 active;
    u16 frame1;
} func_80092868_TownWork;

typedef struct func_80092AB0_S_80090210_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    s32 * unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
    u8 pad_1C[0xA];
    s16 unk_26;
} func_80092AB0_S_80090210_0;

typedef struct func_80092AB0_S_80090210_1 {
    u8 pad_00[0x28];
    s32 unk_28;
} func_80092AB0_S_80090210_1;

typedef struct func_80092AB0_S_80090210_2 {
    u8 pad_00[0x438];
    union { s32 (*s)(); s32 u; } unk_438;                         
} func_80092AB0_S_80090210_2;

typedef void (*func_80092C9C_ObjectCallback)(void *, s32, s32);

typedef void (*func_80092C9C_ActorCallback)(void *, void *, s32);

typedef struct func_80092C9C_S_800903FC_1 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x2];
    u16 unk_16;
} func_80092C9C_S_800903FC_1;

typedef struct func_80092C9C_S_800903FC_2 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x17];
    u8 unk_3B;
} func_80092C9C_S_800903FC_2;

typedef struct func_80092C9C_S_800903FC_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} func_80092C9C_S_800903FC_3;

typedef struct func_80092C9C_S_800903FC_4 {
    u8 pad_00[0x8];
    void * unk_08;
} func_80092C9C_S_800903FC_4;

void initialize_scene_for_mode(void);
void synchronize_mode_and_pending_callback(void);
void initialize_global_scene_record(void);
void plt_init_sleep_set(void);
void initialize_scene_render_state(void);
void initialize_scene_render_object(void);
s32 to_camera_zero_00(void);
void clear_record_state_or_update(struct ObjectPosition *record);
void noop_player_scene_action(void);
void no_op_scene_callback_b(void);

extern void clear_resident_bitmap_bit(s32 flag_id);
extern s32 test_resident_bitmap_bit(s32 bit_id);
extern void zero_words(void *dst, s32 count);
extern void register_node(func_80092868_TownObject *object, void *data);
extern void initialize_circular_list_head(void);
extern void init_town_motion_list(void);
extern void init_secondary_list_record(void *record, func_80092868_ScenePos *scene, void *value_0c); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void init_probe_sample_buffers(void);
extern void sync_collision_motion_xyz(ObjectPosition *context);
extern void create_person_object(void);
extern void init_view_reference_entity(void);
s32 load_town_sprite_bundle(void);
s32 load_alternate_town_sprite_bundle(void);
void dispatch_selected_entry_if_nonzero();
void initialize_player_object(void *object);
extern s32 func_800352FC(void);
extern void submit_object_resource_data(void *owner);
extern s32 read_map_cell_at_world_position(s16 owner, s16 node_in);
extern void add_motion_deltas_to_position(ObjectPosition *motion);
extern void apply_actor_control_offsets(ObjectPosition *out);
extern void store_position_and_compute_delta(void *owner);
extern void update_record_overlap_node(void *owner);
extern s32 has_attached_state_type_1_or_3(void *owner);
extern void set_height_and_slope_velocity(ObjectPosition *obj, s32 base_value, struct TownVec **vec_ptr);
extern s32 update_object_and_clear_status_fields(void *owner);
extern s32 estimate_vector_length(s32, s32);
#include "engine/texture.h"
extern void func_80048AC8(void *, s32);
extern s32 step_angle_toward(s32 angle_delta, s32 target_angle, s32 step);
extern u32 view_relative_angle_sector(s32 angle);
#include "town/player/fallback_handler_position_g00541.h"

extern func_80092868_TownState map_runtime_state;
extern s16 map_scene_selector_alias[];
extern s32 loaded_sprite_bundle_attributes;


extern u8 town_actor_control[];
extern u8 D_800D0420[];
extern u8 town_motion_list[];
extern u8 town_position_reference_state[];
extern s32 camera_turn_lock[];
extern s32 camera_height_mode[];
extern s32 scene_object_payload_alias;

extern u8 town_scene_record_handlers[];
extern s32 town_scene_init_callback;
extern s32 D_800D0178;
extern u8 window_node_list_storage[];
extern s32 town_position_callback_address[3];
extern u8 D_800A5638[];


extern s16 town_scene_effect_flips[];

void rebuild_menu_node_list(TownPlayerRecord *owner, ObjectPosition *node_in, struct SpriteFrameState *sprite);


#endif
