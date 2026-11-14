#ifndef TOWN_MINIGAME_KEIMA_SELECTION_MASK_DATA_H
#define TOWN_MINIGAME_KEIMA_SELECTION_MASK_DATA_H

#include "common.h"

/* Single signed selection mask at 0x80113158.  Sign by opposite-sign trial over its three units
 * (update_keima_selection_menu, update_keima_minigame, randomize_keima_payout_factors): as s16
 * no value cast is needed; as u16 the copy and the two zero tests in update_keima_minigame load lhu
 * where retail loads lh, also with (s16) value casts at those three reads. */
extern s16 keima_selection_mask;

#endif
