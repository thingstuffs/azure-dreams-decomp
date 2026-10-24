#ifndef TOWN_PLAYER_CARRY_ITEM_H
#define TOWN_PLAYER_CARRY_ITEM_H

#include "common.h"

/* The two context words are forwarded by callers; the lookup only reads record. */
void *get_linked_carry_item_data(void *record, s32 unused_first, s32 unused_second);
void *plt_carry_on_chk_ext(void);
void plt_carry_item_del_ext(void);

#endif
