#ifndef TOWN_SCENE_RESOURCE_H
#define TOWN_SCENE_RESOURCE_H

#include "common.h"


/* initialize_resources_assigns_pointer_lookup.c */
void initialize_resources_assigns_pointer_lookup(void);

void reset_resource_entry(s32 index);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void reserve_twch_load(s32 character_id);

#endif
