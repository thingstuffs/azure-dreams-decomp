#ifndef SHARED_ENTITY_OBJECTS_H
#define SHARED_ENTITY_OBJECTS_H

#include "shared/entity.h"

/* Object records that live at fixed addresses (SLUS .bss).  Names stay address-based until evidence names them.
 * D_80083780: the static player's position record.  initialize_dungeon_actor (and the town scene initializer)
 * clear it with six words and store it in the static node's position slot (ObjectNodeHeader +0x08), so it is an
 * ObjectPosition (r121 opus_entity2): x/y/z 16.16 words read whole and as integer halves, velocities at
 * 0x0C/0x10/0x14; gameWork's view-state vector 2 is loaded from its fields (r78 phase 5). */
extern ObjectPosition view_reference_entity;

#endif
