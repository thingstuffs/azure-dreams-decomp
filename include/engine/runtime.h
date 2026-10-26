#ifndef ENGINE_RUNTIME_H
#define ENGINE_RUNTIME_H
/* Prototypes of the functions defined in src/engine/runtime/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_8004FE78_a0;

/* add_counter_increment_capped.c */
void add_counter_increment_capped(void);

/* cd_inc_retry_counters.c */
void cd_inc_retry_counters(void);
void func_8003E70C(void);

/* clear_resident_bit.c */
void clear_resident_bit(s16 value);

/* create_animated_selection_menu_entries.c */
s32 create_animated_selection_menu_entries(void *state);

/* destroy_animated_selection_menu.c */
void destroy_animated_selection_menu(struct S_8004FE78_a0 *entity);

/* poll_resident_slot.c */
int poll_resident_slot(void);

/* set_resident_bit.c */
void set_resident_bit(s16 value);

/* set_resident_mode_flags.c */
void set_resident_mode_flags(s32 mode);

/* test_resident_bit.c */
s32 func_80033BC0(s16 value);
s32 test_resident_bit(s16 value);

#endif
