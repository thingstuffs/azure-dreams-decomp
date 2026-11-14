#ifndef TOWN_PERSON_CALLBACK_OBJECT_RESET_G00688_H
#define TOWN_PERSON_CALLBACK_OBJECT_RESET_G00688_H
struct TownObjectRecord;
/* shared declarations for callback object reset. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800CEC24. */

#include "common.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "m2c_compat.h"
#include "shared/object_index_slots.h"


s32 create_burst_particle_spawner(s32 *);
#include "town/person/object_setup.h"
extern u8 D_800D6CA8[];

/* Functions defined in this translation unit. */
void create_object_and_brighten(struct TownObjectRecord *object, void *context, SpriteFrameState *callback_arg);
void reset_object_entry_and_brighten(struct TownObjectRecord *object, void *draw_arg, SpriteFrameState *packet);

#endif
