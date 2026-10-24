#ifndef ENGINE_EFFECT_H
#define ENGINE_EFFECT_H
/* Prototypes of the functions defined in src/engine/effect/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"

struct ColorState800517CC;
struct Controller;
struct EffectState800517CC;
struct Func8003C4C8State;
struct Main;
struct S_52CE0;
struct S_52CE0_Ent;
struct S_52CE0_Pos;
struct S_80044AAC;
struct S_8004EC20;
struct S_8004F884_arg;
struct S_800504B4;
struct S_80050640;
struct S_80050EF8;
struct S_80051548_Flags;
struct S_80051548_Obj;
struct S_80051CC4_Ptr;
struct S_80051CC4_Sub;
struct S_80051E94;
struct S_80051F58;
struct S_80051F58_a2;
struct S_800520B4;
struct S_8005313C;
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
void decay_gauge_counters(struct S_800504B4 *object);

/* fade_effect_parts.c */
void fade_effect_parts(void *effect, void *unused, void *parts);

/* fade_manager_step_black.c */
void fade_manager_step_black(s32 *active_flag, struct Func8003C4C8State *unused_state, struct Func8003C4C8State *fade_state);

/* flag_fade_manager_dirty.c */
void flag_fade_manager_dirty(void);

/* has_runtime_key_pair.c */
s32 has_runtime_key_pair(s32 first_value, s32 second_value);

/* init_color_fade_effect.c */
void init_color_fade_effect(struct S_800520B4 *object, void *context);

/* init_fade_in_out_effect.c */
void init_fade_in_out_effect(struct S_80051E94 *object, s32 sub_value);

/* link_typed_list_node.c */
void link_typed_list_node(struct S_80044AAC *anchor, struct S_80044AAC *node);

/* pad_both_key_states_clear.c */
void *dispatch_after_controller_release(void *data);

/* play_timed_animation_sequence.c */
void play_timed_animation_sequence(struct S_8005313C *sequence);

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
void update_color_fade_effect(struct S_80051F58 *effect, void *unused_1, struct S_80051F58_a2 *color, void *unused_3);

/* update_fade_in_out_effect.c */
void update_fade_in_out_effect(struct S_80051CC4_Sub *state, void *unused_arg, struct S_80051CC4_Ptr *visual);

/* update_scene_effect_controller.c */
void func_80052144(struct Controller *controller);
void update_scene_effect_controller(struct Controller *controller);

/* update_shaded_line_effect.c */
void func_80052CE0(struct S_52CE0 *anim, struct S_52CE0_Pos *position, struct S_52CE0_Ent *entity);
void update_shaded_line_effect(struct S_52CE0 *anim, struct S_52CE0_Pos *position, struct S_52CE0_Ent *entity);

/* update_sine_motion_effect.c */
void func_800517CC(struct EffectState800517CC *effect, struct VecState800517CC *motion, SpriteFrameState *color);
void update_sine_motion_effect(struct EffectState800517CC *effect, struct VecState800517CC *motion, SpriteFrameState *color);

/* update_staged_motion_effect.c */
void update_staged_motion_effect(struct S_80051548_Obj *obj, IntVector3 *position, SpriteFrameState *flags);

#endif
