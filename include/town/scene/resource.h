#ifndef TOWN_SCENE_RESOURCE_H
#define TOWN_SCENE_RESOURCE_H

#include "common.h"


/* init_okami_give_cape_state.c */
void init_okami_give_cape_state(void);

void reset_resource_entry(s32 index);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void reserve_twch_load(s32 character_id);

void reserve_tw_mon_load(s32 reservation_value);

#endif
