/* Complete resident-engine cohort contract. Review pending. */
#ifndef DUNGEON_ENGINE_ENTITY_PANEL_H
#define DUNGEON_ENGINE_ENTITY_PANEL_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/entity_height_offsets.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"

/* Per-object countdown and selected palette-row offset for entity panels. */
typedef struct EntityPanelObjectBody {
    u16 ticks_remaining;
    u16 palette_row_offset;
} EntityPanelObjectBody;

/* Retail allocator return and flag word; identical to the incoming shared declaration. */
void *allocate_flagged_object_node(int flags);
#endif
