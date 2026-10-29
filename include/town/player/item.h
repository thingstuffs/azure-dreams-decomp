#ifndef TOWN_PLAYER_ITEM_H
#define TOWN_PLAYER_ITEM_H
/* Prototypes of the functions defined in src/town/player/item/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

struct S_800947CC_1;

/* get_linked_carry_item_data.c */
void *get_linked_carry_item_data(void *record, s32 unused_first, s32 unused_second);

/* initialize_returned_item_action.c */
void initialize_returned_item_action(Rec_func_80094268_arg0 *object, struct S_800947CC_1 *settings, void *ptr2);

/* plt_carry_item_del_ext.c */
void plt_carry_item_del_ext(void);

/* set_hold_item_callback.c */
s32 set_hold_item_callback(void);

/* set_item_selection_data_pointer.c */
void set_item_selection_data_pointer(void *object, void *unused_position, void *unused_context);

/* set_return_item_callback.c */
s32 set_return_item_callback(void);

#endif
