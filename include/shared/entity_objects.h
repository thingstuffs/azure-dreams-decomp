#ifndef SHARED_ENTITY_OBJECTS_H
#define SHARED_ENTITY_OBJECTS_H

#include "shared/entity.h"

/* Entity records that live at fixed addresses (SLUS .bss).  Names stay address-based until evidence names them.
 * D_80083780: the struct census rooted Rec_D_800E3D7C (the entity record) at it in 6 functions that take an entity;
 * its accesses fit the EntityRec layout (x/y/z Fixed32 read whole and as integer halves, words at 0x0C/0x10/0x14);
 * gameWork's view-state vector 2 is loaded from its fields (r78 phase 5). */
extern EntityRec D_80083780;

#endif
