#ifndef TOWN_SCENE_RESOURCE_REQUEST_DATA_H
#define TOWN_SCENE_RESOURCE_REQUEST_DATA_H

#include "common.h"

/* Request index at 0x800CF874, shared by town and dungeon resource loaders. */
extern s32 town_resource_request;

/* First word receives the CD resource load result. */
extern s32 loaded_town_resource_attributes[];

#endif
