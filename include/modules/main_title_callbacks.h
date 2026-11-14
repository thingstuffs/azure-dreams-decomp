#ifndef MAIN_TITLE_CALLBACKS_H
#define MAIN_TITLE_CALLBACKS_H
#include "common.h"

struct Menu;
struct MainTitleValueEntry;
struct MainValue;
struct ColorRampEffect;
struct ColorEffect;
struct ObjectPosition;
s32 queue_settings_sprite_grid(u8 *entry_data, u8 *scroll_data);
void start_settings_after_transition(void *object_data_addr);
void create_settings_controller_and_flag_removal(void *entry);
void mark_node_for_removal(unsigned short *data);
void func_80089A14(unsigned short *data);
void handle_settings_menu_input(struct Menu *menu);
s32 build_settings_sprite_tiles(void *node_data, struct ObjectPosition *scroll_state);
void remove_value_entry_with_marked_source(void *record);
void update_color_channel_entry(void *entry);
void update_volume_slider_entry(struct MainTitleValueEntry *entry);
void update_packed_color_entry(void *dest);
void set_output(struct MainValue **value_slot, u8 *output, struct MainValue *value);
void update_settings_effect_color(struct ColorRampEffect *effect);
void cycle_owner_effect_color(struct ColorEffect *effect);
#endif
