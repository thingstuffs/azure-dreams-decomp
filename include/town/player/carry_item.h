#ifndef TOWN_PLAYER_CARRY_ITEM_H
#define TOWN_PLAYER_CARRY_ITEM_H

#include "common.h"

struct ObjectPosition;
struct SpriteFrameState;

/* The node supplies position and sprite; the lookup only reads record. */
void *get_linked_carry_item_data(void *record, struct ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);
void *plt_carry_on_chk_ext(void);
void plt_carry_item_del_ext(void);

#endif
