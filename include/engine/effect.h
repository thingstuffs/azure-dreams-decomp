#ifndef ENGINE_EFFECT_H
#define ENGINE_EFFECT_H
struct ObjectPosition;
/* Prototypes of the functions defined in src/engine/effect/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "engine/effect/fade_manager.h"
#include "engine/effect/screen_fade.h"
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"
#include "shared/entity.h"

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

void scene_initialize_arc_motion_sprite(CdCueEffectNode *object, struct Controller *owner);

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
struct S_8004F884_arg;
struct S_800504B4;
struct S_80050640;
struct S_80050EF8;
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
void schedule_deferred_resource_transition(void *object);

/* decay_gauge_counters.c */
void decay_gauge_counters(struct S_800504B4 *object, s32 unused_arg1, s32 unused_arg2);

/* fade_effect_parts.c */
void fade_effect_parts(void *effect, void *unused, void *parts);

/* fade_manager_step_black.c */
void fade_manager_step_black(FadeManagerBody *manager, struct ObjectPosition *unused_state, SpriteFrameState *fade_state);

/* fade_manager_step_out.c */
void fade_manager_step_out(FadeManagerBody *manager, struct ObjectPosition *unused, SpriteFrameState *data);

/* flag_fade_manager_dirty.c */
void flag_fade_manager_dirty(void);

/* has_runtime_key_pair.c */
s32 has_runtime_key_pair(s32 first_value, s32 second_value);

/* init_color_fade_effect.c */
void init_color_fade_effect(CdCueEffectNode *object, struct Controller *context);

/* init_fade_in_out_effect.c */
void init_fade_in_out_effect(CdCueEffectNode *object, struct Controller *owner);

/* link_typed_list_node.c */
void link_typed_list_node(struct ObjectNodeHeader *anchor, struct ObjectNodeHeader *node);

/* pad_both_key_states_clear.c */
void *dispatch_after_controller_release(void *data);

/* play_timed_animation_sequence.c */
void play_timed_animation_sequence(struct CdCueSequenceBody *sequence);

/* ramp_fade_up_fast.c */
void ramp_fade_up_fast(FadeManagerBody *manager, struct ObjectPosition *unused, SpriteFrameState *state);

/* ramp_fade_up_slow.c */
void ramp_fade_up_slow(FadeManagerBody *manager, struct ObjectPosition *unused, SpriteFrameState *state);

/* reorder_and_interpolate_selection_menu_entries.c */
void reorder_and_interpolate_selection_menu_entries(struct S_8004F884_arg *list);

/* reset_group_and_flag_children.c */
void func_800530C4(struct Main *main);
void reset_group_and_flag_children(struct Main *main);

/* resolve_animated_selection_menu.c */
void *ensure_selection_menu_and_register_draw(struct S_80050EF8 *object);

/* runtime_initialize_polygon_edges.c */
s32 runtime_initialize_polygon_edges(void *vertex_data, s32 *edges, u16 *edge_count);

/* runtime_set_list_pointers_from_type_offsets.c */
void runtime_set_list_pointers_from_type_offsets(s32 data_base, s16 type_index);

/* runtime_update_saved_vectors.c */
s32 runtime_update_saved_vectors(void);

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
void init_gauge_blocks(void *unused, MenuDisplayNode *object, MenuDisplayBlock *primary_data, DisplayPositionWords *secondary_data);

#endif
