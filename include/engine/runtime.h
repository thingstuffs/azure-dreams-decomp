#ifndef ENGINE_RUNTIME_H
#define ENGINE_RUNTIME_H
#include "engine/menu/animated_selection_body.h"
/* Prototypes of the functions defined in src/engine/runtime/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_8004FE78_a0;

/* refresh_items_and_add_counter.c */
void refresh_items_and_add_counter(void);

/* cd_inc_retry_counters.c */
void cd_inc_retry_counters(void);
void func_8003E70C(void);

/* clear_resident_bit.c */
void clear_resident_bit(s16 value);

/* create_animated_selection_menu_entries.c */
s32 create_animated_selection_menu_entries(AnimatedSelectionMenuBody *state);

/* destroy_animated_selection_menu.c */
void destroy_animated_selection_menu(struct S_8004FE78_a0 *entity);

/* poll_window_switch_flags.c */
int poll_window_switch_flags(void);

/* set_resident_bit.c */
void set_resident_bit(s16 value);

/* set_dungeon_exit_flags.c */
void set_dungeon_exit_flags(s32 mode);

/* test_resident_bit.c */
s32 func_80033BC0(s16 value);
s32 test_resident_bit(s16 value);

#endif
