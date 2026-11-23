#ifndef ENGINE_EFFECT_H
#define ENGINE_EFFECT_H
struct ResourceTransitionBody;
struct ObjectPosition;
/* Prototypes of the functions defined in src/engine/effect/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "engine/effect/fade_manager.h"
#include "engine/effect/screen_fade.h"
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"
#include "sdk/libgte_matrix.h"
#include "shared/entity.h"

/* Scan-line edge state init_polygon_edges fills for each polygon edge. */
typedef struct ScanEdge {
    s32 x;
    s32 error_dec;
    s32 error_inc;
    s32 remaining;
    s32 error;
    s32 x_inc;
    s32 start_y;
    s32 state;
    s32 height;
    s32 pad_24;
} ScanEdge;

/* Projected map cell vertex: the packed screen xy word, then the depth word. */
typedef struct MapCellVertex {
    s32 xy;
    u16 z;
    u16 pad;
} MapCellVertex;

/* Scratchpad slots of the map cell rasterisers (render_map_cell_mesh, the town map tile renderers):
 * init_polygon_edges fills edges and active_edges, the GTE stores write otz, otz4 and opz, and the map spans
 * and masks come from the map shift and mask fields. Slots +0xC0/+0xC4 (tile id in render_shaded_map_tiles,
 * gte_stdp outputs in draw_empty_map_cell_quads) and +0x17C..+0x181 (packet_end in render_map_cell_mesh,
 * tile flags in render_shaded_map_tiles, a normal SVECTOR loaded by gte_ldv0 in draw_empty_map_cell_quads)
 * play different roles per function and stay padding. */
typedef struct MapCellScratch {
    /* 0x000 */ s32 color;
    /* 0x004 */ s32 lit_color;
    /* 0x008 */ s32 cur_x;
    /* 0x00C */ s32 cur_y;
    /* 0x010 */ s32 step;
    /* 0x014 */ s32 min_x;
    /* 0x018 */ s32 max_x;
    /* 0x01C */ ScanEdge edges[4];
    /* 0x0BC */ s32 ot_base;
    /* 0x0C0 */ u8 pad_0C0[8];
    /* 0x0C8 */ s32 otz;
    /* 0x0CC */ u8 pad_0CC[8];
    /* 0x0D4 */ s32 otz4;
    /* 0x0D8 */ s32 flag;
    /* 0x0DC */ s32 opz;
    /* 0x0E0 */ MapCellVertex v[4]; /* xy stored as one word, z read as u16 */
    /* 0x100 */ u8 pad_100[0x10];
    /* 0x110 */ s32 overlay_color;
    /* 0x114 */ s32 map_width;
    /* 0x118 */ s32 map_height;
    /* 0x11C */ s32 column_mask;
    /* 0x120 */ s32 row_mask;
    /* 0x124 */ s32 width_shift;
    /* 0x128 */ s32 height_shift;
    /* 0x12C */ u16 cell_height;
    /* 0x12E */ u8 pad_12E[6];
    /* 0x134 */ s32 column;
    /* 0x138 */ s32 row_base;
    /* 0x13C */ s32 neighbor_index;
    /* 0x140 */ u8 pad_140[4];
    /* 0x144 */ s32 cell_index;
    /* 0x148 */ s32 min_height;
    /* 0x14C */ s32 last_normal;
    /* 0x150 */ u8 pad_150[8];
    /* 0x158 */ s32 view_height; /* written after sample_terrain_surface_height returns */
    /* 0x15C */ u8 pad_15C[8];
    /* 0x164 */ s32 vtx;
    /* 0x168 */ u8 pad_168[4];
    /* 0x16C */ u16 face_tex;
    /* 0x16E */ u8 face_skip;
    /* 0x16F */ u8 face_flags;
    /* 0x170 */ u16 halfword_170; /* face attribute x in render_map_cell_mesh and render_shaded_map_tiles; the edge count handed to init_polygon_edges in draw_empty_map_cell_quads */
    /* 0x172 */ u16 face_attr_y;
    /* 0x174 */ u16 active_edges;
    /* 0x176 */ u16 draw_mode;
    /* 0x178 */ u16 blend;
    /* 0x17A */ u8 pad_17A[0x92];
    /* 0x20C */ u16 uv_scroll; /* town tile renderer; stored as a halfword, read back through (u8) value casts */
    /* 0x20E */ u8 pad_20E[2];
} MapCellScratch;
#define MAP_CELL_SCRATCH ((MapCellScratch *)0x1F800000)

typedef struct CdCueMotionOwner {
    u8 pad_00[6];
    u16 count;
    u8 pad_08[4];
    s32 status;
} CdCueMotionOwner;

typedef struct CdCueFadeOwner {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0xC];
    u32 value_14;
} CdCueFadeOwner;

typedef struct CdCueColorOwner {
    u8 pad_00[6];
    u16 count;
    u8 pad_08[0x10];
    s32 status;
} CdCueColorOwner;

/* Shared 16-byte body prefix used by the staged-motion and two fade children. */
struct Controller;
typedef struct CdCueEffectBody {
    union {
        struct Controller *controller;
        CdCueMotionOwner *motion;
        CdCueFadeOwner *fade;
        CdCueColorOwner *color;
    } owner;
    s16 state;
    s16 timer;
    u8 pad_08[2];
    s16 index;
    s16 completion;
} CdCueEffectBody;

#include "shared/object_node.h"
typedef struct CdCueEffectNode {
    ObjectNodeHeader header;
    CdCueEffectBody body;
} CdCueEffectNode;

void init_arc_motion_sprite(CdCueEffectNode *object, struct Controller *owner);

/* Sprite sources the fade-in-out effect cycles through (seven retail pointers), indexed by its entry index. */
extern void *fade_effect_visual_table[7];

struct ColorState800517CC;
struct Controller;
struct EffectState800517CC;
struct Main;
struct S_52CE0;
struct S_52CE0_Ent;
struct S_52CE0_Pos;
struct ObjectNodeHeader;
struct AnimatedSelectionMenuBody;
struct S_800504B4;
struct S_80050640;
struct ObjectNodeHeader;
struct S_80051E94;
struct CdCueSequenceBody;
struct VecState800517CC;

/* append_draw_mode_primitive.c */
void append_draw_mode_primitive(void);

/* begin_fade_out_intensity.c */
void begin_fade_out_intensity(void);

/* begin_fade_to_black.c */
void begin_fade_to_black(void);

/* clear_fade_manager.c */
void clear_fade_manager(void);

/* create_callback_node.c */
void create_marked_callback_node(void);

/* create_cd_cue_effect.c */
void create_cd_cue_effect(void);

/* create_deferred_resource_transition_task.c */
void schedule_deferred_resource_transition(struct ResourceTransitionBody *object);

/* decay_gauge_counters.c */
void decay_gauge_counters(struct S_800504B4 *object, s32 unused_arg1, s32 unused_arg2);

/* fade_effect_parts.c */
struct MenuSelectionBody;
void fade_effect_parts(struct MenuSelectionBody *effect, void *unused, void *parts);

/* fade_manager_step_black.c */
void fade_manager_step_black(FadeManagerBody *manager, struct ObjectPosition *unused_state, SpriteFrameState *fade_state);

/* fade_manager_step_out.c */
void fade_manager_step_out(FadeManagerBody *manager, struct ObjectPosition *unused, SpriteFrameState *data);

/* flag_fade_manager_dirty.c */
void flag_fade_manager_dirty(void);

/* has_tile_coordinate_pair.c */
s32 has_tile_coordinate_pair(s32 first_value, s32 second_value);

/* init_color_fade_effect.c */
void init_color_fade_effect(CdCueEffectNode *object, struct Controller *context);

/* init_fade_in_out_effect.c */
void init_fade_in_out_effect(CdCueEffectNode *object, struct Controller *owner);

/* link_typed_list_node.c */
void link_typed_list_node(struct ObjectNodeHeader *anchor, struct ObjectNodeHeader *node);

/* dispatch_after_controller_release.c */
void *dispatch_after_controller_release(void *data);

/* play_timed_animation_sequence.c */
void play_timed_animation_sequence(struct CdCueSequenceBody *sequence);

/* ramp_fade_up_fast.c */
void ramp_fade_up_fast(FadeManagerBody *manager, struct ObjectPosition *unused, SpriteFrameState *state);

/* ramp_fade_up_slow.c */
void ramp_fade_up_slow(FadeManagerBody *manager, struct ObjectPosition *unused, SpriteFrameState *state);

/* reorder_selection_menu_entries.c */
void reorder_selection_menu_entries(struct AnimatedSelectionMenuBody *list);

/* mark_group_for_removal.c */
void func_800530C4(struct Main *main);
void mark_group_for_removal(struct Main *main);

/* resolve_animated_selection_menu.c */
void *ensure_selection_menu_and_register_draw(struct ObjectNodeHeader *object);

/* init_polygon_edges.c */
s32 init_polygon_edges(void *vertex_data, s32 *edges, u16 *edge_count);

/* shallow.c */
s16 intersect_view_ray_with_depth_plane(SVECTOR *start, SVECTOR *end, SVECTOR *result, s16 target_z);

/* relocate_resource_type_lists.c */
void relocate_resource_type_lists(u8 *data_base, s16 type_index);

/* sync_saved_view_vectors.c */
s32 sync_saved_view_vectors(void);

/* set_destination_flag_from_source.c */
void initialize_shared_sprite_fade_display(void);

/* start_gauge_ramp.c */
void start_gauge_ramp(struct S_80050640 *obj);

/* tick_screen_fade_slots.c */
void tick_screen_fade_slots(void);

/* update_color_fade_effect.c */
void update_color_fade_effect(CdCueEffectBody *effect, ObjectPosition *unused_1, SpriteFrameState *color, void *unused_3);

/* update_fade_in_out_effect.c */
void update_fade_in_out_effect(CdCueEffectBody *state, ObjectPosition *unused_arg, SpriteFrameState *visual);

/* update_scene_effect_controller.c */
void func_80052144(struct Controller *controller);
void update_scene_effect_controller(struct Controller *controller);

/* update_shaded_line_effect.c */
void func_80052CE0(struct S_52CE0 *anim, struct S_52CE0_Pos *position, struct S_52CE0_Ent *entity);
void update_shaded_line_effect(struct S_52CE0 *anim, ObjectPosition *position, SpriteFrameState *entity);

/* update_sine_motion_effect.c */
void func_800517CC(struct EffectState800517CC *effect, struct VecState800517CC *motion, SpriteFrameState *color);
void update_sine_motion_effect(struct EffectState800517CC *effect, ObjectPosition *motion, SpriteFrameState *color);

/* update_staged_motion_effect.c */
void update_staged_motion_effect(CdCueEffectBody *obj, ObjectPosition *position, SpriteFrameState *flags);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/gpu_packets.h"
#include "shared/menu_display.h"
void init_gauge_object(struct MenuSelectionBody *object, void *context);
void init_gauge_blocks(struct MenuSelectionBody *owner, MenuDisplayNode *object, MenuDisplayBlock *primary_data, DisplayPositionWords *secondary_data);

s32 calc_gauge_fill(ActorRecord *state);

#endif
