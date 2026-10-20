#ifndef MAIN_TITLE_CALLBACKS_H
#define MAIN_TITLE_CALLBACKS_H
#include "common.h"

struct Menu;
struct MainTitleValueEntry;
struct MainValue;
struct ColorRampEffect;
struct ColorEffect;
s32 queue_settings_sprite_grid(u8 *entry_data, u8 *scroll_data);
void assign_object_descriptor_on_check(s32 object_data_addr);
void run_flag_handler_and_set_2000_flags(void *entry);
void mark_object_flags_dirty(unsigned short *data);
void func_80089A14(unsigned short *data);
void handle_settings_menu_input(struct Menu *menu);
s32 build_settings_sprite_tiles(void *node_data, void *scroll_state);
void propagate_record_high_bit(void *record);
void load_indexed(void *entry);
void load_table(struct MainTitleValueEntry *entry);
void pack_three_capped_components_and_flag(void *dest);
void set_output(struct MainValue **value_slot, u8 *output, struct MainValue *value);
void update_settings_effect_color(struct ColorRampEffect *effect);
void cycle_owner_effect_color(struct ColorEffect *effect);
#endif
