#ifndef FRONTEND_SETTINGS_H
#define FRONTEND_SETTINGS_H
/* Prototypes of the functions defined in src/frontend/settings/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct ColorEffect;
struct ColorRampEffect;
struct MainTitleValueEntry;
struct Menu;
struct Motion;
struct Obj;
struct S_7FDD3A2C_1;
struct State;

/* build_settings_sprite_tiles.c */
s32 build_settings_sprite_tiles(void *node_data, void *scroll_state);

/* create_settings_controller.c */
void create_settings_controller(void);

/* create_type.c */
void *create_type(struct S_7FDD3A2C_1 *position, s32 object_value, s32 render_value, s32 extra_value);

/* handle_settings_menu_input.c */
void handle_settings_menu_input(struct Menu *menu);

/* initialize_and_submit_record.c */
void initialize_and_submit_record(s32 value, void *data);

/* initialize_available.c */
void initialize_available(s32 value, void *data);

/* initialize_settings_screen.c */
void initialize_settings_screen(void);

/* load_indexed.c */
void load_indexed(void *entry);

/* load_signed_state.c */
void update_settings_color_cycle(struct ColorEffect *effect);

/* load_table.c */
void load_table(struct MainTitleValueEntry *entry);

/* pack_three_capped_components_and_flag.c */
void pack_three_capped_components_and_flag(void *dest);

/* propagate_record_high_bit.c */
void propagate_record_high_bit(void *record);

/* queue_settings_sprite_grid.c */
s32 queue_settings_sprite_grid(u8 *entry_data, u8 *scroll_data);

/* update_settings_effect.c */
void update_settings_effect(void *effect);

/* update_settings_effect_color.c */
void update_settings_effect_color(struct ColorRampEffect *effect);

/* update_settings_effect_object.c */
void update_settings_effect_object(void *object, void *motion, void *sprite);

/* update_settings_menu_animation.c */
void update_settings_menu_animation(struct Obj *obj, s32 *position);

/* update_settings_phase_motion.c */
void update_settings_phase_motion(struct State *state, struct Motion *motion, void *update_data);

#endif
